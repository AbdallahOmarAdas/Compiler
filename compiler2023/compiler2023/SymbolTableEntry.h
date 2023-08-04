#ifndef __SYMBOLTABLEENTRY__H
#define __SYMBOLTABLEENTRY__H SymbolTableEntry
#include <stdio.h>
#define TYPE_SIZE 6
#include <string.h>

typedef enum
{
    STE_NONE, //0
    STE_INT,
    STE_STRING,
    STE_FLOAT,
    STE_DOUBLE,
    STE_CHAR,
}STE_TYPE;
class SymbolTableEntry
{
public:

    char Name[64];
    STE_TYPE Type;  //it is an int
    SymbolTableEntry*Next;
    SymbolTableEntry();
    ////{
    ////    Next = NULL;
    ////    Type = STE_NONE;
    ////    Name[0] =0; //empty String
    ////}
    SymbolTableEntry(char* name, STE_TYPE type);
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

   static  STE_TYPE getType(char* str);
 /*   {
        int i;
        for (i =0; i < TYPE_SIZE; i++){
            if(strcmp(STE_TYPE_SITR[i],str) == 0) return ((STE_TYPE)i);
        }
        return STE_NONE;

    }*/
};

#endif // STENTRY_H
