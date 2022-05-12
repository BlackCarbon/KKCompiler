#pragma once
#include <bits/stdc++.h>
#include "Token.h"
enum class OperatorDefine
{
	/// <summary>
	/// 不可有任何东西
	/// </summary>
	None = 0,
	/// <summary>
	/// 可以有数字
	/// </summary>
	Number = 1,
	/// <summary>
	/// 可以有算式
	/// </summary>
	Formula = 1 << 1,
	/// <summary>
	/// 可以有运算符
	/// </summary>
	Operator = 1 << 2,
	/// <summary>
	/// 标识符
	/// </summary>
	Identifier = 1 << 3,
	/// <summary>
	/// 字符串字面量
	/// </summary>
	Literal = 1 << 4,
	/// <summary>
	/// 有什么都行，但是不能没有
	/// </summary>
	Every = (1 << 5) - 1,
	/// <summary>
	/// 可空
	/// </summary>
	Empty = 1 << 5,
	/// <summary>
	/// 有什么都行，还可以空着
	/// </summary>
	All = (1 << 6) - 1,
};

enum class OperatorCombination
{
	/// <summary>
	/// 左结合
	/// </summary>
	Left,
	/// <summary>
	/// 右结合
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

