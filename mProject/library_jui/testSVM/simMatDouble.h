#ifndef SIMMATDOUBLE_H_
#define SIMMATDOUBLE_H_
#include <malloc.h>
#include <stdlib.h>
#include "initObj.h"
/* 
--------set initialize-----
 set =0  all element =0;
 set =1  random range(max,min)
 set =2  a,b  ---> a=max or min ,b=max or min
 set =3  run number (min -->max)
 set =4  Identify matrix or range 

*/
typedef double element;
typedef unsigned short usint;

typedef struct{
	usint lenght;
	element *data;
} vector_double;

typedef struct{
	usint row;
	usint col;
	element **data;
} matrix_double;

vector_double 	    new_vector_double(usint size);
matrix_double       new_matrix_double(usint row,usint col);


void delete_vector_double(vector_double *rhs);
void delete_matrix_double(matrix_double *rhs);

void initial_vector_double(vector_double* rhs,SetValue set);
void initial_matrix_double(matrix_double* rhs,SetValue set);

int supervise_matrix_double(matrix_double *rhs);
int supervise_vector_double(vector_double *rhs);

void print_vector_double(vector_double *rhs,int option);
void print_matrix_double(matrix_double *rhs,int option);

/* operation */
int multiply_v_m_double(vector_double *rhs,matrix_double *lhs,matrix_double *res);
int multiply_vt_m_double(vector_double *rhs,matrix_double *lhs,matrix_double *res);
int multiply_v_mt_double(vector_double *rhs,matrix_double *lhs,matrix_double *res);
int multiply_m_v_double(matrix_double *rhs,vector_double *lhs,vector_double *res);
int multiply_mt_v_double(matrix_double *rhs,vector_double *lhs,vector_double *res);
int multiply_m_vt_double(matrix_double *rhs,vector_double *lhs,matrix_double *res);
int multiply_m_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);
int multiply_mt_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);
int multiply_m_mt_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);
int multiply_v_vt_double(vector_double *rhs,vector_double *lhs,matrix_double *res);
int multiply_vt_v_double(vector_double *rhs,vector_double *lhs,element *res);//dot product

int dotmultiply_v_double(vector_double *rhs,vector_double *lhs,vector_double *res);
int dotmultiply_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);
int scalarmultiply_v_double(vector_double *rhs,element *lhs,vector_double *res);
int scalarmultiply_m_double(matrix_double *rhs,element *lhs,matrix_double *res); 
int plus_v_double(vector_double *rhs,vector_double *lhs,vector_double *res);
int plus_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);
int minus_v_double(vector_double *rhs,vector_double *lhs,vector_double *res);
int minus_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);
void copy_v_double(vector_double *rhs,vector_double *lhs);
void copy_m_double(matrix_double *rhs,matrix_double *lhs);
void swap_v_double(vector_double *rhs,vector_double *lhs);
void swap_m_double(matrix_double *rhs,matrix_double *lhs);
void minorMdouble(matrix_double *rhs,int row,int col);
void cutRowMdouble(matrix_double *rhs,int row);
void swapRowMdouble(matrix_double *rhs,int row1,int row2);
int compareEqual_v_double(vector_double *rhs,vector_double *lhs);
int compareEqual_m_double(matrix_double *rhs,matrix_double *lhs);
vector_double rowMatrix2Vectordouble(matrix_double *rhs,int index);
element determinant(matrix_double *a);
void colFactorMatrix(matrix_double *a,matrix_double *c);
void matrixInverse(matrix_double *a,matrix_double *c);
#endif //SIMMATDOUBLE_H_
