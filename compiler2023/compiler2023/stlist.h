#ifndef __STLIST__H
#define __STLIST__H
#include "SymbolTableEntry.h"

class STList
{
private:
    int Counter;  // counts the Node n the List
    SymbolTableEntry *Head; // Should be Initialized to Null in the Constructor
public:

    STList();
    SymbolTableEntry *FindEntry(const char *name); // return NULL if Not found
    SymbolTableEntry* AddEntry(char* name, J_type type, ste_entry_type steType, int constVal);//Adds an entry if the Node Does Not exist
    void PrintAll(FILE *fp);
    int Count();
    void Clear();
    ~STList();
};

#endif // STLIST_H
