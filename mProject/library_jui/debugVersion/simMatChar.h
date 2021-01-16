#ifndef SIMMATCHAR_H_
#define SIMMATCHAR_H_
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
typedef char element;
typedef unsigned short usint;

typedef struct{
	usint lenght;
	element *data;
} vector_char;

typedef struct{
	usint row;
	usint col;
	element **data;
} matrix_char;

vector_char 	    new_vector_char(usint size);
matrix_char       new_matrix_char(usint row,usint col);


void delete_vector_char(vector_char *rhs);
void delete_matrix_char(matrix_char *rhs);

void initial_vector_char(vector_char* rhs,SetValue set);
void initial_matrix_char(matrix_char* rhs,SetValue set);

int supervise_matrix_char(matrix_char *rhs);
int supervise_vector_char(vector_char *rhs);

void print_vector_char(vector_char *rhs,int option);
void print_matrix_char(matrix_char *rhs,int option);

/* operation */
int multiply_v_m_char(vector_char *rhs,matrix_char *lhs,matrix_char *res);
int multiply_vt_m_char(vector_char *rhs,matrix_char *lhs,matrix_char *res);
int multiply_v_mt_char(vector_char *rhs,matrix_char *lhs,matrix_char *res);
int multiply_m_v_char(matrix_char *rhs,vector_char *lhs,vector_char *res);
int multiply_mt_v_char(matrix_char *rhs,vector_char *lhs,vector_char *res);
int multiply_m_vt_char(matrix_char *rhs,vector_char *lhs,matrix_char *res);
int multiply_m_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res);
int multiply_mt_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res);
int multiply_m_mt_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res);
int multiply_v_vt_char(vector_char *rhs,vector_char *lhs,matrix_char *res);
int multiply_vt_v_char(vector_char *rhs,vector_char *lhs,int *res);//dot product

int dotmultiply_v_char(vector_char *rhs,vector_char *lhs,vector_char *res);
int dotmultiply_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res);
int scalarmultiply_v_char(vector_char *rhs,element *lhs,vector_char *res);
int scalarmultiply_m_char(matrix_char *rhs,element *lhs,matrix_char *res); 
int plus_v_char(vector_char *rhs,vector_char *lhs,vector_char *res);
int plus_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res);
int minus_v_char(vector_char *rhs,vector_char *lhs,vector_char *res);
int minus_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res);
void copy_v_char(vector_char *rhs,vector_char *lhs);
void copy_m_char(matrix_char *rhs,matrix_char *lhs);
void swap_v_char(vector_char *rhs,vector_char *lhs);
void swap_m_char(matrix_char *rhs,matrix_char *lhs);
void minorMchar(matrix_char *rhs,int row,int col);
void cutRowMchar(matrix_char *rhs,int row);
void swapRowMchar(matrix_char *rhs,int row1,int row2);
int compareEqual_v_char(vector_char *rhs,vector_char *lhs);
int compareEqual_m_char(matrix_char *rhs,matrix_char *lhs);
vector_char rowMatrix2Vectorchar(matrix_char *rhs,int index);
element determinant(matrix_char *a);
void colFactorMatrix(matrix_char *a,matrix_char *c);
void matrixInverse(matrix_char *a,matrix_char *c);
#endif //SIMMATCHAR_H_
