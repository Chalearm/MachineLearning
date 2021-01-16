/********************************************************************/
/*
      FILE        :   learningMgr.h
      Name        :   Chalearm Saelim
      Date        :   29 October 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Group All about modules that are used in SMO learning


      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        29-10-2017    csaelim    First draft 
      2.        07-12-2017    csaelim    Removed some part of code out (redesign)
      
*/
/*******************************************************************/
#ifndef _LEARNINGMGR_H
#define _LEARNINGMGR_H

#include "preprocML.h" 
#include "dtSpc.h"
#include "dtStGnHdl.h"
#include "smoBuff.h"
#include "knFn.h"

struct trainingInfo
{
    /* update after preprocssing data */
    int m_criteria; /**/
    /* update before start training (Every time the application starting a next loop */
    
    int m_nCls2BeTrn;
    /*
    int m_currKFoldSize;
    double m_currC;
    double m_currKenelVal;
    double m_currKenelOff;
    */
    /* update at preprocessing  */
    int *m_whichParty; /* orderly from class (0 to n-1), -1, 1 or 0(not be trained) */
    int m_nPartySlot; /* = number of classes */
};



struct SmpLoopController
{
    /* for loop increament +1, like from 0 to n -1*/
    int m_numClsBetrn; /* the number of trained class */
    int *m_whichCls;   /* allocate for n classes size*/
    
    /* Buffer */
    /* current max fold */
    int m_currMaxFoldVal;
    int m_currBrkLoopSmpIdInCls;
    int m_currWhichFoldId;
    int m_currClsId;
    int m_currSmpId;
    
};

int initialSmpLoopController(struct SmpLoopController *obj);
int constructSmlLpController(struct SmpLoopController *obj,int nParty);
int destructSmlLpController(struct SmpLoopController *obj);


struct oneAgaisOneClassesEle
{
    double *m_alpha;
    int *m_whichIdInCls;
    int m_nAlpha;
/*

m_whichOarty[0] = keep id of cls ,defined value = 1
m_whichOarty[1] = keep id of cls ,defined value = -1

*/
    int m_whichParty[2]; /* orderly from class (0 to n-1), -1, 1 or 0(not be trained) */
};


/* for keeping traing result */
struct oneAgaistAllClassesEle
{
    struct datSpace *m_dtSp;
    double *m_alpha;
    int *m_ySet;
    int *m_whichIdInACls;
    int m_nAlpha;
    
    int m_whichParty; /* orderly from class (0 to n-1), -1, 1 or 0(not be trained) */

};

struct oneAgaistAllClasses
{
    struct datSpace *m_dtSp;
    struct oneAgaistAllClassesEle *m_ele;
    int m_nCls;
};

int initialOneVsAllClasses(struct oneAgaistAllClasses *obj);
int consturctOneVsAllClsesEle(struct oneAgaistAllClassesEle *obj, struct datSpace *dtSp, int num);
int constructOneVsAllClasses(struct oneAgaistAllClasses *obj, struct datSpace *dtSp, int nCls);
int gtDtFromSmoBuff2OneVsAllClses(struct oneAgaistAllClasses *obj,struct SMOBuffer *smoBuff,int whichId);
int gtDtFromSmoBuff2OneVsAllClsesEle(struct oneAgaistAllClassesEle *obj,struct SMOBuffer *smoBuff,int whichId);

int initialOneVsClsesEle(struct oneAgaistAllClassesEle *obj);
int initialOneVs1Cls(struct oneAgaisOneClassesEle *obj);
int destructOneVsAllClasses(struct oneAgaistAllClasses *obj);
int destructOneVsAllClsesEle(struct oneAgaistAllClassesEle *obj);

struct smoParmSet
{
    int m_smoWay;
    double m_cVlMx;
    double m_cVlMn;
    double m_cVlStp;
    double m_tol;
    double m_esp;
    double m_roundNUm;
    
    
    /* local variable */
    int m_indexLoop;
    int m_nLoop;
    double m_currCVal;
};

struct kFold
{
    struct dtClsHdl *m_clsSet;
    int m_nFold;
    
};
struct kFoldSet
{
    struct kFold *m_kFSet;
    int m_nFoldSet;
};
struct dtClsHdl
{
    int m_nCls;
    int *m_firstIdSamCls;
    int *m_numSmCls;
};


/******************************************
////////////////////////////////////////
//////////////////// MAIN CLASS //////////////
//////////////////////////////////////////
///////////////////////////////////////
******************************************/
struct learningMgr
{
    int m_prtOpt;
    int m_svmMultiCls; /* default = 0 */
    struct kFnHdl     m_kFnSet;
    struct smoParmSet m_smoParSet;
    struct preProcDat m_preProSet;
    struct datSetGenHdl  m_dtGenSet;
    struct datSpace m_dtSp;
    struct kFoldSet m_kFoldSt;
    struct dtClsHdl m_trnclsHdl;
    struct dtClsHdl m_testclsHdl;
    
    /* buffer for training */
    struct trainingInfo m_trnInfo;
    struct SMOBuffer m_smoBuff;
    struct SmpLoopController m_loopTrnController;
    struct oneAgaistAllClasses m_oneVsAllClses;
    
};

int intialKFoldSet(struct kFoldSet *obj);
int contructorKFdSet(struct kFoldSet *obj,struct datSetGenHdl *cObj,struct preProcDat *pObj);
int destructKFdSet(struct kFoldSet *obj);
void prntKFdSt(struct kFoldSet *obj);

int intialKFd(struct kFold *obj);
int contructorKFd(struct kFold *obj,struct datSetGenHdl *cObj,int foldSize);
int destructKFd(struct kFold *obj);
int gtStartPosOnLeftInKFd(struct kFold *obj,int indexFold,int indexCls,int *startPos1,int *num);
int gtStartPosOnRightInKFd(struct kFold *obj,int indexFold,int indexCls,int *startPos2,int *num);
int gtStartPosOfKFd(struct kFold *obj,int indexFold,int indexCls,int *startPos1,int *num);
void prntKFd(struct kFold *obj);

/* initialization */
int initialDtClsHdl(struct dtClsHdl *obj);
int chckIsRead2GentDtClsHdl(struct dtClsHdl *obj);
int constructDtClsHdl(struct dtClsHdl *obj,int nCls);
int destructDtClsHdl(struct dtClsHdl *obj);
/* input interface */
int gentDatInDtClsHdl(struct dtClsHdl *obj,struct datSetGenHdl *cObj,int nKFold,int whichK);
int gentDat4TstSmpInDtClsHdl(struct dtClsHdl *obj,struct datSetGenHdl *cObj,int nKFold,int whichK);
/* output interface */
int gtNClsInDtClsHdl(struct dtClsHdl *obj);
void prtDtClsHdl(struct dtClsHdl *obj);
int gtStartPosInDtClsHdl(struct dtClsHdl *obj,int idCls,int *posStart,int *nSample);


void constructorLearningMgr(struct learningMgr *obj,const char *fileName);
void destructorLearningMgr(struct learningMgr *obj); 

int initialDefSmoParm(struct smoParmSet *obj);

int resetLoopOfCSVMInSMOParm(struct smoParmSet *obj);
int isEndOfLoopOfCSVMInSMOParm(struct smoParmSet *obj);
int nxtCSVMParamValInSMOParm(struct smoParmSet *obj);
void prtSmoParm(struct smoParmSet *obj);

void initialVals2MemsFromXML(struct learningMgr *obj,const char *fileName,int *ret1); 
void preprocessDtInLearnMgr(struct learningMgr *obj,int *ret1);
void trainingInLearnMgr(struct learningMgr *obj,int *ret1);
void testSmpInLearnMgr(struct learningMgr *obj,int *ret1);
struct SMOBuffer* gtSMOBuffInLearningMgr(struct learningMgr *obj);
struct oneAgaistAllClasses* gt1VsAllClsesInLearningMgr(struct learningMgr *obj);
struct dtClsHdl* gtTrnDtClsHdlClsLearningMgr(struct learningMgr *obj);
struct datSpace* gtDtSpInLearningMgr(struct learningMgr *obj);

int constructorSmoParm(struct smoParmSet *obj, void *smoParEle);


int destructSMOParSt(struct smoParmSet *obj);

int initialTrainingInfo(struct trainingInfo *obj);
/*int updateBefornTrnInTrnInfo(struct trainingInfo *obj,int kSize,double kenVal,double offsetVal);*/
int constructTrainingInfo(struct trainingInfo *obj,int nParty);
int destructTrainingInfo(struct trainingInfo *obj);
void prntTrainingInfo(struct trainingInfo *obj);


int stSMOParam2SmoBuff(struct smoParmSet *obj,struct SMOBuffer *sObj);
int stOutputVal4KthFoldInSmoBuff(struct SMOBuffer *obj, struct kFold *kObj,int indexCls,int indexKFold,int val);
int setPartyValSMOBuff(struct SMOBuffer *obj,struct dtClsHdl *dObj,int plusId,int minusId);
int stPartyValForAClsSMOBuff(struct SMOBuffer *obj,struct dtClsHdl *dObj,int indexCls,int val);
int setPartyVal2EleInSMOBuff(struct SMOBuffer *obj,int start, int stop,int val);
int stPartyVal4OVsAInSMOBuff(struct SMOBuffer *obj, struct kFold *kObj,int maxCls,int whichFold,int idCls);
int stPartyVal4TestFoldInSMOBuff(struct SMOBuffer *obj, struct kFold *kObj,int maxCls,int whichFold);
int isNot1FoldInKFold(struct kFold *obj);



/*  operation in */

int loopKFoldSetLearning(struct kFoldSet *obj,struct learningMgr *lmObj);
int loopKFoldLearning(struct kFold *obj,struct learningMgr *lmObj);
int loopAFoldLearning(struct dtClsHdl *obj,struct learningMgr *lmObj);

int gtTheNumOfClsInLearning(struct learningMgr *obj);
int generateSmClsVal(struct datSetGenHdl *obj,struct datSpace *dtObj);
int swapValueEachClsInDtStHdl(struct datSetGenHdl *obj,struct datSpace  *dtObj);
#endif /*  _LEARNINGMGR_H */