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

		if (PeekVariableDeclaration(line))
			cout << " 为变量声明 ";

// 		if (PeekVariableDefinition(line))
// 			cout << " 为函数定义 " << endl;


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
	if (line.size() == 1 &&
		line[0].GetType() == TokenType::Identifier ||
		line[0].GetType() == TokenType::Literal ||
		line[0].GetType() == TokenType::Number)
		return true;
	TokenType typeLimit = TokenType::None;
	stack<Token> stk;
	
	for (size_t i = line.size() - 1; i >= 0; i--)
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
	return false;
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
bool Parser::PeekVariableDeclaration(std::vector<Token>& line)
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
				if (line[i].GetType() != TokenType::Operator || line[i].GetText() != ",")
				{
					return false;
				}
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

ParserNode* Parser::GetVariableDeclaration()
{
	return nullptr;

}
bool Parser::PeekVariableDefinition()
{
	return false;
}
ParserNode* Parser::GetVariableDefinition()
{
	return nullptr;

}