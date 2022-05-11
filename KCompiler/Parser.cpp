#include "Parser.h"
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
		cout << "line: " << line[0].GetLineNumber() << "¡¾";
		for (int i = 0; i < line.size(); i++)
			cout << " " << line[i].GetText();
		cout << " ¡¿";
		if (PeekClass(line))
			cout << " is Class. " << endl;

		if (PeekFunctionCall(line))
			cout << " is FunctionCall. " << endl;

		if (PeekFunctionDeclaration(line))
			cout <<" is FunctionDeclaration. " << endl;

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
	if (line.size() == 2 && line[0].GetType() == TokenType::Keyword && line[0].GetText() == "class"
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
bool Parser::PeekFormula()
{
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
	if (typ == TokenType::Identifier)
	{
		stack<Token> stk;
		for (int i = 1; i < line.size(); i++)
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
bool Parser::PeekFunctionDeclaration(std::vector<Token>& line)
{
	if (line.size() < 2)
		return false;
	auto typ = line[0].GetType();
	auto typ1 = line[1].GetType();
	if ((typ == TokenType::Keyword || typ == TokenType::Identifier) && 
		(typ1 == TokenType::Keyword || typ1 == TokenType::Identifier))
	{
		stack<Token> stk;
		for (int i = 2; i < line.size(); i++)
		{
			if (!stk.empty())
			{
				if (line[i].GetType() == TokenType::Operator &&
					stk.top().GetType() == TokenType::Identifier)
				{
					stk.pop();
					if (stk.top().GetType() == TokenType::Identifier ||
						stk.top().GetType() == TokenType::Keyword)
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

ParserNode* Parser::GetFunctionDeclaration()
{
	return nullptr;

}
bool Parser::PeekFunctionDefinition()
{
	return false;
}

ParserNode* Parser::GetFunctionDefinition()
{
	return nullptr;

}
bool Parser::PeekVariableDeclaration()
{
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