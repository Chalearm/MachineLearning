/********************************************************************/
/*
      FILE        :   dtSpc.c
      Name        :   Chalearm Saelim
      Date        :   28 Decenber 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to keep samples

      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        28-12-2017    csaelim    First draft 
*/
/*******************************************************************/
#include "dtSpc.h"

int constructDatSpc(struct datSpace *obj,int numDim)
{
    int ret = (obj != NULL);
    //3open
    constructorRVSetVect(&(m_dt),0xF,numDim+1);
    //1endconstructDatSpc//2end
    return ret;
}
int destructDatSpc(struct datSpace *obj)
{
    int ret = (obj != NULL);
    //3open
    destructorRVSet(&(m_dt));
    //1enddestructDatSpc//2end
    return ret;
}

void prtDatSpace(struct datSpace *obj)
{ 
    int index = 0;
    int index2 = 0;
    int num = 0;
    int num2 = 0;
    double *val = NULL;
    unsigned int segIdTmp = 0;
    unsigned int idTmp = 0;
    //1open
    num2 = numDimenVSet(&(m_dt));
    num = numEleRVSetNotRedunt(&(m_dt));
   // printf("nSam:%d, dim:%d\n",m_nSam,m_nDim);
   // prntMDou(m_dt,m_nSam,m_nDim);
   
    pushStateNxtDat(&(m_dt),&segIdTmp,&idTmp);
    resetGetNxtDat(&(m_dt));
   for (index = 0 ;index < num;index++)
   {
       printf("[");
       val = (double*)getNxtDatInRVSet(&(m_dt));
       for (index2 = 0;index2 < num2 ;index2++)
       {
           printf("%f ",val[index2]);
       }
       printf("]\n");
   }
   popStateNxtDat(&(m_dt),segIdTmp,idTmp);
    //1endprtDatSpace//2end 
    /*
    printRvSet(&(m_dt));
    */
}
/* operation */ 

int swapValueEachRangeInDtSp(struct datSpace *obj,int maxPos,int minPos)
{
    int ret = ((obj != NULL) && (maxPos > minPos));
    //3open
    /*
    printf("ret : %d maxPos:%d ,minPos:%d \n",ret,maxPos,minPos);
    */
    swapRandomPosOfRVSet(&(m_dt),minPos,maxPos);
    //1endswapValueEachRangeInDtSp//2end
    return ret;
}
int st2SetInDtSp(struct datSpace *obj,double *val)
{
    int ret = ((obj != NULL) && (val != NULL));
    //3open
    ret = (int)added2RVSet(&(m_dt),val);
    //1endst2SetInDtSp//2end
    return ret;
}

int gtSampleInputDtInDtSp(struct datSpace *obj,int index,double **val)
{
    int ret = ((obj != NULL) && (val != NULL));
    //3open
    *val = (double*)getDatInRVSetByIndex(&(m_dt),index);
    if (*val != NULL)
    {
        *val = &((*val)[1]);
    }
    else
    {
        printf("Error(1) in gtSampleInputDtInDtSp, index is out of range(%d),val:%p, line:%d, file:%s\n",index,val,__LINE__,__FILE__);
    }
    //1endgtSampleInputDtInDtSp//2end
    return ret;
}