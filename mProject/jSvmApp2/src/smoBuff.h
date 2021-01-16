/********************************************************************/
/*
      FILE        :   smoBuff.h
      Name        :   Chalearm Saelim
      Date        :   03 January 2018
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to provide the buffer for SMO


      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        03-01-2018    csaelim    First draft 
*/
/*******************************************************************/
#ifndef _SMOBUFF_H
#define _SMOBUFF_H

#include "knFn.h"
#include "dtSpc.h"
#include "setRealV.h"
/*
    updateMet : (update method)
    READ_ALPHA : read  m_alpha
    WRITE_ALPHA: write m_alpha
    READ_FVAL  : read  m_fVal
    WRITE_FVAL : write m_fVal
    READ_YCURR : read m_yCurr
    WRITE_YCURR: write m_yCurr
*/
#define READ_ALPHA  0
#define WRITE_ALPHA 1
#define READ_FVAL   2
#define WRITE_FVAL  3
#define READ_YCURR  4
#define WRITE_YCURR 5

struct SMOBufferEle
{
    double m_alpha;
    double m_fVal; /* or error */
    int m_yCurr;   /* 0 is not defined,*/
};
struct SMOBuffer
{
    struct kFnHdl *m_kernelFn1;
    struct datSpace *m_dtSp;
    struct SMOBufferEle *m_smoBuffEle;
    int m_nBuff;
    int m_dim;
    double m_tol;
    double m_cSVM;
    double m_roundNum;
    double m_eps;
    long int m_i; /* up*/
    long int m_j; /* low */
    
    double m_Bias;
    double m_b_up;  /* Bias Upper bound*/
    double m_b_low; /* Bias Lower bound*/
    
    double m_y1;
    double m_y2;
    double m_F1;
    double m_F2;
    double m_s;
    double m_k11;
    double m_k22;
    double m_k12;
    
    double m_alpha1;
    double m_alpha2;
    double m_currEta;
    long int m_index1;
    long int m_index2; 
    
    /* loop sample */
    int m_currIndex;
    
    
    struct rvSet m_I0;
    struct rvSet m_I1;
    struct rvSet m_I2;
    struct rvSet m_I3;
    struct rvSet m_I4;
    struct rvSet m_supportVectSet;
};

int setAllDat2SetSMOK1InSMOBuffer(struct SMOBuffer *obj);
int mainLearningLoopInSMOBuffer(struct SMOBuffer *obj);
int AddIndex2AllSetsSMOK1InSmoBffer(struct SMOBuffer *obj,double alpha,int index1);
void updateBiasAndIndexLowUpSMOK1InSmoBffer(struct SMOBuffer *obj,int index);
void checkObjFnAlpha2SMOK1InSmoBffer(double *L1,double *L2,double *H1,double *H2);
double objectiveFnAlphaSMOK1InSmoBffer(struct SMOBuffer *obj,double alpha2);
double objectiveFnAlphaOrgnSMOK1InSmoBffer(struct SMOBuffer *obj,double alpha2);
void compLAndHInTakeStpSMOK1InSmoBffer(struct SMOBuffer *obj,double *L,double *H);
int takeStepSMOK1InSmoBffer(struct SMOBuffer *obj);
int examineExamSMOK1InSMOBuffer(struct SMOBuffer *obj,int index);
double learnSMOFxInSMOBuffer(struct SMOBuffer *obj,int indexP);
int getNumI0SetInSMOBuffer(struct SMOBuffer *obj);
int nextDatI0setInSMOBuffer(struct SMOBuffer *obj);

int pushReadStateI0SetInSMOBuffer(struct SMOBuffer *obj,unsigned int *segId,unsigned int *id);
int popReadStateI0SetInSMOBuffer(struct SMOBuffer *obj,const unsigned int segId,const unsigned int id);
int isCanPopReadStateI0SetInSMOBuff(struct SMOBuffer *obj,const unsigned int segId,const unsigned int id);
int resetIdDatI0setInSMOBuffer(struct SMOBuffer *obj);
int gtNumSmoBuff(struct SMOBuffer *obj);
int gtNSVSampleInSmoBuff(struct SMOBuffer *obj);
int avrBiasInSMOBuffer(struct SMOBuffer *obj);

int initialSMOBufEle(struct SMOBufferEle *obj);
void prntSMOBuffEle(struct SMOBufferEle *obj);
int constructorSMOBufEle(struct SMOBufferEle *obj);
int destructorSMOBufEle(struct SMOBufferEle *obj);
int setYVal2SMOBuffEle(struct SMOBufferEle *obj,int val);

/*
    updateMet  : (update method)
    READ_ALPHA : read  m_alpha
    WRITE_ALPHA: write m_alpha
    READ_FVAL  : read  m_fVal
    WRITE_FVAL : write m_fVal
    READ_YCURR : read m_yCurr
    WRITE_YCURR: write m_yCurr
*/
int updateValInSMoBuffEle(struct SMOBufferEle *obj,int updateMet,double *val);

int initialSMOBuff(struct SMOBuffer *obj);
int stObjParamsInSMOBuff(struct SMOBuffer *obj, struct kFnHdl *kObj,struct datSpace *dObj);
int stValParamsInSMoBuff(struct SMOBuffer *obj,const double tol,const double cSVM,const double eps,const double roundN);
int stNDimParamInSMOBuff(struct SMOBuffer *obj, const int nDim);
int constructorSMOBuff(struct SMOBuffer *obj, int sizeBuff);
int destructorSMOBuff(struct SMOBuffer *obj);

int flushAllValOfSMOBuffEle2DefaultInSMOBuff(struct SMOBuffer *obj);
int clearMemberInAllSetOfSMOBuff(struct SMOBuffer *obj);
int resetLoopIndexSMOBuffer(struct SMOBuffer *obj);
/*
opt:
0 = in case y current != 0
1 = in case the index is SV's index

*/
int nxtDatInSMOBuffer(struct SMOBuffer *obj,int opt);
int pushCurrIndexInSmoBuff(struct SMOBuffer *obj, int *id);
int popCurrIndexInSmoBuff(struct SMOBuffer *obj,const int  id);
int isEndLoopInSmoBuffer(struct SMOBuffer *obj);
void prntSMOBuff(struct SMOBuffer *obj);

/*
    updateMet  : (update method)
    READ_ALPHA : read  m_alpha
    WRITE_ALPHA: write m_alpha
    READ_FVAL  : read  m_fVal
    WRITE_FVAL : write m_fVal
    READ_YCURR : read m_yCurr
    WRITE_YCURR: write m_yCurr
*/
int updateValInSMOBuff(struct SMOBuffer *obj,int updateMet,int index,double *val);
#endif /*  _SMOBUFF_H */