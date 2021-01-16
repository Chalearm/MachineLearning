/********************************************************************/
/*
      FILE        :   preprocML.c
      Name        :   Chalearm Saelim
      Date        :   28 Decenber 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Handle the preprocessing data


      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        28-12-2017    csaelim    First draft 
*/
/*******************************************************************/
#include <stdio.h>
#include "preprocML.h"
#include "simReadXML.h"

#define DEF_K_FOLD              "K_FOLD"
#define DEF_ATTRB_MX            "max"
#define DEF_ATTRB_MN            "min"
#define DEF_ATTRB_STP           "step"
#define DEF_ATTRB_OK            "ok"
#define DEF_SCALE               "SCALE"

int constructorPrePro(struct preProcDat *obj, void *preProEle)
{
    int ret = (initialDefPrePro(obj) == 1) && (preProEle != NULL);
    //3open
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(preProEle,DEF_K_FOLD,DEF_ATTRB_MX,"10",(void*)&(m_nFoldMx),0x010);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(preProEle,DEF_K_FOLD,DEF_ATTRB_MN,"1",(void*)&(m_nFoldMn),0x010);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(preProEle,DEF_K_FOLD,DEF_ATTRB_STP,"1",(void*)&(m_nFoldStep),0x010);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(preProEle,DEF_SCALE,DEF_ATTRB_OK,"0",(void*)&(m_isScale),0x050);
    //1endconstructorPrePro//2end
    return ret;
}

int initialDefPrePro(struct preProcDat *obj)
{
    int ret = (obj != NULL);
    //3open
    m_nFoldMx    = 0;
    m_nFoldMn    = 0;
    m_nFoldStep  = 0;
    m_isScale    = 0;
    //1endinitialDefPrePro//2end
    return ret;
}

int destructPreproDt(struct preProcDat *obj)
{
    int ret  = (obj != NULL);
    //3open
    ret = initialDefPrePro(obj);
    //1enddestructPreproDt//2end
    return ret;
}


/* operation */
int gtFoldSizeInPrepro(struct preProcDat *obj,int index)
{
    int foldSize = 0;
    //1open
    if (index == 0)
    {
        foldSize = m_nFoldMn;
    }
    else if (index < 0)
    {
        printf("Error(1) in gtFoldSizeInPrepro, index < 0 (%d) ln:%d file:%s\n",index,__LINE__,__FILE__);
    }
    else
    {
        foldSize = m_nFoldStep*index + m_nFoldMn;
        if (foldSize > m_nFoldMx)
        {
            foldSize = m_nFoldMx;
        }
        else
        {
            /* do nothing */
        }
    }
    //1endgtFoldSizeInPrepro//2end
    return foldSize;
}

int gtNFoldSetInPrepro(struct preProcDat *obj)
{
    int nFoldSet = 0;
    //1open
    nFoldSet = 1+(int) (0.5+((double)(m_nFoldMx-m_nFoldMn))/((double)m_nFoldStep));
    //1endgtNFoldSetInPrepro//2end
    return nFoldSet;
}

void prtPrePro(struct preProcDat *obj)
{
    const char *space1 = "     ";
    //1open
    printf("  ----------------  preProcDat obj:%p -------------------------\n",obj);
    printf("%snFoldMx  :%d\n",space1,m_nFoldMx);
    printf("%snFoldMn  :%d\n",space1,m_nFoldMn);
    printf("%snFoldStep:%d\n",space1,m_nFoldStep);
    printf("%sisScale  :%d\n",space1,m_isScale);
    //1endprtPrePro//2end
} 