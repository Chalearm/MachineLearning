#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simMat2.h"
#define MTROW 4
#define MTCOL 4
void setDat(double *dat,int num,double max,double min);
double randomVal(double max,double min);
void setRandomDat(mat2 *obj,int numLoop,int numEle,double max,double min);

int main(int argc,char **argv)
{
    srand(time(NULL));
    struct mat2Ele *m2El =NULL;
    double *dV=NULL;
    double *dV2=NULL;
    int index=0;
    int index2=0;
    void **arrMt =NULL;
    mat2 *oM1 =NULL;
    mat2 *oM2 =NULL;
    

    oM1 = newMt2(MTROW,MTCOL,sizeof(double),2);
    printf("size mt : %u %d \n",calSizeMt2(oM1),sizeof(*oM1));
    arrMt = getDatMt2(oM1);
    setRandomDat(oM1,MTROW,MTCOL,503.9,-7.45);
    printf("---- ok\n");
    if(arrMt !=NULL)
    {
        oM2 = oM1;  
        for(index2=0;index2<MTROW;index2++)
        {
            m2El = (struct mat2Ele*)getDatNextMt2(oM2);
            if(m2El !=NULL)
            {
                dV2 = (double*)(m2El->m_startP);
                printf("&m2El:%p, &mPoin:%p Val(%p), &len:%p val(%u) &Str:%p ",m2El,&(m2El->m_pointRef),m2El->m_pointRef,&(m2El->m_length),m2El->m_length,m2El->m_startP);
                for(index=0;index<MTCOL;index++)
                { 
                    printf("%f ",dV2[index]);
                }
                printf("\n");
            }
            else
            {
                /* do nothing */
            }
        } 
        printf("random --- \n");
        swapRandomMt2(oM2);
        arrMt = getDatMt2(oM2);
        for(index2=0;index2<MTROW;index2++)
        {
            m2El = (struct mat2Ele*)arrMt[index2];
            dV2 = (double*)(m2El->m_startP);
                     printf("&m2El:%p, &mPoin:%p Val(%p), &len:%p val(%u) &Str:%p ",m2El,&(m2El->m_pointRef),m2El->m_pointRef,&(m2El->m_length),m2El->m_length,&(m2El->m_startP));
            for(index=0;index<MTCOL;index++)
            { 
                printf("%f ",dV2[index]);
            }
            printf("\n");
        }
        
        printf("End of random --- \n");
    }
    rmEleMt2(oM2,arrMt[1]);
    setRandomDat(oM1,1,MTCOL,503.9,-7.45);
    printMt24Double(oM2);
    clearMt2(&oM2);
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
 
void setRandomDat(mat2 *obj,int numLoop,int numEle,double max,double min)
{
    int index=0;
    int index2=0;
    double *dV=NULL;
    struct mat2Ele *m2El =NULL;
    void **arrMt =NULL;
    if(obj !=NULL)
    {
        arrMt = getDatMt2(obj);
        m2El = (struct mat2Ele*)arrMt[0];
        printf("arrMt:%p m2El:%p\n",arrMt,m2El);
        for(index2=0;index2<numLoop;index2++)
        {  
            m2El = (struct mat2Ele*)getDatNextMt2(obj);
            if(m2El!=NULL)
            {
                dV = (double*)(m2El->m_startP);
                printf("&m2El:%p, &mPoin:%p Val(%p), &len:%p val(%u) &Str:%p ",m2El,&(m2El->m_pointRef),m2El->m_pointRef,&(m2El->m_length),m2El->m_length,m2El->m_startP);
                setDat(dV,numEle,max,min);
                printf("\n");
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