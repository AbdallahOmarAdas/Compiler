#include "SymbolTable.h"
class symbolTableList
{
public:
	int tableCount;
	SymbolTable *Head;
	symbolTableList() {
		tableCount = 0;
		Head = NULL;
	}
	//addTable() {
	//	SymbolTable* st;
	//	st = new SymbolTable();
	//	st->nextST = Head;
	//	Head = ste;
	//}
};