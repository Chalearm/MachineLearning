/********************************************************************/
/*
      FILE        :   myRoutines.h
      Name        :   Chalearm Saelim
      Date        :   22 November 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to implement the core of the conjugate gradient method


      Description :  as Purpose statement
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        23-11-2017    csaelim    First draft 
*/
/*******************************************************************/
#ifndef MYROUTINES_H
#define MYROUTINES_H

void matvec(double *Ax, double **Adata, double *x, int n);

void jacobi_precond(double *M, double **Adata, int n);

void psolve(double *Minvx, double *Mdata, double *x, int n);

void generate_randsys(double **A, double *x, double *b, int n);

void generate_randvec(double *vec, int n);

void generate_randmat(double **mat, int n);


#endif /* CSR_PROBLEM_H */