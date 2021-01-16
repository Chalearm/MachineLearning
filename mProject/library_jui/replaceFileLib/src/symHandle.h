#ifndef _SYMHANDLE_H
#define _SYMHANDLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listPvoid.h"
#define MAX_BUFF_SYM 500
struct symbolHandle
{
    char *m_oldWord;
    char *m_newWord;
    int m_oldWLength;
    int m_newWLength;
};
typedef struct symbolHandle symbHand;

void constructorSymbHand(symbHand *obj);
int setSymbolToBuff(symbHand *obj,const char* oldBuff,char *newBuff,int sizeNewBuff);
void setSymbHand(symbHand* obj,const char *oldW,const char *nwW);
void destructorSymbHand(symbHand* obj);
void  updateAttrbSymBH(symbHand *obj,pVoidList *list);
void printSysHand(symbHand* obj);
#endif /* _SYMHANDLE_H */