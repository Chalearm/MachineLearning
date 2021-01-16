#ifndef ELEXMLNODELIST_H_
#define ELEXMLNODELIST_H_
#include "simReadXML.h"

struct nodeEle
{
    struct nodeEle *next;
    struct nodeEle *back;
    elementXML *data;
};
struct listElement
{
    struct nodeEle *first;
    struct nodeEle *last;
    struct nodeEle *cur;
    int curIndex;
    int numOfNode;
};
typedef struct listElement listElement;
typedef struct nodeEle nodeEle;
/* methods of nodeEle class */
void constructorEleNode(nodeEle* anode);
int  addNodeEleXMLData(nodeEle* anode,elementXML* dat);
elementXML* getXMLEleData(nodeEle* anode);
int setXMLEleData(nodeEle* anode,elementXML* dat);

/* methods of listElement */
int constructorListXMLEle(listElement* alist);
void makeNodeXMLEleEmpty(listElement* alist);
void destructListXMLEle(listElement* alist);
int addNodeEleXML(listElement* alist,elementXML* dat);
int deleteNodeXMLEleByIndex(listElement* alist,int index);
int generateXMLEleList(listElement* alist,elementXML *dat,const char *str);
int getNumOfXMLNode(listElement* alist);
int gtNXMLNd2(void *alist);
char isXMLNodeEmpty(listElement* alist);
elementXML* getXMLElement(listElement* alist,int index);
void* getXMLElement2(void *alist,int index);
nodeEle getXMLNode(listElement* alist,int index);
void printXMLList(listElement* alist);
void printXMLList2(void* alist);

int getSourceToXMLList(listElement* alist,elementXML *dat,const char *str);
int getSrc2XMLList2(void **list1,void *xmlEle,const char *tagName);
int getAttrbValXMLEle2Var(void *list1,int index,const char* attrb,const char* defaultVal,void *var,unsigned int typeVar);
void destructXMLList2(void **list1);
#endif
