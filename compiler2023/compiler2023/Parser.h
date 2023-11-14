#pragma once
#ifndef __PARSER__H
#define __PARSER__H
#include "SymbolTable.h"
#include "ast.h"
#include "scanner.h"
//#include "types.cpp"
#include <iostream>
using namespace std;
class Parser {
private:
	
	
public:
	FileDescriptor* fd;
	Parser(FileDescriptor* fd );
	AST* parse();
	SymbolTable* tabl;
	void enterScope(SymbolTable* stTemp);
	void exitScope(SymbolTable* stTemp);
	SymbolTableEntry* getSymbolFromTable(const char* str);
	~Parser();
};

void match(LEXEME_TYPE lx);
#endif

