/********************************************************************/
/*
      FILE        :   setRealV.h
      Name        :   Chalearm Saelim
      Date        :   28 July 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to as a Set structure, element is long integer value (32 bits) 
                      setRealV = (Real value = floating point or number) set

      Description :   it keeps element in the way of AVL tree and Fixed sized array (semi-dynamic array)
      Dependency     :   We use the included library as below 
                                                #include "simMat2.h" 
                                                #include "avlTree.h"
      How to compile: gcc setLInt.c -o  a
      How to run        : -
      
      revision-history
      version   date          author     Description
      1.        28-07-2017    csaelim    First draft
      2.        24-09-2017    csaelim    Updated conde convension
*/


/*******************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "setRealV.h"
#include "avlTree.h"
#include "simMat2.h"

 /* data structure */
 /*
    can be kept redundant value
 */
/*m_type  1 st bit  : 0 long integer , 1 floating-point (double)
          2 nd bit  : 0 dynamic array, 1 not dynamic array
          3 rd bit  : 0 count redundant, 1 not count
          4 th bit  : 0 not vector, 1 vector
          5 th bit  : (spare)
          6 th bit  : (spare)
          7 th bit  : (spare)
          8 th bit  : (spare)
          9 th bit  : (void*) set, igore first bit to 8 th bit.
                      Must provide compare method, (option): de-allocation and print method
 */
/*m_buff :in case of no using dynamic arrar, this is used (mat2_2d structure) */
/*m_numMember : include redundant value */
/*
struct rvSet
{
    unsigned long int m_type;
    binaryTree m_tree;
    void *m_buff; 
    unsigned long int m_numMember;  
};
*/
 /* operation */
 void constructorRVSet(struct rvSet *obj,unsigned long int type)
 {
    if(obj != NULL)
    {
        obj->m_dimen = -1;  /*default = -1 in case not vector */
        /* mask 3bits  0x07 */
        obj->m_type = (unsigned long int)(0x07&type);
        obj->m_buff = NULL;
        obj->m_numMember = 0;
        switch(obj->m_type)
        {
            case 0: /* count redundant, dynamic array, long integer */
                /* Have data =1  */
                constructAvlTree((void*)&(obj->m_tree),1,"long int",0,sizeof(long int)); 
                setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_tree),delKeyNode4AvlT,delDatNode4AvlT,compLongInt4StRV);
                obj->m_tree.printKeyPVoid = prntLintKeyAvlT;
                obj->m_tree.printDataPVoid= prntDatIntCountStRV;
                obj->m_tree.getData = getDataFromAvlNode;
            break;
            case 1: /* count redundant, dynamic array, floating-point */
                constructAvlTree((void*)&(obj->m_tree),1,"double",0,sizeof(double)); 
                setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_tree),delKeyNode4AvlT,delDatNode4AvlT,compDouble4StRV);
                obj->m_tree.printKeyPVoid = prntDoubleKeyAvlT;
                obj->m_tree.printDataPVoid= prntDatDoubleCountStRV;
                obj->m_tree.getData = getDataFromAvlNode;
            break;
            case 2: /* count redundant,not dynamic array, long integer */
                /* build in fixed node */
                constructAvlTree((void*)&(obj->m_tree),2,"fixed arr",11,5);
                setDelKeyAndDelDataAndCompFnForAvlTree((void*)&(obj->m_tree),NULL,NULL,compLint4AVLTFixedArrBIn); 
                /* initial */
                obj->m_buff = malloc(sizeof(struct mat2_2d));
                if(obj->m_buff != NULL)
                {
                    obj->m_dimen = 2;
                    initiValInMt22d(obj->m_buff);
                    /* array size */
                    *((struct mat2_2d*)obj->m_buff) = newMt22d(100,2,sizeof(long int),3);
                    setParameterValofBinT((void*)&(obj->m_tree),3,obj->m_buff);
                }
                else
                {
                    printf("Error cannot initial set type :%lu, ln:%d file:%s \n",type,__LINE__,__FILE__);
                }
                obj->m_tree.printKeyPVoid = prntKeyTFixedArryBInIntCountStRV;
            break;
            case 3:/* count redundant,not dynamic array, floating-point */
                            /* build in fixed node */
                constructAvlTree((void*)&(obj->m_tree),2,"fixed arr",11,5);
                setDelKeyAndDelDataAndCompFnForAvlTree((void*)&(obj->m_tree),NULL,NULL,compDouble4AVLTFixedArrBIn); 
                /* initial */
                obj->m_buff = malloc(sizeof(struct mat2_2d));
                if(obj->m_buff != NULL)
                {
                    obj->m_dimen = 2;
                    initiValInMt22d(obj->m_buff);
                    /* array size */
                    *((struct mat2_2d*)obj->m_buff) = newMt22d(100,2,sizeof(double),3);
                    setParameterValofBinT((void*)&(obj->m_tree),3,obj->m_buff);
                }
                else
                {
                    printf("Error cannot initial set type :%lu, ln:%d file:%s \n",type,__LINE__,__FILE__);
                }
                obj->m_tree.printKeyPVoid = prntKeyTFixedArryBInDoubleCountStRV;
            break;
            case 4:/*not count redundant, dynamic array,  long integer */
                /* NODATA =0, only key */
                constructAvlTree((void*)&(obj->m_tree),0,"long int",0,sizeof(long int)); 
                setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_tree),delKeyNode4AvlT,NULL,compLongInt4StRV);
                obj->m_tree.printKeyPVoid = prntLintKeyAvlT;
                printf("type 4 of setReal V\n");
            break;
            case 5:/*not count redundant, dynamic array, floating-point */
                /* NODATA =0, only key */
                constructAvlTree((void*)&(obj->m_tree),0,"double",0,sizeof(double)); 
                setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_tree),delKeyNode4AvlT,NULL,compDouble4StRV);
                obj->m_tree.printKeyPVoid = prntDoubleKeyAvlT;
                printf("type 5 of setReal V\n");
            break;
            case 6:/*not count redundant,not dynamic array, long integer*/
                /* build in fixed node */
                constructAvlTree((void*)&(obj->m_tree),2,"fixed arr",11,5);
                setDelKeyAndDelDataAndCompFnForAvlTree((void*)&(obj->m_tree),NULL,NULL,compLint4AVLTFixedArrBIn); 
                /* initial */
                obj->m_buff = malloc(sizeof(struct mat2_2d));
                if(obj->m_buff != NULL)
                {
                    initiValInMt22d(obj->m_buff);
                    /* array size */
                    *((struct mat2_2d*)obj->m_buff) = newMt22d(100,1,sizeof(long int),3);
                    setParameterValofBinT((void*)&(obj->m_tree),3,obj->m_buff);
                }
                else
                {
                    printf("Error cannot initial set type :%lu, ln:%d file:%s \n",type,__LINE__,__FILE__);
                }
                obj->m_tree.printKeyPVoid = prntKeyTFixedArryBInIntNoCountStRV;
            break;
            case 7:/* not count redundant,not dynamic array, floating-point */
                /* build in fixed node */
                constructAvlTree((void*)&(obj->m_tree),2,"fixed arr",11,5);
                setDelKeyAndDelDataAndCompFnForAvlTree((void*)&(obj->m_tree),NULL,NULL,compDouble4AVLTFixedArrBIn); 
                /* initial */
                obj->m_buff = malloc(sizeof(struct mat2_2d));
                if(obj->m_buff != NULL)
                {
                    initiValInMt22d(obj->m_buff);
                    /* array size */
                    *((struct mat2_2d*)obj->m_buff) = newMt22d(100,1,sizeof(double),3);
                    setParameterValofBinT((void*)&(obj->m_tree),3,obj->m_buff);
                }
                else
                {
                    printf("Error cannot initial set type :%lu, ln:%d file:%s \n",type,__LINE__,__FILE__);
                }
                obj->m_tree.printKeyPVoid = prntKeyTFixedArryBInDoubleNoCountStRV;
            break;
            default: /* count redundant, dynamic array, long integer same 0 */
                /* Have data =1  */
                constructAvlTree((void*)&(obj->m_tree),1,"long int",0,sizeof(long int)); 
                setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_tree),delKeyNode4AvlT,delDatNode4AvlT,NULL);
                obj->m_tree.printKeyPVoid = prntLintKeyAvlT;
            break;
        }
        
    }
    else
    {
        /* do nothing */
    }
 }
 
void constructorRVSetVect(struct rvSet *obj,unsigned long int type,int dimenVal)
{
    if ((obj != NULL) && ((type&VECT_BIT) == VECT_BIT) && (dimenVal > 1))
    {
        obj->m_dimen = dimenVal;  /*default = -1 in case not vector */
        /* mask 3bits  0x07 */
        obj->m_type = (unsigned long int)(0x0f&type);
        obj->m_buff = NULL;
        obj->m_numMember = 0;
        
        switch(obj->m_type)
        {
            case 8: /* count redundant, dynamic array, long integer */
                /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
                constructAvlTree((void*)&(obj->m_tree),1,"custom type 2",0,sizeof(struct vector_lint)); 
                setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_tree),delVLintNodeRVSet,delVLintCountDatRVSet,compVLint4StRV);
                setDelKeyFlag(&(obj->m_tree),0); /*0 : AVL T will do the deallocation node*/
                obj->m_tree.printKeyPVoid = prntVLintKeyAvlT;
                obj->m_tree.printDataPVoid = prntDatIntCountStRV;
                obj->m_tree.getData = getDataFromAvlNode;
            /*
            obj->compareTypeWithOpt = compVDoubWithOpt4StatisLog;
            */
            break;
            case 9: /* count redundant, dynamic array, floating-point */
                /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
                constructAvlTree((void*)&(obj->m_tree),1,"custom type 2",0,sizeof(vector_double)); 
                setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_tree),delVDoubleNodeRVSet,delVLintCountDatRVSet,compVDouble4StRV);
                setDelKeyFlag(&(obj->m_tree),0); /*0 : AVL T will do the deallocation node*/
                obj->m_tree.printKeyPVoid = prntVDoubleKeyAvlT;
                obj->m_tree.printDataPVoid= prntDatDoubleCountStRV;
                obj->m_tree.getData = getDataFromAvlNode;
                
            break;
            case 0x0a: /* count redundant,not dynamic array, long integer */
                /* build in fixed node */
                constructAvlTree((void*)&(obj->m_tree),2,"fixed arr",11,5);
                setDelKeyAndDelDataAndCompFnForAvlTree((void*)&(obj->m_tree),NULL,NULL,compVLint4CountDatAVLTFixedArrBIn); 
                /* initial */
                obj->m_buff = malloc(sizeof(struct mat2_2d));
                if(obj->m_buff != NULL)
                {
                    initiValInMt22d(obj->m_buff); 
                    *((struct mat2_2d*)obj->m_buff) = newMt22d(100,dimenVal+1,sizeof(long int),3);
                    setParameterValofBinT((void*)&(obj->m_tree),3,obj->m_buff);
                }
                else
                {
                    printf("Error cannot initial set type :%lu, ln:%d file:%s \n",type,__LINE__,__FILE__);
                }
                obj->m_tree.printKeyPVoid = prntKeyTFixedArryBInIntCountStRV;
            break;
            case 0x0b:/* count redundant,not dynamic array, floating-point */
                /* build in fixed node */
                constructAvlTree((void*)&(obj->m_tree),2,"fixed arr",11,5);
                setDelKeyAndDelDataAndCompFnForAvlTree((void*)&(obj->m_tree),NULL,NULL,compVDouble4CountDatAVLTFixedArrBIn); 
                /* initial */
                obj->m_buff = malloc(sizeof(struct mat2_2d));
                if(obj->m_buff != NULL)
                {
                    initiValInMt22d(obj->m_buff);
                    *((struct mat2_2d*)obj->m_buff) = newMt22d(100,dimenVal+1,sizeof(double),3);
                    setParameterValofBinT((void*)&(obj->m_tree),3,obj->m_buff);
                }
                else
                {
                    printf("Error cannot initial set type :%lu, ln:%d file:%s \n",type,__LINE__,__FILE__);
                }
                obj->m_tree.printKeyPVoid = prntKeyTFixedArryBInDoubleCountStRV;
                
            break;
            case 0x0c:/*not count redundant, dynamic array,  long integer */
                /* NODATA =0, only key */
                /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
                constructAvlTree((void*)&(obj->m_tree),0,"custom type 2",0,sizeof(struct vector_lint)); 
                setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_tree),delVLintNodeRVSet,NULL,compVLint4StRV);
                setDelKeyFlag(&(obj->m_tree),0); /*0 : AVL T will do the deallocation node*/
                obj->m_tree.printKeyPVoid = prntVLintKeyAvlT;
                
            break;
            case 0x0d:/*not count redundant, dynamic array, floating-point */
                /* NODATA =0, only key */
                /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
                constructAvlTree((void*)&(obj->m_tree),0,"custom type 2",0,sizeof(vector_double)); 
                setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_tree),delVDoubleNodeRVSet,NULL,compVDouble4StRV);
                setDelKeyFlag(&(obj->m_tree),0); /*0 : AVL T will do the deallocation node*/
                obj->m_tree.printKeyPVoid = prntVDoubleKeyAvlT;
                
            break;
            case 0x0e:/*not count redundant,not dynamic array, vector long integer*/
            
                constructAvlTree((void*)&(obj->m_tree),2,"fixed arr",11,5);
                setDelKeyAndDelDataAndCompFnForAvlTree((void*)&(obj->m_tree),NULL,NULL,compVLint4NotCountDatAVLTFixedArrBIn); 
                /* initial */
                
                obj->m_buff = malloc(sizeof(struct mat2_2d));
                if(obj->m_buff != NULL)
                {
                    initiValInMt22d(obj->m_buff);
                    *((struct mat2_2d*)obj->m_buff) = newMt22d(100,dimenVal,sizeof(long int),3);
                    setParameterValofBinT((void*)&(obj->m_tree),3,obj->m_buff);
                }
                else
                {
                    printf("Error cannot initial set type :%lu, ln:%d file:%s \n",type,__LINE__,__FILE__);
                }
                obj->m_tree.printKeyPVoid = prntKeyTFixedArryBInIntNoCountStRV;
                
            break;
            case 0x0f:/* not count redundant,not dynamic array, floating-point */
                /* build in fixed node */
                constructAvlTree((void*)&(obj->m_tree),2,"fixed arr",11,5);
                setDelKeyAndDelDataAndCompFnForAvlTree((void*)&(obj->m_tree),NULL,NULL,compVDouble4NotCountDatAVLTFixedArrBIn); 
                /* initial */
                obj->m_buff = malloc(sizeof(struct mat2_2d));
                if(obj->m_buff != NULL)
                {
                    initiValInMt22d(obj->m_buff);
                    *((struct mat2_2d*)obj->m_buff) = newMt22d(100,dimenVal,sizeof(double),3);
                    setParameterValofBinT((void*)&(obj->m_tree),3,obj->m_buff);
                }
                else
                {
                    printf("Error cannot initial set type :%lu, ln:%d file:%s \n",type,__LINE__,__FILE__);
                }
                obj->m_tree.printKeyPVoid = prntKeyTFixedArryBInDoubleNoCountStRV;
                
            break;
            default: /* count redundant, dynamic array, vector long integer same 0 */
                /* Have data =1  */
                constructorRVSetVect(obj,0,dimenVal);
                
            break;
        }
    }
    else
    {
        if ( obj == NULL)
        {
            printf("obj is NULL in constructorRVSetVect, ln:%d, file:%s\n",__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
        if ((type&VECT_BIT) != VECT_BIT)
        {
            printf("It is not vector(type!=0x08):%lu, ln:%d, file:%s\n",type,__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
        
        if (dimenVal < 2)
        {
            printf("dimension value is not for vector value dim:%d, ln:%d, file:%s\n",dimenVal,__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
    }
}

 void destructorRVSet(struct rvSet *obj)
 {
    if(obj != NULL)
    {
        obj->m_numMember = 0;
        obj->m_type = 0;
        clearBinaryTree(&(obj->m_tree));
        if(obj->m_buff != NULL)
        {
            clearMt22d((struct mat2_2d*)(obj->m_buff));
            free(obj->m_buff);
            obj->m_buff = NULL;
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
unsigned long int isInRVSet(struct rvSet *obj,void *val)
{ 
    unsigned long int ret = 0;
    ret = (isInRVSetPrvt(obj,val) != NULL);
    return ret;
}
/***********************************************************************
* Method Name : unsigned long int added2RVSet(struct rvSet *obj,void *val)
* Parameter   : "obj" is a struct rvSet object.
*               "val" is the array 1 dimension variable.
* Return      :
* Description :
********************************************************************/
unsigned long int added2RVSet(struct rvSet *obj,const void *val)
{
    struct nodeFixedArr *nodeFArr = NULL;
    unsigned long int ret = 0;
    void *tmpP = NULL;
    void *tmpP2 = NULL;
    double *dV = 0;
    double *dV2 = 0;
    long int *lIV = 0;
    long int *lIV1 = 0;
    struct vector_lint *vLi = NULL;
    vector_double *vD = NULL;
    int index = 0;
    int num = 0;
    if ((obj != NULL) && (val != NULL))
    {
        tmpP =  isInRVSetPrvt(obj,val);
        // found redundant data and can get the redundant value
        if ((((obj->m_type) & NOT_COUNT_REDUNDANT_BIT) != NOT_COUNT_REDUNDANT_BIT) && (tmpP != NULL))
        {
            if (((obj->m_type) & NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT)
            {
                nodeFArr = (struct nodeFixedArr*)tmpP;
                if(nodeFArr->m_length > 1)
                {
                    if (((obj->m_type)&FLOATING_POINT_BIT) == FLOATING_POINT_BIT) 
                    {
                        dV = (double*)(nodeFArr->m_dat); 
                        dV[nodeFArr->m_length-1] = dV[nodeFArr->m_length-1] + 1.0;
                    }
                    else
                    {
                        lIV = (long int*)(nodeFArr->m_dat);
                        lIV[nodeFArr->m_length-1] = lIV[nodeFArr->m_length-1] + 1;
                    }
                }
                else
                {
                    printf("Error added2RVSet; nodeFArr->m_length:%u is failed to add ln:%d, File:%s\n",nodeFArr->m_length,__LINE__,__FILE__);
                }
                obj->m_numMember++;
            }
            else
            {
                tmpP2 = getDataFromAvlNode(tmpP);
                if (tmpP2 != NULL)
                {
                    *((long int*)tmpP2) = (*((long int*)tmpP2))+1;
                    obj->m_numMember++;
                    ret = 1;
                }
                else
                {
                
                    printf("there is data count in the node :%p ln:%d, fl:%s\n",tmpP,__LINE__,__FILE__);
                }
            }
        }
        else if ((obj->m_buff != NULL) && (tmpP == NULL) && (((obj->m_type)&NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT)) 
        {
            nodeFArr = (struct nodeFixedArr*)getDatNextMt22d((void*)(obj->m_buff));
            if (nodeFArr != NULL)
            {
                obj->m_numMember++;
                constructFixArrNodeBinary((void*)nodeFArr);
                if (((obj->m_type) & VECT_BIT) != VECT_BIT) 
                {
                    if (((obj->m_type)&FLOATING_POINT_BIT) == FLOATING_POINT_BIT) 
                    {
                        dV = (double*)(nodeFArr->m_dat); 
                        dV[0] = *((double*)val);
                    }
                    else
                    {
                        lIV = (long int*)(nodeFArr->m_dat);
                        lIV[0] = *((long int*)val);
                    }
                }
                else
                {
                    num = obj->m_dimen;
                    if (((obj->m_type) & FLOATING_POINT_BIT) == FLOATING_POINT_BIT) 
                    {
                        dV2 = (double*)val;
                        dV = (double*)(nodeFArr->m_dat);
                        for(index = 0 ;index < num ; index++)
                        {
                            dV[index] = dV2[index];
                        }
                    }
                    else
                    {
                        lIV = (long int*)(nodeFArr->m_dat);
                        lIV1 = (long int*)val;
                        for (index = 0 ;index < num ; index++)
                        {
                            lIV[index] = lIV1[index];
                        }
                    }
                }
                if (((obj->m_type) & NOT_COUNT_REDUNDANT_BIT) != NOT_COUNT_REDUNDANT_BIT)
                {
                    if (((obj->m_type) & FLOATING_POINT_BIT) == FLOATING_POINT_BIT) 
                    {
                        dV = (double*)(nodeFArr->m_dat); 
                        dV[nodeFArr->m_length-1] = 1.0;
                    }
                    else
                    {
                        lIV = (long int*)(nodeFArr->m_dat);
                        lIV[nodeFArr->m_length-1] = 1;
                    }
                }
                tmpP = obj->m_tree.insertFn(&(obj->m_tree),&(nodeFArr));
            }
            else
            {
                printf("new element of set error ln:%d , Fl:%s\n",__LINE__,__FILE__);
            }
        }
        else if (tmpP == NULL)
        {
            if (((obj->m_type) & VECT_BIT) != VECT_BIT) 
            {
                if (((obj->m_type) & FLOATING_POINT_BIT) != FLOATING_POINT_BIT)
                {
                    lIV = malloc(sizeof(long int));
                    if (lIV != NULL)
                    {
                        *lIV = *((long int*)val);
                        tmpP = obj->m_tree.insertFn(&(obj->m_tree),&lIV);
                    }
                    else
                    {
                        printf("Cannot add val to set, file:%s, ln:%d\n",__FILE__,__LINE__);
                    }
                }
                else
                {
                    dV = malloc(sizeof(double));
                    if (dV != NULL)
                    {
                        *dV = *((double*)val);
                        tmpP = obj->m_tree.insertFn(&(obj->m_tree),&dV);
                    }
                    else
                    {
                        printf("Cannot add val to set, file:%s, ln:%d\n",__FILE__,__LINE__);
                    }
                }
            }
            else /* Vector condition*/
            {
                if (((obj->m_type) & FLOATING_POINT_BIT) != FLOATING_POINT_BIT)
                {
                    vLi = malloc(sizeof(struct vector_lint));
                    if (vLi != NULL)
                    {
                        lIV = (long int*)val;
                        *vLi = new_vect_lint(obj->m_dimen);
                        setDat2VLint(vLi,lIV);
                        tmpP = obj->m_tree.insertFn(&(obj->m_tree),&vLi);
                    }
                    else
                    {
                        printf("Cannot add val to set, file:%s, ln:%d\n",__FILE__,__LINE__);
                    }
                }
                else
                {
                    vD = malloc(sizeof(vector_double));
                    if (vD != NULL)
                    {
                         dV =  (double*)val;
                         *vD = new_vector_double(obj->m_dimen);
                         num = obj->m_dimen;
                         if (vD->data != NULL)
                         {
                             for (index = 0;index < num;index++)
                             {
                                 vD->data[index] = dV[index];
                             }
                             tmpP = obj->m_tree.insertFn(&(obj->m_tree),&vD);
                         }
                         else
                         {
                             /* do nothing */
                         }
                    }
                    else
                    {
                        printf("Cannot add val to set, file:%s, ln:%d\n",__FILE__,__LINE__);
                    }
                }
                
            }
            /* add count redundant*/
            if ((((obj->m_type) & NOT_COUNT_REDUNDANT_BIT) != NOT_COUNT_REDUNDANT_BIT) && (tmpP != NULL))
            {
                tmpP2 =  malloc(sizeof(long int));
                *((long int*)tmpP2) = 1;
                setDataToAvlNode(tmpP,&tmpP2); 
                obj->m_numMember++;
            }
            else if (tmpP != NULL)
            {
                obj->m_numMember++;
            }
            else
            {
                printf("cannot add data,new pNode:%p Ln:%d, fl:%s\n",tmpP,__LINE__,__FILE__);
            }
        }
    }
    else
    {
        /* do nothing */
    }
    if (tmpP != NULL)
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}
/*
        m_type  
            1 st bit  : 0 long integer , 1 floating-point (double)
            2 nd bit  : 0 dynamic array, 1 not dynamic array
            3 rd bit  : 0 count redundant, 1 not count
            4 th bit  : 0 not vector, 1 vector
            5 th bit  : (spare)
            6 th bit  : (spare)
            7 th bit  : (spare)
            8 th bit  : (spare)
            9 th bit  : (void*) set, igore first bit to 8 th bit.
                                  Must provide compare method, (option): de-allocation and print method
 */
/* 1 = is remove all, 0 is count--, in case not redundant, opt is ignored. */
unsigned long int  removedValRVSet(struct rvSet *obj,void *val,unsigned long int opt)
{
    void *k = NULL;
    void *tmpP = NULL;
    void *tmpP2 = NULL;
    unsigned long int type = 0;
    unsigned long int ret = 0;
    unsigned long int tVal = 0;
    double *dV = 0;
    long int *lIV = 0;
    struct mat2_2d *m2Obj = NULL;
    struct nodeFixedArr *nodeFArr = NULL;
    struct nodeFixedArr4SpecialUsed aNode = {0,1,0,0,0,val,0}; 
    int dimension = 0;
    struct vector_lint vLiObj = {0,(long int *)val};
    vector_double vDoubObj = {0,(double*)val};
    if ((obj != NULL) && (val != NULL))
    {
        dimension = obj->m_dimen;
        vLiObj.m_lenght = dimension;
        vDoubObj.lenght = dimension;
        type = getTypeOfRVSet(obj);
        /* not dynamic array */
        if((type&NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT) 
        {
 
            k = (void*)&aNode;
            m2Obj = (struct mat2_2d*)(obj->m_tree).parameter3;
            if(obj->m_tree.isData > 1)
            {
                aNode.m_length = m2Obj->m_dat[0]->m_col;
            }
            else
            {
                /* do nothing */
            }
            nodeFArr =  (struct nodeFixedArr*)isInRVSetPrvt(obj,val);
            /* opt == 1 is removed all. */
            if (((opt == 1) || ((type&NOT_COUNT_REDUNDANT_BIT) == NOT_COUNT_REDUNDANT_BIT))&&(nodeFArr != NULL))
            {
                if ((type&NOT_COUNT_REDUNDANT_BIT) != NOT_COUNT_REDUNDANT_BIT)
                {
                        if (((obj->m_type)&FLOATING_POINT_BIT) == FLOATING_POINT_BIT) 
                        {
                            dV = (double*)(nodeFArr->m_dat);
                            obj->m_numMember = obj->m_numMember - (unsigned long int)dV[dimension-1];
                        }
                        else if (((obj->m_type)&FLOATING_POINT_BIT) != FLOATING_POINT_BIT) 
                        {
                            lIV = (long int*)(nodeFArr->m_dat); 
                            obj->m_numMember = obj->m_numMember - (unsigned long int)lIV[dimension-1];
                        }
                }
                else
                {
                    obj->m_numMember = obj->m_numMember - 1;
                }
                ret = (unsigned long int)removeAvlTreeNodeByKey(&(obj->m_tree),(void*)&k);
            }
            else if (((type&NOT_COUNT_REDUNDANT_BIT) != NOT_COUNT_REDUNDANT_BIT))
            {
                if(nodeFArr != NULL)
                {
                    dimension = nodeFArr->m_length;
                    if (((obj->m_type)&FLOATING_POINT_BIT) == FLOATING_POINT_BIT) 
                    {
                        dV = (double*)(nodeFArr->m_dat); 
                        dV[dimension-1] = dV[dimension-1]-1.0;
                        if(dV[dimension-1] <= 0)
                        {
                            ret = (unsigned long int)removeAvlTreeNodeByKey(&(obj->m_tree),(void*)&k);
                        }
                        else
                        {
                            ret = 1;
                        }
                        obj->m_numMember = obj->m_numMember - 1;
                    }
                    else if (((obj->m_type)&FLOATING_POINT_BIT) != FLOATING_POINT_BIT) 
                    {
                        lIV = (long int*)(nodeFArr->m_dat); 
                        lIV[dimension-1] = lIV[dimension-1] -1;
                        if(lIV[dimension-1] <= 0)
                        {
                            ret = (unsigned long int)removeAvlTreeNodeByKey(&(obj->m_tree),(void*)&k);
                        }
                        else
                        {
                            ret = 1;
                        }
                        obj->m_numMember = obj->m_numMember - 1;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                else
                {
                    ret = 0;/*
                    printf("There is no this data to be removed to this set:%p, Ln:%d, F:%s\n",obj,__LINE__,__FILE__);
                    */
                }
            }
        }
        else/* dynamic array */
        {
            /* opt == 1 is removed all. */
            if ((opt == 1)||( (type & NOT_COUNT_REDUNDANT_BIT) == NOT_COUNT_REDUNDANT_BIT))
            {
                /* not cound redundant case */
                if ((type&NOT_COUNT_REDUNDANT_BIT) == NOT_COUNT_REDUNDANT_BIT)
                {
                    ret = 1;
                    tVal = 1;
                }
                else /* redundant case */
                {
                    tmpP =  isInRVSetPrvt(obj,val);
                    tmpP2 = getDataFromAvlNode(tmpP);
                    if (tmpP2 != NULL)
                    {
                        tVal = (unsigned long int)(*((long int*)tmpP2));
                        ret = 1;
                    }
                    else
                    {
                        ret = 0;
                    }
                }
                if (ret == 1)
                {
                    if ((type&VECT_BIT) == VECT_BIT)
                    {
                        if ((type&FLOATING_POINT_BIT) == FLOATING_POINT_BIT)
                        {
                            k = (void*)&vDoubObj;
                        }
                        else
                        {
                            k = (void*)&vLiObj;
                        }
                        ret = (unsigned long int)removeAvlTreeNodeByKey(&(obj->m_tree),(void*)&k);
                    }
                    else
                    {
                        ret = (unsigned long int)removeAvlTreeNodeByKey(&(obj->m_tree),&val);
                    }
                    if (ret == 1  )
                    {
                        obj->m_numMember = obj->m_numMember - tVal;
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
            else if (opt == 0)
            {
                tmpP =  isInRVSetPrvt(obj,val);
                tmpP2 = getDataFromAvlNode(tmpP);
                if(tmpP2 != NULL)
                {
                    tVal = (unsigned long int)(*((long int*)tmpP2));
                    if(tVal == 1)
                    {
                        if ((type&VECT_BIT) == VECT_BIT)
                        {
                            if ((type&FLOATING_POINT_BIT) == FLOATING_POINT_BIT)
                            {
                                k = (void*)&vDoubObj;
                            }
                            else
                            {
                                k = (void*)&vLiObj;
                            }
                            ret = (unsigned long int)removeAvlTreeNodeByKey(&(obj->m_tree),(void*)&k);
                        }
                        else
                        {
                            ret = (unsigned long int)removeAvlTreeNodeByKey(&(obj->m_tree),&val);
                        }
                        obj->m_numMember = obj->m_numMember - 1;
                    }
                    else
                    {
                        obj->m_numMember = obj->m_numMember - 1;
                        (*((long int*)tmpP2))--;
                        ret = 1;
                    }
                }
                else
                {
                    ret = 0;
                }
            }
            else
            {
                printf("opt val error:%lu, ln:%d, File:%s\n",opt,__LINE__,__FILE__);
            }
        }
    }
    else
    {
        printf("paramter is failed, obj:%p, val:%p, ln:%d, file:%s \n",obj,val,__LINE__,__FILE__);
    }
    return ret;
}
unsigned long int  numEleRVSet(struct rvSet *obj)
{
    if(obj != NULL)
    {
        return obj->m_numMember;
    }
    else
    {
        /* do nothing */
    }
    return 0;
    
}
unsigned long int numEleRVSetNotRedunt(struct rvSet *obj)
{
    unsigned long int tmp1 = 0;
    if (obj != NULL)
    {
        tmp1 = (unsigned long int)getNumBinaryNodeOfTree(&(obj->m_tree));
        
      /*  printf("num member:%lu, count in tree:%lu \n ",obj->m_numMember,tmp1); */
        
    }
    else
    {
        /* do nothing */
    }
    return tmp1;
    
}
unsigned long int  merged2ThisRvSet(struct rvSet *lhs,struct rvSet *rhs)
{
    if ((lhs != NULL) && (rhs != NULL))
    {
    }
    else
    {
        /* do nothing */
    }
    return 0;
}
void printRvSet(struct rvSet *obj)
{
    char buff[300];
    buff[0] ='\0';
    void *tmp = NULL;
    int numNode = 0;
    if (obj != NULL)
    {
        numNode = countAllNodesInBT(&(obj->m_tree));
        printf("num mem:%lu, in tree:%d\n",obj->m_numMember,numNode);
        tmp = obj->m_tree.parameter3;
        obj->m_tree.parameter3 = buff;
        obj->m_tree.printTree(&(obj->m_tree),0);
        obj->m_tree.parameter3 = tmp;
    }
    else
    {
        /* do nothing */
    }
}

void printLinearByIndexSet(struct rvSet *obj)
{
    unsigned long int index = 0;
    unsigned long int index2 = 0;
    unsigned long int num = 0;
    unsigned long int num2 = 0;
    unsigned long int type = 0;
    void *tmpV = NULL;
    num = numEleRVSetNotRedunt(obj);
    num2 = numDimenVSet(obj);
    type = obj->m_type;
    if ((type&NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT)
    {
        for (index = 0;index < num ;index++)
        {
                tmpV = getDatInRVSetByIndex(obj,index);
                if ((type&NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT)
                {
                    if((type&VECT_BIT) == VECT_BIT)
                    {
                        if((type&FLOATING_POINT_BIT) == FLOATING_POINT_BIT)
                        {
                            printf("[");
                            for (index2 = 0;index2 < num2;index2++)
                            {
                                printf("%f ",((double*)tmpV)[index2]);
                            }
                            printf("]");
                        }
                        else
                        {
                            printf("[");
                            for (index2 = 0;index2 < num2;index2++)
                            {
                                printf("%ld ",((long int*)tmpV)[index2]);
                            }
                            printf("]");
                        }
                    }
                    else
                    {
                        if((type&FLOATING_POINT_BIT) == FLOATING_POINT_BIT)
                        {
                            printf("%f ",*((double*)tmpV));
                        }
                        else
                        {
                            printf("%ld ",*((long int*)tmpV));
                        }
                    }
                }
                else
                {
                    /* do nothing */
                }
        }
        printf("\n");
    }
    else
    {
        printf("=== Error printLinearByIndexSet doesn't provide in Dynamic array, Ln:%d, Fl:%s\n",__LINE__,__FILE__);
    }
}
/* private method */
void delKeyNode4AvlT(void *obj,void *key)
{
    void **p = (void**)key;
    if (*p != NULL)
    {
        free(*p);
        *p = NULL;
    }
    else
    {
        /* do nothing */
    }
}
void delDatNode4AvlT(void *obj,void *dat)
{
    void **p = (void**)dat;
    if (*p != NULL)
    {
        free(*p);
        *p = NULL;
    }
    else
    {
        /* do nothing */
    }
}

void prntLintKeyAvlT(void* key,char* buf)
{
    if ((key != NULL ) && (buf != NULL))
    {
        sprintf(buf,"%ld",*((long int*)key));
    }
    else
    {
        /* do nothing */
    }
}

void prntVLintKeyAvlT(void* key,char* buf)
{
    struct vector_lint *Vtmp = (struct vector_lint*)key;
    int index = 0;
    int num = 0;
    if ((Vtmp != NULL ) && (buf != NULL))
    {
        num = Vtmp->m_lenght;
        sprintf(buf,"[");
        for (index = 0;index < num ;index++)
        {
            sprintf(buf,"%s %ld",buf,Vtmp->m_data[index]);
        }
        sprintf(buf,"%s]",buf);
        
    }
    else
    {
        /* do nothing */
    }
}
void prntDoubleKeyAvlT(void* key,char* buf)
{
    if ((key != NULL ) && (buf != NULL))
    {
        sprintf(buf,"%f",*((double*)key));
    }
    else
    {
        /* do nothing */
    }
} 
void prntVDoubleKeyAvlT(void* key,char* buf)
{
    int index = 0;
    int num = 0;
    vector_double *VDtmp = key;
    if ((VDtmp != NULL ) && (buf != NULL))
    {
        num = VDtmp->lenght;
        sprintf(buf,"[");
        for (index = 0;index < num;index++)
        {
            sprintf(buf,"%s %f",buf,VDtmp->data[index]);
        }
        sprintf(buf,"%s]",buf);
    }
    else
    {
        /* do nothing */
    }
} 

int compDouble4StRV(const void *a,const void *b)
{
    int res = 0;
    double **aa = (double**)a;
    double **bb = (double**)b;
    if ((aa!=NULL) && (bb != NULL))
    {
        if ((*aa != NULL) && (*bb != NULL))
        {/*
    printf("compare a:%f, b:%f\n",**aa,**bb);*/
            if (**aa == **bb)
            {
                res =EQUAL_DEFINE;
            }
            else if (**aa > **bb)
            {
                res =MORE_DEFINE;
            }
            else if (**aa < **bb)
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
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int compLongInt4StRV(const void *a,const void *b)
{
    int res = 0;
    long int **aa = (long int**)a;
    long int **bb = (long int**)b;
    if ((aa != NULL) && (bb != NULL))
    {
        if ((*aa!=NULL)&&(*bb!=NULL))
        {/*
    printf("compare a:%ld, b:%ld\n",**aa,**bb);*/
            if (**aa == **bb)
            {
                res =EQUAL_DEFINE;
            }
            else if (**aa > **bb)
            {
                res =MORE_DEFINE;
            }
            else if (**aa < **bb)
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
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int compLint4AVLTFixedArrBIn(const void* a,const void *b)
{ 
    int res = UN_DEFINE;
    int index = 0;
    int num = 0;
    long int *lIV1 = NULL;
    long int *lIV2 = NULL;
    struct nodeFixedArr **va = NULL;
    struct nodeFixedArr **vb = NULL;
    if ((a == NULL)||(b == NULL))
    {
        printf("Failed to compare \n");
        /* do nothing */
    }
    else if ((*((struct nodeFixedArr**)a) != NULL) && (*((struct nodeFixedArr**)b)!=NULL))
    {
        va = ((struct nodeFixedArr**)a);
        vb = ((struct nodeFixedArr**)b);
        if (((*va)->m_length >= 1) && ((*vb)->m_length >= 1))
        {
            num = 1;
        }
        else
        {
            num = 0;
        }
        res = EQUAL_DEFINE;
        lIV1 = (long int*)((*va)->m_dat);
        lIV2 = (long int*)((*vb)->m_dat);
        for(index=0;index<num;index++)
        {
         /*    printf("[%ld %ld] \n",lIV1[index],lIV2[index]); */
            if(lIV1[index]> lIV2[index])
            {
                index=num;
                res = MORE_DEFINE; 
            }
            else if(lIV1[index]< lIV2[index])
            {
                index=num;
                res = LESS_DEFINE; 
            }
            else
            {
                /* do nothing */
            }
        }
        if ((res ==EQUAL_DEFINE)&&((*va)->m_length == (*vb)->m_length))
        {
            /* do noting */
        }
        else if ((res ==EQUAL_DEFINE)&&((*va)->m_length == num)&&((*vb)->m_length>num))
        {
            res = LESS_DEFINE;
        } 
        else if ((res ==EQUAL_DEFINE) && ((*vb)->m_length == num) && ((*va)->m_length > num))
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

int compVLint4CountDatAVLTFixedArrBIn(const void* a,const void *b)
{ 
    int res = UN_DEFINE;
    int index = 0;
    int num = 0;
    long int *lIV1 = NULL;
    long int *lIV2 = NULL;
    struct nodeFixedArr **va = NULL;
    struct nodeFixedArr **vb = NULL;
    if ((a == NULL)||(b == NULL))
    {
        printf("Failed to compare \n");
        /* do nothing */
    }
    else if ((*((struct nodeFixedArr**)a) != NULL) && (*((struct nodeFixedArr**)b)!=NULL))
    {
        va = ((struct nodeFixedArr**)a);
        vb = ((struct nodeFixedArr**)b);
        if (((*va)->m_length >= 1) && ((*vb)->m_length >= 1))
        {
            if((*va)->m_length >= (*vb)->m_length)
            {
                num = (*va)->m_length -1;
            }
            else
            {
                num = (*vb)->m_length -1;
            }
        }
        else
        {
            num = 0;
        }
        res = EQUAL_DEFINE;
        lIV1 = (long int*)((*va)->m_dat);
        lIV2 = (long int*)((*vb)->m_dat);
        for(index = 0;index < num;index++)
        {
         /*    printf("[%ld %ld] \n",lIV1[index],lIV2[index]); */
            if(lIV1[index] > lIV2[index])
            {
                index=num;
                res = MORE_DEFINE; 
            }
            else if (lIV1[index] < lIV2[index])
            {
                index=num;
                res = LESS_DEFINE; 
            }
            else
            {
                /* do nothing */
            }
        }
        /*
        if ((res == EQUAL_DEFINE)&&((*va)->m_length == (*vb)->m_length))
        {
            
        }
        else if ((res == EQUAL_DEFINE) && ((*va)->m_length < (*vb)->m_length))
        {
            res = LESS_DEFINE;
        } 
        else if ((res == EQUAL_DEFINE) && ((*vb)->m_length < (*va)->m_length))
        {
            res = MORE_DEFINE;
        }
        else
        {
            
        }
        */
    }
    else
    {
        printf("a:%p, b:%p\n",*((struct nodeFixedArr**)a),*((struct nodeFixedArr**)b));
        printf("cannot compare ln:%d :fl:%s\n",__LINE__,__FILE__);
        /* do nothing */
    }
    return res;
}

int compVLint4NotCountDatAVLTFixedArrBIn(const void* a,const void *b)
{ 
    int res = UN_DEFINE;
    int index = 0;
    int num = 0;
    long int *lIV1 = NULL;
    long int *lIV2 = NULL;
    struct nodeFixedArr **va = NULL;
    struct nodeFixedArr **vb = NULL;
    if ((a == NULL) || (b == NULL))
    {
        printf("Failed to compare in compVLint4NotCountDatAVLTFixedArrBIn method, ln:%d, file:%s \n",__LINE__,__FILE__);
    }
    else if ((*((struct nodeFixedArr**)a) != NULL) && (*((struct nodeFixedArr**)b) != NULL))
    {
        va = ((struct nodeFixedArr**)a);
        vb = ((struct nodeFixedArr**)b);
        if ((*va)->m_length > (*vb)->m_length)
        {
            num = (*vb)->m_length;
        }
        else
        {
            num = (*va)->m_length;
        }
        res = EQUAL_DEFINE;
        lIV1 = (long int*)((*va)->m_dat);
        lIV2 = (long int*)((*vb)->m_dat);
        for (index = 0;index < num;index++)
        {
         /*    printf("[%ld %ld] \n",lIV1[index],lIV2[index]); */
            if (lIV1[index] > lIV2[index])
            {
                index=num;
                res = MORE_DEFINE; 
            }
            else if (lIV1[index] < lIV2[index])
            {
                index=num;
                res = LESS_DEFINE; 
            }
            else
            {
                /* do nothing */
            }
        }
        /*
        if ((res == EQUAL_DEFINE) && ((*va)->m_length == (*vb)->m_length))
        {
            
        }
        else if ((res ==EQUAL_DEFINE) && ((*va)->m_length < (*vb)->m_length))
        {
            res = LESS_DEFINE;
        } 
        else if ((res == EQUAL_DEFINE) && ((*vb)->m_length < (*va)->m_length))
        {
            res = MORE_DEFINE;
        }
        else
        {
            
        }
        */
    }
    else
    {
        printf("a:%p, b:%p\n",*((struct nodeFixedArr**)a),*((struct nodeFixedArr**)b));
        printf("cannot compare ln:%d :fl:%s\n",__LINE__,__FILE__);
        /* do nothing */
    }
    return res;
}

int compVDouble4CountDatAVLTFixedArrBIn(const void* a,const void *b)
{ 
    int res = UN_DEFINE;
    int index = 0;
    int num = 0;
    double *douTmp1 = NULL;
    double *douTmp2 = NULL;
    struct nodeFixedArr **va = NULL;
    struct nodeFixedArr **vb = NULL;
    if ((a == NULL)|| (b == NULL))
    {
        printf("Failed to compare \n");
        /* do nothing */
    }
    else if ((*((struct nodeFixedArr**)a) != NULL) && (*((struct nodeFixedArr**)b) != NULL))
    {
        va = ((struct nodeFixedArr**)a);
        vb = ((struct nodeFixedArr**)b);
        if (((*va)->m_length >= 1) && ((*vb)->m_length >= 1))
        {
            if((*va)->m_length >= (*vb)->m_length)
            {
                num = (*va)->m_length -1;
            }
            else
            {
                num = (*vb)->m_length -1;
            }
            
        }
        else
        {
            num = 0;
        }
        res = EQUAL_DEFINE;
        douTmp1 = (double*)((*va)->m_dat);
        douTmp2 = (double*)((*vb)->m_dat);
        for (index = 0;index < num;index++)
        {
         /*    printf("[%ld %ld] \n",lIV1[index],lIV2[index]); */
            if (douTmp1[index] > douTmp2[index])
            {
                index = num;
                res = MORE_DEFINE; 
            }
            else if (douTmp1[index] < douTmp2[index])
            {
                index = num;
                res = LESS_DEFINE; 
            }
            else
            {
                /* do nothing */
            }
        }/*
        if ((res == EQUAL_DEFINE) && ((*va)->m_length == (*vb)->m_length))
        { 
        }
        else if ((res ==EQUAL_DEFINE) && ((*va)->m_length < (*vb)->m_length))
        {
            res = LESS_DEFINE;
        } 
        else if ((res == EQUAL_DEFINE) && ((*vb)->m_length < (*va)->m_length))
        {
            res = MORE_DEFINE;
        }
        else
        {
           
        }
        */
    }
    else
    {
        printf("a:%p, b:%p\n",*((struct nodeFixedArr**)a),*((struct nodeFixedArr**)b));
        printf("cannot compare ln:%d :fl:%s\n",__LINE__,__FILE__);
        /* do nothing */
    }
    return res;
}

int compVDouble4NotCountDatAVLTFixedArrBIn(const void* a,const void *b)
{ 
    int res = UN_DEFINE;
    int index = 0;
    int num = 0;
    double *douTmp1 = NULL;
    double *douTmp2 = NULL;
    struct nodeFixedArr **va = NULL;
    struct nodeFixedArr **vb = NULL;
    if ((a == NULL) || (b == NULL))
    {
        printf("Failed to compare \n");
        /* do nothing */
    }
    else if ((*((struct nodeFixedArr**)a) != NULL) && (*((struct nodeFixedArr**)b) != NULL))
    {
        va = ((struct nodeFixedArr**)a);
        vb = ((struct nodeFixedArr**)b);
        if ((*va)->m_length > (*vb)->m_length)
        {
            num = (*vb)->m_length;
        }
        else
        {
            num = (*va)->m_length;
        }
        res = EQUAL_DEFINE;
        douTmp1 = (double*)((*va)->m_dat);
        douTmp2 = (double*)((*vb)->m_dat);
        for (index = 0;index < num;index++)
        {
         /*    printf("[%ld %ld] \n",lIV1[index],lIV2[index]); */
            if (douTmp1[index] > douTmp2[index])
            {
                index = num;
                res = MORE_DEFINE; 
            }
            else if (douTmp1[index] < douTmp2[index])
            {
                index=num;
                res = LESS_DEFINE; 
            }
            else
            {
                /* do nothing */
            }
        }
        if ((res == EQUAL_DEFINE) && ((*va)->m_length == (*vb)->m_length))
        {
            /* do noting */
        }
        else if ((res == EQUAL_DEFINE) && ((*va)->m_length < (*vb)->m_length))
        {
            res = LESS_DEFINE;
        } 
        else if ((res == EQUAL_DEFINE) && ((*vb)->m_length < (*va)->m_length))
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


int compVLint4StRV(const void *a,const void *b)
{
    int res = UN_DEFINE;
    unsigned int index =0;
    unsigned int num =0;
    struct vector_lint **va=NULL;
    struct vector_lint **vb=NULL;
    if ((a == NULL) || (b == NULL))
    {
        printf("Error compVLint4StRV Node NULL, a:%p, b:%p, ln:%d, File:%s\n",a,b,__LINE__,__FILE__);
    }
    else if ((*((struct vector_lint**)a) != NULL) && (*((struct vector_lint**)b) != NULL))
    {
        va = ((struct vector_lint**)a);
        vb = ((struct vector_lint**)b);
        if((*va)->m_lenght > (*vb)->m_lenght)
        {
            num = (*vb)->m_lenght;
        }
        else
        {
            num = (*va)->m_lenght;
        }
        res = EQUAL_DEFINE;
        for (index = 0;index < num;index++)
        {
            if ((*va)->m_data[index] > (*vb)->m_data[index])
            {
                index = num;
                res = MORE_DEFINE;
            }
            else if ((*va)->m_data[index] < (*vb)->m_data[index])
            {
                index = num;
                res = LESS_DEFINE;
            }
            else
            {
                /* do nothing */
            }
        }
        if ((res == EQUAL_DEFINE) && ((*va)->m_lenght == (*vb)->m_lenght))
        {
            /* do noting */
        }
        else if ((res == EQUAL_DEFINE) && ((*va)->m_lenght == num)&&((*vb)->m_lenght > num))
        {
            res = LESS_DEFINE;
        } 
        else if ((res == EQUAL_DEFINE) && ((*vb)->m_lenght == num) && ((*va)->m_lenght > num))
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

int compVDouble4StRV(const void *a,const void *b)
{
    int res = UN_DEFINE;
    int index = 0;
    int num = 0;
    vector_double **va = NULL;
    vector_double **vb = NULL;
    double *tmpDouble = NULL;
    if ((a == NULL) || (b == NULL))
    {
        printf("Error ComVDouble Node NULL, a:%p, b:%p, ln:%d, File:%s\n",a,b,__LINE__,__FILE__);
    }
    else if ((*((vector_double**)a)!=NULL)&&(*((vector_double**)b)!=NULL))
    {
        va = ((vector_double**)a);
        vb = ((vector_double**)b);
        if ((*va)->lenght > (*vb)->lenght)
        {
            num = (*vb)->lenght;
        }
        else
        {
            num =(*va)->lenght;
        }
        res = EQUAL_DEFINE;
        tmpDouble = (*vb)->data;
        for (index = 0;index < num;index++)
        {
            if( (*va)->data[index] > tmpDouble[index])
            {
                index=num;
                res = MORE_DEFINE;
            }
            else if ((*va)->data[index] < (*vb)->data[index])
            {
                index = num;
                res = LESS_DEFINE;
            }
            else
            {
                /* do nothing */
            }
        }
        if ((res == EQUAL_DEFINE) && ((*va)->lenght == (*vb)->lenght))
        {
            /* do noting */
        }
        else if ((res == EQUAL_DEFINE) && ((*va)->lenght == num) && ((*vb)->lenght > num))
        {
            res = LESS_DEFINE;
        } 
        else if ((res == EQUAL_DEFINE) && ((*vb)->lenght == num) && ((*va)->lenght > num))
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

int compDouble4AVLTFixedArrBIn(const void* a,const void *b)
{ 
    int res = UN_DEFINE;
    int index = 0;
    int num = 0;
    double *dV1 = NULL;
    double *dV2 = NULL;
    struct nodeFixedArr **va = NULL;
    struct nodeFixedArr **vb = NULL;
    if ((a == NULL)||(b == NULL))
    {
        printf("Failed to compare \n");
        /* do nothing */
    }
    else if ((*((struct nodeFixedArr**)a) != NULL) && (*((struct nodeFixedArr**)b) != NULL))
    {
        va = ((struct nodeFixedArr**)a);
        vb = ((struct nodeFixedArr**)b);
        if (((*va)->m_length >=1) && ((*vb)->m_length >=1))
        {
            num = 1;
        }
        else
        {
            num = 0;
        }
        res = EQUAL_DEFINE;
        dV1 = (double*)((*va)->m_dat);
        dV2 = (double*)((*vb)->m_dat);
        for (index = 0;index < num;index++)
        {
           /*  printf("[%f %f] \n",dV1[index],dV2[index]); */
            if (dV1[index] > dV2[index])
            {
                index=num;
                res = MORE_DEFINE; 
            }
            else if (dV1[index] < dV2[index])
            {
                index=num;
                res = LESS_DEFINE; 
            }
            else
            {
                /* do nothing */
            }
        }
        if((res == EQUAL_DEFINE) && ((*va)->m_length == (*vb)->m_length))
        {
            /* do noting */
        }
        else if ((res == EQUAL_DEFINE)&&((*va)->m_length == num) && ((*vb)->m_length>num))
        {
            res = LESS_DEFINE;
        } 
        else if ((res == EQUAL_DEFINE) && ((*vb)->m_length == num) && ((*va)->m_length>num))
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

void delVLintNodeRVSet(void *obj,void *key)
{
    void **p = (void**)key;
    if (*p != NULL)
    {
        del_vect_lint((struct vector_lint*)(*p));
        free(*p);
        *p = NULL;
    }
    else
    {
        /* do nothing */
    }
}

void delVLintCountDatRVSet(void *obj,void *data)
{
    long int **liTmp = (long int**)data;
    if (liTmp != NULL)
    {
        if (*liTmp !=NULL)
        {
            free(*liTmp);
            *liTmp = NULL;
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

void delVDoubleNodeRVSet(void *obj,void *key)
{
    void **p = (void**)key;
    if (*p != NULL)
    {
        delete_vector_double((vector_double*)(*p));
        free(*p);
        *p = NULL;
    }
    else
    {
        /* do nothing */
    }
}


void* isInRVSetPrvt(struct rvSet *obj,const void *val)
{
    void *k = NULL;
    void *retP = NULL;
    struct mat2_2d *m2Obj = NULL;
    struct nodeFixedArr4SpecialUsed aNode = {0,1,0,0,0,val,0}; 
    struct vector_lint vLiObj = {0,(long int *)val};
    vector_double vDoubObj = {0,(double*)val};
    int dimension = 0;
    unsigned long int type = 0;
    if ((obj != NULL) && (val != NULL))
    {
        type = getTypeOfRVSet(obj);
        dimension = obj->m_dimen;
        vDoubObj.lenght = dimension;
        vLiObj.m_lenght =(unsigned int)dimension;
        /* not dynamic array */
        if ((type & NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT) 
        {
            k = (void*)&aNode;
            aNode.m_length = (unsigned int)(obj->m_dimen);
            if (obj->m_tree.isData > 1)
            {
                m2Obj = (struct mat2_2d*)(obj->m_tree).parameter3;
                aNode.m_length = m2Obj->m_dat[0]->m_col;
            }
            else
            {
                /* do nothing */
            }
            retP = searchDataInBinaryTree(&(obj->m_tree),&k);
        }
        else/* dynamic array */
        {
            if((type & VECT_BIT) == VECT_BIT)
            {
                if((type & FLOATING_POINT_BIT) == FLOATING_POINT_BIT)
                {
                    k = (void*)&vDoubObj;
                }
                else
                {
                    k = (void*)&vLiObj;
                }
                retP = searchDataInBinaryTree(&(obj->m_tree),&k);
            }
            else
            {
                retP = searchDataInBinaryTree(&(obj->m_tree),&val);
            }
        }
    }
    else
    {
        printf("paramter is failed, obj:%p, val:%p, ln:%d, file:%s \n",obj,val,__LINE__,__FILE__);
    }
    return retP;
}
void* getDatInRVSetByIndex(struct rvSet *obj,int index)
{
    void *ret = NULL;
    unsigned int index2 = 0;
    unsigned int tmp = 0;
    struct nodeFixedArr *nodeFArr = NULL;
    struct mat2_2d *obj2 = NULL;
    
    if ((obj != NULL) && (index >= 0))
    {
        if ((obj->m_type&NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT)
        {
            obj2 = (struct mat2_2d*)(obj->m_buff);
            if (obj2 != NULL)
            {
                tmp = index; 
                if (convertIndex2IdSegAndOfSt4Mt22d(obj2,index,&index2,&tmp) == 1)
                {
                    nodeFArr = go2ReadDatMt22d(obj2,index2,tmp);
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
            printf("Cannot use getDatInRVSetByIndex method, it is for Not dynamic arry, Ln:%d, Fl:%s\n ",__LINE__,__FILE__);
        }
        if (nodeFArr != NULL)
        {
            if (((obj->m_type)&FLOATING_POINT_BIT) == FLOATING_POINT_BIT)
            {
                ret = (void*)&(((double*)(nodeFArr->m_dat))[0]); 
            }
            else
            {
                ret = (void*)&(((long int*)(nodeFArr->m_dat))[0]); 
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
    return ret;
}

unsigned long int numDimenVSet(struct rvSet *obj)
{
    unsigned long int tmp = 0;
    if (obj != NULL)
    {
        tmp = (unsigned long int)(obj->m_dimen);
    }
    else
    {
        printf("error rvSet obj is null in numDimenVSet method, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    return tmp;
}
//jui1
int clearMemberOutInRVSet(struct rvSet *obj)
{
    int type = 0;
    int ret = (obj != NULL);
    if (ret == 1)
    {
        type = obj->m_type;
        if ((type&NOT_DYNAMIC_ARR_BIT) == 0x02)
        {
            obj->m_numMember = 0;
            ret = forcetTRoot2NullAvLT(&(obj->m_tree));
            ret = (resetDatStoreInMt22d((struct mat2_2d*)(obj->m_buff)) && (ret == 1));
        }
        else
        {
            printf ("Error(1) in clearMemberOutInRVSet, cannot use this method for dynamic method ln:%d, file:%s\n",__LINE__,__FILE__);
        }
    }
    else
    {
        printf("Error in clearMemberOutInRVSet, obj is NULL, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    return ret;
}

void* getNxtDatInRVSet(struct rvSet *obj)
{
    void *ret = NULL;
    struct nodeFixedArr *nodeFArr = NULL;
    if(obj != NULL)
    {
        if((obj->m_type&NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT)
        {
            if(obj->m_buff != NULL)
            {
                nodeFArr =  (struct nodeFixedArr*)readDatNextMt22d((struct mat2_2d*)(obj->m_buff));
                if(nodeFArr != NULL)
                {
                    if((obj->m_type&FLOATING_POINT_BIT) == FLOATING_POINT_BIT)
                    {
                        ret = (void*)&(((double*)(nodeFArr->m_dat))[0]); 
                    }
                    else
                    {
                        ret = (void*)&(((long int*)(nodeFArr->m_dat))[0]); 
                    }
                }
                else
                {
                    printf(" Error(1) in getNxtDatInRVSet, cannot get the dat in Set, ln:%d, file:%s\n",__LINE__,__FILE__);
                }
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            printf("Cannot use getNxtDatInRVSet method, it is for Not dynamic arry, Ln:%d, Fl:%s\n ",__LINE__,__FILE__);
        }
     
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
void resetGetNxtDat(struct rvSet *obj)
{
    if(obj != NULL)
    {
        if((obj->m_type&NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT)
        {
            if(obj->m_buff != NULL)
            {
                resetReaderDatMt22d((struct mat2_2d*)(obj->m_buff));
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            printf("Cannot use resetGetNxtDat method, it is for Not dynamic arry, Ln:%d, Fl:%s\n ",__LINE__,__FILE__);
        }
     
    }
    else
    {
        /* do nothing */
    }
}

void pushStateNxtDat(struct rvSet *obj, unsigned int *segId,unsigned int *id)
{
    unsigned int ret = 0;
    if((obj != NULL) && (segId != NULL) && (id != NULL))
    {
        ret = ((obj->m_type&NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT)+ (2*((obj->m_type&NOT_DYNAMIC_ARR_BIT) != NOT_DYNAMIC_ARR_BIT));
    }
    else
    {
        printf("== Error (obj,%p), (segId,%p) or (id,%p) point is NULL, ln:%d, fl:%s \n",obj,segId,id,__LINE__,__FILE__);
    }
    if (ret == 1)
    {
        getCurSegIdMt22d(((struct mat2_2d*)obj->m_buff),segId,id);
    }
    else if (ret == 2)
    {
        printf("This feature is used for Dynamic arr, ln:%d , File:%s\n",__LINE__,__FILE__);
    }
    else
    {
        /* do nothing */
    }
}
int isCanPopStateNxtDat(struct rvSet *obj,const unsigned int segId,const unsigned int id)
{
    unsigned int ret = 0;
    if(obj != NULL)
    {
        ret = ((obj->m_type&NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT)+ (2*((obj->m_type&NOT_DYNAMIC_ARR_BIT) != NOT_DYNAMIC_ARR_BIT));
    }
    else
    {
        printf("== Error obj point is NULL, ln:%d, fl:%s \n",__LINE__,__FILE__);
    }
    if (ret == 1)
    {
        ret = isCanSetCurSegIdMt22d(((struct mat2_2d*)obj->m_buff),segId,id);
    }
    else if (ret == 2)
    {
        printf("This feature is used for Dynamic arr, ln:%d , File:%s\n",__LINE__,__FILE__);
        ret = 0;
    }
    else
    {
        /* do nothing */
    }
    return (int)ret;
}

int popStateNxtDat(struct rvSet *obj,const unsigned int segId,const unsigned int id)
{
    unsigned int ret = 0;
    if(obj != NULL)
    {
        ret = ((obj->m_type&NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT)+ (2*((obj->m_type&NOT_DYNAMIC_ARR_BIT) != NOT_DYNAMIC_ARR_BIT));
    }
    else
    {
        printf("== Error obj point is NULL, ln:%d, fl:%s \n",__LINE__,__FILE__);
    }
    if (ret == 1)
    {
        ret = setCurSegIdMt22d(((struct mat2_2d*)obj->m_buff),segId,id);
    }
    else if (ret == 2)
    {
        printf("This feature is used for Dynamic arr, ln:%d , File:%s\n",__LINE__,__FILE__);
        ret = 0;
    }
    else
    {
        /* do nothing */
    }
    return (int)ret;
}

struct vector_lint new_vect_lint(unsigned int size)
{
    struct vector_lint tmp;
    tmp.m_lenght = size;
    tmp.m_data = NULL;
    if ( size > 0)
    {
        tmp.m_data = (long int*)malloc(sizeof(long int)*size);
        if (tmp.m_data == NULL)
        {
            tmp.m_lenght = 0;
            printf("Err, Failed to allocate the Vector long int, size:%u, ln:%d, file:%s\n",size,__LINE__,__FILE__);
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

    return tmp;
}
void del_vect_lint(struct vector_lint *obj)
{
    if (obj != NULL)
    {
        obj->m_lenght = 0;
        if(obj->m_data != NULL)
        {
            free(obj->m_data);
            obj->m_data = NULL;
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Err, Obj is NULL, del_vect_lint: ln:%d, File:%s\n",__LINE__,__FILE__);
    }
}


void setDat2VLint(struct vector_lint *obj,const long int *dat)
{
    unsigned int num = 0;
    unsigned int index = 0;
    if ((obj != NULL) && (dat != NULL))
    {
        num = obj->m_lenght;
        for (index = 0 ;index < num ; index++)
        {
            obj->m_data[index] = dat[index];
        }
    }
    else
    {
        printf("Err setDat2VLint input are null,obj:%p, dat:%p, ln:%d, File:%s\n",obj,dat,__LINE__,__FILE__);
    }
}

void getDatFromVLint(const struct vector_lint *obj,long int *dat)
{
    unsigned int num = 0;
    unsigned int index = 0;
    if ((obj != NULL) && (dat != NULL))
    {
        num = obj->m_lenght;
        for (index = 0 ;index < num ; index++)
        {
            dat[index] = obj->m_data[index];
        }
    }
    else
    {
        printf("Err getDatFromVLint input are null,obj:%p, dat:%p, ln:%d, File:%s\n",obj,dat,__LINE__,__FILE__);
    }
}

void prntKeyTFixedArryBInIntNoCountStRV(void* key,char* buff)
{
    struct nodeFixedArr **nfk = (struct nodeFixedArr**)key;
    long int *bb = NULL;
    int index = 0;
    int num=0;
    if (nfk == NULL)
    {
        printf("cannot print1 ,ln:%d, fl:%s\n",__LINE__,__FILE__);
    }
    else if (*nfk != NULL)
    {
        bb = (long int*)((*nfk)->m_dat);
    }
    else
    {
        printf("cannot print2 dat:%p ,ln:%d, fl:%s\n",bb,__LINE__,__FILE__);
    }
    if ((bb != NULL) && (buff != NULL))
    {
        num = (*nfk)->m_length;
        if(num > 1)
        {
            sprintf(buff,"[");
        }
        else
        {
            buff[0] = '\0';
        }
        for (index = 0;index < num;index++)
        {
            sprintf(buff,"%s%ld ",buff,bb[index]); 
        }
        if(num > 1)
        {
            sprintf(buff,"%s]",buff);
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

void prntKeyTFixedArryBInDoubleNoCountStRV(void* key,char* buff)
{
    struct nodeFixedArr **nfk = (struct nodeFixedArr**)key;
    double *bb = NULL;
    int index = 0;
    int num = 0;
    if (nfk == NULL)
    {
        printf("cannot print1 ,ln:%d, fl:%s\n",__LINE__,__FILE__);
    }
    else if (*nfk != NULL)
    {
        bb = (double*)((*nfk)->m_dat);
    }
    else
    {
        printf("cannot print2 dat:%p ,ln:%d, fl:%s\n",bb,__LINE__,__FILE__);
    }
    if ((bb != NULL) && (buff != NULL))
    {
        num = (*nfk)->m_length;
        if (num > 1)
        {
            sprintf(buff,"[");
        }
        else
        {
            buff[0] = '\0';
        }
        for (index = 0;index < num;index++)
        {
            sprintf(buff,"%s%f ",buff,bb[index]); 
        }
        if (num > 1)
        {
            sprintf(buff,"%s]",buff);
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

void prntKeyTFixedArryBInIntCountStRV(void* key,char* buff)
{
    struct nodeFixedArr **nfk = (struct nodeFixedArr**)key;
    long int *bb =NULL;
    int index=0;
    int num=0;
    if(nfk == NULL)
    {
        printf("cannot print1 ,ln:%d, fl:%s\n",__LINE__,__FILE__);
    }
    else if(*nfk != NULL)
    {
        bb = (long int*)((*nfk)->m_dat);
    }
    else
    {
        printf("cannot print2 dat:%p ,ln:%d, fl:%s\n",bb,__LINE__,__FILE__);
    }
    if((bb != NULL) && (buff != NULL))
    {
        num = (*nfk)->m_length;
        num = num - 1;
        if(num > 1)
        {
            sprintf(buff,"[");
        }
        else
        {
            buff[0] = '\0';
        }
        for(index=0;index < num;index++)
        {
            sprintf(buff,"%s%ld ",buff,bb[index]); 
        }
        if(((*nfk)->m_length) > 2)
        {
            if(bb[((*nfk)->m_length)-1] > 1)
            {
                sprintf(buff,"%s](%ld)",buff,bb[((*nfk)->m_length)-1]);
            }
            else
            {
                sprintf(buff,"%s]",buff);
            }
        }
        else if(((*nfk)->m_length) > 1)
        {
            if(bb[((*nfk)->m_length)-1] > 1)
            {
                sprintf(buff,"%s(%ld)",buff,bb[((*nfk)->m_length)-1]);
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

void prntKeyTFixedArryBInDoubleCountStRV(void* key,char* buff)
{
    struct nodeFixedArr **nfk = (struct nodeFixedArr**)key;
    double *bb =NULL;
    int index=0;
    int num=0;
    if(nfk == NULL)
    {
        printf("cannot print1 ,ln:%d, fl:%s\n",__LINE__,__FILE__);
    }
    else if(*nfk != NULL)
    {
        bb = (double*)((*nfk)->m_dat);
    }
    else
    {
        printf("cannot print2 dat:%p ,ln:%d, fl:%s\n",bb,__LINE__,__FILE__);
    }
    if((bb != NULL) && (buff != NULL))
    {
        num = (*nfk)->m_length;
        num = num - 1;
        if(num > 1)
        {
            sprintf(buff,"[");
        }
        else
        {
            buff[0] = '\0';
        }
        for(index=0;index<num;index++)
        {
            sprintf(buff,"%s%f ",buff,bb[index]); 
        }
        if(((*nfk)->m_length) > 2)
        {
            if(((long int)bb[((*nfk)->m_length)-1]) > 1)
            {
                sprintf(buff,"%s](%ld)",buff,(long int)bb[((*nfk)->m_length)-1]);
            }
            else
            {
                sprintf(buff,"%s]",buff);
            }
        }
        else if(((*nfk)->m_length) > 1)
        {
            if(((long int)bb[((*nfk)->m_length)-1]) > 1)
            {
                sprintf(buff,"%s(%ld)",buff,(long int)bb[((*nfk)->m_length)-1]);
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

unsigned long int getTypeOfRVSet(struct rvSet *obj)
{
    unsigned long int ret = 0;
    if(obj != NULL)
    {
        ret = obj->m_type;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

void prntDatIntCountStRV(void *dat,char *buff)
{
    if((dat != NULL )&&(buff != NULL))
    {
        if(*((long int*)dat) > 1)
        {
            sprintf(buff,"(%ld)",*((long int*)dat));
        }
        else
        {
            buff[0] = '\0';
        }
    }
    else
    {
        /* do nothing */
    }
}
void prntDatDoubleCountStRV(void *dat,char *buff)
{
    if((dat != NULL )&&(buff != NULL))
    {
        if(*((long int*)dat) > 1)
        {
            sprintf(buff,"(%ld)",*((long int*)dat));
        }
        else
        {
            buff[0] = '\0';
        }
    }
    else
    {
        /* do nothing */
    }
}
double randomVal(double max,double min)
{
    return min + rand()%(int)(max-min);
}

void swapRandomPosOfRVSet(struct rvSet *obj,int minPos,int maxPos)
{
    int ret = ((obj != NULL) && (minPos > -1) && (maxPos > minPos));
    int numEle = 0;
    int index = 0;
    int time2Rand = 0;
    int indexA = 0;
    int indexB = 0;
    if (ret == 1 )
    {
        numEle = numEleRVSetNotRedunt(obj);
        if (maxPos >= numEle)
        {
            maxPos = numEle - 1;
        }
        else
        {
            /* do nothing */
        }
        /* start swap random */
        time2Rand = (maxPos-minPos);
        /*
        time2Rand = randomVal((double)(maxPos-minPos),0.0);
        printf("Random time : %d \n",time2Rand);
        */
        for(index = 0;index < time2Rand;index++)
        {
            indexA = (int)randomVal((double)maxPos,(double)minPos);
            indexB = (int)randomVal((double)maxPos,(double)minPos);
            if (indexA != indexB)
            {
                swapByIndex4Mt22D(((struct mat2_2d*)obj->m_buff),indexA,indexB);
            }
            else
            {
                /* do nothing */
            }
        }
    }
    else
    {
        printf("Error(0) in swapRandomPosOfRVSet, some paramete is invalid(obj:%p, minPos:%d,maxPos:%d, ln:%d,File:%s\n",obj,minPos,maxPos,__LINE__,__FILE__);
    }
}