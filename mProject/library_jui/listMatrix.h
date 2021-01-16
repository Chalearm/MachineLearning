#ifndef LISTMATRIX_H_
#define LISTMATRIX_H_
#include "SimpleMatrix.h"
typedef unsigned int uint;
// node of list
struct node_v_int
{
		vector_int element;
		struct node_v_int *next;
		struct node_v_int *back;
};
typedef struct node_v_int node_v_int;
struct node_v_char
{
		vector_char element;
		struct node_v_char *next;
		struct node_v_char *back;
};
typedef struct node_v_char node_v_char;
struct node_v_double
{
		vector_double element;
		struct node_v_double *next;
		struct node_v_double *back;
};
typedef struct node_v_double node_v_double;
struct node_v_float
{
		vector_float element;
		struct node_v_float *next;
		struct node_v_float *back;
};
typedef struct node_v_float node_v_float;

// list 
typedef struct
{	
	uint numOfNode;
	node_v_int *firstNode;
	node_v_int *lastNode;
	node_v_int *currentNode;
}list_v_int;
typedef struct
{	
	uint numOfNode;
	node_v_char *firstNode;
	node_v_char *lastNode;
	node_v_char *currentNode;
}list_v_char;
typedef struct
{	
	uint numOfNode;
	node_v_float *firstNode;
	node_v_float *lastNode;
	node_v_float *currentNode;
}list_v_float;
typedef struct
{	
	uint numOfNode;
	node_v_double *firstNode;
	node_v_double *lastNode;
	node_v_double *currentNode;
}list_v_double;

// node of list Matrix
 struct node_m_int
{
		matrix_int element;
		struct node_m_int *next;
		struct node_m_int *back;
};
typedef struct node_m_int node_m_int;
struct node_m_char
{
		matrix_char element;
		struct node_m_char *next;
		struct node_m_char *back;
};
typedef struct node_m_char node_m_char;
struct node_m_double
{
		matrix_double element;
		struct node_m_double *next;
		struct node_m_double *back;
};
typedef struct node_m_double node_m_double;
struct node_m_float
{
		matrix_float element;
		struct node_m_float *next;
		struct node_m_float *back;
};
typedef struct node_m_float node_m_float;

// list Matrix
typedef struct
{	
	uint numOfNode;
	node_m_int *firstNode;
	node_m_int *lastNode;
	node_m_int *currentNode;
}list_m_int;
typedef struct
{	
	uint numOfNode;
	node_m_char *firstNode;
	node_m_char *lastNode;
	node_m_char *currentNode;
}list_m_char;
typedef struct
{	
	uint numOfNode;
	node_m_float *firstNode;
	node_m_float *lastNode;
	node_m_float *currentNode;
}list_m_float;
typedef struct
{	
	uint numOfNode;
	node_m_double *firstNode;
	node_m_double *lastNode;
	node_m_double *currentNode;
}list_m_double;

void constructListVint(list_v_int* alist);
void constructListVchar(list_v_char* alist);
void constructListVfloat(list_v_float* alist);
void constructListVdouble(list_v_double* alist);

void addNodeVchar(list_v_char* alist,vector_char* dat);
void addNodeVdouble(list_v_double* alist,vector_double* dat);
void addNodeVfloat(list_v_float* alist,vector_float* dat);
void addNodeVint(list_v_int* alist,vector_int* dat);

void addNodeUniqueVchar(list_v_char* alist,vector_char* dat);
void addNodeUniqueVdouble(list_v_double* alist,vector_double* dat);
void addNodeUniqueVfloat(list_v_float* alist,vector_float* dat);
void addNodeUniqueVint(list_v_int* alist,vector_int* dat);
/*
void insertNodeVint(list_v_char* alist,vector_int* dat,int pos);
void insertNodeVchar(list_v_char* alist,vector_char* dat,int pos);
void insertNodeVfloat(list_v_float* alist,vector_float* dat,int pos);
void insertNodeVdouble(list_v_double* alist,vector_double* dat,int pos);

void insertFrontNodeVint(list_v_char* alist,vector_int* dat,int pos);
void insertFrontNodeVchar(list_v_char* alist,vector_char* dat,int pos);
void insertFrontNodeVfloat(list_v_float* alist,vector_float* dat,int pos);
void insertFrontNodeVdouble(list_v_double* alist,vector_double* dat,int pos);
*/
void deleteNodeVintByOreder(list_v_int* alist,int ord);
void deleteNodeVcharByOreder(list_v_char* alist,int ord);
void deleteNodeVfloatByOreder(list_v_float* alist,int ord);
void deleteNodeVdoubleByOreder(list_v_double* alist,int ord);

void deleteNodeVintByElement(list_v_int* alist,vector_int* dat);
void deleteNodeVcharByElement(list_v_char* alist,vector_char* dat);
void deleteNodeVfloatByElement(list_v_float* alist,vector_float* dat);
void deleteNodeVdoubleByElement(list_v_double* alist,vector_double* dat);

int searchListVint(list_v_int* alist,vector_int* dat);
int searchListVchar(list_v_char* alist,vector_char* dat);
int searchListVfloat(list_v_float* alist,vector_float* dat);
int searchListVdouble(list_v_double* alist,vector_double* dat);

vector_int getValueVint(list_v_int* alist,int index);
vector_char getValueVchar(list_v_char* alist,int index);
vector_float getValueVfloat(list_v_float* alist,int index);
vector_double getValueVdouble(list_v_double* alist,int index);

void printListVint(list_v_int* alist,int opt);
void printListVchar(list_v_char* alist,int opt);
void printListVdouble(list_v_double* alist,int opt);
void printListVfloat(list_v_float* alist,int opt);
/*
void replaceElementVintByOrder(list_v_int* alist,vector_int* rep,int num);
void replaceElementVcharByOrder(list_v_char* alist,vector_char* rep,int num);
void replaceElementVfloatByOrder(list_v_float* alist,vector_float* rep,int num);
void replaceElementVdoubleByOrder(list_v_double* alist,vector_double* rep,int num);

void replaceElementVintByElement(list_v_int* alist,vector_int* rep);
void replaceElementVcharByElement(list_v_char* alist,vector_char* rep);
void replaceElementVfloatByElement(list_v_float* alist,vector_float* rep);
void replaceElementVdoubleByElement(list_v_double* alist,vector_double* rep);


*/
matrix_int 	listVint2Matrix(list_v_int* alist);
matrix_char 	listVchar2Matrix(list_v_char* alist);
matrix_float 	listVfloat2Matrix(list_v_float* alist);
matrix_double 	listVdouble2Matrix(list_v_double* alist);

void destructorListVint(list_v_int* alist);
void destructorListVchar(list_v_char* alist);
void destructorListVdouble(list_v_double* alist);
void destructorListVfloat(list_v_float* alist);

void makeEmptyVint(list_v_int* alist);
void makeEmptyVchar(list_v_char* alist);
void makeEmptyVfloat(list_v_float* alist);
void makeEmptyVdouble(list_v_double* alist);

void constructListMint(list_m_int* alist);
void constructListMchar(list_m_char* alist);
void constructListMfloat(list_m_float* alist);
void constructListMdouble(list_m_double* alist);

void addNodeMchar(list_m_char* alist,matrix_char* dat);
void addNodeMdouble(list_m_double* alist,matrix_double* dat);
void addNodeMfloat(list_m_float* alist,matrix_float* dat);
void addNodeMint(list_m_int* alist,matrix_int* dat);

void addNodeUniqueMchar(list_m_char* alist,matrix_char* dat);
void addNodeUniqueMdouble(list_m_double* alist,matrix_double* dat);
void addNodeUniqueMfloat(list_m_float* alist,matrix_float* dat);
void addNodeUniqueMint(list_m_int* alist,matrix_int* dat);


/*
void insertNodeMint(list_m_char* alist,matrix_int* dat,int pos);
void insertNodeMchar(list_m_char* alist,matrix_char* dat,int pos);
void insertNodeMfloat(list_m_float* alist,matrix_float* dat,int pos);
void insertNodeMdouble(list_m_double* alist,matrix_double* dat,int pos);

void insertFrontNodeMint(list_m_char* alist,matrix_int* dat,int pos);
void insertFrontNodeMchar(list_m_char* alist,matrix_char* dat,int pos);
void insertFrontNodeMfloat(list_m_float* alist,matrix_float* dat,int pos);
void insertFrontNodeMdouble(list_m_double* alist,matrix_double* dat,int pos);

*/
int searchListMint(list_m_int* alist,matrix_int* dat);
int searchListMchar(list_m_char* alist,matrix_char* dat);
int searchListMfloat(list_m_float* alist,matrix_float* dat);
int searchListMdouble(list_m_double* alist,matrix_double* dat);

void deleteNodeMintByOreder(list_m_int* alist,int ord);
void deleteNodeMcharByOreder(list_m_char* alist,int ord);
void deleteNodeMfloatByOreder(list_m_float* alist,int ord);
void deleteNodeMdoubleByOreder(list_m_double* alist,int ord);

void deleteNodeMintByElement(list_m_int* alist,matrix_int* dat);
void deleteNodeMcharByElement(list_m_char* alist,matrix_char* dat);
void deleteNodeMfloatByElement(list_m_float* alist,matrix_float* dat);
void deleteNodeMdoubleByElement(list_m_double* alist,matrix_double* dat);

matrix_int 		getValueMint(list_m_int* alist,int index);
matrix_char		getValueMchar(list_m_char* alist,int index);
matrix_float	getValueMfloat(list_m_float* alist,int index);
matrix_double 	getValueMdouble(list_m_double* alist,int index);
/*
void replaceElementMintByOrder(list_m_int* alist,matrix_int* rep,int num);
void replaceElementMcharByOrder(list_m_char* alist,matrix_char* rep,int num);
void replaceElementMfloatByOrder(list_m_float* alist,matrix_float* rep,int num);
void replaceElementMdoubleByOrder(list_m_double* alist,matrix_double* rep,int num);

void replaceElementMintByElement(list_m_int* alist,matrix_int* rep);
void replaceElementMcharByElement(list_m_char* alist,matrix_char* rep);
void replaceElementMfloatByElement(list_m_float* alist,matrix_float* rep);
void replaceElementMdoubleByElement(list_m_double* alist,matrix_double* rep);
*/
void destructorListMint(list_m_int* alist);
void destructorListMchar(list_m_char* alist);
void destructorListMdouble(list_m_double* alist);
void destructorListMfloat(list_m_float* alist);

void makeEmptyMint(list_m_int* alist);
void makeEmptyMchar(list_m_char* alist);
void makeEmptyMfloat(list_m_float* alist);
void makeEmptyMdouble(list_m_double* alist);

void printListMint(list_m_int* alist,int opt);
void printListMchar(list_m_char* alist,int opt);
void printListMdouble(list_m_double* alist,int opt);
void printListMfloat(list_m_float* alist,int opt);
#endif //LISTMATRIX_H__
