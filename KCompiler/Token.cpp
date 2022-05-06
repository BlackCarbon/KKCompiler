#include <bits/stdc++.h>
#include "Token.h"
using namespace std;

const Token Token::TokenEOF = Token(TokenType::None, "", - 1, -1);
const string Token::TokenEOL = "\\n";

Token::Token(TokenType t, std::string val, int line, int column)
{
	type = t;
	value = val;
	lineNumber = line;
	columnNumber = column;
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
	case Number:
		return "Number";
	case String:
		return "String";
	case Identifier:
		return "Identifier";
	case Punctuation:
		return "Punctuation";
	case Operator:
		return "Operator";
	case Literal:
		return "Literal";
	default:
		break;
	}
	return "None";
}