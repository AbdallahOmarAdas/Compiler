#include <stdlib.h>
#include "SymbolTable.h"
#include "SymbolTableEntry.h"
#include <ctime>
#include <iostream>
#include <stdio.h>
#include "scanner.h"
#include "symbolTableList.cpp"
using namespace std;
/**
 * @brief getIdetifier: reads the next Identifier, and its type from the file
 * @param fp
 * @param str    : Identifier is stored here
 * @param type   : stores the type read
 * @return
 */
int  getIdetifier(FILE* fp, char* str, STE_TYPE& type)
{
    char s1[64] = "\0", s2[64] = "\0", s3[64] = "\0";
    //int n = fscanf(fp,"%s%s%s\n", s1,s2,s3);
    int n = fscanf(fp, "%s", s1);
    if (strcmp(s1, "begin") == 0) {
        return 1;
    }
    else if (strcmp(s1, "end") == 0) {
        return 2;
    }
    else if (strcmp(s1, "\0") == 0) {
        return 4;
    }
    else {
        n = fscanf(fp, "%s%s", s2, s3);
        strcpy(str, s2);
        type = SymbolTableEntry::getType(s1);  // notice how we call a static function or data member
        return 3;
    }
    ///printf("%s  %s  %s  \n",s1,s2,s3);
    //printf ("(n= %d,%s,%s,%s)\n", n, s1, s2, s3);

    //printf ("-(%d,%s)\n",(int)type, str); //to make sure  it is reading correctly

}
/**
 * @brief getRandChar  Returns a random char
 * @param isFirst: is First= true character returned is a random char in 'A' --- 'Z'
 *                 else returns a 'A' ---'Z' or '0' -- '9'
 * @return
 */
char getRandChar(bool IsFirst = false)
{
    int index = 0;
    char ch;
    if (IsFirst) index = rand() % 26;
    else index = rand() % (26 + 10); // 10 for 0--9
    if (index < 26) ch = 'A' + index;
    else ch = '0' + (index - 26);
    return ch;
}
/**
 * @brief getRandIdentifier: generates a random 8-char variable name
 * @param str: Stores the generated string
 * @param type: Type of variable generated, random from the types defined in STentry.h
 */
void getRandIdentifier(char* str, STE_TYPE& type)
{
    int i;
    str[0] = getRandChar(true);
    for (i = 1; i < 8; i++)
    {
        str[i] = getRandChar();
    }
    str[i] = 0;//NULL terminate
    type = (STE_TYPE)(rand() % TYPE_SIZE);
}

int main(int argc, char* argv[])
{
    FILE* fp;
    //SymbolTable  ST;
    SymbolTable* STHead = new SymbolTable();
    symbolTableList stList;
    //stList->Head = STHead;
    STE_TYPE type;
    char str[64];
    fp = fopen("t.txt", "r");
    if (!fp) return 0;
    FILE* fout = fopen("out.txt", "w");   //set fout = stdout for screen output

    fprintf(fout, "\n**(Test 1)**: Reading from the file t.txt and creating a symnol table with size = 19(default)\n\n");
    int n;
    bool Added;
    SymbolTable* stTemp = new SymbolTable();
    while (!feof(fp))
    {
        n = getIdetifier(fp, str, type);
        if (n == 1) {
            stTemp = new SymbolTable();
            stTemp->nextST = STHead;
            STHead = stTemp;
        }
        else if (n == 2) {
            fprintf(fout, "\n==============\n");
            STHead->PrintAll(fout);
            fprintf(fout, "\n==============\n");
            stTemp = STHead;
            STHead = STHead->nextST;
            delete stTemp;
            cout << "end" << endl;

        }
        else if (n == 4) {
            cout << "new line" << endl;
        }
        else if (n == 3)
        {
            Added = STHead->PutSymbol(str, type);
            if (!Added)fprintf(fout, "Entry %s Already Exists\n", str);
        }
    }
    fclose(fp);


    fprintf(fout, "\n==============\n");
    STHead->PrintAll(fout);
    STHead->PrintSymbolStats(fout);
    fprintf(fout, "\n==============\n");

    fprintf(fout, "\n\n**(Test 2)**: Searching for some Variables in the Symobol Table Created\n\n");
    STHead->GetSymbol("m", fout);
    STHead->GetSymbol("k", fout);
    STHead->GetSymbol("x", fout);
    STHead->GetSymbol("dog", fout);

    STHead->ClearSymbolTable();
    fprintf(fout, "\nClear Global Symbol Table\n==============\n");
    STHead->PrintAll(fout);
    fprintf(fout, "\n==============\n");

    fprintf(fout, "\n\n**(Test 2)**: Searching for some Variables in the Symobol Table Created\n\n");
    STHead->GetSymbol("m", fout);
    STHead->GetSymbol("k", fout);
    STHead->GetSymbol("x", fout);
    STHead->GetSymbol("dog", fout);

    //fprintf(fout, "\n\n**(Test 3)**: Creatig 8 Symbol Tables with different Slot Size and Different Sizes\n");
    //fprintf(fout, "            : Random Variable Names are generated\n");
    //srand (time(0));

    //int k, i;
    //int Sizes[10]         = {29, 29, 17, 23, 37, 31,101, 101, 101,101};
    //int ElementsCount[10] = {100, 100, 100, 100,100, 150, 300, 100, 200, 50} ;

    //STable ST2(Sizes[8]);//Initil table with 29 elements
    //k = 0;
    //for(k = 0; k < 10; k++)
    //{
    //    if(k !=0 ) ST2.Reset(Sizes[k]);
    //    for(i=0; i < ElementsCount[k]; i++) // create a 100 element table
    //    {
    //        getRandIdentifier (str, type);
    //        Added = ST2.AddEntry(str,type);
    //        if(!Added)fprintf(fout,"Entry %s Already Exists\n",str );

    //    }
    //    fprintf(fout,"\n===== Table (%d) =======\n", k);
    //    ST2.PrintAll(fout);

    //}
    fprintf(fout, "\n------------------done-------------------\n");
    fclose(fout);
    delete STHead;
    return 0;
}

