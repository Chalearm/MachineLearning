#include <stdio.h>
#include <stdlib.h>
#include "setRealV.h"
#include "sampEle.h"
/* Author      : Chalearm Saelim */
/* Email       : chalearm33@hotmail.com, chalearm90@gmail.com */
/* Date        : 7  August 2017     : First draft */
/*               14 August 2017     : update delete feature (work only dynamic allocate case) */
/*               29 September 2017  : added vector set sample testing (fixed array and dynamic work!!)
                 06 December 2017   : added 2 samples any object (case void* 9 th-bit set)

*/
/* information : this source code is for testing of setRealV library */
/* 
   input set  :
        1st round :
        
         - add : new value
            23, 17, 2, 15, 21, 5, 25, 18, 8, 16, 10, 27, 12, 1, 20
            3, 9, 13, 7, 19, 14, 4, 22, 0, 24, 6, 26, 11
         - print
        2nd round : 
         -add : redundant value
            22, 15, 22, 15, 22, 15, 3, 27, 3, 27, 3, 27, 3
         - print
        3rd round:
         - remove :
            14, 15, 22, 11, 15, 15, 3, 3
         - print :
         - add :
            11, 11, 11, 3, 11
         -print :
         - remove :
            15, 15, 15, 15, 15, 15, 3, 3, 27, 27, 3, 27, 3, 27
         - print :
         
    vector case 1 (3D vector):
        1st round :
         - add : new value 
            [0,2,3], [0,1,7], [0,0,2], [0,1,5], [0,2,1],
            [0,0,5], [0,2,5], [0,1,8], [0,0,8], [0,1,6],
            [0,1,0], [0,2,7], [0,1,2], [0,0,1], [0,2,0],
            [0,0,3], [0,0,9], [0,1,3], [0,0,7], [0,1,9],
            [0,1,4], [0,0,4], [0,2,2], [0,0,0], [0,2,4],
            [0,0,6], [0,2,6], [0,1,1]
        2nd round : 
         -add : redundant value
            [0,2,2], [0,1,5], [0,2,2], [0,1,5], [0,2,2],
            [0,1,5], [0,0,3], [0,2,7], [0,0,3], [0,2,7],
            [0,0,3], [0,2,7], [0,0,3]
        3rd round:
         - remove :                        
            [0,1,4], [0,1,5], [0,8,9], [0,2,2], [0,1,1],
            [0,1,5], [0,5,6], [0,1,5], [0,0,3], [0,0,3],
            [0,1,7], [0,1,6], [0,2,2]
         - print :
         - add :
            [0,1,1], [0,1,1], [0,1,1], [0,0,3], [0,1,1]
         -print :
         - remove :
            [0,1,5], [0,1,5], [0,1,5], [0,1,5], [0,1,5], 
            [0,1,5], [0,0,3], [0,0,3], [0,2,7], [0,2,7], 
            [0,0,3], [0,2,7], [0,0,3], [0,2,7]
         - print :
         - print            
*/ 
double datSet1[] = {23.0, 17.0, 2.0, 15.0, 21.0, 5.0, 25.0, 18.0, 8.0, 16.0, 10.0, 27.0, 12.0, 1.0, 20.0,3.0, 9.0, 13.0, 7.0, 19.0, 14.0, 4.0, 22.0, 0.0, 24.0, 6.0, 26.0, 11.0};
double redundDatSet[] = {22.0, 15.0, 22.0, 15.0, 22.0, 15.0, 3.0, 27.0, 3.0, 27.0, 3.0, 27.0, 3.0};
double rmDatSet[] = {14.0,15.0,89.0,22.0,11.0,15.0,56.0,15.0,3.0,3.0,17.0,16.0,22.0};
double datSet2[] = {11.0,11.0,11.0,3.0,11.0};
double rmDatSet2[] = {15.0 ,15.0 , 15.0 ,27.0, 15.0 , 15.0 , 15.0 , 3.0, 3.0, 27.0, 27.0, 3.0, 27.0, 3.0, 27.0};

#define DIMEN1 3
double vDatSet1[][DIMEN1] = {{0.0,2.0,3.0}, {0.0,1.0,7.0}, {0.0,0.0,2.0}, {0.0,1.0,5.0}, {0.0,2.0,1.0},
                        {0.0,0.0,5.0}, {0.0,2.0,5.0}, {0.0,1.0,8.0}, {0.0,0.0,8.0}, {0.0,1.0,6.0},
                        {0.0,1.0,0.0}, {0.0,2.0,7.0}, {0.0,1.0,2.0}, {0.0,0.0,1.0}, {0.0,2.0,0.0},
                        {0.0,0.0,3.0}, {0.0,0.0,9.0}, {0.0,1.0,3.0}, {0.0,0.0,7.0}, {0.0,1.0,9.0},
                        {0.0,1.0,4.0}, {0.0,0.0,4.0}, {0.0,2.0,2.0}, {0.0,0.0,0.0}, {0.0,2.0,4.0},
                        {0.0,0.0,6.0}, {0.0,2.0,6.0}, {0.0,1.0,1.0}};
double redunVDatSet[][DIMEN1] = {{0.0,2.0,2.0}, {0.0,1.0,5.0}, {0.0,2.0,2.0}, {0.0,1.0,5.0}, {0.0,2.0,2.0},
                            {0.0,1.0,5.0}, {0.0,0.0,3.0}, {0.0,2.0,7.0}, {0.0,0.0,3.0}, {0.0,2.0,7.0},
                            {0.0,0.0,3.0}, {0.0,2.0,7.0}, {0.0,0.0,3.0}};
double rmVDatSet[][DIMEN1] = {{0.0,1.0,4.0}, {0.0,1.0,5.0}, {0.0,8.0,9.0}, {0.0,2.0,2.0}, {0.0,1.0,1.0},
                              {0.0,1.0,5.0}, {0.0,5.0,6.0}, {0.0,1.0,5.0}, {0.0,0.0,3.0}, {0.0,0.0,3.0},
                              {0.0,1.0,7.0}, {0.0,1.0,6.0}, {0.0,2.0,2.0}};
double vDatSet2[][DIMEN1] = {{0.0,1.0,1.0}, {0.0,1.0,1.0}, {0.0,1.0,1.0}, {0.0,0.0,3.0}, {0.0,1.0,1.0}};
double rmVDatSet2[][DIMEN1] =  {{0.0,1.0,5.0}, {0.0,1.0,5.0}, {0.0,1.0,5.0}, {0.0,1.0,5.0}, {0.0,1.0,5.0}, 
                           {0.0,1.0,5.0}, {0.0,0.0,3.0}, {0.0,0.0,3.0}, {0.0,2.0,7.0}, {0.0,2.0,7.0}, 
                           {0.0,0.0,3.0}, {0.0,2.0,7.0}, {0.0,0.0,3.0}, {0.0,2.0,7.0}};

void initialValue(struct rvSet *obj,double *dObj,int numaArr);
void initialVectValue(struct rvSet *obj,void *dObj,int numaArr,int numDimen);
void rmSomeDat(struct rvSet *obj,double *dObj,int numaArr);
void rmSomeVDat(struct rvSet *obj,void *dObj,int numaArr,int numDimen);
void printLinearSet(struct rvSet *obj);

void clearDoublePointerArr(void ***obj,int num);
void clearOnePointerArr(void **obj);
/*void newArrInt2Ddynsize(void *obj,int size,int *size2,int *flag); */
void newArrVoid2D(void *obj,int valSize,int valSize2, int size,int size2,int *flag);


int main(int argc,char **argv)
{

    /*
        type :
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
    struct smpEle smObj;
 
    int dimension = 3;
    unsigned long int type = 0;
    struct rvSet setRVobj;
    contructorSmpEle(&smObj,4,2);
    destructorSmpEle(&smObj);
    for(type = 0 ; type < 8 ;type++)
    {
        printf("round #%lu, type:%lu\n",type+1,type);
        constructorRVSet(&setRVobj,type);
        /* 1st round : */
        printf("round 1 --- add : new value--\n");
        initialValue(&setRVobj,datSet1,sizeof(datSet1)/sizeof(double));
            printRvSet(&setRVobj);
        /* 2nd round : */
        printf("round 2 --- add : redundant value--\n");
        initialValue(&setRVobj,redundDatSet,sizeof(redundDatSet)/sizeof(double));
        printRvSet(&setRVobj);
        /* 3rd round : */
        printf("round 3 --------------------\n");
        rmSomeDat(&setRVobj,rmDatSet,sizeof(rmDatSet)/sizeof(double));
        printRvSet(&setRVobj);
        initialValue(&setRVobj,datSet2,sizeof(datSet2)/sizeof(double));
        printRvSet(&setRVobj);
        rmSomeDat(&setRVobj,rmDatSet2,sizeof(rmDatSet2)/sizeof(double));
        printRvSet(&setRVobj);
        /* 4th round : (TBD)*/
        
        /* 5th linear loop */
        printLinearSet(&setRVobj);
        /* 6th linear print loop by index */
        printLinearByIndexSet(&setRVobj);
        
        destructorRVSet(&setRVobj);
        
        
        printf("END XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    }
    /*  Vector case */
    for (type = 0x08 ; type < 0x10 ;type++)
    {
        printf("round #%lu, type:%lu\n",type+1,type);
        constructorRVSetVect(&setRVobj,type,dimension);
        /* 1st round : */
        printf("round 1 --- add : new value--\n");
        initialVectValue(&setRVobj,(void*)vDatSet1,sizeof(vDatSet1)/(sizeof(double)*DIMEN1),DIMEN1);
        printRvSet(&setRVobj);        /* 2nd round : */
        printf("round 2 --- add : redundant value--\n");
        initialVectValue(&setRVobj,(void*)redunVDatSet,13,3);
        printRvSet(&setRVobj);
        /* 3rd round : */
        printf("round 3 --------------------\n");
        rmSomeVDat(&setRVobj,rmVDatSet,sizeof(rmVDatSet)/(sizeof(double)*DIMEN1),DIMEN1);
        printRvSet(&setRVobj);
        initialVectValue(&setRVobj,vDatSet2,sizeof(vDatSet2)/(sizeof(double)*DIMEN1),DIMEN1);
        printRvSet(&setRVobj);
        rmSomeVDat(&setRVobj,rmVDatSet2,sizeof(rmVDatSet2)/(sizeof(double)*DIMEN1),DIMEN1);
        printRvSet(&setRVobj);
        /* 4th round : (TBD)*/
        
        /* 5th linear loop */
        printLinearSet(&setRVobj);
        /* 6th linear print loop by index */
        printLinearByIndexSet(&setRVobj);
        destructorRVSet(&setRVobj);
        
        printf("END VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV\n");
        
    }
    dimension = 100;
    return 0;
}
void printLinearSet(struct rvSet *obj)
{
    unsigned long int index = 0;
    unsigned long int index2 = 0;
    unsigned long int num = 0;
    unsigned long int num2 = 0;
    unsigned long int type = 0;
    void *tmpV = NULL;
    resetGetNxtDat(obj);
    num = numEleRVSetNotRedunt(obj);
    num2 = numDimenVSet(obj);
    type = obj->m_type;
    if((type&NOT_DYNAMIC_ARR_BIT) == NOT_DYNAMIC_ARR_BIT)
    {
        for(index = 0;index < num ;index++)
        {
            tmpV = getNxtDatInRVSet(obj);
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
        printf("\n");
    }
    else
    {
        printf("This feature doesn't provide in Dynamic array\n");
    }
} 

void initialVectValue(struct rvSet *obj,void *dObj,int numaArr,int numDimen)
{
    int ret = 1;
    int index = 0;
    int index2 = 0;
    int num = numaArr;
    int num2 = numDimen;
    unsigned long int val1 = numDimen*sizeof(double);
    unsigned long int val2 = sizeof(double);
    double **pdouble =  dObj;
    unsigned long int uliTmp = 0;
    long int **pLint = NULL;
    unsigned long int type = 0;
    /*
    void clearDoublePointerArr(void ***obj,int num);
void clearOnePointerArr(void **obj);
void newArrInt2Ddynsize(void *obj,int size,int *size2,int *flag);
void newArrVoid2D(void *obj,int valSize,int valSize2, int size,int size2,int *flag);
    */

    if ((obj != NULL)&&(dObj != NULL))
    {
        printf("--------- num ::: %d \n",num);
        type = getTypeOfRVSet(obj);
        if((type&FLOATING_POINT_BIT) != FLOATING_POINT_BIT)
        {
            if ((numaArr > 0) && (numDimen > 0))
            {
                newArrVoid2D((void*)&pLint,sizeof(long int*),sizeof(long int),numaArr,numDimen,&ret);
            }
            else
            {
                printf("err array size or dimen is failed arrySize:%d dim:%d, ln:%d, file:%s\n",numaArr,numDimen,__LINE__,__FILE__);
            }
            if( ret == 1)
            {
                for(index = 0;index < num ;index++)
                {
                    /** copy value to long int */
                    for (index2 = 0 ;index2 < num2;index2++)
                    {
                        uliTmp =   ((unsigned long int)pdouble) + (((unsigned long int)index)*val1) + (((unsigned long int)index2)*val2);
                        pLint[index][index2] = (long int)(0.5+*((double*)uliTmp));
                    }
                    if(added2RVSet(obj,&pLint[index][0]) == 0)
                    {
                        printf("input Error %p, ln:%d, file;%s\n",&pLint[index][0],__LINE__,__FILE__);
                    }
                    else
                    {
                        
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
            /* floating point case */
            for(index = 0;index < num ;index++)
            {
                /* cal address */
                uliTmp =   ((unsigned long int)pdouble) + (((unsigned long int)index)*val1);
                if(added2RVSet(obj,(void*)uliTmp) == 0)
                {
                    printf("input Error %p, ln:%d, file;%s\n",&pdouble[index][0],__LINE__,__FILE__);
                }
                else
                {
                     /* do nothing */ 
                }
            }
        }
    }
    clearDoublePointerArr((void***)&pLint,num);
}
void initialValue(struct rvSet *obj,double *dObj,int numaArr)
{
    int index = 0;
    int num = numaArr;
    long int tmpI = 0;
    unsigned long int type = 0;
    if((obj != NULL)&&(dObj != NULL))
    {
        printf("--------- num ::: %d \n",num);
        type = getTypeOfRVSet(obj);
        if((type&FLOATING_POINT_BIT) != FLOATING_POINT_BIT)
        {
            for(index = 0;index < num ;index++)
            {
                tmpI = (long int)(0.5 +dObj[index]);
                if(added2RVSet(obj,&tmpI) == 0)
                {
                    printf("input Error %ld\n",tmpI);
                }
                else
                {
                     /* do nothing */ 
                }
            }
        }
        else
        {
            for(index = 0;index < num ;index++)
            {
                if(added2RVSet(obj,&dObj[index]) == 0)
                {
                    printf("input Error %f\n",dObj[index]);
                }
                else
                {
                     /* do nothing */ 
                }
            }
        }
    }
}

void rmSomeDat(struct rvSet *obj,double *dObj,int numaArr)
{
    unsigned long int ret = 0;
    unsigned long int sum = 0;
    int index = 0;
    int num = 0;
    long int tmpI = 0;
    unsigned long int type;

    if((obj != NULL)&&(dObj != NULL)&&(numaArr > 0))
    {
    /*
    m_type  1 st bit  : 0 long integer , 1 floating-point (double)
            2 nd bit  : 0 dynamic array, 1 not dynamic array
            3 rd bit  : 0 count redundant, 1 not count
 */
        type = getTypeOfRVSet(obj);
        num = numaArr;
        printf("del list :");
        if((type&FLOATING_POINT_BIT) == FLOATING_POINT_BIT)
        {   
             /* double delete*/
            for(index = 0;index < num ;index++)
            {
                /* opt 1 = is remove all, 0 is count--, in case not redundant, opt is ignored. */
                ret = removedValRVSet(obj,&dObj[index],0);
                sum = ret +sum;
                printf("%0.3f(%lu) ",dObj[index],ret);
            }
            printf("\n");
        }
        else /* long int delete*/
        {
            for(index = 0;index < num ;index++)
            {
                tmpI = (long int)(0.5 + dObj[index]);
                /* opt 1 = is remove all, 0 is count--, in case not redundant, opt is ignored. */
                ret =removedValRVSet(obj,&tmpI,0);
                sum = ret + sum;
                printf("%ld(%lu) ",tmpI,ret);
            }
            printf("\n");
        }
        if(sum != num)
        {
            printf("Partial successful removed \n");
        }
        else
        {
            printf("Delete Completed \n");
        }
    }
    else
    {
        printf("Cannot execute the rmSomeDat method, %d, %s  \n",__LINE__,__FILE__);
    }
}

void rmSomeVDat(struct rvSet *obj,void *dObj,int numaArr,int numDimen)
{
    unsigned long int sum = 0;
    unsigned long int val1 = numDimen*sizeof(double);
    unsigned long int val2 = sizeof(double);
    unsigned long int uliTmp = 0;
    double **pdouble =  dObj;
    int index = 0;
    int index2 = 0;
    int num = numaArr;
    int num2 = numDimen;
    int ret = 1;
    unsigned long int type = 0;
    long int **pLint = NULL;
    if ((obj != NULL) && (dObj != NULL) && (numaArr > 0) && (numDimen > 0))
    {
        if ((numaArr > 0) && (numDimen > 0))
        {
            newArrVoid2D((void*)&pLint,sizeof(long int*),sizeof(long int),numaArr,numDimen,&ret);
        }
        else
        {
            printf("err array size or dimen is failed arrySize:%d dim:%d, ln:%d, file:%s\n",numaArr,numDimen,__LINE__,__FILE__);
        }
        type = getTypeOfRVSet(obj);
        num = numaArr;
        printf("del list :");
        if((type&FLOATING_POINT_BIT) == FLOATING_POINT_BIT)
        {   
             /* double delete*/
            for(index = 0;index < num ;index++)
            {
                /* opt 1 = is remove all, 0 is count--, in case not redundant, opt is ignored. */
                
                /* cal address */
                uliTmp = ((unsigned long int)pdouble) + (((unsigned long int)index)*val1);
                ret = removedValRVSet(obj,(void*)uliTmp,0);
                sum = ret +sum;
                printf("[");
                for(index2 = 0;index2 < num2;index2++)
                {
                    printf("%0.3f ",*((double*)(uliTmp + (sizeof(double)*index2))));
                }
                printf("](%d) ",ret);
            }
            printf("\n");
        }
        else if(ret == 1) /* long int delete*/
        {
            for(index = 0;index < num ;index++)
            {
                
                    /** copy value to long int */
                for (index2 = 0 ;index2 < num2;index2++)
                {
                    uliTmp =   ((unsigned long int)pdouble) + (((unsigned long int)index)*val1) + (((unsigned long int)index2)*val2);
                    pLint[index][index2] = (long int)(0.5+*((double*)uliTmp));
                }
                /* opt 1 = is remove all, 0 is count--, in case not redundant, opt is ignored. */
                ret =removedValRVSet(obj,&(pLint[index][0]),0);
                sum = ret + sum;
                printf("[");
                for(index2 = 0;index2 < num2;index2++)
                {
                    printf("%ld ",pLint[index][index2] );
                }
                printf("](%d) ",ret);
            }
            printf("\n");
        }
        else
        {
            printf("Error cannot remove node in rmSomeVDat method, ret:%d, ln:%d, file:%s \n",ret,__LINE__,__FILE__);
        }
        if(sum != num)
        {
            printf("Partial successful removed \n");
        }
        else
        {
            printf("Delete Completed \n");
        }
    }
    else
    {
        printf("Cannot execute the rmSomeVDat method, %d, %s  \n",__LINE__,__FILE__);
    }
    
    clearDoublePointerArr((void***)&pLint,num);
}

void newArrVoid2D(void *obj,int valSize,int valSize2, int size,int size2,int *flag)
{
    int valid1 = (size > 0)&&(size2 > 0) && (obj != NULL) && (flag != NULL);
    void ***obj2  = NULL;
    int index = 0;
    int count =0;
    unsigned long int tmpUInt = 0;
    unsigned long int tmpULInt2 = 0;
    unsigned long int tmpULInt3 = (unsigned long int)valSize;
    valid1 = (valid1 == 1) && (valSize > 0) && (valSize2 > 0);
    if (valid1 == 1)
    {
        obj2 = (void***)obj;
        if ((*obj2 ==NULL) && (*flag == 1))
        {
            *obj2  = (void**)malloc(size*valSize);
            if (*obj2 != NULL)
            {
                if( ((unsigned long int)sizeof(void**)) == (unsigned long int)valSize)
                {
                    for(index = 0;index < size;index++)
                    {
                         (*obj2)[index] = malloc(valSize2*size2);
                         count = ((*obj2)[index] != NULL) + count;
                    }
                }
                else
                {
                    printf("special case of newArrVoid2D, ln:%d ,file:%s\n ",__LINE__,__FILE__);
                    for(index = 0;index < size;index++)
                    {
                        tmpULInt2 = ((unsigned long int)(*obj2)) + tmpUInt;
                         *((void**)tmpULInt2) = malloc(valSize2*size2);
                        count =(*((void**)tmpULInt2) != NULL) + count;
                        tmpUInt += tmpULInt3;
                    }
                }
                valid1 = 1;
            }
            else
            {
                valid1=0;
                printf("cannot create 1Dimen of arr : %p\n",*obj2);
            }
            if ((count != size) && (valid1 == 1))
            {
                clearDoublePointerArr((void***)obj2,size);
                *flag =0;
                printf("cannot create 2Dimen of arr : %p, count:%d , ln:%d, file:%s\n",*obj2,count,__LINE__,__FILE__);
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
/*
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
            if(*obj2 !=NULL)
            {
                for(index=0;index<size;index++)
                { 
                    if(size2[index] >0)
                    {
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
                
            }
        }
        else
        {
            printf("arr 2D is not null : %p ,fg:%d\n",*obj2,*flag);
        }
    }
    else
    {
        
    } 
}*/

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
    int index = 0;
    if ((obj != NULL) && (num > 0))
    {
        if (*obj!=NULL)
        {
            for (index = 0;index < num;index++)
            {
                if ((*obj)[index] != NULL)
                { 
                    free ((*obj)[index]);
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
