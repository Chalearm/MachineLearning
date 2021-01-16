#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avlTree.h"
#include "simMat2.h"

#define NODENUM 25
#define COLNUM 5
#define FIXARRNODE_BUILD_IN  2
#define FIXARRNODE_NOT_BUILD_IN 3
const unsigned int TREE_TYPE =  FIXARRNODE_BUILD_IN;
const unsigned int ARRSIZE = 28;

#define NUMPARAMS 10 
const double MINVAL = -2.33234;
const double MAXVAL = 1234.43242;

void clearDoublePointerArr(void ***obj,int num);
void printDouble(double *a,int numLoop);
void swapDoublePointer(double *a,double *b,int numLoop);
void initiInputDouble(double ***dat,int numLoop,int numCol);
int compVDouble4AVLTFixedArr(const void* a,const void *b);
int compVDouble4AVLTFixedArrBIn(const void* a,const void *b);
void setRandDat(double *dat,int num,double max,double min);
void setDat(double *ret,const void *lsh,int numLoop);
double randomVal(double max,double min);
void setRandomDat(void **arrMt,int numLoop,int numEle,double max,double min);
void setRandomDatForMat22D(mat2_2d *obj,int numLoop,int numEle,double max,double min);
void setDat4Mat22D(binaryTree *objb,mat2_2d *input,int numDat,int numEle);

/* for built-in case */
void setRandomDatForMat22D_BI(mat2_2d *obj,binaryTree *objb,int numLoop,int numEle,double max,double min);
void setDat4Mat22D_BI(binaryTree *objb,const void *data,int numDat,int numEle);

void initialNobuiltIn(void *obj);
void operationNobuiltIn(void *obj);
void deleteKeyInTNobuiltIn(void *obj);
void displayNobuiltIn(void *obj);
void destructorNobuiltIn(void *obj);

void initialBuiltIn(void *obj);
void operationBuiltIn(void *obj);
void deleteKeyInTBuiltIn(void *obj);
void displayBuildIn(void *obj);
void destructorBuiltIn(void *obj);

struct processFn
{
    void *m_parameter[NUMPARAMS];
    void (*mInitial)(void*);
    void (*mOperation1)(void*);
    void (*mOperation2)(void*);
    void (*mDisplay)(void*);
    void (*destructor)(void *);
};
void constructPFn(struct processFn *obj);
void getParamater(struct processFn *obj,int index,void *para);
void makeEmptyPFn(struct processFn *obj);

/* main process */
int main(int argc,char **argv)
{
    srand(time(NULL));
    struct processFn pFn;
    unsigned int tType =TREE_TYPE;
    double **input=NULL;
    mat2_2d mat2d2;
    mat2_2d vectStorage;
    binaryTree avlTFixArr;
    double *f=NULL;
    
    printf("Hello World Tree_type :%s\n",(tType==FIXARRNODE_BUILD_IN)?"Built-in":"Not BIn");
    constructPFn(&pFn);
    getParamater(&pFn,0,(void*)&tType);
    getParamater(&pFn,1,(void*)&mat2d2);
    getParamater(&pFn,2,(void*)&vectStorage);
    getParamater(&pFn,3,(void*)&avlTFixArr);
    getParamater(&pFn,5,(void*)&input);
    getParamater(&pFn,6,(void*)&f);
    /* initial */
    pFn.mInitial(&pFn);
    /* operation */
    pFn.mOperation1(&pFn);
    
        
    pFn.mDisplay(&pFn);
    printf("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCcc----\n");
    
    /*delete a key */
    pFn.mOperation2(&pFn);
    
    pFn.mDisplay(&pFn);
    
    /* destructor */
    pFn.destructor(&pFn);
    
    
    makeEmptyPFn(&pFn);
    return 0;
}

void printDouble(double *a,int numLoop)
{
    int index =0;
    printf("[");
    for(index=0;index<numLoop;index++)
    {
        printf("%f ",a[index]);
    }
    printf("]");
}
void initiInputDouble(double ***dat,int numLoop,int numCol)
{
    int index=0;
    int index2=0;
    int index3=0;
    double **dd=NULL;
    int num =0;
    int randLoop=NODENUM;
    dd= malloc(sizeof(double*)*numLoop);
    if(dd!=NULL)
    {
        for(index=0;index<numLoop;index++)
        {
            dd[index] = malloc(sizeof(double)*numCol); 
            if(dd[index]!=NULL)
            {
                dd[index][0] = index;
                for(index2=1;index2<numCol;index2++)
                {
                    dd[index][index2] = randomVal(100,-99.2432329);
                }
            }
            else
            {
                /* do nothing */
            }
        }
        num = numLoop-1;
        for(index=0;index<randLoop;index++)
        {
            index2=randomVal(num,0);
            index3=randomVal(num,0);
            if(index3 ==index2)
            {
                index3 = (index3+1)%numLoop;
            }
            else
            {
                /* do nothing */
            }
            swapDoublePointer(dd[index2],dd[index3],numCol);
        }
        *dat = dd;
    }
    else
    {
        /* do nothing */
    }
}

void swapDoublePointer(double *a,double *b,int numLoop)
{
    int index=0;
    double temp =0.0;
    if((a!=NULL)&&(b!=NULL)&&(numLoop>0))
    {
        for(index=0;index<numLoop;index++)
        {
            temp = a[index];
            a[index] = b[index];
            b[index] = temp;
        }
    }
    else
    {
        /* do nothing */
    }
}
double randomVal(double max,double min)
{
    if((int)(max-min)== 0)
    {
        return min;
    }
    else
    {
        return min + rand()%(int)(max-min);
    }
}

void setRandDat(double *dat,int num,double max,double min)
{
    int index=0;
    for(index=0;index<num;index++)
    {
        dat[index] = randomVal(max,min); 
        printf("%f ",dat[index]);
    }
}
void setDat(double *ret,const void *lsh,int numLoop)
{
    int index=0;
    const double *dat = (const double*)lsh; 
    for(index=0;index<numLoop;index++)
    {
        ret[index] = dat[index];
       /* printf("%f ",dat[index]); */
    }
}
void setDat4Mat22D(binaryTree *objb,mat2_2d *input,int numDat,int numEle)
{
    int index=0;
    unsigned int type =0;
    mat2_2d *obj=NULL;
    struct mat2Ele *m2El =NULL;
    if(objb !=NULL)
    { 
        obj = objb->parameter3;
        type = getTypeMt22d(obj);
        if(type ==4)
        {
            resetReaderDatMt22d(input);
            for(index=0;index<numDat;index++)
            {
                m2El = (struct mat2Ele*)readDatNextMt22d(input);
                if(m2El !=NULL)
                {
                 /*   printf("Pass Node : %p \n",nodeFArr);*/
                    objb->insertFn(objb,&(m2El));
                 /*   printf("\ni:%d ",index);
                    printHeadFixedArrNode(nodeFArr);
                    printf("\n");*/
                }
                else
                {
                    index = numDat;
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
void setRandomDatForMat22D(mat2_2d *obj,int numLoop,int numEle,double max,double min)
{
    int index=0;
    unsigned int type =0;
    double *dV=NULL;
    struct mat2Ele *m2El =NULL;
    if(obj !=NULL)
    { 
        type = getTypeMt22d(obj);
        if(type ==2)
        {
            for(index=0;index<numLoop;index++)
            {
                m2El = (struct mat2Ele*)getDatNextMt22d((void*)obj);
                if(m2El !=NULL)
                {
                    dV = (double*)(m2El->m_startP);/*
                    printf("&m2El:%p, &mPoin:%p Val(%p), &len:%p val(%u) &Str:%p ",m2El,&(m2El->m_pointRef),m2El->m_pointRef,&(m2El->m_length),m2El->m_length,(m2El->m_startP));
                    */setRandDat(dV,numEle,max,min);
                     printf("\n"); 
                }
                else
                {
                    index = numLoop;
                }
            }
        }
        else if(type ==3)
        {
            /* do nothing */
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


void setDat4Mat22D_BI(binaryTree *objb,const void *data,int numDat,int numEle)
{
    int index=0;
    unsigned int type =0;
    double *dV=NULL;
    const double **dd1= (const double**)data;
    struct mat2Ele *m2El =NULL;
    mat2_2d *obj=NULL;
    struct nodeFixedArr *nodeFArr =NULL;
    if(objb !=NULL)
    { 
printf("sss : %p, dd1:%p, %p \n",data,dd1,dd1[0]);
        obj = objb->parameter3;
        type = getTypeMt22d(obj);
        if(type ==2)
        {
            for(index=0;index<numDat;index++)
            {
                m2El = (struct mat2Ele*)getDatNextMt22d((void*)obj);
                if(m2El !=NULL)
                {
                    dV = (double*)(m2El->m_startP);/*
                    printf("&m2El:%p, &mPoin:%p Val(%p), &len:%p val(%u) &Str:%p ",m2El,&(m2El->m_pointRef),m2El->m_pointRef,&(m2El->m_length),m2El->m_length,(m2El->m_startP));
                    */setDat(dV,dd1[index],numEle);
                    /*printf("\n");*/
                }
                else
                {
                    index = numDat;
                }
            }
        }
        else if(type ==3)
        {
            for(index=0;index<numDat;index++)
            {
                nodeFArr = (struct nodeFixedArr*)getDatNextMt22d((void*)obj);
                if(nodeFArr !=NULL)
                {
                    dV = (double*)(nodeFArr->m_dat); 
                setDat(dV,dd1[index],numEle);
                 /*   printf("Pass Node : %p \n",nodeFArr);*/
                    objb->insertFn(objb,&(nodeFArr));
                 /*   printf("\ni:%d ",index);
                    printHeadFixedArrNode(nodeFArr);
                    printf("\n");*/
                }
                else
                {
                    index = numDat;
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
void setRandomDatForMat22D_BI(mat2_2d *obj,binaryTree *objb,int numLoop,int numEle,double max,double min)
{
    int index=0;
    unsigned int type =0;
    double *dV=NULL;
    struct mat2Ele *m2El =NULL;
    struct nodeFixedArr *nodeFArr =NULL;
    if(obj !=NULL)
    { 
        type = getTypeMt22d(obj);
        if(type ==2)
        {
            for(index=0;index<numLoop;index++)
            {
                m2El = (struct mat2Ele*)getDatNextMt22d((void*)obj);
                if(m2El !=NULL)
                {
                    dV = (double*)(m2El->m_startP);/*
                    printf("&m2El:%p, &mPoin:%p Val(%p), &len:%p val(%u) &Str:%p ",m2El,&(m2El->m_pointRef),m2El->m_pointRef,&(m2El->m_length),m2El->m_length,(m2El->m_startP));
                    */setRandDat(dV,numEle,max,min);
                    /*printf("\n");*/
                }
                else
                {
                    index = numLoop;
                }
            }
        }
        else if(type ==3)
        {
            for(index=0;index<numLoop;index++)
            {
                nodeFArr = (struct nodeFixedArr*)getDatNextMt22d((void*)obj);
                if(nodeFArr !=NULL)
                {
                    dV = (double*)(nodeFArr->m_dat);
                    setRandDat(dV,numEle,max,min); 
                 /*   printf("Pass Node : %p \n",nodeFArr);*/
                    objb->insertFn(objb,&(nodeFArr));
                 /*   printf("\ni:%d ",index);
                    printHeadFixedArrNode(nodeFArr);
                    printf("\n");*/
                }
                else
                {
                    index = numLoop;
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
void setRandomDat(void **arrMt,int numLoop,int numEle,double max,double min)
{ 
    int index2=0;
    double *dV=NULL;
    struct mat2Ele *m2El =NULL;
    if(arrMt !=NULL)
    {
        m2El = (struct mat2Ele*)arrMt[0];
     /* printf("arrMt:%p m2El:%p\n",arrMt,m2El); */
        for(index2=0;index2<numLoop;index2++)
        {
            m2El = (struct mat2Ele*)arrMt[index2];
            dV = (double*)(m2El->m_startP);
      /* printf("&m2El:%p, &mPoin:%p Val(%p), &len:%p val(%u) &Str:%p ",m2El,&(m2El->m_pointRef),m2El->m_pointRef,&(m2El->m_length),m2El->m_length,(m2El->m_startP));
        */    setRandDat(dV,numEle,max,min);
          /*  printf("\n");*/
        }
    }
    else
    {
        /* do nothing */
    }
}
 
int compVDouble4AVLTFixedArr(const void* a,const void *b)
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
        printf("Failed to compare \n");
        /* do nothing */
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
        res =EQUAL_DEFINE;
        dV1 = (double*)((*va)->m_startP);
        dV2 = (double*)((*vb)->m_startP);
        for(index=0;index<num;index++)
        {
           printf("[%f %f] \n",dV1[index],dV2[index]);
           if(dV1[index]> dV2[index])
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
        printf("----- a->lt:%d, b->lt:%d \n",(*va)->m_length,(*vb)->m_length);
        if((res ==EQUAL_DEFINE)&&((*va)->m_length== (*vb)->m_length))
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
        printf("a:%p, b:%p\n",*((struct mat2Ele**)a),*((struct mat2Ele**)b));
        printf("cannot compare ln:%d :fl:%s\n",__LINE__,__FILE__);
        /* do nothing */
    }
    return res;
}

int compVDouble4AVLTFixedArrBIn(const void* a,const void *b)
{ 
    int res =UN_DEFINE;
    int index =0;
    int num =0;
    double *dV1 =NULL;
    double *dV2 =NULL;
    struct nodeFixedArr **va=NULL,**vb=NULL;
    if((a==NULL)||(b==NULL))
    {
        printf("Failed to compare \n");
        /* do nothing */
    }
    else if((*((struct nodeFixedArr**)a)!=NULL)&&(*((struct nodeFixedArr**)b)!=NULL))
    {
        va = ((struct nodeFixedArr**)a);
        vb = ((struct nodeFixedArr**)b);
        if((*va)->m_length > (*vb)->m_length)
        {
            num = (*vb)->m_length;
        }
        else
        {
            num =(*va)->m_length;
        }
        res =EQUAL_DEFINE;
        dV1 = (double*)((*va)->m_dat);
        dV2 = (double*)((*vb)->m_dat);
        for(index=0;index<num;index++)
        {
           /* printf("[%f %f] ",dV1[index],dV2[index]);
           */if(dV1[index]> dV2[index])
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
        printf("a:%p, b:%p\n",*((struct nodeFixedArr**)a),*((struct nodeFixedArr**)b));
        printf("cannot compare ln:%d :fl:%s\n",__LINE__,__FILE__);
        /* do nothing */
    }
    return res;
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

/*

struct processFn
{
    void *m_parameter[NUMPARAMS];
    void (*mInitial)(void*);
    void (*mOperation1)(void*);
    void (*mOperation2)(void*);
    void (*destructor)(void *);
};

*/
void constructPFn(struct processFn *obj)
{
    int index=0;
    if(obj!=NULL)
    {
        for(index = 0;index < NUMPARAMS;index++)
        {
            obj->m_parameter[index] = NULL;
        }
        obj->mInitial = NULL;
        obj->mOperation1 = NULL;
        obj->mOperation2 = NULL;
        obj->mDisplay = NULL;
        obj->destructor = NULL;
    }
    else
    {
        /* do nothing */
    }
}
void getParamater(struct processFn *obj,int index,void *para)
{
    unsigned int uiTemp = 0;
    if((obj!=NULL)&&(index<NUMPARAMS)&&(para!=NULL))
    {
        obj->m_parameter[index] = para;
        
        if(index == 0) /* type value */
        {
            uiTemp = *((unsigned int*)para);
            if(uiTemp == FIXARRNODE_BUILD_IN)
            {
                obj->mInitial =&initialBuiltIn;
                obj->mOperation1 =&operationBuiltIn;
                obj->mOperation2 =&deleteKeyInTBuiltIn;
                obj->mDisplay =&displayBuildIn;
                obj->destructor =&destructorBuiltIn;
            }
            else if(uiTemp == FIXARRNODE_NOT_BUILD_IN)
            {
                obj->mInitial =&initialNobuiltIn;
                obj->mOperation1 =&operationNobuiltIn;
                obj->mOperation2 =&deleteKeyInTNobuiltIn;
                obj->mDisplay =&displayNobuiltIn;
                obj->destructor =&destructorNobuiltIn;
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
void makeEmptyPFn(struct processFn *obj)
{
    int index=0;
    if(obj!=NULL)
    {
        for(index = 0;index < NUMPARAMS;index++)
        {
            obj->m_parameter[index] = NULL;
        }
        obj->mInitial = NULL;
        obj->mOperation1 = NULL;
        obj->mOperation2 = NULL;
        obj->mDisplay = NULL;
        obj->destructor = NULL;
    }
    else
    {
        /* do nothing */
    }
}

void initialNobuiltIn(void *obj)
{
    mat2_2d *mat2d2 = NULL;
    mat2_2d *vectStorage = NULL;
    void *avlTFixArr = NULL;
    struct processFn *objP =NULL;
    if(obj!=NULL)
    {
        objP =(struct processFn*)obj;
        mat2d2 = (mat2_2d*)(objP->m_parameter[1]);
        vectStorage = (mat2_2d*)(objP->m_parameter[2]);
        avlTFixArr =  (objP->m_parameter[3]);
                    /*    0x110 FIXED_ARR_NBIN (not build in data element)*/
        constructAvlTree(avlTFixArr,TREE_TYPE,"fixed arr no bin",11,5);
        setDelKeyAndDelDataAndCompFnForAvlTree(avlTFixArr,NULL,NULL,compVDouble4AVLTFixedArr); 
    
        /* initial */
        initiValInMt22d(mat2d2);
        initiValInMt22d(vectStorage);
        *mat2d2 = newMt22d(ARRSIZE,0,0,4);
        *vectStorage = newMt22d(ARRSIZE,COLNUM,sizeof(double),2);
        setParameterValofBinT(avlTFixArr,3,(void*)mat2d2);
    }
    else
    {
        /* do nothing */
    }
}
void operationNobuiltIn(void *obj)
{
    mat2_2d *vectStorage = NULL;
    binaryTree *avlTFixArr = NULL;
    struct processFn *objP =NULL;
    if(obj!=NULL)
    {
        objP =(struct processFn*)obj;
        vectStorage = (mat2_2d*)objP->m_parameter[2];
        avlTFixArr = (binaryTree*)objP->m_parameter[3];
        /* operation */
        setRandomDatForMat22D(vectStorage,NODENUM,COLNUM,MAXVAL,MINVAL);
        setDat4Mat22D(avlTFixArr,vectStorage,NODENUM,COLNUM);

    }
    else
    {
        /* do nothing */
    }
}

void deleteKeyInTNobuiltIn(void *obj)
{
    mat2_2d *vectStorage = NULL;
    binaryTree *avlTFixArr = NULL;
    struct processFn *objP =NULL;
    struct mat2Ele *m2Ele =NULL;
    unsigned int maxSegment=0;
    unsigned int maxOffset=0;
    unsigned int offsetChoose = 0;  
    if(obj!=NULL)
    {  
        objP =(struct processFn*)obj;
        vectStorage = (mat2_2d*)objP->m_parameter[2];
        avlTFixArr = (binaryTree*)objP->m_parameter[3];
        maxSegment=getUsedNumDatMt22d(vectStorage);
 
        if(maxSegment >0)
        {
            maxSegment =(unsigned int)randomVal((double)(maxSegment-1),0.0);
            maxOffset=getUsedOffsetNumDatMt22d(vectStorage,(unsigned int)maxSegment);
        }
        if(maxOffset >0)
        {
            offsetChoose = (unsigned int)randomVal(maxOffset-1,0);
            m2Ele = go2ReadDatMt22d(vectStorage,maxSegment,offsetChoose);
            printf("before dele :%p, lt:%d\n",m2Ele,m2Ele->m_length);
            avlTFixArr->deleteNodeByKey(avlTFixArr,&m2Ele);

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

void displayNobuiltIn(void *obj)
{    
    mat2_2d *mat2d2 = NULL;
    mat2_2d *vectStorage = NULL;
    binaryTree *avlTFixArr = NULL;
    struct processFn *objP =NULL;
    if(obj!=NULL)
    {
        objP =(struct processFn*)obj;
        mat2d2 = (mat2_2d*)objP->m_parameter[1];
        vectStorage = (mat2_2d*)objP->m_parameter[2];
        avlTFixArr = (binaryTree*)objP->m_parameter[3];

        printf("root1 : %p \n",avlTFixArr->root);
        printMt22d(mat2d2);
        printMt22d4Double(vectStorage);
        
    }
    else
    {
        /* do nothing */
    }

}

void destructorNobuiltIn(void *obj)
{
    
    mat2_2d *mat2d2 = NULL;
    mat2_2d *vectStorage = NULL;
    binaryTree *avlTFixArr = NULL;
    struct processFn *objP =NULL;
    if(obj!=NULL)
    {
        objP =(struct processFn*)obj;
        mat2d2 = (mat2_2d*)objP->m_parameter[1];
        vectStorage = (mat2_2d*)objP->m_parameter[2];
        avlTFixArr = (binaryTree*)objP->m_parameter[3];
        /* destructor */
        clearMt22d(mat2d2);
        clearMt22d(vectStorage);
        clearBinaryTree(avlTFixArr);
        
    }
    else
    {
        /* do nothing */
    }
}

void initialBuiltIn(void *obj)
{
    double ***input=NULL;
    mat2_2d *mat2d2=NULL;   
    void *avlTFixArr=NULL;
    double **f=NULL;
    struct processFn *objP =NULL;
    if(obj!=NULL)
    {
        objP =(struct processFn*)obj;
        mat2d2 = (mat2_2d*)objP->m_parameter[1];
        avlTFixArr = objP->m_parameter[3];
        input = (double***)objP->m_parameter[5];
        f = (double**)objP->m_parameter[6];
        initiInputDouble(input,NODENUM,COLNUM);
        constructAvlTree(avlTFixArr,TREE_TYPE,"fixed arr",11,5);

        
        setDelKeyAndDelDataAndCompFnForAvlTree(avlTFixArr,NULL,NULL,compVDouble4AVLTFixedArrBIn); 
        *f = (*input)[(int)randomVal(NODENUM-1,0)];
        printf("del Key :");
        printDouble(*f,COLNUM);printf("\n");

        /* initial */
        initiValInMt22d(mat2d2);
        *mat2d2 = newMt22d(ARRSIZE,COLNUM,sizeof(double),3);
        setParameterValofBinT(avlTFixArr,3,(void*)mat2d2);
    }
    else
    {
        /* do nothing */
    }
}

void operationBuiltIn(void *obj)
{
    double ***input=NULL;
    binaryTree *avlTFixArr=NULL;
    struct processFn *objP =NULL;
    if(obj!=NULL)
    {
        objP =(struct processFn*)obj;
        avlTFixArr = (binaryTree*)objP->m_parameter[3];
        input = (double***)objP->m_parameter[5];
        setDat4Mat22D_BI(avlTFixArr,(const void*)(*input),NODENUM,COLNUM);
    }
    else
    {
        /* do nothing */
    }
}
void deleteKeyInTBuiltIn(void *obj)
{
    binaryTree *avlTFixArr=NULL;
    double **f=NULL;
    struct processFn *objP =NULL;
    if(obj!=NULL)
    {        
        objP =(struct processFn*)obj;
        avlTFixArr = (binaryTree*)objP->m_parameter[3];
        f = (double**)objP->m_parameter[6];
        
        /*delete a key */
        avlTFixArr->deleteNodeByKey(avlTFixArr,*f);
    }
    else
    {
        /* do nothing */
    }
}

void displayBuildIn(void *obj)
{
    binaryTree *avlTFixArr=NULL;
    mat2_2d *mat2d2=NULL;
    struct processFn *objP =NULL;
    if(obj!=NULL)
    {           
        objP =(struct processFn*)obj;
        mat2d2 = (mat2_2d*)objP->m_parameter[1];
        avlTFixArr = (binaryTree*)objP->m_parameter[3];
        printf("root1 : %p \n",avlTFixArr->root);
        printMt22d4Double(mat2d2);
    }
    else
    {
        /* do nothing */
    }
}

void destructorBuiltIn(void *obj)
{
    double ***input=NULL;
    binaryTree *avlTFixArr=NULL;
    mat2_2d *mat2d2=NULL;
    struct processFn *objP =NULL;
    if(obj!=NULL)
    {           
        objP =(struct processFn*)obj;
        mat2d2 = (mat2_2d*)objP->m_parameter[1];
        input = (double***)objP->m_parameter[5];
        avlTFixArr = (binaryTree*)objP->m_parameter[3];    /* destructor */
        
        clearMt22d(mat2d2);
        clearBinaryTree(avlTFixArr);
        clearDoublePointerArr((void***)input,NODENUM);
    }
    else
    {
        /* do nothing */
    }
}