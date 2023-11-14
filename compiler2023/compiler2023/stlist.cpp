#include "stlist.h"
#include <iostream>
using namespace std;
/**
 * @brief STList::STList
 * default constructor, initialize head and Counter
 */
STList::STList()
{
    Counter = 0;
    Head = NULL;
}
/**
 * @brief STList::FindEntry: search (linear search) the list and compare the name to the ones in the list
 * @param name : Given name to find
 * @return : If name is found found return NULL otherwise reaturn a pointer to the Node
 */
SymbolTableEntry* STList::FindEntry(const char *name)
{
    SymbolTableEntry *ste = Head;
    while (ste != NULL)
    {
        if( strcmp(name,ste->Name) == 0) return ste;
        ste = ste->Next;
    }
    return NULL;

}
/**
 * @brief STList::AddEntry : Call FindEntry, if name is alread in table return false, otherwise add it to the list
 *                           Add it as the first Entry, like a stack which is fastest. Update Counter and Head
 * @param name : Name of Entry (variable)
 * @param type : Type of variable
 * @return : True if the node is added and False if the Entry Already exists in the Table
 */
SymbolTableEntry* STList::AddEntry(char *name, J_type type, ste_entry_type steType, int constVal)
{
  SymbolTableEntry *ste = FindEntry(name);
  bool added = false;
  if(ste)
  {
      printf("Entry Already exist, nothing Added\n");
      return NULL;
  }
  else
  {
      if (steType ==STE_VAR) {
          ste = new SymbolTableEntry(name, steType, type);
      }
      else if (steType == STE_CONST) {
          //cout << "++J_type: " << type << " ste_type: " << steType << " const val: " << constVal << endl;
          ste = new SymbolTableEntry(name, steType, constVal);
      }
      else if (steType == STE_ROUTINE) {
          ste = new SymbolTableEntry(name, steType, type);
      }
      else {
          ste = new SymbolTableEntry(name, STE_UNDEFINED, STE_NONE);
      }
      //ste = new SymbolTableEntry(name, type) ;
      ste->Next = Head;
      Head = ste;
      added = true;

      Counter++;
      return ste;
  }
  
}
/**
 * @brief STList::PrintAll : Prints All nodes in the list, use the print in the SymbolTableEntry.
 * @param fp : File Pointer where to write
 */
void STList::PrintAll(FILE *fp)
{
    SymbolTableEntry *ste = Head;
    while (ste != NULL)
    {
        ste->print(fp);
        ste = ste->Next;
    }
    fprintf(fp,"\n");

}


/**
 * @brief STList::Count returns Counter which is Number of Elements
 * @return
 */
int STList::Count()
{
    return Counter;
}
/**
 * @brief STList::Clear : deletes all Elements in the List and sets the counter to zero
 */
void STList::Clear()
{
    SymbolTableEntry *ste;
    while (Head != NULL)
    {
        ste = Head;
        Head = Head->Next;
        delete ste;
    }
    Counter =0;
}

STList::~STList()
{
    Clear();
}

