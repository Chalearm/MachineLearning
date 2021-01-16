#ifndef SIMMATINT_H_
#define SIMMATINT_H_
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
typedef unsigned short usint;

typedef struct{
    usint lenght;
    int *data;
} vector_int;

typedef struct{
    usint row;
    usint col;
    int **data;
} matrix_int;

vector_int     new_vector_int(usint size);
matrix_int       new_matrix_int(usint row,usint col);


void delete_vector_int(vector_int *rhs);
void delete_matrix_int(matrix_int *rhs);

void initial_vector_int(vector_int* rhs,SetValue set);
void initial_matrix_int(matrix_int* rhs,SetValue set);

int supervise_matrix_int(matrix_int *rhs);
int supervise_vector_int(vector_int *rhs);

void print_vector_int(vector_int *rhs,int option);
void print_matrix_int(matrix_int *rhs,int option);

/* operation */
int multiply_v_m_int(vector_int *rhs,matrix_int *lhs,matrix_int *res);
int multiply_vt_m_int(vector_int *rhs,matrix_int *lhs,matrix_int *res);
int multiply_v_mt_int(vector_int *rhs,matrix_int *lhs,matrix_int *res);
int multiply_m_v_int(matrix_int *rhs,vector_int *lhs,vector_int *res);
int multiply_mt_v_int(matrix_int *rhs,vector_int *lhs,vector_int *res);
int multiply_m_vt_int(matrix_int *rhs,vector_int *lhs,matrix_int *res);
int multiply_m_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res);
int multiply_mt_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res);
int multiply_m_mt_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res);
int multiply_v_vt_int(vector_int *rhs,vector_int *lhs,matrix_int *res);
int multiply_vt_v_int(vector_int *rhs,vector_int *lhs,int *res);//dot product

int dotmultiply_v_int(vector_int *rhs,vector_int *lhs,vector_int *res);
int dotmultiply_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res);
int scalarmultiply_v_int(vector_int *rhs,int *lhs,vector_int *res);
int scalarmultiply_m_int(matrix_int *rhs,int *lhs,matrix_int *res); 
int plus_v_int(vector_int *rhs,vector_int *lhs,vector_int *res);
int plus_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res);
int minus_v_int(vector_int *rhs,vector_int *lhs,vector_int *res);
int minus_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res);
void copy_v_int(vector_int *rhs,vector_int *lhs);
void copy_m_int(matrix_int *rhs,matrix_int *lhs);
void swap_v_int(vector_int *rhs,vector_int *lhs);
void swap_m_int(matrix_int *rhs,matrix_int *lhs);
void minorMint(matrix_int *rhs,int row,int col);
void cutRowMint(matrix_int *rhs,int row);
void swapRowMint(matrix_int *rhs,int row1,int row2);
int compareEqual_v_int(vector_int *rhs,vector_int *lhs);
int compareEqual_m_int(matrix_int *rhs,matrix_int *lhs);
vector_int rowMatrix2Vectorint(matrix_int *rhs,int index);
int determinantInt(matrix_int *a);
void colFactorMatrixInt(matrix_int *a,matrix_int *c);
void matrixInverseInt(matrix_int *a,matrix_int *c);
#endif /*SIMMATINT_H_*/
