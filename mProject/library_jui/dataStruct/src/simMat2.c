/********************************************************************/
/*
      FILE        :   simMat2.c
      Name        :   Chalearm Saelim
      Date        :   25 October 2016
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Vector manager 

      Description :    -
      Dependency     :   We use the included library as below 
                                                #include -
      How to compile: gcc simMat2.c -o  a
      How to run        : -
      
      revision-history
      version   date          author     Description
      1.        25-10-2016    csaelim    First draft
      2.        29-10-2016    csaelim    Updated methods of struct mat2
                                         Updated header
      3         31-10-2016    csaelim    Updated methods of struct mat2
      4         13-02-2017    csaelim    Implemented methods of mat2_2d struct
      5         06-04-2017    csaelim    Implemented methods of nodeFixedArrNBIn struct (type ==4)
*/


/*******************************************************************/
#include <stdlib.h>
#include <string.h>
#include "simMat2.h" 
#include <stdio.h> 
const double g_arrNum[NUMMULTIPLER_ARR] = {1,1,2,2,2,2,2,2,2,2,2.5,2.5,2.5,4,4,6,6,10,10,100,100,1000,10000,10000,100000};
vect2* newVt2(unsigned int num,unsigned int valSize)
{
    vect2 *obj = NULL;
    if ((num>0)&&(valSize>0))
    {
        obj =  (vect2*)malloc((sizeof(unsigned int)*NUMUNSIGNED_VECT2)+(valSize*num));
    }
    else
    {
        /* do nothing */
    }
    if (obj!=NULL)
    {
        obj->m_length = num;
        obj->m_dataSize = valSize;
    }
    else
    {
        /* do nothing */
    }
    return obj;
}

unsigned int calSizeVt2(struct vect2 *obj)
{
    unsigned int size=0;
    if (obj!=NULL)
    {
        size = (sizeof(unsigned int)*NUMUNSIGNED_VECT2)+((obj->m_length)*(obj->m_dataSize));
    }    
    else
    {
        /* do nothing */
    }
    return size;
}
void clearVt2(struct vect2 **obj)
{
    if (obj!= NULL)
    {
        if (*obj !=NULL)
        {
            free(*obj);
            *obj =NULL;
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

void* getDatVt2(struct vect2 *obj)
{
    if (obj!=NULL)
    {
        return (void*)((((void*)obj)+(NUMUNSIGNED_VECT2*sizeof(unsigned int))));
    }
    else
    {
        return NULL;
    }
}

mat2* newMt2(unsigned int row,unsigned int col,unsigned int valSize,unsigned int type)
{
    struct mat2Ele *lMat2Ele =NULL;
    struct nodeFixedArr *lMat2FArrNode =NULL;
    struct nodeFixedArrNBIn *lMat2FArrNBInNode =NULL;
    struct pVoidEle2 *lMat2PVoidEle2 =NULL;
    unsigned int index =0;
    unsigned int dataRowSize = 0; 
    void *rowStart =NULL;
    mat2 *obj = NULL;
    unsigned int sizeMem =0;
    if (row > 0)
    {
        sizeMem = calAllocateSize(row,col,valSize,type);
        obj =  (mat2*)malloc(sizeMem);
    }
    else
    {
        /* do nothing */
    }
    if (obj != NULL)
    {
        memset((void*)obj,0,(size_t)sizeMem);
        dataRowSize= calRowSizeMt2(col,valSize,type);
        obj->m_type = type;
        obj->m_row = row;
        obj->m_col = col;
        obj->m_usedCount = 0;
        obj->m_currenIndex = 0;
        obj->m_dataSize = valSize;
        obj->rowP =(((void*)obj)+sizeof(struct mat2)); 
     /*   printf("obj:%p , sizeof(mat2):%u, prow:%p\n ",obj,(unsigned int)sizeof(struct mat2),obj->rowP);
      */rowStart =((((void*)obj)+sizeof(struct mat2))+ (sizeof(void*)*row));
        obj->rowP[0] =rowStart;
        if (type == 2)
        { 
            lMat2Ele = (struct mat2Ele*)rowStart;
            lMat2Ele->m_pointRef = (void*)&(obj->rowP[0]);
            lMat2Ele->m_length = col;
            lMat2Ele->m_startP = (((void*)(obj->rowP[0]))+sizeof(struct mat2Ele));
        }
        else if (type == 3)
        {
            lMat2FArrNode = (struct nodeFixedArr*)rowStart; 
            lMat2FArrNode->m_ref = (void*)&(obj->rowP[0]);
            lMat2FArrNode->m_length = col;
            lMat2FArrNode->m_dat = (((void*)(obj->rowP[0]))+sizeof(struct nodeFixedArr));
            lMat2FArrNode->m_dat2 =NULL;
            /*printf("jjjjjjjjjjjjjjjjjjjj\n");*/
        }
        else if (type == 4)
        {
            lMat2FArrNBInNode = (struct nodeFixedArrNBIn*)rowStart; 
            lMat2FArrNBInNode->m_ref = (void*)&(obj->rowP[0]);
            lMat2FArrNBInNode->m_dat = NULL;
            lMat2FArrNBInNode->m_dat2 = NULL;
            /*printf("jjjjjjjjjjjjjjjjjjjj\n");*/
        }
        else if (type == 5)
        {
            lMat2PVoidEle2 = (struct pVoidEle2*)rowStart; 
            lMat2PVoidEle2->m_ref = (void*)&(obj->rowP[0]);
            lMat2PVoidEle2->m_next = NULL;
            lMat2PVoidEle2->m_back = NULL;
            lMat2PVoidEle2->m_data = NULL;
            /*printf("jjjjjjjjjjjjjjjjjjjj\n");*/
        }
        else
        {
            /* do nothing */
        }/*
        printf("sV:%u, sVV:%u, sVVV:%u, sull:%u\n",(unsigned int)sizeof(void*),(unsigned int)sizeof(void**),(unsigned int)sizeof(void***),(unsigned int)sizeof(unsigned long long));
        printf("obj :%p &r:%p &c:%p r:%u l:%u\n",obj,&(obj->m_row),&(obj->m_col),obj->m_row,obj->m_col);
    
        printf("rowStr :%p\n",rowStart);
        printf("%u : %p\n",0,obj->rowP[0]);*/
        if (type == 2)
        {
            for(index=1;index<row;index++)
            {
                obj->rowP[index] = (obj->rowP[index-1]+dataRowSize);
               /* printf("%u : %p\n",index,obj->rowP[index]);*/
                lMat2Ele = (struct mat2Ele*)obj->rowP[index]; 
                lMat2Ele->m_pointRef =  &(obj->rowP[index]);
                lMat2Ele->m_length = col;
                if (valSize >0)
                {
                    lMat2Ele->m_startP = (((void*)(obj->rowP[index]))+sizeof(struct mat2Ele));
                }
                else
                {
                    lMat2Ele->m_startP = NULL;
                }
                /*    printf("matEl:%p , pount:%p Val(%p), len:%p strP:%p \n",lMat2Ele,&(lMat2Ele->m_pointRef),lMat2Ele->m_pointRef,&(lMat2Ele->m_length),&(lMat2Ele->m_startP));
                */
            }
        }
        else if (type == 3)
        {
            for(index=1;index<row;index++)
            {
                obj->rowP[index] = (obj->rowP[index-1]+dataRowSize);
            /*    printf("%u : %p\n",index,obj->rowP[index]);*/
                lMat2FArrNode = (struct nodeFixedArr*)obj->rowP[index]; 
                lMat2FArrNode->m_ref =  &(obj->rowP[index]);
                lMat2FArrNode->m_length = col;
                if (valSize >0)
                {
                    lMat2FArrNode->m_dat = (((void*)(obj->rowP[index]))+sizeof(struct nodeFixedArr));
                }
                else
                {
                    lMat2FArrNode->m_dat = NULL;
                }
                lMat2FArrNode->m_dat2 = NULL;
            }
        }
        else if (type == 4)
        {
            for(index=1;index<row;index++)
            {
                obj->rowP[index] = (obj->rowP[index-1]+dataRowSize);
            /*    printf("%u : %p\n",index,obj->rowP[index]);*/
                lMat2FArrNBInNode = (struct nodeFixedArrNBIn*)obj->rowP[index]; 
                lMat2FArrNBInNode->m_ref =  &(obj->rowP[index]);
                lMat2FArrNBInNode->m_dat = NULL;
                lMat2FArrNBInNode->m_dat2 = NULL;
            }
        }
        else if (type == 5)
        {
            /*printf("jjjjjjjjjjjjjjjjjjjj\n");*/
            for(index=1;index<row;index++)
            {
                obj->rowP[index] = (obj->rowP[index-1]+dataRowSize);
            /*    printf("%u : %p\n",index,obj->rowP[index]);*/
                lMat2PVoidEle2 = (struct pVoidEle2*)obj->rowP[index]; 
                lMat2PVoidEle2->m_ref =  &(obj->rowP[index]);
                lMat2PVoidEle2->m_next = NULL;
                lMat2PVoidEle2->m_back = NULL;
                lMat2PVoidEle2->m_data = NULL;
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
    return obj;
}

unsigned int calAllocateSize(unsigned int row,unsigned int col,unsigned int valSize,unsigned int type)
{
    unsigned int sizeAllocate =0;
    unsigned int rowSize =calRowSizeMt2(col,valSize,type);
    unsigned int sizeUnint =sizeof(struct mat2);
    sizeAllocate = sizeUnint+(row*(sizeof(void*)+rowSize));
    return sizeAllocate;
}
unsigned int getNumUsedMt2(struct mat2 *obj)
{
    unsigned int temp = 0;
    if (obj != NULL)
    {
        temp = obj->m_usedCount;
    }
    else
    {
        /* do nothing */
    }
    return temp;
}
unsigned int calRowSizeMt2(unsigned int col,unsigned int dataSize,unsigned int type)
{
    unsigned int rowSize =0;
    unsigned int temp =0;
    if (type ==0)
    {
        rowSize =col*dataSize;
    }
    else if (type ==1)
    {
        rowSize =(col*dataSize)+ sizeof(unsigned int);
    }
    else if (type ==2)
    {
        temp = (unsigned int)sizeof(struct mat2Ele);
        rowSize =temp+(col*dataSize);
    }
    else if (type ==3)
    {
        /* for Avl tree and using nodeFixedArr struct */
        rowSize =sizeof(struct nodeFixedArr)+(col*dataSize);
    }
    else if (type ==4)
    {
        rowSize =sizeof(struct nodeFixedArrNBIn);
    }
    else if (type ==5)
    {
        rowSize =sizeof(struct pVoidEle2);
    }
    else
    {
        /* do nothing */
    }
    return rowSize;
}
unsigned int calSizeMt2(struct mat2 *obj)
{
    unsigned int size=0;
    if (obj!=NULL)
    {
        size = calAllocateSize(obj->m_row,obj->m_col,obj->m_dataSize,obj->m_type);
    }    
    else
    {
        /* do nothing */
    }
    return size;
}
void** getDatMt2(struct mat2 *obj)
{
    if (obj!=NULL)
    {
        return obj->rowP;
    }
    else
    {
        return NULL;
    }
}
void* getDatNextMt2(void *obj)
{
    void *ret =NULL;
    if (obj!=NULL)
    {
        if (((struct mat2*)obj)->m_usedCount < ((struct mat2*)obj)->m_row)
        {
            ret = ((struct mat2*)obj)->rowP[((struct mat2*)obj)->m_usedCount++];
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
    return ret;
}

void* readDatNextMt2(struct mat2 *obj)
{
    void *ret =NULL;
    if (obj!=NULL)
    {
        if (obj->m_currenIndex < obj->m_usedCount)
        {
            ret = obj->rowP[obj->m_currenIndex++];
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
    return ret;
}

int resetDatStoreInMt2(struct mat2 *obj)
{
    int ret = (obj != NULL);
    if (ret == 1)
    {
        obj->m_usedCount   = 0;
        obj->m_currenIndex = 0;
    }
    else
    {
        printf("Error in resetDatStoreInMt2, obj is null. ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    return ret;
}


unsigned int getCurIndexMt2(struct mat2 *obj)
{    
    unsigned int ret = 0;
    if (obj != NULL)
    {
        ret = obj->m_currenIndex;
    }
    else
    {
        printf("== Error obj point is NULL, ln:%d, fl:%s \n",__LINE__,__FILE__);
    }
    return ret;
}

unsigned int isCanSetCurIdMt2(struct mat2 *obj,unsigned int dat)
{    
    unsigned int ret = 0;
    if (obj != NULL)
    {
        ret = ( dat <= obj->m_usedCount);
    }
    else
    {
        printf("Error in isCanSetCurIdMt2,obj is NULL ln:%d, fl:%s \n",__LINE__,__FILE__);
    }
    return ret;
}

unsigned int setCurIndexMt2(struct mat2 *obj,unsigned int dat)
{    
    unsigned int ret = 0;
    if (obj != NULL)
    {
        if( dat <= obj->m_usedCount)
        {
            obj->m_currenIndex = dat;
            ret = 1;
        }
        else
        {
            ret = 0;
            printf("== Error dat is invalid : %u, usedCount:%u, ln:%d, fl:%s \n",dat,obj->m_usedCount,__LINE__,__FILE__);
        }
    }
    else
    {
        printf("== Error mat2 obj point is NULL, ln:%d, fl:%s \n",__LINE__,__FILE__);
    }
    return ret;
}


void* go2DatMt2(struct mat2 *obj,unsigned int index)
{
    void *ret =NULL;
    if (obj!=NULL)
    {
        if (index < obj->m_usedCount)
        {
            ret = obj->rowP[index];
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
    return ret;
}
void resetReaderDatMt2(struct mat2 *obj)
{
    if (obj != NULL)
    {
        obj->m_currenIndex = 0;
    }
    else
    {
        /* do nothing */
    }
}
void printMt2(struct mat2 *obj)
{
    int index = 0;
    int num = 0;
    void **arrMt = NULL;
    struct mat2Ele *m2El =NULL;
    struct nodeFixedArr *nodeFArr =NULL;
    struct pVoidEle2 *pVele2 =NULL;
    struct nodeFixedArrNBIn *nodeFArr2 =NULL;
    if (obj!=NULL)
    {
        num= obj->m_row;
        printf("Mat2 \n");
        printf("t:%u rxc:(%ux%u) ",obj->m_type,obj->m_row,obj->m_col);
        printf("Dsize:%u uCount:%u, curIndex:%u rowP:%p pAfterObj:%p\n",obj->m_dataSize,obj->m_usedCount,obj->m_currenIndex,obj->rowP,getDatMt2(obj));
        arrMt = getDatMt2(obj);
 
            if (obj->m_type ==2)
            {
                for(index=0;index<num;index++)
                {
                    m2El = (struct mat2Ele*)arrMt[index];
                    printf("i:%d &m2El:%p, &mPoin:%p Val(%p), &len:%p val(%u) &Str:%p \n",index,m2El,&(m2El->m_pointRef),m2El->m_pointRef,&(m2El->m_length),m2El->m_length,m2El->m_startP);
                }
            }
            else if (obj->m_type ==3)
            {
                for(index=0;index<num;index++)
                {
                    nodeFArr = (struct nodeFixedArr*)arrMt[index];
                    printf("i:%d ",index);
                    printHeadFixedArrNode(nodeFArr);
                }
            }
            else if (obj->m_type ==4)
            {
                for(index=0;index<num;index++)
                {
                    nodeFArr2 = (struct nodeFixedArrNBIn*)arrMt[index];
                    printf("i:%d ",index);
                    printHeadFixedArrNode2(nodeFArr2);
                }
            }
            else if (obj->m_type ==5)
            {
                for(index=0;index<num;index++)
                {
                    pVele2 = (struct pVoidEle2*)arrMt[index];
                    printf("i:%d ",index);
                    printHeadPvEle2(pVele2);
                }
            }
            else
            {
                /* do nothing */
            }
 
    }
    else
    {
        printf("Mat2 Is NULL\n");
    }
}

void rmEleMt2(void *obj1,void *dat)
{
    struct nodeFixedArr *p1=NULL;
    struct nodeFixedArrNBIn *p12=NULL;
    struct mat2Ele *p2=NULL;
    struct pVoidEle2 *p3=NULL;
    struct mat2 *obj=(struct mat2*)obj1;
    int index=0;
    if ((obj!=NULL)&&(dat!=NULL))
    {
        if (obj->m_usedCount >= obj->m_row)
        {
            index = obj->m_row-1;
        }
        else
        {
            index = obj->m_usedCount-1;
        }
        if (obj->m_usedCount>0)
        {
            if (obj->m_type ==2)
            {
                p2 = (struct mat2Ele *)obj->rowP[index];
                swapMt2((struct mat2Ele *)dat,p2);
                obj->m_usedCount--;
            }
            else if (obj->m_type ==3)
            {
                p1 = (struct nodeFixedArr *)obj->rowP[index];
                swapMt2t3((struct nodeFixedArr *)dat,p1);
                obj->m_usedCount--;
            }
            else if (obj->m_type ==4)
            {
                p12 = (struct nodeFixedArrNBIn *)obj->rowP[index];
                swapMt2t4((struct nodeFixedArrNBIn *)dat,p12);
                obj->m_usedCount--;
            }
            else if (obj->m_type == 5)
            {
                p3 = (struct pVoidEle2 *)obj->rowP[index];
                swapMt2t5((struct pVoidEle2 *)dat,p3);
                obj->m_usedCount--;
            }
            else
            {
                /* do nothing */
            }
            
            if (obj->m_usedCount == 0)
            {
                obj->m_currenIndex = 0;
            }
            else if (obj->m_usedCount <= obj->m_currenIndex)
            {
                obj->m_currenIndex = obj->m_usedCount-1;
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
void printHeadFixedArrNode(struct nodeFixedArr *obj)
{
    if (obj!=NULL)
    {
        printf("&fAN:%p,&Rf:%p V(%p),&l:%p v(%u) &H:%p v(%u) ",obj,&(obj->m_ref),obj->m_ref,&(obj->m_length),obj->m_length,&(obj->m_height),obj->m_height);
        printf("&L:%p(%p),&R:%p(%p),&Dt:%p(%p), &Dt2:%p(%p)\n",&(obj->m_lf),obj->m_lf,&(obj->m_rt),obj->m_rt,&(obj->m_dat),obj->m_dat,&(obj->m_dat2),obj->m_dat2);
    }
    else
    {
        /* do nothing */
    }
    
}
void printHeadFixedArrNode2(struct nodeFixedArrNBIn *obj)
{
    if (obj!=NULL)
    {
        printf("&fAN:%p,&Rf:%p V(%p), &H:%p v(%u) ",obj,&(obj->m_ref),obj->m_ref,&(obj->m_height),obj->m_height);
        printf("&L:%p(%p),&R:%p(%p),&Dt:%p(%p),&Dt2:%p(%p)\n",&(obj->m_lf),obj->m_lf,&(obj->m_rt),obj->m_rt,&(obj->m_dat),obj->m_dat,&(obj->m_dat2),obj->m_dat2);
    }
    else
    {
        /* do nothing */
    }
    
}
void printHeadPvEle2(struct pVoidEle2 *obj)
{
    if (obj!=NULL)
    {
        printf("&R:%p ",&(obj->m_ref));
        printf("R:%p B:%p, O:%p D:%p, N:%p\n",obj->m_ref,obj->m_back,obj,obj->m_data,obj->m_next);
    }
    else
    {
        /* do nothing */
    }
} 
void printMt24Double(struct mat2 *obj)
{
    int index=0;
    int index2=0;
    int num=0;
    int num2=0;
    void **arrMt =NULL;
    double *dv = NULL;
    struct nodeFixedArr *nodeFArr =NULL;
    struct nodeFixedArrNBIn *nodeFArr2 =NULL;
    struct mat2Ele *m2El =NULL;
    if (obj!=NULL)
    {
        num= obj->m_row;
       /*num= obj->m_usedCount;*/
        printf("Mat2 \n");
        printf("t:%u rxc:(%ux%u) ",obj->m_type,obj->m_row,obj->m_col);
        printf("Dsize:%u uCount:%u rowP:%p pAfterObj:%p\n",obj->m_dataSize,obj->m_usedCount,obj->rowP,getDatMt2(obj));
        arrMt = getDatMt2(obj);

        if (obj->m_type == 2)
        {
            for(index=0;index<num;index++)
            {
                m2El = (struct mat2Ele*)arrMt[index];
                printf("i:%d &m2El:%p, &mPoin:%p Val(%p), &len:%p val(%u) &Str:%p \n",index,m2El,&(m2El->m_pointRef),m2El->m_pointRef,&(m2El->m_length),m2El->m_length,m2El->m_startP);
                num2 = m2El->m_length;
                dv = (double*)(m2El->m_startP);
                if ((dv !=NULL)&&(obj->m_dataSize != 0))
                {
                    for(index2=0;index2<num2;index2++)
                    {
                         printf("%f ",dv[index2]);
                    }
                    printf("\n");
                }
                else
                {
                    printf(" dat:NULL \n");
                }
            }
        }
        else if (obj->m_type==3)
        {            
            for(index=0;index<num;index++)
            {
                nodeFArr = (struct nodeFixedArr*)arrMt[index];
                printf("i:%d ",index);
                printHeadFixedArrNode(nodeFArr);
                num2 = nodeFArr->m_length;
                dv = (double*)(nodeFArr->m_dat);
                if ((dv !=NULL)&&(obj->m_dataSize != 0))
                {
                    for(index2=0;index2<num2;index2++)
                    {
                         printf("%f ",dv[index2]);
                    }
                    printf("\n");
                }
                else
                {
                    printf(" dat:NULL \n");
                }
            }
        }
        else if (obj->m_type==4)
        {            
            for(index=0;index<num;index++)
            {
                nodeFArr2 = (struct nodeFixedArrNBIn*)arrMt[index];
                printf("i:%d ",index);
                printHeadFixedArrNode2(nodeFArr2);
            }
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Mat2 Is NULL\n");
    }
}
void clearMt2(struct mat2 **obj)
{
    void *lobj =NULL;
    if (obj!= NULL)
    {
        if (*obj !=NULL)
        {
            lobj = (void*)*obj;
            free(lobj);
            *obj =NULL;
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

void swapRandomMt2(struct mat2 *obj)
{
    if (obj != NULL)
    { 
        swapRandomMt2WithNum(obj,obj->m_usedCount);
    }
    else
    {
        /* do nothing */
    }
} 

void swapRandomMt2WithNum(struct mat2 *obj,unsigned int numRandom)
{
    unsigned int indexA =0;
    unsigned int indexB =0;
    unsigned int index =0;
    void **arrMt =NULL;
    unsigned int numEle =0;
    unsigned int numLoop = 0;
    if (obj!=NULL)
    {
        numEle = obj->m_usedCount;
        arrMt  = getDatMt2(obj);
        if (numEle > numRandom)
        {
            numLoop = numRandom;
        }
        else
        {
            numLoop = numEle;
        }
        for(index=0;index<numLoop;index++)
        {
            indexA = rand()%numEle;
            indexB = rand()%numEle;
            if (obj->m_type ==2)
            {
                swapMt2((struct mat2Ele*)arrMt[indexA],(struct mat2Ele*)arrMt[indexB]);
            }
            else if (obj->m_type ==3)
            {
                swapMt2t3((struct nodeFixedArr*)arrMt[indexA],(struct nodeFixedArr*)arrMt[indexB]);
            }
            else if (obj->m_type ==4)
            {
                swapMt2t4((struct nodeFixedArrNBIn*)arrMt[indexA],(struct nodeFixedArrNBIn*)arrMt[indexB]);
            }
            else if (obj->m_type == 5)
            {
                swapMt2t5((struct pVoidEle2*)arrMt[indexA],(struct pVoidEle2*)arrMt[indexB]);
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

void swapMt2(struct mat2Ele *rhs,struct mat2Ele *lhs)
{
    void **tmp1=NULL;
    void **tmp2=NULL;
    void **tmp3=NULL;
    void *tmp4=NULL;
    if ((rhs!=NULL)&&(lhs!=NULL))
    {
        tmp1 = (void**)rhs->m_pointRef;
        tmp2 = (void**)lhs->m_pointRef;
        tmp3 = rhs->m_pointRef;
        rhs->m_pointRef = lhs->m_pointRef;
        lhs->m_pointRef = tmp3;
        tmp4 = *tmp1;
        *tmp1 = *tmp2;
        *tmp2 = tmp4;
    }
    else
    {
        /* do nothing */
    }
}
void swapMt2t3(struct nodeFixedArr *rhs,struct nodeFixedArr *lhs)
{
    void **tmp1=NULL;
    void **tmp2=NULL;
    void **tmp3=NULL;
    void *tmp4=NULL;
    if ((rhs!=NULL)&&(lhs!=NULL))
    {
        tmp1 = (void**)rhs->m_ref;
        tmp2 = (void**)lhs->m_ref;
        tmp3 = rhs->m_ref;
        rhs->m_ref = lhs->m_ref;
        lhs->m_ref = tmp3;
        tmp4 = *tmp1;
        *tmp1 = *tmp2;
        *tmp2 = tmp4;
    }
    else
    {
        /* do nothing */
    }
}
void swapMt2t4(struct nodeFixedArrNBIn *rhs,struct nodeFixedArrNBIn *lhs)
{
    void **tmp1=NULL;
    void **tmp2=NULL;
    void **tmp3=NULL;
    void *tmp4=NULL;
    if ((rhs!=NULL)&&(lhs!=NULL))
    {
        tmp1 = (void**)rhs->m_ref;
        tmp2 = (void**)lhs->m_ref;
        tmp3 = rhs->m_ref;
        rhs->m_ref = lhs->m_ref;
        lhs->m_ref = tmp3;
        tmp4 = *tmp1;
        *tmp1 = *tmp2;
        *tmp2 = tmp4;
    }
    else
    {
        /* do nothing */
    }
}
void swapMt2t5(struct pVoidEle2 *rhs,struct pVoidEle2 *lhs)
{
    void **tmp1=NULL;
    void **tmp2=NULL;
    void **tmp3=NULL;
    void *tmp4=NULL;
    if ((rhs!=NULL)&&(lhs!=NULL))
    {
        tmp1 = (void**)rhs->m_ref;
        tmp2 = (void**)lhs->m_ref;
        tmp3 = rhs->m_ref;
        rhs->m_ref = lhs->m_ref;
        lhs->m_ref = tmp3;
        tmp4 = *tmp1;
        *tmp1 = *tmp2;
        *tmp2 = tmp4;
    }
    else
    {
        /* do nothing */
    }
}
void** getDatMt22d(struct mat2_2d *obj,unsigned int indexSegment)
{
    mat2 *objmt =NULL;
    if (obj!=NULL)
    {
        /*
        printf("--indexSegment :%d \n",indexSegment);
        */
        if (indexSegment < NUM_ARR)
        {
            objmt = obj->m_dat[indexSegment];
        }
        else
        {
            /* do nothing */
        }
        return getDatMt2(objmt);
    }
    else
    {
        /* do nothing */
    }
    return NULL;
}
void* getDatNextMt22d(void *obj1)
{
    void *tmp=NULL;
    struct mat2_2d *obj = obj1;
    int currentOffset=0;
    if (obj!=NULL)
    {
        currentOffset = obj->m_dat[obj->m_segmentCur]->m_usedCount;
        if (currentOffset >= obj->m_dat[obj->m_segmentCur]->m_row)
        {
            if ((obj->m_segmentCur+1) < obj->m_numUsed )
            {
                obj->m_segmentCur++;
                tmp = (getDatNextMt2((void*)(obj->m_dat[obj->m_segmentCur])));
            }
            else if (obj->m_segmentCur < (NUM_ARR-1))
            {
                expandMt22dSize(obj);
                obj->m_segmentCur++;
                /*
                printf("seg:%d , offset:%d\n",obj->m_segmentCur,obj->m_offsectCur);
               */ tmp = (getDatNextMt2((void*)(obj->m_dat[obj->m_segmentCur])));
            }
            else
            {
                printf("Mem if full, ln:%d  File:%s\n",__LINE__,__FILE__);
            }
        }
        else
        {
            /*  printf("seg:%d , offset:%d\n",obj->m_segmentCur,obj->m_offsectCur);*/
            tmp = (getDatNextMt2((void*)(obj->m_dat[obj->m_segmentCur])));
        }
    }
    else
    {
        /* do nothing */
    }
    return tmp;
}
void* readDatNextMt22d(struct mat2_2d *obj)
{
    void *tmp = NULL;
    unsigned int currentOffset = 0;
    if (obj != NULL)
    {
        currentOffset = obj->m_dat[obj->m_segmentCurIndex]->m_currenIndex;
        if (currentOffset >= obj->m_dat[obj->m_segmentCurIndex]->m_usedCount)
        {
            if ((obj->m_segmentCurIndex < obj->m_segmentCur) && (obj->m_dat[obj->m_segmentCurIndex]->m_usedCount == obj->m_dat[obj->m_segmentCurIndex]->m_row))
            {
                obj->m_segmentCurIndex++;
                resetReaderDatMt2((obj->m_dat[obj->m_segmentCurIndex]));
                /*
                    printf("seg:%d , offset:%d\n",obj->m_segmentCur,obj->m_offsectCur);
                */ 
                tmp = (readDatNextMt2((obj->m_dat[obj->m_segmentCurIndex])));
            }
            else
            {
                printf("== Error : curnOffset:%u, SegCur:%u, m_useCount:%u\n",currentOffset,obj->m_segmentCurIndex,obj->m_dat[obj->m_segmentCurIndex]->m_usedCount);
                printf("Mem if full, ln:%d  File:%s\n",__LINE__,__FILE__);
            }
        }
        else
        {
            /*  printf("seg:%d , offset:%d\n",obj->m_segmentCur,obj->m_offsectCur);*/
            tmp = (readDatNextMt2((obj->m_dat[obj->m_segmentCurIndex])));
        }
    }
    else
    {
        /* do nothing */
    }
    return tmp;
}


int resetDatStoreInMt22d(struct mat2_2d *obj)
{
    int ret = (obj != NULL);
    int index = 0;
    int num = 0;
    if (ret == 1)
    {
        num = obj->m_numUsed;
        for (index = 0;index < num;index++)
        {
            ret = (resetDatStoreInMt2(obj->m_dat[index]) &&(ret == 1));
        }
        obj->m_segmentCur = 0;
        obj->m_segmentCurIndex = 0;
    }
    else
    {
        printf("Error in resetDatStoreInMt22d, obj is null. ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    return ret;
}
void* go2ReadDatMt22d(struct mat2_2d *obj,unsigned int indexSegment,unsigned int offset)
{
    void *tmp=NULL;
    if (obj!=NULL)
    {
        if (indexSegment < obj->m_numUsed)
        {
            if (offset<obj->m_dat[indexSegment]->m_usedCount)
            {
                /*  printf("seg:%d , offset:%d\n",obj->m_segmentCur,obj->m_offsectCur);*/
                tmp = (go2DatMt2((obj->m_dat[indexSegment]),offset));
            }
            else
            {
                
            }
        }
        else
        {
            printf("Error in go2ReadDatMt22d: indexSegment >obj->m_numUsed : (%u,%u) :ln:%d\n",indexSegment,obj->m_numUsed,__LINE__);
        }

    }
    else
    {
        /* do nothing */
    }
    return tmp;
}

int convertIndex2IdSegAndOfSt4Mt22d(struct mat2_2d *obj,const unsigned int id,unsigned int *indexSegment,unsigned int *offset)
{
    int ret = ((obj != NULL) && (indexSegment != NULL) && (offset != NULL));
    unsigned int index = 0;
    unsigned int num = getUsedNumDatMt22d(obj);
    unsigned int num2 = 0;
    unsigned int tmp1 = id;
    
    if (ret == 1)
    {
        ret = 0;
        for (index = 0;index < num;index++)
        {
            num2 = getUsedOffsetNumDatMt22d(obj,index);
            if (tmp1 < num2)
            {
                *indexSegment = index;
                *offset = tmp1;
                index = num;
                ret = 1;
            }
            else
            {
                tmp1 = tmp1 - num2;
            }
        }
        if (ret == 0)
        {
            printf("Error(1) in convertIndex2IdSegAndOfSt4Mt22d, the id(%u) exceed:%u, ln:%d,File:%s\n",id,tmp1,__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Error(0) in convertIndex2IdSegAndOfSt4Mt22d, obj:%p, idSeg:%p,Offset:%p ,ln:%d, file:%s\n",obj,indexSegment,offset,__LINE__,__FILE__);
    }
    return ret;
}

void expandMt22dSize(struct mat2_2d *obj)
{
    double temp1=0.0;
    if (obj!=NULL)
    {
        temp1 = g_arrNum[obj->m_numUsed-1];
        temp1 = temp1*obj->m_dat[0]->m_row;
        expandMt22dSizeWithSize(obj,(unsigned int)temp1);
    }
    else
    {
        /* do nothing */
    }
}

void resetReaderDatMt22d(struct mat2_2d *obj)
{
    int index=0; 
    if (obj != NULL)
    {
        obj->m_segmentCurIndex = 0;
        for(index = 0;index < NUM_ARR;index++)
        {
            resetReaderDatMt2(obj->m_dat[index]);
        }
    }
    else
    {
        /* do nothing */
    }
}

unsigned int getCurSegIdMt22d(struct mat2_2d *obj,unsigned int *segId,unsigned int *id)
{
    unsigned int ret = 0;
    if ((obj != NULL) && (segId != NULL) && (id != NULL))
    {
        ret = 1;
        *segId = obj->m_segmentCurIndex;
        if(obj->m_segmentCurIndex < obj->m_numUsed)
        {
            *id = getCurIndexMt2(obj->m_dat[*segId]);
        }
        else
        {
            *id = 0;
            ret = 0;
            printf("Error cannot get *id, ln:%d, fl:%s \n",__LINE__,__FILE__);
        }
    }
    else
    {
        printf("== Error (obj,%p), (segId,%p) or (id,%p) point is NULL, ln:%d, fl:%s \n",obj,segId,id,__LINE__,__FILE__);
    }
    return ret;
}

unsigned int isCanSetCurSegIdMt22d(struct mat2_2d *obj,const unsigned int  segId,const unsigned int id)
{
    unsigned int ret = 0;
    if (obj != NULL)
    {
        if(obj->m_numUsed > segId)
        {
            ret = isCanSetCurIdMt2(obj->m_dat[segId],id);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Error in isCanSetCurSegIdMt22d,obj is NULL ln:%d, fl:%s \n",__LINE__,__FILE__);
    }
    return ret;
}

unsigned int setCurSegIdMt22d(struct mat2_2d *obj,const unsigned int  segId,const unsigned int id)
{
    unsigned int ret = 0;
    if (isCanSetCurSegIdMt22d(obj,segId,id) == 1)
    {
        obj->m_segmentCurIndex = segId;
        ret = setCurIndexMt2(obj->m_dat[segId],id);
    }
    else
    {
        printf("Error in setCurSegIdMt22d, obj is null or segId is invalid:%u numUse:%u, ln:%d, fl:%s \n",segId,obj->m_numUsed,__LINE__,__FILE__);
    }
    return ret;
}
unsigned int getUsedNumDatMt22d(struct mat2_2d *obj)
{
    unsigned int ret =0;
    if (obj!=NULL)
    {
        ret = obj->m_numUsed;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

unsigned int getUsedOffsetNumDatMt22d(struct mat2_2d *obj,unsigned int indexSegment)
{
    unsigned int ret = 0;
    if (obj != NULL)
    {
        ret = getUsedNumDatMt22d(obj);
    }
    else
    {
        /* do nothing */
    }
    if (ret > indexSegment)
    {
        ret = obj->m_dat[indexSegment]->m_usedCount;
    }
    return ret;
}
unsigned int getNumOfUsedDatMt22d(struct mat2_2d *obj)
{
    unsigned int uTemp = 0;
    unsigned int index = 0;
    unsigned int num = 0;
    if (obj != NULL)
    {
        num = getUsedNumDatMt22d(obj);
        for (index = 0;index < num;index++)
        {
            uTemp += getNumUsedMt2(obj->m_dat[index]);
        }
    }
    else
    {
        /* do nothing */
    }
    return uTemp;
}

void swapByIndex4Mt22D(struct mat2_2d *obj,unsigned int idA,unsigned int idB)
{
    unsigned  int numArrUsed = getUsedNumDatMt22d(obj);
    unsigned  int indexA = 0;
    unsigned  int indexB = 0;
    unsigned  int offSetA = 0;
    unsigned  int offSetB = 0;
    void **arrMt1 = NULL;
    void **arrMt2 = NULL;
    unsigned  int type = 0;
    int ret = (numArrUsed > 0);
    ret = ((ret == 1) && convertIndex2IdSegAndOfSt4Mt22d(obj,idA,&indexA,&offSetA));
    ret = ((ret == 1) && convertIndex2IdSegAndOfSt4Mt22d(obj,idB,&indexB,&offSetB));
    if (ret == 1)
    {
        type = obj->m_dat[0]->m_type;
        arrMt1  = getDatMt2(obj->m_dat[indexA]);
        arrMt2  = getDatMt2(obj->m_dat[indexB]);
        if (type == 2)
        {
            swapMt2((struct mat2Ele*)arrMt1[offSetA],(struct mat2Ele*)arrMt2[offSetB]);
        }
        else if (type == 3)
        {
            swapMt2t3((struct nodeFixedArr*)arrMt1[offSetA],(struct nodeFixedArr*)arrMt2[offSetB]);
        }
        else if (type == 4)
        {
       /* printf("IndexA:%u, offsetA:%u, IndexB:%u, offsetB:%u\n",indexA,offSetA,indexB,offSetB);*/
            swapMt2t4((struct nodeFixedArrNBIn*)arrMt1[offSetA],(struct nodeFixedArrNBIn*)arrMt2[offSetB]);
        }
        else if (type == 5)
        {
            swapMt2t5((struct pVoidEle2*)arrMt1[offSetA],(struct pVoidEle2*)arrMt2[offSetB]);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {  
        printf("Error(0) in swapByIndex4Mt22D, obj is %p, ln:%d, file:%s\n",obj,__LINE__,__FILE__);
    }
    
}

void expandMt22dSizeWithSize(struct mat2_2d *obj,unsigned int numNewRow)
{
    unsigned int col =0;
    unsigned int valSize =0;
    if ((obj != NULL) && (numNewRow > 0))
    {
        col = obj->m_dat[0]->m_col;
        valSize = obj->m_dat[0]->m_dataSize;
        if (obj->m_numUsed < NUM_ARR)
        {
            /* printf("YYYYYYYYYYYYYYYYYYYYYYYYYYYYy\n");*/
            obj->m_dat[obj->m_numUsed] = newMt2(numNewRow,col,valSize,obj->m_dat[0]->m_type);
            /* printf("YYYYYYYYYYYYYYYYYYYYYYYYYYYYy\n");*/
            if (obj->m_dat[obj->m_numUsed] != NULL)
            {
                obj->m_numUsed++;
            }
            else
            {
                printf("Error cannot extend space of Mt22 :%s %d \n",__FILE__,__LINE__);
            }
        }
        else
        {
            printf("Error cannot extend space of Mt22 :%s %d \n",__FILE__,__LINE__);
        }

    }
    else
    {
        /* do nothing */
    }
}
struct mat2_2d newMt22d(unsigned int row,unsigned int col,unsigned int valSize,unsigned int type)
{
    struct mat2_2d mObj;
    unsigned int index = 0;
    mObj.m_numUsed = 0;
    mObj.m_segmentCur = 0;
    mObj.m_segmentCurIndex = 0;
    for (index = 0;index < NUM_ARR;index++)
    {
        mObj.m_dat[index] = NULL;
    }
    if (row != 0)
    {
        mObj.m_numUsed = 1;
        mObj.m_dat[0] = newMt2(row,col,valSize,type);
    }
    else
    {
        /* do nothing */
    }
    return mObj;
} 
void initiValInMt22d(struct mat2_2d *obj)
{
    int index =0;
    int num = NUM_ARR;
    if (obj != NULL)
    {
        obj->m_segmentCur=-1;
        obj->m_numUsed = 0;
        for (index=  0;index < num;index++)
        {
            obj->m_dat[index] = NULL;
        }
    }
    else
    {
        /* do nothing */
    }
}
void clearMt22d(struct mat2_2d *obj)
{
    int index=0;
    int num = 0;
    if (obj != NULL)
    {
        num = obj->m_numUsed;
        for(index = 0;index < num;index++)
        {
            if (obj->m_dat[index] != NULL)
            {
                free(obj->m_dat[index]);
            }
            else
            {
                /* do nothing */
            }
        }
        initiValInMt22d(obj);
    }
    else
    {
        /* do nothing */
    }
}

unsigned int getTypeMt22d(struct mat2_2d *obj)
{
    unsigned int type =0;
    if (obj!=NULL)
    {
        if (obj->m_dat[0]!=NULL)
        {
            type =obj->m_dat[0]->m_type;
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
    return type;
}

void rmEleMt22d(void *obj1,void *dat)
{
    int index = -1;
    struct mat2_2d *obj = (struct mat2_2d*)obj1;
    if ((obj!=NULL)&&(dat!=NULL))
    {
        if (obj->m_numUsed > 0)
        {
            index = obj->m_numUsed-1;
        }
        else
        {
            index = 0;
        }
    }
    else
    {
        /* do nothing */
    }
    if (index != -1)
    {
        rmEleMt2((void*)(obj->m_dat[index]),dat);
    }
    else
    {
        /* do nothing */
    }
}
void printMt22d(struct mat2_2d *obj)
{
    int index=0;
    int num=0;
    if (obj!=NULL)
    {
        num = NUM_ARR;
        printf("print Mat2_2d\n");
        printf("sg:%d, nUsed:%u, mDatP:%p \n",obj->m_segmentCur,obj->m_numUsed,obj->m_dat);
        for(index=0;index<num;index++)
        {
            printf("index:%d ",index);
            printMt2(obj->m_dat[index]);
        }
    }
    else
    {
        /* do nothing */
    }
}
void printMt22d4Double(struct mat2_2d *obj)
{
    int index=0;
    int num=0;
    if (obj!=NULL)
    {
        num = NUM_ARR;
        printf("print Mat2_2d\n");
        printf("sg:%d, nUsed:%u, mDatP:%p \n",obj->m_segmentCur,obj->m_numUsed,obj->m_dat);
        for(index=0;index<num;index++)
        {
            printf("index:%d ",index);
            printMt24Double(obj->m_dat[index]);
        }
    }
    else
    {
        /* do nothing */
    }
}

void swapRandomMt22dWithNum(struct mat2_2d *obj,unsigned int numRandom)
{
    unsigned  int index = 0;
    unsigned  int numArrUsed = 0;
    unsigned  int numArrUsedA = 0;
    unsigned  int numArrUsedB = 0;
    unsigned  int numLoop = numRandom;
    unsigned  int indexA = 0;
    unsigned  int indexB = 0;
    unsigned  int offSetA = 0;
    unsigned  int offSetB = 0;
    void **arrMt1 =NULL;
    void **arrMt2 =NULL;
    unsigned  int type = 0; 
    printf("numRandom : %u ",numRandom);
    if (obj == NULL)
    {
        /* do nothing */
    }
    else if (getNumOfUsedDatMt22d(obj) == 0)
    {printf("\n");
        /* do nothing */
    }
    else if (getUsedNumDatMt22d(obj)  == 0)
    {
        /* do nothing */
    }
    else if (getUsedNumDatMt22d(obj) > 0)
    {
        numArrUsed = getUsedNumDatMt22d(obj);
        numLoop = getNumOfUsedDatMt22d(obj);
        /*
        printf("maxNum:%u numLoop:%u \n",numLoop,numRandom);
        */
        if (numRandom < numLoop)
        {
            numLoop = numRandom;
        }
        else
        {
            /* do nothing */
        }
        if (numArrUsed != 0)
        {
            type = obj->m_dat[0]->m_type;
        }
        else
        {
            /* do nothing */
        }
        for(index = 0;index < numLoop; index++)
        {
            indexA = rand()%numArrUsed;
            indexB = rand()%numArrUsed; 
            numArrUsedA = obj->m_dat[indexA]->m_usedCount;
            numArrUsedB = obj->m_dat[indexB]->m_usedCount;
            arrMt1  = getDatMt2(obj->m_dat[indexA]);
            arrMt2  = getDatMt2(obj->m_dat[indexB]);
            if ((numArrUsedA > 0) && (numArrUsedB > 0))/* check divide by 0 */
            {
                offSetA = rand()%numArrUsedA;
                offSetB = rand()%numArrUsedB;
            }
            else
            {
                printf("Error divide by zero, numA:%u, numB:%u, fl:%s, ln:%d \n",numArrUsedA,numArrUsedB,__FILE__,__LINE__);
            }
            
            if (offSetA >= obj->m_dat[indexA]->m_row)
            {
                printf("Error out bound:OffsetA:%u, row:%u\n",offSetA,obj->m_dat[indexA]->m_row); continue;
            }
            if (offSetB >= obj->m_dat[indexB]->m_row)
            {
                printf("Error out bound:OffsetB:%u, row:%u\n",offSetB,obj->m_dat[indexB]->m_row);continue;
            }
            if (type ==2)
            {
                swapMt2((struct mat2Ele*)arrMt1[offSetA],(struct mat2Ele*)arrMt2[offSetB]);
            }
            else if (type ==3)
            {
                swapMt2t3((struct nodeFixedArr*)arrMt1[offSetA],(struct nodeFixedArr*)arrMt2[offSetB]);
            }
            else if (type ==4)
            {
           /* printf("IndexA:%u, offsetA:%u, IndexB:%u, offsetB:%u\n",indexA,offSetA,indexB,offSetB);*/
                swapMt2t4((struct nodeFixedArrNBIn*)arrMt1[offSetA],(struct nodeFixedArrNBIn*)arrMt2[offSetB]);
            }
            else if (type == 5)
            {
                swapMt2t5((struct pVoidEle2*)arrMt1[offSetA],(struct pVoidEle2*)arrMt2[offSetB]);
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
/* private method of struct pVoidEle2 */

void* getNxpVd2Ele(void *node)
{
    void *p = NULL;
    if (node!=NULL)
    {
        p = ((struct pVoidEle2*)node)->m_next;
    }
    else
    {
        /* do nothing */
    }
    return p;
}
void* getBkpVd2Ele(void *node)
{
    void *p = NULL;
    if (node!=NULL)
    {
        p = ((struct pVoidEle2*)node)->m_back;
    }
    else
    {
        /* do nothing */
    }
    return p;
} 
void* getDatpVd2Ele(void *node)
{
    void *p = NULL;
    if (node!=NULL)
    {
        p = ((struct pVoidEle2*)node)->m_data;
    }
    else
    {
        /* do nothing */
    }
    return p;
}
     
int setNxpVd2Ele(void *node1,void *node2)
{
    int ret = 0;
    if (node1!=NULL)
    {
        ((struct pVoidEle2*)node1)->m_next = node2;
        ret = 1;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

int setBkpVd2Ele(void *node1,void *node2)
{
    int ret = 0;
    if (node1!=NULL)
    {
        ((struct pVoidEle2*)node1)->m_back = node2;
        ret = 1;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int setDatpVd2Ele(void *node1,void *node2)
{
    int ret = 0;
    if (node1!=NULL)
    {
        ((struct pVoidEle2*)node1)->m_data = node2;
        ret = 1;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

void  freeAlcPEle2(void *obj,void *node)
{
    if ((obj!=NULL)&&(node!=NULL))
    {
        rmEleMt22d(obj,node);
    }
    else
    {
        /* do nothing */
    }
}
void constructPVList4PVEle2(void *node,void *src,void *funct)
{
    void (*funct1)(void*,void*,void**) = funct;
    struct mat2Ele *mtE = (struct mat2Ele*)node;
    if ((mtE!=NULL)&&(src!=NULL)&&(funct1!=NULL))
    {    
        void *paraFunct[8];
        paraFunct[0] = &getNxpVd2Ele;
        paraFunct[1] = &getBkpVd2Ele;
        paraFunct[2] = &getDatpVd2Ele;
        paraFunct[3] = &setNxpVd2Ele;
        paraFunct[4] = &setBkpVd2Ele;
        paraFunct[5] = &setDatpVd2Ele;
        paraFunct[6] = &getDatNextMt22d;
        paraFunct[7] = &freeAlcPEle2;
        funct1(mtE->m_startP,src,paraFunct);
    }
    else
    {
        /* do nothing */
    }
}
/*void setIsFreeDataOfPVoidList(void *list,int value,void *delDatFunct);*/
void initialPVList4PVEle2_1(void *obj,int val,void *funct1,void *funct2)
{
    void (*funct)(void*,int,void*) = funct1;
    struct mat2Ele *mtE = (struct mat2Ele*)obj;
    if ((mtE!=NULL)&&(funct!=NULL))
    {    
        funct(mtE->m_startP,val,funct2);
    }
    else
    {
        /* do nothing */
    }
}
void construAvlT4SmMt2(void *bin,char isWD,const char *key,int sizeDt,int sizeKy,void *fnt)
{
    
}
/* end of private method of struct pVoidEle2 */