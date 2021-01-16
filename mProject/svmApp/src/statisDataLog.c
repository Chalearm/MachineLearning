#include "statisDataLog.h"

int *cM;
/*  #0 general tree  methods */
    /*  #00shared all tree */
int compVDoub4StatisLog(const void* a,const void *b)
{
    int res =UN_DEFINE;
    int index =0;
    int num =0;
    vector_double **va=NULL,**vb=NULL;
    if((a==NULL)||(b==NULL))
    {
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

int compVDoub4StatisLog4Mt22d_NBin(const void* a,const void *b)
{
    int res =UN_DEFINE;
    int index =0;
    int num =0;
    double *dV1 =NULL;
    double *dV2 =NULL;
    struct mat2Ele **va=NULL;
    struct mat2Ele **vb=NULL; 
    if((a==NULL)||(b==NULL))
    {
    }
    else if((*((struct mat2Ele**)a)!=NULL)&&(*((struct mat2Ele**)b)!=NULL))
    {
        va = ((struct mat2Ele**)a);
        vb = ((struct mat2Ele**)b); 
        if((*va)->m_length > (*vb)->m_length)
        {
            num = (*vb)->m_length;
        }
        else
        {
            num =(*va)->m_length;
        }
        dV1 = (double*)((*va)->m_startP);
        dV2 = (double*)((*vb)->m_startP);
        res =EQUAL_DEFINE;
        for(index=0;index<num;index++)
        {
            if(dV1[index] > dV2[index])
            {
                index=num;
                res = MORE_DEFINE;
            }
            else if(dV1[index]< dV2[index])
            {
                index=num;
                res = LESS_DEFINE;
            }
            else
            {
                /* do nothing */
            }
        }
        if((res ==EQUAL_DEFINE)&&((*va)->m_length == (*vb)->m_length))
        {
            /* do noting */
        }
        else if((res ==EQUAL_DEFINE)&&((*va)->m_length == num)&&((*vb)->m_length>num))
        {
            res = LESS_DEFINE;
        } 
        else if((res ==EQUAL_DEFINE)&&((*vb)->m_length == num)&&((*va)->m_length>num))
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

int compVDoubWithOpt4StatisLog(void *opt,const void* a,const void *b)
{
    int res =UN_DEFINE;
    int index =0;
    int num =0;
    int num2 =0;
    searchStatisDataOpt *sOpt =NULL;
    vector_double **va=NULL,**vb=NULL;
    if((a!=NULL)&&(b!=NULL)&&(opt!=NULL))
    {
        sOpt = (searchStatisDataOpt*)opt;
        va = ((vector_double**)a);
        vb = ((vector_double**)b);
        num2 = sOpt->m_numAttb;
        if((*va)->lenght > (*vb)->lenght)
        {
            num = (*vb)->lenght;
        }
        else
        {
            num =(*va)->lenght;
        }
        res =EQUAL_DEFINE;
        if(num2 <num)
        {
            /* do nothing */
        }
        else
        {
            /* error */
            printf("compare with option error :num attrb:%d , lenght :%d\n",sOpt->m_numAttb,num);
            res =UN_DEFINE;
            num =0;
        }
        for(index=0;index<num2;index++)
        {
            if((*va)->data[index]> (*vb)->data[index])
            {
                index=num2;
                res = MORE_DEFINE;
            }
            else if((*va)->data[index]< (*vb)->data[index])
            {
                index=num2;
                res = LESS_DEFINE;
            }
            else
            {
                /* do nothing */
            }
        }
        if(res==EQUAL_DEFINE)
        {
            /* force !!! result is EQUAL_DEFINE */
            /* check redundant or inconsist */
            /*  0= nothing, 1= inconsist , 2 = redundant */
            setResultOfSearchStatisDataOpt(sOpt,0);
            for(index=num2;index<num;index++)
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
                /*  0= nothing, 1= inconsist , 2 = redundant */
                setResultOfSearchStatisDataOpt(sOpt,2);
            }
            else
            {
                /*  0= nothing, 1= inconsist , 2 = redundant */
                setResultOfSearchStatisDataOpt(sOpt,1);
                res=EQUAL_DEFINE;
            }
        }
        else 
        {
            /* do nothing */
        }
        if((res ==EQUAL_DEFINE)&&((*va)->lenght == (*vb)->lenght))
        {
            /* do nothing */
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

int compVDoubWithOpt4StatisLog4Mt22d_NBin(void *opt,const void* a,const void *b)
{
    int res =UN_DEFINE;
    int index =0;
    int num =0;
    int num2 =0;
    searchStatisDataOpt *sOpt =NULL;
    double *dV1 =NULL;
    double *dV2 =NULL;
    struct mat2Ele **va=NULL;
    struct mat2Ele **vb=NULL; 
    if((*((struct mat2Ele**)a)!=NULL)&&(*((struct mat2Ele**)b)!=NULL)&&(opt!=NULL))
    {
        sOpt = (searchStatisDataOpt*)opt;
        num2 = sOpt->m_numAttb;
        va = ((struct mat2Ele**)a);
        vb = ((struct mat2Ele**)b); 
        if((*va)->m_length > (*vb)->m_length)
        {
            num = (*vb)->m_length;
        }
        else
        {
            num =(*va)->m_length;
        }
        res =EQUAL_DEFINE;
        dV1 = (double*)((*va)->m_startP);
        dV2 = (double*)((*vb)->m_startP);
        if(num2 <num)
        {
            /* do nothing */
        }
        else
        {
            /* error */
            printf("compare with option error :num attrb:%d , lenght :%d\n",sOpt->m_numAttb,num);
            res =UN_DEFINE;
            num =0;
        }
        for(index=0;index<num2;index++)
        {
            if(dV1[index] > dV2[index])
            {
                index=num2;
                res = MORE_DEFINE;
            }
            else if(dV1[index] < dV2[index])
            {
                index=num2;
                res = LESS_DEFINE;
            }
            else
            {
                /* do nothing */
            }
        }
        if(res==EQUAL_DEFINE)
        {
            /* force !!! result is EQUAL_DEFINE */
            /* check redundant or inconsist */
            /*  0= nothing, 1= inconsist , 2 = redundant */
            setResultOfSearchStatisDataOpt(sOpt,0);
            for(index=num2;index<num;index++)
            {
                if(dV1[index] > dV2[index])
                {
                    index=num;
                    res = MORE_DEFINE;
                }
                else if(dV1[index] < dV2[index])
                {
                    index=num;
                    res = LESS_DEFINE;
                }
                else
                {
                    /* do nothing */
                }
            }
            if((res ==EQUAL_DEFINE)&&((*va)->m_length == (*vb)->m_length))
            {
                /*  0= nothing, 1= inconsist , 2 = redundant */
                setResultOfSearchStatisDataOpt(sOpt,2);
            }
            else
            {
                /*  0= nothing, 1= inconsist , 2 = redundant */
                setResultOfSearchStatisDataOpt(sOpt,1);
                res=EQUAL_DEFINE;
            }
        }
        else 
        {
            /* do nothing */
        }
        if((res ==EQUAL_DEFINE)&&((*va)->m_length == (*vb)->m_length))
        {
            /* do nothing */
        }
        else if((res ==EQUAL_DEFINE)&&((*va)->m_length == num)&&((*vb)->m_length>num))
        {
            res = LESS_DEFINE;
        } 
        else if((res ==EQUAL_DEFINE)&&((*vb)->m_length == num)&&((*va)->m_length>num))
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
 /*  #00e end of shared all tree */
vector_double* newKeyOfAvlT4Sdl(vector_double *sample)
{
    vector_double *p = NULL;
    if(sample!=NULL)
    {
        p = (vector_double*)malloc(sizeof(vector_double));cM[19]++;
    }
    else
    {
        /* do nothing */
    }
    if(p!=NULL)
    {
        *p = new_vector_double(0);
        copy_v_double(p,sample);
    }
    else
    {
        /* do nothing */
    } 
    return p;
}

int addSampleToPvoidListDataOfAvlTr4Sdl(void *node,void *sample)
{
    int res =(node!=NULL)&&(sample!=NULL);
    pVoidList *list =NULL;
    void *data = NULL;
    if(res==1)
    {
        data = (void**)&sample;
        list = (pVoidList*)getDataFromAvlNode(node);
        res = addDataPtPVoidList(list,data);
    }
    else
    {
        /* do nothing */
    } 
    return res;
}

int addSamp2PVltDatOfAvlTr4Sdl_NBINFixNd(void *node,void *sample)
{
    int res =(node!=NULL)&&(sample!=NULL);
    pVoidList *list =NULL;
    void *data = NULL;
    struct mat2Ele *m2Ele = NULL;
    if(res==1)
    {
        data = (void**)&sample;
        m2Ele = (struct mat2Ele*)(((struct nodeFixedArrNBIn*)(node))->m_dat2);
        list = (pVoidList*)(m2Ele->m_startP);
        res = addDataPtPVoidList(list,data);
    }
    else
    {
        /* do nothing */
    } 
    return res;
}
int initDataOfKeyOfAvlT4Sdl(void *node)
{
    int ret =0;
    void *list =NULL;
    if(node!=NULL)
    {
        list =(pVoidList*)malloc(sizeof(pVoidList));cM[20]++;
        ret =1;
    }
    else 
    {
        ret = 0;
    }
    if(list!=NULL)
    {
        constructorPVoidList(list);
        setIsFreeDataOfPVoidList(list,0,NULL); /* 0 no delete a sample from the source */
        setDataToAvlNode(node,&list);
    }
    else if(node!=NULL)
    {        
        setDataToAvlNode(node,&list);
    }
    else
    {
        ret =0;
    }
    return ret;
}

int mvDatOfONd2NNdOfAvlT4Sdl__NBINFIXArr(void *newNode,void *oldNode)
{
    int res = (newNode!=NULL)&&(oldNode!=NULL);
    pVoidList *newList =NULL;
    pVoidList *oldList =NULL;
    int index=0;
    int num =0;
    void *dummyData=NULL;
    /* initial list */
    if(res==1)
    {
        newList = (pVoidList*)(((struct mat2Ele*)(((struct nodeFixedArrNBIn*)(newNode))->m_dat2))->m_startP);
        oldList = (pVoidList*)(((struct mat2Ele*)(((struct nodeFixedArrNBIn*)(oldNode))->m_dat2))->m_startP);
        res = (newList!=NULL)&&(oldList!=NULL);
    }
    else
    {
        /* do nothing */
    }
    /* copy value */
    if(res==1)
    {
        num = countPVoidList(oldList);
        for(index=0;index<num;index++)
        {
            /* move link from old node to new */
            dummyData =  getDataPVoidList(oldList,index); 
            /* replace NULL to oldList */
            
            /* add old link to new list */
            res =  addDataPtPVoidList(newList,&dummyData);
            if(res ==0)
            {
                break;
            }
            else
            {
                /* do nothing */
            }
        }
        if(res ==0)
        {
            printf("can not move the data from the old node. Ln:%d\n",__LINE__);
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int moveDataOfOldNodeToNewNodeOfAvlT4Sdl(void *newNode,void *oldNode)
{
    int res = (newNode!=NULL)&&(oldNode!=NULL);
    pVoidList *newList =NULL;
    pVoidList *oldList =NULL;
    int index=0;
    int num =0;
    void *dummyData=NULL;
    /* initial list */
    if(res==1)
    {
        newList = (pVoidList*)getDataFromAvlNode(newNode);
        oldList = (pVoidList*)getDataFromAvlNode(oldNode);
        res = (newList!=NULL)&&(oldList!=NULL);
    }
    else
    {
        /* do nothing */
    }
    /* copy value */
    if(res==1)
    {
        num = countPVoidList(oldList);
        for(index=0;index<num;index++)
        {
            /* move link from old node to new */
            dummyData =  getDataPVoidList(oldList,index); 
            /* replace NULL to oldList */
            
            /* add old link to new list */
            res =  addDataPtPVoidList(newList,&dummyData);
            if(res ==0)
            {
                break;
            }
            else
            {
                /* do nothing */
            }
        }
        if(res ==0)
        {
            printf("can not move the data from the old node. Ln:%d\n",__LINE__);
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}

/*  #0e end of general tree  methods */

/* #1 searchStatisDataOpt  method*/
void setAttrbSizeInStatisDataLog(statisDataLog *obj,int value)
{
    if(obj!=NULL)
    {
        setNumAttrbOfSearchStatisDataOpt(&(obj->m_optTSearch),value);
    }
    else
    {
        /* do nothing */
    }
}
void initSearchStatisDataOpt(searchStatisDataOpt *obj)
{
    if(obj!=NULL)
    {
        obj->m_numAttb=0; /* 0 is no option*/
        obj->m_result = 0;   /*  0= nothing, 1= inconsist , 2 = redundant */
    }
    else
    {
        /* do nothing */
    }
}
void setResultOfSearchStatisDataOpt(searchStatisDataOpt *obj,char value)
{    
    if((obj!=NULL)&&(value >=0)&&(value <=2))
    { 
        /*  0= nothing, 1= inconsist , 2 = redundant */
        obj->m_result = value;
    }
    else
    {
        /* do nothing */
    }
}

char getResultOfSearchStatisDataOpt(searchStatisDataOpt *obj)
{
    /*  0= nothing, 1= inconsist , 2 = redundant */
    char result =0;
    if(obj!=NULL)
    {
        result = obj->m_result;
    }
    else
    {
        /* do nothing */
    }
    return result;
}
void setNumAttrbOfSearchStatisDataOpt(searchStatisDataOpt *obj,int value)
{    
    if((obj!=NULL)&&(value >=0))
    { 
         /* 0 is no option*/
        obj->m_numAttb = value;
    }
    else
    {
        /* do nothing */
    }
}
/* #1e end searchStatisDataOpt method*/

/* #2 statisDataLogElement method */
void constructSdlEle(statisDataLogElement *obj)
{
    if(obj!=NULL)
    {
        obj->indexDim =-1;
        obj->typeStatus =-1;
    }
    else
    {
        /* do noting */
    }
}
int setValOfSdlEle(statisDataLogElement *obj,int indexDim,char typeStatus)
{
    int res = (obj!=NULL)&&(indexDim >-1);
    if(res==1)
    {
        obj->indexDim = indexDim;
        obj->typeStatus = typeStatus;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int copyValueOfStatisDataLogElement(statisDataLogElement *obj1,statisDataLogElement *obj2)
{
    int res = (obj1!=NULL)&&(obj2!=NULL);
    if(res ==1)
    {
        res = setValOfSdlEle(obj1,obj2->indexDim,obj2->typeStatus);
    }
    else
    {
         /* do nothing */
    }
    return res;
}
/* #2e end of statisDataLogELement */

/* #3 statDataLogEleArr method */
void constructorStatDataLogEleArr(statDataLogEleArr *obj)
{
    if(obj!=NULL)
    {
        obj->m_data =  NULL;
        obj->m_num = 0;
    }
    else
    {
        /* do nothing */
    }
}
int setArrSizeOfStatDataLogEleArr(statDataLogEleArr *obj,int size)
{
    int res = (obj!=NULL)&&(size>=0);
    if(res==1)
    {
        if(obj->m_data != NULL)
        {
            makeEmptyStatDataLogEleArr(obj);
        }
        else
        {
           /* do nothing */
        }
        if(size >0)
        {
            obj->m_data = (statisDataLogElement*)malloc(sizeof(statisDataLogElement)*size);cM[21]++;
        }
        else
        {
            obj->m_data = NULL;
        }
    }
    else
    {
        /* do nothing */
    }
    if((size !=0)&&(obj->m_data))
    {
        res = 1;
        obj->m_num =size;
    }
    else if((size==0)&&(obj->m_data==NULL))
    {
        res =1;
        obj->m_num=size;
    }
    else
    {
        res =0;
    }
    return res;
}
int setValToStatDataLogEleArr(statDataLogEleArr *obj,statisDataLogElement* data,int size)
{
    int index=0;
    int res = (data!=NULL)&&(size>=0)&&(obj!=NULL);
    if(res ==1)
    {
       res = setArrSizeOfStatDataLogEleArr(obj,size);
    }
    else
    {
        /* do nothing */
    }
    if(res==1)
    {
        for(index=0;index<size;index++)
        {
            res = res&copyValueOfStatisDataLogElement(&(obj->m_data[index]),&data[index]);
        }
        if(res ==0)
        { 
             makeEmptyStatDataLogEleArr(obj);
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
void makeEmptyStatDataLogEleArr(statDataLogEleArr *obj)
{
    if(obj!=NULL)
    {
        if(obj->m_data!=NULL)
        {
            free(obj->m_data);
        }
        else
        {
            /* do nothing */
        }
        obj->m_num = 0;
        obj->m_data = NULL;
    }
    else
    {
        /* do nothing */
    }
}
int getSizeArrOfStatDataLogEleArr(statDataLogEleArr *obj)
{
    int res = (obj!=NULL);
    if(res==1)
    {
        res = obj->m_num;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
char getStatusFromStatDataLogEleArr(statDataLogEleArr *obj,int index)
{
    char res = (obj!=NULL)&&(index>=0);
    if(res==1)
    {
        res = (index <obj->m_num);
        if(res ==1)
        {
            res = obj->m_data[index].typeStatus;
        }
        else
        {
            res=-1;
        }
    }
    else
    {
        res =-1;
    }
    return res;
}
/* #3e end of statDataLogEleArr method*/
  
/* #4 methods of  main tree*/
void constructMainT4Sdl(binaryTree* obj,int vectorType)
{
    if(obj != NULL)
    {
        if(vectorType == 0)
        {
            /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
            constructAvlTree((void*)obj,0,"vector_double",0,sizeof(vector_double)); 
            setDelKeyAndDelDataAndCompFnForAvlTree(obj,NULL,NULL,compVDoub4StatisLog);
            setDelKeyFnForAvlTree(obj,NULL);
            setDelKeyFlag(obj,1);
            obj->compareTypeWithOpt = compVDoubWithOpt4StatisLog;
        }
        else
        {
            /*    0x110 FIXED_ARR_NBIN (not build in data element)*/
            constructAvlTree((void*)obj,3,"fixed arr no bin",11,5); 
            setDelKeyAndDelDataAndCompFnForAvlTree(obj,NULL,NULL,compVDoub4StatisLog4Mt22d_NBin);
            setDelKeyFnForAvlTree(obj,NULL);
            setDelKeyFlag(obj,1);
            obj->compareTypeWithOpt = compVDoubWithOpt4StatisLog4Mt22d_NBin;
            obj->clearNodesBinaryTree = clearNodeAvlTFNBin;
            obj->printKeyPVoid = prntKeyAvlTFixArrNBin4SDL;
            obj->printTree = printFixArrMainT_NBin4SDL;
        }
    }
    else
    {
        /* do nothing */
    }
}

void destructorMainT4Sdl(binaryTree* obj)
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
void printKeyAvlTreeInStatisDataLog(void* key,char* buff)
{
    int index = 0;
    vector_double *p = NULL;
    if((key!=NULL)&&(buff!=NULL))
    {
        p = (vector_double*)key;
        buff[0] = '[';
        buff[1] = '\0';
        for(index=0;index<p->lenght;index++)
        {
            sprintf(buff,"%s%f ",buff,(double)(p->data[index]));
        }
        sprintf(buff,"%s]",buff);
    }
    else
    {
        /* do nothing */
    }
}
/* set to Tobj->printTree */
void printFixArrMainT_NBin4SDL(binaryTree* bin,char option)
{    /*
        parameter1 = option
        parameter2 = size
        parameter3 = char* (buffer)
    */ 
    int height =0;
    int index=0;
    void *tempV = NULL;
    if(bin!=NULL)
    {
        if((bin->root!=NULL)&&(bin->numNode>0))
        {
            height = ((struct nodeFixedArrNBIn*)bin->root)->m_height;
        }
        else
        {
            /* do nothing */
        }
        tempV = bin->parameter1;
        bin->parameter1 =(void*)&option;

        for(index=0;index<height;index++)
        {  
            printFixArrNodeOfMainT_NBin4SDL(bin,bin->root,index);
            printf("\n");
        }
        bin->parameter1 = tempV;
    }
    else
    {
        /* do nothing */
    }
}
/* called in printFixArrMainT_NBin4SDL */
void printFixArrNodeOfMainT_NBin4SDL(binaryTree* bin,void* node,int high)
{
    /*
        parameter1 = style
        parameter2 = size
        parameter3 = char* (buffer)
        
        struct nodeFixedArrNBIn  
        {
            void *m_ref; // void *m_pointRef;  
            unsigned int m_height;
            struct nodeFixedArrNBIn *m_lf;
            struct nodeFixedArrNBIn *m_rt;
            // point at data  
            void *m_dat;
            void *m_dat2;
        }; 
*/
    struct nodeFixedArrNBIn *p = (struct nodeFixedArrNBIn*)node;
    char option = 0;
    if((node !=NULL)&&(high==0))
    {
        option = *((char*)(bin->parameter1));
        /* prinf detail*/
        if((bin->parameter3 != NULL)&&(bin->printKeyPVoid != NULL))
        {
            bin->printKeyPVoid(bin->getKey(node),(char*)bin->parameter3);
            if(option == 0)
            {
                printf("%s ",(char*)bin->parameter3);
            }
            else if(option == 1)
            {
                printf("ref:%p %s ",p->m_ref,(char*)bin->parameter3);
            }
        }
        else if(bin->parameter3==NULL)
        {
            printf("cannot print please assign buffer in para3\n");
        }
        else
        {
            /* do nothing */
        }
        if((bin->parameter3!=NULL)&&(bin->printDataPVoid!=NULL))
        {
            bin->printDataPVoid(node,(char*)bin->parameter3);
            printf("%s ",(char*)bin->parameter3);
        }
        else
        {
            /* do nothing */
        }
    }
    else if(node!=NULL)
    {
        printFixArrNodeOfMainT_NBin4SDL(bin,bin->getNodeLeft(node),high-1);
        printFixArrNodeOfMainT_NBin4SDL(bin,bin->getNodeRight(node),high-1);
    }
    else
    {
        /* do nothing */
    }
}
void prntKeyAvlTFixArrNBin4SDL(void* key,char* buff)
{
    struct mat2Ele **mte = (struct mat2Ele**)key;
    double *bb =NULL;
    int index=0;
    int num=0;
    if(mte == NULL)
    {
        printf("cannot print1 ,ln:%d, fl:%s\n",__LINE__,__FILE__);
    }
    else if(*mte != NULL)
    {
        bb = (*mte)->m_startP;
    }
    else
    {
        printf("cannot print2 bb:%p ,ln:%d, fl:%s\n",bb,__LINE__,__FILE__);
    }
    if((bb != NULL) && (buff != NULL))
    {
        num = (*mte)->m_length;
        sprintf(buff,"[");
        for(index=0;index<num;index++)
        {
            sprintf(buff,"%s%f ",buff,bb[index]); 
        }
        sprintf(buff,"%s]\n",buff);
    }
    else
    {
        /* do nothing */
    }
}
/* #4e end of methods of  main tree*/

/* #5 methods of redundantTree */
void constructRedundantAvlT4Sdl(binaryTree *obj,int vectorType)
{
    if(obj!=NULL)
    {
        if(vectorType == 0)
        {
            /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
            constructAvlTree((void*)obj,1,"custom type 2",0,sizeof(vector_double));
            setDelKeyAndDelDataAndCompFnForAvlTree(obj,NULL,delRedundantDataInSdl,compVDoub4StatisLog); 
            setDelKeyFnForAvlTree(obj,NULL);
            setDelKeyFlag(obj,1);
            obj->compareTypeWithOpt = compVDoubWithOpt4StatisLog;
        }
        else
        {
            constructAvlTree((void*)obj,3,"fixed arr no bin",11,5);
            setDelKeyAndDelDataAndCompFnForAvlTree(obj,NULL,delRedundantDataInSdl_NdFixNBin,compVDoub4StatisLog4Mt22d_NBin); 
            setDelKeyFnForAvlTree(obj,NULL);
            setDelKeyFlag(obj,1);
            obj->compareTypeWithOpt = compVDoubWithOpt4StatisLog4Mt22d_NBin;
            obj->getData = getPVLMt2;
            obj->clearNodesBinaryTree = clearNodeAvlTFNBin;
        }
    }
    else
    {
        /* do noting */
    }
}


void delRedundantDataInSdl_NdFixNBin(void *obj,void *data)
{
    binaryTree *avlTree = (binaryTree*)obj;
    struct mat2Ele *ltPV2_1 = (struct mat2Ele*)data;
    if((avlTree!=NULL)&&(ltPV2_1!=NULL))
    {
        if(ltPV2_1 !=NULL)
        {
            destructorPVoidList(ltPV2_1->m_startP);
        }
        else
        {
            /* do nothing */
        }
        rmEleMt22d(avlTree->parameter4,ltPV2_1);
    }
    else
    {
        /* do nothing */
    }
}

void delRedundantDataInSdl(void *obj,void *data)
{
    pVoidList **list = (pVoidList**)data;
    if(list!=NULL)
    {
        if(*list !=NULL)
        {
            destructorPVoidList(*list);
            free(*list);
            *list =NULL;
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

void destructRedundantAvlT4Sdl(binaryTree *obj)
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

/* #5e end methods of redundantTree */

/* #6 methods of inconsistent tree*/
void constructInconsistAvlT4Sdl(binaryTree *obj,int vectorType)
{
    if(obj!=NULL)
    {
        if(vectorType == 0)
        {
            /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
            constructAvlTree((void*)obj,1,"custom type 2",0,sizeof(vector_double));
            setDelKeyAndDelDataAndCompFnForAvlTree(obj,NULL,delInconsistDataInSdl,compVDoub4StatisLog); 
            setDelKeyFnForAvlTree(obj,NULL);
            setDelKeyFlag(obj,1);
            obj->compareTypeWithOpt = compVDoubWithOpt4StatisLog;
        }
        else
        {
            constructAvlTree((void*)obj,3,"fixed arr no bin",11,5);
            setDelKeyAndDelDataAndCompFnForAvlTree(obj,NULL,delInconsistDataInSdl_NdFixNBin,compVDoub4StatisLog4Mt22d_NBin); 
            setDelKeyFnForAvlTree(obj,NULL);
            setDelKeyFlag(obj,1);
            obj->compareTypeWithOpt = compVDoubWithOpt4StatisLog4Mt22d_NBin;
            obj->getData = getPVLMt2;
            obj->clearNodesBinaryTree = clearNodeAvlTFNBin;
        }
    }
    else
    {
        /* do noting */
    }
}

void destructInconsistAvlT4Sdl(binaryTree *obj)
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
void delInconsistDataInSdl_NdFixNBin(void *obj,void *data)
{
    binaryTree *avlTree = (binaryTree*)obj;
    struct mat2Ele *ltPV2_1 = (struct mat2Ele*)data;
    if((avlTree!=NULL)&&(ltPV2_1!=NULL))
    {
        destructorPVoidList(ltPV2_1->m_startP);
        rmEleMt22d(avlTree->parameter4,ltPV2_1);
    }
    else
    {
        /* do nothing */
    }
}
void delInconsistDataInSdl(void *obj,void *data)
{
    pVoidList **list = (pVoidList**)data;
    if(list!=NULL)
    {
        if(*list !=NULL)
        {
            destructorPVoidList(*list );
            free(*list);
            *list =NULL;
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

int getNumListInNodeAddNode(void *node)
{
    pVoidList *list = NULL;
    int count =0;
    if(node != NULL)
    {
        list = (pVoidList*)getDataFromAvlNode(node);
        count = countPVoidList(list);
    }
    else
    {
        /* do nothing */
    }
    return count;
}
/* #6e end methods of inconsistent tree*/

/* #7 incompAndDiscData  method*/
void constructIncompAndDiscDat(incompAndDiscData *obj)
{
    if(obj!=NULL)
    {
        obj->addr = NULL;
        constructorStatDataLogEleArr(&(obj->statDat));
    }
    else
    {
        /* do nothing */
    }
}
void addData2IncompAndDiscData(incompAndDiscData *obj,void *addr,statisDataLogElement *statEle,int numEle)
{
    if(obj!= NULL)
    {
        obj->addr = addr;
        setValToStatDataLogEleArr(&(obj->statDat),statEle,numEle);
    }
    else
    {
        /* do nothing */
    }
}
void destructIncompAndDiscDat(incompAndDiscData *obj)
{
    if(obj!=NULL)
    {
        obj->addr = NULL;
        makeEmptyStatDataLogEleArr(&(obj->statDat));
    }
    else
    {
        /* do nothing */
    }
}
/*  #7e end incompAndDiscData  method*/

/* statisDataLog   methods */ 
void constructorStatisDataLog(statisDataLog *obj,int vectorType)
{
    if(obj!=NULL)
    {
        obj->m_inputType = vectorType;
        obj->whichDataSet = NULL; 
        obj->m_totalOfRedunNode = 0;
        obj->m_totalOfInconsistNode = 0;
        obj->m_totalOfDiscardInsNode = 0;
        obj->m_totalOfIncompleteNode = 0;
        obj->m_totRejectReassignNode = 0;
        initiValInMt22d(&(obj->m_mat2d24MainT));
        initiValInMt22d(&(obj->m_mat2d24RedunT));
        initiValInMt22d(&(obj->m_mat2d24PVoidCls));
        initiValInMt22d(&(obj->m_mat2d24PVoidEle));
        constructMainT4Sdl(&(obj->m_mainT),vectorType);
        constructIncompAndDiscAvlT4Sdl(&(obj->m_incompleteTree),vectorType);
        constructIncompAndDiscAvlT4Sdl(&(obj->m_discardInsTree),vectorType);
        constructInconsistAvlT4Sdl(&(obj->m_inconsistTree),vectorType);
        constructRedundantAvlT4Sdl(&(obj->m_redundantTree),vectorType);
        initSearchStatisDataOpt(&(obj->m_optTSearch));
        constructAddNodeToTree(&(obj->m_handleTrees));
        
        if(obj->m_inputType == 1)
        {
            obj->m_mat2d24MainT = newMt22d(SIMMAT2_T_MAIN_SIZE,0,0,4);
            obj->m_mainT.parameter3 = &(obj->m_mat2d24MainT);
            obj->m_mat2d24RedunT = newMt22d(SIMMAT2_T_REDUN_SIZE,0,0,4);
            obj->m_mat2d24PVoidCls = newMt22d(SIMMAT2_T_REDUN_SIZE,1,sizeof(struct pVoidList),2);
            obj->m_mat2d24PVoidEle = newMt22d(SIMMAT2_T_PVOIDELEM_SIZE,0,0,5);
            obj->m_redundantTree.parameter3 = &(obj->m_mat2d24RedunT);
            obj->m_redundantTree.parameter4 = &(obj->m_mat2d24PVoidCls);
            obj->m_redundantTree.parameter5 = &(obj->m_mat2d24PVoidEle);
            obj->m_handleTrees.m_PV2List = &(obj->m_mat2d24PVoidCls);
            obj->m_handleTrees.m_PV2Ele = &(obj->m_mat2d24PVoidEle);
            obj->m_inconsistTree.parameter3 =obj->m_redundantTree.parameter3;
            obj->m_inconsistTree.parameter4 =obj->m_redundantTree.parameter4;
            obj->m_inconsistTree.parameter5 =obj->m_redundantTree.parameter5;
            
            obj->m_incompleteTree.parameter3 =obj->m_redundantTree.parameter3;
            obj->m_incompleteTree.parameter4 =obj->m_redundantTree.parameter4;
            obj->m_incompleteTree.parameter5 =obj->m_redundantTree.parameter5;
            printf("This : %p\n",obj);
            printf("m_mat2d24MainT : %p\n",&(obj->m_mat2d24MainT));
            printf("m_mat2d24RedunT : %p\n",&(obj->m_mat2d24RedunT));
            printf("m_mat2d24PVoidCls : %p\n",&(obj->m_mat2d24PVoidCls));
            printf("m_mat2d24PVoidEle : %p\n",&(obj->m_mat2d24PVoidEle));
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

void makeStatisDataLogEmpty(statisDataLog *obj)
{
    if(obj != NULL)
    {
 
        int sum =0;
        if(countAllNodesInBT(&(obj->m_mainT)) !=0)
        {
            printf("MT# Nd(%d,%d) ",getNumBinaryNodeOfTree(&(obj->m_mainT)),countAllNodesInBT(&(obj->m_mainT)));
            if((getNumBinaryNodeOfTree(&(obj->m_inconsistTree))+countAllNodesInBT(&(obj->m_inconsistTree))+obj->m_totalOfInconsistNode)!=0)
            {
                printf("IncnT#(%d,%d,%d)\n",getNumBinaryNodeOfTree(&(obj->m_inconsistTree)),countAllNodesInBT(&(obj->m_inconsistTree)),obj->m_totalOfInconsistNode);
            }
            else
            {
                printf("\n(There is no inconsist data:0)");
            }
            if((getNumBinaryNodeOfTree(&(obj->m_incompleteTree))+countAllNodesInBT(&(obj->m_incompleteTree))+obj->m_totalOfIncompleteNode)!=0)
            {
                printf("IncmT#(%d,%d,%d) ",getNumBinaryNodeOfTree(&(obj->m_incompleteTree)),countAllNodesInBT(&(obj->m_incompleteTree)),obj->m_totalOfIncompleteNode);
            }
            else
            {
                printf("\n(There is no incomplete data data:0)");
            }
            if((getNumBinaryNodeOfTree(&(obj->m_discardInsTree))+countAllNodesInBT(&(obj->m_discardInsTree))+obj->m_totalOfDiscardInsNode)!=0)
            {
                printf("DiscT#(%d,%d,%d) ",getNumBinaryNodeOfTree(&(obj->m_discardInsTree)),countAllNodesInBT(&(obj->m_discardInsTree)),obj->m_totalOfDiscardInsNode);
            }
            else
            {
                printf("\n(There is no discard data data:0)");
            }
            if((getNumBinaryNodeOfTree(&(obj->m_redundantTree))+countAllNodesInBT(&(obj->m_redundantTree))+obj->m_totalOfRedunNode)!=0)
            {
                printf("RT#(%d,%d,%d)\n",getNumBinaryNodeOfTree(&(obj->m_redundantTree)),countAllNodesInBT(&(obj->m_redundantTree)),obj->m_totalOfRedunNode);
            }
            else
            {
                printf("\n(There is no redundant data data:0)\n");
            }
            if(obj->m_totRejectReassignNode !=0)
            {
                printf("Not reas : %d\n",obj->m_totRejectReassignNode);
            }
            sum   = countAllNodesInBT(&(obj->m_mainT))+obj->m_totalOfRedunNode;
            sum += obj->m_totalOfDiscardInsNode;
            sum += obj->m_totalOfInconsistNode+obj->m_totalOfIncompleteNode;
            printf("sum of All Dat: %d\n",sum);
       }
        else
        {
            printf("statisDataLog is Empty : %p\n",obj);
        }
       
        obj->m_inputType = 0;
        obj->m_totalOfRedunNode = 0;
        obj->m_totalOfDiscardInsNode = 0;
        obj->m_totalOfInconsistNode = 0;
        obj->m_totalOfIncompleteNode = 0;
        obj->m_totRejectReassignNode = 0;
        obj->whichDataSet = NULL; 
        destructorMainT4Sdl(&(obj->m_mainT));
        destructIncompAndDiscAvlT4Sdl(&(obj->m_incompleteTree));
        destructInconsistAvlT4Sdl(&(obj->m_inconsistTree));
        destructIncompAndDiscAvlT4Sdl(&(obj->m_discardInsTree));
        destructRedundantAvlT4Sdl(&(obj->m_redundantTree));
        /*
        printMt22d(&(obj->m_mat2d24MainT));
        printMt22d(&(obj->m_mat2d24RedunT));
        printMt22d(&(obj->m_mat2d24PVoidEle));
        printMt22d(&(obj->m_mat2d24PVoidCls));
        */
        clearMt22d(&(obj->m_mat2d24MainT));
        clearMt22d(&(obj->m_mat2d24RedunT));
        clearMt22d(&(obj->m_mat2d24PVoidEle));
        clearMt22d(&(obj->m_mat2d24PVoidCls));
    }
    else
    {
        /* do nothing */
    }
}
void printSampleFxBin(void *sam)
{
    struct mat2Ele *mte = sam;
    double *bb =NULL;
    int index=0;
    int num=0;
    if(mte!=NULL)
    {
        bb = mte->m_startP;
    }
    else
    {
        printf("cannot print bb:%p ,ln:%d, fl:%s\n",bb,__LINE__,__FILE__);
    }
    if(bb != NULL)
    {
        num = mte->m_length;
        printf("[");
        for(index=0;index<num;index++)
        {
            printf("%f ",bb[index]);
        }
        printf("]\n");
    }
    else
    {
        /* do nothing */
    }
}

void printNodeAndPVLAdrr(void *node)
{
    struct nodeFixedArrNBIn *n =(struct nodeFixedArrNBIn*)node;
    struct mat2Ele *mte = NULL;
    if(n!=NULL)
    {
        printf("Nd:%p ",n);
        mte = n->m_dat2;
    }
    else
    {
        /* do nothing */
    }
    if(mte!=NULL)
    {
        printf("md2%p, list:%p\n",mte,mte->m_startP);
    }
    else
    {
        /* do nothing */
    }
}
void printKeyOfNdFixNBin(void *node)
{
    struct nodeFixedArrNBIn *n =(struct nodeFixedArrNBIn*)node;
    if(n!=NULL)
    {
        printf("n:%p ",n);
        printSampleFxBin(n->m_dat);
    }
    else
    {
        /* do nothing */
    }
}
void* getPVLMt2(void *node)
{
    struct nodeFixedArrNBIn *n = (struct nodeFixedArrNBIn*)node;
    struct mat2Ele *mte = NULL;
    if(n != NULL)
    {
        mte = n->m_dat2;
    }
    else
    {
        /* do nothing */
    }
    return (void*)mte;
}
void clearNodeAvlTFNBin(binaryTree* avlTree,void* node)
{
    if((avlTree != NULL)&&(node != NULL))
    {
        clearNodeAvlTFNBin(avlTree,avlTree->getNodeLeft(node));
        clearNodeAvlTFNBin(avlTree,avlTree->getNodeRight(node));
        /*
        if(avlTree->isPrint ==1)
        {
            printf("clearedN ");printNodeAndPVLAdrr(node);
        }*/
        if(avlTree->deleteNode != NULL)
        {
            avlTree->deleteNode(avlTree,&node);
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
void addProcess2AddNode2T(statisDataLog *stdlObj,char type)
{
    /*
0 = main tree
1 = redundant tree
2 = inconsist tree
3 = incomplete and discard tree
other = NULL
*/
    void *mainTree = NULL;
    void *redundantT=NULL;
    void *oldTree =NULL;
    addNodeToTree *obj = NULL;
    void (*fnMvMT2GT)(addNodeToTree *obj);
    void (*fnAddDat2Nd)(addNodeToTree *obj);
    void (*fnAddDat2Nd2)(addNodeToTree *obj);
    void (*fnInitDatOfKy4GT)(addNodeToTree *obj);
    void (*fnInitDatOfKy4GT2)(addNodeToTree *obj);
    void (*fnMvDatONd2NNd)(addNodeToTree *obj);
    if(stdlObj!=NULL)
    {
        obj = &(stdlObj->m_handleTrees);
        mainTree = &(stdlObj->m_mainT);
        redundantT = &(stdlObj->m_redundantTree);
        if(stdlObj->m_inputType == 0)
        {
            fnMvMT2GT = moveDat2Node4GT;
            fnAddDat2Nd = addData2Node;
            fnAddDat2Nd2 = addData2Node2;
            fnInitDatOfKy4GT= initDataOfKey4GT;
            fnInitDatOfKy4GT2=initDataOfKey4GT2;
            fnMvDatONd2NNd = moveDat2Node4GT2;
        }
        else
        {
            fnMvMT2GT = mVDt2Nd4GT_NBINFIXArr;
            fnAddDat2Nd = addData2Node_NBInFxNd;
            fnAddDat2Nd2 = addData2Node2_NdFixNBin;
            fnInitDatOfKy4GT= initDtOfKy4GT_NBINFixNd;
            fnInitDatOfKy4GT2= initDataOfKey4GT2_NBINFixNd;
            fnMvDatONd2NNd = moveDat2Node4GT2_NBINFIXArr;
        }
    }
    else
    {
        /* do nothing */
    }
    if(obj!=NULL)
    {
        oldTree = (void*)obj->m_OldTree;
        switch(type)
        {
            case 0: /*0 = main tree */
                     obj->m_numProc =1;
                     obj->m_fn[0] = &newKey4MainT;
            break;
            case 1: /*1 = redundant tree*/ 
                     obj->m_fn[0] = &newKey4GT;
                     obj->m_fn[1] = fnInitDatOfKy4GT;
                     obj->m_fn[2] = fnAddDat2Nd;
                     if(oldTree == mainTree)
                     {
                        obj->m_fn[3] = fnMvMT2GT;
                        obj->m_numProc =4;
                     }
                     else
                     {
                        obj->m_numProc =1;
                        obj->m_fn[0] = fnAddDat2Nd;
                     }
            break;
            case 2: /*   2 = inconsist tree */   
                     obj->m_fn[0] = &newKey4GT;
                     obj->m_fn[1] = fnInitDatOfKy4GT;
                     obj->m_fn[2] = fnAddDat2Nd;
                     if(oldTree == mainTree)
                     {
                        obj->m_fn[3] = fnMvMT2GT;
                        obj->m_numProc =4;
                     }
                     else if(oldTree ==redundantT)
                     {
                        obj->m_fn[3] = fnMvDatONd2NNd;
                        obj->m_numProc =4;
                     }
                     else
                     {
                        obj->m_numProc =3;
                     } 
            break;
            case 3: /*3 = incomplete and discard tree */ 
                    if(oldTree ==NULL)
                     {
                         obj->m_numProc =3;
                         obj->m_fn[0] = &newKey4GT;
                         obj->m_fn[1] = fnInitDatOfKy4GT2;
                         obj->m_fn[2] = fnAddDat2Nd2;
                     }
                     else
                     {
                         obj->m_numProc =1;
                         obj->m_fn[0] = fnAddDat2Nd2;
                     }
            break;
            default:
                printf("Error assign process : %d \n",type);
            break;
        }
    }
    else
    {
        /* do nothing */
    }
}
/*return type of processing to any tree*/
char searchTheTreeForContainTheNode(statisDataLog *obj,void *sample,statisDataLogElement *statEle,int numEle)
{
    /* There are 7 cases */
    /* found inconsistency node in the inconsistency tree*/
    /* found redundant node in the inconsistency tree*/
    /* found inconsistency node in the redundant tree*/
    /* found redundant node in the redundant tree*/
    /* found inconsistency node in the Main tree*/
    /* found redundant node in the Main tree*/
    /* else */
    struct addNodeToTree *handT = NULL;
    binaryTree *inctTemp = NULL; 
    binaryTree *redtTemp = NULL; 
    binaryTree *maintTemp = NULL; 
    binaryTree **oldTree = NULL;
    binaryTree **newTree = NULL;
    void **oldNode = NULL;
    char typeProc =-1;
    int countTemp =0;
    char searchResult =0; 
    searchStatisDataOpt * optTemp = NULL;  
    int fact1 = (obj!=NULL)&&(sample!=NULL)&&(((statEle!=NULL)&&(numEle>=0))||((statEle==NULL)&&(numEle==0)));
    if(fact1 == 1)
    {
        handT = &(obj->m_handleTrees);
        oldTree = &(handT->m_OldTree);
        newTree = &(handT->m_newTree);
        oldNode = &(handT->m_oldNode);
        handT->m_newNode = NULL;
        handT->m_treeCountOld = NULL;
        handT->m_treeCountNew = NULL;
        handT->m_plusValOld = 0;
        handT->m_plusValNew = 0;
        /*
0 = main tree
1 = redundant tree
2 = inconsist tree
3 = incomplete and discard tree
other = NULL
*/
        if(numEle >0)
        { 
            typeProc =3;  /*3 = discard and incomplete tree*/
            if((numEle == 1)&&(statEle[0].typeStatus==-2)) /* UNKNOW_STATIS = -2*/
            {
                handT->m_treeCountNew =&(obj->m_totalOfDiscardInsNode);
                handT->m_plusValNew =1;
                *oldTree = NULL;
                *oldNode = (void*)searchDataInBinaryTree(&(obj->m_discardInsTree),&sample);
                *newTree = &(obj->m_discardInsTree);
                 if(*oldNode!=NULL)
                 {
                    *oldTree =&(obj->m_discardInsTree);
                 }
                 else
                 {
                     /* do nothing */
                 }
            }
            else
            {
                handT->m_treeCountNew =&(obj->m_totalOfIncompleteNode);
                handT->m_plusValNew =1;
                *oldTree = NULL;
                *oldNode = (void*)searchDataInBinaryTree(&(obj->m_incompleteTree),&sample);
                *newTree = &(obj->m_incompleteTree);
                 if(*oldNode!=NULL)
                 {
                    *oldTree =&(obj->m_incompleteTree);
                    /*
if(obj->m_inputType==1)
{
    printf("juiEq");
    printSampleFxBin(sample);
}*/
                 }
                 else
                 {
                     /*
if(obj->m_inputType==1)
{
    printf("juiNEq");
    printSampleFxBin(sample);
}*/
                     /* do nothing */
                 }
            }
        }
        else
        {
            redtTemp = &(obj->m_redundantTree);
            inctTemp = &(obj->m_inconsistTree);
            maintTemp = &(obj->m_mainT);
            optTemp = &(obj->m_optTSearch);
            /*      char getResultOfSearchStatisDataOpt(searchStatisDataOpt *obj); */
            /* search in inconsistent tree */
            if(fact1 ==1)
            {
                setResultOfSearchStatisDataOpt(optTemp,0); 
                *oldNode = searchDataInBinaryTreeWithOpt(inctTemp,(void*)optTemp,&sample);
                /*  0= nothing, 1= inconsist , 2 = redundant */
                searchResult =getResultOfSearchStatisDataOpt(optTemp);
                /* 1 found inconsistency node in the inconsistency tree*/
                /* 2 found redundant node in the inconsistency tree*/
                if(searchResult >0)  /* 1 or 2 */ 
                {
                    *newTree = inctTemp; 
                    *oldTree =NULL;
                    typeProc =2;  /*2 = inconsist tree*/
                    handT->m_treeCountNew =&(obj->m_totalOfInconsistNode);
                    handT->m_plusValNew =1;
                }
                else
                {
                    /* cannot conclude */
                    fact1=0;
                }
            }
            else
            {
                /* do nothing */
            }
            /* search in redundant tree */
            if(fact1 ==0)
            {
                fact1 =1;
                setResultOfSearchStatisDataOpt(optTemp,0); 
                *oldTree =redtTemp; 
                *oldNode = searchDataInBinaryTreeWithOpt(redtTemp,(void*)optTemp,&sample);
                /*  0= nothing, 1= inconsist , 2 = redundant */
                searchResult =getResultOfSearchStatisDataOpt(optTemp);
                /* 3 found inconsistency node in the redundant tree*/
                if(searchResult ==1) /* 1= inconsist  */
                {
                    *newTree = inctTemp;
                    typeProc =2;  /*2 = inconsist tree*/
                    countTemp = getNumListInNodeAddNode(*oldNode);
                    handT->m_treeCountNew =&(obj->m_totalOfInconsistNode);
                    handT->m_plusValNew =countTemp+1;
                    handT->m_treeCountOld =&(obj->m_totalOfRedunNode);
                    handT->m_plusValOld =-countTemp;
                }
                /* 4 found redundant node in the redundant tree*/
                else if(searchResult ==2) /* 2= redundant  */
                {
                    *newTree = redtTemp; 
                     *oldTree = NULL;
                     typeProc = 1;  /*1= redundant tree*/
                handT->m_treeCountNew =&(obj->m_totalOfRedunNode);
                handT->m_plusValNew =1;
                }
                else
                {
                    /* cannot conclude */
                    fact1=0;
                }
            }
            else
            {
                /* do nothing */
            }
            /* search in main tree */
            if(fact1 ==0)
            {
                fact1 = 1;
                setResultOfSearchStatisDataOpt(optTemp,0); 
                *oldTree =maintTemp; 
                *oldNode = searchDataInBinaryTreeWithOpt(maintTemp,(void*)optTemp,&sample);
                /*  0= nothing, 1= inconsist , 2 = redundant */
                searchResult =getResultOfSearchStatisDataOpt(optTemp);
                /* 5 found inconsistency node in the Main tree*/
                if(searchResult ==1) /* 1= inconsist  */
                {
                    *newTree = inctTemp; 
                     typeProc = 2;  /*2= inconsist tree*/
                    handT->m_treeCountNew =&(obj->m_totalOfInconsistNode);
                    handT->m_plusValNew =2;
                }
                /* 6 found redundant node in the Main tree*/
                else if(searchResult ==2) /* 2= redundant  */
                {
                    *newTree = redtTemp;
                    typeProc = 1;  /*1= redundant tree*/
                    handT->m_treeCountNew =&(obj->m_totalOfRedunNode);
                    handT->m_plusValNew =2;
                } 
                /* 7 else */
                else if(*oldNode  == NULL)
                {
                    *newTree = maintTemp;
                    *oldTree =NULL; 
                    typeProc = 0;  /*0= main tree*/
                }
                else
                {
                    fact1 = 0;
                    printf("error to search tree : %d %s\n",__LINE__,__FILE__);
                }
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
    if(fact1 ==0)
    {
        printf("error!! cannot operate the searchTheTreeForContainTheNode method : ln:%d file:%s\n",__LINE__,__FILE__);
    }
    else
    {
        handT->sample=sample;
        handT->m_statEle =statEle;
        handT->m_num = numEle;
        addProcess2AddNode2T(obj,typeProc);
        verifyAddNodeToTree(handT);
    }
    return typeProc;
}
int addDataToStatisDataLog(statisDataLog* statisDataLogObj,void *sample,statisDataLogElement *statEle,int numEle)
{    
   // nodeBinaryPVoidWithData *node = NULL;
    int res =0;
    char fact1 = (statisDataLogObj!=NULL); 
    fact1 = fact1&&(sample!=NULL);
    fact1 = fact1&&(((statEle!=NULL)&&(numEle>=0))||((statEle==NULL)&&(numEle==0)));

    /* initial phase */
    if(fact1 ==1)
    { 
        searchTheTreeForContainTheNode(statisDataLogObj,sample,statEle,numEle);
        res = runAllProcs4AddNode2T(&(statisDataLogObj->m_handleTrees));
    }
    else
    {  
        /*  temp*/
        fact1 =0;
        printf("data in valid in addDataToStatisDataLog, %s l:%d\n",__FILE__,__LINE__);
    }
    /* process phase */

    
    return res;
}

int allocatStatisDataLogArray(statisDataLog** statisDataLogObj,int num,int numAttrb,int vectorType,int *cm)
{
    int res =0;
    int index=0;
    statisDataLog* pStatisDataLog=NULL;
    if((statisDataLogObj != NULL) && (num >0))
    {
        cM = cm;
        if(*statisDataLogObj  == NULL)
        {
            pStatisDataLog = (statisDataLog*)malloc(sizeof(statisDataLog)*num);
           
            *statisDataLogObj = pStatisDataLog;
            if(pStatisDataLog != NULL)
            {
                for(index=0;index<num;index++)
                {
                    pStatisDataLog[index].countMallo = cm;
                    constructorStatisDataLog(&pStatisDataLog[index],vectorType);
                    setAttrbSizeInStatisDataLog(&pStatisDataLog[index],numAttrb);
                }
                cm[6]++;
                res =1;
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
    if((num ==0)&&(*statisDataLogObj  == NULL))
    {
        res=1;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int deallocatStatisDataLogArray(statisDataLog** statisDataLogObj,int num)
{
    int res =0;
    int index=0;
    statisDataLog *pStatisDataLog = NULL;
    if((statisDataLogObj != NULL) && (num >0))
    {
        if(*statisDataLogObj != NULL)
        {
            pStatisDataLog =*statisDataLogObj;
            for(index=0;index<num;index++)
            {
                makeStatisDataLogEmpty(&pStatisDataLog[index]);
            }
            free(*statisDataLogObj);
            *statisDataLogObj = NULL;
            res =1;
        }
        else
        {
            /* do nothing */
        }
    }
    else if((statisDataLogObj != NULL) && (num ==0))
    {
        if(*statisDataLogObj == NULL)
        {
            res =1;
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
/*  end  of statisDataLog   methods */ 

vector_double* getSampleToAvlNodeInStatisDataLog(void *node)
{
    nodeBinaryPVoidWithData *p = (nodeBinaryPVoidWithData*)node;
    vector_double *pRet = NULL;
    if(p!=NULL)
    {
        pRet = p->key;
    }
    else
    {
        /* do nothing */
    }
    return pRet;
}
statDataLogEleArr* getStatDataLogEleArrFromNodeAvlTreeInStatisDataLog(void *node)
{
    statDataLogEleArr *pRet = NULL;
    avlData *pAvlData =NULL;
    nodeBinaryPVoidWithData *pNode = (nodeBinaryPVoidWithData*)node;
    if(pNode!=NULL)
    {
        pAvlData = (avlData*)pNode->data;
        pRet = (statDataLogEleArr*)pAvlData->data;
    }
    else
    {
        /* do nothing */
    }
    return pRet;
}

int deleteNodeOfStatisTreeForStatisDataLog(statisDataLog* statisDataLogObj,void *node,vector_double **sample,statDataLogEleArr **arr)
{
    int ret = (statisDataLogObj!=NULL)&&(sample!=NULL);
    ret = ret&&(node!=NULL)&&(arr!=NULL);
    binaryTree *tree = NULL;
    void *nullV = NULL;
    if(ret ==1)
    {
        tree = &(statisDataLogObj->m_mainT);
        *arr  = getDataFromAvlNode(node);
        ret = setDataToAvlNode(node,&nullV);
        *sample = tree->getKey(node);
        ret = deleteKeyOfNodeDataInBinaryTree(tree,(void*)sample)&&ret; 
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
 
int getNumOfMainTDataInStatisDataLog(statisDataLog* statisDataLogObj)
{
    int ret=0;
    if(statisDataLogObj!=NULL)
    {
        ret = getNumBinaryNodeOfTree(&(statisDataLogObj->m_mainT));
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

int getnumOfAllTDatInSdl(statisDataLog* obj)
{
    int ret=0;
    if(obj != NULL)
    {        
        ret = getNumBinaryNodeOfTree(&(obj->m_mainT));
        ret += getNumBinaryNodeOfTree(&(obj->m_redundantTree));
        ret += getNumBinaryNodeOfTree(&(obj->m_discardInsTree));
        ret += getNumBinaryNodeOfTree(&(obj->m_inconsistTree));
        ret += getNumBinaryNodeOfTree(&(obj->m_incompleteTree));
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
void* getRootNodeOfMainTInSdl(statisDataLog* obj)
{
    void *p = NULL;
    if(obj!=NULL)
    {
        p =  obj->m_mainT.root;
    }
    else
    {
        /* do nothing */
    }
    return p;
}
void* getRootNodeOfRedunTInSdl(statisDataLog* obj)
{
    void *p = NULL;
    if(obj!=NULL)
    {
        p =  obj->m_redundantTree.root;
    }
    else
    {
        /* do nothing */
    }
    return p;
}
void* getRootNodeOfIncompTInSdl(statisDataLog* obj)
{
    void *p = NULL;
    if(obj!=NULL)
    {
        p =  obj->m_incompleteTree.root;
    }
    else
    {
        /* do nothing */
    }
    return p;
}

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
void randomArrFixSizeNBIn4Sdl(statisDataLog* obj,int whichTree,int swapTime)
{
    int fact1 = (obj != NULL)&&(whichTree >= 0);
    fact1 =  (fact1 == 1) && (whichTree <= 4);
    binaryTree *tTemp = NULL;
    if(fact1 == 1)
    {
        if (whichTree == 0)
        {
            tTemp = &(obj->m_mainT);
        }
        else if (whichTree == 1)
        {
            tTemp = &(obj->m_redundantTree);
        }
        else if (whichTree == 2)
        {
            tTemp = &(obj->m_inconsistTree);
        }
        else if (whichTree == 3)
        {
            tTemp = &(obj->m_incompleteTree);
        }
        else if (whichTree == 4)
        {
            tTemp = &(obj->m_discardInsTree);
        }
        if(tTemp != NULL)
        {
            swapRandomMt22dWithNum((struct mat2_2d *)(tTemp->parameter3),swapTime);
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

void printTsInSdl(statisDataLog* obj,int whichTree)
{
    int fact1 = (obj != NULL)&&(whichTree >= 0);
    fact1 =  (fact1 == 1) && (whichTree <= 4);
    binaryTree *tTemp = NULL;
    if(fact1 == 1)
    {
        if (whichTree == 0)
        {
            tTemp = &(obj->m_mainT);
        }
        else if (whichTree == 1)
        {
            tTemp = &(obj->m_redundantTree);
        }
        else if (whichTree == 2)
        {
            tTemp = &(obj->m_inconsistTree);
        }
        else if (whichTree == 3)
        {
            tTemp = &(obj->m_incompleteTree);
        }
        else if (whichTree == 4)
        {
            tTemp = &(obj->m_discardInsTree);
        }
        if(tTemp != NULL)
        {
            if((tTemp->printKeyPVoid != NULL)&&(tTemp->printTree != NULL))
            {
                char buff[300];
                void *tempV = tTemp->parameter3;
                tTemp->parameter3 =buff; 
                tTemp->printTree(tTemp,1);
                tTemp->parameter3=tempV;
                    
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
/*  #8 incomplete data  tree method*/
void constructIncompAndDiscAvlT4Sdl(binaryTree *obj,int vectorType)
{
    if(obj!=NULL)
    {
        if(vectorType == 0)
        {
            /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
            constructAvlTree((void*)obj,1,"custom type 2",0,sizeof(vector_double));
            setDelKeyAndDelDataAndCompFnForAvlTree(obj,NULL,delIncompAndDiscDataInSdl,compVDoub4StatisLog); 
            setDelKeyFnForAvlTree(obj,NULL);
            setDelKeyFlag(obj,1);
            obj->compareTypeWithOpt = compVDoubWithOpt4StatisLog;
        }
        else
        {
            constructAvlTree((void*)obj,3,"fixed arr no bin",11,5);
            setDelKeyAndDelDataAndCompFnForAvlTree(obj,NULL,delIncompAndDiscDataInSdl_NdFixNBin,compVDoub4StatisLog4Mt22d_NBin); 
            setDelKeyFnForAvlTree(obj,NULL);
            setDelKeyFlag(obj,1);
            obj->compareTypeWithOpt = compVDoubWithOpt4StatisLog4Mt22d_NBin;
            obj->getData = getPVLMt2;
            obj->clearNodesBinaryTree = clearNodeAvlTFNBin;
            obj->isPrint = 1;
        }
    }
    else
    {
        /* do nothing */
    }
}
void destructIncompAndDiscAvlT4Sdl(binaryTree *obj)
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

void delIncompAndDiscDataInSdl_NdFixNBin(void *obj,void *data)
{
    binaryTree *avlTree = (binaryTree*)obj;
    struct mat2Ele *ltPV2_1 = (struct mat2Ele*)data;
    if((avlTree!=NULL)&&(ltPV2_1!=NULL))
    {
        destructorPVoidList(ltPV2_1->m_startP);
        rmEleMt22d(avlTree->parameter4,ltPV2_1);
    }
    else
    {
        /* do nothing */
    }
}
void delIncompAndDiscDataInSdl(void *obj,void *data)
{
    pVoidList **list = (pVoidList**)data;
    if(list!=NULL)
    {
        if(*list !=NULL)
        {
            destructorPVoidList(*list );
            free(*list);
            *list =NULL;
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

void delDatOfIncompAndDiscAvlT4Sdl(void *data)
{
    if(data!=NULL)
    {
        destructIncompAndDiscDat((incompAndDiscData*)data);
        free(data);
    }
    else
    {
        /* do nothing */
    }
}
int initDataOfKeyOfIncompAndDiscAvlT4Sdl(void *node)
{
    int ret =0;
    void *list = NULL;
    if(node!=NULL)
    {
        list =(pVoidList*)malloc(sizeof(pVoidList));cM[7]++;
        ret =1;
    }
    else
    {
        /* do nothing */
    }
    if(list!=NULL) /* new node failed */
    {
        constructorPVoidList(list);
        setIsFreeDataOfPVoidList(list,1,(void*)&delDatOfIncompAndDiscAvlT4Sdl); /* 1   delete  data */
        setDataToAvlNode(node,&list);
    }
    else if(ret == 1)
    {
        setDataToAvlNode(node,&list);
    }
    else
    {
        ret =0;
    }
    return ret;
}
int addSampleToPvoidListDataOfIncompAndDiscAvlTr4Sdl_NdFixNBin(void *node,void *sample,statisDataLogElement *statEle,int numEle)
{
    void *list =NULL;
    int res=0;
    incompAndDiscData *incompDatTemp = NULL;
    if(node !=NULL)
    {
        list = ((struct mat2Ele*)((((struct nodeFixedArrNBIn*)node)->m_dat2)))->m_startP;
        incompDatTemp = (incompAndDiscData*)malloc(sizeof(incompAndDiscData));cM[8]++;
       /* printf("isPRt:%d ,incompDatTemp:%p  ",((pVoidList*)list)->isPrint,incompDatTemp);printNodeAndPVLAdrr(node);
        printKeyOfNdFixNBin(node);*/
        if((list !=NULL)&&(incompDatTemp!=NULL))
        {
            constructIncompAndDiscDat(incompDatTemp);
            addData2IncompAndDiscData(incompDatTemp,sample,statEle,numEle);
            res =  addDataPtPVoidList(list,(void**)&incompDatTemp);
          /*  printf("list count : %d\n",countPVoidList(list));*/
        }
        else if(incompDatTemp!=NULL)
        {
            free(incompDatTemp);
            incompDatTemp= NULL;
        }
        else
        {
            /* do nothing */
        }
    }
    return res;
}
int addSampleToPvoidListDataOfIncompAndDiscAvlTr4Sdl(void *node,vector_double *sample,statisDataLogElement *statEle,int numEle)
{
    void *list =NULL;
    int res=0;
    incompAndDiscData *incompDatTemp = NULL;
    if(node !=NULL)
    {
        list = getDataFromAvlNode(node);
        incompDatTemp = (incompAndDiscData*)malloc(sizeof(incompAndDiscData));cM[9]++;
        if((list !=NULL)&&(incompDatTemp!=NULL))
        {
            constructIncompAndDiscDat(incompDatTemp);
            addData2IncompAndDiscData(incompDatTemp,(void*)sample,statEle,numEle);
            res =  addDataPtPVoidList(list,(void**)&incompDatTemp);
          /*  printf("list count : %d\n",countPVoidList(list));*/
        }
        else if(incompDatTemp!=NULL)
        {
            free(incompDatTemp);
            incompDatTemp= NULL;
        }
        else
        {
            /* do nothing */
        }
    }
    return res;
}

/* #8e end  of incomplete data  tree method*/
/*
struct addNodeToTree
{
    char m_isVerify;
    char m_isNewKey;
    binaryTree *m_newTree;
    binaryTree *m_OldTree;
    struct statisDataLogElement *m_statEle;
    int m_num;
    int m_tempRes;
    void *m_newNode;
    void *m_oldNode;
    void (*process1)(struct addNodeToTree*); 
    void (*process2)(struct addNodeToTree*); 
    void (*process3)(struct addNodeToTree*); 
};
*/
/*  #9 addNodeToTree methods */
void verifyAddNodeToTree(addNodeToTree *obj)
{
    if(obj!=NULL)
    {
        obj->m_isVerify =((obj->sample)!=NULL)&&((obj->m_newTree)!=NULL)&&(obj->m_numProc>0);
        obj->m_isVerify = (obj->m_isVerify==1)&&((((obj->m_statEle)!=NULL)&&((obj->m_num)>=0))||(((obj->m_statEle)==NULL)&&((obj->m_num)==0)));
    }
    else
    {
        /* do nothing */
    }
}

void constructAddNodeToTree(addNodeToTree *obj)
{
    int index=0;
    if(obj!=NULL)
    {
        obj->m_isVerify =0;
        obj->m_num =0;
        obj->m_numProc =0;
        obj->m_tempRes =0;
        obj->m_plusValOld =0;
        obj->m_plusValNew =0;
        obj->sample =NULL;
        obj->m_newTree =NULL;
        obj->m_OldTree =NULL;
        obj->m_statEle =NULL;
        obj->m_newNode =NULL;
        obj->m_oldNode =NULL; 
        obj->m_oldNode =NULL; 
        obj->m_treeCountOld =NULL; 
        obj->m_treeCountNew =NULL;
        obj->m_PV2List =NULL;
        obj->m_PV2Ele =NULL;
        for(index=0;index<MAX_PROCESS;index++)
        {
            obj->m_fn[index] = NULL;
        }
    }
    else
    {
        /* do nothing */
    }
}
/* has only main process1*/
void newKey4MainT(addNodeToTree *obj)/* has only main process1*/
{
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        { 
           obj->m_newNode =obj->m_newTree->insertFn(obj->m_newTree,(void*)&(obj->sample));
        }
        else
        {
            /* do nothing */
        }
        obj->m_tempRes = (obj->m_newNode!=NULL);
    }
    else
    {
        /* do nothing */
    }
}
void newKey4GT(addNodeToTree *obj) /* has sub processes to init data */
{
    if(obj!=NULL)
    {
        if(obj->sample!=NULL)
        {
            obj->m_newNode =obj->m_newTree->insertFn(obj->m_newTree,&(obj->sample));
           /* if(obj->m_newTree->isPrint==1)
            printf("newNode : %p \n",obj->m_newNode);*/
        }
        else
        {
            /* do nothing */
        }
        obj->m_isVerify = (obj->m_newNode!=NULL);
        /* initial data */
    }
    else
    {
        /* do nothing */
    }
}

void initDtOfKy4GT_NBINFixNd(addNodeToTree *obj) /* it is  a sub process*/
{
    int ret =0;
    struct nodeFixedArrNBIn *tNode =NULL;
    void *mtList =NULL;
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        {
            tNode = (struct nodeFixedArrNBIn*)(obj->m_newNode);
            if(tNode!=NULL)
            {
                mtList = getDatNextMt22d(obj->m_PV2List);
                ret =1;
            }
            else
            {
                ret =0;
            }
            if(mtList != NULL)
            {
                constructPVList4PVEle2(mtList,obj->m_PV2Ele,&constrPVL2);
                initialPVList4PVEle2_1(mtList,0,&setIsFreeDataOfPVoidList,NULL);
                /* 0 no delete a sample from the source */
                tNode->m_dat2 = mtList;
            }
            else if(ret == 1)
            {
                tNode->m_dat2 = NULL;
            }
            else
            {
                ret = 0;
            }
        }
        else
        {
            printf("Error in initDtOfKy4GT_NBINFixNd Ln:%d, File:%s\n",__LINE__,__FILE__);
        }
        obj->m_isVerify=ret;
    }
    else
    {
        /* do nothing */
    }
}
void initDataOfKey4GT(addNodeToTree *obj) /* it is  a sub process*/
{
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        {
            obj->m_tempRes =initDataOfKeyOfAvlT4Sdl(obj->m_newNode);
        }
        else
        {
            /* do nothing */
        }
        obj->m_isVerify=obj->m_tempRes;
    }
    else
    {
        /* do nothing */
    }
}
void initDataOfKey4GT2_NBINFixNd(addNodeToTree *obj)/* it is  a sub process for incomp t*/
{
    void *ltPV2_1 = NULL;
    struct nodeFixedArrNBIn *ndNBin = NULL;
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        {
            obj->m_tempRes = 0;
            ndNBin = (struct nodeFixedArrNBIn*)(obj->m_newNode);
            if(obj->m_newNode!=NULL)
            {
                ltPV2_1 = getDatNextMt22d((void*)(obj->m_PV2List));
                obj->m_tempRes =1;
            }
            else
            {
                /* do nothing */
            }
            if(ltPV2_1!=NULL) /* new node failed */
            { 
                constructPVList4PVEle2(ltPV2_1,obj->m_PV2Ele,&constrPVL2);
                initialPVList4PVEle2_1(ltPV2_1,1,&setIsFreeDataOfPVoidList,&delDatOfIncompAndDiscAvlT4Sdl);/* 0 no delete a sample from the source */
                ndNBin->m_dat2 = ltPV2_1;
              /*  ((pVoidList*)(((struct mat2Ele*)ltPV2_1)->m_startP))->isPrint =1; */
        /*printf("iDt2juiC ");printNodeAndPVLAdrr(obj->m_newNode);*/
            }
            else if(obj->m_tempRes == 1)
            {
                ndNBin->m_dat2 = ltPV2_1;
            }
            else
            {
                obj->m_tempRes  = 0;
            }
            if(obj->m_oldNode == NULL)
            {
                obj->m_oldNode = obj->m_newNode;
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
        obj->m_isVerify=obj->m_tempRes ;
    }
    else
    {
        /* do nothing */
    }
}
void initDataOfKey4GT2(addNodeToTree *obj)/* it is  a sub process for incomp t*/
{
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        {
            obj->m_tempRes =initDataOfKeyOfIncompAndDiscAvlT4Sdl(obj->m_newNode);
            if(obj->m_oldNode==NULL)
            {
                obj->m_oldNode = obj->m_newNode;
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
        obj->m_isVerify=obj->m_tempRes;
    }
    else
    {
        /* do nothing */
    }
}
/* add data to old node process  */
void addData2Node_NBInFxNd(addNodeToTree *obj)
{
     void *theNode = NULL;
    if(obj!=NULL)
    {
        if(obj->m_OldTree ==NULL)
        {
            theNode =obj->m_oldNode;
        }
        else if(obj->m_isVerify ==1)
        {
            theNode =obj->m_newNode;
        }
        else
        {
            /*  do nothing */
        }
        if(obj->m_isVerify ==1)
        {
            obj->m_tempRes =addSamp2PVltDatOfAvlTr4Sdl_NBINFixNd(theNode,obj->sample);
            if(obj->m_tempRes ==0)
            {
                printf("Add data not Ok  %d \n",__LINE__);
            }
            else if((obj->m_numProc==1)&&(obj->m_treeCountNew!=NULL))
            {
                *(obj->m_treeCountNew) += obj->m_plusValNew;
            }
        }
        else
        {
            /* do nothing */
        }
        obj->m_isVerify=obj->m_tempRes;
    }
    else
    {
        /* do nothing */
    }
}void addData2Node(addNodeToTree *obj)
{
     void *theNode = NULL;
    if(obj!=NULL)
    {
        if(obj->m_OldTree ==NULL)
        {
            theNode =obj->m_oldNode;
        }
        else if(obj->m_isVerify ==1)
        {
            theNode =obj->m_newNode;
        }
        else
        {
            /*  do nothing */
        }
        if(obj->m_isVerify ==1)
        {
            obj->m_tempRes =addSampleToPvoidListDataOfAvlTr4Sdl(theNode,obj->sample);
            if(obj->m_tempRes ==0)
            {
                printf("Add data not Ok  %d \n",__LINE__);
            }
            else if((obj->m_numProc==1)&&(obj->m_treeCountNew!=NULL))
            {
                *(obj->m_treeCountNew) += obj->m_plusValNew;
            }
        }
        else
        {
            /* do nothing */
        }
        obj->m_isVerify=obj->m_tempRes;
    }
    else
    {
        /* do nothing */
    }
}
void addData2Node2_NdFixNBin(addNodeToTree *obj)/* it is  a sub process for incomp t*/
{
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        {
            obj->m_tempRes = addSampleToPvoidListDataOfIncompAndDiscAvlTr4Sdl_NdFixNBin(obj->m_oldNode,obj->sample, obj->m_statEle,obj->m_num);
            if(obj->m_treeCountNew!=NULL)
            {
                *(obj->m_treeCountNew) +=obj->m_plusValNew;
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
        obj->m_isVerify=obj->m_tempRes;
    }
    else
    {
        /* do nothing */
    }
}void addData2Node2(addNodeToTree *obj)/* it is  a sub process for incomp t*/
{
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        {
            obj->m_tempRes = addSampleToPvoidListDataOfIncompAndDiscAvlTr4Sdl(obj->m_oldNode,obj->sample, obj->m_statEle,obj->m_num);
            if(obj->m_treeCountNew!=NULL)
            {
                *(obj->m_treeCountNew) +=obj->m_plusValNew;
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
        obj->m_isVerify=obj->m_tempRes;
    }
    else
    {
        /* do nothing */
    }
}
/* move and delete an old node */
void moveDat2Node4GT(addNodeToTree *obj) /* main tree to another tree */
{
    int res =0;
    pVoidList *list =NULL;
    void *nNode=NULL;
    void *oNode=NULL;
    void *key = NULL; 
    /* verify Part */
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        {
            res =1;
            nNode = obj->m_newNode;
            oNode = obj->m_oldNode;
            key = (void*)*((void**)obj->m_OldTree->getKey(oNode)); 
            obj->m_oldNode = NULL;
            obj->m_newNode = NULL;
            
        }
        else
        {
            printf("INVALID OBJ in moveDat2Node4GT : fn:%d  fl:%s\n ",__LINE__,__FILE__);
        }
        if(res==1)
        {
            list = (pVoidList*)getDataFromAvlNode(nNode);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("NULL OBJ in moveDat2Node4GT : fn:%d  fl:%s\n ",__LINE__,__FILE__);
    }
    /* process part */
    if(res==1)
    {
        res = addDataPtPVoidList(list,&key);
    }
    else
    {
        /* do nothing */
    }
    /* delete old node */ 
    if(res==1)
    {
        obj->m_isVerify =obj->m_OldTree->deleteNodeByKey(obj->m_OldTree,&key); 
        res = obj->m_isVerify;
        if(res==0)
        {
            printf("can not remove node in moveDat2Node4GT, ln:%d, %s\n",__LINE__,__FILE__);
        }
        else
        {
            /* do nothing*/
        }
        if(obj->m_treeCountOld!=NULL)
        {
            *(obj->m_treeCountOld) += obj->m_plusValOld;
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_treeCountNew!=NULL)
        {
            *(obj->m_treeCountNew) += obj->m_plusValNew;
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
void mVDt2Nd4GT_NBINFIXArr(addNodeToTree *obj) /* main tree to another tree */
{
    int res =0;
    pVoidList *list =NULL;
    void *nNode=NULL;
    void *oNode=NULL;
    void *key = NULL; 
    /* verify Part */
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        {
            res =1;
            nNode = obj->m_newNode;
            oNode = obj->m_oldNode;
            key = (void*)*((void**)obj->m_OldTree->getKey(oNode)); 
            obj->m_oldNode = NULL;
            obj->m_newNode = NULL;
            
        }
        else
        {
            printf("INVALID OBJ in mVDt2Nd4GT_NBINFIXArr : fn:%d  fl:%s\n ",__LINE__,__FILE__);
        }
        if(res==1)
        {
            list = (pVoidList*)(((struct mat2Ele*)(((struct nodeFixedArrNBIn*)(nNode))->m_dat2))->m_startP);
            res = (list!=NULL);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("NULL OBJ in mVDt2Nd4GT_NBINFIXArr : fn:%d  fl:%s\n ",__LINE__,__FILE__);
    }
    /* process part */
    if(res==1)
    {
        res = addDataPtPVoidList(list,&key);
    }
    else
    {
        printf("Error mVDt2Nd4GT_NBINFIXArr list:%p, ln:%d,Fl:%s\n",list,__LINE__,__FILE__);
    }
    /* delete old node */ 
    if(res==1)
    {
        obj->m_isVerify =obj->m_OldTree->deleteNodeByKey(obj->m_OldTree,&key); 
        res = obj->m_isVerify;
        if(res==0)
        {
            printf("can not remove node in mVDt2Nd4GT_NBINFIXArr, ln:%d, %s\n",__LINE__,__FILE__);
        }
        else
        {
            /* do nothing*/
        }
        if(obj->m_treeCountOld!=NULL)
        {
            *(obj->m_treeCountOld) += obj->m_plusValOld;
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_treeCountNew!=NULL)
        {
            *(obj->m_treeCountNew) += obj->m_plusValNew;
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

void moveDat2Node4GT2(addNodeToTree *obj) /* inconsist to/from redundant tree*/
{
    int res =0;
    void *nNode=NULL;
    void *oNode=NULL;
    void *key = NULL;
    /* verify Part */
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        {
            res =1;
            nNode = obj->m_newNode;
            oNode = obj->m_oldNode;
            key = (void*)*((void**)obj->m_OldTree->getKey(oNode));
            
        }
        else
        {
            printf("INVALID OBJ in moveDat2Node4GT2 : fn:%d  fl:%s\n ",__LINE__,__FILE__);
        }
    }
    else
    {
        printf("NULL OBJ in moveDat2Node4GT2 : fn:%d  fl:%s\n ",__LINE__,__FILE__);
    }
    /* process part */
    if(res==1)
    {
        res = moveDataOfOldNodeToNewNodeOfAvlT4Sdl(nNode,oNode);
    }
    else
    {
        /* do nothing */
    }
    /* delete old node */
    if(res==1)
    {
        obj->m_isVerify =obj->m_OldTree->deleteNodeByKey(obj->m_OldTree,&key); 
        res = obj->m_isVerify;
        if(res==0)
        {
            printf("can not remove node in moveDat2Node4GT2, ln:%d, %s\n",__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_treeCountOld!=NULL)
        {
            *(obj->m_treeCountOld) += obj->m_plusValOld;
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_treeCountNew!=NULL)
        {
            *(obj->m_treeCountNew) += obj->m_plusValNew;
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
}void moveDat2Node4GT2_NBINFIXArr(addNodeToTree *obj) /* inconsist to/from redundant tree*/
{
    int res =0;
    void *nNode=NULL;
    void *oNode=NULL;
    void *key = NULL;
    /* verify Part */
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        {
            res =1;
            nNode = obj->m_newNode;
            oNode = obj->m_oldNode;
            key = (void*)*((void**)obj->m_OldTree->getKey(oNode));
            
        }
        else
        {
            printf("INVALID OBJ in moveDat2Node4GT2 : fn:%d  fl:%s\n ",__LINE__,__FILE__);
        }
    }
    else
    {
        printf("NULL OBJ in moveDat2Node4GT2 : fn:%d  fl:%s\n ",__LINE__,__FILE__);
    }
    /* process part */
    if(res==1)
    {
        res = mvDatOfONd2NNdOfAvlT4Sdl__NBINFIXArr(nNode,oNode);
    }
    else
    {
        /* do nothing */
    }
    /* delete old node */
    if(res==1)
    {
        obj->m_isVerify =obj->m_OldTree->deleteNodeByKey(obj->m_OldTree,&key); 
        res = obj->m_isVerify;
        if(res==0)
        {
            printf("can not remove node in moveDat2Node4GT2, ln:%d, %s\n",__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_treeCountOld!=NULL)
        {
            *(obj->m_treeCountOld) += obj->m_plusValOld;
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_treeCountNew!=NULL)
        {
            *(obj->m_treeCountNew) += obj->m_plusValNew;
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

int runAllProcs4AddNode2T(addNodeToTree *obj)
{
    int index=0;
    int num =0;
     void (*fn)(struct addNodeToTree*);
    if(obj!=NULL)
    {
        if(obj->m_isVerify ==1)
        {
            num = obj->m_numProc;
            for(index=0;index<num;index++)
            {
                fn = obj->m_fn[index];
                fn(obj);
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
    return obj->m_isVerify ;
}
/*  #9e addNodeToTree methods */

/* #10 traverseBuff methods */
/*struct traverseBuff
{
    struct statisDataLog *m_pSldFile;
    struct statisDataLog *m_pSldClass;
    int m_numClass;
    binaryTree *m_pIdenClass;
     

};*/
void constructorTravBuff(traverseBuff *obj)
{
    if(obj!=NULL)
    {
        obj->m_pSldFile = NULL;
        obj->m_pSldClass = NULL;
        obj->m_numClass = 0;
        obj->m_numOut = 0;
        obj->m_numIn = 0;
        obj->m_pIdenClass = NULL;
        obj->m_sam = NULL;
        obj->m_t = NULL;
        obj->m_p = NULL;
        obj->m_findN= NULL; 
        obj->m_bufSam = new_vector_double(0);
    }
    else
    {
        /* do nothing */
    }
}

int getNumClassFromTravBuff(traverseBuff *obj)
{
    return obj->m_numClass;
}
void initValueOfTravBuff(traverseBuff *obj,statisDataLog *objFile,statisDataLog *objClass,int numClass,int numOut,int numInp,binaryTree *idenT,struct groupVariableSdv *keepDat)
{
    if((obj!=NULL)&&(numClass>1))
    {
        obj->m_pSldFile = objFile;
        obj->m_pSldClass = objClass;
        obj->m_keepDatStatis = keepDat;
        obj->m_numOut = numOut;
        obj->m_numIn = numInp;
        obj->m_numClass = numClass;
        obj->m_pIdenClass = idenT;
        if(objFile !=NULL)
        {
            obj->m_t = &(objFile->m_mainT); 
        }
        if(obj->m_numOut>1)
        {
            obj->findWhichClass = &findClass4V4Sdl;
        }
        else if(obj->m_numOut==1)
        {
            obj->findWhichClass = &findClass4NotV4Sdl;
        }
    }
    else
    {
        /* do nothing */
    }
}
void init2FindRedunTravBuff(traverseBuff *obj)
{
    if(obj!=NULL)
    {
        if(obj->m_pSldFile !=NULL)
        {
            obj->m_t = &(obj->m_pSldFile->m_redundantTree); 
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
void destructorTravBuff(traverseBuff *obj)
{
    if(obj!=NULL)
    {
        obj->m_pSldFile = NULL;
        obj->m_pSldClass = NULL;
        obj->m_keepDatStatis = NULL;
        obj->m_numClass = 0;
        obj->m_numOut = 0;
        obj->m_numIn = 0;
        obj->m_pIdenClass = NULL;
        obj->m_sam = NULL;
        obj->m_t = NULL;
        obj->m_p = NULL;
        obj->m_findN= NULL;
        obj->m_bufSam = new_vector_double(0);
    }
    else
    {
        /* do nothing */
    }
}
 
/* depth first traverse */
int traverseMainTMSamp2OthT4Sdl(traverseBuff *obj,void *node)
{
    int temp =(obj !=NULL);
    int index = 0;
    void *p2=NULL;
    if((node !=NULL)&&(obj !=NULL))
    {
        /* left node*/
        temp = traverseMainTMSamp2OthT4Sdl(obj,obj->m_t->getNodeLeft(node));
        /* right node*/
        temp = temp&traverseMainTMSamp2OthT4Sdl(obj,obj->m_t->getNodeRight(node));
        /* search agaist with iden T*/
        obj->findWhichClass(obj,node);
    /* below is not yet */
        /* match */
        if(obj->m_findN!=NULL)
        {
            index = *((int*)getDataFromAvlNode(obj->m_findN));
            keepDat2GroupVariableSdv(obj->m_keepDatStatis,obj->m_sam,index);
            temp = temp&addDataToStatisDataLog(&(obj->m_pSldClass[index]),obj->m_sam,NULL,0);
        }
        else /* found new class */
        { 
            index = getNumBinaryNodeOfTree(obj->m_pIdenClass); 
            p2 = malloc(sizeof(int));cM[10]++;
            /* for vector output  or numOutput >1*/
            if(obj->findWhichClass == &findClass4V4Sdl)
            {
                obj->m_p = malloc(sizeof(vector_double));cM[11]++;
                *((vector_double*)(obj->m_p)) = new_vector_double(obj->m_numOut);
                copy_v_double(obj->m_p,&(obj->m_bufSam));
            }
            else
            {
                /* do nothing */
            }
            if((obj->m_numClass >index)&&(p2!=NULL))
            { 
                *((int*)p2 )=index;
                obj->m_p  =obj->m_pIdenClass->insertFn(obj->m_pIdenClass,&(obj->m_p));
                temp = setDataToAvlNode(obj->m_p ,&p2); 
                obj->m_p =NULL;
                p2 =NULL;
                keepDat2GroupVariableSdv(obj->m_keepDatStatis,obj->m_sam,index);
                temp = temp&addDataToStatisDataLog(&(obj->m_pSldClass[index]),obj->m_sam,NULL,0);
            }
            else
            {
                temp =0;
                printf("Error !! There is unknown class, Line:%d \n",__LINE__);
                if(p2!=NULL)
                {
                    free(p2);
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
    return temp;
}
void findClass4NotV4Sdl(traverseBuff *obj,void *node)
{     
        /* search agaist with iden T*/
        if(obj->m_keepDatStatis->m_inputType == 0)
        {
            obj->m_sam =(void*)(*((vector_double**)obj->m_t->getKey(node)));
            obj->m_p =(void*)&(((vector_double*)(obj->m_sam))->data[obj->m_numIn]);
            obj->m_findN = searchDataInBinaryTree(obj->m_pIdenClass,&(obj->m_p));
        }
        else if(obj->m_keepDatStatis->m_inputType == 1)
        {
            obj->m_sam =(void*)(*((struct mat2Ele**)obj->m_t->getKey(node)));
            obj->m_p =(void*)&(((double*)(((struct mat2Ele*)(obj->m_sam))->m_startP))[obj->m_numIn]);
            obj->m_findN = searchDataInBinaryTree(obj->m_pIdenClass,&(obj->m_p));
        }
        else
        {
            /* do nothing */
        }
} 
void findClass4V4Sdl(traverseBuff *obj,void *node)
{ 
    vector_double* vtemp =NULL;
    struct mat2Ele* m2Etemp =NULL;
    if((obj!=NULL)&&(node!=NULL))
    {
        if(obj->m_keepDatStatis->m_inputType == 0)
        {
            obj->m_sam = (void*)(*((vector_double**)obj->m_t->getKey(node)));
            if(obj->m_sam!=NULL)
            {
                vtemp = (vector_double*)(obj->m_sam);
                obj->m_bufSam.data = &(vtemp->data[obj->m_numIn]);
                obj->m_bufSam.lenght =  obj->m_numOut;
            }
            else
            {
                obj->m_bufSam.data =NULL;
                obj->m_bufSam.lenght = 0;
            }

        }
        else if(obj->m_keepDatStatis->m_inputType == 1)
        {
            obj->m_sam = (void*)(*((struct mat2Ele**)obj->m_t->getKey(node)));
            if(obj->m_sam!=NULL)
            {
                m2Etemp = (struct mat2Ele*)(obj->m_sam);
                obj->m_bufSam.data = &(((double*)(m2Etemp->m_startP))[obj->m_numIn]);
                obj->m_bufSam.lenght =  obj->m_numOut;
            }
            else
            {
                obj->m_bufSam.data =NULL;
                obj->m_bufSam.lenght = 0;
            }
        }
        /* search agaist with iden T*/  
        obj->m_p =(void*)&(obj->m_bufSam);
        obj->m_findN = searchDataInBinaryTree(obj->m_pIdenClass,&(obj->m_p)); 
    }
    else
    {
        /* do nothing */
    }

} 

/* #10e traverseBuff methods */

/* #11  statistic value  method */
void constructEleSdv(elemSdv *obj)
{
    if(obj !=NULL)
    {
    
        constructPossibleValTreeInEleSdv(obj);
        obj->m_maxValueInDim =0.0;
        obj->m_minValueInDim =0.0;
        obj->m_isSetMin =0;
        obj->m_avail =0;/* <!-- availValue = available value is using the value from input to replace a missing value-->
                        <!-- use is 1 not use 0 -->  */
        obj->m_sdOpt =0;/*statistic option for mode and median
                         0 is mean them (default value)
                         1 is random choose*/
        obj->m_numMedian =0;
        obj->m_isSetMax =0;
        obj->m_meanValueInDim =0.0;
        obj->m_lastMedianValue =0.0;
        obj->m_medianValueInDim =0.0;
        obj->m_medianVal2 =0.0;
        obj->m_modValueInDim =0.0;
        obj->m_sum =0.0;
        obj->m_numMem =0.0;
        obj->m_middleValueP =NULL;
        obj->m_numMemInMin =-1;
        obj->m_numMemInMax =-1;
        obj->m_maxCount = 0;
        obj->m_numSameCount = 0;
        constructorPVoidList(&(obj->m_hignFreqValList));
        setIsFreeDataOfPVoidList(&(obj->m_hignFreqValList),0,NULL); /* not free data */
        /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
        constructAvlTree((void*)&(obj->m_maxHeap),1,"double",0,sizeof(double));
        setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_maxHeap),NULL,delDatOfHeadInEleSdv,compHeadInEleSdv); 
        obj->m_maxHeap.compareTypeWithOpt = NULL;
        setDelKeyFnForAvlTree(&(obj->m_maxHeap),NULL);
        setDelKeyFlag(&(obj->m_maxHeap),1);
        
        /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
        constructAvlTree((void*)&(obj->m_minHeap),1,"double",0,sizeof(double));
        setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_minHeap),NULL,delDatOfHeadInEleSdv,compHeadInEleSdv); 
        obj->m_minHeap.compareTypeWithOpt = NULL;
        setDelKeyFnForAvlTree(&(obj->m_minHeap),NULL);
        setDelKeyFlag(&(obj->m_minHeap),1);
        
        
        obj->m_medianValueAvailValue =0.0;
        obj->m_meanValueAvailValue =0.0;
        obj->m_modValueAvailValue =0.0;
    }
    else
    {
        /* do nothing */
    }
}

void destructEleSdv(elemSdv *obj)
{
    if(obj !=NULL)
    {
        obj->m_maxValueInDim =0.0;
        obj->m_minValueInDim =0.0;
        obj->m_isSetMin =0;
        obj->m_isSetMax =0;
        obj->m_sdOpt =0;
        obj->m_avail =0;
        obj->m_numMedian =0;
        obj->m_meanValueInDim =0.0;
        obj->m_lastMedianValue =0.0;
        obj->m_medianValueInDim =0.0;
        obj->m_medianVal2 =0.0;
        obj->m_modValueInDim =0.0;
        obj->m_sum =0.0;
        obj->m_numMem =0.0;
        obj->m_middleValueP =NULL;
        obj->m_numMemInMin =-1;
        obj->m_numMemInMax =-1; 
        obj->m_maxCount = 0;
        obj->m_numSameCount = 0;
        destructorPVoidList(&(obj->m_hignFreqValList));
        clearBinaryTree(&( obj->m_maxHeap));
        clearBinaryTree(&( obj->m_minHeap));
        DestructurePossibleValTreeInEleSdv(obj);
        
        
        obj->m_medianValueAvailValue =0.0;
        obj->m_meanValueAvailValue =0.0;
        obj->m_modValueAvailValue =0.0;
    }
    else
    {
        /* do nothing */
    }
}

int compDoublePossibleValTreeInEleSdv(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(**((double**)a)== **((double**)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(**((double**)a)> **((double**)b))
        {
            res =MORE_DEFINE;
        }
        else if(**((double**)a)< **((double**)b))
        {
            res =LESS_DEFINE;
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
void constructPossibleValTreeInEleSdv(elemSdv *obj)
{
    binaryTree *avlTreeP =NULL;
    if(obj!=NULL)
    {
        avlTreeP = &(obj->m_possibleValTree);
        constructAvlTree((void*)avlTreeP,0,"double",0,sizeof(double)); 
        setDelKeyAndDelDataAndCompFnForAvlTree(avlTreeP,deleteDoubleKeyNode4PossibleValTOfEleSdv,NULL,compDoublePossibleValTreeInEleSdv);
        avlTreeP->printKeyPVoid = printDoubleKey4PossibleValTOfEleSdv;
    }
    else
    {
        /* do nothing */
    }
}
void DestructurePossibleValTreeInEleSdv(elemSdv *obj)
{
    if(obj!=NULL)
    {
        clearBinaryTree(&(obj->m_possibleValTree));
    }
    else
    {
        /* do nothing */
    }
}
void deleteDoubleKeyNode4PossibleValTOfEleSdv(void *obj,void *key)
{
    void **p = (void**)key;
    if(*p!=NULL)
    {
        free(*p);
    }
    else
    {
        /* do nothing */
    }
}
void printDoubleKey4PossibleValTOfEleSdv(void* key,char* buff)
{
    if((key != NULL )&&(buff != NULL))
    {
        sprintf(buff,"%f",*((double*)key));
    }
    else
    {
        /* do nothing */
    }
}
void setSdOptionEleSdv(elemSdv *obj,char val)
{
    if((val >=0)&&(val<=1)&&(obj !=NULL))
    {
        obj->m_sdOpt = val;
    }
    else
    {
        /* do nothing */
    }
}
void delDatOfHeadInEleSdv(void *obj,void *data)
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
int compHeadInEleSdv(const void* a,const void *b)
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



void keepDat2EleSdv(elemSdv *obj,double *val)
{
    double temp = 0.0;
    double *pTemp =NULL;
    double *tp =NULL;
    double *tp2 =NULL;
    char factA=0;
    char factB=0;
    void *node =NULL;
    int *tmpInt = NULL;
    int countRepeat=0;
    if(obj !=NULL)
    {
        temp = *val;
        if(obj->m_isSetMin ==0)
        {
            obj->m_isSetMin=1;
            obj->m_minValueInDim=temp;
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_isSetMax ==0)
        {
            obj->m_isSetMax=1;
            obj->m_maxValueInDim=temp;
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_maxValueInDim<temp)
        {
            obj->m_maxValueInDim=temp;
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_minValueInDim>temp)
        {
            obj->m_minValueInDim=temp;
        }
        else
        {
            /* do nothing */
        }
        obj->m_sum +=temp;
        obj->m_numMem++;
        obj->m_modValueInDim =0.0;

        node = insertValP2HeapEleSdv(obj,val,0,&countRepeat); /* 0 is not force selection heap*/
        add2QModeEleSdv(obj,val,countRepeat);
        /* median value */

        factA =((obj->m_numMemInMax-obj->m_numMemInMin)>=2);
        factB =((obj->m_numMemInMin-obj->m_numMemInMax)>=2);
        if(factA==1)
        {
            node = getNodeMinEleSdv(&(obj->m_maxHeap),obj->m_maxHeap.root); 
            tmpInt =(int*)getDataFromAvlNode(node);
            tp = *((double**)obj->m_maxHeap.getKey(node));
            
            if(*tmpInt==1)
            {
                    if(obj->m_maxHeap.deleteNodeByKey(&(obj->m_maxHeap),&tp)==1)
                    {
                        obj->m_numMemInMax--;
                        tp2 = obj->m_middleValueP;
                        obj->m_middleValueP = tp;
                        node = insertValP2HeapEleSdv(obj,tp2,2,&countRepeat);
                    }
                    else
                    {
                        printf("Error to delete node of Max Head %d \n",__LINE__);
                    }
            }
            else
            {
                (*tmpInt)--;
                obj->m_numMemInMax--;
                tp2 = obj->m_middleValueP;
                obj->m_middleValueP = tp;
                node = insertValP2HeapEleSdv(obj,tp2,2,&countRepeat);
            }
            
            if(node==NULL)
            {
                printf("Error cannot move value from Max to Min heap : %d\n",__LINE__);
            }
            else
            {
                /* do nothing */
            }
        }
        else if(factB==1)
        {
            node = getNodeMaxEleSdv(&(obj->m_minHeap),obj->m_minHeap.root);
            tmpInt =(int*)getDataFromAvlNode(node);
            tp = *((double**)obj->m_minHeap.getKey(node));
            
            if(*tmpInt==1)
            {
                    if(obj->m_minHeap.deleteNodeByKey(&(obj->m_minHeap),&tp)==1)
                    {
                        obj->m_numMemInMin--;
                        tp2 = obj->m_middleValueP;
                        obj->m_middleValueP = tp;
                        node = insertValP2HeapEleSdv(obj,tp2,1,&countRepeat);
                    }
                    else
                    {
                        printf("Error to delete node of Min Head %d \n",__LINE__);
                    }
            }
            else
            {
                (*tmpInt)--;
                obj->m_numMemInMin--;
                tp2 = obj->m_middleValueP;
                obj->m_middleValueP = tp;
                node = insertValP2HeapEleSdv(obj,tp2,1,&countRepeat);
            }
            
            if(node==NULL)
            {
                printf("Error cannot move value from Min to Max heap : %d\n",__LINE__);
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
        if(searchDataInBinaryTree(&(obj->m_possibleValTree),&val)==NULL)
        {
            pTemp = (double*)malloc(sizeof(double));cM[12]++;
            if(pTemp!=NULL)
            {
                *pTemp = *val;
                obj->m_possibleValTree.insertFn(&(obj->m_possibleValTree),&pTemp);
            }
            else
            {
                printf("Error cannot allocate the data for the possible value tree, %s, ln:%d\n",__FILE__,__LINE__);
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
void findNeighbourOfStatisticValInAvlT4EleSdv(binaryTree *bin,void *node,data4FindMinMaxValInT *obj)
{
    double currentVal =0.0;
    double maxVal =0.0;
    double minVal =0.0;
    double val =0.0;
    if((bin!=NULL)&&(node!=NULL)&&(obj!=NULL))
    {
        currentVal = obj->m_val;
        maxVal = obj->m_max;
        minVal = obj->m_min;
        val = **((double**)bin->getKey(node));
        if((maxVal >val)&&(val>currentVal))
        {
            setMaxInData4FindMinMaxValInT(obj,val);
            findNeighbourOfStatisticValInAvlT4EleSdv(bin,bin->getNodeLeft(node),obj);
        }
        else
        {
            /* do nothing */
        }
        if((minVal <val)&&(val<currentVal))
        {
            setMinInData4FindMinMaxValInT(obj,val);
            findNeighbourOfStatisticValInAvlT4EleSdv(bin,bin->getNodeRight(node),obj);
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
void findNeighbourOfStatisticValInAvlT4EleSdv2(binaryTree *bin,double maxVal,double minVal,double inputVal,double *outputVal)
{
    double *tmpValDouble =NULL;
    data4FindMinMaxValInT tmpAvialInput;
    if((bin!=NULL)&&(outputVal!=NULL))
    {
        tmpValDouble = &inputVal;
        if(searchDataInBinaryTree(bin,&tmpValDouble)!=NULL)
        {
            *outputVal =inputVal;
        }
        else
        {
            constructorData4FindMinMaxValInT(&tmpAvialInput);
            setMaxInData4FindMinMaxValInT(&tmpAvialInput,maxVal);
            setMinInData4FindMinMaxValInT(&tmpAvialInput,minVal);
            setValInData4FindMinMaxValInT(&tmpAvialInput,inputVal);
            findNeighbourOfStatisticValInAvlT4EleSdv(bin,bin->root,&tmpAvialInput);
            if((inputVal-tmpAvialInput.m_min) <=(tmpAvialInput.m_max-inputVal))
            {
                *outputVal =tmpAvialInput.m_min;
            }
            else
            {
                *outputVal =tmpAvialInput.m_max;
            }
        }
    }
    else
    {
        /* do nothign */
    }
}
void* getNodeMaxEleSdv(binaryTree *obj, void *root)
{
    if(obj->getNodeRight(root)!=NULL)
    {
        return getNodeMaxEleSdv(obj,obj->getNodeRight(root));
    }
    else
    {
        return root;
    }
}
void* getNodeMinEleSdv(binaryTree *obj, void *root)
{
    if(obj->getNodeLeft(root)!=NULL)
    {
        return getNodeMinEleSdv(obj,obj->getNodeLeft(root));
    }
    else
    {
        return root;
    }
}

void add2QModeEleSdv(elemSdv *obj,double *val,int countRepeat)
{
    char fact1 = (obj!=NULL)&&(val!=NULL)&&(countRepeat >1);
    char fact2 =0;
    int countEle =0;
    pVoidList *list =NULL;
    int index=0;
    int num=0;
    if(fact1 ==1)
    {
        list = &(obj->m_hignFreqValList);
        if(obj->m_maxCount <countRepeat)
        {
            obj->m_maxCount = countRepeat;
            obj->m_numSameCount = 1;
            countEle =countPVoidList(list);
            if(countEle>1)
            {
                fact1 =replaceValInPVoidList(list,(void*)val,0);
            }
            else
            {
                fact1 = addDataPtPVoidList(list,(void**)&val);
            }
        }
        else if(obj->m_maxCount ==countRepeat)
        {
            fact2=0;
            num =obj->m_numSameCount;
            /*
            printf("count : %d ,numList : %d -- %p -- same:%d \n ",countRepeat,num,list,obj->m_numSameCount);
            */
            for(index=0;index<num;index++)
            {
                /*
                printf("%f ",*((double*)getDataPVoidList(list,index)));
                */
                if(*((double*)getDataPVoidList(list,index))== *val)
                {
                    fact2 =1;
                    break;
                }
                else
                {
                    /* do nothing */
                }
            }
            /*
            printf("\n"); 
            */
            if(fact2==0)
            {
                obj->m_numSameCount++;
                countEle =countPVoidList(list);
                if(countEle>=obj->m_numSameCount)
                {
                    /*
                    printf("replace old value \n");
                    */
                     fact1 = replaceValInPVoidList(list,(void*)val,obj->m_numSameCount-1);
                }
                else
                {
                    /*
                    printf("new value \n");
                    */
                    fact1 = addDataPtPVoidList(list,(void**)&val);
                }
                /*
                printf("numSame : %d\n",obj->m_numSameCount);
                */
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
        if(fact1==0)
        {
            printf("Error to add value to mode list : %d \n",__LINE__);
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
    clock_t timeCount;
void *insertValP2HeapEleSdv(elemSdv *obj,double *val,char forceVal,int *countRepeat)
{
                timeCount =clock();
    double temp =0.0;
    binaryTree *pBinaryT=NULL;
    binaryTree *pBinaryT2=NULL;
    int *tmpInt = NULL;
    void *node =NULL;
    void *node2 =NULL;
    char fact1 =(obj!=NULL)&&(val!=NULL);
    if(fact1==1)
    {
        temp = *val;
        /* procedure of median */
        /* find appropriate tree */
        if(forceVal==1) /* to max heap */
        {
            pBinaryT = &(obj->m_maxHeap);
            pBinaryT2 = &(obj->m_minHeap);
            obj->m_numMemInMax++;
        }
        else  if(forceVal==2) /* to min heap */
        {
            pBinaryT = &(obj->m_minHeap);
            pBinaryT2 = &(obj->m_maxHeap);
            obj->m_numMemInMin++;
        }
        else if((obj->m_numMemInMax==-1)&&(obj->m_numMemInMin==-1))
        {
            obj->m_numMemInMin=0;
            obj->m_numMemInMax=0;
            obj->m_middleValueP=val;
        }
        else if(*(obj->m_middleValueP)>temp)
        {
            pBinaryT = &(obj->m_minHeap);
            pBinaryT2 = &(obj->m_maxHeap);
            obj->m_numMemInMin++;
        }
        else if(*(obj->m_middleValueP)<=temp)
        {
            pBinaryT = &(obj->m_maxHeap);
            pBinaryT2 = &(obj->m_minHeap);
            obj->m_numMemInMax++;
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* do nothing*/
    }
    /* search for repeat node */
    if(pBinaryT !=NULL)
    {
        node =searchDataInBinaryTree(pBinaryT,&val);
        if(*(obj->m_middleValueP)==temp)
        {
            *countRepeat = 1;
        }
        else
        {
            *countRepeat = 0;
        }
        if(node !=NULL)
        {
            tmpInt =(int*)getDataFromAvlNode(node);
            (*tmpInt)++;
            *countRepeat = *countRepeat+*tmpInt;
            /* to update count */
            node2 =searchDataInBinaryTree(pBinaryT2,&val);
            if(node2 !=NULL)
            {
                tmpInt =(int*)getDataFromAvlNode(node2);
                *countRepeat = *countRepeat+*tmpInt;
            }
            else
            {
                /* do nothign */
            }
        }
        else
        {
            node = pBinaryT->insertFn(pBinaryT,&val);
            if(node !=NULL)
            {
                tmpInt = (int*)malloc(sizeof(int));cM[13]++;
                
                if(tmpInt !=NULL)
                {
                    *tmpInt =1;
                    *countRepeat =*countRepeat+1;
                    setDataToAvlNode(node,&tmpInt);
                }
                else
                {
                    printf("Error Cannot allocate to keep repeat value to find Medain value: %s  :%d\n",__FILE__,__LINE__);
                }
                /* to update count */
                node2 =searchDataInBinaryTree(pBinaryT2,&val);
                if(node2 !=NULL)
                {
                    tmpInt =(int*)getDataFromAvlNode(node2);
                    *countRepeat = *countRepeat+*tmpInt;
                }
                else
                {
                    /* do nothign */
                }
            }
            else
            {
               printf("Error Cannot insert node to Max/min T to find median value :%s %d\n",__FILE__,__LINE__);
            }
        }
    }
    else
    {
        /* do nothing */
    }
                timeCount =clock()-timeCount;cM[22] +=timeCount;
    return node;
}

void printTinEleSdv(void *key,char *buff)
{ 
    if((key!=NULL)&&(buff!=NULL))
    {
        sprintf(buff,"%f ",*((double*)key));
    }
    else
    {
        /* do nothing */
    }
}
void printDataTinEleSdv(void *node,char *buff)
{ 
    void *dat =NULL;
    if((node!=NULL)&&(buff!=NULL))
    {
        dat = getDataFromAvlNode(node);
        sprintf(buff,"|+ %d +|",*((int*)dat));
    }
    else
    {
        /* do nothing */
    }
}
void printEleSdv(elemSdv *obj)
{
    char buff[200];
    buff[0] =0;
    int num=0;
    int index=0;
    if(obj ==NULL)
    {
        /* do nothing */
    }
    else if(obj->m_numMem>0)
    {
        printf("\nStd Opt : %d  ",obj->m_sdOpt);
        printf("Avail input : %d\n",obj->m_avail);
        printf("(min,max) : (%f,%f) \n",obj->m_minValueInDim,obj->m_maxValueInDim);
        printf("mean : %f \n",obj->m_meanValueInDim);
        printf("sum: %f  ... numMem : %f \n",obj->m_sum,obj->m_numMem);
        printf("mode : %f _ maxFrequency: %d \n",obj->m_modValueInDim,obj->m_maxCount);
        if(obj->m_numMedian >1)
        {
            printf("median :%f , %f and %f   , Num Max : %d ,  Num Min:%d \n",obj->m_lastMedianValue,obj->m_medianValueInDim,obj->m_medianVal2,obj->m_numMemInMax,obj->m_numMemInMin);
        }
        else
        {
            printf("median : %f   , Num Max : %d ,  Num Min:%d \n",obj->m_lastMedianValue,obj->m_numMemInMax,obj->m_numMemInMin);
        } 

        if(obj->m_maxCount>0)
        {
            /*
            printf("m_maxCount : %d  --- same : %d  ---- %p\n",obj->m_maxCount,obj->m_numSameCount,&(obj->m_hignFreqValList));
            */
            num = countPVoidList(&(obj->m_hignFreqValList));
            printf("m_maxCount : %d  --- same : %d , numList : %d  \n",obj->m_maxCount,obj->m_numSameCount,num);

            if((obj->m_numSameCount <= num)&&(obj->m_numSameCount>1))
            {
                num = obj->m_numSameCount;
                for(index=0;index<num;index++)
                {
                    printf("%f ",*((double*)getDataPVoidList(&(obj->m_hignFreqValList),index)));
                }
                printf("\n");
            }
            if(obj->m_numMem <150)
            {
                                obj->m_maxHeap.printDataPVoid =&printDataTinEleSdv; 
                obj->m_minHeap.printDataPVoid =&printDataTinEleSdv; 
                obj->m_maxHeap.printKeyPVoid =&printTinEleSdv; 
                obj->m_minHeap.printKeyPVoid =&printTinEleSdv; 

                /* prepare buffer before print tree */
                obj->m_minHeap.parameter3 = &buff;
                obj->m_maxHeap.parameter3 = &buff;
                /* print tree of Heaps */
                obj->m_minHeap.printTree(&(obj->m_minHeap),0);
                printf("---- median : %f  ---- \n",*(obj->m_middleValueP));
                obj->m_maxHeap.printTree(&(obj->m_maxHeap),0);

                
                
            }
            else
            {
                /* do nothign */
            }
        }
        else
        {
            /* do nothing */
        }
        
        obj->m_possibleValTree.parameter3 = &buff;
        /*printf("possible value number : %d\n",getNumBinaryNodeOfTree(&(obj->m_possibleValTree)));
        obj->m_possibleValTree.printTree(&(obj->m_possibleValTree),0);*/
    }
    else
    {
        printf("No element\n");
    }
}
/* 4 find mean, mode and median from the data that kept */
void summarizeEleSdv(elemSdv *obj)
{
    void *node =NULL;
    double *tempD =NULL;
    int randVal = 0;
    int num=0;
    int index=0; 
    if(obj==NULL)
    {
        /* do nothing */
    }
    else if(obj->m_numMem >0)
    { 
        /*void findNeighbourOfStatisticValInAvlT4EleSdv(binaryTree *bin,void *node,data4FindMinMaxValInT *obj)*/
        /*  mean calculation */
        obj->m_meanValueInDim =obj->m_sum/obj->m_numMem;
        /* find avial of mean value*/
        findNeighbourOfStatisticValInAvlT4EleSdv2(&(obj->m_possibleValTree),obj->m_maxValueInDim,obj->m_minValueInDim,obj->m_meanValueInDim,&(obj->m_meanValueAvailValue));
        /*printf("-112-Mean :%f , avialVal:%f \n",obj->m_meanValueInDim,obj->m_meanValueAvailValue);*/
        /*  median calculation */ 
        if(obj->m_middleValueP!=NULL)
        {
            /* by default the number of medians is 2 
               because many cases below have the number of the data that is even */
            obj->m_numMedian =2;
            if(obj->m_numMemInMax==obj->m_numMemInMin)
            {
                obj->m_medianValueInDim =*(obj->m_middleValueP);
                obj->m_lastMedianValue =*(obj->m_middleValueP);
                /* the number of the data is odd */
                 obj->m_numMedian =1;
            }
            else if(obj->m_numMemInMax>obj->m_numMemInMin)
            {
                node = getNodeMinEleSdv(&(obj->m_maxHeap),obj->m_maxHeap.root); 
                tempD = *((double**)obj->m_maxHeap.getKey(node));
                obj->m_medianValueInDim =*(obj->m_middleValueP);
                obj->m_medianVal2 =*tempD;
            }
            else if(obj->m_numMemInMax<obj->m_numMemInMin)
            {
                node = getNodeMaxEleSdv(&(obj->m_minHeap),obj->m_minHeap.root); 
                tempD = *((double**)obj->m_minHeap.getKey(node));
                obj->m_medianValueInDim =*(obj->m_middleValueP);
                obj->m_medianVal2 =*tempD;
            }
            else
            {
                /* do nothing */
            } 
            if(obj->m_numMedian==2)
            {/*statistic option for mode and median
                         0 is mean them (default value)
                         1 is random choose*/
                if(obj->m_sdOpt ==0)
                {
                    obj->m_lastMedianValue = (obj->m_medianValueInDim +obj->m_medianVal2)/2.0;
                }
                else if(obj->m_sdOpt ==1) /* random*/
                {
                    randVal =(clock()+rand() )% 10 + 1;
                    if(randVal%2 ==0)
                    { 
                        obj->m_lastMedianValue =obj->m_medianValueInDim;
                    }
                    else
                    {
                        obj->m_lastMedianValue =obj->m_medianVal2;
                    }
                    
                    printf("randVal_cp2 : %d ,so val :%f\n",randVal,obj->m_lastMedianValue);
                }
            }
            else
            {
                /* do nothing */
            }
            /* find avial of median  value*/
            findNeighbourOfStatisticValInAvlT4EleSdv2(&(obj->m_possibleValTree),obj->m_maxValueInDim,obj->m_minValueInDim,obj->m_lastMedianValue,&(obj->m_medianValueAvailValue));
        }
        else
        {
            /* do nothing */
        }
        /*  mode calculation */
        if(obj->m_numSameCount ==1)
        {
            obj->m_modValueInDim =*((double*)getDataPVoidList(&(obj->m_hignFreqValList),0));
            
        }
        else  
        {
            /*statistic option for mode and median
             0 is mean them (default value)
             1 is random choose*/
            if(obj->m_sdOpt ==0)
            {
                if(obj->m_numSameCount ==0)
                {
                    obj->m_modValueInDim =obj->m_meanValueInDim;
                }
                else
                {
                    num =obj->m_numSameCount;
                    obj->m_modValueInDim=0;
                    if(num<=countPVoidList(&(obj->m_hignFreqValList)))
                    {
                        for(index=0;index<num;index++)
                        {
                            obj->m_modValueInDim +=*((double*)getDataPVoidList(&(obj->m_hignFreqValList),index));
                        }
                        obj->m_modValueInDim = obj->m_modValueInDim/(float)num;
                    }
                    else
                    {
                        printf("Error m_numSameCount is greater than the number of elements in hignFreqValList, ln:%d\n",__LINE__);
                    }
                }
            }
            else
            {
                if(obj->m_numSameCount >1)
                { 
                    num =obj->m_numSameCount;
                    randVal =(clock()+rand() )% num;
                    obj->m_modValueInDim  =*((double*)getDataPVoidList(&(obj->m_hignFreqValList),randVal));
                    printf("Mode, rand : %d , value : %f\n",randVal,obj->m_modValueInDim);
                }
                else if(obj->m_numSameCount ==0)  
                {
                    if((getNumBinaryNodeOfTree(&(obj->m_maxHeap))!=0)&&(getNumBinaryNodeOfTree(&(obj->m_minHeap))!=0))
                    {
                        num =8;
                    }
                    else
                    {
                        num = 4;
                    }
                    randVal =(clock()+rand() )% num;
                    /* random some value */
                    /*  mod by 8
                        0 is max val
                        1 is min val
                        2 is mean val
                        3 is median val
                        4 is first median val (if median have 2 values ) or max val(last value) of min heap
                        5 is second median val(if median have 2 values ) or min val(first value) of max heap
                        6 is first value of min heap
                        7 is last value of max heap
                    */
                    switch(randVal)
                    {
                        case 0:
                            obj->m_modValueInDim =obj->m_maxValueInDim;
                        break;
                        case 1:
                            obj->m_modValueInDim =obj->m_minValueInDim;
                        break;
                        case 2:
                            obj->m_modValueInDim =obj->m_meanValueInDim;
                        break;
                        case 3:
                            obj->m_modValueInDim =obj->m_lastMedianValue;
                        break;
                        case 4:
                            if(obj->m_numMedian==2)
                            {
                                obj->m_modValueInDim =obj->m_medianValueInDim;
                            }
                            else
                            {
                                node = getNodeMaxEleSdv(&(obj->m_minHeap),obj->m_minHeap.root); 
                                tempD = *((double**)obj->m_minHeap.getKey(node));
                                obj->m_modValueInDim =*tempD;
                            }
                        break;
                        case 5:
                            if(obj->m_numMedian==2)
                            {
                                obj->m_modValueInDim =obj->m_medianVal2;
                            }
                            else
                            {
                                node = getNodeMinEleSdv(&(obj->m_maxHeap),obj->m_maxHeap.root); 
                                tempD = *((double**)obj->m_maxHeap.getKey(node));
                                obj->m_modValueInDim =*tempD;
                            }
                        break;
                        case 6:
                                node = getNodeMinEleSdv(&(obj->m_minHeap),obj->m_minHeap.root); 
                                tempD = *((double**)obj->m_minHeap.getKey(node));
                                obj->m_modValueInDim =*tempD;
                        break;
                        case 7:
                                node = getNodeMaxEleSdv(&(obj->m_maxHeap),obj->m_maxHeap.root); 
                                tempD = *((double**)obj->m_maxHeap.getKey(node));
                                obj->m_modValueInDim =*tempD;
                        break;
                    }
                    printf("Mode random :%d --  %f \n",randVal,obj->m_modValueInDim);
                }
            }
        }
        /* find avial of median  value*/
        findNeighbourOfStatisticValInAvlT4EleSdv2(&(obj->m_possibleValTree),obj->m_maxValueInDim,obj->m_minValueInDim,obj->m_modValueInDim,&(obj->m_modValueAvailValue));
        /*printf("-114-Median :%f , avialVal:%f \n",obj->m_modValueInDim,obj->m_modValueAvailValue);*/
    }
    else
    {
        /* do nothing */
    }
}
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
double getValueOfEleSdv(elemSdv *obj,char type)
{
    double ret =0.0;
    if(obj!=NULL)
    {
        switch(type)
        {
            case 0:
                if(obj->m_avail==1)
                {
                    ret = obj->m_meanValueAvailValue;
                }
                else
                {
                    ret = obj->m_meanValueInDim;
                }
                break;
                case 1:
                if(obj->m_avail==1)
                {
                    ret = obj->m_medianValueAvailValue;
                }
                else
                {
                    ret = obj->m_lastMedianValue;
                }
                break;
                case 2:
                if(obj->m_avail==1)
                {
                    ret = obj->m_modValueAvailValue;
                }
                else
                {
                    ret = obj->m_modValueInDim;
                }
                break;
                case 3:
                if(obj->m_avail==1)
                {
                    ret = obj->m_modValueAvailValue;
                }
                else
                {
                    ret = obj->m_modValueInDim;
                }
                break;
                case 4:
                if(obj->m_avail==1)
                {
                    ret = obj->m_modValueAvailValue;
                }
                else
                {
                    ret = obj->m_modValueInDim;
                }
                break;
                case 5:
                ret = obj->m_maxValueInDim;
                break;
                case 6:
                ret = obj->m_minValueInDim;
                break;
                
                
        }
    }
    else
    {
        /* do nothing */
    }
    return ret;
}


void constructGroupVariableSdv(groupVariableSdv *obj,int numDim,int  numOutDim,int numCls,int inputType)
{
    int index=0;
    int index2=0;
    double **ppd=NULL;
    if(obj !=NULL)
    {
        obj->m_variables =NULL;
        obj->m_clsVal =NULL;
        obj->m_inputType =inputType;
        obj->m_numOutDim =0.0;
        obj->m_numDim =0.0;
        obj->m_numClass =0.0; 
        if((numDim>0)&&(numCls>0)&&(numOutDim>0))
        {
            obj->m_numDim  = numDim;
            obj->m_numOutDim  = numOutDim;
            obj->m_numClass =numCls;
            obj->m_variables = (struct elemSdv**)malloc(sizeof(struct elemSdv*)*numCls);obj->countMallo[14]++;
            if(numOutDim ==1)
            {
                obj->m_clsVal = (void*)malloc(sizeof(double)*numCls);obj->countMallo[15]++;
            }
            else
            {
                ppd = (double**)malloc(sizeof(double*)*numCls);obj->countMallo[16]++;
            }
            for(index=0;index<numCls;index++)
            {
                obj->m_variables[index] =  (struct elemSdv*)malloc(sizeof(struct elemSdv)*numDim);obj->countMallo[17]++;
                if(numOutDim ==1)
                {
                    ((double*)obj->m_clsVal)[index] = 0.0;
                }
                else
                {
                    ppd[index] = (double*)malloc(sizeof(double)*numDim);obj->countMallo[18]++;
                }
                for(index2=0;index2<numDim;index2++)
                {
                    constructEleSdv(&(obj->m_variables[index][index2]));
                    if(numOutDim>1)
                    {
                        ppd[index][index2] = 0.0;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
            }
            if(numOutDim>1)
            {
                obj->m_clsVal = (void*)ppd;
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
void summarizeGroupVariableSdv(groupVariableSdv *obj)
{
    int index=0;
    int index2=0;
    if(obj !=NULL)
    { 
        for(index=0;index<obj->m_numClass;index++)
        { 
            for(index2=0;index2<obj->m_numDim;index2++)
            { 
                summarizeEleSdv(&(obj->m_variables[index][index2]));
            }
        }
    }
    else
    {
        /* do nothing */
    }
}
void setSdOptionGroupVariableSdv(groupVariableSdv *obj,int index,char val)
{
    int index2=0;
    int numClass;
    if((obj!=NULL)&&(index>=0))
    {
        if(obj->m_numDim > index)
        {
            numClass = obj->m_numClass;
            for(index2=0;index2<numClass;index2++)
            {
                setSdOptionEleSdv(&(obj->m_variables[index2][index]),val);
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
void printGroupVariableSdv(groupVariableSdv *obj)
{
    int index=0;
    int index2=0;
    if(obj !=NULL)
    { 
        for(index=0;index<obj->m_numClass;index++)
        {
            printf("Class : %d \n",index);
            for(index2=0;index2<obj->m_numDim;index2++)
            {
                printf("  ele : %d ",index2);
                printEleSdv(&(obj->m_variables[index][index2]));
            }
        }
    }
}
double getValueFromGrpValSdv(groupVariableSdv *obj,int whichCls,int indexDim,char type,char *isOk)
{
    double dTemp =0.0;
    if((obj!=NULL)&&(isOk!=NULL))
    {
        if((obj->m_variables!=NULL)&&(obj->m_numClass >whichCls)&&(obj->m_numDim>indexDim)&&(type>-1)&&(type<7))
        {
            *isOk=1;
            dTemp = getValueOfEleSdv(&(obj->m_variables[whichCls][indexDim]),type);
        }
        else
        {
            *isOk =0;
            /* do nothing */
        }
    }
    else
    {
        /* do nothing */
    }
    return dTemp;
}
void destructGroupVariableSdv(groupVariableSdv *obj)
{
    int index=0;
    int index2=0;
    int num=0;
    int num2=0;
    double **ppd=NULL;
    if(obj !=NULL)
    {
        if(obj->m_variables !=NULL)
        {
            num = obj->m_numClass;
            num2 = obj->m_numDim;
            for(index=0;index<num;index++)
            {
                for(index2=0;index2<num2;index2++)
                {
                    destructEleSdv(&(obj->m_variables[index][index2]));
                }
                free(obj->m_variables[index]);
            }
            free(obj->m_variables);
            obj->m_variables = NULL;
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_clsVal !=NULL)
        { 
            if(obj->m_numOutDim ==1)
            {
                free(obj->m_clsVal);
                obj->m_clsVal = NULL;
            }
            else
            {
                ppd = (double**)(obj->m_clsVal);
                for(index=0;index<num;index++)
                {
                    free(ppd[index]);
                }
                free(obj->m_clsVal);
                obj->m_clsVal = NULL;
            }
                
        }
        else
        {
            /* do nothing */
        } 
        obj->m_numDim =0.0;
        obj->m_numClass =0.0; 
        obj->m_numOutDim =0.0; 
    }
    else
    {
        /* do nothing */
    }
}
void keepDat2GroupVariableSdv(groupVariableSdv *obj,void *val,int indexCls)
{
    int ret = (obj!=NULL)&&(val!=NULL)&&(indexCls>-1);
    int index=0;
    int num =0;
    double *vd =NULL;
    if(ret==1)
    {
        if(obj->m_inputType == 0)
        {
            vd = (((vector_double*)val)->data);
        }
        else
        {
            vd = (((struct mat2Ele*)val)->m_startP);
        }
        if(indexCls < obj->m_numClass)
        {
            num = obj->m_numDim;
            for(index=0;index<num;index++)
            {
                keepDat2EleSdv(&(obj->m_variables[indexCls][index]),&vd[index]);
            }
        }
        else
        {
            printf("Error --- index  class is exeed ----file: %s   line :%d\n",__FILE__,__LINE__);
        }
    }
    else
    {
        /* do nothing */
    }
}
int fixMis2ASampleVarSdv(groupVariableSdv *obj,int whichCls,void *pList,int indexEle,vector_double **valVdoub)
{
    char res = (obj!=NULL)&&(pList!=NULL)&&(indexEle >=0)&&(valVdoub!=NULL);
    struct incompAndDiscData *incompDatTemp=NULL;
    int num=0;
    int index2=0;
    int indexDim=0;
    char statusSdv=0;
    vector_double *vDoub =NULL;
    if(res==1)
    {
        incompDatTemp = (incompAndDiscData*)getDataPVoidList(pList,indexEle); 
    }
    else
    {
        /* do nothing */
    }
    if(incompDatTemp!=NULL)
    {
        vDoub = (vector_double*)incompDatTemp->addr;
        *valVdoub = vDoub;
        num = getSizeArrOfStatDataLogEleArr(&(incompDatTemp->statDat));
        for(index2=0;index2<num;index2++)
        {
            indexDim = incompDatTemp->statDat.m_data[index2].indexDim;
            statusSdv = incompDatTemp->statDat.m_data[index2].typeStatus;
            /* print temp : 20 May 2016*/
           /* printf("index :%d status : %d  \n",indexDim,statusSdv);*/
            if(vDoub ==NULL)
            {
                res =0;
                index2=num;
                printf("Vector Double pointer is NULL ");
            }
            else if((indexDim <0)||(indexDim> vDoub->lenght))
            {
                printf("indexDim is invalid ");
                print_vector_double(vDoub,6);
                res =0;
                index2=num;
            }
            else if(vDoub->data[indexDim] ==-1)
            {
                /* replace new value*/
                vDoub->data[indexDim] = getValueFromGrpValSdv(obj,whichCls,indexDim,statusSdv,&res);
              /*  printf(" okoko %f \n", vDoub->data[indexDim]);*/
                if(res==0)
                {
                    printf("Cannot fix this missing (indexDim):%d ",indexDim);
                    index2=num;
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
        if(res==0)
        {
            printf("at fixMis2ASampleVarSdv, file:%s , ln:%d\n",__FILE__,__LINE__);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Null pointer in P list, at fixMis2ASampleVarSdv fn, File:%s , ln : %d\n",__FILE__,__LINE__);
    }
    return res;
}
int fixMis2ASampleVarSdv_NdFixNBin(groupVariableSdv *obj,int whichCls,void *pList,int indexEle,void **valVdoub)
{
    char res = (obj!=NULL)&&(pList!=NULL)&&(indexEle >=0)&&(valVdoub!=NULL);
    struct incompAndDiscData *incompDatTemp=NULL;
    int num=0;
    int index2=0;
    int indexDim=0;
    char statusSdv=0;
    struct mat2Ele *vDoub =NULL;
    if(res==1)
    {
        incompDatTemp = (incompAndDiscData*)getDataPVoidList(pList,indexEle); 
    }
    else
    {
        /* do nothing */
    }
    if(incompDatTemp!=NULL)
    {
        vDoub = (struct mat2Ele*)incompDatTemp->addr;
        *valVdoub = vDoub;
        num = getSizeArrOfStatDataLogEleArr(&(incompDatTemp->statDat));
        for(index2=0;index2<num;index2++)
        {
            indexDim = incompDatTemp->statDat.m_data[index2].indexDim;
            statusSdv = incompDatTemp->statDat.m_data[index2].typeStatus;
            /* print temp : 20 May 2016*/
           /* printf("index :%d status : %d  \n",indexDim,statusSdv);*/
            if(vDoub ==NULL)
            {
                res =0;
                index2=num;
                printf("Vector Double pointer is NULL ");
            }
            else if((indexDim <0)||(indexDim> vDoub->m_length))
            {
                printf("indexDim is invalid ");
                /*print_vector_double(vDoub,6);*/
                res =0;
                index2=num;
            }
            else if(((double*)(vDoub->m_startP))[indexDim] ==-1)
            {
                /* replace new value*/
                ((double*)(vDoub->m_startP))[indexDim] = getValueFromGrpValSdv(obj,whichCls,indexDim,statusSdv,&res);
              /*  printf(" okoko %f \n", vDoub->data[indexDim]);*/
                if(res==0)
                {
                    printf("Cannot fix this missing (indexDim):%d ",indexDim);
                    index2=num;
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
        if(res==0)
        {
            printf("at fixMis2ASampleVarSdv, file:%s , ln:%d\n",__FILE__,__LINE__);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Null pointer in P list, at fixMis2ASampleVarSdv fn, File:%s , ln : %d\n",__FILE__,__LINE__);
    }
    return res;
}
/* #11e  statistic value  method */

/* #12  data4FindMinMaxValInT method*/
void constructorData4FindMinMaxValInT(data4FindMinMaxValInT *obj)
{
    if(obj!=NULL)
    {
        obj->m_val=0;
        obj->m_max=0;
        obj->m_min=0;
    }
    else
    {
        /* do nothing */
    }
}

void destructorData4FindMinMaxValInT(data4FindMinMaxValInT *obj)
{
    if(obj!=NULL)
    {
        obj->m_val=0;
        obj->m_max=0;
        obj->m_min=0;
    }
    else
    {
        /* do nothing */
    }
}

double getMaxInData4FindMinMaxValInT(data4FindMinMaxValInT *obj)
{
    double val = 0.0;
    if(obj!=NULL)
    {
        val = obj->m_max;
    }
    else
    {
        /* do nothing */
    }
    return val;
}
void setMaxInData4FindMinMaxValInT(data4FindMinMaxValInT *obj,double max)
{
    if(obj!=NULL)
    {
        obj->m_max =max;
    }
    else
    {
        /* do nothing */
    }
}
void setValInData4FindMinMaxValInT(data4FindMinMaxValInT *obj,double val)
{
    if(obj!=NULL)
    {
        obj->m_val =val;
    }
    else
    {
        /* do nothing */
    }
}
double getMinInData4FindMinMaxValInT(data4FindMinMaxValInT *obj)
{
    double val = 0.0;
    if(obj!=NULL)
    {
        val = obj->m_min;
    }
    else
    {
        /* do nothing */
    }
    return val;
}
void setMinInData4FindMinMaxValInT(data4FindMinMaxValInT *obj,double min)
{
    if(obj!=NULL)
    {
        obj->m_min =min;
    }
    else
    {
        /* do nothing */
    }
}
/* #12e  data4FindMinMaxValInT method*/


/* not yet */ 
 
void printStatisDataLog(statisDataLog* statisDataLogObj,matrix_double* dataPrint)
{
 
}