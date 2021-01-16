#ifndef XMLUI_H_
#define XMLUI_H_
#include <stdio.h>
#include <string.h>
#include "simMatChar.h"
#include "listChar.h"
#include "listMatChar.h"
#include "simString.h"
#include "simStringList.h"
#include "simReadXML.h"
#include "eleXMLNodeList.h"
#include "simWriteXML.h"
#include "FileNameHandle.h"

struct attrbUi
{
    vector_char name; 
    vector_char value;
    simString desp; /* description for detail how to key input*/
    char typeVal;
    char type;
};
struct tagEleUi
{
    int id;
    int idP;
    char isList;
    vector_char name;
    vector_char value;
    char type;
    commentText comtxt;
    char hasComment;
    simString desp;
    int numAttrb;
    struct attrbUi *attrbUiObj;
    struct tagEleUi *next;
    
};
struct XMLUi
{
    struct tagEleUi *eleUi;
    int numTag;
    FILE* formFile;
    FileNameHandle fileName;
};
typedef struct attrbUi attrbUi;
typedef struct tagEleUi tagEleUi;
typedef struct XMLUi XMLUi;
void initialAttrbUi(attrbUi* attrbUiObj);
void destructAttrbUi(attrbUi* attrbUiObj);

void initialTagEleUi(tagEleUi* tagEleUiObj);
void destructTagEleUi(tagEleUi* tagEleUiObj);

void initialXMLUi(XMLUi *XMLUiObj);
void destructXMLUi(XMLUi *XMLUiObj);

int alloNumEleUiXMLUi(XMLUi *XMLUiObj,int numb);
int alloNumAttrbTagEleUi(tagEleUi *tagEleUiObj,int numb);
int loadSourceToXMLUi(XMLUi *XMLUiObj,const char *namefile);
int loadNode2TagEle(tagEleUi *tagEleUiObj,elementXML *pEle);
int loadNode2AttrbUi(attrbUi *attrbUiObj,elementXML *pEle);
int mappingTypeXMLUi(const char* type);
const char* valueTypeName(char type);
void printAttrbUi(attrbUi *attrbUiObj);
void printTagEleUi(tagEleUi *eleUiObj);
void printXMLUi(XMLUi *XMLUiObj);
#endif