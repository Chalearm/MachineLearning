#ifndef FILENAMEHANDLE_H_#define FILENAMEHANDLE_H_#include <stdio.h>#include "simString.h"struct FileNameHandle{    simString nameFile;    simString typeFile;    int numDuplicate; /* when file is redundant its run to a step */    char asciiPrefix; /* to divide name part and numDuplicat part default '('*/    char asciiSuffix; /* to divide name part and numDuplicat part default ')'*/    char saveType;  /* 1 replace old file,increace step 1 steps, */};typedef struct FileNameHandle FileNameHandle;int initialFileNameHandle(FileNameHandle *fileNameHandle);void destructFileNameHandle(FileNameHandle *fileNameHandle);simString getFileName(FileNameHandle *fileNameHandle);int setAllValueOfFileNameHandle(FileNameHandle *fileNameHandle,simString* name,simString* type,char saveT,char ascii1,char ascii2);#endif