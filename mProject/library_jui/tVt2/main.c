#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simMat2.h"
#define NUMARR 3

void setDat(double *dat,int num,double max,double min);
double randomVal(double max,double min);

int main(int argc,char **argv)
{
    srand(time(NULL)); 
    double *dV=NULL;
    double *dV2=NULL;
    int index=0;
    void **arrMt =NULL;
    vect2 *oV2 = NULL; 
    vect2 *oV1 = newVt2(NUMARR,sizeof(double));
 
    dV = (double*)getDatVt2(oV1);
    printf("dV:%p\n",dV);
    if(dV!=NULL)
    {
        setDat(dV,NUMARR,483.234,-23);
    }
    else
    { 
    }
    oV2 = oV1;
    dV2= (double*)getDatVt2(oV2);
    printf("dV2:%p oV1:%p oV2:%p\n",dV2,oV1,oV2);
    if(dV2!=NULL)
    {
        for(index=0;index<NUMARR;index++)
        { 
            printf("%f ",dV2[index]);
        }
        printf("\n");
    }
    else
    { 
    } 
 
    clearVt2(&oV1); 
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
 