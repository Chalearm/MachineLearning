#ifndef SIMWRITEXML_H_
#define SIMWRITEXML_H_
#include "simMatChar.h"
#include "listChar.h"
#include "listMatChar.h"
#include "simStringList.h"
#include "simReadXML.h"
#define BUFFER_SIZE 200

struct attrbXMLNode
{
    struct attrbXMLNode* next;
    attrbXML data;
};
struct attrbXMLList
{
    struct attrbXMLNode* root;
    struct attrbXMLNode* last;
    int numNode;
};
typedef struct attrbXMLNode attrbXMLNode;
typedef struct attrbXMLList attrbXMLList;

/* ----------- attrbXMLNode-----------*/
int initialAttrbXMLNode(attrbXMLNode* node);
/* ------------attrbXMLList-----------*/
int initialAttrbXMLList(attrbXMLList* list);
int shallowCopyAttrbXMLList(attrbXMLList* rhs,attrbXMLList* lhs); /* no saft */
void makeAttrbXMLListEmpty(attrbXMLList* list);
void destructAttrbXMLList(attrbXMLList* list);
int addAttrbData2AttrbXMLList(attrbXMLList* list,attrbXML* data);
int readAttrbsFromEleXML2AttrbXMLList(attrbXMLList* list,elementXML* root);
int removeAttrbNodeAttrbXMLList(attrbXMLList* list,int index);
int removeAttrbNodeAttrbXMLListByName(attrbXMLList* list,const char* name);
vector_char* getNameOfAttrbWithIndexAttrbXMLList(attrbXMLList* list,int index);
vector_char* getValueOfAttrbWithIndexAttrbXMLList(attrbXMLList* list,int index);
attrbXML* getAttrbOfTheElement(treeXML *tXML,tagXMLAdd *tagXML,vector_char *name);

int setRootElement(treeXML *tXML,elementXML* root);
int setAnAttributeToElement(elementXML* root,attrbXML* attrb);
int setAttributeListToElement(elementXML* root,attrbXMLList* attrbList);
int setChildXMLElement(treeXML *tXML,elementXML* child,tagXMLAdd* tagXML);/* start from zero */
int setWriteFileTreeXML(treeXML *tXML,const char* filename);
int generateTextElement(elementXML* root,FILE* fp,int level);
int generateTextHeadElement(elementXML* root,FILE* fp,int level);
int generateTextEndElement(elementXML* root,FILE* fp,int level);
const char* genTextEndHead(elementXML *child,char type);
int generateTextAttrbs(elementXML* root,simString *attrb);
int generateATextAttrb(attrbXML *attrb,simString *txt);
int createXMLFile(treeXML *tXML);

/* Editable Some some part of XML Tree */
int changeNameElementWithCStr(treeXML *tXML,tagXMLAdd *tagXML,const char* msg);
int changeNameElementWithVector(treeXML *tXML,tagXMLAdd *tagXML,vector_char* msg);
int changeNameElement(treeXML *tXML,tagXMLAdd *tagXML,simString* msg);

int changeValueElementWithCStr(treeXML *tXML,tagXMLAdd *tagXML,const char* msg);
int changeValueElementWithVector(treeXML *tXML,tagXMLAdd *tagXML,vector_char* msg);
int changeValueElement(treeXML *tXML,tagXMLAdd *tagXML,simString* msg);

int changeTypeElement(treeXML *tXML,tagXMLAdd *tagXML,const char type);

/* attrb editable part */

int deleteAttrbInTheElement(treeXML *tXML,tagXMLAdd *tagXML,const char *name);
int deleteAttrbInTheElementByOrder(treeXML *tXML,tagXMLAdd *tagXML,int index);
int addAttrb2TheElementWithDetail(treeXML *tXML,tagXMLAdd *tagXML,const char *name,const char *value,const char type);
int addAttrb2TheElement(treeXML *tXML,tagXMLAdd *tagXML,attrbXML* data);
int changeNameAttrbOfTheElementWithCStr(treeXML *tXML,tagXMLAdd *tagXML,const char *name,const char *newName);
int changeNameAttrbOfTheElementWithSimStr(treeXML *tXML,tagXMLAdd *tagXML,simString *name,simString *newName);
int changeNameAttrbOfTheElement(treeXML *tXML,tagXMLAdd *tagXML,vector_char *name,vector_char *newName);
int changeValueAttrbOfTheElement(treeXML *tXML,tagXMLAdd *tagXML,vector_char *name,vector_char *value);
int changeValueAttrbOfTheElementWithCstr(treeXML *tXML,tagXMLAdd *tagXML,const char *name,const char *value);
int changeValueAttrbOfTheElementWithSimstr(treeXML *tXML,tagXMLAdd *tagXML,simString *name,simString *value);
int changeTypeAttrbOfTheElement(treeXML *tXML,tagXMLAdd *tagXML,vector_char *name,const char type);
int changeTypeAttrbOfTheElementWithCStr(treeXML *tXML,tagXMLAdd *tagXML,const char *name,const char type);
int changeTypeAttrbOfTheElementWithSimStr(treeXML *tXML,tagXMLAdd *tagXML,simString *name,const char type);

#endif
