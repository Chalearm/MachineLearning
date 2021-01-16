#include "taskMgr.h"

#define NAME_INPUT_FAILED -2
/* define Tage XML */
#define DEF_FILE_NAME                     "FILE_NAME"
#define DEF_CURRENT_PATH                  "CURRENT_PATH"
#define DEF_NAME_ATTRB                    "name"
#define DEF_TASK                          "TASK"
#define DEF_use                           "use"
#define DEF_TRAINING_FILE                 "TRAINING_FILE"
#define DEF_TESTING_FILE                  "TESTING_FILE"
#define DEF_NAME                          "NAME"
#define DEF_FILE                          "FILE"
#define DEF_PATH                          "PATH"
#define DEF_NUM_CLASS                     "NUM_CLASS"
#define DEF_NUM_ATTRB                     "NUM_ATTRB"
#define DEF_NUM_ATTRB_OUTPUT              "NUM_ATTRB_OUTPUT"

/*  In task file*/
#define DEF_THE_NUMBER_OF_TRAINING_EX     "THE_NUMBER_OF_TRAINING_EX"
#define DEF_THE_NUMBER_OF_TESTING_EX      "THE_NUMBER_OF_TESTING_EX"
#define DEF_DATA_SET_PATH                 "DATA_SET_PATH"
#define DEF_TYPE_MSVM                     "TYPE_MSVM"
#define DEF_SVM_TYPE                      "SVM_TYPE"
#define DEF_ROUND                         "ROUND"

#define DEF_on                            "on"
#define DEF_CROSS_VALIDATE                "CROSS_VALIDATE"
#define DEF_FOLD                          "FOLD"
#define DEF_MIN_FOLD                      "MIN_FOLD"
#define DEF_MAX_FOLD                      "MAX_FOLD"
#define DEF_STEP_NEXT_FOLD                "STEP_NEXT_FOLD"
#define DEF_INCLUDE_TEST_FILES            "INCLUDE_TEST_FILES"

#define DEF_SCALE                         "SCALE"
#define DEF_MAX                           "MAX"
#define DEF_MIN                           "MIN"

#define DEF_SOFTMARGIN                    "SOFTMARGIN"         
#define DEF_CONST_SOFT_M                  "CONST_SOFT_M"
#define DEF_MIN_CONST_SOFT_M              "MIN_CONST_SOFT_M"
#define DEF_MAX_CONST_SOFT_M              "MAX_CONST_SOFT_M"
#define DEF_STEP_CONST_SOFT_M             "STEP_CONST_SOFT_M"
#define DEF_KERNEL_FUNCTION               "KERNEL_FUNCTION"
#define DEF_no                            "no"
#define DEF_CONSTANT                      "CONSTATN"
#define DEF_CONST_MIN                     "CONST_MIN"
#define DEF_CONST_MAX                     "CONST_MAX"
#define DEF_CONST_STEP                    "CONST_STEP"

/* in traning/testing file*/
#define DEF_NAME_FILE                     "NAME_FILE"
#define DEF_NUM_SAMPLE                    "NUM_SAMPLE"
#define DEF_CONVERT_METHOD                "CONVERT_METHOD"
#define DEF_METHOD                        "METHOD"
#define DEF_MISSING                       "MISSING"
#define DEF_MISSING_WORD                  "MISSING_WORD"
#define DEF_STATICS_VAL                   "STATICS_VAL"
#define DEF_DEFAULT_VAL                   "DEFAULT_VAL"
#define DEF_ATTRB_NUM                     "ATTRB_NUM"
#define DEF_ATTRB                         "ATTRB"
#define DEF_WORD                          "WORD"
#define DEF_value                         "value"
#define DEF_method                        "method"
#define DEF_type                          "type"
#define DEF_available_val                 "availValue"
#define DEF_opt                           "opt"
#define DEF_io                            "io"
#define DEF_SYMBOL                        "SYMBOL"
#define DEF_LINE_START                    "LINE_START"
#define DEF_ORDER_ATTRB_START             "ORDER_ATTRB_START"
#define DEF_IO_START                      "IO_START"
#define DEF_START_OUT                     "START_OUT"
#define DEF_STOP_OUT                      "STOP_OUT"
#define DEF_START_INP                     "START_INP"
#define DEF_STOP_INP                      "STOP_INP"
void constructorInputDsMgr(inputDsMgr* inpDsMgr)
{   
    if(inpDsMgr != NULL)
    {
        inpDsMgr->numClass =0;
        inpDsMgr->numAttrb =0;
        inpDsMgr->numOut =0;
        /*initialSimString(&(inpDsMgr->sourcePath));*/
        initialSimStrList(&(inpDsMgr->trainFile));
        initialSimStrList(&(inpDsMgr->trainName));
        initialSimStrList(&(inpDsMgr->testFile));
        initialSimStrList(&(inpDsMgr->testName));
    }
    else
    {
        /* do nothing */
    }
}

void constructorPreprocParam(preprocParam* preprocP)
{
    if(preprocP != NULL)
    {
        preprocP->isCrossValidation =0;
        preprocP->includeTestFiles =0;
        preprocP->fold =0;
        preprocP->minFold = 0;
        preprocP->maxFold = 0; 
        preprocP->stepNextFold = 0;
        preprocP->scale_max = 0;
        preprocP->scale_min = 0;
        preprocP->isScale = 0;
    }
    else
    {
        /* do nothing */
    }
}
void constructorSvmParam(svmParam* svmPar)
{
    if(svmPar != NULL)
    {
        svmPar->constSoftM=0.0;
        svmPar->minConstSoftM =0.0;
        svmPar->maxConstSoftM =0.0;
        svmPar->stepNextConst =0.0;
        svmPar->constKernelMin = 0.0;
        svmPar->constKernelMax = 0.0;
        svmPar->constKernelStep= 0.0;
        svmPar->kernelType =0; 
        svmPar->kernelParam=0.0;
    }
    else
    {
        /* do nothing */
    }
}
void constructorTaskMgr(taskMgr* taskM)
{
    if(taskM != NULL)
    {
        initialSimString(&(taskM->name)); 
        constructorInputDsMgr(&(taskM->inputFile));
        taskM->numTrainEx = -1; /* optional default = -1 = ignore*/
        taskM->numTestEx =-1;  /* optional default = -1 = ignore*/
        taskM->typeMsvm =0;
        taskM->svmType =0;   /* smo = 0, rch =1 */
        constructorPreprocParam(&(taskM->prePro));
        constructorSvmParam(&(taskM->svmPar));
        taskM->numRound =0;
    }
    else
    {
        /* do nothing */
    }
}
void constructorDataFormat(dataFormat* dataFormatObj)
{
    if(dataFormatObj!=NULL)
    {
        dataFormatObj->io=2;
        dataFormatObj->type =0; /* type =0 --training set, type =1 -- test set */
        dataFormatObj->numSample=0;
        dataFormatObj->lineStart=0;
        dataFormatObj->orderAttrbStart=0;
        constructorConvertMethod(&(dataFormatObj->convertor));
        constructorDSet(&(dataFormatObj->delimeterFormat));
        initialSimString(&(dataFormatObj->filename));
    }
    else
    {
        /* do nothing */
    }
}

void constructorMissingWord(missingWord* missingWordObj)
{
    if(missingWordObj != NULL)
    {
        initialSimString(&(missingWordObj->word));
        missingWordObj->staticVal = -1;
        missingWordObj->m_optStatic = 0;
        missingWordObj->defVal = NULL;
        missingWordObj->type=0;
        missingWordObj->m_availVal=0;
    }
    else
    {
        /* do nothing */
    }
}
void constructorAttrbConvert(attrbConvert* attrbConvertObj)
{
    if(attrbConvertObj != NULL)
    {
        attrbConvertObj->indexDim =-1;
        attrbConvertObj->type=0; /* type 1 = double , 0 is int */
        /*initialSimStrList(&(attrbConvertObj->words));*/
        /* update 1 May 2016 : 14:30*/
        initialSimStrT(&(attrbConvertObj->m_wordT),NULL,NULL);
        /*
        attrbConvertObj->value = NULL;
        attrbConvertObj->numOfVal = 0;*/
    }
    else
    {
        /* do nothing */
    }
}
void constructorConvertMethod(convertMethod* convertMethodObj)
{
    if(convertMethodObj != NULL)
    {
        convertMethodObj->defaultMethod =1;
        convertMethodObj->m_isHasStatisticVal =0;/*
        convertMethodObj->missW = NULL;
        convertMethodObj->attrbW = NULL;
        convertMethodObj->numOfAttrbW=0;
        convertMethodObj->numOfMissW=0;*/
        constructAttrbAVLTInConvMet(&(convertMethodObj->m_attrbT));
        constructMissAVLTInConvMet(&(convertMethodObj->m_missT));
    }
    else
    {
        /* do nothing */
    }
}


int compAttrbTInConvMet(const void* a,const void *b)
{
    int res =UN_DEFINE;
    struct attrbConvert **atba=NULL,**atbb=NULL;
    if((a!=NULL)&&(b!=NULL))
    {
        atba = ((struct attrbConvert**)a);
        atbb = ((struct attrbConvert**)b);
        if((*atba!=NULL)&&(*atbb!=NULL))
        {
            if((*atba)->indexDim ==(*atbb)->indexDim)
            {
                res = EQUAL_DEFINE;
            }
            else if((*atba)->indexDim >(*atbb)->indexDim)
            {
                res = MORE_DEFINE;
            }
            else if((*atba)->indexDim <(*atbb)->indexDim)
            {
                
                res = LESS_DEFINE;
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
    }
    else
    {
        /* do nothing */
    }
    return res;
}

void deleKeyOfAttbAVLTInConvMet(void *obj,void *key)
{
    void **p = (void**)key;
    if(*p!=NULL)
    { 
        makeAttrbConvertEmpty(*p);
        free(*p);
    }
    else
    {
        /* do nothing */
    }
}
void constructAttrbAVLTInConvMet(binaryTree *obj)
{
    if(obj != NULL)
    {
        /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
        constructAvlTree((void*)obj,0,"custom type 2",0,sizeof(struct attrbConvert)); 
        setDelKeyAndDelDataAndCompFnForAvlTree(obj,deleKeyOfAttbAVLTInConvMet,NULL,compAttrbTInConvMet);
    }
    else
    {
        /* do nothing */
    }
}
void delIntDatInSimTAttrbConvert(void *obj,void *dat)
{
    int **pi = (int**)dat;
    if(pi == NULL)
    {
        /* do nothing */
    }
    else if(*pi !=NULL)
    {
        free(*pi);
        *pi = NULL;
    }
    else
    {
        /* do nothing */
    }
}
void delDoubleDatInSimTAttrbConvert(void *obj,void *dat)
{
    double **pi = (double**)dat;
    if(pi == NULL)
    {
        /* do nothing */
    }
    else if(*pi !=NULL)
    {
        free(*pi);
        *pi = NULL;
    }
    else
    {
        /* do nothing */
    }
}
void copyIntDatInSimTAttrbConvert(void *lhs,void *rhs)
{
    int *pInt =NULL;
    void *pI1=NULL;
    if((lhs!=NULL)&&(rhs!=NULL))
    {
        pInt = (int*)getDataFromAvlNode(rhs);
        pI1 = (int*)malloc(sizeof(int));
        if((pI1!=NULL)&&(pInt!=NULL))
        {
            *((int*)pI1) = *pInt;
        }
        else
        {
            /* do nothing */
        }
        setDataToAvlNode(lhs,&pI1);
    }
    else
    {
        /* do nothing*/
    }
}
void copyDoubleDatInSimTAttrbConvert(void *lhs,void *rhs)
{
    double *pDoub =NULL;
    void *pD1=NULL;
    if((lhs!=NULL)&&(rhs!=NULL))
    {
        pDoub = (double*)getDataFromAvlNode(rhs);
        pD1 = (double*)malloc(sizeof(double));
        if((pD1!=NULL)&&(pDoub!=NULL))
        {
            *((double*)pD1) = *pDoub;
        }
        else
        {
            /* do nothing */
        }
        setDataToAvlNode(lhs,&pD1);
    }
    else
    {
        /* do nothing*/
    }
}

void constructMissAVLTInConvMet(binaryTree *obj)
{
    if(obj != NULL)
    {
        /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
        constructAvlTree((void*)obj,0,"custom type 2",0,sizeof(struct missingWord)); 
        setDelKeyAndDelDataAndCompFnForAvlTree(obj,deleKeyOfMissAVLTInConvMet,NULL,compMissTInConvMet);
    }
    else
    {
        /* do nothing */
    }
}
void deleKeyOfMissAVLTInConvMet(void *obj,void *key)
{
    void **p = (void**)key;
    if(*p!=NULL)
    { 
        makeMissingWordEmpty(*p);
        free(*p);
    }
    else
    {
        /* do nothing */
    }
}
int compMissTInConvMet(const void* a,const void *b)
{
    int res =UN_DEFINE;
    struct missingWord **atba=NULL,**atbb=NULL;
    if((a!=NULL)&&(b!=NULL))
    {
        atba = ((struct missingWord**)a);
        atbb = ((struct missingWord**)b);
        if((*atba!=NULL)&&(*atbb!=NULL))
        {
            if((*atba)->indexDim ==(*atbb)->indexDim)
            {
                res = EQUAL_DEFINE;
            }
            else if((*atba)->indexDim >(*atbb)->indexDim)
            {
                res = MORE_DEFINE;
            }
            else if((*atba)->indexDim <(*atbb)->indexDim)
            {
                
                res = LESS_DEFINE;
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
    }
    else
    {
        /* do nothing */
    }
    return res;
}
    
void copyMissingWord(missingWord* rhs,missingWord* lhs)
{
    int *pInt=NULL;
    double *pDouble = NULL;
    if((rhs != NULL)&&(lhs != NULL)&&(rhs != lhs))
    {
        makeMissingWordEmpty(rhs);
        copySimStr(&(rhs->word),&(lhs->word));
        rhs->staticVal = lhs->staticVal;
        rhs->m_optStatic = lhs->m_optStatic;
        rhs->m_availVal = lhs->m_availVal;
        rhs->type = lhs->type;
        rhs->indexDim = lhs->indexDim;
        if(rhs->type ==1)
        {
            rhs->defVal = (double*)malloc(sizeof(double));
        }
        else if(rhs->type ==0)
        {
            rhs->defVal = (int*)malloc(sizeof(int));
        }
        else
        {
            /* do nothing */
        }
        if(rhs->defVal != NULL)
        {
            if(rhs->type == 0)
            {
                pInt = rhs->defVal;
                *pInt = *((int*)lhs->defVal);
             }
             else if(rhs->type ==1)
             {
                pDouble = rhs->defVal;
                *pDouble =  *((double*)lhs->defVal);
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
    }
    else
    {
        /* do nothing */
    }
}
void copyAttrbConvert(attrbConvert* rhs,attrbConvert* lhs)
{
    /*
    int index =0;
    int *pInt=NULL;
    double *pDouble = NULL;
    int *pInt2=NULL;
    double *pDouble2 = NULL;
    int num = 0;*/
    if((rhs != NULL)&&(lhs != NULL)&&(rhs != lhs))
    {
        makeAttrbConvertEmpty(rhs);
        rhs->type = lhs->type;
        rhs->indexDim = lhs->indexDim;
        /*
        num = lhs->numOfVal;
        copySimStrList(&(rhs->words),&(lhs->words));
        if(rhs->type ==1)
        {
            rhs->value = (double*)malloc(num*sizeof(double));
        }
        else if(rhs->type ==0)
        {
            rhs->value = (int*)malloc(num*sizeof(int));
        }
        else
        {
             
        }
        if(rhs->value != NULL)
        {
            rhs->numOfVal = num;
            if(rhs->type == 0)
            {
                pInt = rhs->value;
                pInt2= lhs->value;
                for(index=0;index<num;index++)
                {
                    pInt[index]=pInt2[index];
                }
             }
             else if(rhs->type ==1)
             {
                pDouble = rhs->value;
                pDouble2 = lhs->value;
                for(index=0;index<num;index++)
                {
                    pDouble[index]=pDouble2[index];
                }
             }
             else
             { 
             }
        }
        else
        { 
        }*/
    }
    else
    {
        /* do nothing */
    }
}
void copyConvertMethod(convertMethod* rhs,convertMethod* lhs)
{
    /*int num2=0;
    int index=0;
    int num=0;*/
    if((rhs != NULL)&&(lhs != NULL)&&(rhs != lhs))
    {
        /*
        num = lhs->numOfMissW;
        num2 = lhs->numOfAttrbW;*/
        makeConvertMethodEmpty(rhs);
        rhs->defaultMethod =lhs->defaultMethod;
         /*  rhs->missW = (missingWord*)malloc(sizeof(missingWord)*num);
        rhs->attrbW = (attrbConvert*)malloc(sizeof(attrbConvert)*num2); 
        if(rhs->missW != NULL)
        {
            rhs->numOfMissW = num;
            for(index=0;index<num;index++)
            {
                constructorMissingWord(&(rhs->missW[index]));
                copyMissingWord(&(rhs->missW[index]),&(lhs->missW[index]));
            }
        }
        else
        {
            
        }
     
        if(rhs->attrbW != NULL)
        {
            rhs->numOfAttrbW = num2;
            for(index=0;index<num;index++)
            {
                constructorAttrbConvert(&(rhs->attrbW[index]));
                copyAttrbConvert(&(rhs->attrbW[index]),&(lhs->attrbW[index]));
            }
        }
        else
        { 
        }*/
    }
    else
    {
        /* do nothing */
    }
}


/* 0 = not equal, 1= equal, 2 rhs( attrb word num) >lhr, 3 rhs( attrb word num)<lhr */
int compareMissingWord(missingWord* rhs,missingWord* lhs)
{
    int res =0;
    double val1=0.0,val2=0.0;
    int iVal1=0,iVal2=0;
    if(rhs == lhs)
    {
        res = 1;
    }
    else if((rhs != NULL) && (lhs != NULL))
    {
        res = (rhs->indexDim == lhs->indexDim);
        res &= compareSimString(&(rhs->word),&(lhs->word));
        if(res ==1)
        {
            if((rhs->staticVal > lhs->staticVal))
            {
                res =2;
            }
            else if((rhs->staticVal < lhs->staticVal))
            {
                res =3;
            }
            else if(rhs->staticVal == lhs->staticVal)
            {
                if(rhs->type > lhs->type)
                {
                    if((rhs->staticVal  ==3)&&(rhs->type ==1))
                    {
                        val1 = *((double*)(rhs->defVal));
                        val2 = (double)(*((int*)(lhs->defVal)));
                        if(val1 == val2)
                        {
                            res=2;
                        }
                        else
                        {
                            res=0;
                        }
                    }
                    else
                    {
                        res =2;
                    }
                }
                else if(rhs->type < lhs->type)
                {
                    if((rhs->staticVal  ==3)&&(rhs->type ==0))
                    {
                        iVal1 = *((int*)(rhs->defVal));
                        iVal2= (int)(*((double*)(lhs->defVal)));
                        if(iVal1 == iVal2)
                        {
                            res=3;
                        }
                        else
                        {
                            res=0;
                        }
                    }
                    else
                    {
                        res =3;
                    }
                }
                else if(rhs->type == lhs->type)
                {
                    if((rhs->staticVal  ==3)&&(rhs->type ==0))
                    {
                        iVal1 = *((int*)(rhs->defVal));
                        iVal2 = *((int*)(lhs->defVal));
                        if(iVal1 == iVal2)
                        {
                            res=1;
                        }
                        else
                        {
                            res=0;
                        }
                    }
                    else if((rhs->staticVal  ==3)&&(rhs->type ==1))
                    {
                        val1 = *((double*)(rhs->defVal));
                        val2 = *((double*)(lhs->defVal));
                        if(val1 == val2)
                        {
                            res=1;
                        }
                        else
                        {
                            res=0;
                        }
                    }
                    else
                    {
                        res =1;
                    }
                }
                else
                {
                    res =0;
                }
            }
            else
            {
                 res =0;
            }
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int compareAttrbConvert(attrbConvert* rhs,attrbConvert* lhs)
{
    int res=0;
    /*
    int index=0;
    int num,num2;
    int *pInt1,*pInt2;
    double *pDouble1,*pDouble2;*/
    if(rhs == lhs)
    {
        res =1;
    }
    else if((rhs!= NULL) && (lhs != NULL))
    {
        res = (rhs->indexDim == lhs->indexDim);
        /*
        num = getNumNodeSimStrList(&(rhs->words));
        num2 = getNumNodeSimStrList(&(lhs->words));
        res &= (num==num2);
        res &= (rhs->type == lhs->type);
        res &= (rhs->numOfVal ==num2);
        res &=  (rhs->numOfVal == lhs->numOfVal); 
        res &= compareSimStrList(&(rhs->words),&(lhs->words));
       
        if(res ==1)
        {
            if(rhs->type ==0)
            {
                pInt1 =(int*)(rhs->value);
                pInt2 =(int*)(lhs->value);
                for(index=0;index<num;index++)
                {
                    res &= (pInt1[index] ==  pInt2[index]);
                }
             }
             else
             {
                pDouble1 =(double*)(rhs->value);
                pDouble2 =(double*)(lhs->value);
                for(index=0;index<num;index++)
                {
                    res &= (pDouble1[index] ==  pDouble2[index]);
                }
             }
        }
        else
        { 
        }
        */
    }
    else
    {
        /* do nothing */
    }
    return res;
}
    /* 0 = not equal, 1= equal, 2 rhs( attrb word num) >lhr, 3 rhs( attrb word num)<lhr */
int compareConvertMethod(convertMethod* rhs,convertMethod* lhs)
{
    int res=0;/*
    int res2=0;
    int index=0;
    int index2=0;
    int num = 0;
    int num2 = 0;
    convertMethod *aC= NULL;
    convertMethod *bC = NULL;
    int *score =NULL;*/
    /* score */
    int scoreLsh =0;
    int scoreRsh =0;
    if(lhs == rhs)
    {
        res = 1;
    }
    else if((lhs != NULL) &&(rhs != NULL))
    {
        /*
        num = rhs->numOfAttrbW;
        num2 = lhs->numOfAttrbW;*/
        if(rhs->defaultMethod ==lhs->defaultMethod)
        {
            res =1;
        }
        else if((rhs->defaultMethod == 2)&&(lhs->defaultMethod != 2))
        {
             scoreRsh++;
        }
        else if((rhs->defaultMethod != 2)&&(lhs->defaultMethod == 2))
        {
             scoreLsh++;
        }        
        else if((rhs->defaultMethod == 0)&&(lhs->defaultMethod == 1))
        {
             scoreLsh++;
        }        
        else if((rhs->defaultMethod == 1)&&(lhs->defaultMethod == 0))
        {
             scoreRsh++;
        }        
        else if((rhs->defaultMethod == 3)&&(lhs->defaultMethod == 4))
        {
             scoreLsh++;
        }        
        else if((rhs->defaultMethod == 4)&&(lhs->defaultMethod == 3))
        {
             scoreRsh++;
        }        
        else if((rhs->defaultMethod < 2)&&(lhs->defaultMethod >2))
        {
             scoreRsh++;
        }        
        else if((lhs->defaultMethod < 2)&&(rhs->defaultMethod >2))
        {
             scoreLsh++;
        }
        else
        {
            /* do nothing */
        }
        /*
        if(num2>num)
        {
            aC = rhs;
            bC = lhs;
            score = &scoreLsh;
        }   
        else if(num2<num)
        {            
            aC = lhs;
            bC = rhs;
            score = &scoreRsh;
        }
        
        for(index=0;index<num;index++)
        {
            for(index2=0;index2<num2;index2++)
            {
                if(compareAttrbConvert(&(aC->attrbW[index]),&(bC->attrbW[index2]))==1)
                {
                    res2  =1;
                    index2 = num2;
                }
                else
                {
                    res2 =0;
                }
            }
            if(res2==0)
            {
                index = num;
            }
            else
            { 
            }
        } 
        *score = *score+((num2 != num) &&(res2==1));
        res &= ((num2 == num) && (res2==1));*/
        
    }
    else
    {
        /* do nothing */
    }
    if(scoreLsh >scoreRsh)
    {
        res =3;
    }
    else if(scoreLsh < scoreRsh)
    {
        res =2;
    }
    else
    {
        /* do nothing */
    }
    return res;
}


void makePreprocParamEmpty(preprocParam* preprocP)
{
    if(preprocP != NULL)
    {
        preprocP->isCrossValidation =0;
        preprocP->includeTestFiles =0;
        preprocP->fold =0;
        preprocP->minFold = 0;
        preprocP->maxFold = 0; 
        preprocP->stepNextFold = 0;
        preprocP->isScale = 0;
        preprocP->scale_max = 0;
        preprocP->scale_min = 0;
    }
    else
    {
        /* do nothing */
    }
}
void makePreprocSvmParamEmpty(svmParam* svmPar)
{
    if(svmPar != NULL)
    {
        svmPar->constSoftM =0.0;
        svmPar->minConstSoftM =0.0;
        svmPar->maxConstSoftM =0.0;
        svmPar->stepNextConst =0.0;
        svmPar->constKernelMin = 0.0;
        svmPar->constKernelMax = 0.0;
        svmPar->constKernelStep= 0.0;
        svmPar->kernelType =0.0; 
        svmPar->kernelParam=0.0;
    }
    else
    {
        /* do nothing */
    }
}
void makeTaskMgrEmpty(taskMgr* taskM)
{
    if(taskM != NULL)
    {
        destructSimString(&(taskM->name)); 
        makeInputDsMgrEmpty(&(taskM->inputFile));
        taskM->numTrainEx = -1; /* optional default = -1 = ignore*/
        taskM->numTestEx =-1;  /* optional default = -1 = ignore*/
        taskM->typeMsvm =0;
        taskM->svmType =0;   /* smo = 0, rch =1 */
        makePreprocSvmParamEmpty(&(taskM->svmPar));
        makePreprocParamEmpty(&(taskM->prePro));
        taskM->numRound =0;
    }
    else
    {
        /* do nothing */
    }  
}
void makeMissingWordEmpty(missingWord* missingWordObj)
{
    if(missingWordObj != NULL)
    {
        destructSimString(&(missingWordObj->word));
        missingWordObj->staticVal = -1;
        missingWordObj->m_optStatic = 0;
        if(missingWordObj->defVal!=NULL)
        {
            if(missingWordObj->type==1)
            {
                free((double*)missingWordObj->defVal);
                missingWordObj->defVal = NULL;
            }
            else if(missingWordObj->type==0)
            {
                free((int*)missingWordObj->defVal);
                missingWordObj->defVal = NULL;
            }
            else
            {
                /* do nothing*/
            }
        }
        else
        {
            /* do nothing */
        }
        missingWordObj->type=0; 
        missingWordObj->m_availVal=0; 
        missingWordObj->indexDim=-1; 
    }
    else
    {
        /* do nothing  */
    }
}
void makeAttrbConvertEmpty(attrbConvert* attrbConvertObj)
{
    if(attrbConvertObj!=NULL)
    {
        attrbConvertObj->indexDim = -1;
       /* destructorSimStrList(&(attrbConvertObj->words));*/
        /* update 1 May 2016 : 14:30*/
        destructorSimStrT(&(attrbConvertObj->m_wordT));
        /*
        attrbConvertObj->numOfVal=0;
        if(attrbConvertObj->value!=NULL)
        {
            if(attrbConvertObj->type==1)
            {
                free((double*)attrbConvertObj->value);
                attrbConvertObj->value = NULL;
            }
            else if(attrbConvertObj->type==0)
            {
                free((int*)attrbConvertObj->value);
                attrbConvertObj->value = NULL;
            }
            else
            { 
            }
        }
        else
        {
             
        }*/
    }
    else
    {
        /* do nothing*/
    }
    
}

void makeConvertMethodEmpty(convertMethod* convertMethodObj)
{
    if(convertMethodObj !=NULL)
    {
        convertMethodObj->defaultMethod =1;
        convertMethodObj->m_isHasStatisticVal =0;
        clearBinaryTree(&(convertMethodObj->m_attrbT));
        clearBinaryTree(&(convertMethodObj->m_missT));
        /*
    int index=0;
    int num=0;
        if(convertMethodObj->missW !=NULL)
        {
            num = convertMethodObj->numOfMissW;
            for(index=0;index<num;index++)
            {
                makeMissingWordEmpty(&(convertMethodObj->missW[index]));
            }
            free(convertMethodObj->missW);
            convertMethodObj->missW = NULL;
            convertMethodObj->numOfMissW=0;
        }
        else
        {
            
        }*/
        /*
        if(convertMethodObj->attrbW !=NULL)
        {
            num = convertMethodObj->numOfAttrbW;
            for(index=0;index<num;index++)
            {
                makeAttrbConvertEmpty(&(convertMethodObj->attrbW[index]));
            }
            free(convertMethodObj->attrbW);
            convertMethodObj->attrbW = NULL;
            convertMethodObj->numOfAttrbW=0;
        }
        else
        { 
        }*/
    }
}

void makeDataFormatEmpty(dataFormat* dataFormatObj)
{
    if(dataFormatObj != NULL)
    {
        dataFormatObj->io =2;
        dataFormatObj->type = 0; /* type =0 --training set, type =1 -- test set */
        dataFormatObj->numSample =0;
        dataFormatObj->lineStart =0;
        dataFormatObj->orderAttrbStart =0;
        makeConvertMethodEmpty(&(dataFormatObj->convertor));
        constructorDSet(&(dataFormatObj->delimeterFormat));
        destructSimString(&(dataFormatObj->filename));
    }
    else
    {
        /* do nothing */
    }
}
void makeInputDsMgrEmpty(inputDsMgr* inpDsMgr)
{
    if(inpDsMgr != NULL)
    {
        inpDsMgr->numClass =0;
        inpDsMgr->numAttrb =0;
        inpDsMgr->numOut =0;
      /*  destructSimString(&(inpDsMgr->sourcePath));*/
        destructorSimStrList(&(inpDsMgr->trainFile));
        destructorSimStrList(&(inpDsMgr->trainName));
        destructorSimStrList(&(inpDsMgr->testFile));
        destructorSimStrList(&(inpDsMgr->testName));
    }
    else
    {
        /* do nothing */
    }
}

    
     /* get data from XML*/

int getATaskFromFileByIndex(taskMgr* taskM,svmApp *app,int index)
{
    int res =0;
    treeXML tXML;
    simString aTaskPath;
    simString inputPath;
    initialSimString(&aTaskPath);
    initialSimString(&inputPath);
    if(taskM != NULL && app !=NULL && index >=0)
    {
        makeTaskMgrEmpty(taskM);
        aTaskPath = getNameATaskFile(app,index);
        res = getSourceToTreeXML(&tXML,aTaskPath.data);
        if(res ==1)
        {
            res = getValueOfFirstChildEle2Var(tXML.root,DEF_NAME,"0",(void*)&(taskM->name),0x080); /*simString */
            res &= getValueOfFirstChildEle2Var(tXML.root,DEF_THE_NUMBER_OF_TRAINING_EX,"-1",(void*)&(taskM->numTrainEx),0x010); /*int */
            res &= getValueOfFirstChildEle2Var(tXML.root,DEF_THE_NUMBER_OF_TESTING_EX,"-1",(void*)&(taskM->numTestEx),0x010); /*int */
            res &= getValueOfFirstChildEle2Var(tXML.root,DEF_TYPE_MSVM,"0",(void*)&(taskM->typeMsvm),0x010); /*int */
            res &= getValueOfFirstChildEle2Var(tXML.root,DEF_SVM_TYPE,"0",(void*)&(taskM->svmType),0x010); /*int */
            res &= getValueOfFirstChildEle2Var(tXML.root,DEF_ROUND,"0",(void*)&(taskM->numRound),0x010); /*int */
            res &= getValueOfFirstChildEle2Var(tXML.root,DEF_DATA_SET_PATH,"",(void*)&inputPath,0x080); /*simString */
        
        }
        else
        {
            /* do nothing*/
        }
        if(res==1)
        {
            res = getPreprocParamFromXML(&(taskM->prePro),&tXML);
        }
        else
        {
            /* do nothing */
        }
        if(res==1)
        {
            res = getSvmParamFromXML(&(taskM->svmPar),&tXML);
        }
        else
        {
            /* do nothing */
        }
        if(res==1)
        {
            res = getInputDsMgrFromXML(&(taskM->inputFile),app,&inputPath);
        }
        else
        {
            /* do nothing */
        }
        destructorTreeXML(&tXML);

    }
    else
    {
        /* do nothing */
    }
    destructSimString(&aTaskPath);
    destructSimString(&inputPath);
    return res;
}
/* use in getATaskFromFileByIndex function and root has had tree */
int getPreprocParamFromXML(preprocParam* preprocP,treeXML* root)
{
    int res=0;
    elementXML *pEle = NULL;
    if(preprocP != NULL && root != NULL)
    {
        res  = getAttrbValueOfFirstChildEle2Var(root->root,DEF_CROSS_VALIDATE,DEF_on,"0",(void*)&(preprocP->isCrossValidation),0x000); /* char */
        res  &= getAttrbValueOfFirstChildEle2Var(root->root,DEF_SCALE,DEF_on,"0",(void*)&(preprocP->isScale),0x000); /* char */
        pEle = getfirstChildXML(root->root,DEF_CROSS_VALIDATE);
        if(res ==1 &&pEle != NULL)
        {
            res  = getValueOfFirstChildEle2Var(pEle,DEF_FOLD,"0",(void*)&(preprocP->fold),0x010); /* int */
            res &= getValueOfFirstChildEle2Var(pEle,DEF_MIN_FOLD,"0",(void*)&(preprocP->minFold),0x010); /* int */
            res &= getValueOfFirstChildEle2Var(pEle,DEF_MAX_FOLD,"0",(void*)&(preprocP->maxFold),0x010); /* int */
            res &= getValueOfFirstChildEle2Var(pEle,DEF_STEP_NEXT_FOLD,"0",(void*)&(preprocP->stepNextFold),0x010); /* int */
            res &= getValueOfFirstChildEle2Var(pEle,DEF_INCLUDE_TEST_FILES,"0",(void*)&(preprocP->includeTestFiles),0x000); /* char */
        }
        else
        {
            /* do nothing */
        }
        pEle = getfirstChildXML(root->root,DEF_SCALE);
        if(res ==1 &&pEle != NULL)
        {
            
            res &= getValueOfFirstChildEle2Var(pEle,DEF_MIN,"0.0",(void*)&(preprocP->scale_min),0x050); /* double */
            res &= getValueOfFirstChildEle2Var(pEle,DEF_MAX,"0.0",(void*)&(preprocP->scale_max),0x050); /* double */
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
    return res;
}



int getSvmParamFromXML(svmParam* svmParamObj,treeXML* root)
{
    int res=0;
    elementXML *pEle = NULL;
    if(svmParamObj != NULL && root!=NULL)
    {
        pEle = getfirstChildXML(root->root,DEF_SOFTMARGIN);
        if(pEle != NULL)
        {
            res = getValueOfFirstChildEle2Var(pEle,DEF_CONST_SOFT_M,"0",(void*)&(svmParamObj->constSoftM),0x050); /* double */
            res &= getValueOfFirstChildEle2Var(pEle,DEF_MIN_CONST_SOFT_M,"0",(void*)&(svmParamObj->minConstSoftM),0x050); /* double */
            res &= getValueOfFirstChildEle2Var(pEle,DEF_MAX_CONST_SOFT_M,"0",(void*)&(svmParamObj->maxConstSoftM),0x050); /* double */
            res &= getValueOfFirstChildEle2Var(pEle,DEF_STEP_CONST_SOFT_M,"0",(void*)&(svmParamObj->stepNextConst),0x050); /* double */
        }
        else
        {
            res=0;
        }
        res  = getAttrbValueOfFirstChildEle2Var(root->root,DEF_KERNEL_FUNCTION,DEF_no,"0",(void*)&(svmParamObj->kernelType),0x010); /* int */
        pEle = getfirstChildXML(root->root,DEF_KERNEL_FUNCTION);
        if(res ==1 && pEle!=NULL)
        {
            res = getValueOfFirstChildEle2Var(pEle,DEF_CONSTANT,"0.0",(void*)&(svmParamObj->kernelParam),0x050); /* double */
            res &= getValueOfFirstChildEle2Var(pEle,DEF_CONST_MIN,"0.0",(void*)&(svmParamObj->constKernelMin),0x050); /* double */
            res &= getValueOfFirstChildEle2Var(pEle,DEF_CONST_MAX,"0.0",(void*)&(svmParamObj->constKernelMax),0x050); /* double */
            res &= getValueOfFirstChildEle2Var(pEle,DEF_CONST_STEP,"0.0",(void*)&(svmParamObj->constKernelStep),0x050); /* double */
        }
        else
        {
            res =0;
        }
        
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int getInputDsMgrFromXML(inputDsMgr* inputDsMgrObj,svmApp *app,simString *nameInput)
{
    int res=0;
    int index=0;
    int numList=0;
    treeXML tXML;
    elementXML *pEle = NULL;
    elementXML *pEle2 = NULL;
    simString aInputPath;
    simString fileSimStr;
    simString nameSimStr;
    simString currentPath;
    listElement listFile;
    initialSimString(&aInputPath);
    initialSimString(&currentPath);
    initialSimString(&fileSimStr);
    initialSimString(&nameSimStr);
    if(inputDsMgrObj !=NULL && app!=NULL&&nameInput!=NULL)
    {
        aInputPath = getNameAnInputFileWithsimStrName(app,nameInput);
        if(aInputPath.length !=0)
        {
            res = getSourceToTreeXML(&tXML,aInputPath.data);
            if(res ==1)
            {
                res = getValueOfFirstChildEle2Var(tXML.root,DEF_NUM_CLASS,"0",(void*)&(inputDsMgrObj->numClass),0x010); /*int */
                res &= getValueOfFirstChildEle2Var(tXML.root,DEF_NUM_ATTRB,"0",(void*)&(inputDsMgrObj->numAttrb),0x010); /*int */
                res &= getValueOfFirstChildEle2Var(tXML.root,DEF_NUM_ATTRB_OUTPUT,"0",(void*)&(inputDsMgrObj->numOut),0x010); /*int */
                res &= getValueOfFirstChildEle2Var(tXML.root,DEF_CURRENT_PATH,"0",(void*)&currentPath,0x080); /*simString */
                res &= concatSimStringPathDirectory(&(app->abPath),&currentPath,&currentPath);
            }
            else
            {
                /* do nothing */
            }
            if(res ==1)
            {
                pEle = getfirstChildXML(tXML.root,DEF_TRAINING_FILE);
                if(pEle !=NULL)
                {        
                    res  = getSourceToXMLList(&listFile,pEle,DEF_FILE);
                    numList = getNumOfXMLNode(&listFile);
                    for(index=0;index<numList;index++)
                    {
                        pEle2= getXMLElement(&listFile,index);
                        if(pEle2 !=NULL)
                        {
                            initialSimString(&fileSimStr);
                            initialSimString(&nameSimStr);
                            res =  getValueOfFirstChildEle2Var(pEle2,DEF_NAME,"",(void*)&(nameSimStr),0x080); /*simString */
                            res &= getValueOfFirstChildEle2Var(pEle2,DEF_PATH,"",(void*)&(fileSimStr),0x080); /*simString */
                            res &= concatSimStringPathDirectory(&currentPath,&fileSimStr,&fileSimStr);
                            res &= addNodeSimStrList(&(inputDsMgrObj->trainName),&(nameSimStr));
                            res &= addNodeSimStrList(&(inputDsMgrObj->trainFile),&(fileSimStr));
                            destructSimString(&nameSimStr);
                            destructSimString(&fileSimStr);
                        }
                        else
                        {
                            /* do nothing */
                        }
                        if(res ==0)
                        {
                            index = numList;
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    destructListXMLEle(&listFile);
                }
                else
                {
                    /* do nothing */
                }
                pEle = getfirstChildXML(tXML.root,DEF_TESTING_FILE);
                if(res==1 && pEle !=NULL)
                {
                    res  = getSourceToXMLList(&listFile,pEle,DEF_FILE);
                    if(res ==1 && pEle !=NULL)
                    {
                        numList = getNumOfXMLNode(&listFile);
                        for(index=0;index<numList;index++)
                        {
                            pEle2= getXMLElement(&listFile,index);
                            if(pEle2 !=NULL)
                            {
                                initialSimString(&fileSimStr);
                                initialSimString(&nameSimStr);
                                res =  getValueOfFirstChildEle2Var(pEle2,DEF_NAME,"",(void*)&(nameSimStr),0x080); /*simString */
                                res &= getValueOfFirstChildEle2Var(pEle2,DEF_PATH,"",(void*)&(fileSimStr),0x080); /*simString */
                                res &= concatSimStringPathDirectory(&currentPath,&fileSimStr,&fileSimStr);
                                res &= addNodeSimStrList(&(inputDsMgrObj->testName),&(nameSimStr));
                                res &= addNodeSimStrList(&(inputDsMgrObj->testFile),&(fileSimStr));
                                destructSimString(&nameSimStr);
                                destructSimString(&fileSimStr);
                            }
                            else
                            {
                                /* do nothing */
                            }
                            if(res ==0)
                            {
                                index = numList;
                            }
                            else
                            {
                                /* do nothing */
                            }
                        }
                        destructListXMLEle(&listFile);
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
            }
            else
            {
                /* do nothing */
            }
            destructorTreeXML(&tXML);
        }
        else
        {
            res =0;
        }
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&aInputPath);
    destructSimString(&currentPath);
    return res;
}

int getDelimeterOfDataFormatFromXML(dataFormat* dataFormatObj,elementXML *root)
{
    int res =0;
  //  int dummyInt;
    delimiterSet *pDelimeter = NULL;
    if(dataFormatObj != NULL && root != NULL)
    {
            pDelimeter = &(dataFormatObj->delimeterFormat);
            res = getValueOfFirstChildEle2Var(root,DEF_LINE_START,"0",&(dataFormatObj->lineStart),0x010); /* int */
            res &= getValueOfFirstChildEle2Var(root,DEF_ORDER_ATTRB_START,"0",&(dataFormatObj->orderAttrbStart),0x010); /* int */
            res &= getValueOfFirstChildEle2Var(root,DEF_IO_START,"",&(pDelimeter->ioBegin),0x000); /* char */
            res &= getValueOfFirstChildEle2Var(root,DEF_START_OUT,"",&(pDelimeter->startSymOut),0x002); /* char ascii */
            res &= getValueOfFirstChildEle2Var(root,DEF_STOP_OUT,"",&(pDelimeter->stopSymOut),0x002); /* char ascii */
            res &= getValueOfFirstChildEle2Var(root,DEF_START_INP,"",&(pDelimeter->startSymIn),0x002); /* char ascii */
            res &= getValueOfFirstChildEle2Var(root,DEF_STOP_INP,"",&(pDelimeter->stopSymIn),0x002); /* char ascii */
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int getMissingWordFromXML(missingWord* missingWordObj,elementXML *root)
{
    int res=0;
    if(missingWordObj!=NULL &&root!= NULL)
    {
        res = getValueOfFirstChildEle2Var(root,DEF_MISSING_WORD,"",&(missingWordObj->word),0x080);
        res &= getValueOfFirstChildEle2Var(root,DEF_STATICS_VAL,"-1",&(missingWordObj->staticVal),0x000);
        res &= getAttrbValueOfFirstChildEle2Var(root,DEF_STATICS_VAL,DEF_opt,"0",&(missingWordObj->m_optStatic),0x000);
        res &= getValueOfFirstChildEle2Var(root,DEF_ATTRB_NUM,"0",&(missingWordObj->indexDim),0x010);
        res &= getAttrbValueOfFirstChildEle2Var(root,DEF_ATTRB_NUM,DEF_type,"0",&(missingWordObj->type),0x000);
        res &= getAttrbValueOfFirstChildEle2Var(root,DEF_ATTRB_NUM,DEF_available_val,"0",&(missingWordObj->m_availVal),0x000);
        if(res==1)
        {
            if(missingWordObj->type ==0) /* number*/
            {
                missingWordObj->defVal = (int*)malloc(sizeof(int));
                if(missingWordObj->defVal!=NULL)
                {
                    res &= getValueOfFirstChildEle2Var(root,DEF_DEFAULT_VAL,"0",missingWordObj->defVal,0x010);
                }
                else
                {
                    res =0;
                }
            }
            else if(missingWordObj->type==1) /* float */
            {
                missingWordObj->defVal = (double*)malloc(sizeof(double));
                if(missingWordObj->defVal!=NULL)
                {
                    res &= getValueOfFirstChildEle2Var(root,DEF_DEFAULT_VAL,"0",missingWordObj->defVal,0x050);
                }
                else
                {
                    res =0;
                }
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
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int swapMissingWord(missingWord* lhs,missingWord* rhs)
{
    int res =0;
    missingWord dummyMissing;
    if((lhs!=NULL)&&(rhs!=NULL)&&(rhs!=lhs))
    {
        constructorMissingWord(&dummyMissing);
        copyMissingWord(&dummyMissing,lhs);
        copyMissingWord(lhs,rhs);
        copyMissingWord(rhs,&dummyMissing);
        makeMissingWordEmpty(&dummyMissing);
        res =1;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int sortMissingWordSetFromLessToMore(missingWord *rhs,int numEle)
{
    int res =0;
    int index=0;
    int index2=0;
    if((rhs != NULL)&&(numEle >0))
    {
        res =1;
        for(index=numEle;index>0;index--)
        {
            for(index2=0;index2<index-1;index2++)
            {
                if(rhs[index2].indexDim >rhs[index2+1].indexDim)
                {
                    res = swapMissingWord(&rhs[index2],&rhs[index2+1]);
                }
                else
                {
                    /* do nothing */
                }
            }
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}


int getAttrbConvertFromXML(attrbConvert* attrbConvertObj,elementXML *root)
{
    int res=0;
    int count=0;
    int index=0;
    double *pDouble=NULL;
    int *pInt=NULL;
    simString str1;
    elementXML dummyEle;
    listElement wordList;
    initial_elementXML(&dummyEle);
    constructorListXMLEle(&wordList);
    initialSimString(&str1);
    if(attrbConvertObj!=NULL &&root!= NULL)
    {
        dummyEle.firstChild = root;
        res = generateXMLEleList(&wordList,root,DEF_WORD);
        /* type 1 = double , 0 is int  */
        count = getNumOfXMLNode(&wordList);
        res &= getAttrbValueOfFirstChildEle2Var(&dummyEle,DEF_ATTRB,DEF_type,"0",&(attrbConvertObj->type),0x000);
        res &= getAttrbValueOfFirstChildEle2Var(&dummyEle,DEF_ATTRB,DEF_no,"-1",&(attrbConvertObj->indexDim),0x010);
/*        attrbConvertObj->value =NULL;*/
        if(attrbConvertObj->type ==0)
        {
            initialSimStrT(&(attrbConvertObj->m_wordT),delIntDatInSimTAttrbConvert,copyIntDatInSimTAttrbConvert);
        }
        else if(attrbConvertObj->type ==1)
        {
            initialSimStrT(&(attrbConvertObj->m_wordT),delDoubleDatInSimTAttrbConvert,copyDoubleDatInSimTAttrbConvert);
        }
        if(res==1)
        { 
            for(index=0;index<count;index++)
            {
                initialSimString(&str1);
                dummyEle.firstChild  = getXMLElement(&wordList,index);
                res &= getValueOfFirstChildEle2Var(&dummyEle,DEF_WORD,"",&str1,0x080);
                /*res &= addNodeSimStrList(&(attrbConvertObj->words),&str1);*/
                if(attrbConvertObj->type ==0)
                {
                    pInt = (int*)malloc(sizeof(int));
                    if(pInt!=NULL)
                    {
                        res &= getAttrbValueOfFirstChildEle2Var(&dummyEle,DEF_WORD,DEF_value,"0",pInt,0x010);
                        res &= addELeSimStrT(&(attrbConvertObj->m_wordT),&str1,(void*)pInt);
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                else if(attrbConvertObj->type ==1)
                {
                    pDouble = (double*)malloc(sizeof(double));
                    if(pDouble!=NULL)
                    {
                        res &= getAttrbValueOfFirstChildEle2Var(&dummyEle,DEF_WORD,DEF_value,"0",pDouble,0x050);
                        res &= addELeSimStrT(&(attrbConvertObj->m_wordT),&str1,(void*)pDouble);
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
                destructSimString(&str1);
            }
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
    destructListXMLEle(&wordList);
    return res;
}
int swapAttrbConvert(attrbConvert* lhs,attrbConvert* rhs)
{
    int res =0;
    attrbConvert dummyAttrb;
    if((lhs!=NULL)&&(rhs!=NULL)&&(rhs!=lhs))
    {
        dummyAttrb = *lhs;
        *lhs = *rhs;
        *rhs = dummyAttrb;
        res =1;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
/*

int sortAttrbConvertFromLessToMore(attrbConvert* rhs,int numEle)
{
    int res =0;
    int index=0;
    int index2=0;
    if((rhs != NULL)&&(numEle >0))
    {
        res =1;
        for(index=numEle;index>0;index--)
        {
            for(index2=0;index2<index-1;index2++)
            {
                if(rhs[index2].indexDim >rhs[index2+1].indexDim)
                {
                    res = swapAttrbConvert(&rhs[index2],&rhs[index2+1]);
                }
                else
                { 
                }
            }
        }
    }
    else
    { 
    }
    return res;
}
*/
int getConvertMethodFromXML(convertMethod* convertMethodObj,elementXML *root)
{
    int res=0;
    elementXML *pEle= NULL;
    int numList=0;
    int index=0;
    listElement listEle;
    struct attrbConvert *pAttrb=NULL;
    struct missingWord *pMiss=NULL;
    constructorListXMLEle(&listEle);
    if((convertMethodObj!=NULL) &&(root!= NULL))
    {
            res  = generateXMLEleList(&listEle,root,DEF_MISSING);
            res &= getValueOfFirstChildEle2Var(root,DEF_METHOD,"1",&(convertMethodObj->defaultMethod),0x010);
    }
    else
    {
        /* do nothing */
    }
    /* get missing from xml*/
    if(res==1)
    {
        numList = getNumOfXMLNode(&listEle);
        if(numList ==0)
        {
            res =1;
        }
        else
        {
            /* do nothing */
        }
        if((numList>0)&&(res==1))
        {
            for(index=0;index<numList;index++)
            {
                pEle = getXMLElement(&listEle,index);
                pMiss = (struct missingWord*)malloc(sizeof(struct missingWord)); 
                if((pMiss!=NULL)&&(res==1))
                {
                    constructorMissingWord(pMiss);
                    res &= getMissingWordFromXML(pMiss,pEle);
                    convertMethodObj->m_isHasStatisticVal = (convertMethodObj->m_isHasStatisticVal)|| ((pMiss->staticVal!=-1)&&(pMiss->staticVal!=-3));
                    convertMethodObj->m_missT.insertFn(&(convertMethodObj->m_missT),&pMiss);
                }
                else
                {
                    res =0;
                    index = numList;
                }
            }
            /*
            if(res ==1)
            {
                res = sortMissingWordSetFromLessToMore(convertMethodObj->missW,numList);
            }
            else
            {
                 
            }*/
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
    /* get attribute convert from xml */
    if(res ==1)
    {
        destructListXMLEle(&listEle);
        constructorListXMLEle(&listEle);
        res  = generateXMLEleList(&listEle,root,DEF_ATTRB);
        numList = getNumOfXMLNode(&listEle);
        if((res==1)&&(numList>0))
        {
            for(index=0;index<numList;index++)
            {
                pEle = getXMLElement(&listEle,index);
                pAttrb = (struct attrbConvert*)malloc(sizeof(struct attrbConvert));
                if((pAttrb!=NULL)&&(res==1))
                {
                    constructorAttrbConvert(pAttrb);
                    res &= getAttrbConvertFromXML(pAttrb,pEle);
                    convertMethodObj->m_attrbT.insertFn(&(convertMethodObj->m_attrbT),&pAttrb);
                }
                else
                {
                    res =0;
                    index =numList;
                } 
                /*res &= getAttrbConvertFromXML(&(convertMethodObj->attrbW[index]),pEle);*/
            }
            /*
            if(res ==1)
            {
                res = sortAttrbConvertFromLessToMore(convertMethodObj->attrbW,numList);
            }
            else
            { 
            }*/
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
    if(res==0)
    {
        makeConvertMethodEmpty(convertMethodObj);
    }
    else
    {
        /* do nothing */
    }
    destructListXMLEle(&listEle);
    return res;
}

int getDataFormatFromXML(dataFormat* dataFormatObj,const char *name,int numFeatureInp,int numFeatureOut)
{
    int res=0;
    treeXML tXML;
    elementXML *pEle= NULL;
    elementXML *pEle2= NULL;
    res = getSourceToTreeXML(&tXML,name);
    if(res==1)
    {
        res = getAttrbValueOfFirstChildEle2Var(tXML.root,DEF_FILE,DEF_type,"0",&(dataFormatObj->type),0x000);
        pEle= getfirstChildXML(tXML.root,DEF_FILE);
    }
    else
    {
        res=0;
    }
    if((res==1)&&(pEle!=NULL)&&dataFormatObj!=NULL)
    {
        pEle2= getfirstChildXML(pEle,DEF_CONVERT_METHOD);
        res  = getConvertMethodFromXML(&(dataFormatObj->convertor),pEle2);
        pEle2= getfirstChildXML(pEle,DEF_SYMBOL);
        res &= getValueOfFirstChildEle2Var(pEle,DEF_NAME_FILE,"",&(dataFormatObj->filename),0x080);
        res &= getValueOfFirstChildEle2Var(pEle,DEF_NUM_SAMPLE,"0",&(dataFormatObj->numSample),0x010);
       res &= getAttrbValueOfFirstChildEle2Var(pEle,DEF_NUM_SAMPLE,DEF_io,"2",&(dataFormatObj->io),0x000);
        res &= getAttrbValueOfFirstChildEle2Var(pEle,DEF_NUM_SAMPLE,DEF_type,"0",&(dataFormatObj->type),0x000);
        res &= getDelimeterOfDataFormatFromXML(dataFormatObj,pEle2);
        dataFormatObj->delimeterFormat.numInput=numFeatureInp;
        dataFormatObj->delimeterFormat.numOutput=numFeatureOut;
    }
    else
    {
        /* do nothing */
    }
    if(res ==0) /* some thing wrong*/
    {
        printf("res : %d, line: %d\n",res,__LINE__);
    }
    else
    {
        /* do nothing */
    }
    destructorTreeXML(&tXML);
    return res;
}  

    /* inputDsMgr */

simString* getTrainingFileNameOfInputDsMgr(inputDsMgr* inputDsMgrObj,int index)
{
    simString *pSimStr = NULL;
    int numList= 0;
    if(inputDsMgrObj !=NULL && index >-1)
    {
         numList = getNumNodeSimStrList(&(inputDsMgrObj->trainFile));
         if(numList > index)
         {
            pSimStr = getnthNodeSimStrList(&(inputDsMgrObj->trainFile),index);
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
    return pSimStr;
}
simString* getTestingFileNameOfInputDsMgr(inputDsMgr* inputDsMgrObj,int index)
{
    simString *pSimStr = NULL;
    int numList= 0;
    if(inputDsMgrObj !=NULL && index >-1)
    {
         numList = getNumNodeSimStrList(&(inputDsMgrObj->testFile));
         if(numList > index)
         {
            pSimStr = getnthNodeSimStrList(&(inputDsMgrObj->testFile),index);
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
    return pSimStr;
}
int getTrainingNumberFromInputDsMgr(inputDsMgr* inputDsMgrObj)
{
    int res=0;
    if(inputDsMgrObj != NULL)
    {
        res = getNumNodeSimStrList(&(inputDsMgrObj->trainFile));
    }
    else
    {
        /* do nothing*/
    }
    return res;
}
int getTestingNumberFromInputDsMgr(inputDsMgr* inputDsMgrObj)
{
    int res=0;
    if(inputDsMgrObj != NULL)
    {
        res = getNumNodeSimStrList(&(inputDsMgrObj->testFile));
    }
    else
    {
        /* do nothing*/
    }
    return res;
}
    
     /* taskMgr */
char isIncludeTestSetsToCrossVal(taskMgr* taskMgrObj)
{
    char res =0;
    if(taskMgrObj != NULL)
    {
        res = taskMgrObj->prePro.includeTestFiles;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int getTrainingNumberFromTaskMgr(taskMgr* taskMgrObj)
{
    int res =0;
    if(taskMgrObj != NULL)
    {
        res = taskMgrObj->numTrainEx;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int getTestingNumberFromTaskMgr(taskMgr* taskMgrObj)
{
    int res =0;
    if(taskMgrObj != NULL)
    {
        res = taskMgrObj->numTestEx;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int getTrainingFileNumberFromTaskMgr(taskMgr* taskMgrObj)
{
    int res=0;
    if(taskMgrObj != NULL)
    {
        res = getTrainingNumberFromInputDsMgr(&(taskMgrObj->inputFile));
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int getTestingFileNumberFromTaskMgr(taskMgr* taskMgrObj)
{
    int res=0;
    if(taskMgrObj != NULL)
    {
        res = getTestingNumberFromInputDsMgr(&(taskMgrObj->inputFile));  
    }
    else
    {
        /* do nothing*/
    }
    return res;
}

simString* getTrainingFileNameOfTaskMgr(taskMgr* taskMgrObj,int index)
{
    if(taskMgrObj !=NULL)
    {
        return getTrainingFileNameOfInputDsMgr(&(taskMgrObj->inputFile),index);
    }
    else
    {
        return NULL;
    }
}
simString* getTestingFileNameOfTaskMgr(taskMgr* taskMgrObj,int index)
{
    if(taskMgrObj !=NULL)
    {
        return getTestingFileNameOfInputDsMgr(&(taskMgrObj->inputFile),index);
    }
    else
    {
        return NULL;
    }
}
int getTheNumberOfClassFromTaskMgr(taskMgr* taskMgrObj)
{
    int res =0;
    if(taskMgrObj!=NULL)
    {
        res = taskMgrObj->inputFile.numClass;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int getTheNumberOfFeatureInputFromTaskMgr(taskMgr* taskMgrObj)
{
    int res=0;
    if(taskMgrObj != NULL)
    {
        res = taskMgrObj->inputFile.numAttrb;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int getTheNumberOfFeatureOutputFromTaskMgr(taskMgr* taskMgrObj)
{
    int res=0;
    if(taskMgrObj != NULL)
    {
        res = taskMgrObj->inputFile.numOut;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int getMaxFoldInTaskMgr(taskMgr *obj)
{
    int res=1;
    if(obj != NULL)
    {
        if(obj->prePro.isCrossValidation !=0)
        {
            res = obj->prePro.maxFold;
        }
        else
        {
            res = 1;
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int getMinFoldInTaskMgr(taskMgr *obj)
{
    int res=1;
    if(obj != NULL)
    {
        if(obj->prePro.isCrossValidation !=0)
        {
            res = obj->prePro.minFold;
        }
        else
        {
            res = 1;
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int getStepFoldInTaskMgr(taskMgr *obj)
{
    int res=1;
    if(obj != NULL)
    {
        if(obj->prePro.isCrossValidation !=0)
        {
            res = obj->prePro.stepNextFold;
        }
        else
        {
            res = 1;
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}
       /* get Data From file*/
/* use when the file is available */
int  getNumOfInputFromInputMgrFile(svmApp *app) 
{
    int numOfInput = 0;
    treeXML tXML;
    listElement listXML;
    elementXML *rootXML = NULL;
    int res = 0;
    
    if(app== NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    constructorListXMLEle(&listXML);
    initial_treeXML(&tXML);
    res = setReadFile(&tXML,app->inputMgrPath.data);
    if(res == 0)
    {
        destructListXMLEle(&listXML);
        destructorTreeXML(&tXML);
        numOfInput = 0;
    }
    else
    {   
        createTreeXML(&tXML);
        rootXML = getRootElementXML(&tXML);
        generateXMLEleList(&listXML,rootXML,DEF_FILE_NAME); 
        numOfInput = getNumOfXMLNode(&listXML);
        destructListXMLEle(&listXML);
        destructorTreeXML(&tXML);
    }
    return numOfInput;
}
/* convertMethod method*/
int getDataFromAttrbTableOfConvertMethod(convertMethod* obj,const char* buff,int indexAttrb,char *staticVal,double  *valReal)
{
    char res =(obj!=NULL)&&(buff!=NULL)&&(indexAttrb>=0)&&(valReal!=NULL)&&(staticVal!=NULL);
    int methodType = 0;
    if(res==1)
    {
        methodType = obj->defaultMethod;
        res =0;
        /* random value */
        if((res!=1)&&((methodType ==3) ||(methodType ==4)))
        {
            res  =1;
        }
        else
        {
            /* do nothing */
        }
        /* convert from string to real number */
        if((res!=1)&&((methodType ==0) ||(methodType ==1)))
        {
            *valReal = (double)str2DoubleWithBoolean(buff,&res);
        }
        else
        {
            /* do nothing */
        }
        /*convert mapping missing value */
        if(res!=1)
        {
            res = getDataFromAttrbTableOfMissingWord(obj,buff,indexAttrb,staticVal,valReal);
        }
        else
        {
            /* do nothing */
        }
        /* convert mapping attrb word*/ 
        if(res!=1)
        {
            res = getDataFromAttrbTableOfAttrbConvert(obj,buff,indexAttrb,valReal);
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
   return (int)res;
}
/* dataFormat  method*/
int assignValueToVectorDByDataFormat(dataFormat* obj,double* data,double* data1,int indexAttrb)
{
    int res =(obj!=NULL)&&(data!=NULL)&&(indexAttrb>=0);
    if(res==1)
    {
        if(obj->delimeterFormat.ioBegin==0) /* 0 output before input */
        {
            /* to align the data like [---input value---|---output value---] format*/
            /* 21 May 2016 : Chalearm Saelim*/
            if(indexAttrb <obj->delimeterFormat.numOutput)
            {/* indexAttrb at the time is an index that point to output value so placed behide the input at numInput+indexAttrb*/
                data[obj->delimeterFormat.numInput+indexAttrb] = *data1;
            }
            else /* the input value has to be placed before the output value group*/
            {
                data[indexAttrb-obj->delimeterFormat.numOutput] = *data1;
            }
        }
        else if(obj->delimeterFormat.ioBegin==1)/* 1 input berfore output*/
        {
            data[indexAttrb] = *data1; 
        }
        else
        {
            res =0;
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}
/* end of dataFormat method*/
int getDataFromAttrbTableOfMissingWord(convertMethod* obj,const char* buff,int indexAttrb,char *staticVal,double  *valReal)
{
    int res =0;
    simString *str = NULL;
    missingWord *pMissResult=NULL; 
    res = (obj!=NULL)&&(buff!=NULL);
    if(res==1)
    { 
        pMissResult = searchIndexDimMissInConvertMet(obj,indexAttrb);
        if(pMissResult!=NULL)
        {
            str =&(pMissResult->word);
            if(strcmp(buff,str->data)==0) /* is equal */
            { 
                *staticVal =pMissResult->staticVal;
                /* replacing with special value */
                /* type: 1(double), 0(int) */
                if((*staticVal == IGNORE_STATIS)&&(pMissResult->type<=1)&&(pMissResult->type >=0)&&(pMissResult->defVal != NULL))
                {
                    res = 1;
                    *staticVal = UNDEFINE_STATIS;
                    if(pMissResult->type ==1)
                    {
                        *valReal = *((double*)pMissResult->defVal);
                    }
                    else if(pMissResult->type ==0)
                    {
                        *valReal = (double)(*((int*)pMissResult->defVal));
                    }
                    else
                    {
                        res =0;
                    }
                }
                else if(*staticVal == IGNORE_STATIS)
                {
                    *staticVal = UNKNOW_STATIS;
                }
                else if((*staticVal>IGNORE_STATIS)&&(*staticVal<UNDEFINE_STATIS))
                { 
                    res = 1;
                }
                else
                {
                    /* do nothing */
                }
            }
            else
            {
                res =0;
            }
        }
        else
        {
            res =0;
        }
    }
    else
    {
        /* do nothing */
    }
   return res;
}
int getDataFromAttrbTableOfAttrbConvert(convertMethod* obj,const char* buff,int indexAttrb,double  *valReal)
{
    int res =0; 
    attrbConvert *pAttrbResult=NULL;
    void *resultV=NULL;
    res = (buff!=NULL)&&(valReal!=NULL)&&(indexAttrb>=0);
    if(res ==1)
    {
        res=1;
        pAttrbResult = searchIndexDimAttrbInConvertMet(obj,indexAttrb);
        if(pAttrbResult ==NULL)
        {
            res=0;
        }
        else
        {
            resultV =search2GetValueInSimStrTByCstr(&(pAttrbResult->m_wordT),buff);
        }
        if(resultV ==NULL)
        {
            res =0;
        }
        else if(pAttrbResult->type ==1) /* double */
        {
            *valReal = *((double*)resultV);
        }
        else if(pAttrbResult->type ==0) /* int */
        {
            *valReal = (double)(*((int*)resultV));
        }
        else
        {
            res =0;
        } 
    }
   return res;
}
attrbConvert *searchIndexDimAttrbInConvertMet(convertMethod* obj,int indexDim)
{
    attrbConvert *pAttrb=NULL;
    void *node =NULL;
    void *key =NULL;
    attrbConvert tempAttrb;
    if((obj!=NULL)&&(indexDim>-1))
    {
       tempAttrb.indexDim =indexDim;
       key = (void*)&tempAttrb;
       node = searchDataInBinaryTree(&(obj->m_attrbT),&key);
    }
    else
    {
        /* do nothing */
    }
    if(node !=NULL)
    {
       pAttrb = *((attrbConvert**)(obj->m_attrbT.getKey(node)));
    }
    else
    {
        /* do nothing */
    }
    return pAttrb;
}
missingWord *searchIndexDimMissInConvertMet(convertMethod* obj,int indexDim)
{
    missingWord *pMiss=NULL;
    void *node =NULL;
    void *key =NULL;
    missingWord tempMiss;
    if((obj!=NULL)&&(indexDim>-1))
    {
       tempMiss.indexDim =indexDim;
       key = (void*)&tempMiss;
       node = searchDataInBinaryTree(&(obj->m_missT),&key);
    }
    else
    {
        /* do nothing */
    }
    if(node !=NULL)
    {
       pMiss = *((missingWord**)(obj->m_missT.getKey(node)));
    }
    else
    {
        /* do nothing */
    }
    return pMiss;
}
simString getNameAnInputFile(svmApp *app,int index)
{
    int numOfNode = 0;
    int index2 = 0;
    int res   = 0;
    simString str1;
    simString str2;
    vector_char currP= new_vector_char(0);
    vector_char pInp = new_vector_char(0);
    treeXML tXML;
    listElement listXML;
    elementXML *rootXML = NULL;
    elementXML dummyXML;
    initial_elementXML(&dummyXML);
    initialSimString(&str1);
    newSimStr(&str1,0);
    initialSimString(&str2);
    newSimStr(&str2,0);
    if(app == NULL)
    {
        destructSimString(&str2);
        delete_vector_char(&currP);
        delete_vector_char(&pInp);
        return str1;
    }
    else
    {
        /* do nothing */
    }
    numOfNode =  getNumOfInputFromInputMgrFile(app);
    if(numOfNode != 0)
    {
        constructorListXMLEle(&listXML);
        initial_treeXML(&tXML);
        res = setReadFile(&tXML,app->inputMgrPath.data);
        if(res == 0)
        {
            destructSimString(&str2);
            delete_vector_char(&pInp);
            delete_vector_char(&currP);
            destructListXMLEle(&listXML);
            destructorTreeXML(&tXML);
        }
        else
        {
            createTreeXML(&tXML);
            rootXML = getRootElementXML(&tXML);
            currP = getValueFirstChildXML(rootXML,DEF_CURRENT_PATH,"");
            if(currP.lenght != 0)
            {
                convertVectorChar2SimString(&str2,&currP);
                generateXMLEleList(&listXML,rootXML,DEF_FILE_NAME); 
                for(index2 =0;index2 <numOfNode;index2++)
                {   
                    dummyXML.firstChild = getXMLElement(&listXML,index2);
                    if(index2 == index)
                    {  
                        pInp =getValueFirstChildXML(&dummyXML,DEF_FILE_NAME,"");
                        convertVectorChar2SimString(&str1,&pInp);
                        concatSimStringPathDirectory(&str2,&str1,&str1);
                        concatSimStringPathDirectory(&(app->abPath),&str1,&str1);
                        break;
                    }
                    else
                    {
                        /* do nothing */
                    }
                } 
            }
            else
            {
                /* do nothing */
            }
            destructSimString(&str2);
            delete_vector_char(&pInp);
            delete_vector_char(&currP);
            destructListXMLEle(&listXML);
            destructorTreeXML(&tXML);
        }
    }
    else 
    {
        /* do nothing */
    }
    return str1;
}

simString getNameAnInputFileWithName(svmApp *app,vector_char *name)
{
    int numOfNode = 0;
    int index2 = 0;
    int res   = 0;
    simString str1;
    simString str2;
    vector_char currP= new_vector_char(0);
    vector_char pInp = new_vector_char(0);
    vector_char nameF= new_vector_char(0);
    treeXML tXML;
    listElement listXML;
    elementXML *rootXML = NULL;
    elementXML dummyXML;
    initial_elementXML(&dummyXML);
    initialSimString(&str1);
    newSimStr(&str1,0);
    initialSimString(&str2);
    newSimStr(&str2,0);
    if(app == NULL)
    {
        destructSimString(&str2);
        delete_vector_char(&currP);
        delete_vector_char(&pInp);
        delete_vector_char(&nameF);
        return str1;
    }
    else
    {
        /* do nothing */
    }
    numOfNode =  getNumOfInputFromInputMgrFile(app);
    if(numOfNode != 0)
    {
        constructorListXMLEle(&listXML);
        initial_treeXML(&tXML);
        res = setReadFile(&tXML,app->inputMgrPath.data);
        if(res == 0)
        {
            destructSimString(&str2);
            delete_vector_char(&pInp);
            delete_vector_char(&currP);
            delete_vector_char(&nameF);
            destructListXMLEle(&listXML);
            destructorTreeXML(&tXML);
        }
        else
        {
            createTreeXML(&tXML);
            rootXML = getRootElementXML(&tXML);
            currP = getValueFirstChildXML(rootXML,DEF_CURRENT_PATH,"");
            if(currP.lenght != 0)
            {
                convertVectorChar2SimString(&str2,&currP);
                generateXMLEleList(&listXML,rootXML,DEF_FILE_NAME); 
                for(index2 =0;index2 <numOfNode;index2++)
                {   
                    dummyXML.firstChild = getXMLElement(&listXML,index2);
                    nameF = getAttrbFromXMLEle(&dummyXML,DEF_FILE_NAME,DEF_NAME_ATTRB,"");
                    if(compareEqual_v_char(&nameF,name)==1)
                    {  
                        pInp =getValueFirstChildXML(&dummyXML,DEF_FILE_NAME,"");
                        convertVectorChar2SimString(&str1,&pInp);
                        concatSimStringPathDirectory(&str2,&str1,&str1);
                        concatSimStringPathDirectory(&(app->abPath),&str1,&str1);
                        delete_vector_char(&nameF);
                        break;
                    }
                    else
                    {
                        /* do nothing */
                    }
                    delete_vector_char(&nameF);
                } 
            }
            else
            {
                /* do nothing */
            }
            destructSimString(&str2);
            delete_vector_char(&pInp);
            delete_vector_char(&currP);
            delete_vector_char(&nameF);
            destructListXMLEle(&listXML);
            destructorTreeXML(&tXML);
        }
    }
    else 
    {
        destructSimString(&str2);
        delete_vector_char(&currP);
        delete_vector_char(&pInp);
        delete_vector_char(&nameF);
    }
    return str1;
}
simString getNameAnInputFileWithsimStrName(svmApp *app,simString *name)
{
    simString str;
    vector_char nameV= new_vector_char(0);
    initialSimString(&str);
    if(app != NULL && name != NULL)
    {
        convertSimString2VectorChar(&nameV,name);
        str = getNameAnInputFileWithName(app,&nameV);
    }
    else
    {
        /* do nothing */
    }
    delete_vector_char(&nameV);
    return str;
}

int getNumAPathTestInput(simString *aPath)
{
    int numNode = 0;
    int res = 0;
    treeXML tXML;
    listElement listXML;
    elementXML *rootXML = NULL;
    if(aPath != NULL)
    {
        constructorListXMLEle(&listXML);
        initial_treeXML(&tXML);
        res = setReadFile(&tXML,aPath->data);
        if(res ==1)
        {
            createTreeXML(&tXML);      
            rootXML = getRootElementXML(&tXML);
            rootXML = getfirstChildXML(rootXML,DEF_TESTING_FILE);
            generateXMLEleList(&listXML,rootXML,DEF_FILE); 
            numNode = getNumOfXMLNode(&listXML);
        }
        else
        {
            /* do nothing */
        }
        destructListXMLEle(&listXML);
        destructorTreeXML(&tXML);
    }
    else
    {
        /* do nothing */
    }  
    return numNode;   
}

simString getAPathTestInput(simString *abPath,simString *aPath,int index)
{
    int numNode = 0;
    int res = 0;
    int index2 = 0;
    treeXML tXML;
    listElement listXML;
    vector_char test1 = new_vector_char(0);
    vector_char test2 = new_vector_char(0);
    elementXML *rootXML = NULL;
    elementXML dummyXML;
    simString str1;
    simString str2;
    initialSimString(&str1);
    initialSimString(&str2);
    newSimStr(&str1,0);
    newSimStr(&str2,0);
    initial_elementXML(&dummyXML);
    if(aPath != NULL && abPath != NULL)
    {
        constructorListXMLEle(&listXML);
        initial_treeXML(&tXML);
        res = setReadFile(&tXML,aPath->data);
        if(res ==1)
        {
            createTreeXML(&tXML);          
            rootXML = getRootElementXML(&tXML);
            test2   = getValueFirstChildXML(rootXML,DEF_CURRENT_PATH,"");
            convertVectorChar2SimString(&str2,&test2);
            delete_vector_char(&test2);
            rootXML = getfirstChildXML(rootXML,DEF_TESTING_FILE);
            generateXMLEleList(&listXML,rootXML,DEF_FILE); 
            numNode = getNumOfXMLNode(&listXML);
            for(index2 = 0;index2 <numNode;index2++)
            {
                dummyXML.firstChild = getXMLElement(&listXML,index2);
                if(index2 == index)
                {
                    dummyXML.firstChild = getfirstChildXML(dummyXML.firstChild,DEF_PATH);
                    test1 = getValueFirstChildXML(&dummyXML,DEF_PATH,"");
                    convertVectorChar2SimString(&str1,&test1);
                    delete_vector_char(&test1);
                    concatSimStringPathDirectory(abPath,&str2,&str2);
                    concatSimStringPathDirectory(&str2,&str1,&str1);
                    break;
                }
                else
                {
                    /* do nohting */ 
                }
            }
            destructSimString(&str2);
        }
        else
        {
            /* do nothing */
        }
        destructSimString(&str2);
        destructListXMLEle(&listXML);
        destructorTreeXML(&tXML);
    }
    else
    {
        /* do nothing */
    }   
    destructSimString(&str2);
    delete_vector_char(&test2);
    delete_vector_char(&test1);
    return str1;   
}

void getPathTestInputList(simString *abPath,simString *aPath,simStrList *listname)
{
    int numNode = 0;
    int res = 0;
    int index = 0;
    treeXML tXML;
    listElement listXML;
    vector_char test1 = new_vector_char(0);
    vector_char test2 = new_vector_char(0);
    elementXML *rootXML = NULL;
    elementXML dummyXML;
    simString str1;
    simString str2;
    initialSimString(&str1);
    initialSimString(&str2);
    newSimStr(&str1,0);
    newSimStr(&str2,0);
    initial_elementXML(&dummyXML);
    if(aPath != NULL && abPath != NULL && listname!=NULL)
    {
        constructorListXMLEle(&listXML);
        initial_treeXML(&tXML);
        res = setReadFile(&tXML,aPath->data);
        if(res ==1)
        {
            createTreeXML(&tXML);
            rootXML = getRootElementXML(&tXML);
            test2   = getValueFirstChildXML(rootXML,DEF_CURRENT_PATH,"");
            convertVectorChar2SimString(&str2,&test2);
            delete_vector_char(&test2);
            rootXML = getfirstChildXML(rootXML,DEF_TESTING_FILE);
            generateXMLEleList(&listXML,rootXML,DEF_FILE); 
            numNode = getNumOfXMLNode(&listXML);
            for(index = 0;index <numNode;index++)
            {
                dummyXML.firstChild = getXMLElement(&listXML,index);
                dummyXML.firstChild = getfirstChildXML(dummyXML.firstChild,DEF_PATH);
                test1 = getValueFirstChildXML(&dummyXML,DEF_PATH,"");
                convertVectorChar2SimString(&str1,&test1);
                concatSimStringPathDirectory(abPath,&str2,&str2);
                concatSimStringPathDirectory(&str2,&str1,&str1);
                addNodeSimStrList(listname,&str1);
                delete_vector_char(&test1);
                destructSimString(&str1);
            }
        }
        else
        {
            /* do nothing */
        }
        destructListXMLEle(&listXML);
        destructorTreeXML(&tXML);
    }
    else
    {
        /* do nothing */
    }  
    destructSimString(&str1);
    destructSimString(&str2);
    delete_vector_char(&test1);
    delete_vector_char(&test2);
}

int getNumAPathTrainInput(simString *aPath)
{
    int numNode = 0;
    int res = 0;
    treeXML tXML;
    listElement listXML;
    elementXML *rootXML = NULL;
    if(aPath != NULL)
    {
        constructorListXMLEle(&listXML);
        initial_treeXML(&tXML);
        res = setReadFile(&tXML,aPath->data);
        if(res ==1)
        {
            createTreeXML(&tXML);
            rootXML = getRootElementXML(&tXML);
            rootXML = getfirstChildXML(rootXML,DEF_TRAINING_FILE);
            generateXMLEleList(&listXML,rootXML,DEF_FILE); 
            numNode = getNumOfXMLNode(&listXML);
        }
        else
        {
            /* do nothing */
        }
        destructListXMLEle(&listXML);
        destructorTreeXML(&tXML);
    }
    else
    {
        /* do nothing */
    }  
    return numNode;   
}


simString getAPathTrainInput(simString *abPath,simString *aPath,int index)
{
    int numNode = 0;
    int res = 0;
    int index2 = 0;
    treeXML tXML;
    listElement listXML;
    vector_char test1 = new_vector_char(0);
    vector_char test2 = new_vector_char(0);
    elementXML *rootXML = NULL;
    elementXML dummyXML;
    simString str1;
    simString str2;
    initialSimString(&str1);
    initialSimString(&str2);
    newSimStr(&str1,0);
    newSimStr(&str2,0);
    initial_elementXML(&dummyXML);
    if(aPath != NULL && abPath != NULL)
    {
        constructorListXMLEle(&listXML);
        initial_treeXML(&tXML);
        res = setReadFile(&tXML,aPath->data);
        if(res ==1)
        {
            createTreeXML(&tXML);
            rootXML = getRootElementXML(&tXML);
            test2   = getValueFirstChildXML(rootXML,DEF_CURRENT_PATH,"");
            convertVectorChar2SimString(&str2,&test2);
            delete_vector_char(&test2);
            rootXML = getfirstChildXML(rootXML,DEF_TRAINING_FILE);
            generateXMLEleList(&listXML,rootXML,DEF_FILE); 
            numNode = getNumOfXMLNode(&listXML);
            for(index2 = 0;index2 <numNode;index2++)
            {
                dummyXML.firstChild = getXMLElement(&listXML,index2);
                if(index2 == index)
                {
                    dummyXML.firstChild = getfirstChildXML(dummyXML.firstChild,DEF_PATH);
                    test1 = getValueFirstChildXML(&dummyXML,DEF_PATH,"");
                    convertVectorChar2SimString(&str1,&test1);
                    delete_vector_char(&test1);
                    concatSimStringPathDirectory(abPath,&str2,&str2);
                    concatSimStringPathDirectory(&str2,&str1,&str1);
                    break;
                }
                else
                {
                    /* do nohting */ 
                }
            }
        }
        else
        {
            /* do nothing */
        }
        destructListXMLEle(&listXML);
        destructorTreeXML(&tXML);
    }
    else
    {
        /* do nothing */
    }  
    delete_vector_char(&test1);
    delete_vector_char(&test2);
    destructSimString(&str2);
    return str1;   
}

void getPathTrainInputList(simString *abPath,simString *aPath,simStrList *listname)
{
    int numNode = 0;
    int res = 0;
    int index = 0;
    treeXML tXML;
    listElement listXML;
    vector_char test1 = new_vector_char(0);
    vector_char test2 = new_vector_char(0);
    elementXML *rootXML = NULL;
    elementXML dummyXML;
    simString str2;
    simString str1;
    initialSimString(&str1);
    initialSimString(&str2);
    newSimStr(&str1,0);
    newSimStr(&str2,0);
    initial_elementXML(&dummyXML);
    if(aPath != NULL && abPath != NULL && listname!=NULL)
    {
        constructorListXMLEle(&listXML);
        initial_treeXML(&tXML);
        res = setReadFile(&tXML,aPath->data);
        if(res ==1)
        {
            createTreeXML(&tXML);
            rootXML = getRootElementXML(&tXML);
            test2   = getValueFirstChildXML(rootXML,DEF_CURRENT_PATH,"");
            convertVectorChar2SimString(&str2,&test2);
            delete_vector_char(&test2);
            rootXML = getfirstChildXML(rootXML,DEF_TRAINING_FILE);
            generateXMLEleList(&listXML,rootXML,DEF_FILE); 
            numNode = getNumOfXMLNode(&listXML);
            for(index = 0;index <numNode;index++)
            {
                dummyXML.firstChild = getXMLElement(&listXML,index);
                dummyXML.firstChild = getfirstChildXML(dummyXML.firstChild,DEF_PATH);
                test1 = getValueFirstChildXML(&dummyXML,DEF_PATH,"");
                convertVectorChar2SimString(&str1,&test1);
                concatSimStringPathDirectory(abPath,&str2,&str2);
                concatSimStringPathDirectory(&str2,&str1,&str1);
                addNodeSimStrList(listname,&str1);
                delete_vector_char(&test1);
                destructSimString(&str1);
            }
        }
        else
        {
            /* do nothing */
        }
        destructListXMLEle(&listXML);
        destructorTreeXML(&tXML);
    }
    else
    {
        /* do nothing */
    }  
    destructSimString(&str1);
    destructSimString(&str2);
    delete_vector_char(&test1);
    delete_vector_char(&test2);
}

void getListInputFile(svmApp *app,simStrList *listName)
{
    int numOfNode = 0;
    int index2 = 0;
    int res   = 0;
    simString str1;
    simString str2;
    vector_char currP= new_vector_char(0);
    vector_char pInp = new_vector_char(0);
    treeXML tXML;
    listElement listXML;
    elementXML *rootXML = NULL;
    elementXML dummyXML;
    initial_elementXML(&dummyXML);
    initialSimString(&str1);
    newSimStr(&str1,0);
    initialSimString(&str2);
    newSimStr(&str2,0);
    if(app == NULL || listName == NULL)
    {
        destructSimString(&str2);
        destructSimString(&str1);
        delete_vector_char(&currP);
        delete_vector_char(&pInp);
        return;
    }
    else
    {
        /* do nothing */
    }
    numOfNode =  getNumOfInputFromInputMgrFile(app);
    if(numOfNode != 0)
    {
        constructorListXMLEle(&listXML);
        initial_treeXML(&tXML);
        res = setReadFile(&tXML,app->inputMgrPath.data);
        if(res == 0)
        {
            destructSimString(&str2);
            destructSimString(&str1);
            delete_vector_char(&pInp);
            delete_vector_char(&currP);
            destructSimString(&str1);
            destructListXMLEle(&listXML);
            destructorTreeXML(&tXML);
        }
        else
        {
            createTreeXML(&tXML);
            rootXML = getRootElementXML(&tXML);
            currP = getValueFirstChildXML(rootXML,DEF_CURRENT_PATH,"");
            if(currP.lenght != 0)
            {
                convertVectorChar2SimString(&str2,&currP);
                generateXMLEleList(&listXML,rootXML,DEF_FILE_NAME); 
                for(index2 =0;index2 <numOfNode;index2++)
                {   
                    dummyXML.firstChild = getXMLElement(&listXML,index2);
                    pInp =getValueFirstChildXML(&dummyXML,DEF_FILE_NAME,"");
                    convertVectorChar2SimString(&str1,&pInp);
                    concatSimStringPathDirectory(&str2,&str1,&str1);
                    concatSimStringPathDirectory(&(app->abPath),&str1,&str1);
                    addNodeSimStrList(listName,&str1);
                    destructSimString(&str1);
                }
            }
            else
            {
                /* do nothing */
            }
            destructSimString(&str1);
            destructSimString(&str2);
            delete_vector_char(&pInp);
            delete_vector_char(&currP);
            destructListXMLEle(&listXML);
            destructorTreeXML(&tXML);
        }
    }
    else 
    {
        destructSimString(&str2);
        destructSimString(&str1);
        delete_vector_char(&currP);
        delete_vector_char(&pInp);
    }
}
  

int getNumOfTaskFromTaskMgrFile(svmApp *app)
{
    int numOfTask = 0;
    treeXML tXML;
    listElement listXML;
    elementXML *rootXML = NULL;
    int res = 0;
    
    if(app== NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    constructorListXMLEle(&listXML);
    initial_treeXML(&tXML);
    res = setReadFile(&tXML,app->taskMgrPath.data);
    if(res == 0)
    {
        destructListXMLEle(&listXML);
        destructorTreeXML(&tXML);
        numOfTask = 0;
    }
    else
    {   
        createTreeXML(&tXML);
        rootXML = getRootElementXML(&tXML);
        generateXMLEleList(&listXML,rootXML,DEF_TASK); 
        numOfTask = getNumOfXMLNode(&listXML);
        destructListXMLEle(&listXML);
        destructorTreeXML(&tXML);
    }
    return numOfTask;
}
simString getNameATaskFile(svmApp *app,int index)
{
    int numOfNode = 0;
    int index2 = 0;
    int res   = 0;
    simString str1;
    simString str2;
    vector_char currP= new_vector_char(0);
    vector_char pInp = new_vector_char(0);
    treeXML tXML;
    listElement listXML;
    elementXML *rootXML = NULL;
    elementXML dummyXML;
    initial_elementXML(&dummyXML);
    initialSimString(&str1);
    newSimStr(&str1,0);
    initialSimString(&str2);
    newSimStr(&str2,0);
    if(app == NULL)
    {
        destructSimString(&str2);
        delete_vector_char(&currP);
        delete_vector_char(&pInp);
        return str1;
    }
    else
    {
        /* do nothing */
    }
    numOfNode =  getNumOfTaskFromTaskMgrFile(app);
    if(numOfNode != 0)
    {
        constructorListXMLEle(&listXML);
        initial_treeXML(&tXML);
        res = setReadFile(&tXML,app->taskMgrPath.data);
        if(res == 0)
        {
            destructSimString(&str2);
            delete_vector_char(&pInp);
            delete_vector_char(&currP);
            destructListXMLEle(&listXML);
            destructorTreeXML(&tXML);
        }
        else
        {
            createTreeXML(&tXML);
            rootXML = getRootElementXML(&tXML);
            currP = getValueFirstChildXML(rootXML,DEF_CURRENT_PATH,"");
            if(currP.lenght != 0)
            {
                convertVectorChar2SimString(&str2,&currP);
                generateXMLEleList(&listXML,rootXML,DEF_TASK); 
                for(index2 =0;index2 <numOfNode;index2++)
                {   
                    dummyXML.firstChild = getXMLElement(&listXML,index2);
                    if(index2 == index)
                    {  
                        pInp =getValueFirstChildXML(&dummyXML,DEF_TASK,"");
                        convertVectorChar2SimString(&str1,&pInp);
                        concatSimStringPathDirectory(&str2,&str1,&str1);
                        concatSimStringPathDirectory(&(app->abPath),&str1,&str1);
                        break;
                    }
                    else
                    {
                        /* do nothing */
                    }
                } 
            }
            else
            {
                /* do nothing */
            }
            destructSimString(&str2);
            delete_vector_char(&pInp);
            delete_vector_char(&currP);
            destructListXMLEle(&listXML);
            destructorTreeXML(&tXML);
        }
    }
    else 
    {
        /* do nothing */
    }
    return str1;
}
int getUseStatusATaskFile(svmApp *app,int index)
{
    int numOfNode = 0;
    int index2 = 0;
    int res   = 0;
    treeXML tXML;
    listElement listXML;
    elementXML *rootXML = NULL;
    elementXML dummyXML;
    constructorListXMLEle(&listXML);
    initial_elementXML(&dummyXML);
    initial_treeXML(&tXML);
    if(app != NULL)
    {
        numOfNode =  getNumOfTaskFromTaskMgrFile(app);
        res = setReadFile(&tXML,app->taskMgrPath.data);
        if(numOfNode != 0 && res !=0)
        {
            createTreeXML(&tXML);
            rootXML = getRootElementXML(&tXML);
            generateXMLEleList(&listXML,rootXML,DEF_TASK); 
            for(index2 =0;index2 <numOfNode;index2++)
            {   
                dummyXML.firstChild = getXMLElement(&listXML,index2);
                if(index2 == index)
                {  
                    getAttrbValueOfFirstChildEle2Var(&dummyXML,DEF_TASK,DEF_use,"0",(void*)&res,0x010); /* int */
                    index2 = numOfNode;
                }
                else
                {
                    /* do nothing */
                }
            } 
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
    destructListXMLEle(&listXML);
    destructorTreeXML(&tXML);
    return res;
}

void getListTaskFile(svmApp *app,simStrList *listName)
{
    int numOfNode = 0;
    int index2 = 0;
    int res   = 0;
    simString str1;
    simString str2;
    vector_char currP= new_vector_char(0);
    vector_char pInp = new_vector_char(0);
    treeXML tXML;
    listElement listXML;
    elementXML *rootXML = NULL;
    elementXML dummyXML;
    initial_elementXML(&dummyXML);
    initialSimString(&str1);
    newSimStr(&str1,0);
    initialSimString(&str2);
    newSimStr(&str2,0);
    if(app == NULL || listName == NULL)
    {
        destructSimString(&str2);
        destructSimString(&str1);
        delete_vector_char(&currP);
        delete_vector_char(&pInp);
        return;
    }
    else
    {
        /* do nothing */
    }
    numOfNode =  getNumOfTaskFromTaskMgrFile(app);
    if(numOfNode != 0)
    {
        constructorListXMLEle(&listXML);
        initial_treeXML(&tXML);
        res = setReadFile(&tXML,app->taskMgrPath.data);
        if(res == 0)
        {
            destructSimString(&str2);
            destructSimString(&str1);
            delete_vector_char(&pInp);
            delete_vector_char(&currP);
            destructSimString(&str1);
            destructListXMLEle(&listXML);
            destructorTreeXML(&tXML);
        }
        else
        {
            createTreeXML(&tXML);
            rootXML = getRootElementXML(&tXML);
            currP = getValueFirstChildXML(rootXML,DEF_CURRENT_PATH,"");
            if(currP.lenght != 0)
            {
                convertVectorChar2SimString(&str2,&currP);
                generateXMLEleList(&listXML,rootXML,DEF_TASK); 
                for(index2 =0;index2 <numOfNode;index2++)
                {   
                    dummyXML.firstChild = getXMLElement(&listXML,index2);
                    pInp =getValueFirstChildXML(&dummyXML,DEF_TASK,"");
                    convertVectorChar2SimString(&str1,&pInp);
                    concatSimStringPathDirectory(&str2,&str1,&str1);  
                    concatSimStringPathDirectory(&(app->abPath),&str1,&str1); 
                    addNodeSimStrList(listName,&str1);
                    destructSimString(&str1);
                }
            }
            else
            {
                /* do nothing */
            }
            destructSimString(&str1);
            destructSimString(&str2);
            delete_vector_char(&pInp);
            delete_vector_char(&currP);
            destructListXMLEle(&listXML);
            destructorTreeXML(&tXML);
        }
    }
    else 
    {
        destructSimString(&str2);
        destructSimString(&str1);
        delete_vector_char(&currP);
        delete_vector_char(&pInp);
    }
}


int checkATaskPath(svmApp *app,simString *tpath)
{
    int         res       = 0;
    simString str1;
    treeXML     tXML;
    elementXML *rootXML   = NULL;
    vector_char nameInput = new_vector_char(0);
    initialSimString(&str1);
    if(app != NULL && tpath != NULL)
    {
        res =  getSourceToTreeXML(&tXML,tpath->data);
        if(res ==1)
        {
            rootXML   = getRootElementXML(&tXML);
            res= getValueOfFirstChildEle2Var(rootXML,DEF_DATA_SET_PATH,"",&nameInput,0x070); /* 0x07 = vector_char*/
            destructorTreeXML(&tXML);
            /* search name input */
            str1 = getNameAnInputFileWithName(app,&nameInput);
            res &= (str1.length >1)&&(str1.data!=NULL);
            destructSimString(&str1);
            delete_vector_char(&nameInput);
            if(res == 0 )
            {
                return NAME_INPUT_FAILED; /* input name in task can not find */
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
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int checkATaskPathByIndex(svmApp *app,int index)
{
    int res =0;
    simString str1;
    initialSimString(&str1);
    if(app != NULL && index>=0)
    {
        str1 =getNameATaskFile(app,index);
        res = checkATaskPath(app,&str1);
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&str1);
    return res;
}


    /* handle ds_mgr.xml  */

int getNumClassInDsMgrWithNameInp(svmApp *app,simString *nameInput)
{
    int res = 0;
    simString dummyPath;
    initialSimString(&dummyPath);
    if(app != NULL && nameInput != NULL)
    {
        dummyPath =  getNameAnInputFileWithsimStrName(app,nameInput);
        res = getNumClassInDsMgr(&dummyPath);
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&dummyPath);    
    return res;
}
int getNumClassInDsMgr(simString *aPath)
{
    int res = 0;
    treeXML tXML;
    if(aPath != NULL)
    {
        res = getSourceToTreeXML(&tXML,aPath->data);
        if(res ==1)
        {
            getValueOfFirstChildEle2Var(tXML.root,DEF_NUM_CLASS,"0",(void*)&res,0x010);
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
    destructorTreeXML(&tXML);
    return res;
}

int getNumAttrbInDsMgrWithNameInp(svmApp *app,simString *nameInput)
{
    int res =0;
    simString aPath;
    initialSimString(&aPath);
    aPath = getNameAnInputFileWithsimStrName(app,nameInput);
    if(aPath.length != 0)
    {
        res = getNumAttrbInDsMgr(&aPath);
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&aPath);
    return res;
}
int getNumAttrbInDsMgr(simString *aPath)
{
    int res =0;
    treeXML tXML;
    if(aPath->length != 0)
    {
        res = getSourceToTreeXML(&tXML,aPath->data);
        getValueOfFirstChildEle2Var(tXML.root,DEF_NUM_ATTRB,"0",(void*)&res,0x010);
        destructorTreeXML(&tXML);
    }
    else
    {
        /* do nothing */
    }
    return res;
}

    simString getCurrentPathInDsMgr(simString *abPath,simString *aPath);
    simString getCurrentPathInDsMgrWithNameInp(svmApp *app,simString *nameInput);
    simString getSourcePathInDsMgr(simString *abPath,simString *aPath);
    simString getSourcePathInDsMgrWithNameInp(svmApp *app,simString *nameInput);

void printMissingWord(missingWord* missingWordObj)
{
/*<!--- -1 or no tag is ignore  (use value)
         0 is mean, 
         1 is median, 
         2 mod, 
         3 random(double) 
         4 random(int) -->
         */
    if(missingWordObj != NULL)
    {
        printf("word:%s\n",missingWordObj->word.data);
        printf("indDim:%d\n",missingWordObj->indexDim);
        if(missingWordObj->type ==1)
        {
            printf("type:double \n"); 
            printf("Val: %lf\n",*((double*)(missingWordObj->defVal)));
        }
        else if(missingWordObj->type ==0)
        {
            printf("type:int \n"); 
            printf("Val: %d\n",*((int*)(missingWordObj->defVal)));
        }
        else
        {
            /* do nothing */
        }
        switch((int)(missingWordObj->staticVal))
        {
            case -1:
                printf("statics: not used \n");
            break;
            case 0:
                printf("statics: mean \n");
            break;
            case 1:
                printf("statics: median \n");
            break;
            case 2:
                printf("statics: mode \n");
            break;
            case 3:
                printf("statics: random (double)\n");
            break;
            case 4:
                printf("statics: random (int)\n");
            break;
            default :
                printf("statics: invalid \n");
            break;
        }
        if((missingWordObj->staticVal == ((char)2))||(missingWordObj->staticVal==((char)3))) /*median or mode*/
        {
            printf("Option :");
            switch(missingWordObj->m_optStatic)
            {
                case 0:
                    printf("mean\n");
                break;
                case 1:
                    printf("random\n");
                break;
                default:
                    printf("invalid option\n");
                break;
            }
        }
    }
    else
    {
        /* do nothing*/
    }
}

int checkDataFormatHasStatisRepresent(dataFormat* dataFormatObj)
{
    int res = 0;
    if(dataFormatObj != NULL)
    {   /* 3 = random (int) , 4=random(4) */
    /*<!-- STATICS_VAL detail -->
  <!-- -1 or no tag is ignore  (use value) -->
   <!-- 0 is mean, 1 is median, 2 mod,-->
   <!-- 3 random(double) , 4 random(int)  -->
*/      res = (dataFormatObj->convertor.m_isHasStatisticVal ==1);
    }
    else
    {
       /* do nothing */
    }
    return res;
}
    
void printAttrbConvert(attrbConvert* attrbConvertObj)
{
    /*
    int index =0;
    int num =0;
    simString *str=NULL;
    double *pDouble=NULL;
    int *pInt=NULL;*/
    if(attrbConvertObj!=NULL)
    {
        printf("indDim:%d\n",attrbConvertObj->indexDim);
        if(attrbConvertObj->type ==1)
        {
            printf("type:double \n"); 
        }
        else if(attrbConvertObj->type ==0)
        {
            printf("type:int \n"); 
        }
        else
        {
            /* do nothing */
        }
        /* 1 May 2016 15:00 have to update from strList to strTree*/
        /*
        num = attrbConvertObj->numOfVal;
        for(index=0;index<num;index++)
        {
            str = getnthNodeSimStrList(&(attrbConvertObj->words),index);
            if(attrbConvertObj->type==1)
            {
                pDouble = attrbConvertObj->value+ sizeof(double)*index;
                printf("w:%s v:%f\n",str->data,*pDouble);
            }
            else if(attrbConvertObj->type==0)
            {
                pInt =  attrbConvertObj->value+ sizeof(int)*index;
                printf("w:%s v:%d\n",str->data,*pInt);
            }
            else
            {
                 
            }
        }
        */
    }
    else
    {
        /* do nothing */
    }
}
void printConvertMethod(convertMethod* convertMethodObj)
{
/*
    int index=0;
    int num =0;*/
    if(convertMethodObj!=NULL)
    {
        printf("defMet:%d\n",convertMethodObj->defaultMethod);
                /*
        num = convertMethodObj->numOfMissW;
        for(index=0;index<num;index++)
        {
            printMissingWord(&(convertMethodObj->missW[index]));
        }

        num = convertMethodObj->numOfAttrbW;
        for(index=0;index<num;index++)
        {
            printAttrbConvert(&(convertMethodObj->attrbW[index]));
        }*/
    }
    else
    {
        /* do nothig */
    }
}
void printDataFormat(dataFormat* dataFormatObj)
{
    if(dataFormatObj!=NULL)
    {
        printf("name:%s\n",dataFormatObj->filename.data);
        if(dataFormatObj->type ==1)
        {
            printf("type:testing \n");
        }
        else if(dataFormatObj->type ==0)
        {
            printf("type:training \n");
        }
        else
        {
            /* do nothing */
        }
        printf("num samples:%d\n",dataFormatObj->numSample);
        printf("line start:%d\n",dataFormatObj->lineStart);
        printf("order attrb start:%d\n",dataFormatObj->orderAttrbStart);
        printConvertMethod(&(dataFormatObj->convertor));
    }
    else
    {
        /* do nothing */
    }
} 
    /*print detail */
void printInputDsMgr(inputDsMgr* inputMgrObj)
{
    int index = 0;
    int numList =0;
    int numList2 =0;
    simString *pSim = NULL;
    if(inputMgrObj!=NULL)
    {
        printf("the number of classes:%d\n",inputMgrObj->numClass);
        printf("the number of attrbs :%d\n",inputMgrObj->numAttrb);
        printf("the number of output :%d\n",inputMgrObj->numOut);
      /*  printf("sourcePath:%s\n",inputMgrObj->sourcePath.data);*/
        numList=getNumNodeSimStrList(&(inputMgrObj->trainFile));
        numList2=getNumNodeSimStrList(&(inputMgrObj->trainName));
        if(numList2==numList)
        {
            printf("List of Training:\n");
            for(index=0;index < numList;index++)
            {
                pSim = getnthNodeSimStrList(&(inputMgrObj->trainName),index);
                printf("NamePath:%s\n",pSim->data);
                pSim = getnthNodeSimStrList(&(inputMgrObj->trainFile),index);
                printf("Path:%s\n",pSim->data);
            }
        }
        else
        {
            /* do nothing */
        }
        numList=getNumNodeSimStrList(&(inputMgrObj->testFile));
        numList2=getNumNodeSimStrList(&(inputMgrObj->testName));
        if(numList2==numList)
        {
            printf("List of Testing:\n");
            for(index=0;index < numList;index++)
            {
                pSim = getnthNodeSimStrList(&(inputMgrObj->testName),index);
                printf("NamePath:%s\n",pSim->data);
                pSim = getnthNodeSimStrList(&(inputMgrObj->testFile),index);
                printf("Path:%s\n",pSim->data);
            }
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
}


void printPreprocParam(preprocParam* preprocObj)
{
    if(preprocObj!=NULL)
    {
        printf("IsCross:%d\n",preprocObj->isCrossValidation);
        printf("IncludeTestFile:%d\n",preprocObj->includeTestFiles);     
        printf("fold:%d\n",preprocObj->fold);
        printf("minFold:%d\n",preprocObj->minFold);
        printf("maxFold:%d\n",preprocObj->maxFold);
        printf("stepNextFold:%d\n",preprocObj->stepNextFold);
        printf("IsScale:%d\n",preprocObj->isScale);
        printf("scale_max:%f\n",preprocObj->scale_max);
        printf("scale_min:%f\n",preprocObj->scale_min);
    }
    else
    {
        /* do nothing */
    }
}
void printSvmParam(svmParam* svmParamObj)
{
    if(svmParamObj != NULL)
    {
   
        printf("soft margin constant%f\n",svmParamObj->constSoftM);
        printf("minimum soft Const:%f\n",svmParamObj->minConstSoftM); 
        printf("maxConstSoftM:%f\n",svmParamObj->maxConstSoftM);
        printf("stepNextConst:%f\n",svmParamObj->stepNextConst);
        printf("kernelType:%d\n",svmParamObj->kernelType);
        printf("kernelParam:%f\n",svmParamObj->kernelParam);
        printf("constKernelMin:%f\n",svmParamObj->constKernelMin);
        printf("constKernelMax:%f\n",svmParamObj->constKernelMax);
        printf("constKernelStep:%f\n",svmParamObj->constKernelStep);
    }
    else
    {
        /* do nothing */
    }
}

void printTaskMgr(taskMgr* taskMgrObj)
{
    if(taskMgrObj!=NULL)
    {
        printf("name:%s\n",taskMgrObj->name.data);
        printf("numTrainEx:%d\n",taskMgrObj->numTrainEx);
        printf("numTestEx:%d\n",taskMgrObj->numTestEx);
        printf("typeMsvm:%d\n",taskMgrObj->typeMsvm);
        printf("svmType:%d\n",taskMgrObj->svmType);
        printf("numRound:%d\n",taskMgrObj->numRound);
        printSvmParam(&(taskMgrObj->svmPar));
        printInputDsMgr(&(taskMgrObj->inputFile));
        printPreprocParam(&(taskMgrObj->prePro));

    }
    else
    {
        /* do nothing */
    }
}