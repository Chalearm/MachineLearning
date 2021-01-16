/********************************************************************/
/*
      FILE        :   knFn.h
      Name        :   Chalearm Saelim
      Date        :   28 Decenber 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to keep the kernel function setting

      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        07-01-2018    csaelim    First draft 
*/
/*******************************************************************/
#ifndef _KNFN_H
#define _KNFN_H


struct kFnHdl
{
    int m_type;
    int m_currType4Loop; /* -1: there is no loop (fix) */
    double m_gaussMx;
    double m_gaussMn;
    double m_gaussStp;
    
    double m_polyMx;
    double m_polyMn;
    double m_polyOffSt;
    double m_polyStp;
    
    double m_sigMMx;
    double m_sigMMn;
    double m_sigMStp;
    
    /* local variable */
    double m_curKnVal;
    double m_curOff;
    double m_currPoly;
    
    /* use in case of m_currType4Loop > -1,((m_currModel++)+m_currType4Loop)%3*/
    /* use for loop */
    int m_currModelLoop; 
    
    int m_indexSigmaLoop;
    int m_indexPolyLoop;
    
    int m_nSigmaLoop;
    int m_nPolyLoop;
    
    double (*m_currFn)(struct kFnHdl*,const double*,const double*,int);
};

int constructorKernelFnHdl(struct kFnHdl *obj, void *kernelEle);
int destructKernelFnHdl(struct kFnHdl *obj);

int initialDefValKernelFnHdl(struct kFnHdl *obj);
void prtValKernelFnHdl(struct kFnHdl *obj);
const char* gtTypeInStringKernelFnHdl(struct kFnHdl *obj);
int nextParameterInKernelFnHdl(struct kFnHdl *obj);
int isEndloopSigmaInKFnHdl(struct kFnHdl *obj);
int isEndloopPolyInKFnHdl(struct kFnHdl *obj);
int resetAllLoopInKFnHdl(struct kFnHdl *obj);

double calValByKFnInKFnHdl(struct kFnHdl *obj,const double *va,const double *vb,int numDim);
double linearKernelFnInkFnHdl(struct kFnHdl *obj,const double *va,const double *vb, int num);
double polyKernelFnInkFnHdl(struct kFnHdl *obj,const double *va,const double *vb, int num);
double gausRadiusKernelFnInkFnHdl(struct kFnHdl *obj,const double *va,const double *vb, int num);
double sigMoidKnFnInkFnHdl(struct kFnHdl *obj,const double *va,const double *vb, int num);


#endif /*  _KNFN_H  */