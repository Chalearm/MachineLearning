#include "replacingApp.h"
 
 /* XML tag define */
#define STR_SYMBOLS             "SYMBOLS"
#define STR_SYM                      "SYM"
#define STR_FILES                    "FILES"
#define STR_FILE                      "FILE"
#define STR_ID_ATTRB              "id"
#define STR_OLD_ATTRB           "old"
#define STR_NEW_ATTRB          "new"
#define STR_NEW_FL_ATTRB     "new_fl"
#define STR_NAME_ATTRB         "name"
#define STR_OUTPUT_ATTRB      "output"
 
 
void constructorRepApp(repApp *obj)
{
    if(obj!=NULL)
    {
        constructorPVoidList(&(obj->fileList));
        constructorPVoidList(&(obj->symbList));
        obj->symbList.deleteData =&deleteSymNodeRepApp;
        obj->symbList.isFreeData =1;
        obj->fileList.deleteData =&deleteFileNodeRepApp;
        obj->fileList.isFreeData =1;
    }
    else
    {
        /* do nothing */
    }
}

void deleteFileNodeRepApp(void *node)
{
    destructorFileHand((fileHand*)node);
    if(node!=NULL)
    {
        free(node); 
    }
    else
    {
        /* do nothing */
    }
}
void deleteSymNodeRepApp(void *node)
{
    destructorSymbHand((symbHand*)node);
    if(node!=NULL)
    {
        free(node);
    }
    else
    {
        /* do nothing */
    }
}
void destructorRepApp(repApp *obj)
{
    if(obj!=NULL)
    {
        destructorPVoidList(&(obj->fileList));
        destructorPVoidList(&(obj->symbList));
    }
    else
    {
        /* do nothing */
    }
}

fileHand* newFileHand(const char *nameOld,const char *nwName)
{
    fileHand *obj = (fileHand*)malloc(sizeof(fileHand));
    if(obj!=NULL)
    {
        setFileHand(obj,nameOld,nwName);
    }
    else
    {
        /* do notihng */
    }
    return obj;
}
void readNewReplaceFromFileRepApp(simString *str1) /* str1 contents file name */
{
    FILE *fp =NULL;
    long int startPos =0;
    long int stopPos =0;
    long int diffPos =0;
    char *buff =NULL;
    if(str1!=NULL)
    {
        fp = fopen(str1->data,"r");
    }
    else
    {
        /* do nothing */
    }
    if(fp!=NULL)
    {
        fseek(fp,0,SEEK_SET);
        startPos =ftell(fp);
        fseek(fp,0,SEEK_END);
        stopPos =ftell(fp);
        diffPos =stopPos-startPos;
        fseek(fp,0,SEEK_SET);
        buff = (char*)malloc(sizeof(char)*(diffPos+1)); /* +1 for add '\0' */
    }
    else
    {
        /* do nothing */
    }
    if(buff!=NULL)
    {
        memset(buff,0,diffPos+1); /* +1 for add '\0' */
        fread(buff,diffPos,1,fp);
        buff[diffPos] ='\0';
        convertCString2SimString(str1,buff);
        free(buff);
    }
    else
    {
        /* do nothing */
    }
    if(fp!=NULL)
    {
        fclose(fp);
        fp =NULL;
    }
    else
    {
        /* do nothing */
    }
}
void getSymValueFromListXMLRepApp(repApp *obj,listElement *listSymXML)
{
    simString dummySimStr;
    simString dummySimStr2;
    elementXML *DummyEle = NULL;
    elementXML dummyEle3; 
    symbHand *symObj=NULL;
    pVoidList *symList=NULL;
    int index =0;
    int count =0;
    if((obj!=NULL)&&(listSymXML!=NULL))
    {
        count = getNumOfXMLNode(listSymXML);
        initialSimString(&dummySimStr);
        initialSimString(&dummySimStr2);
        initial_elementXML(&dummyEle3);
        symList = &(obj->symbList);
        for(index=0;index<count;index++)
        {
            DummyEle = getXMLElement(listSymXML,index);
            dummyEle3.firstChild =DummyEle;
            if(isAttrbFromXMLEle(&dummyEle3,STR_SYM,STR_OLD_ATTRB)==1)
            {
                getAttrbValueOfFirstChildEle2Var(&dummyEle3,STR_SYM,STR_OLD_ATTRB,"",(void*)&dummySimStr,0x080);
            }
            else
            {
                printf("error sysm(%d) has no \"old\" attrb\n",index);
            }
            if(isAttrbFromXMLEle(&dummyEle3,STR_SYM,STR_NEW_ATTRB)==1)
            {
                getAttrbValueOfFirstChildEle2Var(&dummyEle3,STR_SYM,STR_NEW_ATTRB,"",(void*)&dummySimStr2,0x080); 
            }
            else if(isAttrbFromXMLEle(&dummyEle3,STR_SYM,STR_NEW_FL_ATTRB)==1)
            {
                getAttrbValueOfFirstChildEle2Var(&dummyEle3,STR_SYM,STR_NEW_FL_ATTRB,"",(void*)&dummySimStr2,0x080); 
                /*  read file and get the content */
                readNewReplaceFromFileRepApp(&dummySimStr2);
            }
            else
            {
                printf("error sysm(%d) has no \"new or new_fl\" attrb\n",index);
            }
            if(dummySimStr.length >0)
            { 
                symObj = newSymHand(dummySimStr.data,dummySimStr2.data);
                addDataPVoidList(symList,(void*)symObj); /* return 1 is ok*/
            }
            else
            {
                /* do nothing */
            }
            destructSimString(&dummySimStr);
            destructSimString(&dummySimStr2); 
        }
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&dummySimStr);
    destructSimString(&dummySimStr2); 
}

void getFileValueFromListXMLRepApp(repApp *obj,listElement *fileEleList)
{
    simString dummySimStr;
    simString dummySimStr2;
    elementXML *DummyEle = NULL;
    elementXML dummyEle3; 
    fileHand *fileObj=NULL;
    pVoidList *fileList=NULL;
    int index =0;
    int count =0;
    if((obj!=NULL)&&(fileEleList!=NULL))
    {
        count = getNumOfXMLNode(fileEleList);
        initialSimString(&dummySimStr);
        initialSimString(&dummySimStr2);
        initial_elementXML(&dummyEle3);
        fileList = &(obj->fileList);
        for(index=0;index<count;index++)
        {
            DummyEle = getXMLElement(fileEleList,index);
            dummyEle3.firstChild =DummyEle;
            if(isAttrbFromXMLEle(&dummyEle3,STR_FILE,STR_NAME_ATTRB)==1)
            {
                getAttrbValueOfFirstChildEle2Var(&dummyEle3,STR_FILE,STR_NAME_ATTRB,"",(void*)&dummySimStr,0x080);
            }
            else
            {
                printf("error file(%d) has no \"name\" attrb\n",index);
            }
            if(isAttrbFromXMLEle(&dummyEle3,STR_FILE,STR_OUTPUT_ATTRB)==1)
            {
                getAttrbValueOfFirstChildEle2Var(&dummyEle3,STR_FILE,STR_OUTPUT_ATTRB,"",(void*)&dummySimStr2,0x080); 
            }
            else
            {
                printf("error file(%d) has no \"output\" attrb\n",index);
            }
            if(dummySimStr.length >0)
            { 
                fileObj =  newFileHand(dummySimStr.data,dummySimStr2.data);
                addDataPVoidList(fileList,(void*)fileObj); /* return 1 is ok*/
            }
            else
            {
                /* do nothing */
            }
            destructSimString(&dummySimStr);
            destructSimString(&dummySimStr2); 
        }
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&dummySimStr);
    destructSimString(&dummySimStr2);
}
void getInputRepApp(repApp *obj,const char *filename)
{
    treeXML tXML; 
    elementXML *fileEle = NULL;
    elementXML *symEle = NULL;
    listElement listFileXML;
    listElement listSymXML;
    int ret = 0;
    int ret2 = 0;
    int ret3 = 0;
    if((obj!=NULL)&&(filename!=NULL))
    { 
        constructorListXMLEle(&listFileXML);
        constructorListXMLEle(&listSymXML);
        ret = getSourceToTreeXML(&tXML,filename);
         
    }
    else
    {
        /* do nothing */
    }
    if(ret ==1)
    {
        fileEle =getfirstChildXML(tXML.root,STR_FILES);
        symEle =getfirstChildXML(tXML.root,STR_SYMBOLS);
        ret2 = getSourceToXMLList(&listFileXML,fileEle,STR_FILE);
        ret3 = getSourceToXMLList(&listSymXML,symEle,STR_SYM);
         
    }
    else
    {
        /* do nothing */
    }    
    if ((ret == 1) && (ret2 == 1) && (ret3 == 1))
    {
        getSymValueFromListXMLRepApp(obj,&listSymXML);
        getFileValueFromListXMLRepApp(obj,&listFileXML);

    }
    else
    {
        /* do nothing */
    }
    if(ret3==1)
    { 
        destructListXMLEle(&listSymXML);
    }
    else
    {
        /* do nothing */
    }    
    if(ret2==1)
    {
        destructListXMLEle(&listFileXML);
    }
    else
    {
        /* do nothing */
    }
    if(ret==1)
    {
        destructorTreeXML(&tXML);
    }
    else
    {
        /* do nothing */
    } 
}
symbHand* newSymHand(const char *oldW,const char *nwW)
{
    symbHand *obj = (symbHand*)malloc(sizeof(symbHand));
    if(obj!=NULL)
    {
        constructorSymbHand(obj);
        setSymbHand(obj,oldW,nwW);
    }
    else
    {
        /* do nothing */
    }
    return obj;
}

void printRepApp(repApp *obj)
{
    pVoidList *list = NULL;
    pVoidList *list2 = NULL;
    int index=0;
    int count=0;
    fileHand *fileObj =NULL;
    symbHand *symObj=NULL;
    if(obj!=NULL)
    {
        list = &(obj->fileList);
        list2 = &(obj->symbList);
        count = countPVoidList(list);
        for(index=0;index<count;index++)
        {
            fileObj = (fileHand*)getDataPVoidList(list,index);
            printf("oldName:%s - NewName: %s\n",fileObj->oldFile,fileObj->newFile);
        }
        
        count = countPVoidList(list2);
        for(index=0;index<count;index++)
        {
            symObj = (symbHand*)getDataPVoidList(list2,index); 
            printSysHand(symObj);
        }
    }
    else
    {
        /* do nothing */
    }
}
void initialRepApp(repApp *obj)
{
    int index=0;
    int count=0;
    fileHand *fileEle = NULL;
    symbHand *symEle = NULL;
    pVoidList *list = NULL;
    pVoidList *list2 = NULL;
    if(obj!=NULL)
    {
        list = &(obj->fileList);
        list2 = &(obj->symbList);
        count = countPVoidList(list2);
        printf("phase 1 loop: %d \n",count);
        for(index=0;index<count;index++)
        {
            symEle =  (symbHand*)getDataPVoidList(list2,index);
            updateAttrbSymBH(symEle,list2);
        }
        printf("phase 2 \n");
        list2 = &(obj->symbList);
        count = countPVoidList(list);
        for(index=0;index<count;index++)
        {
            fileEle =  (fileHand*)getDataPVoidList(list,index);
            updateAttrbFileHand(fileEle,list2);
        }
        

    }
    else
    {
        /* do nothing */
    }
}
void startProcessRepApp(repApp *obj)
{
    int index=0;
    int count=0;
    fileHand *fileEle = NULL;
    pVoidList *list = NULL;
    pVoidList *list2 = NULL;
    if(obj!=NULL)
    {
        list = &(obj->fileList);
        list2 = &(obj->symbList);
        count = countPVoidList(list);
        for(index=0;index<count;index++)
        {
            fileEle =  (fileHand*)getDataPVoidList(list,index);
            processReplacingWordFileHande(fileEle,list2);
        }
    }
    else
    {
        /* do nothing */
    }
}