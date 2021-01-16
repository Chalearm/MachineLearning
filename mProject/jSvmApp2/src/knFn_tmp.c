/********************************************************************/
/*
      FILE        :   knFn.h
      Name        :   Chalearm Saelim
      Date        :   28 Decenber 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to keep the kernel function setting

      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        07-01-2018    csaelim    First draft 
*/
/*******************************************************************/
#include <stdio.h>
#include "knFn.h"
#include "eleXMLNodeList.h"
#include "simReadXML.h"
#include "basicVarArea.h"

#define DEF_GAUSSIAN_VAL        "GAUSSIAN_VAL"
#define DEF_POLYNOMIAL          "POLYNOMIAL"
#define DEF_SIGMOID_VAL         "SIGMOID_VAL"

#define DEF_ATTRB_MX            "max"
#define DEF_ATTRB_MN            "min"

#define DEF_ATTRB_TYPE          "type" 
#define DEF_ATTRB_STP           "step"
#define DEF_ATTRB_TRY_ALL       "tryAll" 
#define DEF_ATTRB_OFS           "offset" 

int constructorKernelFnHdl(struct kFnHdl *obj, void *kernelEle)
{
    int isTryAll = 0;
    int ret = (initialDefValKernelFnHdl(obj) == 1) && (kernelEle != NULL);
    //3open
    ret = (ret == 1) && getAttrbValXMLEle2Var2(kernelEle,DEF_ATTRB_TYPE,"0",(void*)&(m_type),0x010);
    ret = (ret == 1) && getAttrbValXMLEle2Var2(kernelEle,DEF_ATTRB_TRY_ALL,"0",(void*)&(isTryAll),0x010);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(kernelEle,DEF_GAUSSIAN_VAL,DEF_ATTRB_MX,"0.0",(void*)&(m_gaussMx),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(kernelEle,DEF_GAUSSIAN_VAL,DEF_ATTRB_MN,"0.0",(void*)&(m_gaussMn),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(kernelEle,DEF_GAUSSIAN_VAL,DEF_ATTRB_OFS,"0.0",(void*)&(m_gaussStp),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(kernelEle,DEF_POLYNOMIAL,DEF_ATTRB_MX,"0.0",(void*)&(m_polyMx),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(kernelEle,DEF_POLYNOMIAL,DEF_ATTRB_MN,"0.0",(void*)&(m_polyMn),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(kernelEle,DEF_POLYNOMIAL,DEF_ATTRB_OFS,"0.0",(void*)&(m_polyStp),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(kernelEle,DEF_POLYNOMIAL,DEF_ATTRB_OFS,"0.0",(void*)&(m_polyOffSt),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(kernelEle,DEF_SIGMOID_VAL,DEF_ATTRB_MX,"0.0",(void*)&(m_sigMMx),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(kernelEle,DEF_SIGMOID_VAL,DEF_ATTRB_MN,"0.0",(void*)&(m_sigMMn),0x050);
    ret = (ret == 1) && getAttrbValueOfFirstChildEle2Var2(kernelEle,DEF_SIGMOID_VAL,DEF_ATTRB_OFS,"0.0",(void*)&(m_sigMStp),0x050);
    
    if (ret == 1)
    {
        if((m_gaussStp > 0.0) && (m_gaussMx > m_gaussMn))
        {
            m_nSigmaLoop = (int)((0.99999+m_gaussMx-m_gaussMn)/(m_gaussStp));
        }
        else
        {
            m_nSigmaLoop = 0;
        }
        if((m_polyStp > 0.0) && (m_polyMx > m_polyMn))
        {
            m_nPolyLoop = (int)((0.99999+m_polyMx-m_polyMn)/(m_polyStp));
        }
        else
        {
            m_nPolyLoop = 0;
        }
        ret = nextParameterInKernelFnHdl(obj);
    }
    else
    {
        printf("Error(1) in constructorKernelFnHdl, Bad read XML, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    
    if (isTryAll == 0)
    {
        m_currType4Loop = -1;
    }
    else
    {
        /* loop !!*/
        m_currType4Loop = m_type;
        /* start position */
        m_currModelLoop = m_currType4Loop;
    }
    if (m_type == 0)
    {
        m_currFn = linearKernelFnInkFnHdl;
    }
    else if (m_type == 1)
    {
        m_currFn = polyKernelFnInkFnHdl;
    }
    else if (m_type == 2)
    {
        m_currFn = gausRadiusKernelFnInkFnHdl;
    }
    else if (m_type == 3)
    {
        m_currFn = sigMoidKnFnInkFnHdl;
    }
    else
    {
        m_currFn = gausRadiusKernelFnInkFnHdl;
    }
  
    //1endconstructorKernelFnHdl//2end
    return ret;
}

int nextParameterInKernelFnHdl(struct kFnHdl *obj)
{
    double sigmaVal = 0.0;
    int ret = (obj != NULL);
    //3open
    sigmaVal = m_gaussStp*(m_indexSigmaLoop++) + m_gaussMn;
    /* Radius kernel */
    if (sigmaVal > m_gaussMx)
    {
        sigmaVal = m_gaussMx;
    }
    else
    {
        /* do nothing */
    }
    if (sigmaVal != 0.0)
    {
        m_curKnVal = (-2.0)*pow(sigmaVal,2.0);
    }
    else
    {
        m_curKnVal = 1;
        printf(" Warning in nextParameterInKernelFnHdl, bad parameter, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    
    /* Poly nomial kernel */
    m_currPoly = m_polyMn +(m_indexPolyLoop++)*m_polyStp;
    if (m_currPoly == 0)
    {
        m_currPoly = 1;
    }
    else if (m_currPoly > m_polyMx)
    {
        m_polyMx = m_polyMx;
    }
    else
    {
        /* do nothing */
    }
    //1endnextParameterInKernelFnHdl//2end
    return ret;
}

int isEndloopSigmaInKFnHdl(struct kFnHdl *obj)
{
    int ret = (obj != NULL);
    //3open
    ret = (m_indexSigmaLoop >= m_nSigmaLoop);
    //1endisEndloopSigmaInKFnHdl//2end
    return ret;
}

int isEndloopPolyInKFnHdl(struct kFnHdl *obj)
{
    int ret = (obj != NULL);
    //3open
    ret = (m_indexPolyLoop >= m_nPolyLoop);
    //1endisEndloopPolyInKFnHdl//2end
    return ret;
}

int resetAllLoopInKFnHdl(struct kFnHdl *obj)
{
    int ret = (obj != NULL);
    //3open
    m_indexSigmaLoop = 0;
    m_indexPolyLoop = 0;
    //1endresetAllLoopInKFnHdl//2end
    return ret;
}
int destructKernelFnHdl(struct kFnHdl *obj)
{
    int ret = (obj != NULL);
    //3open
    ret = initialDefValKernelFnHdl(obj);
    //1enddestructKernelFnHdl//2end
    return ret; 
}

int initialDefValKernelFnHdl(struct kFnHdl *obj)
{
    int ret = (obj != NULL);
    //3open
    m_type          = 0;
    m_currType4Loop = -1; /* default no loop */
    
    m_gaussMx       = 0.0;
    m_gaussMn       = 0.0;
    m_gaussStp      = 0.0;
    
    m_polyMx        = 0.0;
    m_polyMn        = 0.0;
    m_polyOffSt     = 0.0;
    m_polyStp       = 0.0;
    
    m_sigMMx        = 0.0;
    m_sigMMn        = 0.0;
    m_sigMStp       = 0.0;
    
    m_curKnVal      = 0.0;
    m_curOff        = 0.0;
    m_currModelLoop = 0;
    
    m_currFn = NULL;
    m_indexSigmaLoop = 0;
    m_indexPolyLoop = 0;

    m_nSigmaLoop = 0;
    m_nPolyLoop  = 0;
    //1endinitialDefValKernelFnHdl//2end
    return ret;
}

void prtValKernelFnHdl(struct kFnHdl *obj)
{
    const char *space1 = "     ";
    //1open
    printf("  ----------------  KernelFnHdl obj:%p -------------------------\n",obj);
    printf("%sType     :%s(%d) \n",space1,gtTypeInStringKernelFnHdl(obj),m_type);
    printf("%sIsLoop   :%d \n",space1,m_currType4Loop);
    printf("%sgaussMx  :%f \n",space1,m_gaussMx);
    printf("%sgaussMn  :%f \n",space1,m_gaussMn);
    printf("%sgaussStp :%f \n",space1,m_gaussStp);
    printf("%spolyMx   :%f \n",space1,m_polyMx);
    printf("%spolyMn   :%f \n",space1,m_polyMn);
    printf("%spolyOffSt:%f \n",space1,m_polyOffSt);
    printf("%spolyStp  :%f \n",space1,m_polyStp);
    printf("%ssigMMx   :%f \n",space1,m_sigMMx);
    printf("%ssigMMn   :%f \n",space1,m_sigMMn);
    printf("%ssigMStp  :%f \n",space1,m_sigMStp);
    //1endprtValKernelFnHdl//2end
}

const char* gtTypeInStringKernelFnHdl(struct kFnHdl *obj)
{
    /*
     <!--   0 linear, 1 poly nomial, 2 guassian radius, 3 sigmoid, (default == 2) -->
    */
    const char *linStr    = "linear";
    const char *plStr     = "polynomial";
    const char *guassStr  = "guassian";
    const char *sigmStr   = "sigmoid";
    const char *nullStr   = "";
    const char *ch = nullStr;
    int type = 0;
    //1open
    type = m_type;
    if (type == 0)
    {
        ch = linStr;
    }
    else if (type == 1)
    {
        ch = plStr;
    }
    else if (type == 2)
    {
        ch = guassStr;
    }
    else if (type == 3)
    {
        ch = sigmStr;
    }
    else
    {
        /* do nothing */
    }
    //1endgtTypeInStringKernelFnHdl//2end
    return ch;
}

double calValByKFnInKFnHdl(struct kFnHdl *obj,const double *va,const double *vb,int numDim)
{
    double dTmp = 0.0;
    int ret = ((obj != NULL) && (va != NULL) && (vb != NULL) && (numDim > 0 ));
    //3open
    if (m_currFn != NULL)
    {
        dTmp = m_currFn(obj,va,vb,numDim);
    }
    else
    {
        printf(" Error(1) in calValByKFnInKFnHdl, m_currFn is NULL (%p), ln:%d, file:%s\n",m_currFn,__LINE__,__FILE__);
    }
    //1endcalValByKFnInKFnHdl//2end
    
    return dTmp;
}

double linearKernelFnInkFnHdl(struct kFnHdl *obj,const double *va,const double *vb, int num)
{
    double tmp = 0;
    int ret = ((obj != NULL) && (va != NULL) && (vb != NULL) && (num > 0));
    //3open
    tmp =  linearKernelFn_2(va,vb,num);

    //1endlinearKernelFnInkFnHdl//2end
    return tmp;
}

double polyKernelFnInkFnHdl(struct kFnHdl *obj,const double *va,const double *vb, int num)
{
    double tmp = 0;
    int ret = ((obj != NULL) && (va != NULL) && (vb != NULL)&& (num > 0));
    //3open
    tmp =  linearKernelFn_2(va,vb,num);
    tmp = pow(tmp+m_curOff,m_currPoly);
    //1endpolyKernelFnInkFnHdl//2end
    return tmp;
}

double gausRadiusKernelFnInkFnHdl(struct kFnHdl *obj,const double *va,const double *vb, int num)
{
    double tmp = 0;
    int ret = ((obj != NULL) && (va != NULL) && (vb != NULL)&& (num > 0));
    //3open
    tmp = diffVAbsoluateValDoub(va,vb,num);
    

    if (m_curKnVal != 0.0)
    {
        tmp = exp(tmp/m_curKnVal);
    }
    else
    {
        tmp = 1;
        printf("Error(1) in gausRadiusKernelFnInkFnHdl,m_curKnVal is 0, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    
    /*
    int index = 0;
        printf("curKnVal:%f, val:%f \n %p[",m_curKnVal,tmp,va);
    for(index = 0;index < num ;index++)
    {
        printf("%f ",va[index]);
    }printf("]\n %p[",vb);
    for(index = 0;index < num ;index++)
    {
        printf("%f ",vb[index]);
    }printf("]\n");
    
    
    */
    //1endgausRadiusKernelFnInkFnHdl//2end
    return tmp;
}

double sigMoidKnFnInkFnHdl(struct kFnHdl *obj,const double *va,const double *vb, int num)
{
    double tmp = 0;
    int ret = ((obj != NULL) && (va != NULL) && (vb != NULL)&& (num > 0));
    //3open
    tmp = (m_curKnVal)*diffVAbsoluateValDoub(va,vb,num);
    if (m_curKnVal != 0.0)
    {
        tmp = exp(tmp/m_curKnVal);
    }
    else
    {
        tmp = 1;
        printf("Error(1) in gausRadiusKernelFnInkFnHdl,m_curKnVal is 0, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    //1endsigMoidKnFnInkFnHdl//2end
    return tmp;
}
 