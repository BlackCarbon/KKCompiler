#pragma once
#include "ParserNode.h"
#include "Lexer.h"
class Parser
{
private:
	Lexer* lexer;
	bool PeekClass(std::vector<Token> & line);
	bool PeekFormula();
	bool PeekFunctionCall(std::vector<Token>& line);
	bool PeekFunctionDeclaration(std::vector<Token>& line);
	bool PeekFunctionDefinition();
	bool PeekVariableDeclaration();
	bool PeekVariableDefinition();

	ParserNode* GetClass();
	ParserNode* GetFormula();
	ParserNode* GetFunctionCall();
	ParserNode* GetFunctionDeclaration();
	ParserNode* GetFunctionDefinition();
	ParserNode* GetVariableDeclaration();
	ParserNode* GetVariableDefinition();

public:
	Parser(Lexer* lex);
	ParserNode* GenerateAST();
};