#ifndef SIMREADXML_H_
#define SIMREADXML_H_
#include "simMatChar.h"
#include "listChar.h"
#include "listMatChar.h"
#include "simStringList.h"
#include "convertStr2Digi.h"

#define BUFFER_SIZE 200

struct commentText
{
    char type; /* 0 upper Element, 1 behind Element, 2 below Element */
    simStrList text;
};

struct attrbXML
{
    vector_char name;
    vector_char value;
    char type; /* 0 = "", 1 =''  default = 0*/
};
struct elementXML
{
    vector_char name;
    vector_char value;
    struct commentText *com;
    struct elementXML *next;
    struct elementXML *firstChild;
    struct attrbXML   *attrb;
    int numAttrb;
    int typeEle; /* 0 = value type , 1 = non value type */
};
struct treeXML
{
    FILE* fp;
    struct elementXML *root;
    list_v_char stackParser;
    element str[BUFFER_SIZE];
    charList state;
    int index;

};

struct tagXMLAdd
{
    charList arrayOrder;
    simStrList tagName;
};

typedef struct attrbXML attrbXML;
typedef struct elementXML elementXML;
typedef struct treeXML treeXML;
typedef struct tagXMLAdd tagXMLAdd;
typedef struct commentText commentText;
elementXML* getRootElementXML(treeXML *root);
const void* getRootElementXML2(const void *obj);
elementXML* getNextELementXML(elementXML *root,const char *str,int order);
void* getNextELementXML2(void *root,const char *str,int order);
elementXML* getAnElementXML(treeXML *root,tagXMLAdd* searcher);
elementXML* getfirstChildXML(elementXML* root,const char *str);
void* getfirstChildXML2(const void *root,const char *str);
/* comment operation */
int initialComment(commentText* comment);
int makeACommentInElementXML(elementXML* root,int type);
int getTypeCommentInElementXML(elementXML* root);
int addCommentInElementXML(elementXML* root,simString* data);
int writeCommentIntoFpElementXML(elementXML* root,FILE* fp,int disSpace,int startIndex);
/* get value and attribute of an element */
vector_char getValueFirstChildXML(elementXML *root,const char *str,const char *defaultStr);
vector_char getValueDeepFirstChildXML(elementXML *root,simStrList *strList,const char *defaultStr);
vector_char getAttrbFromXMLEle(elementXML *root,const char *str,const char *strAttrb,const char *defaultStr);
vector_char getAttrbFromXMLEle2(elementXML *root,const char *strAttrb,const char *defaultStr);
vector_char getAttrbDeepFromXMLEle(elementXML *root,simStrList *strList,const char *strAttrb,const char *defaultStr);
/* check tag and attrib is available*/
int isFirstChildXML(elementXML *root,const char *str);
int isAttrbFromXMLEle(elementXML *root,const char *str,const char *strAttrb);
/*  get int double value of value and attribute of an element */
int getIntValueOfAttrbFromXMLEle(elementXML *root,const char *tagName,const char* attrb,const char* defaultVal);
int getIntValueOfAttrbDeepFromXMLEle(elementXML *root,simStrList *strList,const char* attrb,const char* defaultVal);
double getDoubleValueOfAttrbFromXMLEle(elementXML *root,const char *tagName,const char* attrb,const char* defaultVal);
double getDoubleValueOfAttrbDeepFromXMLEle(elementXML *root,simStrList *strList,const char* attrb,const char* defaultVal);
int compNameElemetVsCstr(vector_char *a,const char *str);
int new_elementXML(elementXML** eleXML);
int new_attrbXML(elementXML* eleXML);
int initial_attrbXML(attrbXML* atXML);
int initial_elementXML(elementXML* eleXML);
int initial_treeXML(treeXML *tXML);
int copyElementXML(elementXML *rhs,elementXML *lhs);
int copyAttrbXML(attrbXML* rhs,attrbXML* lhs);
void destructorTreeXML(treeXML *tXML);
void destructorAttrbXML(attrbXML* attrb);
void clearAttrbInElementXML(elementXML* elemXML);
void destructorElementXML(elementXML* elemXML);
void setTypeElement(elementXML* eleXML,char cmd);
FILE* readFile2XMLTree(elementXML* root,const char* filename);
int parserXML(treeXML *tXML,elementXML *rootEle);
int addData2Attrb(treeXML *root,elementXML *rootEle);
int setReadFile(treeXML *tXML,const char* filename);
int createTreeXML(treeXML *tXML);
/* 1 true 0 false */
char alphabetCheck(char in);
char digiCheck(char in);
char specialCharCheck(char in,char state);
int spaceExeception(int state,char reserveWord); /* 0 = execept, 1= not*/
char alphabetAndDigiCheck(char in);
/* 2 : '<' 3: '>' 4:'/' 5:'=' 6:'\"' 7:' ' 8:'\n' 9: '\t' 10: '\0' 11: '\\'  */
char reserveWord(char in);
int  findWord(treeXML *root,char state);
char  findPredefinedEntity(treeXML *root,int *index);
void printReserveWord(char in);
void popXMLElement(treeXML *root);
char assignStateReadXML(treeXML *tXML,char num);
void setTypeEleInTreeXML(elementXML *rootEle,char state);
void checkCommentXML(treeXML *tXML,char opt);
char getStringFile(element *str,int* index,FILE** fp,int size_buf);
void printTreeXML(treeXML *root);
void printEleXML(elementXML *root);
void printAttrbXML(attrbXML *root);

/* ------------ tagXMLAdd --------------*/
void initialTagXMLAdd(tagXMLAdd* tagXML);
void makeTagXMLAddEmpty(tagXMLAdd* tagXML);
int copyTagXMLAdd(tagXMLAdd* tagXMLLsh,tagXMLAdd* tagXMLRsh);
int addTagXMLValue(tagXMLAdd* tagXML,simString *msg,char val);
int addTagXMLvalueWithCStr(tagXMLAdd* tagXML,const char *msg,char val);
int removeTagXMLValue(tagXMLAdd* tagXML,int index);
int insertTagXMLValueAfterIndex(tagXMLAdd* tagXML,int index,simString *msg,char val);
int insertTagXMLValueAfterIndexWithCStr(tagXMLAdd* tagXML,int index,const char *msg,char val);
int getTagXMLValue(tagXMLAdd* tagXML,int index,simString *msg,char *val);
int getNumOfTagXMLAdd(tagXMLAdd* tagXML);
void destructTagXMLAdd(tagXMLAdd* tagXML);

/* all in 1 to get XML Tree */
int getSourceToTreeXML(treeXML *treeObj,const char *namefile);
/*defined 
    use  12 bits
    last nibble
    0 = sign
    1 = unsign
    2 = special (ascii)
    0x000 char
    0x010 int
    0x020 short
    0x030 long
    0x040 float
    0x050 double
    0x060 long double
    0x070 vector_char
    0x080 simString
    
*/
int getVectorToVar(vector_char *val,void* var,unsigned int typeVar);
int getValueOfFirstChildEle2Var(elementXML *root,const char *str,const char *defaultStr,void *var,unsigned int typeVar);
int getValueOfFirstChildEle2Var2(const void *root,const char *str,const char *defaultStr,void *var,unsigned int typeVar);
int getAttrbValueOfFirstChildEle2Var(elementXML *root,const char *tagName,const char* attrb,const char* defaultVal,void *var,unsigned int typeVar);
int getAttrbValueOfFirstChildEle2Var2(const void *root,const char *tagName,const char* attrb,const char* defaultVal,void *var,unsigned int typeVar);
int getAttrbValXMLEle2Var2(const void *ele,const char* attrb,const char* defaultVal,void *var,unsigned int typeVar);
#endif
