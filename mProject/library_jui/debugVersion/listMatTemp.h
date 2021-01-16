#ifndef LISTMATTEMP_H_
#define LISTMATTEMP_H_
#include "simMatTemp.h"
typedef unsigned int uint;
// node of list
struct node_v_temp
{
		vector_temp element;
		struct node_v_temp *next;
		struct node_v_temp *back;
};
typedef struct node_v_temp node_v_temp;

// list 
typedef struct
{	
	uint numOfNode;
	node_v_temp *firstNode;
	node_v_temp *lastNode;
	node_v_temp *currentNode;
}list_v_temp;

// node of list Matrix
 struct node_m_temp
{
		matrix_temp element;
		struct node_m_temp *next;
		struct node_m_temp *back;
};
typedef struct node_m_temp node_m_temp;

// list Matrix
typedef struct
{	
	uint numOfNode;
	node_m_temp *firstNode;
	node_m_temp *lastNode;
	node_m_temp *currentNode;
}list_m_temp;

void constructListVtemp(list_v_temp* alist);
void addNodeVtemp(list_v_temp* alist,vector_temp* dat);
void addNodeUniqueVtemp(list_v_temp* alist,vector_temp* dat);
void addNodeElement(list_v_temp* alist,element* dat,int size);
/*
void insertNodeVtemp(list_v_temp* alist,vector_temp* dat,int pos);
void insertFrontNodeVtemp(list_v_temp* alist,vector_temp* dat,int pos);
*/
void deleteNodeVtempByOreder(list_v_temp* alist,int ord);
void deleteNodeVtempByElement(list_v_temp* alist,vector_temp* dat);
void deleteLastNodeVtemp(list_v_temp* alist);
int searchListVtemp(list_v_temp* alist,vector_temp* dat);
vector_temp getValueVtemp(list_v_temp* alist,int index);
vector_temp getLastValueVtemp(list_v_temp* alist);
void printListVtemp(list_v_temp* alist,int opt);
/*
void replaceElementVtempByOrder(list_v_temp* alist,vector_temp* rep,int num);
void replaceElementVtempByElement(list_v_temp* alist,vector_temp* rep);
*/
matrix_temp listVtemp2Matrix(list_v_temp* alist);
void destructorListVtemp(list_v_temp* alist);
void makeEmptyVtemp(list_v_temp* alist);
void constructListMtemp(list_m_temp* alist);
void addNodeMtemp(list_m_temp* alist,matrix_temp* dat);
void addNodeUniqueMtemp(list_m_temp* alist,matrix_temp* dat);
/*
void insertNodeMtemp(list_m_temp* alist,matrix_temp* dat,int pos);
void insertFrontNodeMtemp(list_m_temp* alist,matrix_temp* dat,int pos);


*/
int searchListMtemp(list_m_temp* alist,matrix_temp* dat);
void deleteNodeMtempByOreder(list_m_temp* alist,int ord);
void deleteNodeMtempByElement(list_m_temp* alist,matrix_temp* dat);
matrix_temp 		getValueMtemp(list_m_temp* alist,int index);
/*
void replaceElementMtempByOrder(list_m_temp* alist,matrix_temp* rep,int num);


void replaceElementMtempByElement(list_m_temp* alist,matrix_temp* rep);

*/
void destructorListMtemp(list_m_temp* alist);
void makeEmptyMtemp(list_m_temp* alist);
void printListMtemp(list_m_temp* alist,int opt);

#endif //LISTMATTEMP_H__
