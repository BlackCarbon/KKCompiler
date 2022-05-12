#include <bits/stdc++.h>
#include "Token.h"
using namespace std;

const Token Token::TokenEOF = Token(TokenType::None, "", - 1, -1);
const string Token::TokenEOL = "\\n";
const std::unordered_map<std::string, KeyWordType> Token::Keywords{
{"main", KeyWordType::Main},
{"print", KeyWordType::Func},
{"while", KeyWordType::Condition}, {"if", KeyWordType::Condition}, {"for", KeyWordType::Condition}, {"do", KeyWordType::Condition},
{"else", KeyWordType::Other}, {"return" , KeyWordType::Other}, {"continue", KeyWordType::Other}, {"then", KeyWordType::Other}, {"end", KeyWordType::Other},
{"class", KeyWordType::Class},
{"int", KeyWordType::Type}, {"float", KeyWordType::Type}, {"char", KeyWordType::Type},
{"var", KeyWordType::Var},
{"void", KeyWordType::Void},
{"nil", KeyWordType::Nil}
};
Token::Token(TokenType t, std::string val, int line, int column)
{
	type = t;
	value = val;
	lineNumber = line;
	columnNumber = column;
}
Token::Token()
{
	type = TokenType::None;
	value = TokenEOL;
	lineNumber = -1;
	columnNumber = -1;
}
Token::~Token() {}
int Token::GetLineNumber() const
{
	return lineNumber;
}
int Token::GetColumnNumber() const
{
	return columnNumber;
}
int Token::GetNumber() const
{
	if (type == TokenType::Number)
		return	atoi(value.c_str());
	return -1;
}
std::string  Token::GetText() const
{
	return value;
}
TokenType Token::GetType() const
{
	return type;
}
std::string Token::GetTypeString() const
{
	switch (type)
	{
	case TokenType::Number:
		return "Number";
	case TokenType::Identifier:
		return "Identifier";
	case TokenType::Operator:
		return "Operator";
	case TokenType::Literal:
		return "Literal";
	case TokenType::Keyword:
		return "Keyword";
	default:
		break;
	}
	return "None";
}