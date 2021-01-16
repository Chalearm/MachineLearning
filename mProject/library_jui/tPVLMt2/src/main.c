#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listPvoid.h"
#include "simMat2.h"
#include "simMatDouble.h"

#define NUM_ROW_PVL 10
#define NUM_ROW 34
#define COL_SIZE_VD 3

#define MAX_NODE 12

#define MAX_VAL 3453.2453
#define MIN_VAL -23242.2322
/*
    pVoidList PVL;
    constructorPVoidList(&PVL);
    printPVoidList(&PVL,4);
    makeEmptyPVoidList(&PVL);
*/
void deleDatVD(void *dat);
double randomVal(double max,double min);
void setPVListMt22d(mat2_2d *list,mat2_2d *nodes);
void setDelDat2PVMt22d(struct mat2Ele *list);
void clearPVL2(struct mat2Ele *list);
void clearPVListMt22d(mat2_2d *list,mat2_2d *nodes);
void createNode2List(struct mat2Ele *list,int numNode);
/* main process */
int main(int argc,char **argv)
{
    struct mat2Ele *ltPV2_1 = NULL;
    struct mat2Ele *ltPV2_2 = NULL;
    struct mat2Ele *ltPV2_3 = NULL;
    int count1 = MAX_NODE;
    int count2 = MAX_NODE;
    int count3 = MAX_NODE;
    int index =0;
    int index2 =0;
    int temp =0;
    srand(time(NULL));
    mat2_2d mDPVEle2;
    mat2_2d mDPVL;
    setPVListMt22d(&mDPVL,&mDPVEle2);
    ltPV2_1 = (struct mat2Ele*)getDatNextMt22d((void*)(&mDPVL));
    ltPV2_2 = (struct mat2Ele*)getDatNextMt22d((void*)(&mDPVL));
    ltPV2_3 = (struct mat2Ele*)getDatNextMt22d((void*)(&mDPVL));
    constructPVList4PVEle2(ltPV2_1,&mDPVEle2,&constrPVL2);
    constructPVList4PVEle2(ltPV2_2,&mDPVEle2,&constrPVL2);
    constructPVList4PVEle2(ltPV2_3,&mDPVEle2,&constrPVL2);
    setDelDat2PVMt22d(ltPV2_1);
    setDelDat2PVMt22d(ltPV2_2);
    setDelDat2PVMt22d(ltPV2_3);
    printf("Hello World sizeOF PVE2:%lu, l1:%p, l2:%p, l3:%p\n",sizeof(struct pVoidEle2),ltPV2_1,ltPV2_2,ltPV2_3);
    
    while((count1!=0)||(count2!=0)||(count3!=0))
    {
        index = (int)randomVal(2,0);
        index2 = (int)randomVal(3,1);
        if((index == 0)&&(count1>0))
        {
            temp = count1 - index2;
            if(temp < 0)
            {
                index2 = count1;
            }
            else
            {
                /* do nothing */
            }
            count1 = count1 - index2;
            createNode2List(ltPV2_1,index2);
        }
        else if((index == 1)&&(count2>0))
        {
            temp = count2 - index2;
            if(temp < 0)
            {
                index2 = count2;
            }
            else
            {
                /* do nothing */
            }
            count2 = count2 - index2;
            createNode2List(ltPV2_2,index2);
            
        }
        else if((index == 2)&&(count3>0))
        {
            temp = count3 - index2;
            if(temp < 0)
            {
                index2 = count3;
            }
            else
            {
                /* do nothing */
            }
            count3 = count3 - index2;
            createNode2List(ltPV2_3,index2);
        }
    }
    printPVoidList((pVoidList*)(ltPV2_1->m_startP),-4);
    printPVoidList((pVoidList*)(ltPV2_2->m_startP),-4);
    printPVoidList((pVoidList*)(ltPV2_3->m_startP),-4);
    printMt22d(&mDPVL);
    printMt22d(&mDPVEle2);
    clearPVL2(ltPV2_1);
    clearPVL2(ltPV2_2);
    clearPVL2(ltPV2_3);
    clearPVListMt22d(&mDPVL,&mDPVEle2);
    return 0;

}


void setPVListMt22d(mat2_2d *list,mat2_2d *nodes)
{
    if((list!=NULL)&&(nodes!=NULL))
    {
        initiValInMt22d(list);
        initiValInMt22d(nodes);
        *list  = newMt22d(NUM_ROW_PVL,1,sizeof(struct pVoidList),2);
        *nodes = newMt22d(NUM_ROW,0,0,5);
    }
    else
    {
        /* do nothing */
    }
}

void clearPVL2(struct mat2Ele *list)
{
    struct pVoidList *lt = NULL;
    if(list !=NULL)
    {
        lt = (struct pVoidList*)(list->m_startP);
    }
    else
    {
        /* do nothing */
    }
    if(lt != NULL)
    {
        makeEmptyPVoidList(lt);
    }
    else
    {
        /* do nothing */
    }
}
void clearPVListMt22d(mat2_2d *list,mat2_2d *nodes)
{
    if((list!=NULL)&&(nodes!=NULL))
    {
        clearMt22d(list);
        clearMt22d(nodes);
    }
    else
    {
        /* do nothing */
    }
}
double randomVal(double max,double min)
{
    if(max==min)
    {
        return min;
    }
    else
    {
        return min + rand()%(int)(1+max-min);
    }
}

void createNode2List(struct mat2Ele *list,int numNode)
{
    vector_double *vd = NULL;
    int index = 0;
    struct pVoidList *lt = NULL;
    if((list !=NULL)&&(numNode > 0))
    {
        lt = (struct pVoidList*)(list->m_startP);
        vd = malloc(sizeof(vector_double));
    }
    else
    {
        /* do nothing */
    }
    if((lt != NULL)&&(numNode > 0)&&(vd != NULL))
    {
        *vd = new_vector_double(COL_SIZE_VD);
        if(vd->data != NULL)
        {
            for(index = 0;index < COL_SIZE_VD;index++)
            {
                vd->data[index] = randomVal(MAX_VAL,MIN_VAL);
            }
            addDataPtPVoidList(lt,(void**)&vd);
            createNode2List(list,numNode-1);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        if(vd != NULL)
        {
            free(vd);
        }
        else
        {
            /* do nothing */
        }
    }
}

void setDelDat2PVMt22d(struct mat2Ele *list)
{
    struct pVoidList *lt = NULL;
    if(list !=NULL)
    {
        lt = (struct pVoidList*)(list->m_startP);
    }
    else
    {
        /* do nothing */
    }
    if(lt != NULL)
    {
        lt->deleteData = &deleDatVD;
    }
    else
    {
        /* do nothing */
    }
}
void deleDatVD(void *dat)
{
    if(dat != NULL)
    {
        delete_vector_double((vector_double*)dat);
        free(dat);
    }
    else
    {
        /* do nothing */
    }
}