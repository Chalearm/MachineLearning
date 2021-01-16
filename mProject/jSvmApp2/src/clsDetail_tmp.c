/********************************************************************/
/*
      FILE        :   clsDetail.c
      Name        :   Chalearm Saelim
      Date        :   28 Decenber 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Handle the class data


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
#include "clsDetail.h"
#include "eleXMLNodeList.h"
#include "simReadXML.h"

#define DEF_NUM_DIMENSION       "NUM_DIMENSION"
#define DEF_DAT_SET             "DAT_SET"
#define DEF_DIM                 "DIM"

#define DEF_ATTRB_MX            "max"
#define DEF_ATTRB_MN            "min"
#define DEF_ATTRB_STP           "step"
#define DEF_ATTRB_OFS           "offset"
#define DEF_ATTRB_OK            "ok"
#define DEF_ATTRB_VL            "val"
#define DEF_ATTRB_NSAM          "nSam"
#define DEF_ATTRB_PENCTRN       "percentNTrain"

int constructorClsDetl(struct clsDetail *obj,int nmDim,void *clsEle)
{
    double dTmp = 0.0;
    void *dtDMLt = NULL;
    int ret = (initialClsDetl(obj) == 1) && (clsEle != NULL) && (nmDim > 0);
    //3open
    m_nDim = nmDim;
    m_dtDm = NULL;
    getSrc2XMLList2(&dtDMLt,clsEle,DEF_DIM);
    ret = (ret == 1) && getAttrbValXMLEle2Var2(clsEle,DEF_ATTRB_NSAM,"100",(void*)&(m_nSam),0x010);
    ret = (ret == 1) && getAttrbValXMLEle2Var2(clsEle,DEF_ATTRB_PENCTRN,"70.0",(void*)&(dTmp),0x050);
    ret = (ret == 1) && getAttrbValXMLEle2Var2(clsEle,DEF_ATTRB_MX,"1",(void*)&(m_defMxV),0x050);
    ret = (ret == 1) && getAttrbValXMLEle2Var2(clsEle,DEF_ATTRB_MN,"0",(void*)&(m_defMnV),0x050);
    ret = (ret == 1) && newDtDms(&(m_dtDm),m_nDim,dtDMLt,m_defMxV,m_defMnV);

    destructXMLList2(&dtDMLt);
    
    if (m_nSam > 0 )
    {
        m_nTrnSam = ((double)(m_nSam))*dTmp/100.0;
        m_nTestSam = m_nSam - m_nTrnSam;
    }
    else
    {
        ret = 0;
        m_nSam = 0;
        m_nTestSam = 0;
        m_nTrnSam = 0;
    }
    //1endconstructorClsDetl//2end
    return ret;
}

int initialClsDetl(struct clsDetail *obj)
{
    int ret = (obj != NULL);
    //3open
    m_nDim = 0;
    m_nSam = 0;
    m_nTrnSam = 0;
    m_nTestSam = 0;
    m_defMxV = 0.0;
    m_defMnV = 0.0;
    m_dtDm = NULL;
    //1endinitialClsDetl//2end
    return ret;
}

int destructClsDetl(struct clsDetail *obj)
{
    int index = 0;
    int num = 0;
    int ret = (obj != NULL);
    //3open
    if (m_dtDm != NULL)
    {
        num = m_nDim;
        for (index = 0;index < num;index++)
        {
            destructDtDim(&(m_dtDm[index]));
        }
        free(m_dtDm);
    }
    else
    {
        /* do nothing */
    }
    
    ret = (ret == 1) && (initialClsDetl(obj) == 1);
    //1enddestructClsDetl//2end
    return ret;
}

/* operation */
int generateASmVal(struct clsDetail *obj,double *val)
{
    int index = 0;
    int num = 0;
    int ret = ((obj != NULL) &&  (val != NULL));
    //3open
    num = m_nDim; 
    for (index = 0; index < num; index++)
    {
        ret = (ret == 1) && generateAnEleInASmVal(&(m_dtDm[index]),&(val[index]));
    }
    //1endgenerateASmVal//2end
    return ret;
}

int newClsDetail(struct clsDetail **obj, int numDim,void *clsListNode)
{
    int numCls = gtNXMLNd2(clsListNode);
    int ret = (obj != NULL) && (clsListNode != NULL);
    void *ndEle = NULL;
    int index = 0;
    struct clsDetail *clsObjTmp = NULL;
    //3open
    clsObjTmp = (struct clsDetail*)malloc(sizeof(struct clsDetail)*numCls);
    for (index = 0;index < numCls; index++)
    {
        ndEle = getXMLElement2(clsListNode,index);
        ret = (ret == 1) && constructorClsDetl(&(clsObjTmp[index]),numDim,ndEle);
    }
    if (ret == 0)
    {
        printf("Error(1) in newClsDetail, constructClsDetl not work all ,ln:%d file:%s\n",__LINE__,__FILE__);
    }
    else
    {
        /* do nothing */
    }
    *obj = clsObjTmp;
    //1endnewClsDetail//2end
    return numCls;
    
}

int gtNsmInAllCls(struct clsDetail *obj,int nCls)
{
    int tmp = 0;
    int index = 0;
    int ret = ((obj != NULL) && (nCls > 0));
    //3open
    for (index = 0 ; index < nCls ; index++)
    {
        tmp += gtNsmInACls(&(obj[index]));
    }
    //1endgtNsmInAllCls//2end
    return tmp;
}
int gtNsmInACls(struct clsDetail *obj)
{
    int ret = (obj != NULL);
    //3open
    ret = m_nSam;
    //1endgtNsmInACls//2end
    return ret;
}
int gtTrnNsmInACls(struct clsDetail *obj)
{
    int ret = (obj != NULL);
    //3open
    ret = m_nTrnSam;
    //1endgtTrnNsmInACls//2end
    return ret;
}

void prtClsDetl(struct clsDetail *obj)
{
    int index = 0;
    int num = 0;
    const char *space2 = "          ";
    //1open
    printf("  ----------------  clsDetail obj:%p -------------------------\n",obj);
    num = m_nDim;
    printf("%snDim  : %d\n",space2,m_nDim);
    printf("%snSam  : %d\n",space2,m_nSam);
    printf("%snTns  : %d\n",space2,m_nTrnSam);
    printf("%snTst  : %d\n",space2,m_nTestSam);
    printf("%sdefMxV:%f\n", space2,m_defMxV);
    printf("%sdefMnV:%f\n", space2,m_defMnV);
    printf("%sdtDm  : %p\n", space2,m_dtDm); 
    for(index = 0;index < num;index++)
    {
        prtDtDm(&(m_dtDm[index]));
    }
    
    //1endprtClsDetl//2end
}