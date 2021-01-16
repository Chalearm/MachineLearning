#ifndef SIMREADXML_H_
#define SIMREADXML_H_
#include "simMatChar.h"
#include "listChar.h"
#include "listMatChar.h"
#define BUFFER_SIZE 200

struct attrbXML
{
	vector_char name;
	vector_char value;
};
struct elementXML
{
	vector_char name;
	vector_char value;
	struct elementXML *next;
	struct elementXML *firstChild;
	struct attrbXML   *attrb;
	int numAttrb;
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
typedef struct attrbXML attrbXML;
typedef struct elementXML elementXML;
typedef struct treeXML treeXML;
elementXML* getRootElementXML(treeXML *root);
elementXML* getfirstChildXML(elementXML* root,const char *str);
int compNameElemetVsCstr(vector_char *a,const char *str);
int new_elementXML(elementXML** eleXML);
int new_attrbXML(elementXML* eleXML);
int initial_attrbXML(attrbXML* atXML);
int initial_elementXML(elementXML* eleXML);
int initial_treeXML(treeXML *tXML);
void destructorTreeXML(treeXML *tXML);
void destructorAttrbXML(attrbXML* attrb);
void destructorElementXML(elementXML* elemXML);
FILE* readFile2XMLTree(elementXML* root,const char* filename);
void parserXML(treeXML *tXML,elementXML *rootEle);
int addData2Attrb(treeXML *root,elementXML *rootEle);
int setReadFile(treeXML *tXML,const char* filename);
void createTreeXML(treeXML *tXML);
// 1 true 0 false
char alphabetCheck(char in);
char digiCheck(char in);
char specialCharCheck(char in);
char alphabetAndDigiCheck(char in);
// 2 : '<' 3: '>' 4:'/' 5:'=' 6:'\"' 7:' ' 8:'\n' 9: '\t' 10: '\0' 11: '\\'
char reserveWord(char in);
int  findWord(char* in);
void printReserveWord(char in);
void popXMLElement(treeXML *root);
char assignStateReadXML(treeXML *tXML,char num);
void checkCommentXML(treeXML *tXML,char opt);
char getStringFile(element *str,int* index,FILE** fp,int size_buf);
void printTreeXML(treeXML *root);	
void printEleXML(elementXML *root);
void printAttrbXML(attrbXML *root);
#endif
