/********************************************************************/
/*
      FILE        :   basicVarArea.h
      Name        :   Chalearm Saelim
      Date        :   17 October 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Provide method for managing the double-type variable allocation


      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        17-10-2017    csaelim    First draft 
*/
/*******************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "basicVarArea.h"

void minusVectorDoub(const double *va,const double *vb,double *ret,int numDim)
{
    int index = 0;
    if ( (va != NULL) && ( vb != NULL) && (ret != NULL) && (numDim > 0 ))
    {
        for ( index = 0;index < numDim;index++)
        {
            ret[index] = va[index] - vb[index];
        }
    }
    else
    {
        printf("Error va:%p, vb:%p, ret:%p numDim:%d , ln:%d file:%s \n",va,vb,ret,numDim,__LINE__,__FILE__);
    }
}
void plusVectorDoub(const double *va,const double *vb,double *ret,int numDim)
{
    int index = 0;
    if ( (va != NULL) && ( vb != NULL) && (ret != NULL) && (numDim > 0 ))
    {
        for ( index = 0;index < numDim;index++)
        {
            ret[index] = va[index] + vb[index];
        }
    }
    else
    {
        printf("Error va:%p, vb:%p, ret:%p numDim:%d , ln:%d file:%s \n",va,vb,ret,numDim,__LINE__,__FILE__);
    }
}
void scaleVectorDoub(const double *va,const double val,double *ret,int numDim)
{
    int index = 0;
    if ( (va != NULL) && (ret != NULL) && (numDim > 0 ))
    {
        for ( index = 0;index < numDim;index++)
        {
            ret[index] = va[index]*val;
        }
    }
    else
    {
        printf("Error va:%p,  ret:%p numDim:%d , ln:%d file:%s \n",va,ret,numDim,__LINE__,__FILE__);
    }
}

double linearKernelFn_2(const double *va,const double *vb,int numDim)
{
    double ret = 0.0;
    int index = 0;
    if ( (va != NULL) && (vb != NULL) && (numDim > 0) )
    {
        for (index = 0;index < numDim ;index++)
        {
            ret = va[index]*vb[index] + ret;
        }
    }
    else
    {
        printf(" Error in linearKernelFn2, va:%p,numDim:%d ln:%d, file:%s\n",va,numDim,__LINE__,__FILE__);
    }
    return ret;
}

double diffVAbsoluateValDoub(const double *va,const double *vb,int numDim)
{
    double ret = 0.0;
    int index = 0;
    if ( (va != NULL) && (vb != NULL) && (numDim > 0) )
    {
        for (index = 0;index < numDim ;index++)
        {
            ret = pow(va[index]- vb[index],2.0) + ret;
        }
        ret = pow(ret,0.5);
    }
    else
    {
        printf(" Error in diffVAbsoluateValDoub, va:%p,numDim:%d ln:%d, file:%s\n",va,numDim,__LINE__,__FILE__);
    }
    return ret;
}
double plusVAbsoluateValDoub(const double *va,const double *vb,int numDim)
{
    double ret = 0.0;
    int index = 0;
    if ( (va != NULL) && (vb != NULL) && (numDim > 0) )
    {
        for (index = 0;index < numDim ;index++)
        {
            ret = pow(va[index] + vb[index],2.0) + ret;
        }
        ret = pow(ret,0.5);
    }
    else
    {
        printf(" Error in diffVAbsoluateValDoub, va:%p,numDim:%d ln:%d, file:%s\n",va,numDim,__LINE__,__FILE__);
    }
    return ret;
}

double absf(double a)
{
    double ret = 0.0;
    if(a<0)
    {
        ret = -1*a;
    }
    else
    {
        ret = a;
    }
    return ret;
}

double maxVal(double a,double b)
{
    double ret = a;
    if(a<b)
    {
        ret = b;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

double minVal(double a,double b)
{
    double ret = a;
    if(a>b)
    {
        ret = b;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
/* ------ utility  A group*/

/*
    isln = 0 : no new line
           1 : new line
*/
void printDou(const char *str,const double val,int isln)
{
    if (str != NULL)
    {
        printf("%s",str);
    }
    else
    {
        /* do nothing */
    }
    printf("%f",val);
    if (isln == 1)
    {
        printf("\n");
    }
    else
    {
        /* do nothing */
    }
    
}
void printInt(const char *str,const int val,int isln)
{
    if (str != NULL)
    {
        printf("%s",str);
    }
    else
    {
        /* do nothing */
    }
    printf("%d",val);
    if (isln == 1)
    {
        printf("\n");
    }
    else
    {
        /* do nothing */
    }
}

void printVoidSt(const char *str,const void *val,int isln)
{
    if (str != NULL)
    {
        printf("%s",str);
    }
    else
    {
        /* do nothing */
    }
    printf("%p",val);
    if (isln == 1)
    {
        printf("\n");
    }
    else
    {
        /* do nothing */
    }
}
void printLnAndFile(const char *str,const int ln,int isln)
{
    printf("ln:%d ,",ln);
    if (str != NULL)
    {
        printf(" fl:%s",str);
    }
    else
    {
        /* do nothing */
    } 
    if (isln == 1)
    {
        printf("\n");
    }
    else
    {
        /* do nothing */
    }
}

void prntVDou(const double *dat,int n)
{
    int index = 0;
    printf("[");
    for (index = 0;index < n;index++)
    {
        printf("%f ",dat[index]);
    }
    printf("]");
}

void prntMDou(double **dat,int m,int n)
{
    int index1 = 0;
    int index2 = 0;
    for (index1 = 0; index1 < m;index1++)
    {
        for(index2 = 0;index2 < n;index2++)
        {
            printf("%f ",dat[index1][index2]);
        }
        printf("\n");
    } 
}

double* newDoubleArea(int size,int *ret)
{
    void *pTmp = NULL;
    if ((ret != NULL) && ( size >= 0))
    {
        pTmp = malloc(sizeof(double)*size);
        if ((pTmp == NULL) && (size != 0))
        {
            *ret = 0;
        }
        else 
        {
            /* do nothing */
        }
    }
    else if (ret != NULL)
    {
        *ret = 0;
        printInt("Error Cannot allocate space ,size:",size,0);
        printLnAndFile(__FILE__,__LINE__,1);
    }
    else
    {
        printVoidSt("Error ret is",ret,0);
        printLnAndFile(__FILE__,__LINE__,1);
    }
    return (double*)pTmp;
}

double** newPDoubleDArea(int size,int *ret)
{
    void *pTmp = NULL;
    if ((ret != NULL) && ( size >= 0))
    {
        pTmp = malloc(sizeof(double*)*size);
        if ((size != 0) && (pTmp == NULL))
        {
            *ret = 0;
        }
        else
        {
            /* do nothing */
        }
    }
    else if (ret != NULL)
    {
        *ret = 0;
        printInt("Error Cannot allocate space ,size:",size,0);
        printLnAndFile(__FILE__,__LINE__,1);
    }
    else
    {
        printVoidSt("Error ret is",ret,0);
        printLnAndFile(__FILE__,__LINE__,1);
    }
    return (double**)pTmp;
}

double** new2DimDoubleArea(int size,int dmi,int *ret)
{
    double **pTmp = newPDoubleDArea(size,ret);
    int index = 0;
    if ((ret != NULL) && ( pTmp != NULL))
    {
        for (index = 0;index < size;index++)
        {
            pTmp[index] = newDoubleArea(dmi,ret);
        }
        
    }
    else if ( (pTmp == NULL) && (size != 0 ))
    {
        *ret = 0;
    }
    else if (ret != NULL)
    {
        *ret = 0;
        printf("Error Cannot allocate space (size:%d), ln:%d, file:%s \n",size,__LINE__,__FILE__);
    }
    else
    {
        printf("Error ret is null, ln:%d, file:%s \n",__LINE__,__FILE__);
    }
    return (double**)pTmp;
}

void initialDoubleArea(double *dat,double val,int num)

{
    int index = 0;
    if ( (dat != NULL) && (num > 0))
    {
        for (index = 0;index < num;index++)
        {
            dat[index] = val;
        }
    }
    else
    {
        printf("Error dat is null, num:%d, ln:%d, file:%s \n",num,__LINE__,__FILE__);
    }
}

void initial2DDoubleArea(double **dat,double val,int num,int num2)

{
    int index = 0;
    int index2 = 0;
    if ( (dat != NULL) && (num > 0))
    {
        for (index = 0;index < num;index++)
        {
            for (index2 = 0;index2 < num2;index2++)
            {
                dat[index][index2] = val;
            }
        }
    }
    else
    {
        printf("Error dat is null, num:%d, ln:%d, file:%s \n",num,__LINE__,__FILE__);
    }
}

int delDoubleArea(void **dat)

{
    int ret = 0;
    if (dat != NULL)
    {
        ret = 1;
        if (*dat != NULL)
        {
            free(*dat);
            *dat = NULL;
        }
        else
        {
            /* do nothing */
        }
    }

    else
    {
        printf("Error the pointer is null, ln:%d, File:%s \n",__LINE__,__FILE__);
    }
    return ret;
}
int del2DimDoubleArea(void **dat,int size)
{
    int ret = 1;
    int index = 0;
    void ***dat1 = (void***)dat;
    if ((dat1 != NULL) && (size > 0))
    { 
        for(index = 0;index < size;index++)
        {
            ret = (ret == 1) && delDoubleArea(&((*dat1)[index]));
        }
        if (*dat1 != NULL)
        {
            free(*dat1);
            *dat1 = NULL;
        }
        else
        {
            /* do nothing */
        }
    }
    else if ((dat != NULL)  && (size == 0) )
    {
        ret = delDoubleArea(dat);
    }
    else
    {
        printf("Error the pointer is null, ln:%d, File:%s \n",__LINE__,__FILE__);
    }
    return ret;
}
double randomFn(const double max,const double min)
{
    return min + ((double)rand()/(double)(RAND_MAX)) * (max-min);
}
/*
    opt - bit set
    1 - no max checking
    2 - no min checking
*/ 
double setDoubleInbound(const double max,const double min,const double val,const int option,const int isShowErr)
{
    double tmp = val;
    if ( (max < val) && ((option&0x1)== 0))
    {
        tmp = max;
        if (isShowErr == 1)
        {
            printf("Error in setDoubleInbound Val is greater than MAX : %f > %f , ln:%d, file:%s\n",val,max,__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
    }
    else if ( (min > val) && ((option&0x2)== 0))
    {
        tmp = min;
        if (isShowErr == 1)
        {
            printf("Error in setDoubleInbound Val is leaster than Min : %f < %f , ln:%d, file:%s\n",val,max,__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* do nothing */
    }
    return tmp;
}
/*
    opt - bit set
    1 - no max checking
    2 - no min checking
*/ 
int setIntInbound(const int max,const int min,const int val,const int option,const int isShowErr)
{
    int tmp = val;
    if ( (max < val) && ((option&0x1)== 0))
    {
        tmp = max;
        if (isShowErr == 1)
        {
            printf("Error in setDoubleInbound Val is greater than MAX : %d > %d , ln:%d, file:%s\n",val,max,__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
    }
    else if ( (min > val) && ((option&0x2)== 0))
    {
        tmp = min;
        if (isShowErr == 1)
        {
            printf("Error in setDoubleInbound Val is leaster than Min : %d < %d , ln:%d, file:%s\n",val,max,__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* do nothing */
    }
    return tmp;
} 

/* validatBound */
int vdIntBound(const int max,const int min,const int val)
{
    int ret = 0;
    if ((max <= val) && (min >= val))
    {
        ret = 1;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int vdDoubleBound(const double max,const double min,const double val)
{
    int ret = 0;
    if ((max <= val) && (min >= val))
    {
        ret = 1;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}