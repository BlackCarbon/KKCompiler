#include "Lexer.h"
using namespace std;

queue<vector<Token*>> lexer;

void MakeLexer(std::string file)
{
	Lexer lex("G:/KCompiler/input.txt");
	Token t = lex.Read();
	while (t != Token::TokenEOF)
	{
		vector<Token*> temp;
		while (t.GetType() != TokenType::None)
		{
			temp.push_back(new Token(t));
			std::cout << t.GetText() << "  Type:" << t.GetTypeString() <<
				" Line:" << t.GetLineNumber() << " Column:" << t.GetColumnNumber() << std::endl;
			t = lex.Read();
		}
		t = lex.Read();
		if(temp.size() > 0)
		lexer.push(temp);
	}
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