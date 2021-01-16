/********************************************************************/
/*
      FILE        :   dDimn.c
      Name        :   Chalearm Saelim
      Date        :   28 Decenber 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Handle the element of a sample, 
                      in case of generate data by the application

      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        28-12-2017    csaelim    First draft 
*/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "eleXMLNodeList.h"
#include "simReadXML.h"
#include "basicVarArea.h"
#include "dDimn.h"

#define DEF_ATTRB_MX            "max"
#define DEF_ATTRB_MN            "min"

int initialDtDm(struct dtDim *obj)
{
    int ret = (obj != NULL);
    //3open
    m_mx = 0.0;
    m_mn = 0.0;
    //1endinitialDtDm//2end
    return ret;
}


int constructorDtDm(struct dtDim *obj,void *dmEle,double defMx,double defMn)
{
    int ret = (initialDtDm(obj) == 1);
    //3open
    if (dmEle != NULL)
    {
        ret = (ret == 1) && getAttrbValXMLEle2Var2(dmEle,DEF_ATTRB_MX,"1.0",(void*)&(m_mx),0x050);
        ret = (ret == 1) && getAttrbValXMLEle2Var2(dmEle,DEF_ATTRB_MN,"2.0",(void*)&(m_mn),0x050);
    }
    else
    {
        m_mx = defMx;
        m_mn = defMn;
    }
    if ( m_mx < m_mn)
    {
        m_mx = defMx;
        m_mn = defMn;
    }
    else
    {
        /* do nohting */
    }
    //1endconstructorDtDm//2end
    return ret;
}

int destructDtDim(struct dtDim *obj)
{
    int ret = (obj != NULL);
    //3open
    m_mx = 0.0;
    m_mn = 0.0;
    //1enddestructDtDmi//2end
    return ret;
}

/* operation */ 
int newDtDms(struct dtDim **obj,int numDim,void *dtDmListNode,double defMx,double defMn)
{
    int nmDimEle = gtNXMLNd2(dtDmListNode);
    int ret = (obj != NULL) ;
    void *ndEle = NULL;
    int index = 0;
    int index2 = 0;
    struct dtDim *dTmpObj = NULL;
    //3open
    dTmpObj = (struct dtDim*)malloc(sizeof(struct dtDim)*numDim);
    if (dTmpObj != NULL)
    {
        for (index = 0;index < nmDimEle; index++)
        {
            ndEle = getXMLElement2(dtDmListNode,index);
            ret = (ret == 1) && constructorDtDm(&(dTmpObj[index]),ndEle,defMx,defMn);
        }
        ndEle = NULL;
        for (index2 = index; index2 < numDim;index2++)
        {
            ret = (ret == 1) && constructorDtDm(&(dTmpObj[index2]),ndEle,defMx,defMn);
        }
    }
    else
    {
        printf("Error(1) in newDtDms, cannot allocation struct dtDim, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    *obj = dTmpObj;
    //1endnewDtDms//2end
    return ret;
    
}
int generateAnEleInASmVal(struct dtDim *obj,double *val)
{
    int ret = ((obj != NULL) && (val != NULL));
    //3open
    *val =  randomFn(m_mx,m_mn);
    //1endgenerateAnEleInASmVal//2end
    return ret;
}
void prtDtDm(struct dtDim *obj)
{
    //1open
    const char *space3 = "              ";
    printf("  ----------------  dtDim obj:%p -------------------------\n",obj);
    printf("%smx  :%f\n",space3,m_mx);
    printf("%smn  :%f\n",space3,m_mn);
    //1endprtDtDm//2end
}

 