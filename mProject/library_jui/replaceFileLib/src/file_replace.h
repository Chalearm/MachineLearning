#ifndef _FILE_REPLACE_H
#define _FILE_REPLACE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listPvoid.h"
#include "symHandle.h"
/* the maximum number of characters of the filename */
#define MAX_CHAR 300 
#define MAX_BUFF 500

/* this object is created after the list of symbols is created */
struct  fileHandle
{
    char oldFile[MAX_CHAR];
    char newFile[MAX_CHAR];
};
typedef struct fileHandle fileHand;

void constructorFileHand(fileHand *obj);
void destructorFileHand(fileHand *obj);
void setFileHand(fileHand *obj,const char *nameold,const char *newName);
void updateAttrbFileHand(fileHand *obj,pVoidList *list);
void processReplacingWordFileHande(fileHand *obj,pVoidList *list);
#endif /* _FILE_REPLACE_H */