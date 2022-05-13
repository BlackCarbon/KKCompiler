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
	bool PeekVariableFormula(std::vector<Token>& line);
	bool PeekVariableDefinition(std::vector<Token>& line);

	ParserNode* GetClass();
	ParserNode* GetFormula();
	ParserNode* GetFunctionCall();
	ParserNode* GetFunctionDefinition();
	ParserNode* GetVariableFormula();
	ParserNode* GetVariableDefinition();

	OperatorNode* BuildFormulaTree(std::stack<Token>& stk);
public:
	Parser(Lexer* lex);
	ParserNode* GenerateAST();
};