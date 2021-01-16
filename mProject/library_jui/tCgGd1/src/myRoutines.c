/********************************************************************/
/*
      FILE        :   myRoutines.c
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "myRoutines.h"

#ifndef min
#define min(a,b) ((a) < (b) ? (a):(b))
#endif
#ifndef max
#define max(a,b) ((a) > (b) ? (a) :(b))
#endif
/*
    Multiply a table on a vector
*/

void matvec(double *Ax, double **Adata, double *x, int n)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < n;i++)
    {
        Ax[i] = 0;
        for(j = 0 ;j < n ;j++)
        {
            Ax[i] += Adata[i][j]*x[j];
        }
    }
}
/*
    Creating a Jacobi preconditioner - zeros are not saved
*/

void jacobi_precond(double *M, double **Adata, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        M[i] += Adata[i][i];
    }
}

/*
    Applying the Jacobi preconditioner
*/

void psolve(double *Minvx, double *Mdata, double *x, int n)
{
    int i = 0;
    for ( i = 0;i < n ;i++)
    {
        Minvx[i] = 1.0/Mdata[i]*x[i];
    }
}

void generate_randsys(double **A, double *x, double *b, int n)
{
    int i = 0;
    int j = 0;
    generate_randmat(A, n);
    generate_randvec(x, n);
    for (i = 0; i < n ;i++)
    {
        for(j = 0;j < n ; j++)
        {
            b[i] += A[i][j]*x[j];
        }
    }
}

void generate_randvec(double *vec, int n)
{
    int i = 0;
    for (i = 0; i < n ; i++)
    {
        vec[i] = (double)random()/(RAND_MAX+1.0);
    }
}

void generate_randmat(double **mat, int n)
{
    int i = 0;
    int j = 0;
    int k = 0;
    double **randmat = NULL;
    double **mattrans = NULL;
    randmat = malloc(n*sizeof(double*));
    if (randmat == NULL)
    {
        printf("randmat -- Out of memory\n");
    }
    else
    {
        randmat[0] = malloc(n * n * sizeof(double));
        for( i = 1; i < n ;i++)
        {
            randmat[i] = randmat[0] +i * n;
            
        }
        for( i = 0; i < n ;i++)
        {
            for(j = 0; j < n; j++)
            {
                randmat[i][j] = (double)random()/(RAND_MAX+1.0);
            }
        }
    
    }
    mattrans = malloc(n * sizeof(double*));
    if ( mattrans == NULL)
    {
        printf("mattrans--Out of memory");
    }
    else
    {
        mattrans[0] = malloc(n * n *sizeof(double));
        for( i = 1; i < n; i++)
        {
            mattrans[i] = mattrans[0] + i * n;
        }
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                mattrans[i][j] = randmat[j][i];
            }
        }
    }
    if ((mattrans != NULL) && (randmat != NULL))
    {
        for( i = 0;i < n;i++)
        {
            for(j = 0;j < n;j++)
            {
                for(k = 0;k < n;k++)
                {
                    mat[i][k] += mattrans[i][j]*randmat[j][k];
                }
            }
        }
    }
    else
    {
        /* do nothing */
    }
    if (randmat != NULL)
    {
        if (randmat[0] != NULL)
        {
            free(randmat[0]);
        }
        else
        {
            /* do nothing */
        }
        free(randmat);
        randmat = NULL;
    }
    else
    {
        /* do nothing */
    }
    if (mattrans != NULL)
    {
        if (mattrans[0] != NULL)
        {
            free(mattrans[0]);
        }
        else
        {
            /* do nothing */
        }
        free(mattrans);
        mattrans = NULL;
    }
    else
    {
        /* do nothing */
    }
} 