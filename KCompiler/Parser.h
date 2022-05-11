#pragma once
#include "ParserNode.h"
#include "Lexer.h"
class Parser
{
private:
	Lexer* lexer;

	ParserNode* CheckClass();
	ParserNode* CheckFormula();
	ParserNode* CheckFunctionCall();
	ParserNode* CheckFunctionDeclaration();
	ParserNode* CheckFunctionDefinition();
	ParserNode* CheckVariableDeclaration();
	ParserNode* CheckVariableDefinition();

public:
	Parser(Lexer* lex);
	ParserNode* GenerateAST();
};