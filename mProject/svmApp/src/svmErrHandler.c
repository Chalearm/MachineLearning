#include <stdlib.h>
#include <stdio.h>
#include "svmErrHandler.h"
#define NAME_INPUT_FAILED -2
#define TASK_FILE_FAILED -1
#define FILE_MGR_FAILED 0
#define FILE_OK 1
/*-------------------------------- DEFINED XML KEY SESSION -------------*/
#define STR_PRINT                           "print"
#define STR_CURRENT_PATH                    "CURRENT_PATH"
#define STR_TASK                            "TASK"
#define STR_NAME                            "name"
#define STR_TASK_USE                        "use"
#define STR_DATA_SET_PATH                   "DATA_SET_PATH"
#define STR_FILE_NAME                       "FILE_NAME"
#define STR_ERROR_PATH_FILE                 "ERROR_PATH_FILE"
int  initialErrReport(errReport* errP)
{
    if(errP == NULL)
    {
        return 0;
    }
    else
    {
        initialSimStrList(&(errP->msgList));
        constructorCharList(&(errP->statusList));
        errP->canWork = 1;
    }
    return 1;
}

void destructorErrReport(errReport* errP)
{
    if(errP != NULL)
    {
        destructorSimStrList(&(errP->msgList));
        destructorCharList(&(errP->statusList)); 
        errP->canWork = 0;
    }
    else
    { 
        /* do nothing */
    }
}

void addListErrReportVChar(errReport *errP,vector_char *vch,char status)
{
    if(errP != NULL && vch != NULL)
    {
        addData(&(errP->statusList),status);
        addNodeSimStrListFromVChar(&(errP->msgList),vch);
    }
    else
    {
        /* do nothing */
    }
}

void addListErrReport(errReport *errP,simString *str,char status)
{
    if(errP != NULL && str != NULL)
    {
        addData(&(errP->statusList),status);
        addNodeSimStrList(&(errP->msgList),str);
    }
    else
    {
        /* do nothing */
    }
}

/*-------- application of errReport */;
int openFileBysimString(FILE **fp,const char *mode,simString *str)
{   /* 0 is file mgr failed  1 is FILE_OK */
    if(fp == NULL || mode == NULL|| str == NULL)
    {
        return FILE_MGR_FAILED;
    }
    else if(*fp != NULL)
    {
        fclose(*fp);
        *fp = NULL;
    }
    else
    {
       /* do nothing */
    }
    *fp = fopen(str->data,mode);
    if(*fp == NULL)
    {
        return FILE_MGR_FAILED;
    }
    else
    {
        fclose(*fp); 
        *fp = NULL; 
    }
    return FILE_OK;
}

int openFileByVectorChar(FILE **fp,const char *mode,vector_char *vch)
{
    int fact1 = 0;
    if(vch == NULL)
    {
        return 0;
    }
    else
    {
        simString simStr1;
        initialSimString(&simStr1);
        convertVectorChar2SimString(&simStr1,vch);
        fact1 = openFileBysimString(fp,mode,&simStr1);
        destructSimString(&simStr1);
    }
    return fact1;
}
int checkAllTaskPath(svmApp *app,errReport *errP)
{
    simStrList pathList;
    simString  *pData = NULL;
    charList   statusList;
    char       fact1 = 1;
    int index = 0;
    int numNode=0;
    int res = 0;
    if(app == NULL || errP == NULL)
    {
       return 0; 
    }
    else
    {
        constructorCharList(&statusList);
        initialSimStrList(&pathList);
        fact1 = getListPathInTaskMgr(errP,&pathList,&statusList,app);
        if(fact1 == 0)
        {
            errP->canWork = 0;
        }
        else
        {
            /* do nothing */
        }
        numNode = getNumNodeSimStrList(&pathList);
        for(index = 0; index < numNode;index++)
        {
//printf("error:%s\n",errorNumberToMsg(index));
            pData = getnthNodeSimStrList(&pathList,index);   
            res   = checkATaskPath(app,pData);
            addListErrReport(errP,pData,res);
        }
        destructorSimStrList(&pathList);
        destructorCharList(&statusList);
    }
    
    return FILE_OK;
}
int readTagErrPathFile(treeXML *root)
{
    int res = 0;
    elementXML  *rootXML          = NULL;
    if(root == NULL)
    {
         return 0;
    }
    else
    {
        /* do nothing */
    }

    rootXML     = getRootElementXML(root);
    res         = getIntValueOfAttrbFromXMLEle(rootXML,STR_ERROR_PATH_FILE,STR_PRINT,"0");
    return res;
}
vector_char  readPathFromTagErrPathFile(treeXML *root)
{
    vector_char path = new_vector_char(0);
    elementXML  *rootXML          = NULL;
    if(root == NULL)
    {   
        /* do nothing */
    }
    else
    {
        rootXML     = getRootElementXML(root);
        path        = getValueFirstChildXML(rootXML,STR_ERROR_PATH_FILE,"");
    }
    return path;
}

int getListPathInTaskMgr(errReport *errP,simStrList *listPath,charList *listUse,svmApp *app)
{
     int         index = 0;
     int         numNode=0;
     treeXML     tXML;
     simString   aPath;
     simString   tPath;
     listElement listXML; 
     int print1 = 0;
     int isOpenFile = 0;
     char useVal  = 0;
     vector_char pathTask       = new_vector_char(0);
     vector_char currentAbPathV = new_vector_char(0);
     elementXML *rootXML = NULL;
     elementXML dummyXML;
     initial_elementXML(&dummyXML);
     if(errP == NULL || listPath == NULL ||listUse == NULL || app == NULL)
     { 
         return 0;
     }
     else
     {
          /* do nothing */
     }   
     initialSimString(&aPath);
     initialSimString(&tPath);
     initial_treeXML(&tXML);
     isOpenFile = setReadFile(&tXML,app->taskMgrPath.data);
     if(isOpenFile == 0 )
     {
         addListErrReport(errP,&(app->taskMgrPath),0);
         destructorTreeXML(&tXML); 
         return FILE_MGR_FAILED;
     }
     else
     {
         addListErrReport(errP,&(app->taskMgrPath),1);
     }
// STR_CURRENT_PATH  
     constructorListXMLEle(&listXML);
     createTreeXML(&tXML);
     /* get Absolute path */
     rootXML = getRootElementXML(&tXML);  
     print1  = getIntValueOfAttrbFromXMLEle(rootXML,STR_CURRENT_PATH,STR_PRINT,"0");
     currentAbPathV = getValueFirstChildXML(rootXML,STR_CURRENT_PATH,"");
     convertVectorChar2SimString(&aPath,&currentAbPathV);
     concatSimStringPathDirectory(&(app->abPath),&aPath,&aPath);
     /* print path if print =1 */
     if(print1 ==1)
     {
         printf("--------- Debug In task_mgr.xml ---------\n");
         printSimString(&aPath);
     }
     else
     {
         /* do nothing */
     }
     generateXMLEleList(&listXML,rootXML,STR_TASK);
     numNode = getNumOfXMLNode(&listXML);
     if(numNode == 0)
     {
         addListErrReport(errP,&(app->taskMgrPath),-1); //-1 no task
         delete_vector_char(&currentAbPathV);
         destructListXMLEle(&listXML);
         destructorTreeXML(&tXML); 
         destructSimString(&aPath);
         destructSimString(&tPath);
         return 0;
     }
     else
     {
         /* do nothing */
     }
     for(index = 0;index < numNode;index++)
     {
         dummyXML.firstChild = getXMLElement(&listXML,index);
         useVal   = getIntValueOfAttrbFromXMLEle(&dummyXML,STR_TASK,STR_TASK_USE,"0");
         pathTask = getValueFirstChildXML(&dummyXML,STR_TASK,"");
         convertVectorChar2SimString(&tPath,&pathTask);
         concatSimStringPathDirectory(&aPath,&tPath,&tPath);
         /* keep it to listPath */
         addNodeSimStrList(listPath,&tPath);
         addData(listUse,useVal);
         delete_vector_char(&pathTask);
         
     }
     delete_vector_char(&currentAbPathV);
     destructSimString(&aPath);
     destructSimString(&tPath);
     destructListXMLEle(&listXML);
     destructorTreeXML(&tXML); 
     return FILE_OK;
}
int checkAllInputPath(svmApp *app,errReport *errP)
{
    FILE *fp = NULL;
    char res = 0;
    char res2 = 0;
    char allTestRes=0;
    char allTrainRes=0;
    int numInput = 0;
    //int numTrainingInput=0;
    int index= 0;
    simString name1;
    simStrList pathList;
    charList statusList;
    if(app == NULL || errP == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    /* check input mgr */
    initialSimString(&name1);
    res = openFileBysimString(&fp,"r",&(app->inputMgrPath));
    if(fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }
    else
    {
       /* do nothing */
    }
    addListErrReport(errP,&(app->inputMgrPath),(char)res);
    if(res == FILE_MGR_FAILED)
    {
        errP->canWork = 0; 
        return FILE_MGR_FAILED;
    }
    else
    {
        /* do nothing */
    }
/*
    int  getNumOfInputFromInputMgrFile(svmApp *app);
    simString getNameAnInputFile(svmApp *app,int index);
    simString getNameAnInputFileWithName(svmApp *app,vector_char *name);
    void getListInputFile(svmApp *app,simStrList *listName);
*/
    /*  check all input in input mgr */
    numInput = getNumOfInputFromInputMgrFile(app);
    for(index = 0;index <numInput;index++)
    {
        name1 = getNameAnInputFile(app,index);
        res   = openFileBysimString(&fp,"r",&name1);
        res2  |= res;
        if(fp != NULL)
        {
            fclose(fp);
            fp = NULL;
        }
        else
        {
            /* do nothing */
        }
        if(res == 1)
        {
            /*  read in file */
            constructorCharList(&statusList);
            initialSimStrList(&pathList);
            allTrainRes = getAndCheckTrainingList(app,&name1,&pathList,&statusList);
            allTestRes  = getAndCheckTestingList(app,&name1,&pathList,&statusList);
            res = allTestRes&allTrainRes;
            addListErrReport(errP,&name1,(char)res);
            moveSimStrListAndCharListToErrReport(errP,&pathList,&statusList);
            destructorCharList(&statusList);
            destructorSimStrList(&pathList);
            
        }
        else
        {
            addListErrReport(errP,&name1,(char)res);
        } 
        
        destructSimString(&name1);
    }
    if(res2==0)
    {
       errP->canWork = 0;
    }
    else
    {
       /* do nothing */
    } 
    destructSimString(&name1);
    return errP->canWork;
}



int checkConfigPaths(svmApp *app,errReport *errP)
{
    int fact1 = 0;
    int fact2 = 0;
    if(errP == NULL || app == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    fact1 = checkAllInputPath(app,errP);
    if(fact1 == 1)
    {
        fact2 = checkAllTaskPath(app,errP);
    }
    else
    {
        /* do nothing */
    }
    return fact1 & fact2;
}

const char* errorNumberToMsg(int a)
{
    switch(a)
    {
        case -2:
            return "name input failed";
        case -1:
            return "task file failed";
        case 0:
            return "file mgr failed";
        case 1:
            return "file ok";
        case 2:
            return "not use but ok";
        case 3:
            return "not use and ok";
        default:
            return "unknow type";
    };
    return "unknow type";
}
void reportConfigPathError(errReport *errP,treeXML *root)
{
    int errVal = 0;
    char res   = 0;
    int index  = 0; 
    int numNode= 0;
    FILE *fp = NULL;
    vector_char path = new_vector_char(0);
    simString   aPath;
    simString  *str = NULL;
    initialSimString(&aPath);
    if(root != NULL && errP != NULL)
    {
        errVal = readTagErrPathFile(root);
    }
    else
    {
        delete_vector_char(&path);
    }
    if( (errVal&0x01) == 1) /* print to file */
    {
        path   = readPathFromTagErrPathFile(root);
        convertVectorChar2SimString(&aPath,&path);
        delete_vector_char(&path);
        if(aPath.length > 0)
        {
            numNode = getNumListErrReport(errP);
            fp = fopen(aPath.data,"w");
            if(fp != NULL && numNode > 0)
            {
                for(index = 0;index< numNode;index++)
                {
                    res = getDataCharList(&(errP->statusList),index);
                    str = getnthNodeSimStrList(&(errP->msgList),index);
                    fputs(str->data,fp);
                    fputs("\t",fp);
                    fputs(errorNumberToMsg(res),fp);
                    fputs("\n",fp);
                }
                fclose(fp);
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
        destructSimString(&aPath);
    }
    else
    {
        /* do nothing */
    }
    if(((errVal>>1)&0x01) == 1) /* print to console */
    {
        numNode = getNumListErrReport(errP);
        for(index = 0;index< numNode;index++)
        {
            res = getDataCharList(&(errP->statusList),index);
            str = getnthNodeSimStrList(&(errP->msgList),index);
            printSimString(str);
            printf("%s\n",errorNumberToMsg(res));
        }   
    }
    else
    {
        /* do nothing */
    }
}
int  getNumListErrReport(errReport *errP)
{
    int res  = 0;
    int res2 = 0;
    if(errP != NULL)
    {
        res = getNumNodeSimStrList(&(errP->msgList));
        res2= countCharList(&(errP->statusList));
        if(res > res2)
        {
            res = res2;
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
int moveSimStrListAndCharListToErrReport(errReport *errP,simStrList *pathList,charList *statusList)
{
    simString *pData = NULL;
    int res;
    int index = 0;
    int num = 0;
    if(errP == NULL || pathList == NULL || statusList == NULL)
    {
        return 0;
    }
    else if((getNumNodeSimStrList(pathList) != countCharList(statusList)) || (countCharList(statusList) <= 0))
    {
        return 0;
    }
    else
    {
        num = getNumNodeSimStrList(pathList);
        for(index = 0;index < num; index++)
        {
             pData    = getnthNodeSimStrList(pathList,index);
             res      = getDataCharList(statusList,index);
             addListErrReport(errP,pData,res);
        }
        
    }
    return 1;
}
int getAndCheckTrainingList(svmApp *app,simString *ds_mgr,simStrList *pathList,charList *statusList)
{
    int res;
    int index = 0;
    int num = 0;
    int allTrainRes = 0;
    FILE *fp = NULL;
    simString name2;
    if(ds_mgr == NULL || app == NULL || pathList == NULL || statusList == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }

    num = getNumAPathTrainInput(ds_mgr);
    initialSimString(&name2);
    for(index =0;index<num;index++)
    {
        name2  = getAPathTrainInput(&(app->abPath),ds_mgr,index);
        res    = openFileBysimString(&fp,"r",&name2);
        addNodeSimStrList(pathList,&name2);
        addData(statusList,res);
        destructSimString(&name2);
        allTrainRes |=res;
    }
    destructSimString(&name2);
    return allTrainRes;
}
int getAndCheckTestingList(svmApp *app,simString *ds_mgr,simStrList *pathList,charList *statusList)
{
    int res;
    int index = 0;
    int num = 0;
    int allTestRes = 0;
    FILE *fp = NULL;
    simString name2;
    if(ds_mgr == NULL || app == NULL || pathList == NULL || statusList == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }

    num = getNumAPathTestInput(ds_mgr);
    initialSimString(&name2);
    for(index =0;index<num;index++)
    {
        name2  = getAPathTestInput(&(app->abPath),ds_mgr,index);
        res    = openFileBysimString(&fp,"r",&name2);
        addNodeSimStrList(pathList,&name2);
        addData(statusList,res);
        destructSimString(&name2);
        allTestRes |=res;
    }
    destructSimString(&name2);
    return allTestRes;
}
