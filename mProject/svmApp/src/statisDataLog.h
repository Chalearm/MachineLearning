#ifndef _STATISDATALOG_H
#define _STATISDATALOG_H
#include <stdlib.h>
#include <time.h>
#include "simMatDouble.h"
#include "avlTree.h"
#include "listPvoid.h"
#define MAX_PROCESS 4
#define SIMMAT2_T_MAIN_SIZE 12000
#define SIMMAT2_T_REDUN_SIZE 200
#define SIMMAT2_T_PVOIDELEM_SIZE 30
 

struct data4FindMinMaxValInT
{
    double m_val;
    double m_max;
    double m_min;
};
struct searchStatisDataOpt
{
    int m_numAttb; /* 0 is no option*/
    char m_result; /*  0= nothing, 1= inconsist , 2 = redundant */
};
struct statisDataLogElement
{
    int indexDim;
    char typeStatus;
};
struct statDataLogEleArr
{
    struct statisDataLogElement *m_data;
    int m_num;
}; 

struct elemSdv /* sdv = statistic data value*/
{
    double m_maxValueInDim;
    double  m_minValueInDim;
    char m_isSetMin;
    char m_isSetMax;
    /* From dataFormat struct */
    char m_sdOpt; /*statistic option for mode and median
                         0 is mean them (default value)
                         1 is random choose*/
    char m_avail;/* <!-- availValue = available value is using the value from input to replace a missing value-->
                        <!-- use is 1 not use 0 -->  */
    /* statistic value */
    double  m_meanValueInDim;
    double m_lastMedianValue;
    double  m_medianValueInDim;
    double  m_medianVal2;
    int m_numMedian;
    double  m_modValueInDim;
    
    /* for mean */
    double m_sum;
    double m_numMem;
    
    /* for median*/
    double *m_middleValueP; 
    int m_numMemInMax;
    int m_numMemInMin;
    binaryTree m_maxHeap; /*key is double and data is int*/
    binaryTree m_minHeap;
    
    /* for mode */
    pVoidList m_hignFreqValList;
    int m_maxCount;
    int m_numSameCount;
    
    
    /* keep possible value */
    binaryTree m_possibleValTree;
    
    /* the statistical value from available value */
    double m_meanValueAvailValue;
    double m_medianValueAvailValue;
    double m_modValueAvailValue;
};
struct groupVariableSdv /* only input elements*/
{
    int *countMallo;
    struct elemSdv **m_variables;
    int m_numDim;
    int m_numOutDim;
    void *m_clsVal;  /*  m_numOutDim =1 void* = double* , >1 void* = double** */
    int m_numClass;
    int m_inputType;
};
struct incompAndDiscData
{
    void *addr;
    struct statDataLogEleArr statDat;
};

/* search which is for contain node*/
struct addNodeToTree
{
    char m_isVerify;
    char m_isNewKey;
    binaryTree *m_newTree;
    binaryTree *m_OldTree;
    void *sample;
    struct statisDataLogElement *m_statEle;
    int m_num;
    int m_numProc;/* num process */
    char m_tempRes;
    void *m_newNode;
    void *m_oldNode;
    void *m_data;
    void *m_fn[MAX_PROCESS]; 
    
    /* member variable to keep track the number of each */
    /* use only tree has updated*/
    int *m_treeCountOld;
    int *m_treeCountNew;
    int m_plusValOld;
    int m_plusValNew;
    
    void *m_PV2List;
    void *m_PV2Ele;
};

/* for filling value to some elements */
struct statisDataLog
{
    int *countMallo;
    int m_inputType; /*0 (default) = vector version1 or 1 = version 2 (Mt22d)*/
    void *whichDataSet; /* point to the buffer to keep the data set */
    /* 
        -1 is reject this sample
        0 is mean
        1 is median
        2 is mod
        3 is random (double)
        4 is random (int)
        5 is maximum
        6 is minimum
    */
    int m_totalOfRedunNode;
    int m_totalOfDiscardInsNode;
    int m_totalOfInconsistNode;
    int m_totalOfIncompleteNode;
    int m_totRejectReassignNode;
    binaryTree m_redundantTree;
    binaryTree m_discardInsTree;
    binaryTree m_inconsistTree;
    binaryTree m_incompleteTree;
    binaryTree m_mainT;
    struct addNodeToTree m_handleTrees;
    struct searchStatisDataOpt m_optTSearch;
    
    
    mat2_2d m_mat2d24MainT;
    mat2_2d m_mat2d24RedunT;
    mat2_2d m_mat2d24PVoidCls;  /*use in Redunt and conflict T*/
    mat2_2d m_mat2d24PVoidEle;  /*use in Redunt and conflict T*/

    int *count1;
    };

    /*
        Parameter :
        statis keep
        (
            sld file
            sld class
            int numberOfClass
            identifier Tree
            statistic data set (to calculate value)
        )
        current node address
    */
/* Use to separate class */
struct traverseBuff
{
    struct statisDataLog *m_pSldFile;
    struct statisDataLog *m_pSldClass;
    int m_numClass;
    int m_numOut;
    int m_numIn;
    struct groupVariableSdv *m_keepDatStatis;
    binaryTree *m_pIdenClass;
    
    /* internal variable */
    binaryTree *m_t;
    /* statis value is not defined */

    /* temp */
    void *m_findN;
    vector_double m_bufSam;
    void *m_sam; /* keep sample */ 
    void *m_p;
    
    
    void (*findWhichClass)(struct traverseBuff*,void*); 
};
/*

    int (*compareTypeWithOpt)(void*,const void*,const void*);
void* searchDataInBinaryTreeWithOpt(binaryTree* bin,void *opt,const void* key)
*/
typedef struct statisDataLogElement statisDataLogElement;
typedef struct statisDataLog statisDataLog;
typedef struct statDataLogEleArr statDataLogEleArr;
typedef struct redundantData redundantData;
typedef struct searchStatisDataOpt searchStatisDataOpt;
typedef struct incompAndDiscData incompAndDiscData;
typedef struct addNodeToTree addNodeToTree;
typedef struct traverseBuff traverseBuff;
typedef struct elemSdv elemSdv; 
typedef struct groupVariableSdv groupVariableSdv;
typedef struct data4FindMinMaxValInT data4FindMinMaxValInT;
/*
0 = main tree
1 = redundant tree
2 = inconsist tree
3 = incomplete tree
other = NULL
*/
/*in case VectType = 1*/
void printNodeAndPVLAdrr(void *node);
void printKeyOfNdFixNBin(void *node);
void printSampleFxBin(void *sam);
void* getPVLMt2(void *node);
void clearNodeAvlTFNBin(binaryTree* avlTree,void* node);
/*end of in case VectType = 1*/

void addProcess2AddNode2T(statisDataLog *stdlObj,char type); 
char searchTheTreeForContainTheNode(statisDataLog *obj,void *sample,statisDataLogElement *statEle,int numEle);
/* #0 general tree  methods */
    /*  #00shared all tree */
    int compVDoub4StatisLog(const void* a,const void *b);
    int compVDoub4StatisLog4Mt22d_NBin(const void* a,const void *b);
    int compVDoubWithOpt4StatisLog(void *opt,const void* a,const void *b);
    int compVDoubWithOpt4StatisLog4Mt22d_NBin(void *opt,const void* a,const void *b);
    /*  #00e end of shared all tree */
    vector_double* newKeyOfAvlT4Sdl(vector_double *sample);
    int addSampleToPvoidListDataOfAvlTr4Sdl(void *node,void *sample);
    int addSamp2PVltDatOfAvlTr4Sdl_NBINFixNd(void *node,void *sample);
    int initDataOfKeyOfAvlT4Sdl(void *node);
    int moveDataOfOldNodeToNewNodeOfAvlT4Sdl(void *newNode,void *oldNode);
    int mvDatOfONd2NNdOfAvlT4Sdl__NBINFIXArr(void *newNode,void *oldNode);
/*  #0e end of general tree  methods */

/* #1 searchStatisDataOpt  method*/
    void setAttrbSizeInStatisDataLog(statisDataLog *obj,int value);
    void initSearchStatisDataOpt(searchStatisDataOpt *obj);
    /*  0= nothing, 1= inconsist , 2 = redundant */
    void setResultOfSearchStatisDataOpt(searchStatisDataOpt *obj,char value);
    char getResultOfSearchStatisDataOpt(searchStatisDataOpt *obj);
    void setNumAttrbOfSearchStatisDataOpt(searchStatisDataOpt *obj,int value);
/* #1e end searchStatisDataOpt method*/

/* #2 statisDataLogElement method */
    void constructSdlEle(statisDataLogElement *obj);
    int setValOfSdlEle(statisDataLogElement *obj,int indexDim,char typeStatus);
    int copyValueOfStatisDataLogElement(statisDataLogElement *obj1,statisDataLogElement *obj2);
/* #2e end of statisDataLogELement */

/* #3 statDataLogEleArr method */
    void constructorStatDataLogEleArr(statDataLogEleArr *obj);
    int setArrSizeOfStatDataLogEleArr(statDataLogEleArr *obj,int size);
    int setValToStatDataLogEleArr(statDataLogEleArr *obj,statisDataLogElement* data,int size);
    void makeEmptyStatDataLogEleArr(statDataLogEleArr *obj);
    int getSizeArrOfStatDataLogEleArr(statDataLogEleArr *obj);
    char getStatusFromStatDataLogEleArr(statDataLogEleArr *obj,int index);
/* #3e end of statDataLogEleArr method*/

/* #4 methods of  main tree*/
    void constructMainT4Sdl(binaryTree* obj,int vectorType);
    void destructorMainT4Sdl(binaryTree* obj);
    void printKeyAvlTreeInStatisDataLog(void* key,char* buff); 
    /* in case of using static array (fixed size) */
    /* set to Tobj->printTree */
    void printFixArrMainT_NBin4SDL(binaryTree* bin,char option); 
    /* called in printFixArrMainT_NBin4SDL */
    void printFixArrNodeOfMainT_NBin4SDL(binaryTree* bin,void* node,int high);
    /* set to Tobj->printKeyPVoid */ 
    void prntKeyAvlTFixArrNBin4SDL(void* key,char* buff); 
/* #4e end of methods of  main tree*/

/* #5 methods of redundantTree */
    void constructRedundantAvlT4Sdl(binaryTree *obj,int vectorType);
    void destructRedundantAvlT4Sdl(binaryTree *obj);
    void delRedundantDataInSdl(void *obj,void *data);
    void delRedundantDataInSdl_NdFixNBin(void *obj,void *data);
    /* #5e end methods of redundantTree */

/* #6 methods of inconsistent tree*/
    void constructInconsistAvlT4Sdl(binaryTree *obj,int vectorType);
    void destructInconsistAvlT4Sdl(binaryTree *obj);
    void delInconsistDataInSdl(void *obj,void *data);
    void delInconsistDataInSdl_NdFixNBin(void *obj,void *data);
    /* is able use for redundant and inconsist node */
    int getNumListInNodeAddNode(void *node);
/* #6e end methods of inconsistent tree*/

/* #7 incompAndDiscData  method*/
    void constructIncompAndDiscDat(incompAndDiscData *obj);
    void addData2IncompAndDiscData(incompAndDiscData *obj,void *addr,statisDataLogElement *statEle,int numEle);
    void destructIncompAndDiscDat(incompAndDiscData *obj);
    void printIncompAndDiscDat(incompAndDiscData *obj);
/*  #7e end incompAndDiscData  method*/

/*  #8 incomplete and discard data  tree method*/
    void constructIncompAndDiscAvlT4Sdl(binaryTree *obj,int vectorType);
    void destructIncompAndDiscAvlT4Sdl(binaryTree *obj);
    void delIncompAndDiscDataInSdl(void *obj,void *data);
    void delIncompAndDiscDataInSdl_NdFixNBin(void *obj,void *data);
    void delDatOfIncompAndDiscAvlT4Sdl(void *data);
    int initDataOfKeyOfIncompAndDiscAvlT4Sdl(void *node);
    int addSampleToPvoidListDataOfIncompAndDiscAvlTr4Sdl(void *node,vector_double *sample,statisDataLogElement *statEle,int numEle);
    int addSampleToPvoidListDataOfIncompAndDiscAvlTr4Sdl_NdFixNBin(void *node,void *sample,statisDataLogElement *statEle,int numEle);
/* #8e end  of incomplete and discard data  tree method*/

/*
struct addNodeToTree
{
    char m_isVerify;
    char m_isNewKey;
    binaryTree *m_newTree;
    binaryTree *m_OldTree;
    vector_double *sample;
    struct statisDataLogElement *m_statEle;
    int m_num; 
    int m_numProc;
    char m_tempRes;
    void *m_newNode;
    void *m_oldNode;
    void *m_data;
    void *m_fn[MAX_PROCESS]; 
};
*/
/*  #9 addNodeToTree methods */
void verifyAddNodeToTree(addNodeToTree *obj);
void constructAddNodeToTree(addNodeToTree *obj);
/* process1 */
void newKey4MainT(addNodeToTree *obj); /* has only main process1*/
void newKey4GT(addNodeToTree *obj);  /* has sub processes to init data */
/* process 2*/
void initDataOfKey4GT(addNodeToTree *obj); /* it is  a sub process*/
void initDtOfKy4GT_NBINFixNd(addNodeToTree *obj); /* it is  a sub process*/
void initDataOfKey4GT2(addNodeToTree *obj); /* it is  a sub process for incomp t*/
void initDataOfKey4GT2_NBINFixNd(addNodeToTree *obj); /* it is  a sub process for incomp t*/
/* process 3*/
/* add data to old node process  */
void addData2Node(addNodeToTree *obj);
void addData2Node_NBInFxNd(addNodeToTree *obj);
void addData2Node2(addNodeToTree *obj);/* it is  a sub process for incomp t*/
void addData2Node2_NdFixNBin(addNodeToTree *obj);/* it is  a sub process for incomp t*/
/* move and delete an old node */
void moveDat2Node4GT(addNodeToTree *obj);  /* main tree to another tree */
void mVDt2Nd4GT_NBINFIXArr(addNodeToTree *obj);  /* main tree to another tree */
void moveDat2Node4GT2(addNodeToTree *obj); /* inconsist to/from redundant tree*/
void moveDat2Node4GT2_NBINFIXArr(addNodeToTree *obj); /* inconsist to/from redundant tree*/
/* incomp data(s) have been not moved */

int runAllProcs4AddNode2T(addNodeToTree *obj); 
/*  #9e addNodeToTree methods */
/* #10 traverseBuff methods */ 
void constructorTravBuff(traverseBuff *obj);
int getNumClassFromTravBuff(traverseBuff *obj);
void initValueOfTravBuff(traverseBuff *obj,statisDataLog *objFile,statisDataLog *objClass,int numClass,int numInOut,int numInp,binaryTree *idenT,struct groupVariableSdv *keepDat);
void init2FindRedunTravBuff(traverseBuff *obj);
void destructorTravBuff(traverseBuff *obj);
/* depth first traverse */
int traverseMainTMSamp2OthT4Sdl(traverseBuff *obj,void *node);
void findClass4NotV4Sdl(traverseBuff *obj,void *node); 
void findClass4V4Sdl(traverseBuff *obj,void *node); 
/* #10e traverseBuff methods */

/* #11  statistic value  method */
void constructEleSdv(elemSdv *obj);
void destructEleSdv(elemSdv *obj);
int compDoublePossibleValTreeInEleSdv(const void* a,const void *b);
void constructPossibleValTreeInEleSdv(elemSdv *obj);
void DestructurePossibleValTreeInEleSdv(elemSdv *obj);
void deleteDoubleKeyNode4PossibleValTOfEleSdv(void *obj,void *key);
void printDoubleKey4PossibleValTOfEleSdv(void* key,char* buff);
void setSdOptionEleSdv(elemSdv *obj,char val);
void delDatOfHeadInEleSdv(void *obj,void *data);
int compHeadInEleSdv(const void* a,const void *b);
void keepDat2EleSdv(elemSdv *obj,double *val);
/* find neighbour of statistic value */
void findNeighbourOfStatisticValInAvlT4EleSdv(binaryTree *bin,void *node,data4FindMinMaxValInT *obj);
void findNeighbourOfStatisticValInAvlT4EleSdv2(binaryTree *bin,double maxVal,double minVal,double inputVal,double *outputVal);

void* getNodeMaxEleSdv(binaryTree *obj, void *root);
void* getNodeMinEleSdv(binaryTree *obj, void *root);
void add2QModeEleSdv(elemSdv *obj,double *val,int countRepeat);
/* 0 is not force, 1 is max, 2 is min*/
void *insertValP2HeapEleSdv(elemSdv *obj,double *val,char forceVal,int *countRepeat);

void printTinEleSdv(void *key,char *buff);
void printDataTinEleSdv(void *node,char *buff);
void printEleSdv(elemSdv *obj);
/* 4 find mean, mode and median from the data that kept */
void summarizeEleSdv(elemSdv *obj);
double getValueOfEleSdv(elemSdv *obj,char type); 

void constructGroupVariableSdv(groupVariableSdv *obj,int numDim,int  numOutDim,int numCls,int inputType);
void summarizeGroupVariableSdv(groupVariableSdv *obj);
void setSdOptionGroupVariableSdv(groupVariableSdv *obj,int index,char val);
void printGroupVariableSdv(groupVariableSdv *obj);
double getValueFromGrpValSdv(groupVariableSdv *obj,int whichCls,int indexDim,char type,char *isOk);
void destructGroupVariableSdv(groupVariableSdv *obj);
void keepDat2GroupVariableSdv(groupVariableSdv *obj,void *val,int indexCls);

int fixMis2ASampleVarSdv(groupVariableSdv *obj,int whichCls,void *pList,int indexEle,vector_double **valVdoub);
int fixMis2ASampleVarSdv_NdFixNBin(groupVariableSdv *obj,int whichCls,void *pList,int indexEle,void **valVdoub);
/* #11e  statistic value  method */

/* #12  data4FindMinMaxValInT method*/
void constructorData4FindMinMaxValInT(data4FindMinMaxValInT *obj);
void destructorData4FindMinMaxValInT(data4FindMinMaxValInT *obj);
double getMaxInData4FindMinMaxValInT(data4FindMinMaxValInT *obj);
void setMaxInData4FindMinMaxValInT(data4FindMinMaxValInT *obj,double max);
void setValInData4FindMinMaxValInT(data4FindMinMaxValInT *obj,double val);
double getMinInData4FindMinMaxValInT(data4FindMinMaxValInT *obj);
void setMinInData4FindMinMaxValInT(data4FindMinMaxValInT *obj,double min);
/* #12e  data4FindMinMaxValInT method*/

vector_double* getSampleToAvlNodeInStatisDataLog(void *node);
statDataLogEleArr* getStatDataLogEleArrFromNodeAvlTreeInStatisDataLog(void *node);

/* statisDataLog(SLD)   methods */ 
    /*
        Parameter :
        statis keep
        (
            sld file
            sld class
            int numberOfClass
            identifier Tree
            statistic data set (to calculate value)
        )
        current node address
    */
    void constructorStatisDataLog(statisDataLog *obj,int vectorType);
    void makeStatisDataLogEmpty(statisDataLog *obj);
    /* insert data to list */ 
    int addDataToStatisDataLog(statisDataLog* statisDataLogObj,void *sample,statisDataLogElement *statEle,int numEle);
    int allocatStatisDataLogArray(statisDataLog** statisDataLogObj,int num,int numAttrb,int vectorType,int *cm);
    int deallocatStatisDataLogArray(statisDataLog** statisDataLogObj,int num);
/*  end  of statisDataLog   methods */ 
    int getNumOfMainTDataInStatisDataLog(statisDataLog* statisDataLogObj);
    int getnumOfAllTDatInSdl(statisDataLog* obj);
    void* getRootNodeOfMainTInSdl(statisDataLog* obj);
    void* getRootNodeOfRedunTInSdl(statisDataLog* obj);
    void* getRootNodeOfIncompTInSdl(statisDataLog* obj);
    /* 
    2017 June 27
    swap value between element in the array
     this is used for Statitis data log of each class 
    0 = is main Tree
    1 = is redundant tree
    2 = is inconflic tree
    3 = is incomplete tree
    4 = is discard tree

    */
    void randomArrFixSizeNBIn4Sdl(statisDataLog* obj,int whichTree,int swapTime);
    void printTsInSdl(statisDataLog* obj,int whichTree);
       /* not yet */ 


    void printStatisDataLog(statisDataLog* statisDataLogObj,matrix_double* dataPrint);
#endif /* _STATISDATALOG_H */