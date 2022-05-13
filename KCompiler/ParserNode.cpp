#include "ParserNode.h"
ParserNode::ParserNode()
{
	type = ParserType::None;
}
ParserNode::ParserNode(ParserType t, Token tkn)
{
	type = t;
	token = tkn;
}
ParserNode::~ParserNode()
{
	delete parentNode;
	for (size_t i = 0; i < childrenNode.size(); i++)
	{
		delete childrenNode[i];
	}
}


OperatorNode::OperatorNode() { }
OperatorNode::OperatorNode(std::string val)
{
	value = val;
	leftNode = nullptr;
	rightNode = nullptr;
	parentNode = nullptr;
}
OperatorNode::~OperatorNode()
{
// 	if (leftNode != nullptr)
// 		delete leftNode;
// 	if (rightNode != nullptr)
// 		delete rightNode;
// 	if (parentNode != nullptr)
// 		delete parentNode;
}
