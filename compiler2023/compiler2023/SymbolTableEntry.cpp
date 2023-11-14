#include "SymbolTableEntry.h"

#pragma warning(disable : 4996)


const char* STE_TYPE_SITR[] = { "None","integer","string","float","double","char","boolean"};// It is not a good idea to put this here
static char  str[128];
SymbolTableEntry::SymbolTableEntry() {
    Next = NULL;
    Type = STE_NONE;
    steType = STE_UNDEFINED;
    constVal = 0;
    Name[0] = 0; //empty String
}
SymbolTableEntry::SymbolTableEntry(char* name, ste_entry_type steT, J_type type)//var routine
{
    Next = NULL;
    Type = type;
    steType = steT;
    constVal = 0;
    strcpy(Name, name);
}
SymbolTableEntry::SymbolTableEntry(char* name, ste_entry_type steT, int constValue)//const
{
    Next = NULL;
    Type = STE_NONE;
    steType = STE_CONST;
    constVal = constValue;
    strcpy(Name, name);
}

char* SymbolTableEntry::toString()
{
    if ((Type < STE_NONE) || Type > STE_BOOLEAN)  Type = STE_NONE;
    sprintf(str, "(%s,%s)", Name, STE_TYPE_SITR[Type]);
    return str;
}
void SymbolTableEntry::print(FILE* fp)
{
    fprintf(fp, "%s ", toString());
}

  J_type SymbolTableEntry::getType(char* str)
{
    int i;
    for (i = 0; i < TYPE_SIZE; i++) {
        if (strcmp(STE_TYPE_SITR[i], str) == 0) return ((J_type)i);
    }
    return STE_NONE;

}