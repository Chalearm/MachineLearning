#ifndef SIMPLEMATRIX_H_
#define SIMPLEMATRIX_H_
#include <malloc.h>
#include <stdlib.h>
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
	char set;
	double max;
	double min;
} SetValue;

typedef struct{
	usint lenght;
	int *data;
} vector_int;

typedef struct{
	usint lenght;
	double *data;
} vector_double;

typedef struct{
	usint lenght;
	char *data;
} vector_char;

typedef struct{
	usint lenght;
	float *data;
} vector_float;

typedef struct{
	usint row;
	usint col;
	int **data;
} matrix_int;

typedef struct{
	usint row;
	usint col;
	double **data;
} matrix_double;

typedef struct{
	usint row;
	usint col;
	char **data;
} matrix_char;

typedef struct{
	usint row;
	usint col;
	float **data;
} matrix_float;

vector_int 	    new_vector_int(usint size);
vector_double 	new_vector_double(usint size);
vector_char 	new_vector_char(usint size);
vector_float 	new_vector_float(usint size);

matrix_int	new_matrix_int(usint row,usint col);
matrix_double	new_matrix_double(usint row,usint col);
matrix_float	new_matrix_float(usint row,usint col);
matrix_char	new_matrix_char(usint row,usint col);

void delete_vector_int(vector_int *rhs);
void delete_vector_char(vector_char *rhs);
void delete_vector_float(vector_float *rhs);
void delete_vector_double(vector_double *rhs);

void delete_matrix_int(matrix_int *rhs);
void delete_matrix_double(matrix_double *rhs);
void delete_matrix_float(matrix_float *rhs);
void delete_matrix_char(matrix_char *rhs);

void initial_vector_int(vector_int* rhs,SetValue set);
void initial_vector_double(vector_double* rhs,SetValue set);
void initial_vector_char(vector_char* rhs,SetValue set);
void initial_vector_float(vector_float* rh,SetValue set);

void initial_matrix_int(matrix_int* rhs,SetValue set);
void initial_matrix_double(matrix_double* rhs,SetValue set);
void initial_matrix_char(matrix_char* rhs,SetValue set);
void initial_matrix_float(matrix_float* rhs,SetValue set);

int supervise_matrix_int(matrix_int *rhs);
int supervise_matrix_char(matrix_char *rhs);
int supervise_matrix_double(matrix_double *rhs);
int supervise_matrix_float(matrix_float *rhs);
int supervise_vector_int(vector_int *rhs);
int supervise_vector_char(vector_char *rhs);
int supervise_vector_double(vector_double *rhs);
int supervise_vector_float(vector_float *rhs);

void print_vector_int(vector_int *rhs,int option);
void print_vector_float(vector_float *rhs,int option);
void print_vector_double(vector_double *rhs,int option);
void print_vector_char(vector_char *rhs,int option);
void print_matrix_int(matrix_int *rhs,int option);
void print_matrix_float(matrix_float *rhs,int option);
void print_matrix_double(matrix_double *rhs,int option );
void print_matrix_char(matrix_char *rhs,int option);

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
int multiply_vt_v_double(vector_double *rhs,vector_double *lhs,double *res);//dot product
 
int multiply_v_m_float(vector_float *rhs,matrix_float *lhs,matrix_float *res);
int multiply_vt_m_float(vector_float *rhs,matrix_float *lhs,matrix_float *res);
int multiply_v_mt_float(vector_float *rhs,matrix_float *lhs,matrix_float *res);
int multiply_m_v_float(matrix_float *rhs,vector_float *lhs,vector_float *res);
int multiply_mt_v_float(matrix_float *rhs,vector_float *lhs,vector_float *res);
int multiply_m_vt_float(matrix_float *rhs,vector_float *lhs,matrix_float *res);
int multiply_m_m_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res);
int multiply_mt_m_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res);
int multiply_m_mt_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res);
int multiply_v_vt_float(vector_float *rhs,vector_float *lhs,matrix_float *res);
int multiply_vt_v_float(vector_float *rhs,vector_float *lhs,float *res);//dot product
 
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
int multiply_vt_v_char(vector_char *rhs,vector_char *lhs,char *res);//dotproduct

int dotmultiply_v_int(vector_int *rhs,vector_int *lhs,vector_int *res);
int dotmultiply_v_double(vector_double *rhs,vector_double *lhs,vector_double *res);
int dotmultiply_v_char(vector_char *rhs,vector_char *lhs,vector_char *res);
int dotmultiply_v_float(vector_float *rhs,vector_float *lhs,vector_float *res);

int dotmultiply_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res);
int dotmultiply_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);
int dotmultiply_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res);
int dotmultiply_m_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res);

int scalarmultiply_v_int(vector_int *rhs,int *lhs,vector_int *res); 
int scalarmultiply_v_char(vector_char *rhs,char *lhs,vector_char *res); 
int scalarmultiply_v_float(vector_float *rhs,float *lhs,vector_float *res); 
int scalarmultiply_v_double(vector_double *rhs,double *lhs,vector_double *res); 
int scalarmultiply_m_int(matrix_int *rhs,int *lhs,matrix_int *res); 
int scalarmultiply_m_char(matrix_char *rhs,char *lhs,matrix_char *res); 
int scalarmultiply_m_float(matrix_float *rhs,float *lhs,matrix_float *res); 
int scalarmultiply_m_double(matrix_double *rhs,double *lhs,matrix_double *res); 

int plus_v_int(vector_int *rhs,vector_int *lhs,vector_int *res);
int plus_v_char(vector_char *rhs,vector_char *lhs,vector_char *res);
int plus_v_float(vector_float *rhs,vector_float *lhs,vector_float *res);
int plus_v_double(vector_double *rhs,vector_double *lhs,vector_double *res);
int plus_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res);
int plus_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res);
int plus_m_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res);
int plus_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);
int minus_v_int(vector_int *rhs,vector_int *lhs,vector_int *res);
int minus_v_char(vector_char *rhs,vector_char *lhs,vector_char *res);
int minus_v_float(vector_float *rhs,vector_float *lhs,vector_float *res);
int minus_v_double(vector_double *rhs,vector_double *lhs,vector_double *res);
int minus_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res);
int minus_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res);
int minus_m_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res);
int minus_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);

void copy_v_int(vector_int *rhs,vector_int *lhs);
void copy_v_char(vector_char *rhs,vector_char *lhs);
void copy_v_float(vector_float *rhs,vector_float *lhs);
void copy_v_double(vector_double *rhs,vector_double *lhs);

void copy_m_int(matrix_int *rhs,matrix_int *lhs);
void copy_m_char(matrix_char *rhs,matrix_char *lhs);
void copy_m_float(matrix_float *rhs,matrix_float *lhs);
void copy_m_double(matrix_double *rhs,matrix_double *lhs);

void swap_v_int(vector_int *rhs,vector_int *lhs);
void swap_v_char(vector_char *rhs,vector_char *lhs);
void swap_v_float(vector_float *rhs,vector_float *lhs);
void swap_v_double(vector_double *rhs,vector_double *lhs);

void swap_m_int(matrix_int *rhs,matrix_int *lhs);
void swap_m_char(matrix_char *rhs,matrix_char *lhs);
void swap_m_float(matrix_float *rhs,matrix_float *lhs);
void swap_m_double(matrix_double *rhs,matrix_double *lhs);

void minorMchar(matrix_char *rhs,int row,int col);
void minorMint(matrix_int *rhs,int row,int col);
void minorMfloat(matrix_float *rhs,int row,int col);
void minorMdouble(matrix_double *rhs,int row,int col);

void cutRowMchar(matrix_char *rhs,int row);
void cutRowMint(matrix_int *rhs,int row);
void cutRowMfloat(matrix_float *rhs,int row);

void swapRowMint(matrix_int *rhs,int row1,int row2);
void swapRowMchar(matrix_char *rhs,int row1,int row2);
void swapRowMfloat(matrix_float *rhs,int row1,int row2);
void swapRowMdouble(matrix_double *rhs,int row1,int row2);

int compareEqual_v_int(vector_int *rhs,vector_int *lhs);
int compareEqual_v_char(vector_char *rhs,vector_char *lhs);
int compareEqual_v_float(vector_float *rhs,vector_float *lhs);
int compareEqual_v_double(vector_double *rhs,vector_double *lhs);

int compareEqual_m_int(matrix_int *rhs,matrix_int *lhs);
int compareEqual_m_char(matrix_char *rhs,matrix_char *lhs);
int compareEqual_m_float(matrix_float *rhs,matrix_float *lhs);
int compareEqual_m_double(matrix_double *rhs,matrix_double *lhs);

vector_int 		rowMatrix2VectorInt(matrix_int *rhs,int index);
vector_char 	rowMatrix2Vectorchar(matrix_char *rhs,int index);
vector_float 	rowMatrix2Vectorfloat(matrix_float *rhs,int index);
vector_double 	rowMatrix2Vectordouble(matrix_double *rhs,int index);
#endif //SIMPLEMATRIX_H__
