#pragma once
#include <bits/stdc++.h>
#include "Token.h"
enum class OperatorDefine
{
	/// <summary>
	/// �������κζ���
	/// </summary>
	None = 0,
	/// <summary>
	/// ����������
	/// </summary>
	Number = 1,
	/// <summary>
	/// ��������ʽ
	/// </summary>
	Formula = 1 << 1,
	/// <summary>
	/// �����������
	/// </summary>
	Operator = 1 << 2,
	/// <summary>
	/// ��ʶ��
	/// </summary>
	Identifier = 1 << 3,
	/// <summary>
	/// �ַ���������
	/// </summary>
	Literal = 1 << 4,
	/// <summary>
	/// ��ʲô���У����ǲ���û��
	/// </summary>
	Every = (1 << 5) - 1,
	/// <summary>
	/// �ɿ�
	/// </summary>
	Empty = 1 << 5,
	/// <summary>
	/// ��ʲô���У������Կ���
	/// </summary>
	All = (1 << 6) - 1,
};

enum class OperatorCombination
{
	/// <summary>
	/// ����
	/// </summary>
	Left,
	/// <summary>
	/// �ҽ��
	/// </summary>
	Right,
};

class OperatorOrder
{
public:
	int leftOrder;
	int rightOrder;
	int priority;
	OperatorCombination combination;

	OperatorOrder();
	OperatorOrder(int left, int right, int pry = 0, OperatorCombination cmb = OperatorCombination::Left);
	OperatorOrder(OperatorDefine left, OperatorDefine right, int pry = 0, OperatorCombination cmb = OperatorCombination::Left);
};
class OperatorRule
{
public:
	static const std::unordered_map<std::string, OperatorOrder> operatorRule;
	static OperatorDefine TokenChangeToDefine(TokenType type);
	
	
};

