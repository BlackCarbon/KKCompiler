#pragma once
#include "Token.h"
template <class E>
class EnumTool
{
public:
	std::string GetString(E e);
	E GetEnum(std::string e);
};
