#include "Parser.h"
using namespace std;
Parser::Parser(Lexer* lex)
{
	lexer = lex;
}
ParserNode* Parser::GenerateAST()
{
	ParserNode* root = new ParserNode(ParserType::None, Token());
	auto line = lexer->PeekLine();
	while (line.size() > 0)
	{
		if (line[0].GetType() == TokenType::Keyword)
		{
			if (PeekClass(line))
			{
				auto ptr = GetClass();
				if(ptr != nullptr)
					root->childrenNode.push_back(ptr);
			}
			else
			{

			}
		}
		else
		{
			cout << "cant handle line:" + line[0].GetLineNumber() << endl;
		}
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
bool Parser::PeekFunctionCall()
{
	return false;
}


ParserNode* Parser::GetFunctionCall() 
{

	return nullptr;
}
bool Parser::PeekFunctionDeclaration(std::vector<Token>& line)
{
	auto typ = line[0].GetType();
	auto checkDeclaration = [&line]() ->bool
	{
		auto typ = line[1].GetType();
		if (typ == TokenType::Keyword || typ == TokenType::Identifier)
		{
			stack<Token> stk;
			
			for (int i = 2; i < line.size(); i++)
			{
				if(stk.empty())
					stk.push(line[i]);
				else
				{
					if (stk.top().GetType() == TokenType::Identifier)
					{
						stk.pop();
						if (stk.top().GetType() == TokenType::Operator &&
							stk.top().GetText() == ",")
							stk.pop();
					}
					stk.push(line[i]);
				}
			}
			if (stk.top().GetType() == TokenType::Operator &&
				stk.top().GetText() == ")")
			{
				stk.pop();
				auto temp = stk.top();
				stk.pop();
				if (stk.empty() && temp.GetText() == "(" &&
					temp.GetType() == TokenType::Operator)
					return true;
			}
		}
		return false;
	};
	if (typ == TokenType::Keyword || typ == TokenType::Identifier)
	{

	

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