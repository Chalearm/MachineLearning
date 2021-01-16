#ifndef _LiSTCHAR_H
#define _LiSTCHAR_H
#include <stdlib.h>
#include "simMatChar.h"
struct charElement
{
	element data;
 	struct charElement *next;
	struct charElement *back;
};

typedef struct charElement charElement;
struct charList
{
	charElement *first;
	charElement *last;
	charElement *cur;
    int currentIndex;
	int numOfNode; 
};

typedef struct charList charList;
void constructorCharList(charList *list);
int addDataPt(charList *list,element *data);
int addData(charList *list,element data);
void makeEmptyCharList(charList *list);
void destructorCharList(charList *list);
int copyCharList(charList *lsh,charList *rsh);
int insetWithIndexCharList(charList *list,element data,int index);
int searchCharListPt(charList* list,element *data);
int searchCharList(charList* list,element data);
element getDataCharList(charList* list,int index);
charElement* getAddressElementCharList(charList* list,int index);
void setCurrentPointerCharList(charList* list,int index);
void resetCurrentPointerCharList(charList* list);
element getLastDataCharList(charList* list);
int getCurrentIndexOfCharList(charList* list);
int countCharList(charList* list);
element popCharList(charList* list);
int pushCharListPt(charList* list,element *data);	
int pushCharList(charList* list,element data);	
int enQueueCharList(charList* list,element data);
int enQueueCharListPt(charList* list,element *data);
element deQueueCharList(charList* list);
int deleteIndexElementCharList(charList *list,int index);
int deleteElementCharListPt(charList *list,element *data);
int deleteElementCharList(charList *list,element data);
int swapElementCharList(charList *list,int index1,int index2);
int swapElementCharListPt(charList *list,int index1,int index2);
void printCharList(charList *list,int opt);

vector_char convertTovector_char(charList *list);
#endif
