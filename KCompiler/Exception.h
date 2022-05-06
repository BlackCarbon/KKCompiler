#pragma once
#include <bits/stdc++.h>
class Exception : public std::exception
{
public:
	Exception(std::string str);
	//Exception(std::string str, AbTree)
};
