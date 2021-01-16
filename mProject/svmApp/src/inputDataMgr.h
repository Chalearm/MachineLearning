#ifndef INPUTANDTASKMGR_H_
#define INPUTANDTASKMGR_H_
#include <time.h>
#include "svmApp.h"
#include "simString.h"
#include "taskMgr.h"
#include "simMatDouble.h"
#include "listMatDouble.h"
#include "statisDataLog.h"
#include "simMat2.h"
#define DEFAULT_PERCEN_NUM_SAM 90
#define DEFAULT_PERCEN_NUM_TESTSAM 10

struct logReadFileDataSet
{
    int lineNumber;
    simString filename;
   FILE* fp;
};
/*
struct dataInput
{
    double **output; // which [class][numOfDimOutput] 
    matrix_double *input; // which [class][numberData x Dimension] 
    int numClass;
    int numDesireInput; //number in the file,it is not more than numRealInput
    int* numRealInput; // number whhih is allocated
    
    double **maxValueInDim;
    double **minValueInDim;
    // statistic value 
    double **meanValueInDim;
    double **medianValueInDim;
    double **modValueInDim;
    int numberOfDim;
    int numberOfDimOutput;
    int isScale; // set after scale alreay
};
*/
struct dataInput
{
    long int m_maxNumSam;
    long int m_currNumSam;
    long int m_currentIndex;
    void *m_data;
};

struct numSamOfCls
{
    int m_index;
    int m_numSam;
    int m_numRealSam;
    int m_numTrain;
    int m_numTest;
};
struct clsDivision
{
    struct numSamOfCls *m_samDetail;
    int m_numTrainSam;
    /* size array of m_samDetail*/
    int numOFNumSamOfCls;
    int numTrainCls;
};
struct foldDetailEle
{
    int m_indexCls;
    int m_numEx;
};
struct aFold
{
    struct foldDetailEle *m_dat;
    int m_realUsedNum;
    int m_numMaxSam;
    int m_numDat;
    int m_currIndex;
};
struct akfold
{
    struct aFold *m_dat;
    int m_numDat;
};
struct kFoldSet
{
    struct akfold *m_dat;
    int m_numDat;
};
struct dataCrossValidSet
{
    struct dataInput m_testSam;
    struct dataInput *m_fold;
    int m_maxNumFold;
    int m_numOfNumFoldSet; /* size of m_numFoldSet array*/
    int *m_numFoldSet;
    int **m_numSampleOfEachFold;
    int *m_numTestSam;
};
/* new design cross validation set 17 July 2017*/
/*
    struct dataClsOfaFold
    {
        int m_clsIndex;
        int m_startIndexSample;
        int m_nSample;
    };
    struct aFold
    {
        struct dataClsOfaFold *m_clsSet;
        int m_nCls;
        int m_nSample;
    };
    struct dataCrossValid
    {
        struct aFold *m_fold;
        int m_numKFold;
        int m_numSample; // might be not used in future
    };
    struct dataCrossValidSet
    {
        void *m_dataSet; //(struct inputDataManager)
        void *m_attrb; //(struct taskManager)
        struct dataCrossValid *m_datCrossVSet;
        int m_nDatCorssVdSet;
        int m_nTrainSample;
        int m_nTestSample;

    };
*/
/* these struct is used with statisDataLog obj
   to handle sorting, replacing missing value */
struct dataSetContainer
{
    vector_double **data; /* 1st dim is which file */
    int numArr;           /* 2nd dim is which sample */
    int *numSample;
};
struct inputDataManager
{
    int *countMallo;
    int m_inputType; /*0 (default) = vector version1 or 1 = version 2 (Mt22d)*/
    int m_res; /* for keeping return value */
    struct taskMgr* m_taskToGet; /* no allocation or deallocation */
    char m_isIncludeTestToCrossVal;
    struct logReadFileDataSet *m_logReadFileDataSetObj; /* the array size is m_numTrainingFile */
    struct dataSetContainer m_dataSet;
    struct mat2_2d m_dataSet2;
    struct statisDataLog* m_statisDataObj;
    struct statisDataLog* m_statisDataEachClassObj;
    struct dataFormat* m_dataFormat;
    struct groupVariableSdv m_summaryDataStatistic;
    /* according to the number of statisDataLog and the number of dataFormat*/
    /* numFile is m_numTrainingFile + m_numTestingFile*(m_isIncludeTestToCrossVal==1) */
    int m_numFile; 
    int m_numDim;
    int m_numOutDim;
    int m_numClass;
    int m_numTrainingFile; 
    int m_numTestingFile;
    
    /* processing result */
    int m_numRealClass;
    int m_numValidSamples;
    
    
    int m_numSharedFile; /* used to keep the number of files that is used overlap between training and testing.*/
    char* m_bufferData;
    int m_buffSize;
    int *m_listOrderPosOfData;
    
    binaryTree m_identifyClassT;
    /* Temp for pass parameter, always count to be cleared after leave a method*/
    void *m_param1;
    void *m_param2;
    
    
};
typedef struct dataSetContainer dataSetContainer;
typedef struct dataInput dataInput;
typedef struct logReadFileDataSet logReadFileDataSet;
typedef struct dataCrossValidSet dataCrossValidSet;
typedef struct inputDataManager inputDataManager;
typedef struct numSamOfCls numSamOfCls;
typedef struct clsDivision clsDivision;
typedef struct foldDetailEle foldDetailEle;
typedef struct aFold aFold;
typedef struct akfold akfold;
typedef struct kFoldSet kFoldSet;

/*
    opt : 0 : construct by assigning *param
*/
void constructVoidClsArr(void *obj,int nloop,void* (*func)(void*,void*,int*),void *param,int opt,int *flag);
void newArrInt1D(void *obj,int size,int *flag);
void newArrVoidSt1D(void *obj,int typesize,int *flag);
void newArrInt2D(void *obj,int size,int size2,int *flag);
void newArrInt2Ddynsize(void *obj,int size,int* size2,int *flag);
void clearOnePointerArr(void **obj);
void clearDoublePointerArr(void ***obj,int num);
int randomFx(int max,int min);

/* declaration dataSetContainer method area */
int constructorDataSetContainer(dataSetContainer* obj);
int newNumberDataSetContainer(dataSetContainer* obj,int num);
int newNumberSamplesInDataSetContainer(dataSetContainer* obj,int index,int num,int numDim);
    int newArraryOfVectDoubleForDataSetContainer(vector_double **vecdou,int num,int numDim);
    void destructArraryOfVectDoubleForDataSetContainer(vector_double **vecdou,int num);
int initialValueOfDataSetContainer(dataSetContainer* obj,int index,double value);
void* getPointerOfArrFor1FileOfDataSetContainer(dataSetContainer* obj,int index);
vector_double* getAVectorOfDataSetContainer(dataSetContainer* obj,int index,int index2);
void destructDataSetContainer(dataSetContainer *obj);
/* end dataSetContainer method area */
/*  inputDataManager method area */

void constructorInputDataManager(inputDataManager* obj);
/* Identify class T(to fast compare) */
/* normal compare not used */
void constructIdenClsT4InpDatMgr(binaryTree *obj,int numDimOut); /* Dim = dimension*/

void delIdenClsTData4InpDatMgr(void *obj,void *data); 
void delVKey4InpDatMgr(void *obj,void *data);
int compVDouble4InpDatMgr(const void* a,const void *b);
int compDouble4InpDatMgr(const void* a,const void *b);

void destructIdenClsTT44InpDatMgr(binaryTree *obj);
/* end methods of Identify class T */
void setReturnValueOfInputDataManager(inputDataManager* obj,int val);
void destructInputDataManager(inputDataManager *obj);
void getTheQuantityValueToInputDataManager(inputDataManager *obj,taskMgr* taskMgrObj);
int verifyAllQuantityValueOfInputDataManager(inputDataManager *obj);
void startInitialAllVariableOfInputDataManager(inputDataManager *obj);
void addSharedFileToLogReadFileDataOfInputDataManager(inputDataManager *obj);
int initialFormatDataOfInputDataManager(inputDataManager *obj); /*dataFormat* dataFormatObj is set at here. */
void readDataFromFileToInputDataManager(inputDataManager *obj);
void loadFpAndLnAndIsNotCloseFileOfInputDataManager(inputDataManager *obj,int indexFile,FILE** fp,int* oldIndex,char *status);
void readDataFromFileInInputDataManager(inputDataManager *obj,int indexFile,FILE* fp,int* oldIndex);
void backupIndexAndFpInInputDataManager(inputDataManager *obj,int indexFile,FILE* fp,int oldIndex,char status);
void separateDatToEachClass4IntDatMgr(inputDataManager *obj);
void updateGroupValSdvFromDataFormat4IntDatMgr(inputDataManager *obj);
/* private method */
void fixMis2SampleVarSdv(inputDataManager *obj,int whichCls,void *incompNode);
void fixMis2SampleVarSdv_NdFixNBin(inputDataManager *obj,int whichCls,void *incompNode);
int findWhichClsInIdentityT4IntDatMgr(inputDataManager *obj,void *incompNode);
int findWhichClsInIdentityT4IntDatMgr_NdFixNBin(inputDataManager *obj,void *incompNode);
void TransverseMissT2UpdateGroupValSdvFromDatFormat4IntDatMgr(void *node,inputDataManager *obj);
void clrMsValAndSeparate2ClsInIncomplT4IntDatMgr(inputDataManager *obj);
void randAllInputElementsOfEachClass4IntDatMgr(inputDataManager *obj);
int transverIncompT2SeparateCls4IntDatMgr(inputDataManager *obj,void *incompNode);
void countActualClsAndNumSample4IntDatMgr(inputDataManager *obj);


int getThenumOfTrainEx(inputDataManager *obj);
int getThenumOfTestEx(inputDataManager *obj);
/* end inputDataManager method area  */

/* numSamOfCls methods */
void constructNumSamOfCls(numSamOfCls *obj,int *ret);
void swapIntValue(int *a,int *b,int *ret);
void swapNumSamOfCls(numSamOfCls *obj,numSamOfCls *objB,int *ret);
void assignAVal2NumSamOfCls(numSamOfCls *obj,inputDataManager *objI,int index,int *ret);
/* end of numSamOfCls methods */
/* clsDivision methods*/
void constructClsDivision(clsDivision *obj,int numCls,int *ret);
void assignVal2NumSamOfCls(clsDivision *obj,inputDataManager *objI,int *ret);
void destructClsDivision(clsDivision *obj);
/* end of clsDivision methods*/

/* foldDetailEle methods*/
void constructFoldDetailEle(foldDetailEle *obj,int *ret);
void printFoldDetailEle(foldDetailEle *obj);
void destructFoldDetailEle(foldDetailEle *obj,int *ret);
/* end of foldDetailEle methods*/
/* aFold methods*/
void constructAFold(aFold *obj,int numSam,int numArry,int *ret);
/*
 1 = full
 2 = ok
 3 = ok and full
*/
int setDat2AFold(aFold *obj,int indexCls,int num,int *remain1,int *ret);
void printAFoldAndVerify(aFold *obj);
void destructAFold(aFold *obj,int *ret);
/* end of aFold methods*/
/* akfold methods*/
void constructAkfold(akfold *obj,int num,int *ret);
void printAkFold(akfold *obj);
void setNumSam2AFofAKFold(akfold *obj,clsDivision *objC,int *ret);
void destructAkfold(akfold *obj,int *ret);
/* end of akfold methods*/
/* kFoldSet methods*/
void constructKFoldSet(kFoldSet *obj,int num,int *ret);
void divideNumSam2EachKFold(kFoldSet *obj,clsDivision *objC,int *ret);
void setAkfoldInKFoldSet(kFoldSet *obj,int whichIndex,int num,int *ret);
void destructKFoldSet(kFoldSet *obj,int *ret);
/* end of kFoldSet methods*/

    void constructorDataCrossValidSet(dataCrossValidSet* obj);
    void constructorDataInput(dataInput* obj);
    void newSetofDataInputAndConstruct(dataInput **obj,int num,int *flag);
    void constructSetOfDataInput(dataInput *obj,int num);
    void constructorLogReadFileDataSet(logReadFileDataSet* logReadFileDataSetObj);

    void makeDataCrossValidSetEmpty(dataCrossValidSet* obj);
    void makeDataInputEmpty(dataInput *obj);

    
    int initialLogReadFileDataSetArray(logReadFileDataSet** logReadFileDataSetObj,int numArray);
    void deallocateLogReadFileDataSetArray(logReadFileDataSet** logReadFileDataSetObj,int numArray);
    void loadFilePointerAndLineNumberToLogReadFileDataSetArray(logReadFileDataSet* logReadFileDataSetObj,int numArray,FILE **fp,int* numLine,simString *pFile);
    int addFilePointerAndLineNumberToLogReadFileDataSetArray(logReadFileDataSet* logReadFileDataSetObj,int numArray,FILE *fp,int numLine,simString *pFile);
    int checkSharedFileInLodReadFileDataSetArray(logReadFileDataSet* logReadFileDataSetObj,int arraySize,simString *str);
    
    void setInfo2DataCrossValidSet(dataCrossValidSet *obj,inputDataManager *objI);
    /*  DataCrossValidSet */
    void getTraingDataFromTaskObjToInputDataManager(taskMgr* taskMgrObj,inputDataManager *inputDataManagerObj);

    void printStatisDataLog(statisDataLog* statisDataLogObj,matrix_double* dataPrint);
    int validateBeforeConvertDataBytDataFormat(dataFormat* dataFormatObj,char *buff,statisDataLog *statisDataLogObj,int* listStr,int numEle);  
    int convertDataByDataFormat(inputDataManager *obj,int indexFile,int indexEx,statisDataLogElement *missLog);
  /* run learning task phase */
  int runAllTasksOfSvm(svmApp *app);
  
    /* timer */
    void timerStart(clock_t* t);
    float timeBreak(clock_t* t);
#endif
