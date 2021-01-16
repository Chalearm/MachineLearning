#ifndef _REPLACINGAPP_H
#define _REPLACINGAPP_H
#include <stdio.h>
#include <stdlib.h>
#include "file_replace.h"
#include "symHandle.h"
#include "listPvoid.h"
#include "simMatChar.h"
#include "simReadXML.h"
#include "eleXMLNodeList.h"

struct replaceApp
{
    pVoidList fileList; /* fileHand type */
    pVoidList symbList; /* symbHand type */
};
typedef struct replaceApp repApp;
void constructorRepApp(repApp *obj);
void deleteSymNodeRepApp(void *node);
void deleteFileNodeRepApp(void *node);
void getInputRepApp(repApp *obj,const char *filename);
void getSymValueFromListXMLRepApp(repApp *obj,listElement *listSymXML);
void getFileValueFromListXMLRepApp(repApp *obj,listElement *fileObj);
void readNewReplaceFromFileRepApp(simString *str1); /* str1 contents file name*/
void initialRepApp(repApp *obj);
symbHand* newSymHand(const char *oldW,const char *nwW);
fileHand* newFileHand(const char *nameOld,const char *nwName);
void startProcessRepApp(repApp *obj);
void destructorRepApp(repApp *obj);
void printRepApp(repApp *obj);
#endif /* _REPLACINGAPP_H */