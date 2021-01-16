#ifndef _LiSTTEMP_H
#define _LiSTTEMP_H
#include <stdlib.h>
#include "simMatTemp.h"
struct tempElement
{
    element data;
    struct tempElement *next;
    struct tempElement *back;
};

typedef struct tempElement tempElement;
struct tempList
{
    tempElement *first;
    tempElement *last;
    tempElement *cur;
    int numOfNode; 
};

typedef struct tempList tempList;
void constructorTempList(tempList *list);
int addDataPt(tempList *list,element *data);
int addData(tempList *list,element data);
void makeEmptyTempList(tempList *list);
void destructorTempList(tempList *list);
int searchTempListPt(tempList* list,element *data);
int searchTempList(tempList* list,element data);
element getDataTempList(tempList* list,int index);
element getLastDataTempList(tempList* list);
int countTempList(tempList* list);
element popTempList(tempList* list);
int pushTempListPt(tempList* list,element *data);	
int pushTempList(tempList* list,element data);	
int enQueueTempList(tempList* list,element data);
int enQueueTempListPt(tempList* list,element *data);
element deQueueTempList(tempList* list);
int deleteIndexElementTempList(tempList *list,int index);
int deleteElementTempListPt(tempList *list,element *data);
int deleteElementTempList(tempList *list,element data);
int swapElementTempList(tempList *list,int index1,int index2);
int swapElementTempListPt(tempList *list,int index1,int index2);
void printTempList(tempList *list,int opt);

vector_temp convertTovector_temp(tempList *list);
#endif
