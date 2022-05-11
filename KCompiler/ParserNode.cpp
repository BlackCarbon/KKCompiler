#include "ParserNode.h"
ParserNode::ParserNode()
{
	type = ParserType::None;
	parentNode = nullptr;
}
ParserNode::ParserNode(ParserType t, Token tkn)
{
	type = t;
	token = tkn;
}