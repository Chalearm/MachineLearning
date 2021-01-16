/********************************************************************/
/*
      FILE        :   dtStGnHdl.c
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
#include "dtStGnHdl.h"
#include "simReadXML.h"
#include "eleXMLNodeList.h"
#include "basicVarArea.h"

#define DEF_DAT_SET             "DAT_SET"
#define DEF_NUM_DIMENSION       "NUM_DIMENSION"

int constructorDatStGnHdl(struct datSetGenHdl *obj,void *dtStEle)
{
    void *dtLt = NULL;
    int ret = (initialDatStHdl(obj) == 1) && (dtStEle != NULL);
    //3open
    ret = (ret == 1) &&  getSrc2XMLList2(&dtLt,dtStEle,DEF_DAT_SET);
    ret = (ret == 1 ) && getValueOfFirstChildEle2Var2(dtStEle,DEF_NUM_DIMENSION,"1",(void*)&(m_nDim),0x010);
    m_nCls = newClsDetail(&(m_clsEle),m_nDim,dtLt);
    m_nSam = gtNsmInAllCls(m_clsEle,m_nCls);
    m_tmpDtArea = newDoubleArea((1 + m_nDim),&ret);
    if (m_tmpDtArea != NULL)
    {
        m_tmpY = &(m_tmpDtArea[0]);
        m_tmpDt = &(m_tmpDtArea[1]);
    }
    else
    {
        ret = 0;
        printf("Error(1) in constructorDatStGnHdl, cannot allocate data area, ln: %d, file:%s\n",__LINE__,__FILE__);
    }
    destructXMLList2(&dtLt);
    //1endconstructorDatStGnHdl//2end
    return ret;
}

int initialDatStHdl(struct datSetGenHdl *obj)
{
    int ret = (obj != NULL);
    //3open
    m_nDim = 0;
    m_nSam = 0;
    m_nCls = 0;
    m_clsEle = NULL;
    m_tmpDtArea = NULL;
    m_tmpY = NULL;
    m_tmpDt = NULL;
    //1endinitialDatStHdl//2end
    return ret;
}

int destructDtStHdl(struct datSetGenHdl *obj)
{
    int ret = (obj != NULL);
    int index = 0;
    int num = 0;
    //3open
    num = m_nCls;
    if (m_clsEle != NULL)
    {
        for (index = 0;index < num ;index++)
        {
            destructClsDetl(&(m_clsEle[index]));
        }
        free(m_clsEle);
    }
    else
    {
        /* do nothing */
    } 
    ret = delDoubleArea((void*)&(m_tmpDtArea));
    ret = (ret == 1) && initialDatStHdl(obj);
    //1enddestructDtStHdl//2end
    return ret;
}

/* operation */

int gtAllNSmpInDtSHld(struct datSetGenHdl *obj)
{
    int tmp = 0;
    //1open
    tmp = m_nSam;
    //1endgtAllNSmpInDtSHld//2end
    return tmp;
}
int gtNDimInDtSHld(struct datSetGenHdl *obj)
{
    int tmp = 0;
    //1open
    tmp = m_nDim;
    //1endgtNDimInDtSHld//2end
    return tmp;
}

int gtNsmInAClsInDtSHld(struct datSetGenHdl *obj,int index)
{
    int tmp = 0;
    //1open
    if (index < m_nCls)
    {
        tmp = gtNsmInACls(&(m_clsEle[index]));
    }
    else
    {
        printf("Error(1) in gtNsmInAClsInDtSHld, out of range(index:%d>%d) ln:%d,%s\n",index,m_nCls,__LINE__,__FILE__);
    }
    //1endgtNsmInAClsInDtSHld//2end
    return tmp;
}

int gtNTrnsmInAClsInDtSHld(struct datSetGenHdl *obj,int index)
{
    int tmp = 0;
    //1open
    if (index < m_nCls)
    {
        tmp = gtTrnNsmInACls(&(m_clsEle[index]));
    }
    else
    {
        printf("Error(1) in gtNTrnsmInAClsInDtSHld, out of range(index:%d>%d) ln:%d,%s\n",index,m_nCls,__LINE__,__FILE__);
    }
    //1endgtNsmInAClsInDtSHld//2end
    return tmp;
}
int gtNClsInDtSHld(struct datSetGenHdl *obj)
{
    int tmp = 0;
    //1open
    tmp = m_nCls;
    //1endgtNClsInDtSHld//2end
    return tmp;
} 

void prtStHdl(struct datSetGenHdl *obj)
{
    int index = 0;
    int num = 0;
    const char *space1 = "     ";
    //1open
    printf("  ----------------  datSetGenHdl obj:%p -------------------------\n",obj);
    num = m_nCls;
    printf("%snDim  : %d\n",space1,m_nDim);
    printf("%snSam  : %d\n",space1,m_nSam);
    printf("%snCls  : %d\n",space1,m_nCls);
    printf("%sclsEle: %p\n",space1,m_clsEle);
    for(index = 0;index < num;index++)
    {
        prtClsDetl(&(m_clsEle[index]));
    }
    
    //1endprtStHdl//2end
}
 