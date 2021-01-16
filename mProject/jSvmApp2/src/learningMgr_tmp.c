/********************************************************************/
/*
      FILE        :   learningMgr.c
      Name        :   Chalearm Saelim
      Date        :   29 October 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Group All about modules that are used in SMO learning


      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        29-10-2017    csaelim    First draft 
*/
/*******************************************************************/
#include "learningMgr.h"
#include "simReadXML.h"
#include "eleXMLNodeList.h"
#include "basicVarArea.h"

#define DEF_KERNEL_FN           "KERNEL_FN"

#define DEF_PRNT_OPT            "PRNT_OPT"
#define DEF_SMO_WAY             "SMO_WAY"
#define DEF_SVM_MULTICLS        "SVM_MULTICLS"

#define DEF_SVM_PARM            "SVM_PARM"
#define DEF_C_SVM               "C_SVM"
#define DEF_TOLERANCE_PARAM     "TOLERANCE_PARAM"
#define DEF_ESP_PARAM           "ESP_PARAM"
#define DEF_ROUND_NUM_PARAM     "ROUND_NUM_PARAM"
#define DEF_PREPROCESS          "PREPROCESS"
#define DEF_DAT_HANDLE          "DAT_HANDLE"
#define DEF_ATTRB_MX            "max"
#define DEF_ATTRB_MN            "min"
#define DEF_ATTRB_STP           "step"

#define DEF_ATTRB_VL            "val" 


int initialSmpLoopController(struct SmpLoopController *obj)
{
    int ret = (obj != NULL);
    //3open
    m_numClsBetrn = 0;
    m_whichCls = NULL;
    m_currMaxFoldVal = 0;
    m_currBrkLoopSmpIdInCls = 0;
    m_currWhichFoldId = 0;
    m_currClsId = 0;
    m_currSmpId = 0;
    //1endinitialSmpLoopController//2end
    return ret;
}

int constructSmlLpController(struct SmpLoopController *obj,int nParty)
{
    int index = 0;
    int num = 0;
    int ret = (initialSmpLoopController(obj) == 1);
    //3open
    m_whichCls = (int*)malloc(sizeof(int)*nParty);
    if (m_whichCls != NULL)
    {
        m_numClsBetrn = nParty;
        num = nParty;
        for (index = 0;index < num;index++)
        {
            m_whichCls[index] = 0;
        }
    }
    else
    {
        ret = 0;
        printf("Error(1) in constructSmlLpController, cannot allocate(m_numClsBetrn), ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    //1endconstructSmlLpController//2end
    return ret;
}
int destructSmlLpController(struct SmpLoopController *obj)
{
    int ret = (obj != NULL);
    //3open 
    if (m_whichCls != NULL)
    {
        free(m_whichCls);
    }
    else
    {
        /* do nothing */
    }
    ret = (ret == 1) && (initialSmpLoopController(obj));
    //1enddestructSmlLpController//2end
    return ret;
}

int initialTrainingInfo(struct trainingInfo *obj)
{
    int ret = (obj != NULL);
    //3open
    m_criteria = 0;  
    m_nCls2BeTrn = 0;
    m_whichParty = NULL;
    m_nPartySlot = 0;
    //1endinitialTrainingInfo//2end
    return ret;
}

int initialOneVsAllClasses(struct oneAgaistAllClasses *obj)
{
    int ret = (obj != NULL);
    //3open
    m_dtSp = NULL;
    m_ele = NULL;  
    m_nCls = 0;
    //1endinitialOneVsAllClasses//2end
    return ret;
}


int consturctOneVsAllClsesEle(struct oneAgaistAllClassesEle *obj, struct datSpace *dtSp, int num)
{
    int index = 0;
    int ret = ((initialOneVsClsesEle(obj) == 1) && (num > 0));
    //3open
    m_dtSp = dtSp;
    m_alpha = (double*)malloc(sizeof(double)*num);
    m_whichIdInACls = (int*)malloc(sizeof(int)*num);
    m_ySet = (int*)malloc(sizeof(int)*num);
    ret = ((m_alpha != NULL) && (m_whichIdInACls != NULL) && (m_ySet != NULL));
    if (ret == 1)
    {
        for (index = 0;index < num ;index++)
        {
            /* alpha and m_whichIdInACls are undefined (-1), defined range is greter than or equal 0 */
            m_alpha[index] = -1.0;
            m_ySet[index] = 0;
            m_whichIdInACls[index] = -1;
        }
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n");
        m_nAlpha = num;
    }
    else
    {
        destructOneVsAllClsesEle(obj);
        ret = 0;
        printf("Error(1) of consturctOneVsAllClsesEle, cannot allocate the data area, line:%d , file;%s\n",__LINE__,__FILE__);
    }
    //1endconsturctOneVsAllClsesEle//2end
    return ret;
}

int destructOneVsAllClsesEle(struct oneAgaistAllClassesEle *obj)
{
    int ret = (obj != NULL);
    //3open
    m_nAlpha = 0;
    if(m_ySet != NULL)
    {
        free(m_ySet);
        m_ySet = NULL;
    }
    else
    {
        /* do nothing */
    }
    if (m_alpha != NULL)
    {
        free(m_alpha);
        m_alpha = NULL;
    }
    else
    {
        /* do nothing */
    }
    if (m_whichIdInACls != NULL)
    {
        free(m_whichIdInACls);
        m_whichIdInACls = NULL;
    }
    else
    {
        /* do nothing */
    }
    //1enddestructOneVsAllClsesEle//2end
    return ret;
}


int constructOneVsAllClasses(struct oneAgaistAllClasses *obj, struct datSpace *dtSp, int nCls)
{
    int index = 0;
    int num = 0;
    int ret = ((initialOneVsAllClasses(obj) == 1) && (nCls > 0) && (dtSp != NULL));
    //3open
    m_dtSp = dtSp;
    m_ele = (struct oneAgaistAllClassesEle*)malloc(sizeof(struct oneAgaistAllClassesEle)*nCls);
    if (m_ele != NULL)
    {
        m_nCls = nCls;
        for (index = 0;index < num ; index++)
        {
            ret = ((initialOneVsClsesEle(&(m_ele[index])) == 1) && (ret == 1));
        }
    }
    else
    {
        printf(" Error(1) of constructOneVsAllClasses, Cannot allocate m_ele, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    //1endconstructOneVsAllClasses//2end
    return ret;
}

int gtDtFromSmoBuff2OneVsAllClses(struct oneAgaistAllClasses *obj,struct SMOBuffer *smoBuff,int whichId)
{
    int num = 0;
    int ret = ((obj != NULL) && (smoBuff != NULL) && (whichId > -1));
    //3open
    if (whichId < m_nCls)
    {   
        num = gtNSVSampleInSmoBuff(smoBuff);
        ret = consturctOneVsAllClsesEle(&(m_ele[whichId]),m_dtSp,num);
        ret = ((gtDtFromSmoBuff2OneVsAllClsesEle(&(m_ele[whichId]),smoBuff,whichId) == 1) && (ret == 1));
    }
    else
    {
        /* do nothing */
    }
    //1endgtDtFromSmoBuff2OneVsAllClses//2end
    return ret;
}

int gtDtFromSmoBuff2OneVsAllClsesEle(struct oneAgaistAllClassesEle *obj,struct SMOBuffer *smoBuff,int whichId)
{
    double tmp1 = 0.0;
    int index = 0;
    int index2 = 0;
    int num = 0;
    int ret = ((obj != NULL) && (smoBuff != NULL) && (whichId > -1));
    //3open
    num = m_nAlpha;
    ret = resetLoopIndexSMOBuffer(smoBuff);
    printf("Start stored sv value whichId :%d numSv:%d \n",whichId,num);
    for (index = 0;index < num ;index++)
    {
        index2 = nxtDatInSMOBuffer(smoBuff,1);
        ret = ((updateValInSMOBuff(smoBuff,READ_ALPHA,index2,&(m_alpha[index])) == 1) && (ret == 1));
        ret = ((updateValInSMOBuff(smoBuff,READ_YCURR,index2,&tmp1) == 1) && (ret == 1));
        m_ySet[index] = (int)(tmp1);
        m_whichIdInACls[index] = index2;
        printf("id:%d, y:%d, al:%f \n",m_whichIdInACls[index],m_ySet[index],m_alpha[index]);
    }
    printf("End stored sv value whichId :%d numSv:%d \n",whichId,num);
    //1endgtDtFromSmoBuff2OneVsAllClsesEle//2end
    return ret;
}

int destructOneVsAllClasses(struct oneAgaistAllClasses *obj)
{
    int index = 0;
    int num = 0;
    int ret = (obj != NULL);
    //3open 
    if (m_ele != NULL)
    {
        num = m_nCls;
        for (index = 0;index < num;index++)
        {
            ret = (destructOneVsAllClsesEle(&(m_ele[index])) && (ret == 1));
        }
        free(m_ele);
        m_ele = NULL;
    }
    else
    {
        /* do nothing */
    }
    ret = (initialOneVsAllClasses(obj) == 1);
    //1enddestructOneVsAllClses//2end
    return ret;
}

int initialOneVsClsesEle(struct oneAgaistAllClassesEle *obj)
{
    int ret = (obj != NULL);
    //3open
    m_dtSp = NULL;
    m_alpha = NULL;  
    m_ySet = NULL;
    m_whichIdInACls = NULL;
    m_nAlpha = 0;
    m_whichParty = 0;
    //1endinitialOneVsClsesEle//2end
    return ret;
}
/*
int updateBefornTrnInTrnInfo(struct trainingInfo *obj,int kSize,double kenVal,double offsetVal)
{
    int ret = (obj != NULL);
    //3open
    m_currKFoldSize = kSize;  
    m_currC = NULL;
    m_currKenelVal = kenVal;
    m_currKenelOff = offsetVal; 
    //1endupdateBefornTrnInTrnInfo//2end
    return ret;
}
*/
int initialOneVs1Cls(struct oneAgaisOneClassesEle *obj)
{
    int ret = (obj != NULL);
    //3open
    m_alpha = NULL;  
    m_whichIdInCls = NULL;
    m_nAlpha = 0;
    //1endinitialTrainingInfo//2end
    return ret;
}

int constructTrainingInfo(struct trainingInfo *obj,int nParty)
{
    int index = 0;
    int num = 0;
    int ret = (initialTrainingInfo(obj) == 1);
    //3open
    m_whichParty = (int*)malloc(sizeof(int)*nParty);
    if (m_whichParty != NULL)
    {
        m_nPartySlot = nParty;
        num = nParty;
        for (index = 0;index < num;index++)
        {
            m_whichParty[index] = 0;
        }
    }
    else
    {
        ret = 0;
        printf("Error(1) in constructTrainingInfo, cannot allocate(m_nPartySlot), ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    //1enddestructTrainingInfo//2end
    return ret;
}

int destructTrainingInfo(struct trainingInfo *obj)
{
    int ret = (obj != NULL);
    //3open 
    if (m_whichParty != NULL)
    {
        free(m_whichParty);
    }
    else
    {
        /* do nothing */
    }
    ret = (ret == 1) && (initialTrainingInfo(obj));
    //1enddestructTrainingInfo//2end
    return ret;
}

void prntTrainingInfo(struct trainingInfo *obj)
{
    int index = 0;
    int num = 0;
    //1open
    printf("trainingInfo : %p \n",obj);
    printf("crit     : %d \n",m_criteria);
    printf("nCls2Trn : %d \n",m_nCls2BeTrn);
    /*
    printf("Current updated value \n");
    printf("K-Fold-size:%d \n",m_currKFoldSize);
    printf("C:%f, Kernal v:%f, offset:%f\n",m_currC,m_currKenelVal,m_currKenelOff);
    */
    printf("nParty   : %d \n",m_nPartySlot);
    num = m_nPartySlot;
    for (index = 0;index < num ;index++)
    {
        printf("    i:%d val:%d\n",index,m_whichParty[index]);
    }
    //1endprntTrainingInfo//2end
}

int intialKFoldSet(struct kFoldSet *obj)
{
    int ret = (obj != NULL);
    //3open
    m_nFoldSet = 0;
    m_kFSet = NULL;
    //1endintialKFoldSet//2end
    return ret;
}
int contructorKFdSet(struct kFoldSet *obj,struct datSetGenHdl *cObj,struct preProcDat *pObj)
{
    int ret = (intialKFoldSet(obj)) && (cObj != NULL) &&(pObj !=NULL);
    int nFoldSet = gtNFoldSetInPrepro(pObj);
    int foldSize = 0;
    int index = 0;
    //3open
    m_nFoldSet = nFoldSet;
    m_kFSet = (struct kFold*)malloc(sizeof(struct kFold)*nFoldSet);
    if(m_kFSet != NULL)
    {
        for (index = 0;index < nFoldSet;index++)
        {
            foldSize = gtFoldSizeInPrepro(pObj,index);
            ret = (ret == 1) && contructorKFd(&(m_kFSet[index]),cObj,foldSize);
        }
    
    }
    else
    {
        printf("Error(1) in contructorKFdSet, cannot allocate:%p ,ln:%d file:%s\n",m_kFSet,__LINE__,__FILE__);
    }
    //1endcontructorKFdSet//2end
    return ret;
}
int destructKFdSet(struct kFoldSet *obj)
{
    int num = 0;
    int index = 0;
    int ret = (obj != NULL);
    //3open
    if (m_kFSet != NULL)
    {
        num = m_nFoldSet;
        for (index = 0;index < num;index++)
        {
            destructKFd(&(m_kFSet[index]));
        }
        free(m_kFSet);
    }
    else
    {
        /* do nothing */
    }
    ret = ((ret == 1) &&  intialKFoldSet(obj));
    //1enddestructKFdSet//2end
    return ret;
}
void prntKFdSt(struct kFoldSet *obj)
{
    int num = 0;
    int index = 0;
    //1open
    num = m_nFoldSet;
    printf("kFoldSet :%p, num:%d \n",m_kFSet,m_nFoldSet);
    for (index = 0;index < num;index++)
    {
        prntKFd(&(m_kFSet[index]));
    }
    printf("\n");
    //1endprntKFdSt//2end
}
int intialKFd(struct kFold *obj)
{
    int ret = (obj != NULL);
    //3open
    m_nFold = 0;
    m_clsSet = NULL;
    //1endintialKFd//2end
    return ret;
}
int contructorKFd(struct kFold *obj,struct datSetGenHdl *cObj,int foldSize)
{
    int index = 0;
    int nCls = 0;
    int ret = ((intialKFd(obj)) && (foldSize > 0));
    //3open
    m_clsSet = (struct dtClsHdl*)malloc(sizeof(struct dtClsHdl)*foldSize); 
    if(m_clsSet != NULL)
    {
        m_nFold = foldSize;
        nCls = gtNClsInDtSHld(cObj);
        for(index = 0 ;index < foldSize;index++)
        {
            ret = (ret == 1) && constructDtClsHdl(&(m_clsSet[index]),nCls);
            ret = (ret == 1) && gentDatInDtClsHdl(&(m_clsSet[index]),cObj,foldSize,index);
        }
    }
    else
    {
        ret = 0;
        printf(" Error(1) in contructorKFd, failed to allocate, m_clsSet:%p,ln:%d, file:%s\n",m_clsSet,__LINE__,__FILE__);
        destructKFd(obj);
        
    }
    //1endcontructorKFd//2end
    return ret;
}
int destructKFd(struct kFold *obj)
{
    int index = 0;
    int num = 0;
    int ret = (obj != NULL);
    //3open
    if (m_clsSet != NULL)
    {
        num = m_nFold;
        for (index = 0;index < num;index++)
        {
            destructDtClsHdl(&(m_clsSet[index]));
        }
        free(m_clsSet);
    }
    else
    {
        /* do nothing */
    }
    ret = ((ret == 1) &&  intialKFd(obj));
    //1enddestructKFd//2end
    return ret;
}
int gtStartPosOnLeftInKFd(struct kFold *obj,int indexFold,int indexCls,int *startPos1,int *num)
{
    int numFld = 0;
    int tmp = 0;
    int ret = ((obj != NULL) && (indexFold > -1) && (indexCls > -1) && (startPos1 != NULL) && (num != NULL));
    //3open
    numFld = m_nFold;
    if (indexFold == 0)
    {
        /* no data in this case */
        *startPos1 = -1;
        *num = -1;
    }
    else if ((indexFold == 1) && (indexFold < numFld))
    {
        ret = gtStartPosOfKFd(obj,indexFold-1,indexCls,startPos1,num);
    }
    else if ((indexFold > 0) && (indexFold < numFld))
    {
        ret = gtStartPosOfKFd(obj,0,indexCls,startPos1,num);
        ret = ((ret == 1) && gtStartPosOfKFd(obj,indexFold-1,indexCls,&tmp,num));
        *num = (tmp - *startPos1) + (*num);
    }
    else
    {
        ret = 0;
        printf(" Error(1) in gtStartPosOnLeftInKFd, indexFold > numFld (%d,%d) ln:%d, file:%s\n",indexFold,numFld,__LINE__,__FILE__);
    }
    //1endgtStartPos1InKFd//2end
    return ret;
}
int gtStartPosOnRightInKFd(struct kFold *obj,int indexFold,int indexCls,int *startPos2,int *num)
{
    int numFld = 0;
    int tmp = 0;
    int ret = ((obj != NULL) && (indexFold > -1) && (indexCls > -1) && (startPos2 != NULL) && (num != NULL));
    //3open
    numFld = m_nFold;
    if ((indexFold == 0) && (numFld == 1))
    {
        ret = gtStartPosOfKFd(obj,indexFold,indexCls,startPos2,num);
    }
    else if (indexFold == (numFld -1))
    {
        *startPos2 = -1;
        *num = -1;
    }
    else if (indexFold < numFld)
    {
        ret = gtStartPosOfKFd(obj,indexFold,indexCls,startPos2,num);
        ret = ((ret == 1) && gtStartPosOfKFd(obj,numFld-1,indexCls,&tmp,num));
        *num = (tmp - *startPos2) + (*num);
    }
    else
    {
        ret = 0;
        printf(" Error(1) in gtStartPosOnRightInKFd, indexFold > numFld (%d,%d) ln:%d, file:%s\n",indexFold,numFld,__LINE__,__FILE__);
    }
    //1endgtStartPos1InKFd//2end
    return ret;
}
void prntKFd(struct kFold *obj)
{
    int num = 0;
    int index = 0;
    //1open
    num = m_nFold;
    const char *space1 = "    ";
    printf("%skFold :%p, num:%d \n",space1,m_clsSet,m_nFold);
    for (index = 0;index < num;index++)
    {
        prtDtClsHdl(&(m_clsSet[index]));
    }
    //1endprntKFd//2end
}
int initialDtClsHdl(struct dtClsHdl *obj)
{
    int ret = (obj != NULL);
    //3open
    m_nCls = 0;
    m_firstIdSamCls = NULL;
    m_numSmCls = NULL;
    //1endinitialDtClsHdl//2end
    return ret;
}

int constructDtClsHdl(struct dtClsHdl *obj,int nCls)
{
    int index = 0;
    int ret = ((initialDtClsHdl(obj)) && (nCls > 0));
    //3open
    m_firstIdSamCls = (int*)malloc(sizeof(int)*nCls);
    m_numSmCls = (int*)malloc(sizeof(int)*nCls);
    if((m_firstIdSamCls != NULL)&&(m_numSmCls != NULL))
    {
        m_nCls = nCls;
        for(index = 0 ;index < nCls;index++)
        {
            m_firstIdSamCls[index] = 0;
            m_numSmCls[index] = 0;
        }
    }
    else
    {
        ret = 0;
        printf(" Error(1) in constructDtClsHdl, failed to allocate, firstIdSamCls:%p, numSmCls:%p ,ln:%d, file:%s\n",m_firstIdSamCls,m_numSmCls,__LINE__,__FILE__);
        destructDtClsHdl(obj);
        
    }
    //1endconstructDtClsHdl//2end
    return ret;
}
int destructDtClsHdl(struct dtClsHdl *obj)
{
    int ret = (obj != NULL);
    //3open
    if (m_firstIdSamCls != NULL)
    {
        free(m_firstIdSamCls);
    }
    else
    {
        /* do nothing */
    }
    if (m_numSmCls != NULL)
    {
        free(m_numSmCls);
    }
    else
    {
        /* do nothing */
    }
    ret = ((ret == 1) &&  initialDtClsHdl(obj));
    //1enddestructDtClsHdl//2end
    return ret;
}

int chckIsRead2GentDtClsHdl(struct dtClsHdl *obj)
{
    int ret = (obj != NULL);
    //3open
    ret = (m_nCls > 0);
    ret = ((ret == 1) && (m_firstIdSamCls != NULL));
    ret = ((ret == 1) && (m_numSmCls != NULL));
    //1endchckIsRead2GentDtClsHdl//2end
    return ret;
}

int gentDatInDtClsHdl(struct dtClsHdl *obj,struct datSetGenHdl *cObj,int nKFold,int whichK)
{
    int ret =  ((cObj != NULL) && (nKFold > 0) &&(nKFold > whichK));
    int nSmInCls = 0;
    int sumSam = 0;
    int tmp1 = 0;
    int index = 0;
    int fraction = 0;
    ret = ((ret == 1) && (chckIsRead2GentDtClsHdl(obj) == 1));
    //3open
    tmp1 = gtNClsInDtSHld(cObj);
    nSmInCls = m_nCls;
    if (nSmInCls == tmp1)
    {
        for (index = 0;index < m_nCls ;index++)
        {
            if (index > 0)
            {
                sumSam += gtNsmInAClsInDtSHld(cObj,index-1);
            }
            else
            {
                /* do nothing */
            }
            nSmInCls = gtNTrnsmInAClsInDtSHld(cObj,index);
            tmp1     = nSmInCls/nKFold;
            fraction = nSmInCls%nKFold;
            if (whichK >= nSmInCls)
            {
                m_firstIdSamCls[index] = -1;
                m_numSmCls[index] = 0;
            }
            else if (whichK >= fraction)
            {
                m_firstIdSamCls[index] =sumSam + tmp1*whichK + fraction;
                m_numSmCls[index] = tmp1;
            }
            else
            {
                m_firstIdSamCls[index] =sumSam + whichK*(tmp1+1);
                m_numSmCls[index] = tmp1+1;
            }
        }
    }
    else
    {
        printf("Error(1) in gentDatInDtClsHdl, nCls between 2 objects diff(%d,%d), ln:%d, file:%s\n",nSmInCls,tmp1,__LINE__,__FILE__); 
    }
    //1endgentDatInDtClsHdl//2end
    return ret;
}

int gentDat4TstSmpInDtClsHdl(struct dtClsHdl *obj,struct datSetGenHdl *cObj,int nKFold,int whichK)
{
    int ret =  ((cObj != NULL) && (nKFold > 0) &&(nKFold > whichK));
    int nSmInCls = 0;
    int nTrnSmInCls = 0;
    int sumSam = 0;
    int nTestSmInCls = 0;
    int tmp1 = 0;
    int index = 0;
    int fraction = 0;
    ret = ((ret == 1) && (chckIsRead2GentDtClsHdl(obj) == 1));
    //3open
    tmp1 = gtNClsInDtSHld(cObj);
    nSmInCls = m_nCls;
    if (nSmInCls == tmp1)
    {
        for (index = 0;index < m_nCls ;index++)
        {
            if (index > 0)
            {
                sumSam += gtNsmInAClsInDtSHld(cObj,index-1);
            }
            else
            {
                /* do nothing */
            }
            nTrnSmInCls = gtNTrnsmInAClsInDtSHld(cObj,index);
            nTestSmInCls = gtNsmInAClsInDtSHld(cObj,index) - nTrnSmInCls;
            tmp1     = nTestSmInCls/nKFold;
            fraction = nTestSmInCls%nKFold;
            if (whichK >= nTestSmInCls)
            {
                m_firstIdSamCls[index] = -1;
                m_numSmCls[index] = 0;
            }
            else if (whichK >= fraction)
            {
                m_firstIdSamCls[index] = sumSam+nTrnSmInCls + tmp1*whichK + fraction;
                m_numSmCls[index] = tmp1;
            }
            else
            {
                m_firstIdSamCls[index] = sumSam+nTrnSmInCls+ whichK*(tmp1+1);
                m_numSmCls[index] = tmp1+1;
            }
        }
    }
    else
    {
        printf("Error(1) in gentDatInDtClsHdl, nCls between 2 objects diff(%d,%d), ln:%d, file:%s\n",nSmInCls,tmp1,__LINE__,__FILE__); 
    }
    //1endgentDat4TstSmpInDtClsHdl//2end
    return ret;
}

int gtNClsInDtClsHdl(struct dtClsHdl *obj)
{
    int tmp = 0;
    //1open
    tmp = m_nCls;
    //1endgtNClsInDtClsHdl//2end
    return tmp;
}

void prtDtClsHdl(struct dtClsHdl *obj)
{
    int num = 0;
    int index = 0;
    //1open
    num = m_nCls;
    
    const char *space2 = "        ";
    const char *space3 = "            ";
    printf("%sprt DtCls Hdl: %p \n",space2,obj);
    printf("%sFirst id each cls:\n",space2);
    for (index = 0;index < num;index++)
    {
        printf("%scls id:%d  id:%d , nSm:%d\n",space3,index,m_firstIdSamCls[index],m_numSmCls[index]);
    }
    //1endprtDtClsHdl//2end
}

int gtStartPosOfKFd(struct kFold *obj,int indexFold,int indexCls,int *startPos1,int *num)
{
    int ret = ((obj != NULL) && (indexFold > -1) && (indexCls > -1) && (startPos1 != NULL) && (num != NULL));
    //3open
    ret = gtStartPosInDtClsHdl(&(m_clsSet[indexFold]),indexCls,startPos1,num);
    //1endgtStartPosOfKFd//2end
    return ret;
}

int gtStartPosInDtClsHdl(struct dtClsHdl *obj,int idCls,int *posStart,int *nSample)
{
    int ret = ((obj != NULL) && (idCls > -1) && (posStart != NULL) && (nSample != NULL));
    //3open
    if ((m_nCls > 0) && (idCls < m_nCls))
    {
        *posStart = m_firstIdSamCls[idCls];
        *nSample = m_numSmCls[idCls];
    }
    else
    {
        printf("Error(1) in gtStartPosInDtClsHdl, bad parameter (idCls:%d,nCls:%d), ln:%d file:%s\n",idCls,m_nCls,__LINE__,__FILE__);
    }
    //1endgtStartPosInDtClsHdl//2end
    return ret;
}

void constructorLearningMgr(struct learningMgr *obj,const char *fileName)
{
    
    int ret = (obj != NULL) && (fileName != NULL);
    //3open
    initialVals2MemsFromXML(obj,fileName,&ret);
    preprocessDtInLearnMgr(obj,&ret);
    trainingInLearnMgr(obj,&ret);
    testSmpInLearnMgr(obj,&ret);
    if (ret == 0)
    {
        printf("Error(1) in constructorLearningMgr, some process does't work, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    else
    {
        /* do nothing */
    }
    //1endconstructorLearningMgr//2end
}

void destructorLearningMgr(struct learningMgr *obj)
{
    int ret = (obj != NULL);
    //3open
    m_prtOpt = 0;
    m_svmMultiCls = 0;
    ret = (ret == 1) && destructKernelFnHdl(&(m_kFnSet));
    ret = (ret == 1) && destructSMOParSt(&(m_smoParSet));
    ret = (ret == 1) && destructPreproDt(&(m_preProSet));
    ret = (ret == 1) && destructDtStHdl(&(m_dtGenSet));
    ret = (ret == 1) && destructDatSpc(&(m_dtSp));
    ret = (ret == 1) && destructDtClsHdl(&(m_trnclsHdl));
    ret = (ret == 1) && destructDtClsHdl(&(m_testclsHdl));
    ret = (ret == 1) && destructKFdSet(&(m_kFoldSt));
    ret = (ret == 1) && destructTrainingInfo(&(m_trnInfo));
    ret = (ret == 1) && destructSmlLpController(&(m_loopTrnController));
    ret = (ret == 1) && destructorSMOBuff(&(m_smoBuff));
    ret = (ret == 1) && destructOneVsAllClasses(&(m_oneVsAllClses));
    //1enddestructorLearningMgr//2end
}

int initialDefSmoParm(struct smoParmSet *obj)
{
    int ret = (obj != NULL);
    //3open
    m_smoWay    = 0;
    m_cVlMx     = 0.0;
    m_cVlMn     = 0.0;
    m_cVlStp    = 0.0;
    m_tol       = 0.00002;
    m_esp       = 0.00001;
    m_roundNUm  = 0.00000001;
    m_currCVal  = 0.0;
    m_indexLoop = 0;
    m_nLoop     = 0;
    //1endinitialDefSmoParm//2end
    return ret;
}

int resetLoopOfCSVMInSMOParm(struct smoParmSet *obj)
{
    int ret = (obj != NULL);
    //3open
    m_indexLoop = 0;
    //1endresetLoopOfCSVMInSMOParm//2end
    return ret;
}

int isEndOfLoopOfCSVMInSMOParm(struct smoParmSet *obj)
{
    int ret = (obj != NULL);
    //3open
    ret = (m_indexLoop >= m_nLoop);
    //1endisEndOfLoopOfCSVMInSMOParm//2end
    return ret;
}

int nxtCSVMParamValInSMOParm(struct smoParmSet *obj)
{
    int ret = (obj != NULL);
    //3open
    m_currCVal = m_cVlMn + m_cVlStp*(m_indexLoop);
    m_indexLoop++;
    if (m_currCVal > m_cVlMx)
    {
        m_currCVal = m_cVlMx;
    }
    else
    {
        /* do nothing */
    }
    //1endnxtCSVMParamValInSMOParm//2end
    return ret;
}
void prtSmoParm(struct smoParmSet *obj)
{
    const char *space1 = "     ";
    //1open
    printf("  ----------------  smoParmSet obj:%p -------------------------\n",obj);
    printf("%ssmoWay   :%d\n",space1,m_smoWay);
    printf("%scVlMx    :%f\n",space1,m_cVlMx);
    printf("%scVlMn    :%f\n",space1,m_cVlMn);
    printf("%scVlStp   :%f\n",space1,m_cVlStp);
    printf("%stol      :%f\n",space1,m_tol);
    printf("%sesp      :%f\n",space1,m_esp);
    printf("%sRoundNum :%0.16f\n",space1,m_roundNUm);
    printf("%snLoop    :%d\n",space1,m_nLoop);
    printf("%sindexLoop:%d\n",space1,m_indexLoop);
    //1endprtSmoParm//2end
}
 

void initialVals2MemsFromXML(struct learningMgr *obj,const char *fileName,int *ret1)
{
    int ret = 0;
    treeXML tXML;
    void *tXMLV = &tXML;
    void *rootEle = NULL;
    void *kernelEle = NULL;
    void *smoParEle = NULL;
    void *preProEle = NULL;
    void *dtStEle = NULL;
    ret = ((obj != NULL) && (ret1 != NULL) && (getSourceToTreeXML(&tXML,fileName)));
    /* Phase 1 */
    if (ret == 1)
    {
        if( *ret1 == 1)
        {
            rootEle = (void*)getRootElementXML2(tXMLV);
            ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(rootEle,DEF_SVM_MULTICLS,DEF_ATTRB_VL,"0",(void*)&(m_svmMultiCls),0x010);
            kernelEle = (void*)getfirstChildXML2(rootEle,DEF_KERNEL_FN);
            smoParEle = (void*)getfirstChildXML2(rootEle,DEF_SVM_PARM);
            preProEle = (void*)getfirstChildXML2(rootEle,DEF_PREPROCESS);
            dtStEle = (void*)getfirstChildXML2(rootEle,DEF_DAT_HANDLE);
            
            ret = (ret == 1) && constructorKernelFnHdl(&(m_kFnSet),kernelEle);
            ret = (ret == 1) && constructorSmoParm(&(m_smoParSet),smoParEle);
            ret = (ret == 1) && constructorPrePro(&(m_preProSet),preProEle);
            ret = (ret == 1) && constructorDatStGnHdl(&(m_dtGenSet),dtStEle);
            prtValKernelFnHdl(&(m_kFnSet));
            prtSmoParm(&(m_smoParSet));
          
            prtPrePro(&(m_preProSet)); 
            prtStHdl(&(m_dtGenSet));
             *ret1 = ret;
        }
        else
        {
            printf("Error(1) in initialVals2MemsFromXML, previous step is faile(ret:%d), ln:%d,file:%s\n",*ret1,__LINE__,__FILE__);
        }
        destructorTreeXML(&tXML);
    }
    else
    {
        printf("Error(0) in initialVals2MemsFromXML: obj:%p, xmlFl:%p, ln:%d, file:%s\n",obj,fileName,__LINE__,__FILE__);
    }
}


void preprocessDtInLearnMgr(struct learningMgr *obj,int *ret1)
{
    int nCls = 0;
    int nAllSmp = 0;
    int nDim = 0;
    int ret = ((obj != NULL) && (ret1 != NULL));
    //3open
    if (*ret1 == 1)
    {
        nDim = gtNDimInDtSHld(&(m_dtGenSet));
        nCls = gtNClsInDtSHld(&(m_dtGenSet));
        nAllSmp = gtAllNSmpInDtSHld(&(m_dtGenSet));
        /* allocate data */
        ret = constructDatSpc(&(m_dtSp),nDim);
ret = (ret == 1) && constructDtClsHdl(&(m_trnclsHdl),nCls);
ret = (ret == 1) && constructDtClsHdl(&(m_testclsHdl),nCls);
        /* generate and rearrange data in Random way */
        ret = (ret == 1) && generateSmClsVal(&(m_dtGenSet),&(m_dtSp));
/* prtDatSpace(&(m_dtSp));*/
        ret = (ret == 1) && swapValueEachClsInDtStHdl(&(m_dtGenSet),&(m_dtSp));
/*
printf(" After random ---------------------\n");
prtDatSpace(&(m_dtSp));

*/
        /* set mark points to allocate k-th fold area */
        ret = (ret == 1) && contructorKFdSet(&(m_kFoldSt),&(m_dtGenSet),&(m_preProSet));
        ret = (ret == 1) && gentDatInDtClsHdl(&(m_trnclsHdl),&(m_dtGenSet),1,0);
        ret = (ret == 1) && gentDat4TstSmpInDtClsHdl(&(m_testclsHdl),&(m_dtGenSet),1,0);
/*
prtDtClsHdl(&(m_trnclsHdl));
prtDtClsHdl(&(m_testclsHdl));
*/
/*
prntKFdSt(&(m_kFoldSt));
*/
        /* set training information */
        ret = ((ret == 1) && constructTrainingInfo(&(m_trnInfo),nCls));
        ret = ((ret == 1) && initialOneVsAllClasses(&(m_oneVsAllClses)));
        ret = ((ret == 1) && constructSmlLpController(&(m_loopTrnController),nCls));
        ret = ((ret == 1) && constructorSMOBuff(&(m_smoBuff),nAllSmp));
        ret = (stObjParamsInSMOBuff(&(m_smoBuff),&(m_kFnSet),&(m_dtSp)) && (ret == 1));
        ret = (stSMOParam2SmoBuff(&(m_smoParSet),&(m_smoBuff)) && (ret == 1));
        ret = (stNDimParamInSMOBuff(&(m_smoBuff),nDim) && (ret == 1));
        *ret1 = ret;
    }
    else
    {
        printf("Error(1) in preprocessDtInLearnMgr, previous step is faile(ret:%d), ln:%d,file:%s\n",*ret1,__LINE__,__FILE__);
    }
    //1endpreprocessDtInLearnMgr//2end 
}

/*
    try to implement 1 vs All class Multi-class SVM_MULTICLS
    try to implement 1 vs 1 clsss multi-class SVM_MULTICLS
*/

void trainingInLearnMgr(struct learningMgr *obj,int *ret1)
{ 
    int ret = ((obj != NULL) && (ret1 != NULL));
    //3open
    if(*ret1 == 1) /* DO this function */
    {
        /* parameter changed list :
            - C svm
            - Kernal parameter
            - K-Fold size
        */
        /* learning loop */
        
        /* model selected */
        /*
        while()
        {
        }
        */
        /* start with 1 agaist All Multi-class SVM */
        ret = loopKFoldSetLearning(&(m_kFoldSt),obj);
    }
    else
    {
        printf("Error(1) in trainingInLearnMgr,pre-process is not passed, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    //1endtrainingInLearnMgr//2end
}

int loopKFoldSetLearning(struct kFoldSet *obj,struct learningMgr *lmObj)
{
    int index = 0;
    int num = 0;
    int ret = ((obj != NULL) && (lmObj != NULL));
    //3open
    num = m_nFoldSet;
    for (index = 0;index < num;index++)
    {
        printf("loopKFoldSetLearning Loop : %d, num:%d obj:%p \n",index,num,lmObj);
        ret = ((loopKFoldLearning(&(m_kFSet[index]),lmObj)) && (ret == 1));
    }
    //1endloopKFoldSetLearning//2end
    return ret;
}
int gtTheNumOfClsInLearning(struct learningMgr *obj)
{
    int tmp = 0;
    //1open
    tmp = gtNClsInDtSHld(&(m_dtGenSet));
    //1endgtTheNumOfClsInLearning//2end
    return tmp;
}
int loopKFoldLearning(struct kFold *obj,struct learningMgr *lmObj)
{
    int indexFold = 0;
    int index2 = 0;
    int num = 0;
    int nCls = gtTheNumOfClsInLearning(lmObj);
    int ret = ((obj != NULL) && (lmObj != NULL) && (nCls > 0));
    //3open
    num = m_nFold;
    for (indexFold = 0;indexFold < num;indexFold++)
    {
        printf("    id:%d %d-Fold Loop1\n",indexFold,num);
        /* training loop */
        /* 1 for All classes */
        ret = constructOneVsAllClasses(gt1VsAllClsesInLearningMgr(lmObj),gtDtSpInLearningMgr(lmObj),nCls);
        for (index2 = 0;index2 < nCls;index2++)
        {
            printf(" AAAAAAAAAAAAAAAAAAAAAAAAA k-id:%d ClsId:%d ret:%d\n",indexFold,index2,ret);
            ret = ((flushAllValOfSMOBuffEle2DefaultInSMOBuff(gtSMOBuffInLearningMgr(lmObj)) == 1) && (ret == 1));
            ret = (stPartyVal4OVsAInSMOBuff(gtSMOBuffInLearningMgr(lmObj),obj,nCls,indexFold,index2) && (ret == 1));
            /* prntSMOBuff(gtSMOBuffInLearningMgr(lmObj)); */
            ret = ((mainLearningLoopInSMOBuffer(gtSMOBuffInLearningMgr(lmObj)) == 1) && (ret == 1));
            prntSMOBuff(gtSMOBuffInLearningMgr(lmObj));  
            printf(" OOOOOOOOOOOOOOOOOOOOOOOOO k-id:%d ClsId:%d ret:%d\n",indexFold,index2,ret);
            /* keep the alpha value */
            ret = ((gtDtFromSmoBuff2OneVsAllClses(gt1VsAllClsesInLearningMgr(lmObj),gtSMOBuffInLearningMgr(lmObj),index2) == 1) && (ret == 1));
        }
        /* jui */
        printf("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n");
        /* validation phase fold-indexFold */
        ret = ((stPartyVal4TestFoldInSMOBuff(gtSMOBuffInLearningMgr(lmObj),obj,nCls,indexFold) == 1) && (ret == 1));
        
        prntSMOBuff(gtSMOBuffInLearningMgr(lmObj));
        printf("Test fold-%d \n",indexFold);
                   prntSMOBuff(gtSMOBuffInLearningMgr(lmObj));
                   
        printf("End of Test fold-%d \n",indexFold);
        ret = destructOneVsAllClasses(gt1VsAllClsesInLearningMgr(lmObj));
    }
    //1endloopKFoldLearning//2end
    return ret;
}

int loopAFoldLearning(struct dtClsHdl *obj,struct learningMgr *lmObj)
{
    int index = 0;
    int num = 0;
    int ret = ((obj != NULL) && (lmObj != NULL));
    //3open
    num = m_nCls;
    for (index = 0;index < num;index++)
    {
        /* describe about learning method in below */
        setPartyValSMOBuff(gtSMOBuffInLearningMgr(lmObj),obj,index,-1);
        //prntSMOBuff(gtSMOBuffInLearningMgr(lmObj));
        printf("        Class id:%d  obj:%p\n",index,lmObj);
    }
    //1endloopAFoldLearning//2end
    return ret;
}

struct SMOBuffer* gtSMOBuffInLearningMgr(struct learningMgr *obj)
{
    struct SMOBuffer *tmp = NULL;
    //1open
    tmp = &(m_smoBuff);
    //1endgtSMOBuffInLearningMgr//2end
    return tmp;
}

struct oneAgaistAllClasses* gt1VsAllClsesInLearningMgr(struct learningMgr *obj)
{
    struct oneAgaistAllClasses *tmp = NULL;
    //1open
    tmp = &(m_oneVsAllClses);
    //1endgt1VsAllClsesInLearningMgr//2end
    return tmp;
}

struct dtClsHdl* gtTrnDtClsHdlClsLearningMgr(struct learningMgr *obj)
{
    struct dtClsHdl *tmp = NULL;
    //1open
    tmp = &(m_trnclsHdl);
    //1endgtTrnDtClsHdlClsLearningMgr//2end
    return tmp;
}

struct datSpace* gtDtSpInLearningMgr(struct learningMgr *obj)
{
    struct datSpace *tmp = NULL;
    //1open
    tmp = &(m_dtSp);
    //1endgtDtSpInLearningMgr//2end
    return tmp;
}

void testSmpInLearnMgr(struct learningMgr *obj,int *ret1)
{
    int ret = ((obj != NULL) && (ret1 != NULL));
    //3open
    if(*ret1 == 1) /* DO this function */
    {
        
    }
    else
    {
        printf("Error(1) in testSmpInLearnMgr,pre-process is not passed, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    //1endtestSmpInLearnMgr//2end
}

int constructorSmoParm(struct smoParmSet *obj, void *smoParEle)
{
    int ret = (initialDefSmoParm(obj) == 1) && (smoParEle != NULL);
    //3open
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(smoParEle,DEF_SMO_WAY,DEF_ATTRB_VL,"0",(void*)&(m_smoWay),0x010);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(smoParEle,DEF_C_SVM,DEF_ATTRB_MX,"0.0",(void*)&(m_cVlMx),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(smoParEle,DEF_C_SVM,DEF_ATTRB_MN,"0.0",(void*)&(m_cVlMn),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(smoParEle,DEF_C_SVM,DEF_ATTRB_STP,"0.0",(void*)&(m_cVlStp),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(smoParEle,DEF_TOLERANCE_PARAM,DEF_ATTRB_VL,"0.0",(void*)&(m_tol),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(smoParEle,DEF_ESP_PARAM,DEF_ATTRB_VL,"0.0",(void*)&(m_esp),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(smoParEle,DEF_ROUND_NUM_PARAM,DEF_ATTRB_VL,"0.0",(void*)&(m_roundNUm),0x050);
    if((ret == 1) && (m_cVlStp > 0.0))
    {
        m_nLoop = (m_cVlMx - m_cVlMn)/m_cVlStp;
        ret = nxtCSVMParamValInSMOParm(obj);
    }
    else
    {
        printf(" Error(1) in constructorSmoParm, XML Reading is not completed, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    
    //1endconstructorSmoParm//2end
    return ret;
}

int destructSMOParSt(struct smoParmSet *obj)
{
    int ret = (obj != NULL);
    //3open
    ret = initialDefSmoParm(obj);
    //1enddestructSMOParSt//2end
    return ret;
}

int setPartyVal2EleInSMOBuff(struct SMOBuffer *obj,int startId, int stopId,int val)
{
    int index = 0;
    int num = 0;
    int ret = (obj != NULL);
    //3open
    num = m_nBuff;
    if (num > stopId)
    {
        num = stopId;
    }
    else if (num < stopId)
    {
        num = m_nBuff;
        printf("Error(1) in setPartyVal2EleInSMOBuff, stopId(%d) is greater than nBuff(%d) ln:%d file:%s\n",stopId,m_nBuff,__LINE__,__FILE__);
    }
    else
    {
        /* do nothing */
    }
    if ((startId < stopId) && (startId > -1))
    {
        for (index = startId; index < num; index++)
        {
            ret = ((ret == 1) && setYVal2SMOBuffEle(&(m_smoBuffEle[index]),val));
        }
    }
    else if (startId == -1)
    {
        /* do nothing */
    }
    else
    {
        printf("Error(1) in setPartyVal2EleInSMOBuff, bad parameters startId,stopId:%d,%d ln:%d file:%s\n",startId,stopId,__LINE__,__FILE__);
    }
    //1endsetPartyValSMOBuffEle//2end
    return ret;
}

int stPartyVal4TestFoldInSMOBuff(struct SMOBuffer *obj, struct kFold *kObj,int maxCls,int whichFold)
{
    int strPos = 0;
    int numSmp = 0;
    int index = 0;
    int isNot1Fold = 0;
    int ret = ((obj != NULL) && (kObj != NULL) && (maxCls > -1) && (whichFold > -1));
    //3open
    isNot1Fold = isNot1FoldInKFold(kObj);
    
    for (index = 0;index < maxCls;index++)
    {
        /* assign 0 to other fold */
        ret = (stOutputVal4KthFoldInSmoBuff(obj,kObj,index,whichFold,0) && (ret == 1));
        if (isNot1Fold == 1)
        {
            /* assign 0 to k-th fold */
            ret = (gtStartPosOfKFd(kObj,whichFold,index,&strPos,&numSmp) && (ret == 1));
            ret = (setPartyVal2EleInSMOBuff(obj,strPos,strPos+numSmp,index) && (ret == 1));
        }
        else
        {
            /* do nothing */
        }
    }
    //1endstPartyVal4TestFoldInSMOBuff//2end
    return ret;
}

int stPartyVal4OVsAInSMOBuff(struct SMOBuffer *obj, struct kFold *kObj,int maxCls,int whichFold,int idCls)
{
    int strPos = 0;
    int numSmp = 0;
    int index = 0;
    int valTmp = 0;
    int isNot1Fold = 0;
    int ret = ((obj != NULL) && (kObj != NULL) && (maxCls > idCls) && (idCls > -1) && (whichFold > -1));
    //3open
    isNot1Fold = isNot1FoldInKFold(kObj);
    
    /* An index is the current id class that has been considered */
  
    for (index = 0;index < maxCls;index++)
    {
        if (index == idCls)
        {
            valTmp = 1;
        }
        else
        {
            valTmp = -1;
        }
        /* assign +1,-1 to other fold */
        ret = (stOutputVal4KthFoldInSmoBuff(obj,kObj,index,whichFold,valTmp) && (ret == 1));
        if (isNot1Fold == 1)
        {
            /* assign 0 to k-th fold */
            ret = (gtStartPosOfKFd(kObj,whichFold,index,&strPos,&numSmp) && (ret == 1));
            ret = (setPartyVal2EleInSMOBuff(obj,strPos,strPos+numSmp,0) && (ret == 1));
        }
        else
        {
            /* do nothing */
        }
    }
    //1endstPartyVal4OVsAInSMOBuff//2end
    return ret;
}
int isNot1FoldInKFold(struct kFold *obj)
{
    int ret = 0;
    //1open
    ret = (m_nFold > 1);
    //1endisNot1FoldInKFold//2end
    return ret;
}
int setPartyValSMOBuff(struct SMOBuffer *obj,struct dtClsHdl *dObj,int plusId,int minusId)
{
    int index = 0;
    int startPos = 0;
    int numSmp = 0;
    int nCls = gtNClsInDtClsHdl(dObj);
    int ret = ((obj != NULL) && (nCls > 0) && (plusId >= -1) && (minusId >= -1));
    //3open
    if ((plusId == -1) && (minusId == -1))
    {
        for (index = 0;index < nCls;index++)
        {
            ret = ((ret == 1) && gtStartPosInDtClsHdl(dObj,index,&startPos,&numSmp));
            /* set to be undefined */
            ret = ((ret == 1) && setPartyVal2EleInSMOBuff(obj,startPos,numSmp + startPos,0));
        }
        /*
        int 
        int gtStartPosInDtClsHdl(struct dtClsHdl *obj,int idCls,int *posStart,int *nSample)
        */
    }
    else if ((plusId == -1) && (minusId > -1))
    {
        ret = ((ret == 1) && gtStartPosInDtClsHdl(dObj,minusId,&startPos,&numSmp));
        /* set to be undefined */
        ret = ((ret == 1) && setPartyVal2EleInSMOBuff(obj,startPos,numSmp + startPos,-1));
        for (index = 0;index < nCls;index++)
        {
            if (index != minusId )
            {
                ret = ((ret == 1) && gtStartPosInDtClsHdl(dObj,index,&startPos,&numSmp));
                /* set to be undefined */
                ret = ((ret == 1) && setPartyVal2EleInSMOBuff(obj,startPos,numSmp + startPos,1));
            }
            else
            {
                /* do nothing */
            }
        }
    }
    else if ((plusId > -1) && (minusId == -1))
    {
        ret = ((ret == 1) && gtStartPosInDtClsHdl(dObj,plusId,&startPos,&numSmp));
        /* set to be undefined */
        ret = ((ret == 1) && setPartyVal2EleInSMOBuff(obj,startPos,numSmp + startPos,1));
        for (index = 0;index < nCls;index++)
        {
            if (index != plusId )
            {
                ret = ((ret == 1) && gtStartPosInDtClsHdl(dObj,index,&startPos,&numSmp));
                /* set to be undefined */
                ret = ((ret == 1) && setPartyVal2EleInSMOBuff(obj,startPos,numSmp + startPos,-1));
            }
            else
            {
                /* do nothing */
            }
        }
    }
    else if ((plusId > -1) && (minusId > -1) && (minusId != plusId))
    {
        ret = ((ret == 1) && gtStartPosInDtClsHdl(dObj,plusId,&startPos,&numSmp));
        /* set to be undefined */
        ret = ((ret == 1) && setPartyVal2EleInSMOBuff(obj,startPos,numSmp + startPos,1));
        
        ret = ((ret == 1) && gtStartPosInDtClsHdl(dObj,minusId,&startPos,&numSmp));
        /* set to be undefined */
        ret = ((ret == 1) && setPartyVal2EleInSMOBuff(obj,startPos,numSmp + startPos,-1));
    }
    else
    {
        printf("Error(1) in setPartyValSMOBuffEle, bad parameter :minusId:%d,plusId:%d ,ln:%d, file:%s\n",minusId,plusId,__LINE__,__FILE__);
    }
    //1endsetPartyValSMOBuffEle//2end
    return ret;
}

int stSMOParam2SmoBuff(struct smoParmSet *obj,struct SMOBuffer *sObj)
{
    int ret = ((obj != NULL) && (sObj != NULL));
    //3open
    ret = stValParamsInSMoBuff(sObj,m_tol,m_currCVal,m_esp,m_roundNUm);
    //1endstSMOParam2SmoBuff//2end
    return ret;
}

int stOutputVal4KthFoldInSmoBuff(struct SMOBuffer *obj, struct kFold *kObj,int indexCls,int indexKFold,int val)
{
    int startOnLeft = 0;
    int startOnRight = 0;
    int numOnLeft = 0;
    int numOnRight = 0;
    int ret = ((obj != NULL) && (kObj != NULL) && (indexCls > -1) && (indexKFold > -1));
    //3open
    ret = (gtStartPosOnLeftInKFd(kObj,indexKFold,indexCls,&startOnLeft,&numOnLeft) && (ret == 1));
    ret = (gtStartPosOnRightInKFd(kObj,indexKFold,indexCls,&startOnRight,&numOnRight) && (ret == 1));
    ret = (setPartyVal2EleInSMOBuff(obj,startOnLeft,startOnLeft+numOnLeft,val) && (ret == 1));
    ret = (setPartyVal2EleInSMOBuff(obj,startOnRight,startOnRight+numOnRight,val) && (ret == 1));
    
    //1endsetPartyValOfClsIdSmoBuff//2end
    return ret;
}

int stPartyValForAClsSMOBuff(struct SMOBuffer *obj,struct dtClsHdl *dObj,int indexCls,int val)
{
    /* indexCls = -1: set all clases */
    int index = 0;
    int num = 0;
    int startPos = 0;
    int numSmp = 0;
    int ret = ((obj != NULL) && (dObj != NULL) && (indexCls > -2));
    num = gtNClsInDtClsHdl(dObj);
    //3open
    if (indexCls == -1)
    {
        for (index = 0;index < num;index++)
        {
            ret = ((ret == 1) && gtStartPosInDtClsHdl(dObj,index,&startPos,&numSmp));
            ret = ((ret == 1) && setPartyVal2EleInSMOBuff(obj,startPos,numSmp + startPos,val));
        }
    }
    else if ( num > index)
    {
            ret = ((ret == 1) && gtStartPosInDtClsHdl(dObj,indexCls,&startPos,&numSmp));
            ret = ((ret == 1) && setPartyVal2EleInSMOBuff(obj,startPos,numSmp + startPos,val));
    }
    else
    {
        printf("Error(1) in stPartyValForAClsSMOBuff, Bad value of indexCls:%d ,ln:%d, file:%s\n",indexCls,__LINE__,__FILE__);
    }
    //1endstPartyValForAClsSMOBuff//2end
    return ret;
}

/*  operation in */


int generateSmClsVal(struct datSetGenHdl *obj,struct datSpace *dtObj)
{
    int index = 0;
    int index2 = 0;
    int num1 = 0;
    int num2 = 0;
    int ret = ((obj != NULL) && (dtObj != NULL));
    //3open
    num1 = m_nCls; 
    for (index = 0;index < num1;index++)
    {
        num2 = gtNsmInACls(&(m_clsEle[index]));
        for (index2 = 0;index2 < num2;index2++)
        {
            *(m_tmpY) = index;
            ret = (ret == 1) && generateASmVal(&(m_clsEle[index]),m_tmpDt);
            ret = (ret == 1) && st2SetInDtSp(dtObj,m_tmpDtArea);
        }
    }
    //1endgenerateSmClsVal//2end
    return ret;
}

int swapValueEachClsInDtStHdl(struct datSetGenHdl *obj,struct datSpace  *dtObj)
{
    int index = 0;
    int num1 = 0;
    int num2 = 0;
    int preNum = 0;
    int ret = ((obj != NULL) && (dtObj != NULL));
    //3open
    num1 = gtNClsInDtSHld(obj); 
    for (index = 0;index < num1;index++)
    {
        num2 = gtNsmInACls(&(m_clsEle[index]));
        ret = ((ret == 1) && swapValueEachRangeInDtSp(dtObj,num2+preNum-1,preNum));
        
        preNum += num2; 
    }
    //1endswapValueEachClsInDtStHdl//2end
    return ret;
}