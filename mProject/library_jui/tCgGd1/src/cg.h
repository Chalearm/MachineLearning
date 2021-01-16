/********************************************************************/
/*
      FILE        :   main.c
      Name        :   Chalearm Saelim
      Date        :   22 November 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to implement the core of the conjugate gradient method


      Description :  as Purpose statement
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        22-11-2017    csaelim    First draft 
*/
/*******************************************************************/
#ifndef CG_H
#define CG_H

#define MAX_NPROCS 100

void axpy(double *dest, double alpha, double *x, double *y, int n);

double ddot(double *x, double *y, int n);

int precond_cg(void (*matvec)(double *Ax, double **Adata, double *x, int n),
               void (*psolve)(double *Minvx, double *Mdata, double *x, int n),
               double **Adata, double *Mdata, double *b,double *x, double rtol, int n,int maxiter);
            
void dummy_psolve(double *Minvx,void *Mdata, double *x, int n);

#endif /* CG_H */