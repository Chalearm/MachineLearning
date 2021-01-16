/********************************************************************/
/*
      FILE        :   main.c
      Name        :   Chalearm Saelim
      Date        :   22 November 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   To study the Conjugate gradient method


      Description :  This is the main program of the Conjugate gradient method
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        22-11-2017    csaelim    First draft 
*/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "basicVarArea.h"
#include "cg.h"
#include "myRoutines.h"

int main(int argc, char **argv)
{
    int ret = 1;
    double **Adata = NULL; /* the system table */
    double *Mdata = NULL;  /* the preconditioner */
    double *x = NULL; /* the system solution (generated for the random system)*/
    double *cg_x = NULL; /*  the system solution resulting from cg */
    double *b = NULL;    /*  the right system member */
    
    int i = 0;

    clock_t time1,timeGen,timeExec;
    int n = 1000;  /* the size of the system */
    int maxiter = 10000;   /*  the max iterations before returning */
    double rtol = 1e-8;
    double abs_error = 0.0;
    
    Adata = new2DimDoubleArea(n,n,&ret);
    Mdata = newDoubleArea(n,&ret);
    x = newDoubleArea(n,&ret);
    cg_x = newDoubleArea(n,&ret);
    b = newDoubleArea(n,&ret);
    initial2DDoubleArea(Adata,0.0,n,n);
    initialDoubleArea(Mdata,0.0,n);
    initialDoubleArea(x,0.0,n);
    initialDoubleArea(cg_x,0.0,n);
    initialDoubleArea(b,0.0,n);
    
    time1 = clock();
    generate_randsys(Adata, x, b, n);
    timeGen = clock() - time1;

    
    printf("Befo Jacobi :");prntVDou(Mdata,n);printf("\n");
    jacobi_precond(Mdata, Adata, n);
    printf("Jacobi      :");prntVDou(Mdata,n);printf("\n");
    time1 = clock();
    
    int iter = precond_cg(matvec, psolve, Adata, Mdata,b, cg_x, rtol, n, maxiter);
    timeExec = clock() - time1;
    
    /* find absolute error */
    for (i = 0 ; i < n ;i++)
    {
        if(fabs(x[i] - cg_x[i]) > abs_error)
        {
            abs_error = fabs(x[i] - cg_x[i]);
        }
        else
        {
            /* do nothing */
        }
        
    }

    
    
    printf("Execution time: %lf \n",((double)timeExec)/CLOCKS_PER_SEC);
    printf("Time to create a random system :%lf sec\n",((double)timeGen)/CLOCKS_PER_SEC);
    printf("Repeat:%d, Abs_error = %lf\n",iter,abs_error);
    /*
    void prntVDou(const double *dat,int n);
void prntMDou(double **dat,int m,int n);
    */
    printf("Jaco:");prntVDou(Mdata,n);printf("\n");
    printf("x   :");prntVDou(x,n);printf("\n");
    printf("A   :\n");prntMDou(Adata,n,n);printf("\n");
    printf("b   :");prntVDou(b,n);printf("\n");
    printf("xcg :");prntVDou(cg_x,n);printf("\n");
    /* free memory */
    delDoubleArea((void*)&Mdata);
    delDoubleArea((void*)&x);
    delDoubleArea((void*)&cg_x);
    delDoubleArea((void*)&b);
    del2DimDoubleArea((void*)&Adata,n);
    return 0;
}