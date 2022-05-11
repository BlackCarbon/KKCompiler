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
	FunctionDeclaration,
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
	ParserType type;
	ParserNode* parentNode;
	std::vector<ParserNode*> childrenNode;
	ParserNode();
};

