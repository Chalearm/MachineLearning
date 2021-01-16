#ifndef _LiSTPVOID_H
#define _LiSTPVOID_H
#include <stdlib.h>
#include <stdio.h>
/*#include "simMatInt.h"*/
struct pVoidElement
{
    void* data;
    struct pVoidElement *next;
    struct pVoidElement *back;
};

typedef struct pVoidElement pVoidElement;
struct pVoidList
{
    void *first;
    void *last;
    void *cur;
    int currentIndex;
    int numOfNode;
    int isFreeData; /* 1 = is Free , 0 is no*/
    void (*deleteData)(void*);
    void *otherSrc;
    
    void* (*getNext)(void*);
    void* (*getBack)(void*);
    void* (*getDat)(void*);
    
    int   (*setNext)(void*,void*);
    int   (*setBack)(void*,void*);
    int   (*setDat)(void*,void*);
    
    void* (*getAllocate)(void*);
    void (*freeAlloc)(void*,void*);
    
};

typedef struct pVoidList pVoidList;

void constructorPVoidList(pVoidList *list);
void constrPVL2(void *list1,void *othSrc,void **paraFunct);
void setIsFreeDataOfPVoidList(void *obj,int value,void *delDatFunct);
int addDataPtPVoidList(pVoidList *list,void** data);
int addDataPVoidList(pVoidList *list,void* data);
void freeNode(void *list1,void *node);
void makeEmptyPVoidList(pVoidList *list);
void destructorPVoidList(pVoidList *list);
int copyPVoidList(pVoidList *lsh,pVoidList *rsh);
int insetWithIndexPVoidList(pVoidList *list,void* data,int index);
int searchPVoidListPt(pVoidList* list,void** data);
int searchPVoidList(pVoidList* list,void* data);
int replaceValInPVoidList(pVoidList *list,void *data,int index);
void* getDataPVoidList(pVoidList *list,int index); 
pVoidElement* getAddressElementPVoidList(pVoidList* list,int index);
void* getLastDataPVoidList(pVoidList* list);
void pullNodeOutFromPVoidList(pVoidList* list,pVoidElement* node1);
int countPVoidList(pVoidList* list);
void* popPVoidList(pVoidList* list);
void setCurrentPointerPVoidList(pVoidList* list,int index);
void resetCurrentPointerPVoidList(pVoidList* list);
int getCurrentIndexOfPVoidList(pVoidList* list);
int pushPVoidListPt(pVoidList* list,void** data);
int pushPVoidList(pVoidList* list,void* data);
int enQueuePVoidList(pVoidList* list,void* data);
int enQueuePVoidListPt(pVoidList* list,void** data);
void* deQueuePVoidList(pVoidList* list);
int deleteIndexElementPVoidList(pVoidList *list,int index);
int deleteElementPVoidListPt(pVoidList *list,void** data);
int deleteElementPVoidList(pVoidList *list,void* data);
int swapElementPVoidList(pVoidList *list,int index1,int index2);
int swapElementPVoidListPt(pVoidList *list,int index1,int index2);
void printPVoidList(pVoidList *list,int opt);

/*vector_int convertTovector_int(pVoidList *list);*/


/* private method ------ */
void* getNN(void *obj,void *node);
void* getNB(void *obj,void *node);
void* getBB(void *obj,void *node);
void* getBN(void *obj,void *node);
void* getNAt(void *obj,int index,void *node);
void* getBAt(void *obj,int index,void *node);

int setNN(void *obj,void *node1,void *node2);
int setNB(void *obj,void *node1,void *node2);
int setBB(void *obj,void *node1,void *node2);
int setBN(void *obj,void *node1,void *node2);
int setNAt(void *obj,void *node1,void *node2,int index);
int setBAt(void *obj,void *node1,void *node2,int index);


/* end of private method ----- */
/* for struct pVoidElement*/
void* getNxpVoidEle(void *node);
void* getBkpVoidEle(void *node);
void* getDatpVoidEle(void *node);

int   setNxpVoidEle(void *node1,void *node2);
int   setBkpVoidEle(void *node1,void *node2);
int   setDatpVoidEle(void *node1,void *node2);

void* getAllocatePVoidEle(void *obj);
void freeAllocPVoidEle(void *obj,void *node);
/* End of for struct pVoidElement*/
#endif /* _LiSTPVOID_H */
