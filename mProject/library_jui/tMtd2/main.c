#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simMat2.h"
#define MTROW 4
#define MTCOL 4

void setDat(double *dat,int num,double max,double min);
double randomVal(double max,double min);
void setRandomDat(void **arrMt,int numLoop,int numEle,double max,double min);
void setRandomDatForMat22D(mat2_2d *obj,int numLoop,int numEle,double max,double min);

int main(int argc,char **argv)
{
    srand(time(NULL));
    void **arrMt =NULL;
    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    mat2_2d om2d = newMt22d(MTROW,MTCOL,sizeof(double),3);
    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

       
    arrMt = getDatMt22d(&om2d,0);
    printf("arrMt of om2d :%p\n",arrMt);
    setRandomDatForMat22D(&om2d,4330,MTCOL,503.9,-7.45);
    printf("-----xxxx----\n");
    printMt22d(&om2d);
    printMt22d4Double(&om2d);
    clearMt22d(&om2d);
    return 0;
}

double randomVal(double max,double min)
{
    return min + rand()%(int)(max-min);
}

void setDat(double *dat,int num,double max,double min)
{
    int index=0;
    for(index=0;index<num;index++)
    {
        dat[index] = randomVal(max,min); 
        printf("%f ",dat[index]);
    }
}

void setRandomDatForMat22D(mat2_2d *obj,int numLoop,int numEle,double max,double min)
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
                    dV = (double*)&(m2El->m_startP);
                    printf("&m2El:%p, &mPoin:%p Val(%p), &len:%p val(%u) &Str:%p ",m2El,&(m2El->m_pointRef),m2El->m_pointRef,&(m2El->m_length),m2El->m_length,&(m2El->m_startP));
                    setDat(dV,numEle,max,min);
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
            for(index=0;index<numLoop;index++)
            {
                nodeFArr = (struct nodeFixedArr*)getDatNextMt22d((void*)obj);
                if(nodeFArr !=NULL)
                {
                    dV = (double*)(nodeFArr->m_dat);
                    printf("i:%d ",index);
                    printHeadFixedArrNode(nodeFArr);
                    setDat(dV,numEle,max,min);
                    printf("\n");
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
    int index=0;
    int index2=0;
    double *dV=NULL;
    struct mat2Ele *m2El =NULL;
    if(arrMt !=NULL)
    {
        m2El = (struct mat2Ele*)arrMt[0];
        printf("arrMt:%p m2El:%p\n",arrMt,m2El);
        for(index2=0;index2<numLoop;index2++)
        {
            m2El = (struct mat2Ele*)arrMt[index2];
            dV = (double*)&(m2El->m_startP);
            printf("&m2El:%p, &mPoin:%p Val(%p), &len:%p val(%u) &Str:%p ",m2El,&(m2El->m_pointRef),m2El->m_pointRef,&(m2El->m_length),m2El->m_length,&(m2El->m_startP));
            setDat(dV,numEle,max,min);
            printf("\n");
        }
    }
    else
    {
        /* do nothing */
    }
}