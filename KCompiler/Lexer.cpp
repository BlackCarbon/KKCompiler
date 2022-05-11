#include <bits/stdc++.h>
#include "Lexer.h"
#include "Exception.h"
#include "Token.h"

using namespace std;
//空格*((注释2)|(数字3)|(标识符4)|(运算符5)|(字符串字面量6)|(英文标点7))
const string Lexer::regexPat = 
R"([[:s:]]*((//.*)|([[:d:]]+)|([[:alpha:]][[:w:]]*)|(!=|==|<=|>=|&&|\|\|)|("[^"]*")|([[:punct:]]))?)";

Lexer::Lexer(std::string fileName):file(fileName)
{
	lineNumber = 0;
	hasMore = true;
	//file.open(fileName, std::ios::in);
	rgx = regex(regexPat);
	InitQ();
}
Lexer::~Lexer()
{
	file.close();
}

void Lexer::InitQ()
{
	Token t = Read();
	while (t != Token::TokenEOF)
	{
		vector<Token> temp;
		while (t.GetType() != TokenType::None)
		{
			temp.push_back(t);
			t = Read();
		}
		t = Read();
		if (temp.size() > 0)
			lineQ.push(temp);
	}
}
std::vector<Token> Lexer::GetLine()
{
	auto temp = lineQ.front();
	lineQ.pop();
	return temp;
}
std::vector<Token> Lexer::PeekLine()
{
	return lineQ.front();
}

Token Lexer::Read()
{
	if (q.empty())
	{
		ReadLine();
		if (q.empty())
			return Token::TokenEOF;
		else
		{
			auto temp = q.front();
			q.pop();
			return temp;
		}
	}
	auto temp = q.front();
	q.pop();
	return temp;
}
Token Lexer::Peek(int i)
{
	if (q.empty())
		return Token::TokenEOF;
	return q.front();
}

void Lexer::ReadLine()
{
	string line;
	try
	{
		lineNumber += 1;
		getline(file, line);
	}
	catch (Exception e)
	{
		throw new Exception(e);
	}
	if (file.eof())
	{
		hasMore = false;
		return;
	}
	int clm = 0;
	string str = line;
	smatch mth;
	while (str != "" && regex_search(str, mth, rgx))
	{
		clm += mth.str(0).length();
		AddToken(lineNumber, clm, mth);
		str = mth.suffix();
	}
	q.push(Token(TokenType::None, Token::TokenEOL, lineNumber, line.length() - 1));
}
void Lexer::AddToken(int line, int clm, std::smatch mth)
{
	string m = mth.str(1);
	if (m != "")
	{
		if (!mth[2].matched)
		{
			if (mth[3].matched)
			{
				q.push(Token(TokenType::Number, mth.str(3), lineNumber, clm));
			}
			else if (mth[4].matched)
			{
				if (Token::Keywords.count(mth.str(4)) > 0)
				{
					q.push(Token(TokenType::Keyword, mth.str(4), lineNumber, clm));
				}
				else
					q.push(Token(TokenType::Identifier, mth.str(4), lineNumber, clm));
			}
			else if(mth[5].matched)
			{
				q.push(Token(TokenType::Operator, mth.str(5), lineNumber, clm));
			}
			else if (mth[6].matched)
			{
				q.push(Token(TokenType::Literal, ToStringLiteral(m), lineNumber, clm));
			}
			else if (mth[7].matched)
			{
				if(mth.str(7) != ";")
					q.push(Token(TokenType::Operator, mth.str(7), lineNumber, clm));
				else
					q.push(Token(TokenType::None, mth.str(7), lineNumber, clm));
			}
			else
			{
				cout << "Cant match this string: " << m << " (line: " << line <<" column:" << clm << ")" << endl;
			}
		}
	}
}
string Lexer::ToStringLiteral(std::string s)
{
	string str = "";
	int len = s.length() - 1;
	for (int i = 1; i < len; i++)
	{
		char c = s[i];
		if (c == '\\' && i + 1 < len)
		{
			int c2 = s[i + 1];
			if (c2 == '"' || c2 == '\\')
				c = s[++i];
			else if (c2 == 'n')
			{
				++i;
				c = '\n';
			}
		}
		str += c;
	}
	return str;
}
