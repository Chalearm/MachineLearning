#ifndef SIMSTRINGLIST_H_
#define SIMSTRINGLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include "simString.h"
#include "simMatChar.h"

struct simStrNode
{
    simString          data;
    struct simStrNode  *next;
};
struct simStrList
{
    int                numOfNode;
    struct simStrNode *root;
    struct simStrNode *last;
};
typedef struct simStrNode simStrNode;
typedef struct simStrList simStrList;
int initialSimStrList(simStrList *list);
void destructorSimStrList(simStrList *list);
int addNodeSimStrListFromVChar(simStrList *list,vector_char *vch);
int addNodeSimStrList(simStrList *list,simString *str);
int addNodeSimStrListFromCStr(simStrList *list,const char* str);
int insertNodeSimStrList(simStrList *list,int index,simString *str);
simString* getnthNodeSimStrList(simStrList *list,int num);
void printSimStrList(simStrList *list);
int getNumNodeSimStrList(simStrList *list);
int deleteNodeSimStrListWithIndex(simStrList *list,int index);
int copySimStrList(simStrList *listLsh,simStrList *listRsh);
int compareSimStrList(simStrList *listLsh,simStrList *listRsh);
#endif
