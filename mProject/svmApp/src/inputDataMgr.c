#include "inputDataMgr.h"
#define DATA_BUFFER_SIZE 500

int convertDataByDataFormat(inputDataManager *obj,int indexFile,int indexEx,statisDataLogElement *missLog)
{
    /* 
        -2 is  reject this sample 
        -1 is use default value
        0 is mean
        1 is median
        2 is mod
        3 is random (double)
        4 is random (int)
        5 is maximum
        6 is minimum
#define UNDEFINE_STATIS            7 
    */
    int res=(obj!=NULL)&&(indexFile >=0)&&(indexEx>=0)&&(missLog!=NULL);
    int numEle =0;
    int countMissVal=0;
    double dummyDouble = 0;
    double *doubTemp2 = NULL;
    int indexAttrb=0;
    char isSet = 0; /* when operation for an attribute is completed*/
    char staticVal =UNDEFINE_STATIS;
    int positionBuffer = 0;
    statisDataLog *statisDataLogObj = NULL;
    void *result = NULL;
    char *buff = NULL;
    if(res==1)
    {
        statisDataLogObj = &(obj->m_statisDataObj[0]);
        buff = obj->m_bufferData;
        if(statisDataLogObj->m_inputType == 0)
        {
            result = (void*)getAVectorOfDataSetContainer(&(obj->m_dataSet),indexFile,indexEx);
            doubTemp2 = ((vector_double*)result)->data;
        }
        else
        {
            result = (void*)getDatNextMt22d((void*)&(obj->m_dataSet2));
            doubTemp2 = ((struct mat2Ele*)result)->m_startP;
        }

        numEle = obj->m_numDim + obj->m_numOutDim; /* numEle is equal to size of miss log*/
        for(indexAttrb=0;(indexAttrb<numEle)&&(res == 1);indexAttrb++)
        {
            staticVal = UNDEFINE_STATIS;
            dummyDouble=-1;
            isSet=0;
            positionBuffer = obj->m_listOrderPosOfData[indexAttrb];
            /* rejected sample , assign to discard tree*/
            if((positionBuffer == -1)&&(statisDataLogObj != NULL))
            {
                isSet =1; 
                staticVal =UNKNOW_STATIS;
                missLog[0].indexDim = indexAttrb;
                missLog[0].typeStatus = staticVal;
                countMissVal=1;
                indexAttrb =numEle;
            }
            else
            {
                /* do nothing */
            }
            if(isSet==0)
            {
                
                isSet = getDataFromAttrbTableOfConvertMethod(&(obj->m_dataFormat[indexFile].convertor),&buff[positionBuffer],indexAttrb,&staticVal,&dummyDouble);
            }
            else
            {
                /* do nothing */
            }
            if(isSet ==1) /* assign dummyDouble to result array*/
            {
                res = assignValueToVectorDByDataFormat(&(obj->m_dataFormat[indexFile]),doubTemp2,&dummyDouble,indexAttrb);
            }
            else
            {
                /* do nothing */
            }
            
            /* input that cannot be read */
            /* rejected sample , assign to discard tree*/
            if((isSet==0)&&(statisDataLogObj!=NULL)) 
            {
                printf("-err \"%s\" %d %f\n",&buff[positionBuffer],indexAttrb,dummyDouble);
                staticVal =UNKNOW_STATIS;
                missLog[0].indexDim = indexAttrb;
                missLog[0].typeStatus = staticVal;
                countMissVal=1;
                indexAttrb = numEle;
                isSet =1;
            }
            else
            {
                /* do nothing */
            }
            if((staticVal>UNKNOW_STATIS)&&(staticVal<UNDEFINE_STATIS))
            {
                missLog[countMissVal].indexDim = indexAttrb;
                missLog[countMissVal].typeStatus = staticVal;
                countMissVal++;
                if(isSet==0)printf("1234567890fmdklfjkdfklnekvbndfkvbdfjklvbkdsfvbkdsbvdsbjklvbdsjklvb\n");
            }
            else
            {
                /* do nothing */
            }
        } 
            if(isSet==0)
            {
                printf("error isSet :0 attrb:%d\n",indexAttrb);
            }
            else
            {
               
          /*   printf("resultAddr:%p\n",result);
                print_vector_double(result,6);
                printf("\n");*/
                isSet = addDataToStatisDataLog(statisDataLogObj,result,missLog,countMissVal);
            }

    }
    else
    {
        /* do nothing */
    }
    return res;
}

int validateBeforeConvertDataBytDataFormat(dataFormat* dataFormatObj,char *buff,statisDataLog *statisDataLogObj,int* listStr,int numEle)
{
    char fact1 = (dataFormatObj!=NULL)&&(buff!=NULL);
    char fact2=  checkDataFormatHasStatisRepresent(dataFormatObj);
    fact2 = (fact2==0)||(statisDataLogObj!=NULL);
    fact1 =fact1&&(listStr!=NULL)&&(numEle>0);
    return fact1 && fact2;
}
int countMallo[23];
int runAllTasksOfSvm(svmApp *app)
{
    int index=0;
    int numTask = 0;
    int res = 0;
    char isUse =0;
    clock_t timeCount =clock();
    clock_t timeCount1 =clock();
    clock_t timeEachTask = clock();
    taskMgr aTaskDetail;
    for(index =0;index<23;index++)countMallo[index]=0;
    if(app !=NULL)
    {
        dataCrossValidSet dataCrossValidSetObj;
        inputDataManager inputDataManagerObj;
        numTask = getNumOfTaskFromTaskMgrFile(app);
printf("Num Task : %d\n",numTask);

        for(index=0;index < numTask;index++)
        {
            timeEachTask = clock();
            isUse = getUseStatusATaskFile(app,index);
            /* check file is valid. */
            isUse &= checkATaskPathByIndex(app,index);
            /* this task is work */
            if(isUse ==1)
            {
                constructorTaskMgr(&aTaskDetail);
                
                inputDataManagerObj.countMallo = countMallo;
                constructorInputDataManager(&inputDataManagerObj);
                constructorDataCrossValidSet(&dataCrossValidSetObj);
                res = getATaskFromFileByIndex(&aTaskDetail,app,index);
                
                printf("Task %d: %d\n",index+1,isUse);
                /*  printTaskMgr(&aTaskDetail);*/
                getTraingDataFromTaskObjToInputDataManager(&aTaskDetail,&inputDataManagerObj);
timeCount1 = clock();
                setInfo2DataCrossValidSet(&dataCrossValidSetObj,&inputDataManagerObj);
timeCount1 = clock()-timeCount1;
printf("t3 setInfo2DataCrossValidSet Time : %f \n",((float)timeCount1)/CLOCKS_PER_SEC);

                /* learning */
                
                makeDataCrossValidSetEmpty(&dataCrossValidSetObj);
                destructInputDataManager(&inputDataManagerObj);
                makeTaskMgrEmpty(&aTaskDetail);
                if(res==0)
                {
                    break;
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
            timeEachTask = clock()-timeEachTask;
            printf("Time For task:%d : %f\n",index+1,((float)timeEachTask)/CLOCKS_PER_SEC);
        }
        timeCount = clock()-timeCount;
        printf("Usage Time : %f \n",((float)timeCount)/CLOCKS_PER_SEC);
        printf("allocation Part usage :\n");
        for(index=0;index<22;index++)
        {
            printf("cm[%d]:%d\n",index,countMallo[index]);
        }
        printf("Usage Time At CM[13]: %f \n",((float)countMallo[22])/CLOCKS_PER_SEC);
        res =1;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
 
void constructorDataCrossValidSet(dataCrossValidSet* obj)
{
    if(obj!=NULL)
    {
        constructorDataInput(&(obj->m_testSam));
        obj->m_fold = NULL;
        obj->m_maxNumFold = 0;
        obj->m_numFoldSet = NULL;
        obj->m_numSampleOfEachFold = NULL;
        obj->m_numTestSam = NULL;
        obj->m_numOfNumFoldSet = 0;
    }
    else
    {
        /* do nothing */
    }
}

void constructorDataInput(dataInput* obj)
{
    if(obj!=NULL)
    {
        obj->m_maxNumSam = 0;
        obj->m_currNumSam = 0;
        obj->m_currentIndex = 0;
        obj->m_data = NULL;
    }
    else
    {
        /* do nothing */
    }
}

void newSetofDataInputAndConstruct(dataInput **obj,int num,int *flag)
{
    int valid1 =(obj!=NULL)&&(num>0)&&(flag!=NULL);
    int index=0;
    if(valid1 == 1)
    {
        newArrVoidSt1D((void*)obj,sizeof(dataInput)*num,flag);
        *flag = ((*obj)!=NULL);
        if(*flag==1)
        {
            for(index=0;index<num;index++)
            {
                constructorDataInput(&(*obj)[index]);
            }
        }
        else
        {
            printf("failed to new Set of Data Input :%p \n",obj);
        }
    }
    else
    {
        /* do nohting */
    }

}
void constructSetOfDataInput(dataInput *obj,int num)
{
    int index =0;
    int ret = (obj!=NULL)&&(num>1);
    if(ret ==1)
    {
        for(index=0;index<num;index++)
        {
            constructorDataInput(&obj[index]);
        }
    }
    else
    {
        /* do nothing */
    }
}

void makeDataCrossValidSetEmpty(dataCrossValidSet* obj)
{
    int index =0;
    if(obj!=NULL)
    {
        makeDataInputEmpty(&(obj->m_testSam));
        if(obj->m_fold !=NULL)
        {
            for(index=0;index<obj->m_maxNumFold;index++)
            {
                makeDataInputEmpty(&(obj->m_fold[index]));
            }
            free(obj->m_fold);
            obj->m_fold =NULL;
        }
        else
        {
            /* do nothing */
        } 
        clearOnePointerArr((void**)&(obj->m_numFoldSet));
        clearOnePointerArr((void**)&(obj->m_numTestSam));
        clearDoublePointerArr((void***)&(obj->m_numSampleOfEachFold),obj->m_numOfNumFoldSet);
 
        obj->m_maxNumFold = 0;
        obj->m_numOfNumFoldSet = 0;
    }
    else
    {
        /* do nothibg */
    }
}
void makeDataInputEmpty(dataInput *obj)
{
    if(obj!=NULL)
    {
        clearOnePointerArr(&(obj->m_data));
        obj->m_maxNumSam = 0;
        obj->m_currNumSam = 0;
        obj->m_currentIndex = 0;
    }
    else
    {
        /* do nothibg */
    }
}

int initialFormatDataOfInputDataManager(inputDataManager *obj) /*dataFormat* dataFormatObj is set at here. */
{    /* 0 is train, 1 is test */
    int res=verifyAllQuantityValueOfInputDataManager(obj);
    int index=0;
    simString *pFilePath = NULL;
    if(res==1)
    {
        newArrVoidSt1D((void*)&(obj->m_dataFormat),sizeof(dataFormat)*(obj->m_numFile),&res);
        if(res !=0)
        { 
            for(index=0;index<obj->m_numFile;index++)
            {
                constructorDataFormat(&(obj->m_dataFormat[index]));
                if(index <obj->m_numTrainingFile)
                {
                    pFilePath = getTrainingFileNameOfTaskMgr(obj->m_taskToGet,index);
                    res &= getDataFormatFromXML(&(obj->m_dataFormat[index]),pFilePath->data,obj->m_numDim,obj->m_numOutDim);
                   /* printDataFormat(&(obj->m_dataFormat[index]));*/
                }
                else if(obj->m_isIncludeTestToCrossVal==1)
                {
                    /*index-obj->m_numTrainingFile == run number of test index file from 0 to m_numFile-m_numTrainingFile*/
                    /* see  # 014420012016 about  m_numFile */ 
                   pFilePath = getTestingFileNameOfTaskMgr(obj->m_taskToGet,index-obj->m_numTrainingFile);
                    res &= getDataFormatFromXML(&(obj->m_dataFormat[index]),pFilePath->data,obj->m_numDim,obj->m_numOutDim);
                    /*printDataFormat(&(obj->m_dataFormat[index]));*/
                }
                else
                {
                    index = obj->m_numFile;
                }
            }
            if(res ==0)
            {
                for(index=0;index<obj->m_numFile;index++)
                {
                    makeDataFormatEmpty(&(obj->m_dataFormat[index]));
                }
                free(obj->m_dataFormat);
                obj->m_dataFormat= NULL;
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
        /* do nothing */
    }
    return res;
}

void constructorLogReadFileDataSet(logReadFileDataSet* logReadFileDataSetObj)
{
    if(logReadFileDataSetObj != NULL)
    {
        logReadFileDataSetObj->lineNumber=0;
        initialSimString(&(logReadFileDataSetObj->filename));
        logReadFileDataSetObj->fp = NULL;
    }
    else
    {
        /* do nothing */ 
    }
}
int initialLogReadFileDataSetArray(logReadFileDataSet** logReadFileDataSetObj,int numArray)
{
    int res=0;
    int index=0;
    logReadFileDataSet* pLogReadFileDataSet = NULL;
    if((logReadFileDataSetObj != NULL)&&(numArray >0))
    {
        if(*logReadFileDataSetObj == NULL)
        {
            res =1;
            newArrVoidSt1D((void*)&pLogReadFileDataSet,sizeof(logReadFileDataSet)*numArray,&res);
             if(res !=0)
             {
                for(index=0;index<numArray;index++)
                {
                    constructorLogReadFileDataSet(&(pLogReadFileDataSet[index]));
                }
                *logReadFileDataSetObj =pLogReadFileDataSet;
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
void deallocateLogReadFileDataSetArray(logReadFileDataSet** logReadFileDataSetObj,int numArray)
{
    int index=0;
    logReadFileDataSet *pLogReadFileDataSet = NULL;
    if((logReadFileDataSetObj!=NULL)&&(numArray >0))
    {
        if(*logReadFileDataSetObj != NULL)
        {
            pLogReadFileDataSet = *logReadFileDataSetObj;
            for(index=0;index<numArray;index++)
            {
                pLogReadFileDataSet[index].lineNumber=0;
                destructSimString(&(pLogReadFileDataSet[index].filename));
                if(pLogReadFileDataSet[index].fp != NULL)
                {
                    fclose(pLogReadFileDataSet[index].fp);
                    pLogReadFileDataSet[index].fp = NULL;
                }
                else
                {
                    /* do nothing */
                }
            }
            free(pLogReadFileDataSet);
            *logReadFileDataSetObj = NULL;
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
}
int verifyAllQuantityValueOfInputDataManager(inputDataManager *obj)
{
    int res = (obj!=NULL);
    if(res==1)
    {
        res = (obj->m_taskToGet!=NULL);
        res = res&(obj->m_numFile >0);
        res = res&(obj->m_numDim >0);
        res = res&(obj->m_numOutDim >0);
        res = res&(obj->m_numClass >1);
        res = res&(obj->m_numTrainingFile >0);
        res = res&((obj->m_isIncludeTestToCrossVal == 1)||(obj->m_isIncludeTestToCrossVal == 0));
    }
    else
    {
        /* do nothing */
    }
    return res;
}
 
void startInitialAllVariableOfInputDataManager(inputDataManager *obj)
{
    int numTotalDim = 0;
    int index=0;
    int res = verifyAllQuantityValueOfInputDataManager(obj);
    if(res==1)
    {
        res= res&&(obj->m_res ==1);
    }
    else
    {
        /* do nothing */
    }
    if(res==1)
    {
        res = res&initialFormatDataOfInputDataManager(obj);
        res = res&initialLogReadFileDataSetArray(&(obj->m_logReadFileDataSetObj),obj->m_numTrainingFile);
        addSharedFileToLogReadFileDataOfInputDataManager(obj);
        res = (res==1)&newNumberDataSetContainer(&(obj->m_dataSet),obj->m_numFile);
        res = allocatStatisDataLogArray(&(obj->m_statisDataObj),1,obj->m_numDim,obj->m_inputType,obj->countMallo)&res;
        res = allocatStatisDataLogArray(&(obj->m_statisDataEachClassObj),obj->m_numClass,obj->m_numDim,obj->m_inputType,obj->countMallo)&res;
        
        numTotalDim = (obj->m_numDim+obj->m_numOutDim);
        newArrVoidSt1D((void*)&(obj->m_bufferData),sizeof(char)*DATA_BUFFER_SIZE,&res);
        newArrInt1D((void*)&(obj->m_listOrderPosOfData),numTotalDim,&res);
        res = (obj->m_bufferData!=NULL)&&(res==1);
        if(res==1)
        {
            obj->m_buffSize = DATA_BUFFER_SIZE;
            for(index=0;index<numTotalDim;index++)
            {
                obj->m_listOrderPosOfData[index] =-1;
            }
        }
        else
        {
            /* do nothing */
        }        
        res = res&&(obj->m_statisDataObj!=NULL);
        res = res&&(obj->m_statisDataEachClassObj!=NULL);
        res = res&&(obj->m_dataSet.data!=NULL);
        res = res&&(obj->m_dataFormat!=NULL);
    }
    else
    {
        /* do nothing */
    }    
    if(obj!=NULL)
    {
        obj->m_res =(res==1)&&(obj->m_res==1);
        if(obj->m_res==0)
        {
            printf("failed at : %s %d in startInitialAllVariableOfInputDataManager method\n",__FILE__,__LINE__);
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
void addSharedFileToLogReadFileDataOfInputDataManager(inputDataManager *obj)
{
    int res=verifyAllQuantityValueOfInputDataManager(obj);
    int index=0;
    int index2=0;
    int count=0;
    int index3=0;
    int isRedundant = 0;
    if(res==1)
    {
        res = (obj->m_res==1)&&(obj->m_isIncludeTestToCrossVal==1);
        res = (res==1)&&(obj->m_dataFormat !=NULL)&&(obj->m_logReadFileDataSetObj!=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(res==1)
    {
       for(index=0;index<obj->m_numTrainingFile;index++)
       {
            for(index2=0;index2<obj->m_numTestingFile;index2++)
            {
                if(compareSimString(&(obj->m_dataFormat[index].filename),&(obj->m_dataFormat[obj->m_numTrainingFile+index2].filename))==1)
                {
                    isRedundant =0;
                    for(index3=0;index3<count;index3++)
                    {
                        isRedundant = compareSimString(&(obj->m_logReadFileDataSetObj[index3].filename),&(obj->m_dataFormat[obj->m_numTrainingFile+index2].filename));
                        if(isRedundant==1)
                        {
                            index3=count;
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    if(isRedundant ==0)
                    {
                        copySimStr(&(obj->m_logReadFileDataSetObj[count++].filename),&(obj->m_dataFormat[index].filename));
                    }
                    else
                    {
                        /* do nothing */
                    }
                    index2 = obj->m_numTestingFile;
                }
                else
                {
                    /* do nothing */
                }
            }
       }
       obj->m_numSharedFile = count;
       res =1;
    }
    else
    {
        /* do nothing */
    }
    res = res||(obj->m_isIncludeTestToCrossVal==0);
    if(obj!=NULL)
    {
        obj->m_res =(res==1)&&(obj->m_res==1);
        if(obj->m_res==0)
        {
            printf("failed at : %s %d in addSharedFileToLogReadFileDataOfInputDataManager method\n",__FILE__,__LINE__);
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
int checkSharedFileInLodReadFileDataSetArray(logReadFileDataSet* logReadFileDataSetObj,int arraySize,simString *str)
{
    int res=0;
    int index=0;
    if((logReadFileDataSetObj!= NULL)&&(arraySize >0) &&(str != NULL))
    {
        for(index=0;index<arraySize;index++)
        {
            if(compareSimString(&(logReadFileDataSetObj[index].filename),str) ==1)
            {
                res=1;
                index=arraySize;
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
    return res;
}

void setInfo2DataCrossValidSet(dataCrossValidSet *obj,inputDataManager *objI)
{
    int index =0;
    int numRealCls=0; 
    int ret = (obj!=NULL)&&(objI!=NULL);
    int minFold =0;
    double numStepFold =0;
    double sum1 =0.0;
    double sum2 =0.0;
    double sum3 =0.0;
    taskMgr *objT =NULL;
    int numTrainEx =0;
    int numTestEx = 0;
    clsDivision l_clsdiv;
    kFoldSet l_foldSet;
    numSamOfCls *l_numSam;
    constructClsDivision(&l_clsdiv,0,&ret);
    constructKFoldSet(&l_foldSet,0,&ret);
    if(ret ==0)
    {
        /* do nothing */
    }
    else if(objI->m_res ==0)
    {
        ret =0;
    }
    else
    {
        objT = objI->m_taskToGet;
        numTrainEx = getThenumOfTrainEx(objI);
        numTestEx  = getThenumOfTestEx(objI);
        makeDataCrossValidSetEmpty(obj);
        /* get and set the fold attribute*/
        obj->m_maxNumFold = getMaxFoldInTaskMgr(objT);
        minFold = getMinFoldInTaskMgr(objT);
        numStepFold = (double)getStepFoldInTaskMgr(objT);
        obj->m_numOfNumFoldSet =(int)(1.99999+((double)(obj->m_maxNumFold-minFold))/numStepFold);
        
        /* find the number of valid class */
        numRealCls = objI->m_numRealClass;
        constructClsDivision(&l_clsdiv,numRealCls,&ret);
        constructKFoldSet(&l_foldSet,obj->m_numOfNumFoldSet,&ret);

        l_numSam = l_clsdiv.m_samDetail;
        printf("################################## \n");
        printf("max: %d , min:%d, step : %f numFoldset:%d\n",obj->m_maxNumFold,minFold,numStepFold,obj->m_numOfNumFoldSet);
        printf("num train : %d , num test: %d , numAll:%d\n",numTrainEx,numTestEx,objI->m_numValidSamples);
        printf("################################## -- ret:%d \n",ret);
        assignVal2NumSamOfCls(&l_clsdiv,objI,&ret);
        sum1=0;
        for(index=0;index<numRealCls;index++)
        {
            sum1 += l_numSam[index].m_numRealSam;
            sum2 += l_numSam[index].m_numTrain;
            sum3 += l_numSam[index].m_numTest;
            printf("i:%d, mi:%d , num:%d numR:%d ,tr:%d, test:%d\n",index,l_numSam[index].m_index,l_numSam[index].m_numSam,l_numSam[index].m_numRealSam,l_numSam[index].m_numTrain,l_numSam[index].m_numTest);
            
        }
        printf("sum1 : %f \n",sum1);
        printf("Train : %f, Test: %f\n",sum2,sum3);
        /* if a fold */
        
    }
    if((ret ==1) && (obj->m_numOfNumFoldSet >0))/* if multi- k- folds */
    {
        newSetofDataInputAndConstruct(&(obj->m_fold ),obj->m_maxNumFold,&ret);
        newArrInt1D((void*)&(obj->m_numFoldSet),obj->m_numOfNumFoldSet,&ret);
        newArrInt1D((void*)&(obj->m_numTestSam),obj->m_numOfNumFoldSet,&ret);
        if(ret ==1)
        {
            obj->m_numFoldSet[0] = minFold;
            setAkfoldInKFoldSet(&l_foldSet,0,minFold,&ret);
            for(index=1;index<obj->m_numOfNumFoldSet-1;index++)
            {
                obj->m_numFoldSet[index] = obj->m_numFoldSet[index-1]+numStepFold;
                setAkfoldInKFoldSet(&l_foldSet,index,obj->m_numFoldSet[index],&ret);
            }
            obj->m_numFoldSet[obj->m_numOfNumFoldSet-1] =obj->m_maxNumFold;
            setAkfoldInKFoldSet(&l_foldSet,obj->m_numOfNumFoldSet-1,obj->m_numFoldSet[obj->m_numOfNumFoldSet-1],&ret);
            newArrInt2Ddynsize((void*)&(obj->m_numSampleOfEachFold),obj->m_numOfNumFoldSet,obj->m_numFoldSet,&ret);
            if(ret ==1)
            {
                divideNumSam2EachKFold(&l_foldSet,&l_clsdiv,&ret);
                /* assign bound of every fold (15 July 2017)*/
               /*
               objI->m_numClass
               objI->m_statisDataEachClassObj[];
               //below (15 July 2017)
               //obj->m_numSampleOfEachFold
               //obj->m_numOfNumFoldSet
               //obj->m_numFoldSet
               
m_statisDataEachClassObj               
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
               */
            }
            else
            {
                clearDoublePointerArr((void***)&(obj->m_numSampleOfEachFold),obj->m_numOfNumFoldSet);
                clearOnePointerArr((void**)&(obj->m_fold));
                clearOnePointerArr((void**)&(obj->m_numFoldSet));
                clearOnePointerArr((void**)&(obj->m_numTestSam));
                obj->m_numOfNumFoldSet =0;
                obj->m_maxNumFold = 0;
                objI->m_res =0;
            }
            
        printf("################################## \n");
            printf("numFold FBT :");
            for(index=0;index<obj->m_numOfNumFoldSet;index++)
            {
                printf(" %d", obj->m_numFoldSet[index]);
            }
            printf("\n");
        printf("################################## \n");
        }
        else
        {
            clearOnePointerArr((void**)&(obj->m_fold));
            clearOnePointerArr((void**)&(obj->m_numFoldSet));
            clearOnePointerArr((void**)&(obj->m_numSampleOfEachFold));
            clearOnePointerArr((void**)&(obj->m_numTestSam));
            obj->m_numOfNumFoldSet =0;
            obj->m_maxNumFold = 0;
        }
    }
    else if(ret ==1)
    {
        makeDataCrossValidSetEmpty(obj);
        ret =0;
        objI->m_res =0;
    }
    else
    {
        /* do nothing */
    }
    destructKFoldSet(&l_foldSet,&ret);
    destructClsDivision(&l_clsdiv);
}
void loadFilePointerAndLineNumberToLogReadFileDataSetArray(logReadFileDataSet* logReadFileDataSetObj,int numArray,FILE **fp,int* numLine,simString *pFile)
{
    int index=0;
    if((logReadFileDataSetObj !=NULL)&&(fp!=NULL)&&(numLine !=NULL)&&(numArray>0))
    {
        for(index=0;index<numArray;index++)
        {
            if((*fp==NULL)&&(compareSimString(&(logReadFileDataSetObj[index].filename),pFile) ==1))
            {
                *numLine =logReadFileDataSetObj[index].lineNumber;
                *fp = logReadFileDataSetObj[index].fp;
                printf("load : %s %d %p\n",pFile->data,logReadFileDataSetObj[index].lineNumber,*fp);
                index = numArray;
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
int addFilePointerAndLineNumberToLogReadFileDataSetArray(logReadFileDataSet* logReadFileDataSetObj,int numArray,FILE *fp,int numLine,simString *pFile)
{
    int res =0;
    int index=0;
    if((logReadFileDataSetObj !=NULL)&&(fp!=NULL)&&(numLine >=0)&&(numArray>0))
    {
        for(index=0;index<numArray;index++)
        {
            if(compareSimString(&(logReadFileDataSetObj[index].filename),pFile) ==1)
            {
                logReadFileDataSetObj[index].lineNumber=numLine;
                if((logReadFileDataSetObj[index].fp != fp) &&(logReadFileDataSetObj[index].fp != NULL))
                {
                    fclose(logReadFileDataSetObj[index].fp);
                    
                    logReadFileDataSetObj[index].fp=fp;
                }
                else if(logReadFileDataSetObj[index].fp==NULL)
                {
                     logReadFileDataSetObj[index].fp=fp;
                }
                else
                {
                    /* do nothing */
                }
                index = numArray;
                res =1;
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
    return res;
}
void newArrVoidSt1D(void *obj,int typesize,int *flag)
{
    void **obji =NULL;
    if((obj!=NULL)&&(flag!=NULL))
    {
        if(*flag ==1)
        {            
            obji = (void**)obj;
            clearOnePointerArr(obji);
            if(typesize>0)
            {countMallo[5]++;
                *obji =  malloc(typesize);
            }
            else
            {
                *flag = 0; /*failed size */
                printf("size is below 0 failed to allocation int arry 1d :%p \n",obji);
            }
            if((*obji ==NULL)&&(typesize>0))
            {
                *flag = 0;
                printf("size > 0 failed to allocation int arry 1d :%p \n",obji);
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            printf("flag 0 reject to allocation 1D int array :%p\n",obj);
        }
    }
    else
    {
        /* do nothing */
    }
    
}
void constructVoidClsArr(void *obj,int nloop,void* (*func)(void*,void*,int*),void *param,int opt,int *flag)
{
    
}
void newArrInt1D(void *obj,int size,int *flag)
{
    int **obji =NULL;
    if((obj!=NULL)&&(flag!=NULL))
    {
        if(*flag ==1)
        {            
            obji = (int**)obj;
            clearOnePointerArr((void**)obji);
            if(size >0)
            {countMallo[4]++;
                *obji = (int*)malloc(sizeof(int)*size);
            }
            else
            {
                *flag = 0; /*failed size */
                printf("size is below 0 failed to allocation int arry 1d :%p \n",obji);
            }
            if((*obji ==NULL)&&(size>0))
            {
                *flag = 0;
                printf("size > 0 failed to allocation int arry 1d :%p \n",obji);
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            printf("flag 0 reject to allocation 1D int array :%p\n",obj);
        }
    }
    else
    {
        /* do nothing */
    }
    
}
void newArrInt2D(void *obj,int size,int size2,int *flag)
{
    int valid1 = (size >0)&&(size2>0)&&(obj!= NULL)&&(flag!=NULL);
    int ***obj2  = NULL;
    int index=0;
    int count =0;
    if(valid1==1)
    {
        obj2 = (int***)obj;
        if((*obj2 ==NULL)&&(*flag==1))
        {countMallo[2]++;
            *obj2  = (int**)malloc(sizeof(int*)*size);
            if(*obj2 !=NULL)
            {
                for(index=0;index<size;index++)
                {countMallo[3]++;
                    (*obj2)[index] = (int*)malloc(sizeof(int)*size2);
                    count =((*obj2)[index] !=NULL)+count;
                }
                valid1 =1;
            }
            else
            {
                valid1=0;
                printf("cannot create 1Dimen of arr : %p\n",*obj2);
            }
            if((count != size)&&(valid1==1))
            {
                clearDoublePointerArr((void***)obj2,size);
                *flag =0;
                printf("cannot create 2Dimen of arr : %p\n",*obj2);
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            printf("arr 2D is not null : %p ,fg:%d\n",*obj2,*flag);
        }
    }
    else
    {
        /* do nothing */
    }
}
void newArrInt2Ddynsize(void *obj,int size,int *size2,int *flag)
{
    int valid1 = (size >0)&&(size2!=NULL)&&(obj!= NULL)&&(flag!=NULL);
    int ***obj2  = NULL;
    int index=0;
    int count =0;
    if(valid1==1)
    { 
        obj2 = (int***)obj;
        if((*obj2 ==NULL)&&(*flag==1))
        {
            *obj2  = (int**)malloc(sizeof(int*)*size);
            countMallo[0]++;
            if(*obj2 !=NULL)
            {
                for(index=0;index<size;index++)
                { 
                    if(size2[index] >0)
                    {
                        countMallo[1]++;
                        (*obj2)[index]= (int*)malloc(sizeof(int)*(size2[index]));
                    }
                    else
                    {
                        (*obj2)[index] = NULL;
                    }
                    if((*obj2)[index]!=NULL)
                    {
                        count++;
                    }
                    else if(size2[index]==0)
                    {
                        count++;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
            }
            else
            {
                valid1=0;
                printf("cannot create 1Dimen of arr : %p\n",*obj2);
            }
            if((count != size)&&(valid1==1))
            {
                clearDoublePointerArr((void***)obj2,size);
                *flag =0;
                printf("cannot create 2Dimen of arr : %p\n",*obj2);
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            printf("arr 2D is not null : %p ,fg:%d\n",*obj2,*flag);
        }
    }
    else
    {
        /* do nothing */
    } 
}
void clearOnePointerArr(void **obj)
{
    if(obj!=NULL)
    {
        if(*obj!=NULL)
        {
            free(*obj);
            *obj = NULL;
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
void clearDoublePointerArr(void ***obj,int num)
{
    int index=0;
    if((obj!=NULL)&&(num>0))
    {
        if(*obj!=NULL)
        {
            for(index=0;index<num;index++)
            {
                if((*obj)[index] !=NULL)
                { 
                    free((*obj)[index]);
                }
                else
                {
                    /* do nothing */
                }
            }
            free(*obj);
            *obj = NULL;
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

int randomFx(int max,int min)
{
    return (rand()%(1+(max-min))) +min;
}
/* declaration dataSetContainer method area */
int constructorDataSetContainer(dataSetContainer* obj)
{
    int res=0;
    if(obj!=NULL)
    {
        obj->data = NULL;
        obj->numSample = NULL;
        obj->numArr = 0;
        res =1;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
/* used this metho after constructor once */
int newNumberDataSetContainer(dataSetContainer* obj,int num)
{
    int res =1;
    int index=0;
    if((obj!=NULL)&&(num>=0))
    {
        destructDataSetContainer(obj);
    }
    else
    {
        res =0;
    }
    if((res==1)&&(num!=0))
    {
        newArrInt1D((void*)&(obj->numSample),num,&res);
        newArrVoidSt1D((void*)&(obj->data),sizeof(vector_double*)*num,&res);
        obj->numArr = num;
        if(res!=0)
        {
            for(index=0;index<num;index++)
            {
                obj->numSample[index] =0;
            }
            for(index=0;index<num;index++)
            {
                obj->data[index] =NULL;
            }
        }
        else
        {
            /* do nothing */
        }
        
        if(res==0)
        {
            destructDataSetContainer(obj);
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
int newArraryOfVectDoubleForDataSetContainer(vector_double **vecdou,int num,int numDim)
{
    int res =0;
    int index=0;
    vector_double *pVect=NULL;
    if((vecdou!=NULL)&&(num>0)&&(numDim>0))
    {
        res = (*vecdou == NULL);
    }
    else
    {
        /* do nothing */
    }
    if(res==1)
    {
        newArrVoidSt1D((void*)&pVect,sizeof(vector_double)*num,&res);
        *vecdou = pVect;
        if(res!= 0)
        {
            for(index=0;((index<num)&&(res));index++)
            {
                pVect[index] = new_vector_double(numDim);
                res = res&&(pVect[index].lenght ==numDim);
            }
            for(index=0;((index<num)&&(res==0));index++)
            {
                delete_vector_double(&pVect[index]);
            }
            if(res==0)
            {
                free(pVect);
                *vecdou = NULL;
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
void destructArraryOfVectDoubleForDataSetContainer(vector_double **vecdou,int num)
{
    int index=0;
    vector_double *pVect=NULL;
    if((vecdou!=NULL)&&(num>0))
    {
        pVect = *vecdou;

    }
    else
    {
        /* do nothing */
    }
    if(pVect!=NULL)
    {
        for(index=0;index<num;index++)
        {
            /*printf("dele vect cond ; %p\n",&(pVect[index]));*/
            delete_vector_double(&(pVect[index]));
        }
        free(pVect);
        *vecdou = NULL;
    }
    else
    {
        /* do nothing */
    }
}
int newNumberSamplesInDataSetContainer(dataSetContainer* obj,int index,int num,int numDim)
{
    int res = ((obj!=NULL)&&(index>=0)&&(num>=0)&&(numDim>0));
    if(res==1)
    {
        res = (index<obj->numArr);
    }
    else
    {
        /* do nothing */
    }
    if(res==1)
    {
        if(obj->data[index] !=NULL)
        {
            destructArraryOfVectDoubleForDataSetContainer(&(obj->data[index]),obj->numSample[index]);
        }
        else
        {
            /* do nothing */
        }
        res = newArraryOfVectDoubleForDataSetContainer(&(obj->data[index]),num,numDim);
        obj->numSample[index] = num*(res==1);
        if(res==0)
        {
            destructArraryOfVectDoubleForDataSetContainer(&(obj->data[index]),obj->numSample[index]);
            obj->numSample[index] = 0;
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
int initialValueOfDataSetContainer(dataSetContainer* obj,int index,double value)
{
    int index2=0;
    int index3=0;
    int num = 0;
    int res = (obj!=NULL);
    res = res&&(index>=0); 
    if(res==1)
    {
        res = (index < obj->numArr);
    }
    else
    {
        /* do nothing */
    }
    if(res==1)
    {
        num =obj->numSample[index];
        for(index2=0;index2<num;index2++)
        {
            for(index3=0;index3<obj->data[index][index2].lenght;index3++)
            {
                obj->data[index][index2].data[index3]= value;
            }
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}
void destructDataSetContainer(dataSetContainer *obj)
{
    int index=0;
    int num =0;
    if(obj!=NULL)
    {
        num = obj->numArr;
        for(index=0;index<num;index++)
        {
            destructArraryOfVectDoubleForDataSetContainer(&(obj->data[index]),obj->numSample[index]);
        }
        clearOnePointerArr((void**)&(obj->data));
        obj->numArr =0;
        clearOnePointerArr((void**)&(obj->numSample));
    }
    else
    {
        /* do nothing */
    }
}
/* end dataSetContainer method area */

void* getPointerOfArrFor1FileOfDataSetContainer(dataSetContainer* obj,int index)
{
    void *p = NULL;
    if((obj!=NULL)&&(index>=0))
    {
        if(index < obj->numArr)
        {
            p = obj->data[index];
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
    return p;
}
vector_double* getAVectorOfDataSetContainer(dataSetContainer* obj,int index,int index2)
{
    vector_double *p = NULL;
    if((obj!=NULL)&&(index>=0)&&(index2>=0))
    {
        if((obj->numSample!=NULL)&&(index<obj->numArr))
        {
            if((index2 <obj->numSample[index]))
            {
                p = &(obj->data[index][index2]);
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
    return p;
}
void destructInputDataManager(inputDataManager *obj)
{
    int index=0;
    if(obj!=NULL)
    {
        obj->m_isIncludeTestToCrossVal =0;
        if(obj->m_dataFormat !=NULL)
        { 
            for(index=0;index<obj->m_numFile;index++)
            {
                makeDataFormatEmpty(&(obj->m_dataFormat[index]));
            }
            free(obj->m_dataFormat);
            obj->m_dataFormat = NULL;
        }
        else
        {
            /* do nothing */
        } 
        clearOnePointerArr((void**)&(obj->m_bufferData));
        clearOnePointerArr((void**)&(obj->m_listOrderPosOfData)); 
        deallocateLogReadFileDataSetArray(&(obj->m_logReadFileDataSetObj),obj->m_numTrainingFile);
        destructDataSetContainer(&(obj->m_dataSet));
        clearMt22d(&(obj->m_dataSet2));
    /* temporary print for displaying the detail about tree 24 April 2016 12:00  */
    printf("--------------------------------------\n");
    printf("Nd is the count variable in a tree,\nrc is result of counting node in a tree,\nAd is the result from  searchTheTreeForContainTheNode\n");
    printf("--------------------------------------\n");
    printf("T#(Nd,rc,Ad)\n");
    /*End of temporary print for displaying the detail about tree 24 April 2016 12:00  */
        deallocatStatisDataLogArray(&(obj->m_statisDataObj),1);
        deallocatStatisDataLogArray(&(obj->m_statisDataEachClassObj),obj->m_numClass);
        destructIdenClsTT44InpDatMgr(&(obj->m_identifyClassT));
        destructGroupVariableSdv(&(obj->m_summaryDataStatistic));
        obj->m_logReadFileDataSetObj = NULL;
        obj->m_statisDataObj = NULL;
        obj->m_statisDataEachClassObj = NULL;
        obj->m_numFile =0;
        obj->m_numDim =0;
        obj->m_numOutDim =0;
        obj->m_numClass =0;
        obj->m_numTrainingFile =0;
        obj->m_numTestingFile =0;
        obj->m_buffSize = 0;
        obj->m_taskToGet = NULL;
        obj->m_numSharedFile =0;
        obj->m_numRealClass =0;
        obj->m_numValidSamples =0;
        obj->m_param1 =NULL;
        obj->m_param2 =NULL;
    }
    else
    {
        /* do nothing */
    }
}
void constructorInputDataManager(inputDataManager* obj)
{
    if(obj!=NULL)
    {
        /* jui 30 April 2017, 26 June 2017
            0 = is not arr fixed size
            1 = is arr fixed size
        */
        obj->m_inputType=1; 
        obj->m_taskToGet = NULL;
        obj->m_isIncludeTestToCrossVal =0;
        obj->m_numFile =0;
        obj->m_numDim =0;
        obj->m_numOutDim =0;
        obj->m_numClass =0;
        obj->m_numTrainingFile =0;
        obj->m_numTestingFile =0;
        obj->m_numRealClass =0;
        obj->m_numValidSamples =0;
        obj->m_logReadFileDataSetObj =NULL;
        obj->m_statisDataEachClassObj =NULL;
        obj->m_statisDataObj =NULL;
        obj->m_dataFormat =NULL;
        obj->m_bufferData =NULL;
        obj->m_listOrderPosOfData =NULL;
        constructGroupVariableSdv(&(obj->m_summaryDataStatistic),obj->m_numDim,obj->m_numOutDim,obj->m_numClass,obj->m_inputType);
        constructorDataSetContainer(&(obj->m_dataSet));
        initiValInMt22d(&(obj->m_dataSet2));
        obj->m_numSharedFile =0;
        obj->m_res=1;
        constructIdenClsT4InpDatMgr(&(obj->m_identifyClassT),0);
        
        obj->m_param1 = NULL;
        obj->m_param2 = NULL;
        
        
        
    }
    else
    {
        /* do nothing */
    }
}

/* Identify class T(to fast compare) */
/* normal compare not used */
void constructIdenClsT4InpDatMgr(binaryTree *obj,int numDimOut) 
{
    if(obj!=NULL)
    {

        if(numDimOut>1)
        {
            /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
            constructAvlTree((void*)obj,1,"custom type 2",0,sizeof(vector_double));
            setDelKeyAndDelDataAndCompFnForAvlTree(obj,delVKey4InpDatMgr,delIdenClsTData4InpDatMgr,compVDouble4InpDatMgr); 
            obj->compareTypeWithOpt = NULL;
        }
        else
        {
            /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
            constructAvlTree((void*)obj,1,"double",0,sizeof(double));
            setDelKeyAndDelDataAndCompFnForAvlTree(obj,NULL,delIdenClsTData4InpDatMgr,compDouble4InpDatMgr); 
            obj->compareTypeWithOpt = NULL;
            setDelKeyFnForAvlTree(obj,NULL);
            setDelKeyFlag(obj,1);
        }
    }
    else
    {
        /* do noting */
    }
}
void delVKey4InpDatMgr(void *obj,void *data)
{
    vector_double** vd= (vector_double**)data;
    if(vd !=NULL)
    {
        if(*vd!=NULL)
        {
            delete_vector_double(*vd);
            free(*vd);
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
void delIdenClsTData4InpDatMgr(void *obj,void *data)
{
    int **tempInt = (int**)data;
    if(tempInt!=NULL)
    {
        if(*tempInt !=NULL)
        { 
 
            free(*tempInt);
            *tempInt =NULL;
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
 
int compVDouble4InpDatMgr(const void* a,const void *b)
{
    int res =UN_DEFINE;
    int index =0;
    int num =0;
    vector_double **va=NULL,**vb=NULL;
    if((a==NULL)||(b==NULL))
    {
        /* do nothing */
    }
    else if((*((vector_double**)a)!=NULL)&&(*((vector_double**)b)!=NULL))
    {
        va = ((vector_double**)a);
        vb = ((vector_double**)b);
        if((*va)->lenght > (*vb)->lenght)
        {
            num = (*vb)->lenght;
        }
        else
        {
            num =(*va)->lenght;
        }
        res =EQUAL_DEFINE;
        for(index=0;index<num;index++)
        {
            if((*va)->data[index]> (*vb)->data[index])
            {
                index=num;
                res = MORE_DEFINE; 
            }
            else if((*va)->data[index]< (*vb)->data[index])
            {
                index=num;
                res = LESS_DEFINE; 
            }
            else
            {
                /* do nothing */
            }
        }
        if((res ==EQUAL_DEFINE)&&((*va)->lenght == (*vb)->lenght))
        {
            /* do noting */
        }
        else if((res ==EQUAL_DEFINE)&&((*va)->lenght == num)&&((*vb)->lenght>num))
        {
            res = LESS_DEFINE;
        } 
        else if((res ==EQUAL_DEFINE)&&((*vb)->lenght == num)&&((*va)->lenght>num))
        {
            res = MORE_DEFINE;
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

int compDouble4InpDatMgr(const void* a,const void *b)
{
    int res =UN_DEFINE;
    double *aa=NULL,*bb=NULL;
    if((a==NULL)||(b==NULL))
    {
        /* do nothing */
    }
    else if((*((double**)a)!=NULL)&&(*((double**)b)!=NULL))
    {
        aa = *((double**)a);
        bb = *((double**)b);
        if(*aa> *bb)
        { 
            res = MORE_DEFINE;
        }
        else if(*aa< *bb)
        { 
            res = LESS_DEFINE;
        }
        else
        {
            res =EQUAL_DEFINE;
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}
void destructIdenClsTT44InpDatMgr(binaryTree *obj)
{
    if(obj!=NULL)
    { 
        clearBinaryTree(obj);
    }
    else
    {
        /* do noting */
    }
}
/* end methods of Identify class T */
void getTheQuantityValueToInputDataManager(inputDataManager *obj,taskMgr* taskMgrObj)
{
    int res = (obj!=NULL)&&(taskMgrObj!=NULL);
    if(res==1)
    {
        obj->m_taskToGet = taskMgrObj;
        obj->m_isIncludeTestToCrossVal = isIncludeTestSetsToCrossVal(obj->m_taskToGet);
        obj->m_numTrainingFile = getTrainingFileNumberFromTaskMgr(obj->m_taskToGet);
        obj->m_numTestingFile = getTestingFileNumberFromTaskMgr(obj->m_taskToGet);
        obj->m_numDim = getTheNumberOfFeatureInputFromTaskMgr(obj->m_taskToGet);
        obj->m_numOutDim = getTheNumberOfFeatureOutputFromTaskMgr(obj->m_taskToGet);
        obj->m_numClass = getTheNumberOfClassFromTaskMgr(obj->m_taskToGet);
        /*  # 014420012016*/
        obj->m_numFile = obj->m_numTrainingFile+((obj->m_isIncludeTestToCrossVal==1)*(obj->m_numTestingFile));
        constructIdenClsT4InpDatMgr(&(obj->m_identifyClassT),obj->m_numOutDim);
        obj->m_summaryDataStatistic.countMallo = obj->countMallo;
        constructGroupVariableSdv(&(obj->m_summaryDataStatistic),obj->m_numDim,obj->m_numOutDim,obj->m_numClass,obj->m_inputType);
    }
    else 
    {
        /* do nothing */
    } 
    if(obj!=NULL)
    {
        obj->m_res =(res==1)&&(obj->m_res==1);
        if(obj->m_res==0)
        {
            printf("failed at : %s %d in getTheQuantityValueToInputDataManager method\n",__FILE__,__LINE__);
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
void readDataFromFileToInputDataManager(inputDataManager *obj)
{
    FILE *fp=NULL; 
    char isNotCloseFileImmediately=0;
    int index=0;
    int index2=0;
    int res = verifyAllQuantityValueOfInputDataManager(obj);
    /* initial value of local variables */
    if(res==1)
    {
        res = (obj->m_res==1)&&(obj->m_listOrderPosOfData!=NULL)&&(obj->m_bufferData!=NULL);
        res = res&&((obj->m_dataFormat!=NULL)&&(obj->m_statisDataObj!=NULL));
    }
    else
    {
        /* do nothing */
    }
    /* start processing */
    if(res==1)
    {
        for(index=0;(index<obj->m_numFile)&&(obj->m_res==1);index++)
        {
            /* load/set fp to read data */
            loadFpAndLnAndIsNotCloseFileOfInputDataManager(obj,index,&fp,&index2,&isNotCloseFileImmediately);
            /* read data */
            readDataFromFileInInputDataManager(obj,index,fp,&index2);
            /* update old fp or close file */
            backupIndexAndFpInInputDataManager(obj,index,fp,index2,isNotCloseFileImmediately);
        }
    }
    else
    {
        /* do nothing */
    }
    if(obj!=NULL)
    {
        obj->m_res =(res==1)&&(obj->m_res==1);
        if(obj->m_res==0)
        {
            printf("failed at : %s %d in readDataFromFileToInputDataManage method\n",__FILE__,__LINE__);
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
void readDataFromFileInInputDataManager(inputDataManager *obj,int indexFile,FILE* fp,int* oldIndex)
{
    statisDataLogElement *missValueLog = NULL;
    int res = verifyAllQuantityValueOfInputDataManager(obj);
    int numEx = 0;
    int numTotalDim = 0;
    int countEx = 0;
    if(res==1)
    {
        res = res&&obj->m_res;

    }
    else
    {
        /* do nothing */
    }
    if(res ==1)
    { 
  
        if(indexFile<obj->m_numFile)
        {   
            numTotalDim = obj->m_numOutDim+obj->m_numDim;
            numEx = obj->m_dataFormat[indexFile].numSample;
            if(obj->m_inputType == 1)
            {
                if(indexFile==0)
                {
                    obj->m_dataSet2 = newMt22d(numEx,(obj->m_numDim + obj->m_numOutDim),sizeof(double),2);
                }
                else
                {
                    expandMt22dSizeWithSize(&(obj->m_dataSet2),numEx);
                }
            }
            else
            {
                res = newNumberSamplesInDataSetContainer(&(obj->m_dataSet),indexFile,numEx,(obj->m_numDim + obj->m_numOutDim));
                res = res&initialValueOfDataSetContainer(&(obj->m_dataSet),indexFile,-1);
            }
            /*obj->m_statisDataObj[indexFile].whichDataSet = getPointerOfArrFor1FileOfDataSetContainer(&(obj->m_dataSet),indexFile);*/
            res = delimiterSetValidate(&(obj->m_dataFormat[indexFile].delimeterFormat));
            res = res&validateBeforeConvertDataBytDataFormat(&(obj->m_dataFormat[indexFile]),obj->m_bufferData,&(obj->m_statisDataObj[0]),obj->m_listOrderPosOfData,numTotalDim);
            newArrVoidSt1D((void*)&missValueLog,sizeof(statisDataLogElement)*numTotalDim,&res);
            if(res==1)
            {
                while((res==1)&&(countEx<numEx)&&(fgets(obj->m_bufferData,DATA_BUFFER_SIZE,fp) != 0))
                {
                    res =dividedDataAttrbByNullChar(&(obj->m_dataFormat[indexFile].delimeterFormat),obj->m_bufferData,obj->m_listOrderPosOfData,numTotalDim,DATA_BUFFER_SIZE,obj->m_dataFormat[indexFile].orderAttrbStart);
                    res &= convertDataByDataFormat(obj,indexFile,countEx,missValueLog);
                    countEx++;
                    (*oldIndex)++;
                }
            }
            else
            {
                printf("failed while read data at index:%d\n",indexFile);
            }
            clearOnePointerArr((void**)&missValueLog);
        }
        else
        {
            res =0;
            printf("Trianing file: if--: %d \n",indexFile);
        }
    }
    else
    {
        /* do nothing */
    }
    if(obj!=NULL)
    {
        obj->m_res =(res==1)&&(obj->m_res==1);
        if(obj->m_res==0)
        {
            printf("failed at : %s %d in readDataFromFileInInputDataManager method\n",__FILE__,__LINE__);
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
void backupIndexAndFpInInputDataManager(inputDataManager *obj,int indexFile,FILE* fp,int oldIndex,char  status)
{
    int res = verifyAllQuantityValueOfInputDataManager(obj);
    if(res==1)
    {
        res = (obj->m_res==1)&&(oldIndex>=0);
        res = (res==1)&&(obj->m_logReadFileDataSetObj!=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(res==1)
    {
        if(status ==1)
        {
            res = addFilePointerAndLineNumberToLogReadFileDataSetArray(obj->m_logReadFileDataSetObj,obj->m_numSharedFile,fp,oldIndex,&(obj->m_dataFormat[indexFile].filename));
        }
        else if((status ==0)&&(fp!=NULL))
        {
            fclose(fp);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("member variables are failed to backupIndex.. fn : %d -- fp:%p , status:%d\n",__LINE__,fp,status);
    }
    if(obj!=NULL)
    {
        obj->m_res =(res==1)&&(obj->m_res==1);
        if(obj->m_res==0)
        {
            printf("failed at : %s %d in backupIndexAndFpInInputDataManager method\n",__FILE__,__LINE__);
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
void separateDatToEachClass4IntDatMgr(inputDataManager *obj)
{
    int res = verifyAllQuantityValueOfInputDataManager(obj); 
    void *rootN=NULL;
    traverseBuff trvObj;
    statisDataLog* objStatis =NULL;
    statisDataLog* objStatisClass =NULL;
    constructorTravBuff(&trvObj);
    if (res == 1 ) /* start work here */
    {
        objStatis = &(obj->m_statisDataObj[0]);
        objStatisClass = &(obj->m_statisDataEachClassObj[0]);
        /* identify class in main tree */
        rootN =getRootNodeOfMainTInSdl(objStatis);
        initValueOfTravBuff(&trvObj,objStatis,objStatisClass,obj->m_numClass,obj->m_numOutDim,obj->m_numDim,&(obj->m_identifyClassT),&(obj->m_summaryDataStatistic));
        res = traverseMainTMSamp2OthT4Sdl(&trvObj,rootN);
        /*
        printf("before add redundant to each class ---- \n");
        
        int index = 0;int num =0;
            randomArrFixSizeNBIn4Sdl(&(obj->m_statisDataObj[0]),0,-1);
    randomArrFixSizeNBIn4Sdl(&(obj->m_statisDataObj[0]),1,-1);
    randomArrFixSizeNBIn4Sdl(&(obj->m_statisDataObj[0]),2,-1);
    randomArrFixSizeNBIn4Sdl(&(obj->m_statisDataObj[0]),3,-1);
    randomArrFixSizeNBIn4Sdl(&(obj->m_statisDataObj[0]),4,-1);
        num = obj->m_numClass;
    for(index = 0;index < num ; index++)
    {
        randomArrFixSizeNBIn4Sdl(&(obj->m_statisDataEachClassObj[index]),0,-1);
        randomArrFixSizeNBIn4Sdl(&(obj->m_statisDataEachClassObj[index]),1,-1);
        randomArrFixSizeNBIn4Sdl(&(obj->m_statisDataEachClassObj[index]),2,-1);
        randomArrFixSizeNBIn4Sdl(&(obj->m_statisDataEachClassObj[index]),3,-1);
        randomArrFixSizeNBIn4Sdl(&(obj->m_statisDataEachClassObj[index]),4,-1);
    }
    printf("---------- end of redundant to each class \n");
        */
    }
    else
    {
        /* do nothing */
    }
    if(res ==1)
    {
        /* identify class in redundant tree */
        rootN =getRootNodeOfRedunTInSdl(objStatis);
        init2FindRedunTravBuff(&trvObj);
        res = traverseMainTMSamp2OthT4Sdl(&trvObj,rootN);
        updateGroupValSdvFromDataFormat4IntDatMgr(obj);
        summarizeGroupVariableSdv(&(obj->m_summaryDataStatistic));
        /*
          printGroupVariableSdv(&(obj->m_summaryDataStatistic));
          */
        obj->m_res =res;
    }
    else
    {
        /* do nothing */
    }
}
void updateGroupValSdvFromDataFormat4IntDatMgr(inputDataManager *obj)
{
    int index=0;
    int numFile=0;
    int num=0; 
    struct dataFormat *pDf=NULL; 
    int res = verifyAllQuantityValueOfInputDataManager(obj); 
    char *stvOpt=NULL;
    if(res==0)
    {
        /* do nothing */
    }
    else if(obj->m_dataFormat!=NULL)
    {
        pDf = obj->m_dataFormat;
        numFile = obj->m_numFile;
        newArrVoidSt1D((void*)&stvOpt,sizeof(char)*(obj->m_numDim),&res);
    }
    else
    {
        /* do nothing */
    }
    if(res==1)
    {    
        obj->m_param1 = (void*)stvOpt;
        num = obj->m_numDim;
        /*
        <!-- opt in <STATICS_VAL>  -1 or no is set to be default.(0)
                                  It is used when there are 2 or more values of mode or median
                                  0 is mean them
                                  1 is random choose -->
        */
        for(index=0;index<num;index++)
        {
            stvOpt[index] =0;
        }
        /* use last value from the latest file which setting m_stdOpt */
        for(index=0;index<numFile;index++)
        { 
            obj->m_param2 = (void*)&pDf[index];
            TransverseMissT2UpdateGroupValSdvFromDatFormat4IntDatMgr(pDf[index].convertor.m_missT.root,obj);
        }
        obj->m_param1=NULL;
        obj->m_param2=NULL;
        free(stvOpt);
        stvOpt=NULL;
    }
    else
    {
        /* do nothing */
    }
}
void fixMis2SampleVarSdv(inputDataManager *obj,int whichCls,void *incompNode)
{
    int index=0,count=0;
    int index2= 0;
    int numCls =0;
    char typeOfPut2Tree=-1;
    vector_double *vDoub =NULL;
    pVoidList *plist = NULL;
    struct statisDataLog *stdatEachClsobj=NULL;
    struct groupVariableSdv *pGValSdv =NULL;
    char res = (obj!=NULL)&&(incompNode!=NULL)&&(whichCls>=0);
    if(res==0)
    {
        /* do nothing */
    }
    else if((res==1)&&(whichCls <obj->m_numClass))
    {
        //jui 30 april 2017
        numCls = obj->m_numClass;
        pGValSdv = (struct groupVariableSdv*)&(obj->m_summaryDataStatistic);
        plist = (pVoidList*)getDataFromAvlNode(incompNode);
        count = countPVoidList(plist);
        stdatEachClsobj = obj->m_statisDataEachClassObj;
        for(index=0;index<count;index++)
        {
            typeOfPut2Tree =-1;
            res = fixMis2ASampleVarSdv(pGValSdv,whichCls,plist,index,&vDoub);
            if(res==1)/*can fix all dimensions*/
            {
                /* Add 2 Trees */
                /* filter level 1*/
                typeOfPut2Tree = searchTheTreeForContainTheNode(&(obj->m_statisDataObj[0]),(void*)vDoub,NULL,0);
               /* printf("Type to Tree : %d\n",typeOfPut2Tree);*/
                if(typeOfPut2Tree ==-1)
                {
                    index=count;
                    res=0;
                    printf("Errrrrrrrrrrrrrrrr cannot reconize type cls, File :%s, Ln: %d\n",__FILE__,__LINE__);
                }
                else if(typeOfPut2Tree==0)
                { 
                    /* filter level 2*/
                    for(index2=0;index2<numCls;index2++)
                    {
                        typeOfPut2Tree = searchTheTreeForContainTheNode(&(stdatEachClsobj[index2]),(void*)vDoub,NULL,0);
                        if(typeOfPut2Tree !=0)
                        {
                            index2=numCls;
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    if(typeOfPut2Tree==0)
                    {
                        addDataToStatisDataLog(&(stdatEachClsobj[whichCls]),vDoub,NULL,0);
                    }
                    else
                    {
                        obj->m_statisDataObj[0].m_totRejectReassignNode++;
                    }
                }
                else
                {
                    obj->m_statisDataObj[0].m_totRejectReassignNode++;
                    /* do nothing*/
                    /* found redundant or in consist */
                }
            }
            else /* can fix partial dimensions*/
            {
                res=0;
                index=count;
                printf("Can not fix this vector completed 123456, file:%s ,Ln:%d\n",__FILE__,__LINE__);
            }

         }
    }
    else
    {
        printf("res==0 and whichcls:%d at fixMis2SampleVarSdv, fn: %s ln:%d   \n",whichCls,__FILE__,__LINE__);
    }
}void fixMis2SampleVarSdv_NdFixNBin(inputDataManager *obj,int whichCls,void *incompNode)
{
    int index=0,count=0;
    int index2= 0;
    int numCls =0;
    char typeOfPut2Tree=-1;
    void *vDoub =NULL;
    pVoidList *plist = NULL;
    struct statisDataLog *stdatEachClsobj=NULL;
    struct groupVariableSdv *pGValSdv =NULL;
    char res = (obj!=NULL)&&(incompNode!=NULL)&&(whichCls>=0);
    if(res==0)
    {
        /* do nothing */
    }
    else if((res==1)&&(whichCls <obj->m_numClass))
    {
        //jui 30 april 2017
        numCls = obj->m_numClass;
        pGValSdv = (struct groupVariableSdv*)&(obj->m_summaryDataStatistic);
        plist = (pVoidList*)(((struct mat2Ele*)((struct nodeFixedArrNBIn*)(incompNode))->m_dat2)->m_startP);
        count = countPVoidList(plist);
        stdatEachClsobj = obj->m_statisDataEachClassObj;
        for(index=0;index<count;index++)
        {
            typeOfPut2Tree =-1;
            res = fixMis2ASampleVarSdv_NdFixNBin(pGValSdv,whichCls,plist,index,&vDoub);
            if(res==1)/*can fix all dimensions*/
            {
                /* Add 2 Trees */
                /* filter level 1*/
                typeOfPut2Tree = searchTheTreeForContainTheNode(&(obj->m_statisDataObj[0]),vDoub,NULL,0);
               /* printf("Type to Tree : %d\n",typeOfPut2Tree);*/
                if(typeOfPut2Tree ==-1)
                {
                    index=count;
                    res=0;
                    printf("Errrrrrrrrrrrrrrrr cannot reconize type cls, File :%s, Ln: %d\n",__FILE__,__LINE__);
                }
                else if(typeOfPut2Tree==0)
                { 
                    /* filter level 2*/
                    for(index2=0;index2<numCls;index2++)
                    {
                        typeOfPut2Tree = searchTheTreeForContainTheNode(&(stdatEachClsobj[index2]),vDoub,NULL,0);
                        if(typeOfPut2Tree !=0)
                        {
                            index2=numCls;
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    if(typeOfPut2Tree==0)
                    {
                        addDataToStatisDataLog(&(stdatEachClsobj[whichCls]),vDoub,NULL,0);
                    }
                    else
                    {
                        obj->m_statisDataObj[0].m_totRejectReassignNode++;
                    }
                }
                else
                {
                    obj->m_statisDataObj[0].m_totRejectReassignNode++;
                    /* do nothing*/
                    /* found redundant or in consist */
                }
            }
            else /* can fix partial dimensions*/
            {
                res=0;
                index=count;
                printf("Can not fix this vector completed 123456, file:%s ,Ln:%d\n",__FILE__,__LINE__);
            }

         }
    }
    else
    {
        printf("res==0 and whichcls:%d at fixMis2SampleVarSdv_NdFixNBin, fn: %s ln:%d   \n",whichCls,__FILE__,__LINE__);
    }
}
int findWhichClsInIdentityT4IntDatMgr(inputDataManager *obj,void *incompNode)
{
    int resIndex =-1;
    vector_double *pVect=NULL;
    vector_double tempVect;
    void *pVoid = NULL;
    void *pDat = NULL;
    if((obj!=NULL)&&(incompNode!=NULL))
    {
        binaryTree *pIdenT = &(obj->m_identifyClassT);
        /* search agaist with iden T*/
        pVect = *((vector_double**)pIdenT->getKey(incompNode));
        if(obj->m_numOutDim ==1)
        {
            pVoid=(void*)&(pVect->data[obj->m_numDim]);

        }
        else
        {
            tempVect.data = &(pVect->data[obj->m_numDim]);
            tempVect.lenght =  obj->m_numOutDim;
 
            /* search agaist with iden T*/  
            pVoid =(void*)&(tempVect);
        }
        pDat= searchDataInBinaryTree(pIdenT,&pVoid); 
        if(pDat != NULL)
        {
            resIndex =  *((int*)getDataFromAvlNode(pDat));
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
        
    return resIndex;
}

int findWhichClsInIdentityT4IntDatMgr_NdFixNBin(inputDataManager *obj,void *incompNode)
{
    int resIndex =-1;
    double *tmpDouble=NULL;
    vector_double tempVect;
    void *pVoid = NULL;
    void *pDat = NULL;
    binaryTree *tt = NULL;
    if((obj!=NULL)&&(incompNode!=NULL))
    {
        tt = (binaryTree*)(obj->m_param1);
        binaryTree *pIdenT = &(obj->m_identifyClassT);
        /* search agaist with iden T*/
        tmpDouble =(((double*)(((struct mat2Ele*)((*((struct mat2Ele**)tt->getKey(incompNode)))))->m_startP)));
        if(obj->m_numOutDim ==1)
        {
            pVoid=(void*)&(tmpDouble[obj->m_numDim]);

        }
        else
        {
            tempVect.data = &(tmpDouble[obj->m_numDim]);
            tempVect.lenght =  obj->m_numOutDim;
 
            /* search agaist with iden T*/  
            pVoid =(void*)&(tempVect);
        }
        pDat= searchDataInBinaryTree(pIdenT,&pVoid); 
        if(pDat != NULL)
        {
            resIndex =  *((int*)getDataFromAvlNode(pDat));
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
        
    return resIndex;
}
void TransverseMissT2UpdateGroupValSdvFromDatFormat4IntDatMgr(void *node,inputDataManager *obj)
{
    struct dataFormat *pDf=NULL;
    struct groupVariableSdv *pGVs =NULL;
    char *stvOpt=NULL;
    int *pInt =NULL;
    char *pCh = NULL;
    char *pAailVal=NULL;
    int index3=0;
    int num=0;
    binaryTree *pBinMiss =NULL;
    struct missingWord *pMissAttrb =NULL;
    /*
        obj->m_param1; keep char array
        obj->m_param2; keep &dataFormat[index]
        
    */
    if((node!=NULL)&&(obj!=NULL))
    {
        if(obj->m_param2!=NULL)
        {
            pDf = (struct dataFormat*)obj->m_param2; 
            pGVs = &(obj->m_summaryDataStatistic);
            stvOpt = (char*)obj->m_param1;
            pBinMiss = &(pDf->convertor.m_missT);
        }
        else
        {
            /* do nothing */
        }
        if(pBinMiss!=NULL)
        {
            pMissAttrb = *((missingWord**)pBinMiss->getKey(node));

            if(pMissAttrb!=NULL)
            {
                pInt = &(pMissAttrb->indexDim);
                pCh = &(pMissAttrb->m_optStatic);
                pAailVal = &(pMissAttrb->m_availVal);
            }
            else
            {
                /* do nothing */
            }
            if((pInt!=NULL)&&(pCh!=NULL))
            {
                if((*pInt!=-1)&&(*pInt<obj->m_numDim))
                {
                    num = pGVs->m_numClass; 
                    if(stvOpt[*pInt] == *pCh)
                    {
                        /* do nothing */
                    }
                    else /* set the value to */
                    {   
                        stvOpt[*pInt] = *pCh;
                        for(index3=0;index3<num;index3++)
                        {
                            pGVs->m_variables[index3][*pInt].m_sdOpt = *pCh;
                        }
                    }
                    for(index3=0;index3<num;index3++)
                    {
                        pGVs->m_variables[index3][*pInt].m_avail = *pAailVal;
                    }
                }
                else
                {
                    printf("Error indexD is invalid in TransverseMissT2UpdateGroupValSdvFromDatFormat4IntDatMgr l:%d\n",__LINE__);
                }
            }
            else
            {
                /* do nothing */
            }
            TransverseMissT2UpdateGroupValSdvFromDatFormat4IntDatMgr(pBinMiss->getNodeLeft(node),obj);
            TransverseMissT2UpdateGroupValSdvFromDatFormat4IntDatMgr(pBinMiss->getNodeRight(node),obj);
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
void clrMsValAndSeparate2ClsInIncomplT4IntDatMgr(inputDataManager *obj)
{
    int ret = verifyAllQuantityValueOfInputDataManager(obj); 
    statisDataLog* objStatis =NULL;
    void *anode =NULL;
    if(ret==0)
    {
        /* do nothing */
    }
    else if(obj->m_res ==1)
    {
        objStatis = &(obj->m_statisDataObj[0]);
        /* transverse Incomplete data tree*/
        anode = getRootNodeOfIncompTInSdl(objStatis);
        obj->m_param1 = &(objStatis->m_incompleteTree);
        obj->m_res = transverIncompT2SeparateCls4IntDatMgr(obj,anode);
        obj->m_param1 = NULL;
        countActualClsAndNumSample4IntDatMgr(obj);
    }
    else
    {
        /* do nothing */
    }
}
void randAllInputElementsOfEachClass4IntDatMgr(inputDataManager *obj)
{
    int numMainT = 0;
    int numAllT = 0;
    int ret = verifyAllQuantityValueOfInputDataManager(obj); 
    int num =0;
    int index = 0;
    if(ret==0)
    {
        printf("Invalid process InputDatManage->ret:%d, Fl:%s, ln:%d \n",obj->m_res,__FILE__,__LINE__);
    }
    else if(obj->m_inputType == 1) /*0 (default) = vector version1 or 1 = version 2 (Mt22d)*/
    {
        num = obj->m_numClass;
        for(index = 0;index < num;index++)
        {
            numMainT = getNumOfMainTDataInStatisDataLog(&(obj->m_statisDataEachClassObj[index]));
            numAllT = getnumOfAllTDatInSdl(&(obj->m_statisDataEachClassObj[index]));
            if(numAllT ==0)
            {
                /* do nothing */
            }
            else if(numMainT == numAllT)
            {
                            /* 
                2017 June 27
                swap value between element in the array
                 this is used for Statitis data log of each class 
                0 = is main Tree
                1 = is redundant tree
                2 = is inconsistent tree
                3 = is incomplete tree
                4 = is discard tree
                */
                /*
                printf("\n112------ jui28071990 -----\n");
                printMt22d((struct mat2_2d *)(obj->m_statisDataEachClassObj[index].m_mainT.parameter3));
                printf("\n113------ jui28071990 -----\n");
                */
                randomArrFixSizeNBIn4Sdl(&(obj->m_statisDataEachClassObj[index]),0,rand()%numMainT);
                /*
                printMt22d((struct mat2_2d *)(obj->m_statisDataEachClassObj[index].m_mainT.parameter3));
                printf("\n114------ jui28071990 -----\n");
                */
            }
            else
            {
                printf("10:This intManage:%p, T(s) are not equal, Fl:%s, ln:%d\n",obj,__FILE__,__LINE__);
                printf("numMT:%d, numAT:%d\n",numMainT,numAllT);
            }
        }
        
    }
    else
    {
        
    }
}
int transverIncompT2SeparateCls4IntDatMgr(inputDataManager *obj,void *incompNode)
{
    /* obj->m_param1 is binaryTree pointer */
    int res =(obj!=NULL);
    int whichCls =0;
    binaryTree *pBin = NULL; 
    if((res==1)&&(incompNode!=NULL))
    {
        pBin = (binaryTree*)obj->m_param1;
        if(obj->m_inputType == 0)
        {
            whichCls = findWhichClsInIdentityT4IntDatMgr(obj,incompNode);
            /* printf("ele---------------- cls:%d\n",whichCls);*/
            fixMis2SampleVarSdv(obj,whichCls,incompNode); 
        }
        else
        {
            whichCls = findWhichClsInIdentityT4IntDatMgr_NdFixNBin(obj,incompNode);
            fixMis2SampleVarSdv_NdFixNBin(obj,whichCls,incompNode);
        }
    }
    else
    {
        /* do nothing */
    }
    if(pBin !=NULL)
    {
        res = res&transverIncompT2SeparateCls4IntDatMgr(obj,pBin->getNodeLeft(incompNode));
        res = res&transverIncompT2SeparateCls4IntDatMgr(obj,pBin->getNodeRight(incompNode));
    }
    else
    {
        /* do nothing */
    }
    return res;
}

void countActualClsAndNumSample4IntDatMgr(inputDataManager *obj)
{
    int index =0;
    int countCls = 0;
    int countMem = 0;
    int sum1 = 0;
    int numCls = 0;
    if(obj!=NULL)
    {
        numCls = obj->m_numClass;
        for(index=0;index<numCls;index++)
        {
            countMem =getNumOfMainTDataInStatisDataLog(&(obj->m_statisDataEachClassObj[index]));
            sum1 += countMem;
            if(countMem>0)
            {
                /*printf("m %d: %d\n",countCls,countMem);*/
                countCls++;
            }
            else
            {
                /* do nothing */
            }
        }
        obj->m_numValidSamples = sum1;
        obj->m_numRealClass = countCls;
    }
    else
    {
        /* do nothing */
    }
}

int getThenumOfTrainEx(inputDataManager *obj)
{
    struct taskMgr *objT =NULL;
    int numExInmainT =0;
    int num =0;
    int numExInTask = 0;
    int numTestExInTask = 0;
    float tempF =0.0;
    if(obj!=NULL)
    {
        objT = obj->m_taskToGet;
        numExInTask  = getTrainingNumberFromTaskMgr(objT);
        numTestExInTask  = getTestingNumberFromTaskMgr(objT);
        numExInmainT = obj->m_numValidSamples;
        if((numExInTask<0)&&(numTestExInTask>0)&&(numTestExInTask<numExInmainT))
        {
            num = numExInmainT-numTestExInTask;
        }
        else if((numExInTask >=numExInmainT)||(numTestExInTask >=numExInmainT)||((numExInTask+numTestExInTask)>numExInmainT))
        {
            printf("1 nExT:%d, nTestE:%d, mT:%d \n",numExInTask,numTestExInTask,numExInmainT);
            tempF = (((float)DEFAULT_PERCEN_NUM_SAM)/100.0)*((float)numExInmainT);
            num = (int)tempF;
        }
        else if((numExInTask<numExInmainT)&&(numExInTask>0))
        {
            num = numExInTask;
        }
        else if((numExInTask<0)&&(numTestExInTask<0)&&(numExInmainT>0))
        {
            printf("2 nExT:%d, nTestE:%d, mT:%d \n",numExInTask,numTestExInTask,numExInmainT);
            tempF = (((float)DEFAULT_PERCEN_NUM_SAM)/100.0)*((float)numExInmainT);
            num = (int)tempF;
        }
        else
        {
            num =-1;
        }
    }
    else
    {
        /* do nothing */
    }
    return num;
}
int getThenumOfTestEx(inputDataManager *obj)
{
    struct taskMgr *objT =NULL;
    int numExInmainT =0;
    int num =0;
    int numExInTask = 0;
    int numTestExInTask = 0;
    float tempF =0.0;
    if(obj!=NULL)
    {
        objT = obj->m_taskToGet;
        numExInTask  = getTrainingNumberFromTaskMgr(objT);
        numTestExInTask  = getTestingNumberFromTaskMgr(objT);
        numExInmainT = getNumOfMainTDataInStatisDataLog(obj->m_statisDataObj);
        if((numTestExInTask<0)&&(numExInTask>0)&&(numExInTask<numExInmainT))
        {
            num = numExInmainT-numExInTask;
        }
        else if((numExInTask >=numExInmainT)||(numTestExInTask >=numExInmainT)||((numExInTask+numTestExInTask)>numExInmainT))
        {
            tempF = (((float)DEFAULT_PERCEN_NUM_SAM)/100.0)*((float)numExInmainT);
            num =numExInmainT- (int)tempF;
        }
        else if((numTestExInTask<numExInmainT)&&(numTestExInTask>0))
        {
            num = numTestExInTask;
        }
        else if((numExInTask<0)&&(numTestExInTask<0)&&(numExInmainT>0))
        {
            tempF = (((float)DEFAULT_PERCEN_NUM_SAM)/100.0)*((float)numExInmainT);
            num =numExInmainT- (int)tempF;
        }
        else
        {
            num =-1;
        }
    }
    else
    {
        /* do nothing */
    }
    return num;
}

void loadFpAndLnAndIsNotCloseFileOfInputDataManager(inputDataManager *obj,int indexFile,FILE** fp,int* oldIndex,char *status)
{
    char *pFile = NULL; 
    int res = verifyAllQuantityValueOfInputDataManager(obj);
    res = res&&(fp!=NULL)&&(status!=NULL)&&(oldIndex!=NULL)&&(indexFile>=0);
    if(res==1)
    {
        res = (res==1)&&(obj->m_res==1);
    }
    else
    {
        /* do nothing */
    }
    if(res==1)
    { 
            pFile = obj->m_dataFormat[indexFile].filename.data;
            //*oldIndex =obj->m_dataFormat[indexFile].numSample;
            *status = checkSharedFileInLodReadFileDataSetArray(obj->m_logReadFileDataSetObj,obj->m_numSharedFile,&(obj->m_dataFormat[indexFile].filename));
            loadFilePointerAndLineNumberToLogReadFileDataSetArray(obj->m_logReadFileDataSetObj,obj->m_numSharedFile,fp,oldIndex,&(obj->m_dataFormat[indexFile].filename));
            if(*fp == NULL)
            {
                *fp = fopen(pFile,"r");
                *oldIndex=0;
            }
            else
            {
                if(obj->m_dataFormat[indexFile].lineStart < *oldIndex)
                {
                    *fp = fopen(pFile,"r");
                    *oldIndex=0;
                    addFilePointerAndLineNumberToLogReadFileDataSetArray(obj->m_logReadFileDataSetObj,obj->m_numSharedFile,*fp,*oldIndex,&(obj->m_dataFormat[indexFile].filename));
                }
                else
                {
                    /* do nothing */
                }
                if(obj->m_dataFormat[indexFile].lineStart > *oldIndex)
                {
                    while(((obj->m_dataFormat[indexFile].lineStart- *oldIndex)!=0) &&(fgets(obj->m_bufferData,DATA_BUFFER_SIZE,*fp) != 0))
                    {
                        (*oldIndex)++;
                    }
                }
                else
                {
                    /* do nothing */
                }
            } 
            res = ((*fp)!=NULL)&&((*oldIndex)>=0);
    }
    else
    {
        /* do nothing */
    }
    if(obj!=NULL)
    {
        obj->m_res =(res==1)&&(obj->m_res==1);
        if(obj->m_res==0)
        {
            printf("failed at : %s %d in loadFpAndLnAndIsNotCloseFileOfInputDataManager method\n",__FILE__,__LINE__);
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
void setReturnValueOfInputDataManager(inputDataManager* obj,int val)
{
    if(obj!=NULL)
    {
        obj->m_res = (obj->m_res==1)&&(val==1);
    }
    else
    {
        /* do nothing */
    }
}
void getTraingDataFromTaskObjToInputDataManager(taskMgr* taskMgrObj,inputDataManager *inputDataManagerObj)
{
    clock_t timeCount =clock();
    int res =(taskMgrObj != NULL)&&(inputDataManagerObj!=NULL);
    /* read test flags for cross-validation */
    /* get the number of training files */
    /* get the number of testing files */
    /* calcuate the total number of files which is read */
    setReturnValueOfInputDataManager(inputDataManagerObj,res);
timeCount = clock()-timeCount;
printf("t4 setReturnValueOfInputDataManager Time : %f \n",((float)timeCount)/CLOCKS_PER_SEC);
timeCount = clock();
    getTheQuantityValueToInputDataManager(inputDataManagerObj,taskMgrObj);
timeCount = clock()-timeCount;
printf("t4 getTheQuantityValueToInputDataManager Time : %f \n",((float)timeCount)/CLOCKS_PER_SEC);
timeCount = clock();
    startInitialAllVariableOfInputDataManager(inputDataManagerObj);
timeCount = clock()-timeCount;
printf("t4 startInitialAllVariableOfInputDataManager Time : %f \n",((float)timeCount)/CLOCKS_PER_SEC);
timeCount = clock();
    /* read data from file */ 
    readDataFromFileToInputDataManager(inputDataManagerObj); 
timeCount = clock()-timeCount;
printf("t4 readDataFromFileToInputDataManager Time : %f \n",((float)timeCount)/CLOCKS_PER_SEC);
timeCount = clock();
    /*  separate sample to each class */
    /* initial buffer for calculating Statis vlalue */
    /*  cal statistisc value of each class and each dimension */
    separateDatToEachClass4IntDatMgr(inputDataManagerObj);

timeCount = clock()-timeCount;
printf("t4 separateDatToEachClass4IntDatMgr Time : %f \n",((float)timeCount)/CLOCKS_PER_SEC);
timeCount = clock();
    /* clear missing, statis value, random value, etc*/ 
    /* repair incomplete tree */
    clrMsValAndSeparate2ClsInIncomplT4IntDatMgr(inputDataManagerObj);
timeCount = clock()-timeCount;
printf("clrMsValAndSeparate2ClsInIncomplT4IntDatMgr Time : %f \n",((float)timeCount)/CLOCKS_PER_SEC);

    
    /* cross validation phase */ 
        /* random order of input elements    */
        timeCount = clock();
    randAllInputElementsOfEachClass4IntDatMgr(inputDataManagerObj);
timeCount = clock()-timeCount;
printf("randAllInputElementsOfEachClass4IntDatMgr Time : %f \n",((float)timeCount)/CLOCKS_PER_SEC);
} 

void timerStart(clock_t* t)
{
    *t = clock();
}
float timeBreak(clock_t* t)
{
    return (float)(clock()-*t)/CLOCKS_PER_SEC;
}

/* numSamOfCls methods */
void constructNumSamOfCls(numSamOfCls *obj,int *ret)
{
    int fact = (obj!=NULL)&&(ret!=NULL);
    if(fact==1)
    {
        obj->m_index      =-1;
        obj->m_numSam     = 0;
        obj->m_numRealSam = 0;
        obj->m_numTrain   = 0;
        obj->m_numTest    = 0;
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
void assignAVal2NumSamOfCls(numSamOfCls *obj,inputDataManager *objI,int index,int *ret)
{
    int fact = (index>=0)&&(obj!=NULL)&&(objI!=NULL)&&(ret!=NULL);
    int numSamp=0;
    if(fact ==1)
    {
        numSamp = getNumOfMainTDataInStatisDataLog(&(objI->m_statisDataEachClassObj[index]));
        obj->m_index =index;
        obj->m_numSam =numSamp;
        obj->m_numRealSam =numSamp;
    }
    else if(ret !=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}

void swapIntValue(int *a,int *b,int *ret)
{
    int fact = (a!=NULL)&&(b!=NULL)&&(ret!=NULL);
    int temp=0;
    if(fact==1)
    {
        temp = *a;
        *a = *b;
        *b = temp;
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
void swapNumSamOfCls(numSamOfCls *obj,numSamOfCls *objB,int *ret)
{
    int fact = (obj!=NULL)&&(objB!=NULL)&&(ret!=NULL);
    if(fact==1)
    {
        swapIntValue(&(obj->m_index),&(objB->m_index),ret);
        swapIntValue(&(obj->m_numSam),&(objB->m_numSam),ret);
        swapIntValue(&(obj->m_numRealSam),&(objB->m_numRealSam),ret);
        swapIntValue(&(obj->m_numTrain),&(objB->m_numTrain),ret);
        swapIntValue(&(obj->m_numTest),&(objB->m_numTest),ret);
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
void assignVal2NumSamOfCls(clsDivision *obj,inputDataManager *objI,int *ret)
{
    int temp1=0;
    int temp2=0;
    int index =0;
    int index2=0;
    int index3=0;
    int strPoint =0;
    int numLoop=0;
    int numSamp=0;
    int numTrainEx=0;
    int numTestEx=0;
    int numAvgSamPerCls =0;
    int numLeftSam =0;
    int fraction =0;
    int sum =0;
    int numCls=0;
    int numClsLeft=0;
    int fact = (obj!=NULL)&&(objI!=NULL)&&(ret!=NULL);
    int isDivideOk =-1; /* undefined */
    struct numSamOfCls *objl =NULL;
    float trainExpercentT =0.0;
    if(fact==1)
    {
        objl = obj->m_samDetail;
        numTrainEx = getThenumOfTrainEx(objI);
        numTestEx = getThenumOfTestEx(objI);
        obj->m_numTrainSam = numTrainEx;
        numCls     =  objI->m_numRealClass;
        numLeftSam =  numTrainEx+numTestEx;
        trainExpercentT = ((float)numTrainEx)/((float)numLeftSam);
        printf("Perce train : %f , test%f\n",trainExpercentT,1-trainExpercentT);
        
        sum =0;
        index3 =0;
        isDivideOk=0;
        index=0;
    }
    else
    {
        /* do nothing */
    }        
    while(isDivideOk==0)
    {
        index2 = numCls-1;
        strPoint = index3;
        numClsLeft = numCls-index3;
        numLeftSam = numLeftSam-sum;
        numAvgSamPerCls = numLeftSam/numClsLeft;
        fraction = numLeftSam%numClsLeft;
        sum =0;
        isDivideOk=1;
        for(index=strPoint;index<numCls;index++)
        {
            if(index3<numCls)
            {
                numSamp = objl[index3].m_numSam;
            }
            else
            {
                *ret =0;
            }
            if((numSamp==0)||(objl[index3].m_index ==-1))
            {
                assignAVal2NumSamOfCls(&objl[index3],objI,index,ret);
                numSamp = objl[index3].m_numSam;
            }
            else
            {
                /* do nothing */
            }
            fact = (numSamp > numAvgSamPerCls)||((numSamp >=numAvgSamPerCls)&&(fraction==0));
            if((fact ==1)&&(index2>-1)&&(index2<numCls))
            {
                swapNumSamOfCls(&objl[index3],&objl[index2],ret);
                objl[index2].m_numRealSam = numAvgSamPerCls;
                objl[index2].m_numTrain =(int)(0.5+trainExpercentT*(float)numAvgSamPerCls);
                objl[index2].m_numTest = objl[index2].m_numRealSam-objl[index2].m_numTrain;
                index2--;
                strPoint =index2;
            }
            else
            {
                isDivideOk =0;
                objl[index3].m_numRealSam = numSamp;
                if(numSamp ==1)
                {
                    objl[index3].m_numTrain =randomFx(numSamp,0);
                }
                else if(((int)(0.5+trainExpercentT*(float)numSamp))==numSamp)
                {
                    objl[index3].m_numTrain = numSamp-1;
                }
                else
                {
                    objl[index3].m_numTrain =(int)(0.5+trainExpercentT*(float)numSamp);
                }
                if(objl[index3].m_numTrain ==0)
                {
                    obj->numTrainCls--;
                }
                else
                {
                    /* do nothing */
                }
                objl[index3].m_numTest = objl[index3].m_numRealSam-objl[index3].m_numTrain;
                sum +=numSamp;
                index3++;
            }
            
            if(*ret==0)
            {
                /* abort work */
                isDivideOk =-1;/* undefined */
                index = numCls;
                fraction=0;
                sum =0;
                index3 =0;
            }
            else
            {
                /* do nothing */
            }
        }
    }
    if(isDivideOk!=-1)
    {
        numLoop = numCls-index3;
        index2 = numCls-1;
        while(numLoop!=0)
        {
            swapNumSamOfCls(&objl[randomFx(index2,index3)],&objl[randomFx(index2,index3)],ret);
            numLoop--;
        }
    }
    else
    {
        /* do nothing */
    }
    index=numCls-1;
    printf("fraction:%d index3 : %d , TrainClsLeft:(%d/%d) \n",fraction,index3,obj->numOFNumSamOfCls,obj->numTrainCls);
    while(fraction!=0)
    {
        index = index%numCls;
        fact = (objl[index].m_numSam > objl[index].m_numRealSam);
        objl[index].m_numRealSam += fact;
        if(fact==1)
        {
            objl[index].m_numTrain =(int)(0.5+trainExpercentT*(float)objl[index].m_numRealSam);
            objl[index].m_numTest = objl[index].m_numRealSam-objl[index].m_numTrain;
        }
        else
        {
            /* do nothing */
        }
        fraction -=fact;
        index--;
    }
    /* check the number of both side*/
    sum =0;
    for(index=0;index<numCls;index++)
    {
        sum += objl[index].m_numTrain;
    }
    if(sum<numTrainEx)
    {
        temp1=1;
        temp2=-1;
        fraction = numTrainEx-sum;
    }
    else if(sum>numTrainEx)
    { 
        temp1=-1;
        temp2=1;
        fraction = sum-numTrainEx;
    }
    else
    {
        fraction =0;
    }
    index=numCls-1;
    while(fraction!=0)
    {   
        if(index3>index)
        {
            index = numCls-1;
        }
        else
        {
            /* do nothing */
        }
        if(objl[index].m_numRealSam >0)
        {
            objl[index].m_numTrain +=temp1;
            objl[index].m_numTest +=temp2;
            fraction--;
        }
        else
        {
           /* do nothing */
        }
        index--;
    }
}
/* end of  numSamOfCls methods */
/* clsDivision methods*/
void constructClsDivision(clsDivision *obj,int numCls,int *ret)
{
    int index=0;
    if((obj!=NULL)&&(numCls >=0)&&(ret!=NULL))
    {
        obj->numOFNumSamOfCls = 0;
        obj->numTrainCls = 0;
        obj->m_samDetail = NULL;
        obj->m_numTrainSam =0;
        if(numCls >0)
        {
            newArrVoidSt1D((void*)&(obj->m_samDetail),sizeof(struct numSamOfCls)*numCls,ret);
        }
        else
        {
            /* do  nothing */
        }
        if((obj->m_samDetail != NULL)&&(numCls>0))
        {
            obj->numOFNumSamOfCls = numCls;
            obj->numTrainCls = numCls;
            for(index=0;index<numCls;index++)
            {
                constructNumSamOfCls(&(obj->m_samDetail[index]),ret);
            }
        }
        else if(numCls==0)
        {
            /* do nothing */
        }
        else
        {
            *ret = 0;
        }
    }
    else if(ret !=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
void destructClsDivision(clsDivision *obj)
{    
    if(obj!=NULL)
    {
        obj->numOFNumSamOfCls = 0;
        obj->m_numTrainSam = 0;
        obj->numTrainCls = 0;
        clearOnePointerArr((void**)&(obj->m_samDetail));
        obj->m_samDetail = NULL;

    }
    else
    {
        /* do nothing */
    }
}
/* end of clsDivision methods*/

/* foldDetailEle methods*/
void constructFoldDetailEle(foldDetailEle *obj,int *ret)
{
    if((obj!=NULL)&&(ret!=NULL))
    {
        obj->m_indexCls =-1;
        obj->m_numEx    =0;
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
void printFoldDetailEle(foldDetailEle *obj)
{
    if(obj!=NULL)
    {
        printf("iCls : %d, numEx:%d\n",obj->m_indexCls,obj->m_numEx);
    }
    else
    {
        /* do nothing */
    }
}
void destructFoldDetailEle(foldDetailEle *obj,int *ret)
{
    if((obj!=NULL)&&(ret!=NULL))
    {
        obj->m_indexCls =-1;
        obj->m_numEx    =0;
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
/* end of foldDetailEle methods*/

/* aFold methods*/
void constructAFold(aFold *obj,int numSam,int numArry,int *ret)
{
    int index=0;
    if((obj!=NULL)&&(ret!=NULL)&&(numArry>=0)&&(numSam>=0))
    {
        obj->m_dat   =NULL;
        obj->m_realUsedNum=0;
        obj->m_numMaxSam=0;
        obj->m_currIndex=-1;
        obj->m_numDat=0;
        if(numArry >0)
        {
            newArrVoidSt1D((void*)&(obj->m_dat),sizeof(foldDetailEle)*numArry,ret);
        }
        else
        {
            /* do  nothing */
        }
        if(*ret ==1)
        {
            obj->m_numMaxSam=numSam;
            obj->m_numDat = numArry;
            for(index=0;index<numArry;index++)
            {
                constructFoldDetailEle(&( obj->m_dat[index]),ret);
            }
        }
        else
        {
            /* do nothing */
        }
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
/*
 1 = full
 2 = ok
 3 = ok and full
*/
int setDat2AFold(aFold *obj,int indexCls,int num,int *remain1,int *ret)
{
    int sum=0;
    int remain=0;
    int currInd=0;
    int currCls=0;
    int index=0;
    int fact1 = (obj !=NULL)&&(indexCls>-1)&&(num >0)&&(ret!=NULL)&&(remain1!=NULL);
    /*printf("indexCl :%d, num:%d, fact1 :%d\n ",indexCls,num,*ret);*/
    if(fact1 == 1)
    {
        remain = obj->m_numMaxSam-obj->m_realUsedNum;
        currInd =obj->m_currIndex;
        sum = num; 
        if(obj->m_realUsedNum >=obj->m_numMaxSam)
        {
            /*printf("cond 1 ");*/
            fact1=1;
            obj->m_currIndex=-1;
        }
        else if((obj->m_realUsedNum+sum)==obj->m_numMaxSam)
        {
          /*  printf("cond 2 ");*/
            fact1=3;
        }
        else if((remain>0)&&(remain <sum))
        {
          /*  printf("cond 3 ");*/
            *remain1 = sum-remain;
            sum = remain;
            fact1=3;
        }
        else
        {
          /*  printf("cond 4 ");*/
            fact1=2;
        }  
        if(currInd ==-1)
        {
            currCls=obj->m_dat[0].m_indexCls;
        }
        else if(currInd >=obj->m_numDat)
        {
            obj->m_currIndex=-1;
            fact1 =0;
        }
        else
        {
            currCls=obj->m_dat[currInd].m_indexCls;
        }
        if(currCls !=indexCls)
        {                
            for(index=0;index<currInd;index++)
            {
                if(obj->m_dat[index].m_indexCls == indexCls)
                {
                    currInd =index;
                    obj->m_currIndex=index;
                    currCls = indexCls;
                    index = obj->m_numDat;
                }
                else
                {
                    /* do nohting */
                }
            }
            if(currCls != indexCls)
            {
                for(index=currInd+1;index<obj->m_numDat;index++)
                {
                    if(obj->m_dat[index].m_indexCls == indexCls)
                    {
                        currInd =index;
                        obj->m_currIndex=index;
                        currCls = indexCls;
                        index = obj->m_numDat;
                    }
                    else if(obj->m_dat[index].m_indexCls == -1)
                    {
                        currInd =index;
                        obj->m_currIndex=index;
                        currCls = indexCls;
                        index = obj->m_numDat;
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
        }
        else
        {
            /* do nothing */
        }
            
    }
    else if(ret !=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
    if((fact1>=2)&&(sum>0))
    {
        obj->m_dat[currInd].m_indexCls = indexCls;
        obj->m_dat[currInd].m_numEx += sum;
        obj->m_realUsedNum +=sum;
    }
    else
    {
        /* do nothing */
    }
    return fact1;
}
void printAFoldAndVerify(aFold *obj)
{
    int num=0;
    int index=0;
    char *nok="---NOk-j--";
    char *not="";
    char *pch =not;
    int sum =0;
    if(obj!=NULL)
    {
        num = obj->m_numDat;
        if(obj->m_numMaxSam ==obj->m_realUsedNum)
        {
            for(index=0;index<num;index++)
            {
                if(obj->m_dat[index].m_indexCls !=-1)
                {
                    sum += obj->m_dat[index].m_numEx;
                }
                else
                {
                    index =num;
                }
            }
            if(obj->m_numMaxSam != sum)
            {
                pch = nok;
            }
            else
            {
                /* do nohing */
            }
        }
        else
        {
            pch = nok;
        }
        printf("nId:%d (nD,nRel):(%d,%d)  %s\n",obj->m_numDat,obj->m_numMaxSam,obj->m_realUsedNum,pch);
        for(index=0;index<num;index++)
        {
            printFoldDetailEle(&(obj->m_dat[index]));
        }
    }
    else
    {
        /* do nothing */
    }
}
void destructAFold(aFold *obj,int *ret)
{
    if((obj!=NULL)&&(ret!=NULL))
    {
        clearOnePointerArr((void**)&(obj->m_dat));
        obj->m_numDat=0;
        obj->m_realUsedNum=0;
        obj->m_numMaxSam=0;
        obj->m_currIndex=-1;
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
/* end of aFold methods*/

/* akfold methods*/
void constructAkfold(akfold *obj,int num,int *ret)
{
    int index=0;
    if((obj!=NULL)&&(ret!=NULL)&&(num>=0))
    {
        obj->m_dat   =NULL;
        obj->m_numDat=0;
        if(num >0)
        {
            newArrVoidSt1D((void*)&(obj->m_dat),sizeof(aFold)*num,ret);
          /*  printf("new Akfold[%d]:%p \n",num,obj->m_dat);*/
        }
        else
        {
            /* do  nothing */
        }
        if(*ret ==1)
        {
            obj->m_numDat = num;
            for(index=0;index<num;index++)
            {
                constructAFold(&(obj->m_dat[index]),0,0,ret);
            }
        }
        else
        {
            /* do nothing */
        }
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}

void printAkFold(akfold *obj)
{
    int numFold =0;
    int index =0;
    if(obj!=NULL)
    {
        numFold = obj->m_numDat;
        printf("numFold : %d\n",numFold);
        for(index=0;index<numFold;index++)
        {
            printf("id:%d ",index);
            printAFoldAndVerify(&(obj->m_dat[index]));
        }
    }
    else
    {
        /* do noting */
    }
        
}
void setNumSam2AFofAKFold(akfold *obj,clsDivision *objC,int *ret)
{
    int index =0;
    int index2 =0;
    int index3=0;
    int indexStr=0;
    int num =0;
    int num2 =0;
    int remain=0;
    int numSamPerFold=0;
    int fraction;
    int preFraction =0;
    int numFold =0;
    int temp =0;
    int l_fraction =0;
    int ret2 =0;
    int l_numSmPerFold=0;
    int fact = (obj!=NULL)&&(objC!=NULL)&&(ret!=NULL);
    if(fact == 1)
    {
        fact = (obj->m_numDat>0)&&(objC->m_numTrainSam>0);
    }
    else if(ret !=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
    if(fact ==1)
    {
        l_numSmPerFold = (objC->m_numTrainSam/obj->m_numDat);
        l_fraction = (objC->m_numTrainSam%obj->m_numDat);
        numFold = obj->m_numDat;
        num = objC->numOFNumSamOfCls;
        printf("nSmPerFold:%d, frac:%d, Kf:%d rt:%d\n",l_numSmPerFold,l_fraction,obj->m_numDat,*ret);
        for(index=0;index<numFold;index++)
        {
            temp = l_numSmPerFold+((l_fraction--)>0);
            if(temp>num)
            {
                constructAFold(&(obj->m_dat[index]),temp,num,ret);
            }
            else
            {
                constructAFold(&(obj->m_dat[index]),temp,temp,ret);
            }
          /*  printf("-- numSam in a Fold : %d \n",temp);*/
        }
        indexStr=0;
        /* akfold *obj */
       /* printf("ret : %d\n",*ret);*/
        for(index=0;index<num;index++)
        {
            num2 = objC->m_samDetail[index].m_numTrain;
            numSamPerFold = num2/numFold;
            if(numSamPerFold>0)
            {
                for(index2=indexStr;index2<numFold;index2++)
                {
                    remain = 0;
                    /*printf("A  ");*/
                    ret2 = setDat2AFold(&(obj->m_dat[index2]),objC->m_samDetail[index].m_index,numSamPerFold,&remain,ret); 
/*printf("rm:%d rt:%d\n",remain,ret2);    */               
                    if((ret2==1)||(ret2==3))
                    {
                        indexStr= index2+1;
                    }
                    else
                    {
                        /* do nothing */
                    }
                    if((ret2==3)&&(remain>0))
                    {
                        printf("Is it used ? test for existing of this area: jj2 File:%s ln:%d \n",__FILE__,__LINE__);
                        index3 =0;
                        while(remain>0)
                        {                    
                            if((index2+index3)<numFold)
                            {
                     printf("B  ");
                                ret2 = setDat2AFold(&(obj->m_dat[index2+index3]),objC->m_samDetail[index].m_index,remain,&remain,ret);printf(" rt:%d\n",ret2);
                                if((ret2==1)||(ret2==3))
                                {
                                    indexStr= index2+1;
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
                            index3++;
                        }
                    }
                    if(*ret ==0)
                    {
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
        }
        ret2 =0;
        for(index=0;index<num;index++)
        {
            num2 = objC->m_samDetail[index].m_numTrain;
            fraction = num2%numFold;
            /*printf("stFraction :%d\n",fraction);*/
            do
            {
                preFraction= fraction;
                for(index2=0;index2<numFold;index2++)
                {
                    if(fraction >0)
                    {
                        remain =0;
                        /*   printf("C  id:%d ",index2);*/
                        ret2 = setDat2AFold(&(obj->m_dat[index2]),objC->m_samDetail[index].m_index,(fraction>0),&remain,ret);
                        /*  printf(" rt:%d\n",ret2);*/
                    }
                    else
                    {
                        ret2=0;
                        index2= numFold;
                    }
                    if((ret2 >=2)&&(index2!=numFold))
                    {
                        fraction--;
                    }
                    else
                    {
                        /* do nothign */
                    }

                    if(*ret ==0)
                    {
                        break;
                    }
                    else
                    {
                        /* do nothing */
                    } 
                } 
                /*printf("result Fraction : %d, cls:%d, \n",fraction,objC->m_samDetail[index].m_index);*/
                if((preFraction==fraction)&&(fraction!=0))
                {
                    printf("Error in setNumSam2AFofAKFold method ln:%d , fract:%d\n",__LINE__,fraction);
                    fraction=0;
                }
                else
                {
                    /* do nothing */
                }
             }while(fraction >0); 
        }
    }
    else if(ret !=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
void destructAkfold(akfold *obj,int *ret)
{
    int index=0;
    int num = 0;
    if((obj!=NULL)&&(ret!=NULL))
    {
        num = obj->m_numDat;
        for(index=0;index<num;index++)
        {
            destructAFold(&(obj->m_dat[index]),ret);
        }
        clearOnePointerArr((void**)&(obj->m_dat));
        obj->m_numDat=0;
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
/* end of akfold methods*/
/* kFoldSet methods*/
void constructKFoldSet(kFoldSet *obj,int num,int *ret)
{
    int index=0;
    if((obj!=NULL)&&(ret!=NULL)&&(num>=0))
    {
        obj->m_dat   =NULL;
        obj->m_numDat=0;
        if(num >0)
        {
            newArrVoidSt1D((void*)&(obj->m_dat),sizeof(akfold)*num,ret);
          /* printf("new fold set[%d] : %p \n",num,obj->m_dat);*/
        }
        else
        {
            /* do  nothing */
        }
        if(*ret ==1)
        {
            obj->m_numDat = num;
            for(index=0;index<num;index++)
            {
                constructAkfold(&(obj->m_dat[index]),0,ret);
            }
        }
        else
        {
            /* do nothing */
        }
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}

void divideNumSam2EachKFold(kFoldSet *obj,clsDivision *objC,int *ret)
{
    int index=0;
    akfold *akFObj = NULL;
    int l_numL =0;
    int fact = (obj!=NULL)&&(objC != NULL)&&(ret != NULL);
    if(fact == 1)
    {
        fact = (objC->m_numTrainSam >0)&&(objC->numTrainCls >0)&&(obj->m_numDat >0)&&(*ret==1);
    }
    else
    {
        /* do nothing */
    }
    if(fact == 1)
    {
        l_numL = obj->m_numDat;
        for(index=0;index<l_numL;index++)
        {
            akFObj = &(obj->m_dat[index]);
            if(akFObj != NULL)
            {
                setNumSam2AFofAKFold(akFObj,objC,ret);
                printAkFold(akFObj);
            }
            else
            {
                /* do nohing */
            }
        }
    }
    else
    {
        /* do nothing */
    }
}
void setAkfoldInKFoldSet(kFoldSet *obj,int whichIndex,int num,int *ret)
{
    int fact = ((obj!=NULL)&&(whichIndex>-1)&&(num>-1)&&(ret!=NULL));
    if(fact ==1)
    {
        fact = (obj->m_numDat > whichIndex);
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
    if(fact ==1)
    {
        destructAkfold(&(obj->m_dat[whichIndex]),ret);
        constructAkfold(&(obj->m_dat[whichIndex]),num,ret);
        /*printf("i:%d \n",whichIndex);*/
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
void destructKFoldSet(kFoldSet *obj,int *ret)
{
    int index=0;
    int num =0;
    if((obj!=NULL)&&(ret!=NULL))
    {
        num = obj->m_numDat;
        for(index=0;index<num;index++)
        {
            destructAkfold(&(obj->m_dat[index]),ret);
        }
        clearOnePointerArr((void**)&(obj->m_dat));
        obj->m_numDat=0;
    }
    else if(ret!=NULL)
    {
        *ret =0;
    }
    else
    {
        /* do nothing */
    }
}
/* end of kFoldSet methods*/