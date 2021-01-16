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

#ifndef _BASICVARAREA_H
#define _BASICVARAREA_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void minusVectorDoub(const double *va,const double *vb,double *ret,int numDime);
void plusVectorDoub(const double *va,const double *vb,double *ret,int numDime);
void scaleVectorDoub(const double *va,const double val,double *ret,int numDime);
double linearKernelFn_2(const double *va,const double *vb,int numDim);
double diffVAbsoluateValDoub(const double *va,const double *vb,int numDim);
double plusVAbsoluateValDoub(const double *va,const double *vb,int numDim);

double absf(double a);
double maxVal(double a,double b);
double minVal(double a,double b);

/* ------ utility  A group*/
/*
    isln = 0 : no new line
           1 : new line
*/
void printDou(const char *str,const double val,int isln);
void printInt(const char *str,const int val,int isln);
void printVoidSt(const char *str,const void *val,int isln);
void printLnAndFile(const char *str,const int ln,int isln);
void prntVDou(const double *dat,int n);
void prntMDou(double **dat,int m,int n);
double* newDoubleArea(int size,int *ret);
double** newPDoubleDArea(int size,int *ret);
double** new2DimDoubleArea(int size,int dmi,int *ret);
void initialDoubleArea(double *dat,double val,int num);
void initial2DDoubleArea(double **dat,double val,int num,int num2);
int delDoubleArea(void **dat);
int del2DimDoubleArea(void **dat,int size);
double randomFn(const double max,const double min);
/*
    opt - bit set
    1 - no max checking
    2 - no min checking
*/ 
double setDoubleInbound(const double max,const double min,const double val,const int option,const int isShowErr);
int setIntInbound(const int max,const int min,const int val,const int option,const int isShowErr);

/* validatBound */
int vdIntBound(const int max,const int min,const int val);
int vdDoubleBound(const double max,const double min,const double val);

/* reading XML*/


#endif /* _BASICVARAREA_H */
