#pragma once
#include "Token.h"

enum class ParserType
{
	None,
	/// <summary>
	/// 终结符
	/// </summary>
	Terminator,
	/// <summary>
	/// 关键字
	/// </summary>
	Keyword,
	/// <summary>
	/// 标识符
	/// </summary>
	Identifier,
	/// <summary>
	/// 字符串字面量
	/// </summary>
	Literal,
	/// <summary>
	/// 数字
	/// </summary>
	Number,
	/// <summary>
	/// 标点符号
	/// </summary>
	Punction,
	/// <summary>
	/// 运算符
	/// </summary>
	Operator,

	/// <summary>
	/// 类定义
	/// </summary>
	ClassDefinition,
	/// <summary>
	/// 函数调用
	/// </summary>
	FunctionCall,
	/// <summary>
	/// 函数定义
	/// </summary>
	FunctionDefinition,
	/// <summary>
	/// 变量定义
	/// </summary>
	VariableDefinition,
	/// <summary>
	/// 变量声明
	/// </summary>
	VariableDeclaration,
	/// <summary>
	/// 算式
	/// </summary>
	Formula,
};

class ParserNode
{
public:
	Token token;
	ParserType type;
	ParserNode* parentNode;
	std::vector<ParserNode*> childrenNode;
	ParserNode();
	ParserNode(ParserType t, Token tkn);
};

