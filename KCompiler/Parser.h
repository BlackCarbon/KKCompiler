#pragma once
#include "ParserNode.h"
#include "Lexer.h"
class Parser
{
private:
	Lexer* lexer;
	bool PeekClass(std::vector<Token> & line);
	bool PeekFormula(std::vector<Token>& line);
	bool PeekFunctionCall(std::vector<Token>& line);
	bool PeekFunctionDefinition(std::vector<Token>& line);
	bool PeekVariableDeclaration(std::vector<Token>& line);
	bool PeekVariableDefinition();

	ParserNode* GetClass();
	ParserNode* GetFormula();
	ParserNode* GetFunctionCall();
	ParserNode* GetFunctionDefinition();
	ParserNode* GetVariableDeclaration();
	ParserNode* GetVariableDefinition();

public:
	Parser(Lexer* lex);
	ParserNode* GenerateAST();
};