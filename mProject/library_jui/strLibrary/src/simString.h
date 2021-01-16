#ifndef SIMSTRING_H_
#define SIMSTRING_H_
#include <stdio.h>
#include <stdlib.h>
#include "simMatChar.h"
struct simString
{
    char *data;
    int length;
};
typedef struct simString simString;
void convertCString2SimString(simString *simStr,const char *ch);
void convertVectorChar2SimString(simString *simStr,vector_char *vch);
void convertSimString2VectorChar(vector_char *vch,simString *simStr);
void initialSimString(simString *simStr);
int newSimStr(simString *simStr,int num);
int newSimStrWithInitailData(simString *simStr,int num,char dat);
void destructSimString(simString *simStr);
void copySimStr(simString *simStr1,simString *simStr2);
void copyNLetterSimStr(simString *simStr1,simString *simStr2,int num);
int concatSimString(simString *simStr1,simString *simStr2,simString *res);
int concatSimStringPathDirectory(simString *simStr1,simString *simStr2,simString *res);
int compareSimString(simString *simStr1,simString *simStr2);
int compareSimStrWithCstr(simString *simStr1,const char *cstr);
int compareNLetterSimString(simString *simStr1,simString *simStr2,int num);
void printSimString(simString *simStr1);

#endif

