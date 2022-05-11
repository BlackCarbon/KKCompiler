#include "Lexer.h"
using namespace std;

void MakeLexer(std::string file)
{
	Lexer lex("G:/KCompiler/input.txt");

	return;
}

void Main(std::string file)
{
	MakeLexer(file);

}


int main(int argc, char** arg)
{
	if (argc > 1)
	{
		Main(arg[1]);
	}
	else
	{
		Main("G:/KKCompiler/KCompiler/input.txt");
	}
	system("pause");
	return 0;
}