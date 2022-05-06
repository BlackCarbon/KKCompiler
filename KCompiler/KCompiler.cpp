#include "Lexer.h"

int main(int argc, char** arg)
{
    std::cout << "Hello World!\n";
	Lexer lex("G:/KKCompiler/KCompiler/input.txt");
	Token t = lex.Read();
	while (t != Token::TokenEOF)
	{
		std::cout << t.GetText() << " Type:" << t.GetTypeString() <<
			" Line:" << t.GetLineNumber() << " Column:" << t.GetColumnNumber() << std::endl;
		t = lex.Read();
	}
	std::cout << std::endl;

	system("pause");

//     if (argc > 1)
//     {
//         std::string str(arg[1]);
//         Lexer lex(str);
//         Token t = lex.Read();
//         while (t != Token::TokenEOF)
//         {
//             std::cout << t.GetText() << " ";
//         }
//         std::cout << std::endl;
//     }
//     else
//     {
//         std::cerr << "param count error." << std::endl;
//         return 0;
//     }
}