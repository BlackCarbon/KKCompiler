#pragma once
#include "Token.h"
#include <regex>
class Lexer
{
private:
	int lineNumber;
	bool hasMore;
	std::queue<Token> q;
	std::ifstream file;
	std::regex rgx;
	bool FillQueue(int i);
protected:
	void ReadLine();
	void AddToken(int line, int clm, std::smatch mth);
	std::string ToStringLiteral(std::string s);

public:
	static const std::string regexPat;

	Lexer(std::string fileName);
	~Lexer();
	Token Read();
	Token Peek(int i);

};