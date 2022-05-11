#pragma once
#include "Token.h"
#include <regex>
class Lexer
{
private:
	static const std::string regexPat;

	int lineNumber;
	std::queue<Token> q;
	std::ifstream file;
	std::regex rgx;
	std::queue<std::vector<Token>> lineQ;
	Token Read();
	Token Peek(int i);
	void InitQ();
	void ReadLine();
	void AddToken(int line, int clm, std::smatch mth);
	std::string ToStringLiteral(std::string s);

public:
	Lexer(std::string fileName);
	~Lexer();

	std::vector<Token>  GetLine();
	std::vector<Token> PeekLine();
};