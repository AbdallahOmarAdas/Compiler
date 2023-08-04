#include "SymbolTableEntry.h"

#pragma warning(disable : 4996)


const char* STE_TYPE_SITR[] = { "None","integer","char*","float","double","char" };// It is not a good idea to put this here
static char  str[128];
SymbolTableEntry::SymbolTableEntry() {
    Next = NULL;
    Type = STE_NONE;
    Name[0] = 0; //empty String
}
SymbolTableEntry::SymbolTableEntry(char* name, STE_TYPE type)
{
    Next = NULL;
    Type = type;
    strcpy(Name, name);
}
char* SymbolTableEntry::toString()
{
    if ((Type < STE_NONE) || Type > STE_CHAR)  Type = STE_NONE;
    sprintf(str, "(%s,%s)", Name, STE_TYPE_SITR[Type]);
    return str;
}
void SymbolTableEntry::print(FILE* fp)
{
    fprintf(fp, "%s ", toString());
}

  STE_TYPE SymbolTableEntry::getType(char* str)
{
    int i;
    for (i = 0; i < TYPE_SIZE; i++) {
        if (strcmp(STE_TYPE_SITR[i], str) == 0) return ((STE_TYPE)i);
    }
    return STE_NONE;

}