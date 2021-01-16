#ifndef LISTMATDOUBLE_H_
#define LISTMATDOUBLE_H_
#include "simMatDouble.h"
typedef unsigned int uint;
/* node of list */
struct node_v_double
{
        vector_double element;
        struct node_v_double *next;
        struct node_v_double *back;
};
typedef struct node_v_double node_v_double;

/* list */ 
typedef struct
{
    uint numOfNode;
    node_v_double *firstNode;
    node_v_double *lastNode;
    node_v_double *currentNode;
}list_v_double;

/* node of list Matrix */
 struct node_m_double
{
        matrix_double element;
        struct node_m_double *next;
        struct node_m_double *back;
};
typedef struct node_m_double node_m_double;

/* list Matrix*/
typedef struct
{
    uint numOfNode;
    node_m_double *firstNode;
    node_m_double *lastNode;
    node_m_double *currentNode;
}list_m_double;

void constructListVdouble(list_v_double* alist);
void addNodeVdouble(list_v_double* alist,vector_double* dat);
void addNodeUniqueVdouble(list_v_double* alist,vector_double* dat);
void addNodeDouble(list_v_double* alist,double* dat,int size);
/*
void insertNodeVdouble(list_v_double* alist,vector_double* dat,int pos);
void insertFrontNodeVdouble(list_v_double* alist,vector_double* dat,int pos);
*/
void deleteNodeVdoubleByOreder(list_v_double* alist,int ord);
void deleteNodeVdoubleByElement(list_v_double* alist,vector_double* dat);
void deleteLastNodeVdouble(list_v_double* alist);
int searchListVdouble(list_v_double* alist,vector_double* dat);
vector_double getValueVdouble(list_v_double* alist,int index);
vector_double getLastValueVdouble(list_v_double* alist);
void printListVdouble(list_v_double* alist,int opt);
/*
void replaceElementVdoubleByOrder(list_v_double* alist,vector_double* rep,int num);
void replaceElementVdoubleByElement(list_v_double* alist,vector_double* rep);
*/
matrix_double listVdouble2Matrix(list_v_double* alist);
void destructorListVdouble(list_v_double* alist);
void makeEmptyVdouble(list_v_double* alist);
void constructListMdouble(list_m_double* alist);
void addNodeMdouble(list_m_double* alist,matrix_double* dat);
void addNodeUniqueMdouble(list_m_double* alist,matrix_double* dat);
/*
void insertNodeMdouble(list_m_double* alist,matrix_double* dat,int pos);
void insertFrontNodeMdouble(list_m_double* alist,matrix_double* dat,int pos);


*/
int searchListMdouble(list_m_double* alist,matrix_double* dat);
void deleteNodeMdoubleByOreder(list_m_double* alist,int ord);
void deleteNodeMdoubleByElement(list_m_double* alist,matrix_double* dat);
matrix_double   getValueMdouble(list_m_double* alist,int index);
/*
void replaceElementMdoubleByOrder(list_m_double* alist,matrix_double* rep,int num);


void replaceElementMdoubleByElement(list_m_double* alist,matrix_double* rep);

*/
void destructorListMdouble(list_m_double* alist);
void makeEmptyMdouble(list_m_double* alist);
void printListMdouble(list_m_double* alist,int opt);

#endif /*LISTMATDOUBLE_H_*/
