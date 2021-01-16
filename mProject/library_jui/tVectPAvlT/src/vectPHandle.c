/********************************************************************/
/*
            FILE        :  vectPHandl.c
             Name     :   Chalearm Saelim
            Date       :   15 Nov 2015
            Purpose :   Vector  (integer)pointer array handle library
                            Adding, Removing, Reblance and destruct tree
    
            Dependency lib list :  simMatInt.h
            Description :      In this file is make up of following list below :
                                    1. data structure to handle array of vector integer
                                    2. methods for pluging to AVL tree
                                    3  statements about adding Vector integer  pointer key to the tree
                                    4. statements about removing Vector integer  pointer key from the node
 */
/*******************************************************************/ 
#include <string.h>
#include "vectPHandle.h"
/*
struct vectIHand
{
    vector_int  *m_dat;
    int m_numVect;
    int m_num;
};
*/ 

void constructVH(vectIHand *obj,int numVect,int numArr)
{
    int index=0;
    SetValue set;
    if(obj!=NULL)
    {
        obj->m_dat =NULL;
        obj->m_numCur =0;
        obj->m_numVect =0;
        obj->m_num =0;
        if(numVect>0)
        {
            obj->m_numVect =numVect;
        }
        else
        {
            /* do nothing */
        }
        if(numArr>0)
        {
            obj->m_num =numArr;
        }
        else
        {
            /* do nothing */
        }
        if((obj->m_numVect!=0)&&(obj->m_num!=0))
        {
            obj->m_dat =(vector_int*)malloc(sizeof(vector_int)*obj->m_num);
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_dat !=NULL)
        {
            set.set =0;
            set.max =0;
            set.min =0;
            for(index=0;index<numArr;index++)
            {
                obj->m_dat[index] = new_vector_int(numVect);
                initial_vector_int(&(obj->m_dat[index]),set);
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

void removeVectInVectHand(vectIHand *obj)
{
    if(obj!=NULL)
    {
        if( obj->m_numCur>0)
        {
            obj->m_numCur--;
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
void printInfoVH(vectIHand *obj,char style)
{
    int index=0;
    if(obj!=NULL)
    {
            printf("num ,vNum: %d %d , @dat :%p \n",obj->m_num,obj->m_numVect,obj->m_dat);
            printf("the number of Vects that is assigned value: %d\n",obj->m_numCur);
            for(index=0;index<obj->m_numCur;index++)
            {
                    printf("%d [ ",index);
                    print_vector_int(&(obj->m_dat[index]),6);
                    if((style&0x2)==2)
                    {
                        printf("] %p\n",&(obj->m_dat[index]));
                    }
                    else
                    {
                        printf("]\n");
                    }
            }
    }
    else
    {
        /* do nothing */
    }
}

void addManyVectInrandomVH(vectIHand *obj,int num,int max,int min)
{
    int index=0; 
    char fact1 = (obj!=NULL)&&(num>0)&&(max>=min);
    if(fact1 ==1)
    {
        if((obj->m_numCur+num)>(obj->m_num))
        {
            obj->m_numCur=obj->m_num-num;
            if(obj->m_numCur<0)
            {
                obj->m_numCur =0;
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
        for(index=0;index<num;index++)
        {
            addVectorIntRandom(obj,max,min);
        }
    }
    else
    {
        /* do nothing */
    }
}
void randomAllVectVH(vectIHand *obj,int max,int min)
{
    if(obj!=NULL)
    {
        addManyVectInrandomVH(obj,obj->m_num,max,min);
    }
    else
    {
        /* do nothign */
    }
}
void destructVectHand(vectIHand *obj)
{
    int index =0;
    int numArr =0;
    if(obj->m_dat !=NULL)
    {
        numArr =obj->m_num;
        for(index=0;index<numArr;index++)
        {
            delete_vector_int(&(obj->m_dat[index])); 
        }
        free(obj->m_dat);
        obj->m_num=0;
        obj->m_dat =NULL;
    }
    else
    {
        /* do nothing */
    }
}
void addVectorInt(vectIHand *obj,const int* dat)
{
    char fact1 = (obj!=NULL)&&(dat!=NULL);
    int numVect= 0;
    if(fact1 ==1)
    {
        fact1 = (obj->m_num > obj->m_numCur);
    }
    else
    {
        /* do nothing */
    }
    if(fact1 ==1)
    {
        numVect = obj->m_numVect;
        memcpy(obj->m_dat[obj->m_numCur].data,dat,numVect*sizeof(int));
        obj->m_numCur++;
    }
    else
    {
        /* do nothing */
    }
}
void addVectorIntRandom(vectIHand *obj,int max,int min)
{
     SetValue set;
     char isOk = (obj!=NULL);
    if(isOk==1)
    {
        isOk = (obj->m_num > obj->m_numCur);
    }
    else
    {
        /* do nothing */
    }
    if(isOk==1)
    {
        set.set =1;
        set.max =max;
        set.min = min;
        initial_vector_int(&(obj->m_dat[obj->m_numCur]),set);
        obj->m_numCur++;
    }
    else
    {
        /* do nothing */
    }
}

void* getVectInVH(vectIHand *obj,int index)
{
    void *p =NULL;
    if((index>-1)&&(index < obj->m_numCur))
    {
        p = &(obj->m_dat[index]);
    }
    else
    {
        /* do nothing */
    }
    return p;
}
