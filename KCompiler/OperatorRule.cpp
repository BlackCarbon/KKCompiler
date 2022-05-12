#include "OperatorRule.h"
OperatorOrder::OperatorOrder()
{
	leftOrder = 0;
	rightOrder = 0;
	combination = OperatorCombination::Left;
}
OperatorOrder::OperatorOrder(int left, int right, int pry, OperatorCombination cmb)
{
	leftOrder = left;
	rightOrder = right;
	priority = pry;
	combination = cmb;
}
OperatorOrder::OperatorOrder(OperatorDefine left, OperatorDefine right, int pry, OperatorCombination cmb)
{
	leftOrder = (int)left;
	rightOrder = (int)right;
	priority = pry;
	combination = cmb;
}
OperatorDefine OperatorRule::TokenChangeToDefine(TokenType type)
{
	switch (type)
	{
	case TokenType::Number:
		return OperatorDefine::Number;
	case TokenType::Identifier:
		return OperatorDefine::Identifier;
	case TokenType::Operator:
		return OperatorDefine::Operator;
	case TokenType::Literal:
		return OperatorDefine::Literal;
	default:
		break;
	}
	return OperatorDefine::None;
}
const std::unordered_map<std::string, OperatorOrder> OperatorRule::operatorRule{
	{"=", OperatorOrder(OperatorDefine::Identifier, OperatorDefine::Every)},

	{"+", OperatorOrder(OperatorDefine::Every, OperatorDefine::Every, 2)},
	{"-", OperatorOrder(OperatorDefine::All, OperatorDefine::Every, 2)},
	{"*", OperatorOrder(OperatorDefine::Every, OperatorDefine::Every, 4)},
	{"/", OperatorOrder(OperatorDefine::Every, OperatorDefine::Every, 4)},

	{"+=", OperatorOrder(OperatorDefine::Identifier, OperatorDefine::Every)},
	{"-=", OperatorOrder((int)(OperatorDefine::Identifier), (int)(OperatorDefine::Number) | (int)(OperatorDefine::Formula))},
	{"*=", OperatorOrder((int)(OperatorDefine::Identifier), (int)(OperatorDefine::Number) | (int)(OperatorDefine::Formula))},
	{"/=", OperatorOrder((int)(OperatorDefine::Identifier), (int)(OperatorDefine::Number) | (int)(OperatorDefine::Formula))},

	{"++", OperatorOrder(((int)(OperatorDefine::Number) | (int)(OperatorDefine::Formula) | (int)(OperatorDefine::Empty)),
	((int)(OperatorDefine::Number) | (int)(OperatorDefine::Formula) | (int)(OperatorDefine::Empty)), 3)},
	{"--", OperatorOrder(((int)(OperatorDefine::Number) | (int)(OperatorDefine::Formula) | (int)(OperatorDefine::Empty)),
	((int)(OperatorDefine::Number) | (int)(OperatorDefine::Formula) | (int)(OperatorDefine::Empty)), 3)},
};
