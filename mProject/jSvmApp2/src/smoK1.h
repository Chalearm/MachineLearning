/********************************************************************/
/*
      FILE        :   smoK1.h
      Name        :   Chalearm Saelim
      Date        :   03 January 2018
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to provide the training feature by the modified SMO of Keerthi v. 1 (SMO K1)


      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        03-01-2018    csaelim    First draft 
*/
/*******************************************************************/
#ifndef _SMOK1_H
#define _SMOK1_H

#include "smoBuff.h"

struct smoK1Learner
{
    /* offset value */
    double m_eps;
    double m_roundNum;
    
    double m_cSMO;
    
    int m_dim;
    struct SMOBuffer *m_buff1;
    
    struct rvSet m_I0;
    struct rvSet m_I1;
    struct rvSet m_I2;
    struct rvSet m_I3;
    struct rvSet m_I4;
    struct rvSet m_supportVectSet;
    
};

/*
// Public method 

void initiSMOKMBuff(struct SMOKMBuff *obj,struct inputSet *objP);
void initIupAndIlowofSMOKMBuff(struct SMOKMBuff *obj);
void clearSMOKMBuff(struct SMOKMBuff *obj);
int takeStep(struct SMOKMBuff *obj);
int examineExam(struct SMOKMBuff *obj,long int index);



void printSMOKMBuff(struct SMOKMBuff *obj,unsigned int opt);
void setAllDat2SetSMOKBuff(struct SMOKMBuff *obj);
// Private method 
void updateBiasAndIndexLowUp(struct SMOKMBuff *obj, long int index); 

void computeLAndHInTakeStep(struct SMOKMBuff *obj,double *L,double *H);
int AddIndex2AllSets(struct SMOKMBuff *obj,double alpha,long int index);
// from tutorial of Sequential Minimal Optimization for SVM
double objectiveFnAlpha(struct SMOKMBuff *obj,double alpha2);
// origin equation from Platt 
double objectiveFnAlphaOrgn(struct SMOKMBuff *obj,double alpha2);

*/





void checkObjFnAlpha2(double *L1,double *L2,double *H1,double *H2);
void updateCurrentError(struct smoK1Learner *obj,int index1or2);


int mainLearningLoopInSmoK1Learner(struct smoK1Learner *obj);
int initiSmoK1Learner(struct smoK1Learner *obj);
int constructSmoK1Learner(struct smoK1Learner *obj,struct SMOBuffer *smoBObj,struct datSpace *dtSp, struct kFnHdl *kFn);
int destructSmoK1Learner(struct smoK1Learner *obj); 
int stErrParamInSmoK1Learner(struct smoK1Learner *obj,const double eps, const double tol,const double rdNum);
int stSMOParamInSmoK1Learner(struct smoK1Learner *obj,const double cAlpha,const int nDim);

#endif /*  _SMOK1_H */