#include "SymbolTable.h"


void SymbolTable::init(int size)
{
   nextST = NULL;
   Size = size;
   Table = new STList[size];
   number_entries = 0;
   number_probes = 0;
   number_hits = 0;
   max_search_dist = 0;
}
/**
 * @brief SymbolTable::SymbolTable : Default constructor, call init with DEFAULT_SIZE
 */
SymbolTable::SymbolTable()
{
    fold_flag = 0;
    init(DEFAULT_SIZE);
}
/**
 * @brief SymbolTable::SymbolTable  constructor with Number of slots = size, call init with size
 * @param size
 */

SymbolTable::SymbolTable(unsigned long size, int fold_case_flag)
{
    fold_flag = fold_case_flag;
    init(size);
}
/**
 * @brief SymbolTable::Reset   Recreate the Table by calling clear then call init
 * @param size
 */
void SymbolTable::Reset(unsigned long size)
{
    ClearSymbolTable();
    init(size);
}
/**
 * @brief SymbolTable::ElfHash : Hash Function
 * @param str  : Key which is the Variable Name to be added to the Symbol Table
 * @return
 */
unsigned long SymbolTable::ElfHash(const char *str )
{
    std::string ss = str;
    int length = 1;// ss.length();
    unsigned long   h = 0, high; // h=0, g
    unsigned char *s = (unsigned char *) str;
    while ( *s )
    {
        h = ( h << 4 ) + *s++;  //1/4 of bits
        if ( high = h & 0xF0000000 )
            h ^= high >> 24; // h = h ^ (g >>24)
        h &= ~high; // in book this is h = h^g
    }
    return h%Size;

    //unsigned long p = 31, m = 1e9 + 7;
    //unsigned long hash_value = 0;
    //unsigned long p_pow = 1;
    //for (int i = 0; i < length; i++) {
    //    hash_value = (hash_value + (s[i] - 'a' + 1) * p_pow) % m;
    //    p_pow = (p_pow * p) % m;
    //}
    //printf("%lu\n", hash_value);
    //return hash_value%Size;
}
/**
 * @brief SymbolTable::AddEntry : Adds the Entry, call Hash to find index, then call Add to the List in Table[index] to add it
 * @param name : Name of Entry to be added
 * @param type : type of Entry. See the Main function for example how to find it
 * @return  true if added and false otherwise, the List Table[index] Already returns this for you
 */
bool SymbolTable::PutSymbol(char *name, STE_TYPE type)
{   
    if (fold_flag == 1) {
        for (int i = 0; name[i] != '\0';i++) {
            if ((int(name[i]) >= 65) && (int(name[i]) <= 90)) {
                name[i] = int(name[i]) + 32;
            }
        }
    }
    unsigned long index = ElfHash(name);
    bool Added = Table[index].AddEntry(name, type);
    return Added;
}
/**
 * @brief SymbolTable::FindAndPrintEntry Finds and prints the Entry if it is found
 *                if Not found print the Message Not found, see the example result
 * @param name  : name to search for
 * @param fp  : File pointer to print : See Example in reults
 */
void  SymbolTable::GetSymbol(const char *name, FILE *fp)// may be find and print entry
{
    unsigned long index = ElfHash(name);
    SymbolTableEntry *ste = Table[index].FindEntry(name);
    if(ste) fprintf(fp,"%s: Found = %s\n", name, ste->toString()); // to be fixed , se
    else fprintf(fp,"%s: not found \n",name);

}
/**
 * @brief SymbolTable::PrintAll : Prints all Elements. Print the Count of each list and the Entries.
 *                            See the Sample Result (fout.txt) to format your output
 *                            Loop through the Slots (Lists) and Call Table[i].printAll
 * @param fp
 */

void SymbolTable::PrintAll(FILE *fp)
{
    number_entries = 0;
    number_probes = 0;
    number_hits = 0;
    max_search_dist = 0;

    unsigned long i;
    for (i =0; i < Size; i++)
    {
        fprintf(fp,"T[%d]: %d ste:\t", i, Table[i].Count());
        number_entries += Table[i].Count();
        if (Table[i].Count() == 1) {
            number_hits++;
        }
        if (max_search_dist < Table[i].Count()) {
            max_search_dist = Table[i].Count();
        }
        Table[i].PrintAll(fp);
    }
    number_probes = number_entries - number_hits;
}
/**
 * @brief SymbolTable::Clear : Delete All Elements, use a loop and call the Table[i].clear. Then Delete the Array Table
 */
void SymbolTable::ClearSymbolTable()
{
    unsigned long i;
    for (i =0; i < Size; i++)
    {
        Table[i].Clear();
    }
    

}
void SymbolTable::PrintSymbolStats(FILE* fp)
{   
    printf("Number of entries in table: %d\n", number_entries);
    fprintf(fp, "Number of entries in table: %d\n", number_entries);
    printf("Number of probes into table: %d\n", number_probes);
    fprintf(fp, "Number of probes into table: %d\n", number_probes);
    printf("Number of probes that immediately found entry: %d\n", number_hits);
    fprintf(fp, "Number of probes that immediately found entry: %d\n", number_hits);
    printf("Maximum entries searched: %d\n", max_search_dist);
    fprintf(fp, "Maximum entries searched: %d\n", max_search_dist);
}
SymbolTable::~SymbolTable()
{
    ClearSymbolTable();
    delete[]Table;
}


