/********************************************************************/
/*
      FILE     :   simStringTree.h
      Name     :   Chalearm Saelim
      Date     :   24 April 2016 15:45
      Email    :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose  :   To manage the simString struct in the AVL Tree style
                   To make a good performance of searching and look up the data
                   ** the structure support mapping string and the value 
   Description :   This structure is based on the AVL tree which supports keeping and fast accessing 

     Dependency:   We use the included library as below 
                    #include "simString.h"
                    #include "simMatChar.h"
                    #include "avlTree.h"
  How to compile:   - Not update -
*/
/*******************************************************************/
#ifndef SIMSTRINGTREE_H_
#define SIMSTRINGTREE_H_
#include <stdio.h>
#include <stdlib.h>
#include "simString.h"
#include "simMatChar.h"
#include "avlTree.h"

struct simStrTree
{
    /* defined the AVL tree type as pVoid with value*/
    binaryTree m_root;
};

typedef struct simStrTree simStrTree; 
int initialSimStrT(simStrTree *obj,void (*delData)(void*,void*),void (*copyDataValue)(void*,void*));
void destructorSimStrT(simStrTree *obj);
int addELeSimStrTFromVChar(simStrTree *obj,vector_char *vch,void *val);
int addELeSimStrT(simStrTree *obj,simString *str,void *val);
int addELeSimStrTFromCStr(simStrTree *obj,const char* str,void *val); 
void printSimStrT(simStrTree *obj);
int getNumEleSimStrT(simStrTree *obj);
void* search2GetValueInSimStrTByCstr(simStrTree *obj,const char *cstr);
void* search2GetValueInSimStrTByVChar(simStrTree *obj,vector_char *vch);
void* search2GetValueInSimStrTBySimStr(simStrTree *obj,simString *simStr);
int deleteEleSimStrTByCStr(simStrTree *obj,const char *cstr);
int deleteEleSimStrTBySimStr(simStrTree *obj,simString *simStr);
int deleteEleSimStrTByVChar(simStrTree *obj,vector_char *vch);
int copySimStrTree(simStrTree *oLsh,simStrTree *oRsh);
/*
int compareSimStrList(simStrTree *oLsh,simStrTree *oRsh);

*/

/* private methods*/
void* copyKeySimStrTree(binaryTree *obj,void *node);
int compSimStrEleInSimStrTree(const void* a,const void *b);
void delSimStrKeyInSimStrTree(void *obj,void *key);
void printKeyOfSimStrT(void *key,char *buff); /* with address*/
#endif /* SIMSTRINGTREE_H_*/
