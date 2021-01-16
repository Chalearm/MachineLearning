#ifndef _LiSTINT_H
#define _LiSTINT_H
#include <stdlib.h>
#include "simMatInt.h"
struct intElement
{
    int data;
    struct intElement *next;
    struct intElement *back;
};

typedef struct intElement intElement;
struct intList
{
    intElement *first;
    intElement *last;
    intElement *cur;
    int currentIndex;
    int numOfNode;
};

typedef struct intList intList;
void constructorIntList(intList *list);
int addDataPtIntList(intList *list,int *data);
int addDataIntList(intList *list,int data);
void makeEmptyIntList(intList *list);
void destructorIntList(intList *list);
int copyIntList(intList *lsh,intList *rsh);
int insetWithIndexIntList(intList *list,int data,int index);
int searchIntListPt(intList* list,int *data);
int searchIntList(intList* list,int data);
int getDataIntList(intList* list,int index);
intElement* getAddressElementIntList(intList* list,int index);
int getLastDataIntList(intList* list);
int countIntList(intList* list);
int popIntList(intList* list);
void setCurrentPointerIntList(intList* list,int index);
void resetCurrentPointerIntList(intList* list);
int getCurrentIndexOfIntList(intList* list);
int pushIntListPt(intList* list,int *data);
int pushIntList(intList* list,int data);
int enQueueIntList(intList* list,int data);
int enQueueIntListPt(intList* list,int *data);
int deQueueIntList(intList* list);
int deleteIndexElementIntList(intList *list,int index);
int deleteElementIntListPt(intList *list,int *data);
int deleteElementIntList(intList *list,int data);
int swapElementIntList(intList *list,int index1,int index2);
int swapElementIntListPt(intList *list,int index1,int index2);
void printIntList(intList *list,int opt);

vector_int convertTovector_int(intList *list);
#endif /* _LiSTINT_H */
