#ifndef __SYMBOLTABLE__H
#define __SYMBOLTABLE__H
#include "stlist.h"
#include <string>
#define DEFAULT_SIZE 19
#pragma warning(disable : 4996)
class SymbolTable
{
private:
    unsigned long Size;
    STList *Table;   // Dynamic Array of size = Size
    void init(int size);
    unsigned long ElfHash(const char *str);
    int fold_flag;
    int number_entries; // Number of entries in table
    int number_probes; // Number of probes into table
    int number_hits; // Number of probes that immediately found entry
    int max_search_dist; // Maximum entries searched
public:
    SymbolTable* nextST;
    SymbolTable();
    ~SymbolTable();
    SymbolTable(unsigned long size, int fold_case_flag);
    void Reset(unsigned long size);
    bool PutSymbol(char *name, STE_TYPE type);
    void GetSymbol(const char *name, FILE *fp);//finds and prints the Entry if it exist
    void PrintAll(FILE *fp);
    void ClearSymbolTable();
    void PrintSymbolStats(FILE* fp);
};

#endif // STABLE_H
