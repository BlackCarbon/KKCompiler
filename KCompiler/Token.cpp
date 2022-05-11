#include <bits/stdc++.h>
#include "Token.h"
using namespace std;

const Token Token::TokenEOF = Token(TokenType::None, "", - 1, -1);
const string Token::TokenEOL = "\\n";
const std::unordered_set<std::string> Token::Keywords{
"main", "print", "class",
"int", "float", "char", "void", "nil",
"while", "if", "else", "for", "return", "continue", "do", "then", "end"
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