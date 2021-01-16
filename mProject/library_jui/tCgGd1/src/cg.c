/********************************************************************/
/*
      FILE        :   cg.c
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cg.h" 

void axpy(double *dest, double alpha, double *x, double *y, int n)
{
    int i = 0;
    for (i = 0; i < n;i++)
    {
        dest[i] = alpha * x[i] + y[i];
    }
}

double ddot(double *x, double *y, int n)
{
    int i = 0;
    double final_sum = 0;
    for (i = 0; i < n;i++)
    {
        final_sum += x[i]*y[i];
    }
    return final_sum;
}

/*
    Solve Ax=b using preconditioned conjugate-gradient
    Arguments
    matvec (Ax,Adata,x,n) - Adata*x in Ax
    psolve (Minvx,Mdata,x,n) - Apply the preconditioner
    Adata - The system table
    Mdata - The preconditioner
    b - Right member of the system
    x - Result
    rtol - Tolerance to the rest (||r||/||b||)
    n - system Size
    maxiter - Maximum number of reps
    
    Returns : Number of reps for successful execution, -1 in case of failure
*/
int precond_cg(void (*matvec)(double *Ax, double **Adata, double *x, int n),
               void (*psolve)(double *Minvx, double *Mdata, double *x, int n),
               double **Adata, double *Mdata, double *b,double *x, double rtol, int n,int maxiter)
{
    const int nbytes = n * sizeof(double);
    double bnorm2 = 0.0;        /*  ||b||^2 */
    double rnorm2 = 0.0;        /*  Balance left in the square */
    double rz = 0.0;            /*  r * z for 2 consecutive iterations */
    double rzold = 0.0;           
    double alpha = 0.0; 
    double beta = 0.0;
    
    
    double *s = 0;   /*  search direction */
    double *r = 0;   /*  Rest of */
    double *z = 0;   /*  Temporary vector*/
    
    int i = 0;         /*  Current repeat */
    
    s = (double*)malloc(nbytes);
    r = (double*)malloc(nbytes);
    z = (double*)malloc(nbytes);
    
    bnorm2 = ddot(b,b,n);
    
    memset(x, 0, nbytes);   /*    initialize a solution */
    memcpy(r, b, nbytes);   /*    and the remainder - r0 = b- A* x0(x0 = 0) */
    
    psolve(z, Mdata, r, n);  /*    Apply the preconditioner -z0 = (M at -1)* r0    */
    
    memcpy(s, z, nbytes);    /*    search direction initialization -p0 = z0  */
    
    /*   Initialize rz and rnorm2  */
    rz     = ddot(r, z, n);
    rnorm2 = ddot(r, r, n);
    
    printf("rz=%2.15f, aplha=%2.15f, rnorm=%2.15f, bnorm:%f\n",rz,alpha,rnorm2,bnorm2);
    
    for (i = 0; i < maxiter ; i++)
    {
        printf("Repeat# %d \n",i);
        
        matvec(z, Adata, s, n);  /*  z:= A*pk*/
        
        /*   Ddat */
        alpha = rz/ddot(s,z,n);   /*  ak = rkT*zk/pkT*A*pk  */
        axpy(x, alpha, s, x, n); /*   xk+1 = xk + ak*pk  */
        axpy(r, -alpha, z, r, n); /*   rk+1 = rk - ak*A*pk  */
        
        psolve(z, Mdata, r, n); /* zk+1 = (M in -1)* rk+1 */
        rzold = rz;
    
        rz = ddot(r, z, n);     /*  rTk+1*zK+1*/
        beta = -rz/ rzold;     /* 6= rTk+1*zk+1/rTk*zk */
        axpy(s, -beta, s, z, n);   /*  pk+1 = zk+1+6k*pk */
        
        printf("(%d)rz=%2.15f, alpha=%2.15f, rnorm=%2.15f\n",i,rz,alpha,rnorm2);
        
        /* check error */
        rnorm2 = ddot(r, r, n);
        if (rnorm2 <= bnorm2 * rtol * rtol)
        {
            break;
        }
        else
        {
            /* do nothing */
        }
    }
    free(z);
    free(r);
    free(s);
    if (i >= maxiter)
    {
        return -1;
    }
    else
    {
        return i;
    }
}

            
void dummy_psolve(double *Minvx,void *Mdata, double *x, int n);

 