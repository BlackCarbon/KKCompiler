#include <bits/stdc++.h>
#include "Exception.h"

Exception::Exception(std::string str) : std::exception(str.c_str())
{
}