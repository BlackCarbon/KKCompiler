#include "Parser.h"
using namespace std;

void LexicalAnalysis(std::string file)
{
	Lexer lex("G:/KCompiler/input.txt");
	Parser parser(&lex);
	//parser.GenerateAST();
	return;
}

void Main(std::string file)
{
	LexicalAnalysis(file);

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