#ifndef SIMMATTEMP_H_
#define SIMMATTEMP_H_
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
typedef int element;
typedef unsigned short usint;

typedef struct{
	usint lenght;
	element *data;
} vector_temp;

typedef struct{
	usint row;
	usint col;
	element **data;
} matrix_temp;

vector_temp 	    new_vector_temp(usint size);
matrix_temp       new_matrix_temp(usint row,usint col);


void delete_vector_temp(vector_temp *rhs);
void delete_matrix_temp(matrix_temp *rhs);

void initial_vector_temp(vector_temp* rhs,SetValue set);
void initial_matrix_temp(matrix_temp* rhs,SetValue set);

int supervise_matrix_temp(matrix_temp *rhs);
int supervise_vector_temp(vector_temp *rhs);

void print_vector_temp(vector_temp *rhs,int option);
void print_matrix_temp(matrix_temp *rhs,int option);

/* operation */
int multiply_v_m_temp(vector_temp *rhs,matrix_temp *lhs,matrix_temp *res);
int multiply_vt_m_temp(vector_temp *rhs,matrix_temp *lhs,matrix_temp *res);
int multiply_v_mt_temp(vector_temp *rhs,matrix_temp *lhs,matrix_temp *res);
int multiply_m_v_temp(matrix_temp *rhs,vector_temp *lhs,vector_temp *res);
int multiply_mt_v_temp(matrix_temp *rhs,vector_temp *lhs,vector_temp *res);
int multiply_m_vt_temp(matrix_temp *rhs,vector_temp *lhs,matrix_temp *res);
int multiply_m_m_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res);
int multiply_mt_m_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res);
int multiply_m_mt_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res);
int multiply_v_vt_temp(vector_temp *rhs,vector_temp *lhs,matrix_temp *res);
int multiply_vt_v_temp(vector_temp *rhs,vector_temp *lhs,int *res);//dot product

int dotmultiply_v_temp(vector_temp *rhs,vector_temp *lhs,vector_temp *res);
int dotmultiply_m_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res);
int scalarmultiply_v_temp(vector_temp *rhs,element *lhs,vector_temp *res);
int scalarmultiply_m_temp(matrix_temp *rhs,element *lhs,matrix_temp *res); 
int plus_v_temp(vector_temp *rhs,vector_temp *lhs,vector_temp *res);
int plus_m_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res);
int minus_v_temp(vector_temp *rhs,vector_temp *lhs,vector_temp *res);
int minus_m_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res);
void copy_v_temp(vector_temp *rhs,vector_temp *lhs);
void copy_m_temp(matrix_temp *rhs,matrix_temp *lhs);
void swap_v_temp(vector_temp *rhs,vector_temp *lhs);
void swap_m_temp(matrix_temp *rhs,matrix_temp *lhs);
void minorMtemp(matrix_temp *rhs,int row,int col);
void cutRowMtemp(matrix_temp *rhs,int row);
void swapRowMtemp(matrix_temp *rhs,int row1,int row2);
int compareEqual_v_temp(vector_temp *rhs,vector_temp *lhs);
int compareEqual_m_temp(matrix_temp *rhs,matrix_temp *lhs);
vector_temp 		rowMatrix2Vectortemp(matrix_temp *rhs,int index);

#endif //SIMMATTEMP_H_
