#pragma once
#include <bits/stdc++.h>
enum class TokenType
{
	None,
	/// <summary>
	/// ����
	/// </summary>
	Number,
	/// <summary>
	/// ��ʶ��
	/// </summary>
	Identifier,
	/// <summary>
	/// �����
	/// </summary>
	Operator,
	/// <summary>
	/// �ַ���������
	/// </summary>
	Literal,
	/// <summary>
	/// �ؼ���
	/// </summary>
	Keyword,
};
class Token
{
private:
	TokenType type;
	int lineNumber;
	int columnNumber;
	std::string value;
protected:
public:
	static const Token TokenEOF;
	static const std::string TokenEOL;
	static const std::unordered_set<std::string> Keywords;

	Token(TokenType t, std::string val, int line, int column);
	~Token();
	int GetLineNumber() const;
	int GetColumnNumber() const;
	int GetNumber() const;
	std::string GetText() const;
	TokenType GetType() const;
	std::string GetTypeString() const;

	bool operator==(const Token &t)
	{
		return (
			this->lineNumber == t.lineNumber &&
			this->columnNumber == t.columnNumber &&
			value == value);
	}
	bool operator!=(const Token& t)
	{
		return (
			this->lineNumber != t.lineNumber ||
			this->columnNumber != t.columnNumber ||
			value != value);
	}
};
