#pragma once
#include "Token.h"

enum class ParserType
{
	None,
	/// <summary>
	/// �ս��
	/// </summary>
	Terminator,
	/// <summary>
	/// �ؼ���
	/// </summary>
	Keyword,
	/// <summary>
	/// ��ʶ��
	/// </summary>
	Identifier,
	/// <summary>
	/// �ַ���������
	/// </summary>
	Literal,
	/// <summary>
	/// ����
	/// </summary>
	Number,
	/// <summary>
	/// ������
	/// </summary>
	Punction,
	/// <summary>
	/// �����
	/// </summary>
	Operator,

	/// <summary>
	/// �ඨ��
	/// </summary>
	ClassDefinition,
	/// <summary>
	/// ��������
	/// </summary>
	FunctionCall,
	/// <summary>
	/// ��������
	/// </summary>
	FunctionDefinition,
	/// <summary>
	/// ��������
	/// </summary>
	VariableDefinition,
	/// <summary>
	/// ��������
	/// </summary>
	VariableDeclaration,
	/// <summary>
	/// ��ʽ
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

