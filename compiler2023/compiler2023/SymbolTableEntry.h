#ifndef __SYMBOLTABLEENTRY__H
#define __SYMBOLTABLEENTRY__H SymbolTableEntry
#include <stdio.h>
#define TYPE_SIZE 7
#include <string.h>

typedef enum
{
    STE_NONE, //0
    STE_INT,
    STE_STRING,
    STE_FLOAT,
    STE_DOUBLE,
    STE_CHAR,
    STE_BOOLEAN
}J_type;
typedef enum
{
    STE_VAR, // A VARIABLE
    STE_CONST, //A CONSTANT
    STE_ROUTINE, //A ROUTINE
    STE_UNDEFINED
}ste_entry_type;

class SymbolTableEntry
{
public:

    char Name[64];
    J_type Type;  //it is an int
    ste_entry_type steType;
    int constVal;
    //J_type resutType;
    SymbolTableEntry*Next;
    SymbolTableEntry();
    ////{
    ////    Next = NULL;
    ////    Type = STE_NONE;
    ////    Name[0] =0; //empty String
    ////}
    SymbolTableEntry(char* name,ste_entry_type steType, J_type type);//var routine
    SymbolTableEntry(char* name,ste_entry_type steType, int constVal);//const
    //SymbolTableEntry(char* name, J_type resutType);
    //{
    //    Next= NULL;
    //    Type = type;
    //    strcpy(Name, name);
    //}
    char* toString();
    //{
    //    if ((Type < STE_NONE) ||Type> STE_CHAR)  Type = STE_NONE;
    //    sprintf(str,"(%s,%s)",Name, STE_TYPE_SITR[Type]);
    //    return str;
    //}
    void print(FILE* fp);
 /*   {
        fprintf(fp,"%s ", toString());
    }*/

   static  J_type getType(char* str);
 /*   {
        int i;
        for (i =0; i < TYPE_SIZE; i++){
            if(strcmp(STE_TYPE_SITR[i],str) == 0) return ((STE_TYPE)i);
        }
        return STE_NONE;

    }*/
};

#endif // STENTRY_H
