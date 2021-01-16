#ifndef TASKMGR_H_
#define TASKMGR_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "svmApp.h"
#include "simReadXML.h"
#include "simMatChar.h"
#include "listChar.h"
#include "listInt.h"
#include "eleXMLNodeList.h"
#include "simStringList.h"
#include "simStringTree.h"
#include "convertDataType.h"
struct missingWord
{
    simString word;
/*<!-- STATICS_VAL detail -->
  <!-- -1 or no tag is ignore  (use value) -->
   <!-- 0 is mean, 1 is median, 2 mod,-->
   <!-- 3 random(double) , 4 random(int)  -->
*/
    char staticVal;
    char m_optStatic; /* opt in <STATICS_VAL>  -1 or no is set to be default.(0)
                        It is used when there are 2 or more values of mode or median
                        0 is mean them
                        1 is random choose*/
    char type; /* type 1 = double , 0 is int */
    char m_availVal; /* <!-- availValue = available value is using the value from input to replace a missing value-->
                        <!-- use is 1 not use 0 -->  */
    int indexDim;
    void* defVal;
};
struct attrbConvert
{
    int indexDim;
    char type; /* type 1 = double , 0 is int */
    /* create simStr AVL Tree  24 04 2016 13:30 */
    /* Update simStr to simStrTree 1 May 2016 14:30*/
    simStrTree m_wordT;
    /*
    simStrList words;
    void* value;
    int numOfVal;*/
};
/* compare rule*/
/*
attrbConvert
indexDim must be equal
numOfVal be equal
word must be equal
value must be equal
 
 missisngWord
 indexDim must be equal
 word must be equal
*/
struct convertMethod
{/* 0 string to int, 1 string to double, 2 map table, 3 random(int) 4 random(double) */
    int defaultMethod;
    /* update to AVL Tree 24 04 2016 13:30 */
    /* indexDim is the key of tree */

    /* update to AVL Tree 24 04 2016 13:30 */
    /* indexDim is the key of tree */
   /* struct attrbConvert *attrbW;
    int numOfAttrbW;
        struct missingWord *missW;
    int numOfMissW;
    */
    char m_isHasStatisticVal; /*   m_isHasStatisticVal
    0 is mean, 1 is median, 2 mod,--
    3 random(double) , 4 random(int)*/
    binaryTree m_attrbT;
    binaryTree m_missT;
};

struct dataFormat
{
   char type; /* type =0 --training set, type =1 -- test set */
   char io;
   int numSample;
   int lineStart;
   int orderAttrbStart;
   struct convertMethod convertor;
   delimiterSet delimeterFormat;
   simString filename;
};
struct inputDsMgr
{
    int numClass;
    int numAttrb;
    int numOut;
   /* simString sourcePath;*/
    simStrList trainFile;
    simStrList trainName;
    simStrList testFile;
    simStrList testName;
};
struct preprocParam 
{
    /* data selection */
    char isCrossValidation; /* if 0 ---> ignore this feature */
    int  fold;     /* current fold --> default = 10 */
    char includeTestFiles; /* 0 is only training samples, 1 including test set the remainings is to test */
    /* in case of brust force or genetic algorithm */
    int  minFold;  /* default = 0 */
    int  maxFold;  /* default =10 */
    int  stepNextFold;  /* next fold = old fold + stepNextFold in boundary (min-max) */

    /* normalization */
    char isScale;/* if 0 ---> ignore this feature */
    double scale_max;  
    double scale_min;
};
struct svmParam
{
    double constSoftM;  /* more than 0, 0 is hard margin , it is current constant Soft margin */
    
    /* in case of (brust force or genetic algor) and constSoftM != 0 */
    double minConstSoftM;
    double maxConstSoftM;
    double stepNextConst;
   
    int kernelType;     /* 1 = linear, 2 = polynomail, 3 = guessian */
    double kernelParam; /* if kernelType == 1 then this is ignored, if 2, this = power number, if 3, this = constant of guessian */

    /* in case of (brust force or genetic algor) and kernelType != 1 */
    double constKernelMin;
    double constKernelMax;
    double constKernelStep;
};
struct taskMgr
{
    simString name; 
    struct inputDsMgr inputFile;
   
    int numTrainEx; /* optional default = -1 = ignore*/
    int numTestEx;  /* optional default = -1 = ignore*/
    int typeMsvm;
    int svmType;   /* smo = 0, rch =1 */
    struct preprocParam prePro;
    struct svmParam svmPar;
    int numRound;
};
typedef struct inputDsMgr inputDsMgr;
typedef struct preprocParam  preprocParam;
typedef struct svmParam svmParam;
typedef struct taskMgr taskMgr;
typedef struct missingWord missingWord;
typedef struct attrbConvert attrbConvert;
typedef struct convertMethod convertMethod;
typedef struct dataFormat dataFormat;

    void constructorInputDsMgr(inputDsMgr* inpDsMgr);
    void constructorPreprocParam(preprocParam* preprocP);
    void constructorSvmParam(svmParam* svmPar); 
    void constructorTaskMgr(taskMgr* taskM);
    void constructorDataFormat(dataFormat* dataFormatObj);
    void constructorMissingWord(missingWord* missingWordObj);
    void constructorAttrbConvert(attrbConvert* attrbConvertObj);
    void constructorConvertMethod(convertMethod* convertMethodObj);

    int compAttrbTInConvMet(const void* a,const void *b);
    void deleKeyOfAttbAVLTInConvMet(void *obj,void *key);
    void constructAttrbAVLTInConvMet(binaryTree *obj);
    void delIntDatInSimTAttrbConvert(void *obj,void *dat);
    void delDoubleDatInSimTAttrbConvert(void *obj,void *dat);
    void copyIntDatInSimTAttrbConvert(void *lhs,void *rhs);
    void copyDoubleDatInSimTAttrbConvert(void *lhs,void *rhs);
    
    
    void constructMissAVLTInConvMet(binaryTree *obj);
    void deleKeyOfMissAVLTInConvMet(void *obj,void *key);
    int compMissTInConvMet(const void* a,const void *b);
    
    void copyMissingWord(missingWord* rhs,missingWord* lhs);
    void copyAttrbConvert(attrbConvert* rhs,attrbConvert* lhs);
    void copyConvertMethod(convertMethod* rhs,convertMethod* lhs);

    /* 0 = not equal, 1= equal, 2 rhs( attrb word num) >lhr, 3 rhs( attrb word num)<lhr */
    int compareMissingWord(missingWord* rhs,missingWord* lhs);
    int compareAttrbConvert(attrbConvert* rhs,attrbConvert* lhs);
    int compareConvertMethod(convertMethod* rhs,convertMethod* lhs);
    void makePreprocParamEmpty(preprocParam* preprocP);
    void makePreprocSvmParamEmpty(svmParam* svmPar);
    void makeTaskMgrEmpty(taskMgr* taskM); 
    
    void makeMissingWordEmpty(missingWord* missingWordObj);
    void makeAttrbConvertEmpty(attrbConvert* attrbConvertObj);
    void makeConvertMethodEmpty(convertMethod* convertMethodObj);
    void makeDataFormatEmpty(dataFormat* dataFormatObj);
    void makeInputDsMgrEmpty(inputDsMgr* inpDsMgr);
    
     /* get data from XML*/
    int getATaskFromFileByIndex(taskMgr* taskM,svmApp *app,int index);
    int getPreprocParamFromXML(preprocParam* preprocP,treeXML* root);
    int getSvmParamFromXML(svmParam* svmParamObj,treeXML* root);
    int getInputDsMgrFromXML(inputDsMgr* inputDsMgrObj,svmApp *app,simString *nameInput);
    int getDelimeterOfDataFormatFromXML(dataFormat* dataFormatObj,elementXML *root);
    int getMissingWordFromXML(missingWord* missingWordObj,elementXML *root);
    int swapMissingWord(missingWord* lhs,missingWord* rhs);
    int sortMissingWordSetFromLessToMore(missingWord *rhs,int numEle);
    int getAttrbConvertFromXML(attrbConvert* attrbConvertObj,elementXML *root);
    int swapAttrbConvert(attrbConvert* lhs,attrbConvert* rhs);
    int sortAttrbConvertFromLessToMore(attrbConvert* rhs,int numEle);
    int getConvertMethodFromXML(convertMethod* convertMethodObj,elementXML *root);
    int getDataFormatFromXML(dataFormat* dataFormatObj,const char *name,int numFeatureInp,int numFeatureOut);

    int checkDataFormatHasStatisRepresent(dataFormat* dataFormatObj);
    /* inputDsMgr */
    simString* getTrainingFileNameOfInputDsMgr(inputDsMgr* inputDsMgrObj,int index);
    simString* getTestingFileNameOfInputDsMgr(inputDsMgr* inputDsMgrObj,int index);     
    int getTrainingNumberFromInputDsMgr(inputDsMgr* inputDsMgrObj);
    int getTestingNumberFromInputDsMgr(inputDsMgr* inputDsMgrObj);
    
     /* taskMgr */
     char isIncludeTestSetsToCrossVal(taskMgr* taskMgrObj);
     int getTrainingNumberFromTaskMgr(taskMgr* taskMgrObj);
     int getTestingNumberFromTaskMgr(taskMgr* taskMgrObj);
     int getTrainingFileNumberFromTaskMgr(taskMgr* taskMgrObj);
     int getTestingFileNumberFromTaskMgr(taskMgr* taskMgrObj);
     simString* getTrainingFileNameOfTaskMgr(taskMgr* taskMgrObj,int index);
     simString* getTestingFileNameOfTaskMgr(taskMgr* taskMgrObj,int index);
     int getTheNumberOfClassFromTaskMgr(taskMgr* taskMgrObj);
     int getTheNumberOfFeatureInputFromTaskMgr(taskMgr* taskMgrObj);
     int getTheNumberOfFeatureOutputFromTaskMgr(taskMgr* taskMgrObj);
     int getMaxFoldInTaskMgr(taskMgr *obj);
     int getMinFoldInTaskMgr(taskMgr *obj);
     int getStepFoldInTaskMgr(taskMgr *obj);
  /* get Data From file*/
    int  getNumOfInputFromInputMgrFile(svmApp *app); /* use when the file is available */
    simString getNameAnInputFile(svmApp *app,int index);
    simString getNameAnInputFileWithName(svmApp *app,vector_char *name);
    simString getNameAnInputFileWithsimStrName(svmApp *app,simString *name);
    int getNumAPathTestInput(simString *aPath);
    simString getAPathTestInput(simString *abPath,simString *aPath,int index);
    void getPathTestInputList(simString *abPath,simString *aPath,simStrList *listname);
    int getNumAPathTrainInput(simString *aPath);
    simString getAPathTrainInput(simString *abPath,simString *aPath,int index);
    void getPathTrainInputList(simString *abPath,simString *aPath,simStrList *listname);
    void getListInputFile(svmApp *app,simStrList *listName);
 
    
    int getNumOfTaskFromTaskMgrFile(svmApp *app);
    simString getNameATaskFile(svmApp *app,int index);
    int getUseStatusATaskFile(svmApp *app,int index);
    void getListTaskFile(svmApp *app,simStrList *listName);
    int checkATaskPath(svmApp *app,simString *tpath);
    int checkATaskPathByIndex(svmApp *app,int index);

    /* handle ds_mgr.xml  */
    int getNumClassInDsMgrWithNameInp(svmApp *app,simString *nameInput);
    int getNumClassInDsMgr(simString *aPath);
    int getNumAttrbInDsMgrWithNameInp(svmApp *app,simString *nameInput);
    int getNumAttrbInDsMgr(simString *aPath);
    simString getCurrentPathInDsMgr(simString *abPath,simString *aPath);
    simString getCurrentPathInDsMgrWithNameInp(svmApp *app,simString *nameInput);
    simString getSourcePathInDsMgr(simString *abPath,simString *aPath);
    simString getSourcePathInDsMgrWithNameInp(svmApp *app,simString *nameInput);
  
   /* convertMethod method*/
   int getDataFromAttrbTableOfConvertMethod(convertMethod* obj,const char* buff,int indexAttrb,char *staticVal,double  *valReal);
   int getDataFromAttrbTableOfMissingWord(convertMethod* obj,const char* buff,int indexAttrb,char *staticVal,double  *valReal);
   int getDataFromAttrbTableOfAttrbConvert(convertMethod* obj,const char* buff,int indexAttrb,double  *valReal);
   attrbConvert *searchIndexDimAttrbInConvertMet(convertMethod* obj,int indexDim);
   missingWord *searchIndexDimMissInConvertMet(convertMethod* obj,int indexDim);
    /* dataFormat  method*/
    int assignValueToVectorDByDataFormat(dataFormat* obj,double* data,double* data1,int indexAttrb);
    /* end of dataFormat method*/
   void printMissingWord(missingWord* missingWordObj);
    void printAttrbConvert(attrbConvert* attrbConvertObj);
    void printConvertMethod(convertMethod* convertMethodObj);
    void printDataFormat(dataFormat* dataFormatObj);
 
    /*print detail */
    void printInputDsMgr(inputDsMgr* inputMgrObj);

    void printPreprocParam(preprocParam* preprocObj);
    void printSvmParam(svmParam* svmParamObj);
    void printTaskMgr(taskMgr* taskMgrObj);
#endif /* end taskMgr.h*/