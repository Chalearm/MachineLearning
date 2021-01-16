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

typedef struct{
    unsigned int lenght;
    double *data;
} vector_double;

typedef struct{
    unsigned int row;
    unsigned int col;
    double **data;
} matrix_double;

vector_double       new_vector_double(unsigned int size);
matrix_double       new_matrix_double(unsigned int row,unsigned int col);


void delete_vector_double(vector_double *rhs);
void delete_matrix_double(matrix_double *rhs);

void initial_vector_double(vector_double* rhs,SetValue set);
void initial_matrix_double(matrix_double* rhs,SetValue set);

int supervise_matrix_double(const matrix_double *rhs);
int supervise_vector_double(const vector_double *rhs);

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
int multiply_vt_v_double(const vector_double *rhs,const vector_double *lhs,double *res);//dot product

int dotmultiply_v_double(vector_double *rhs,vector_double *lhs,vector_double *res);
int dotmultiply_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);
int scalarmultiply_v_double(vector_double *rhs,double *lhs,vector_double *res);
int scalarmultiply_m_double(matrix_double *rhs,double *lhs,matrix_double *res); 
int plus_v_double(vector_double *rhs,vector_double *lhs,vector_double *res);
int plus_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);
int minus_v_double(vector_double *rhs,vector_double *lhs,vector_double *res);
int minus_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res);
void copy_v_double(vector_double *rhs,vector_double *lhs);
void copy_m_double(matrix_double *rhs,matrix_double *lhs);
void swap_v_double(vector_double *rhs,vector_double *lhs);
void swap_m_double(matrix_double *rhs,matrix_double *lhs);
void minorMdouble(matrix_double *rhs,int row,int col);
matrix_double concatColMatrix(matrix_double *rhs,matrix_double *lhs);
void rowOperationM(matrix_double *rhs,matrix_double *ret,unsigned int r1,double fact1,unsigned int r2,double fact2,unsigned int rowRet);
/*
opt = 0 --> diagonal matrix
opt = 1 --> upper triangular matrix
opt = 2 --> lower triangular matrix
*/
int GaussElimination(matrix_double *rhs,matrix_double *retm,const int numRowVars,int opt);
void cutRowMdouble(matrix_double *rhs,int row);
void swapRowMdouble(matrix_double *rhs,int row1,int row2);
int compareEqual_v_double(vector_double *rhs,vector_double *lhs);
int compareEqual_m_double(matrix_double *rhs,matrix_double *lhs);
vector_double rowMatrix2Vectordouble(matrix_double *rhs,int index);
double determinant(matrix_double *a);
double determinant2(matrix_double *a,matrix_double *buff);
void colFactorMatrix(matrix_double *a,matrix_double *c);
void matrixInverse(matrix_double *a,matrix_double *c);
void matrixInverse2(matrix_double *a,matrix_double *c);

/* safe vector*/
/*
gt = get
st = set
sf = safe
dg = debug
df = default
*/
/*debug mode */
double gtsfdg(vector_double *rhs,int index,int line,const char *filename);
int stsfdg(vector_double *rhs,int index,double val,int line,const char *filename);
int stsfdfdg(vector_double *rhs,int index,double val,int line,const char *filename);
/* release mode*/
void stsf(vector_double *rhs,int index,double val);
void stsfdf(vector_double *rhs,int index,double val);
#endif //SIMMATDOUBLE_H_
