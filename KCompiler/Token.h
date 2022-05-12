#pragma once
#include <bits/stdc++.h>
enum class TokenType
{
	None,
	/// <summary>
	/// 数字
	/// </summary>
	Number,
	/// <summary>
	/// 标识符
	/// </summary>
	Identifier,
	/// <summary>
	/// 运算符
	/// </summary>
	Operator,
	/// <summary>
	/// 字符串字面量
	/// </summary>
	Literal,
	/// <summary>
	/// 关键字
	/// </summary>
	Keyword,
};
enum class KeyWordType
{
	Main,
	Func,
	Condition,
	Other,
	Class,
	Type,
	Var,
	Void,
	Nil,
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
	static const std::unordered_map<std::string, KeyWordType> Keywords;
	Token();
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
