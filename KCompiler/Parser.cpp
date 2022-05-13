#include "Parser.h"
#include "OperatorRule.h"
using namespace std;
Parser::Parser(Lexer* lex)
{
	lexer = lex;
}
ParserNode* Parser::GenerateAST()
{
	ParserNode* root = new ParserNode(ParserType::None, Token());
	//auto line = lexer->PeekLine();
	auto line = lexer->GetLine();
	while (line.size() > 0)
	{
		cout << "line: " << line[0].GetLineNumber() << "【";
		for (size_t i = 0; i < line.size(); i++)
			cout << " " << line[i].GetText();
		cout << " 】";
		if (PeekClass(line))
			cout << " 为类定义 ";

		if (PeekFunctionCall(line))
			cout << " 为函数调用 ";

		if (PeekFunctionDefinition(line))
			cout <<" 为函数定义 ";

		if (PeekVariableFormula(line))
			cout << " 为算式 ";

		if (PeekVariableDefinition(line))
			cout << " 为变量声明定义 ";


		cout << endl;
		line = lexer->GetLine();
// 		if (line[0].GetType() == TokenType::Keyword)
// 		{
// 			if (PeekClass(line))
// 			{
// 				auto ptr = GetClass();
// 				if(ptr != nullptr)
// 					root->childrenNode.push_back(ptr);
// 			}
// 			else
// 			{
// 
// 			}
// 		}
// 		else
// 		{
// 			cout << "cant handle line:" + line[0].GetLineNumber() << endl;
// 		}
	}
	return root;
}

bool Parser::PeekClass(std::vector<Token>& line)
{
	if (line.size() == 2 && line[0].GetType() == TokenType::Keyword && (Token::Keywords.at(line[0].GetText())) == KeyWordType::Class
		&& line[1].GetType() == TokenType::Identifier)
		return true;
	return false;
}

ParserNode* Parser::GetClass()
{
	vector<vector<Token>> classContent;
// 	auto line = lexer->PeekLine();
// 	while (line[0].GetText() == "end")
// 	{
// 		line = lexer->GetLine();
// 		if (line.size() == 0)
// 		{
// 			cout << "this class is declared incorrectly in line:" << classContent[0][0].GetLineNumber() << endl;
// 			return nullptr;
// 		}
// 		classContent.push_back(line);
// 	}
// 	new ParserNode(ParserType::ClassDefinition, line[0]);
	return nullptr;
}
bool Parser::PeekFormula(std::vector<Token>& line)
{
	if (line.size() == 0)
		return false;
	if (line.size() == 1 && (line[0].GetType() == TokenType::Identifier || line[0].GetType() == TokenType::Literal || line[0].GetType() == TokenType::Number))
		return true;
	TokenType typeLimit = TokenType::None;
	stack<Token> stk;
	
	for (int i = line.size() - 1; i >= 0; i--)
	{
		auto typ = line[i].GetType();
		if (typ == TokenType::Identifier || typ == TokenType::Literal || typ == TokenType::Number || typ == TokenType::Operator)
		{
			if (typ == TokenType::Literal || typ == TokenType::Number)
			{
				if (typeLimit == TokenType::None)
					typeLimit = typ;
				else if (typeLimit != typ)
					return false;
			}
			stk.push(line[i]);
		}
		else
			return false;
	}
	auto tree = BuildFormulaTree(stk);
	if (tree != nullptr)
		return true;
	return false;
}

OperatorNode* Parser::BuildFormulaTree(std::stack<Token>& stk)
{
	vector<OperatorNode*> nodes;
	OperatorNode* root = new OperatorNode("");
	while (!stk.empty())
	{
		auto token = stk.top();
		stk.pop();
		OperatorNode* node = nullptr;
		if (token.GetType() == TokenType::Operator && token.GetText() == "(")
		{
			auto t = stk.top();
			stack<Token> temp;
			int count = 1;
			while (count > 0)
			{
				if (t.GetType() == TokenType::Operator)
				{
					if(t.GetText() == "(")
						count++;
					if (t.GetText() == ")")
						count--;
				}
				temp.push(t);
				stk.pop();
				if (stk.empty())
				{
					break;
				}
				t = stk.top();
			}
			temp.pop();
			stack<Token> result;
			while (!temp.empty())
			{
				result.push(temp.top());
				temp.pop();
			}
			node = BuildFormulaTree(result);
		}
		else if (token.GetType() == TokenType::Operator)
		{
			if (root->value != "")
			{
				for (size_t i = 0; i < nodes.size(); i++)
					delete nodes[i];
				delete root;
				return nullptr;
			}
			root->value = token.GetText();
			if (nodes.size() > 0 &&
				OperatorRule::operatorRule.at(root->value).priority > OperatorRule::operatorRule.at(nodes[nodes.size() - 1]->value).priority)
			{
				root->leftNode->parentNode = nullptr;
				root->leftNode = nodes[nodes.size() - 1]->rightNode;
				nodes[nodes.size() - 1]->rightNode->parentNode = root;
			}
		}
		else
		{
			node = new OperatorNode(token.GetText());
		}
		if (node != nullptr)
		{
			if (root->leftNode == nullptr)
				root->leftNode = node;
			else
			{
				root->rightNode = node;
				nodes.push_back(root);
				root = new OperatorNode("");
				root->leftNode = nodes[nodes.size() - 1];
				root->leftNode->parentNode = root;
			}
		}
	}
	if(nodes.size() > 0)
		return nodes[0];
	return nullptr;
}
ParserNode* Parser::GetFormula()
{
	return nullptr;

}
bool Parser::PeekFunctionCall(std::vector<Token>& line)
{
	if (line.size() < 1)
		return false;
	auto typ = line[0].GetType();
	if (typ == TokenType::Identifier || Token::Keywords.at(line[0].GetText()) == KeyWordType::Func)
	{
		stack<Token> stk;
		for (size_t i = 1; i < line.size(); i++)
		{
			if (!stk.empty())
			{
				if (stk.top().GetType() == TokenType::Identifier ||
					stk.top().GetType() == TokenType::Literal ||
					stk.top().GetType() == TokenType::Number)
				{
					stk.pop();
					if (stk.top().GetType() == TokenType::Operator &&
						stk.top().GetText() == ",")
						stk.pop();
				}
			}
			stk.push(line[i]);
		}
		if (!stk.empty() &&
			stk.top().GetType() == TokenType::Operator &&
			stk.top().GetText() == ")")
		{
			stk.pop();
			if (!stk.empty())
			{
				auto temp = stk.top();
				stk.pop();
				if (stk.empty() && temp.GetText() == "(" &&
					temp.GetType() == TokenType::Operator)
					return true;
			}
		}
	}
	return false;
}


ParserNode* Parser::GetFunctionCall() 
{

	return nullptr;
}
bool Parser::PeekFunctionDefinition(std::vector<Token>& line)
{
	if (line.size() < 2)
		return false;
	auto typ = line[0].GetType();
	auto typ1 = line[1].GetType();
	if (((typ == TokenType::Keyword && (Token::Keywords.at(line[0].GetText()) == KeyWordType::Type || (Token::Keywords.at(line[0].GetText())) == KeyWordType::Void)) || typ == TokenType::Identifier) &&
		(typ1 == TokenType::Identifier || (typ1 == TokenType::Keyword && (Token::Keywords.at(line[1].GetText())) == KeyWordType::Main)))
	{
		stack<Token> stk;
		for (size_t i = 2; i < line.size(); i++)
		{
			if (!stk.empty())
			{
				if (line[i].GetType() == TokenType::Operator &&
					stk.top().GetType() == TokenType::Identifier)
				{
					stk.pop();
					if (stk.top().GetType() == TokenType::Identifier ||
						(stk.top().GetType() == TokenType::Keyword && Token::Keywords.at(stk.top().GetText()) == KeyWordType::Type))
						stk.pop();
					else
						return false;
					if (stk.top().GetType() == TokenType::Operator &&
						stk.top().GetText() == ",")
						stk.pop();
				}
			}
			stk.push(line[i]);
		}
		if (!stk.empty() &&
			stk.top().GetType() == TokenType::Operator &&
			stk.top().GetText() == ")")
		{
			stk.pop();
			if (!stk.empty())
			{
				auto temp = stk.top();
				stk.pop();
				if (stk.empty() && temp.GetText() == "(" &&
					temp.GetType() == TokenType::Operator)
					return true;
			}
		}
	}
	return false;
}

ParserNode* Parser::GetFunctionDefinition()
{
	return nullptr;

}
bool Parser::PeekVariableFormula(std::vector<Token>& line)
{
	if (line.size() < 2)
		return false;
	auto typ = line[0].GetType();
	if (line[0].GetType() == TokenType::Identifier)
	{
		auto token = line[1];
		if (token.GetType() == TokenType::Operator && (token.GetText() == "++" || token.GetText() == "--") &&
			line.size() == 2)
			return true;

		if (token.GetType() == TokenType::Operator &&
			OperatorRule::operatorRule.count(token.GetText()) > 0 &&
			OperatorRule::operatorRule.at(token.GetText()).isAssignmentOperator)
		{
			vector<Token> vec;
			for (size_t k = 2; k < line.size(); k++)
				vec.push_back(line[k]);
			return PeekFormula(vec);
		}
		return false;
	}
	return false;

}

ParserNode* Parser::GetVariableFormula()
{
	return nullptr;

}
bool Parser::PeekVariableDefinition(std::vector<Token>& line)
{
	if (line.size() < 2)
		return false;
	auto typ = line[0].GetType();
	if (((typ == TokenType::Keyword && (Token::Keywords.at(line[0].GetText()) == KeyWordType::Type || Token::Keywords.at(line[0].GetText()) == KeyWordType::Var)) || typ == TokenType::Identifier) &&
		line[1].GetType() == TokenType::Identifier)
	{
		for (size_t i = 2; i < line.size(); i++)
		{
			if (i % 2 == 0)
			{
				if (line[i].GetType() == TokenType::Operator && line[i].GetText() == ",")
				{
					continue;
				}
				if (line[i].GetType() == TokenType::Operator && (line[i].GetText() == "++" || line[i].GetText() == "--") &&
					i == line.size() - 1)
					return true;
				if (line[i].GetType() == TokenType::Operator &&
					OperatorRule::operatorRule.count(line[i].GetText()) > 0 &&
					OperatorRule::operatorRule.at(line[i].GetText()).isAssignmentOperator)
				{
					vector<Token> vec;
					for (size_t k = i + 1; k < line.size(); k++)
						vec.push_back(line[k]);
					return PeekFormula(vec);
				}
				return false;
			}
			else
			{
				if (line[i].GetType() != TokenType::Identifier)
				{
					return false;
				}
			}
		}
		return true;
	}
	return false;
}
ParserNode* Parser::GetVariableDefinition()
{
	return nullptr;

}