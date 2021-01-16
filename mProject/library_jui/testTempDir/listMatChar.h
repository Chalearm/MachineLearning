#ifndef LISTMATCHAR_H_
#define LISTMATCHAR_H_
#include "simMatChar.h"
typedef unsigned int uint;
// node of list
struct node_v_char
{
		vector_char element;
		struct node_v_char *next;
		struct node_v_char *back;
};
typedef struct node_v_char node_v_char;

// list 
typedef struct
{	
	uint numOfNode;
	node_v_char *firstNode;
	node_v_char *lastNode;
	node_v_char *currentNode;
}list_v_char;

// node of list Matrix
 struct node_m_char
{
		matrix_char element;
		struct node_m_char *next;
		struct node_m_char *back;
};
typedef struct node_m_char node_m_char;

// list Matrix
typedef struct
{	
	uint numOfNode;
	node_m_char *firstNode;
	node_m_char *lastNode;
	node_m_char *currentNode;
}list_m_char;

void constructListVchar(list_v_char* alist);
void addNodeVchar(list_v_char* alist,vector_char* dat);
void addNodeUniqueVchar(list_v_char* alist,vector_char* dat);
/*
void insertNodeVchar(list_v_char* alist,vector_char* dat,int pos);
void insertFrontNodeVchar(list_v_char* alist,vector_char* dat,int pos);
*/
void deleteNodeVcharByOreder(list_v_char* alist,int ord);
void deleteNodeVcharByElement(list_v_char* alist,vector_char* dat);
int searchListVchar(list_v_char* alist,vector_char* dat);
vector_char getValueVchar(list_v_char* alist,int index);
void printListVchar(list_v_char* alist,int opt);
/*
void replaceElementVcharByOrder(list_v_char* alist,vector_char* rep,int num);
void replaceElementVcharByElement(list_v_char* alist,vector_char* rep);
*/
matrix_char 	listVchar2Matrix(list_v_char* alist);
void destructorListVchar(list_v_char* alist);
void makeEmptyVchar(list_v_char* alist);
void constructListMchar(list_m_char* alist);
void addNodeMchar(list_m_char* alist,matrix_char* dat);
void addNodeUniqueMchar(list_m_char* alist,matrix_char* dat);
/*
void insertNodeMchar(list_m_char* alist,matrix_char* dat,int pos);
void insertFrontNodeMchar(list_m_char* alist,matrix_char* dat,int pos);


*/
int searchListMchar(list_m_char* alist,matrix_char* dat);
void deleteNodeMcharByOreder(list_m_char* alist,int ord);
void deleteNodeMcharByElement(list_m_char* alist,matrix_char* dat);
matrix_char 		getValueMchar(list_m_char* alist,int index);
/*
void replaceElementMcharByOrder(list_m_char* alist,matrix_char* rep,int num);


void replaceElementMcharByElement(list_m_char* alist,matrix_char* rep);

*/
void destructorListMchar(list_m_char* alist);
void makeEmptyMchar(list_m_char* alist);
void printListMchar(list_m_char* alist,int opt);

#endif //LISTMATTEMP_H__
