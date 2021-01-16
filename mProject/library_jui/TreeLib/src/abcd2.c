 /********************************************************************/
/*
      FILE        :   smoBuff.c
      Name        :   Chalearm Saelim
      Date        :   03 January 2018
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to provide the buffer for SMO


      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        03-01-2018    csaelim    First draft 
*/
/*******************************************************************/
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include "basicVarArea.h"
#include "smoBuff.h"

int setAllDat2SetSMOK1InSMOBuffer(struct SMOBuffer *obj)
{
    int indexBuff = 0;
    int ret = (obj != NULL);
    int index = 0;
    double alpha = 0;
    //3open
    ret = pushCurrIndexInSmoBuff(obj,&indexBuff);
    ret = (resetLoopIndexSMOBuffer(obj) && (ret == 1));
    while(isEndLoopInSmoBuffer(obj) != -1)
    {
        index = nxtDatInSMOBuffer(obj);
       /* if(index == 45)printf(" here is 45\n"); */
        if (index > -1)
        { 
            ret = (updateValInSMOBuff(obj,READ_ALPHA,index,&alpha) && (ret == 1));
            ret = (AddIndex2AllSetsSMOK1InSmoBffer(obj,alpha,index) && (ret == 1));
        }
        else
        {
            /* do nothing */
        }
    }
    ret = (popCurrIndexInSmoBuff(obj,indexBuff) && (ret == 1));
    //1endsetAllDat2SetSMOK1InSMOBuffer//2end
    return ret;
}

int mainLearningLoopInSMOBuffer(struct SMOBuffer *obj)
{
    double sum1 = 0.0;
    int ret = (obj != NULL);
    //3open

    unsigned int segId = 0;
    unsigned int id = 0; 
    
    int index = 0;
    int index2 = 0;
    
    int numChanged = 0;
    int examineAll = 1;
    int num = 0;  /* num sample */
    
    /*
        printSMOKMBuff(obj,0x1F00);
    */  
    ret = ((clearMemberInAllSetOfSMOBuff(obj) == 1) && (ret == 1));
    ret = ((setAllDat2SetSMOK1InSMOBuffer(obj) == 1) && (ret == 1));
    while((numChanged > 0) || (examineAll))
    {
        numChanged = 0;
        if(examineAll)
        {
            ret = pushCurrIndexInSmoBuff(obj,&index2);
            ret = (resetLoopIndexSMOBuffer(obj) && (ret == 1));
            while(isEndLoopInSmoBuffer(obj) != -1)
            {
                index = nxtDatInSMOBuffer(obj);
 /* if(index == 45)printf(" here is 45\n"); */
                if (index > -1)
                { 
                   // printf("Examine :%d  \n",index);
                    numChanged += examineExamSMOK1InSMOBuffer(obj,index);
                    //printf("numChanged:%d\n",numChanged);
                     /* 
                    printSMOKMBuff(obj,0x1F00);
                    */
                }
                else
                {
                    /* do nothing */
                }
            }
            ret = (popCurrIndexInSmoBuff(obj,index2) && (ret == 1));
        }
        else
        {
            num = getNumI0SetInSMOBuffer(obj);
            resetIdDatI0setInSMOBuffer(obj);
            /*
            printf("xxxxxxxxxxxx Else case of examine, num:%d \n",num);
            */
            for(index = 0;index < num; index++)
            {
                index2 = (int)nextDatI0setInSMOBuffer(obj);
                /*
                if (index > 140)
                {
                    printLinearByIndexSet(&(m_I0));
                    printf("index2 :%d\n",index2);
                }
                */
                if(index2 >= 0)
                {
                    /*
                    unsigned int tmpSegId = 0;
                    unsigned int tmpId = 0;
                    */
                    pushReadStateI0SetInSMOBuffer(obj,&segId,&id);
                    //  printf("loop ------------index 2 : %d, segId:%u, id:%u \n",index2,segId,id);
                    //   printf("alpha[%d]=%f ,C=%f\n",index,smoBf.m_alpha[index2],(double)C_ALPHA);
                    numChanged += examineExamSMOK1InSMOBuffer(obj,index2);
                    //pushReadStateI0SetInSMOBuffer(obj,&tmpSegId,&tmpId);
                    //   printf("after calling examine tmp SegId : %u, id :%u\n",tmpSegId,tmpId);
                    popReadStateI0SetInSMOBuffer(obj,segId,id);
                    /*printSMOKMBuff(&smoBf,0x08);*/
                    
                    if(m_b_up > (m_b_low - (2.0*(m_tol))))
                    {
                        // exit loop  
                        index = num;
                        numChanged = 0;
                    }
                    else
                    {
                        num = getNumI0SetInSMOBuffer(obj);
                    }
                   
                }
                else
                {
                    /*
                    printf("jui Update loop fail to update alpha num Lo:%d, index:%d, ln:%d\n",num,index,__LINE__);
                    */
                    /* do nothing */  
                }
            }
        }
        if(examineAll == 1)
        {
            examineAll = 0;
        }
        else if(numChanged == 0)
        {
            examineAll = 1;
        }
        else
        {
            /* do nothing */
        }
    }
    ret = (avrBiasInSMOBuffer(obj) && (ret == 1));

    printf("Hey jui Biso:%f\n",m_Bias);    
    double dAlpha = 0.0;
    double dYVal1 = 0.0;
        ret = pushCurrIndexInSmoBuff(obj,&index2);
        resetLoopIndexSMOBuffer(obj);
        while(isEndLoopInSmoBuffer(obj) != -1)
        {
            index = nxtDatInSMOBuffer(obj);

/* if(index == 45)printf(" here is 45\n"); */
            if (index > -1)
            {
                ret = (updateValInSMOBuff(obj,READ_ALPHA,index,&dAlpha) && (ret == 1));
                ret = (updateValInSMOBuff(obj,READ_YCURR,index,&dYVal1) && (ret == 1));
                
                sum1 += dAlpha*dYVal1;
            }
        }
        ret = (popCurrIndexInSmoBuff(obj,index2) && (ret == 1));
        printf("SIGMA YiAi = %f \n",sum1);
    /*
    for(index = 0;index < num; index++)
    {
        sum1 += smoBf.m_alpha[index]*inp.m_out[index];
        printf("i:%d  y:%d, fx:%f, y*alpha:%0.39f\n",index,(int)inp.m_out[index],learnSMOFx(&smoBf,index,gausRadiusKernelFn),smoBf.m_alpha[index]*inp.m_out[index]);
    }

    printf("Call taskStep :%u\n",countCallTask);
    clearInputSet(&inp); 
    clearSMOKMBuff(&smoBf);
    delete_vector_double(&vBuff);
    return 0;
    */
    //1endmainLearningLoopInSmoK1Learner//2end
    return ret;
}

int AddIndex2AllSetsSMOK1InSmoBffer(struct SMOBuffer *obj,double alpha,int index1)
{
    int ret = 1;
    double yTmp = 0.0;
    long int index = (long int)index1;

    if ( obj != NULL)
    {
        ret = updateValInSMOBuff(obj,READ_YCURR,index1,&yTmp);
        if(alpha > 0.0)
        {
            ret = added2RVSet(&(m_supportVectSet),&index);
        }
        else
        {
            removedValRVSet(&(m_supportVectSet),&index,1);
        }
        if((alpha > 0.0) && (alpha < m_cSVM))
        {
            ret =(ret == 1) && added2RVSet(&(m_I0),&index);
        }
        else
        {
            /* printLinearByIndexSet(&(m_I0)); */
            /* printf("remove index:%ld \n",index); */
            removedValRVSet(&(m_I0),&index,1);
            /*   printLinearByIndexSet(&(m_I0)); */
        }
        
        if((alpha == 0.0) && (yTmp == 1.0))
        {
            ret =(ret == 1) && added2RVSet(&(m_I1),&index);
        }
        else
        {
            removedValRVSet(&(m_I1),&index,1);
        }
        
        if((alpha == m_cSVM)&&(yTmp == -1.0))
        {
            ret =(ret == 1) && added2RVSet(&(m_I2),&index);
        }
        else
        {
            removedValRVSet(&(m_I2),&index,1);
        }
        if((alpha == m_cSVM)&&(yTmp == 1.0))
        {
            ret =(ret == 1) && added2RVSet(&(m_I3),&index);
        }
        else
        {
            removedValRVSet(&(m_I3),&index,1);
        }
        if((alpha == 0.0) && (yTmp == -1.0))
        {
            ret =(ret == 1) && added2RVSet(&(m_I4),&index);
        }
        else
        {
            removedValRVSet(&(m_I4),&index,1);
        }
    }
    else
    {
        ret = 0;
        printf("Error Parameter in  AddIndex2AllSetsSMOK1InSmoBffer (SmoBffer obj):%p, id:%ld, ln:%d File:%s \n",obj,index,__LINE__,__FILE__);
    }
    return ret;

}

void updateBiasAndIndexLowUpSMOK1InSmoBffer(struct SMOBuffer *obj,int index)
{
    double dFTmp = 0.0;
    int ret = updateValInSMOBuff(obj,READ_FVAL,index,&dFTmp);
    if ( (ret == 1) && ( index >= 0 ))
    {
        if(dFTmp < m_b_up)
        {
            m_b_up = dFTmp;
            m_i = index;
        }
        else
        {
            /* do nothing */
        }
        if(dFTmp > m_b_low)
        {
            m_b_low = dFTmp;
            m_j = index;
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

void checkObjFnAlpha2SMOK1InSmoBffer(double *L1,double *L2,double *H1,double *H2)
{
    if((L1 != NULL)&&(L2 != NULL)&&(H1 != NULL)&&(H2 != NULL))
    {
        if((*L1!=*L2)||(*H1!=*H2))
        {
            printf("i357: Found something wrong \n");
            printf("Lobj : %f, org:%f\n",*L1,*L2);
            printf("Hobj : %f, org:%f\n",*H1,*H2);
            printf("End of i357: Found something wrong \n");
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        /* do nothing */
    }
}

double objectiveFnAlphaSMOK1InSmoBffer(struct SMOBuffer *obj,double alpha2)
{
    double y2 = 0.0;
    double c1 = 0.0;
    int ret = (obj != NULL);
    //3open
    c1 = (0.5)*(m_currEta);
    ret = (updateValInSMOBuff(obj,READ_YCURR,(int)(m_index2),&(y2)) && (ret == 1));
    c1 =  c1*pow(alpha2,2)+alpha2*((y2*(m_F1 - m_F2))-((m_currEta)*(m_alpha2)));
    //1endobjectiveFnAlphaSMOK1InSmoBffer//2end
    return c1;
}

double objectiveFnAlphaOrgnSMOK1InSmoBffer(struct SMOBuffer *obj,double alpha2)
{
    double f1 = 0.0;
    double f2 = 0.0;
    double v1 = 0.0;
    double v2 = 0.0;
    double gamma = 0.0;
    double ret = 0.0;
    double delTmp = 0.0;
    if ((obj != NULL) && (alpha2 >=0.0))
    {
        gamma = (m_alpha1)+((m_s)*(m_alpha2));
        
        delTmp = gamma - ((m_s)*alpha2);
        f1 = learnSMOFxInSMOBuffer(obj,(int)m_index1);
        f2 = learnSMOFxInSMOBuffer(obj,(int)m_index2);
        v1 = f1+(m_Bias) - ((m_y1)*(m_alpha1)*(m_k11))-((m_y2)*(m_alpha2)*(m_k12));
        v2 = f2+(m_Bias) - ((m_y1)*(m_alpha1)*(m_k12))-((m_y2)*(m_alpha2)*(m_k22));
        ret = delTmp +(alpha2) - 
              ((0.5)*(m_k11)*delTmp*delTmp) - 
              ((0.5)*(m_k22)*alpha2*alpha2)-
              ((m_s)*(m_k12)*delTmp*alpha2)-
              ((m_y1)*delTmp*v1)-
              ((m_y2)*alpha2*v2);
    }
    else
    {
        printf("objectiveFnAlphaOrgn alp2:%f cannot operate, File:%s ln:%d \n",alpha2,__FILE__,__LINE__);
    }
    return ret;
}

void compLAndHInTakeStpSMOK1InSmoBffer(struct SMOBuffer *obj,double *L,double *H)
{
    if((obj != NULL)&&(L != NULL)&&(H != NULL))
    {        
        if( m_y1 == m_y2)
        {
            *L = maxVal(0.0,m_alpha2+m_alpha1-m_cSVM);
            *H = minVal(m_cSVM,m_alpha2+m_alpha1);
        }
        else
        {
            *L = maxVal(0.0,m_alpha2 - m_alpha1);
            *H = minVal(m_cSVM,m_cSVM + m_alpha2 - m_alpha1);
        }
    }
    else
    {
        printf("computeLAndHInTakeStep cannot operate, File:%s, ln:%d\n",__FILE__,__LINE__);
    }
}

int takeStepSMOK1InSmoBffer(struct SMOBuffer *obj)
{
  /*  printf("Start takeStepSMOK1InSmoBffer \n"); */
    double *vSmp1 = NULL;
    double *vSmp2 = NULL;
    double *vSmp3 = NULL;
    int ret = 1;
    double L = 0.0;
    double H = 0.0;
    double k1i = 0.0;
    double k2i = 0.0;
    double a1 = 0;
    double a2 = 0;
    double Lobj = 0.0;
    double Hobj = 0.0;
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    double tmp3 = 0.0;
    int index = 0;
    int index3 = 0;
    int num = 0;
    int index1 = m_index1;
    int index2 = m_index2;
    if(index1 != index2)
    {
    //countCallTask++;
        ret = (updateValInSMOBuff(obj,READ_ALPHA,index1,&(m_alpha1)) && (ret == 1));
        ret = (updateValInSMOBuff(obj,READ_YCURR,index1,&(m_y1)) && (ret == 1));
        ret = (updateValInSMOBuff(obj,READ_FVAL,index1,&(m_F1)) && (ret == 1));
        m_s = (m_y1)*(m_y2);
        compLAndHInTakeStpSMOK1InSmoBffer(obj,&L,&H);
/*printf("index1 :%d , %ld, index2:%d (H,L):(%f,%f), (F1,F2):(%f,%f), a1:%f, a2:%f\n",index1,m_index1,index2,H,L,m_F1,m_F2,m_alpha1,m_alpha2);
*/        if(L != H)
        {
            ret = (gtSampleInputDtInDtSp(m_dtSp,index1,&vSmp1) && (ret == 1));
            ret = (gtSampleInputDtInDtSp(m_dtSp,index2,&vSmp2) && (ret == 1));
            m_k11 = calValByKFnInKFnHdl(m_kernelFn1,vSmp1,vSmp1,m_dim);
            m_k22 = calValByKFnInKFnHdl(m_kernelFn1,vSmp2,vSmp2,m_dim);
            m_k12 = calValByKFnInKFnHdl(m_kernelFn1,vSmp1,vSmp2,m_dim);
            m_currEta = (2*(m_k12))-(m_k11)-(m_k22);
/*printf("k11:%f, k22:%f, k12:%f, Eta:%f \n",m_k11,m_k22,m_k12,m_currEta);
  */          if(m_currEta <0)
            {
                a2 = m_alpha2-((m_y2)*(m_F1 - m_F2)/(m_currEta));
/*printf("Eta <0 --> a2 : %f ",a2); */
                if(a2 < L)
                {
                    a2 = L;
                }
                else if(a2 > H)
                {
                    a2 = H;
                }
                else
                {
                    /* do nothing */
                }
/*
                printf(" new a2:%f\n",a2);*/
            }
            else
            {
                tmp1 = objectiveFnAlphaOrgnSMOK1InSmoBffer(obj,L);
                tmp2 = objectiveFnAlphaOrgnSMOK1InSmoBffer(obj,H);
                Lobj = objectiveFnAlphaSMOK1InSmoBffer(obj,L);
                Hobj = objectiveFnAlphaSMOK1InSmoBffer(obj,H);
                /* temporary uesed to compare the result between 2 methods:
                objectiveFnAlphaOrgnSMOK1InSmoBffer and objectiveFnAlphaSMOK1InSmoBffer */
                checkObjFnAlpha2SMOK1InSmoBffer(&Lobj,&tmp1,&Hobj,&tmp2);
              //  printf("(Lobj,Hobj):(%f,%f)\n",Lobj,Hobj);
                if(Lobj > Hobj + m_eps)
                {
                    a2 = L;
                }
                else if(Lobj < Hobj - m_eps)
                {
                    a2 = H;
                }
                else 
                {
                    a2 = m_alpha2;
                }
            }
            
            // this is used in original SMO, 31 August 2017
            // make it used, 03 September 2017
            if(a2 < m_roundNum)
            {
                a2 = 0.0;
            }
            else if(a2 > m_cSVM - m_roundNum)
            {
                a2 = m_cSVM;
            }
            else
            {
                /* do nothing */
            }
           
            if(absf(a2- m_alpha2)<(m_eps)*(a2+ m_alpha2+m_eps))
            {
                ret = 0;
            }
            else
            {              
                /*
                    Update threshold to reflect change in Lagrange multipliers
                    Update weight vector to reflect change in a1 & a2, if linear SVM
                    Update error cache using new Lagrange multipliers
                    Store a1 in the alpha array
                    Store a2 in the alpha array
                */
                a1 = m_alpha1+(m_s)*(m_alpha2-a2);
                if(a1 < m_roundNum)
                {
                    a1 = 0.0;
                }
                else if(a1 > m_cSVM - m_roundNum)
                {
                    a1 = m_cSVM;
                }
                else
                {
                    /* do nothing */
                }
                
                tmp1 = (m_y1)*(a1 - m_alpha1);
                tmp2 = (m_y2)*(a2 - m_alpha2);
                
                /* update sets, 3 september 2017 */
                ret = ret && (AddIndex2AllSetsSMOK1InSmoBffer(obj,a1,index1));
                ret = ret && (AddIndex2AllSetsSMOK1InSmoBffer(obj,a2,index2));
                m_i = -1;
                m_j = -1;
                m_b_low = -DBL_MAX;
                m_b_up = DBL_MAX; 
                resetIdDatI0setInSMOBuffer(obj);
                num = (int)getNumI0SetInSMOBuffer(obj);
                /*printf("the number of member in I0 set is : %d\n",num); */
                ret = (gtSampleInputDtInDtSp(m_dtSp,index1,&vSmp1) && (ret == 1));
                ret = (gtSampleInputDtInDtSp(m_dtSp,index2,&vSmp2) && (ret == 1));
/*printf("Start loop to update alpha num Lo:%d \n",num);*/
               for(index = 0; index < num; index++)
                {
                    index3 = nextDatI0setInSMOBuffer(obj);
                   
                    if (index3 >= 0)
                    {
                        ret = (gtSampleInputDtInDtSp(m_dtSp,index3,&vSmp3) && (ret == 1));
        if(ret == 0 )
        {
             printf("error Index3 : %d\n",(int)index3);
        }
                        k1i = calValByKFnInKFnHdl(m_kernelFn1,vSmp1,vSmp3,m_dim);
                        k2i = calValByKFnInKFnHdl(m_kernelFn1,vSmp2,vSmp3,m_dim);
                        ret = (updateValInSMOBuff(obj,READ_FVAL,index3,&(tmp3)) && (ret == 1));
                        tmp3 = tmp3 +(k1i*tmp1)+(k2i*tmp2);
                        ret = (updateValInSMOBuff(obj,WRITE_FVAL,index3,&(tmp3)) && (ret == 1));
                        updateBiasAndIndexLowUpSMOK1InSmoBffer(obj,index3);
                        vSmp3 = NULL;
                    }
                    else
                    {
                        printf("Update loop fail to update alpha num Lo:%d, index:%d\n",num,index);
                        /* do nothing */
                    }
                }
/*  printf("End loop to update alpha \n");   */
                tmp3 = (m_F1) +(m_y1)*(m_k11)*(a1-m_alpha1)+((m_y2)*(m_k12)*(a2-m_alpha2));
                ret = (updateValInSMOBuff(obj,WRITE_FVAL,index1,&(tmp3)) && (ret == 1));
                tmp3 = (m_F2) +(m_y1)*(m_k12)*(a1-m_alpha1)+((m_y2)*(m_k22)*(a2-m_alpha2));
                ret = (updateValInSMOBuff(obj,WRITE_FVAL,index2,&(tmp3)) && (ret == 1));
                updateBiasAndIndexLowUpSMOK1InSmoBffer(obj,index1);
                updateBiasAndIndexLowUpSMOK1InSmoBffer(obj,index2);
              /*  printf("Update alpha1(%d):%f , alpha2(%d):%f \n",index1,a1,index2,a2); */
                ret = (updateValInSMOBuff(obj,WRITE_ALPHA,index1,&(a1)) && (ret == 1));
                ret = (updateValInSMOBuff(obj,WRITE_ALPHA,index2,&(a2)) && (ret == 1));

                if(isInRVSet(&(m_I0),&(m_index1)) == 0)
                {
                    ret = (updateValInSMOBuff(obj,2,(int)(m_index1),&(tmp3)) && (ret == 1));
                    if((isInRVSet(&(m_I3),&(m_index1)) == 1)||(isInRVSet(&(m_I4),&(m_index1)) == 1))
                    {
                        if(tmp3 > m_b_low)
                        {
                            m_b_low = tmp3;
                            m_j = m_index1;
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    else if (tmp3 < m_b_up)
                    {
                        m_b_up = tmp3;
                        m_i = m_index1;
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
                if(isInRVSet(&(m_I0),&(m_index2)) == 0)
                {
                    ret = (updateValInSMOBuff(obj,READ_FVAL,(int)(m_index2),&(tmp3)) && (ret == 1));
                    if((isInRVSet(&(m_I3),&(m_index2)) == 1)||(isInRVSet(&(m_I4),&(m_index2)) == 1))
                    {
                        if(tmp3 > m_b_low)
                        {
                            m_b_low = tmp3;
                            m_j = m_index2;
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    else if (tmp3 < m_b_up)
                    {
                        m_b_up = tmp3;
                        m_i = m_index2;
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
                avrBiasInSMOBuffer(obj);
                if ((m_j == -1) || (m_i == -1))
                {
                    printf("Error I low/up : %ld/%ld , Ln:%d, File:%s\n",m_j,m_i,__LINE__,__FILE__);
                }
                else
                {
                    /* do nothing */
                }
                /*
for(index = 0; index < num; index++)
{
    printf("error[%d]:%f, alpha:%f \n",index,obj->m_fCache[index],obj->m_alpha[index]);
}
printf("New Bias:%f \n",m_Bias);
*/
            }
        }
        else
        {
            ret = 0;
        }
    }
    else
    {
        ret = 0;
    }
  /*  printf("End takeStepSMOK1InSmoBffer \n");*/
    return ret;
}



int examineExamSMOK1InSMOBuffer(struct SMOBuffer *obj,int index)
{
    /*printf(" Start examineExamSMOK1InSMOBuffer \n");*/
    double dY2 = 0.0;
    double dA2 = 0.0;
    double dF2 = 0.0;
    int optimality = 1;
    int ret = 1;
    ret = (updateValInSMOBuff(obj,READ_ALPHA,index,&dA2) && (ret == 1));
    ret = (updateValInSMOBuff(obj,READ_YCURR,index,&dY2) && (ret == 1));
    m_y2 = dY2;
    m_alpha2 = dA2;
    m_index2 = index;

    /*printf("Exam index:%d \n",index); */
    if(isInRVSet(&(m_I0),&(m_index2)) == 1) /* if i2 is in I_0*/
    {
        ret = (updateValInSMOBuff(obj,READ_FVAL,index,&dF2) && (ret == 1));
        m_F2 = dF2;
    }
    else
    {
        m_F2 = learnSMOFxInSMOBuffer(obj,m_index2) + m_Bias - m_y2;
        ret = (updateValInSMOBuff(obj,WRITE_FVAL,index,&(m_F2)) && (ret == 1));
     /*  printf("Not is in I0 set, I:%d F2:%f\n",index,m_F2); */
    //printSMOKMBuff(obj,0x28);
        if((isInRVSet(&(m_I1),&(m_index2))||isInRVSet(&(m_I2),&(m_index2)))&&(m_F2 < m_b_up))
        {
            m_b_up = m_F2;
            m_i = m_index2;
        }
        else if((isInRVSet(&(m_I3),&(m_index2))||isInRVSet(&(m_I4),&(m_index2)))&&(m_F2 > m_b_low))
        {
            m_b_low = m_F2;
            m_j = m_index2;
        }
        else
        {
            /* printf("not is in I1, I2, I3 and I4 \n");  */
            /* do nothing */
        }
        /*printSMOKMBuff(obj,0x39); */
    }
    optimality = 1;
     /*printf("F2 - b_up = %f ,2*tol:%f \n",(m_F2 - m_b_up),(2.0*(m_tol))); */
    if((isInRVSet(&(m_I0),&(m_index2)))||(isInRVSet(&(m_I1),&(m_index2)))||(isInRVSet(&(m_I2),&(m_index2))))
    {
        if((m_b_low-m_F2) > (2.0*(m_tol)))
        {
            optimality = 0;
            m_index1 = m_j;
           /* printf("Is not opt 1, index1:%ld\n",m_index1); */
        }
        else
        {
          /*  printf("  Examine  Else Case 1\n");*/
            /* do nothing */
        }
    }
    else if((isInRVSet(&(m_I0),&(m_index2)))||(isInRVSet(&(m_I3),&(m_index2)))||(isInRVSet(&(m_I4),&(m_index2))))
    {
        if((m_F2 - m_b_up) > (2.0*(m_tol)))
        {
            optimality = 0;
            m_index1 = m_i;
         /*   printf("Is not opt 2, index1:%ld\n",m_index1); */
        }
        else
        {
            
           /* printf("  Examine  Else Case 2\n"); */
            /* do nothing */
        }
    }
    else
    {
      /*  printf("No entre in Opt=0\n"); */
    }
    /*
     printf("optimality :%d, index2: %ld\n",optimality,m_index2);  
     */
    if(optimality == 0)
    {
        if(isInRVSet(&(m_I0),&(m_index2)) == 1)
        {
            if((m_b_low - m_F2) > (m_F2- m_b_up))
            {
                m_index1 = m_j;
            }
            else
            {
                m_index1 = m_i;
            }

        }
        else
        {
            /* do nothing */
        }
    
        if(takeStepSMOK1InSmoBffer(obj))
        {
            ret = 1;
        }
        else
        {
            ret = 0;
        }
    }
    else
    {
        ret = 0;
    }
    
    /*printf(" End examineExamSMOK1InSMOBuffer \n");*/
    return ret;
}
double learnSMOFxInSMOBuffer(struct SMOBuffer *obj,int indexP)
{
    int indexBuff = 0;
    double *vSmp1 = NULL;
    double *vSmp2 = NULL;
    double dAlpha = 0.0;
    double dYVal1 = 0.0;
    double dSum = 0.0;
    double tmp3 = 0.0;
    int index = 0;
    int ret =  ((obj != NULL) && (indexP > -1));
    //3open
    ret = gtSampleInputDtInDtSp(m_dtSp,indexP,&vSmp2);
    if (ret == 1)
    {
        ret = pushCurrIndexInSmoBuff(obj,&indexBuff);
        resetLoopIndexSMOBuffer(obj);
        while(isEndLoopInSmoBuffer(obj) != -1)
        {
            index = nxtDatInSMOBuffer(obj);
/* if(index == 45)printf(" here is 45\n"); */
            if (index > -1)
            {
                
                ret = (gtSampleInputDtInDtSp(m_dtSp,index,&vSmp1) && (ret == 1));
                ret = (updateValInSMOBuff(obj,READ_ALPHA,index,&dAlpha) && (ret == 1));
                ret = (updateValInSMOBuff(obj,READ_YCURR,index,&dYVal1) && (ret == 1));
                if (dAlpha > 0.0)
                {
                    tmp3 = calValByKFnInKFnHdl(m_kernelFn1,vSmp1,vSmp2,m_dim);
                  /*  printf("learnFx index:%d, indexP:%d, val:%f ",index,indexP,tmp3);
                     double calValByKFnInKFnHdl(struct kFnHdl *obj,const double *va,const double *vb,int numDim)*/
                    dSum += dAlpha*dYVal1*(tmp3);
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
        ret = (popCurrIndexInSmoBuff(obj,indexBuff) && (ret == 1));
        if (ret == 0)
        {
            dSum = 0;
            printf("Error(2) in learnSMOFxInSmoK1Learner, this is not done: ln:%d, file:%s\n",__LINE__,__FILE__);
        }
        else
        {
            dSum = dSum - m_Bias;
        }
    }
    else
    {
        printf("Error(1) in learnSMOFxInSMOBuffer, Cannot get value from data space(indexP:%d): ln:%d, file:%s\n",indexP,__LINE__,__FILE__);
    } 
    //1endlearnSMOFxInSMOBuffer//2end
    return dSum;
}
int getNumI0SetInSMOBuffer(struct SMOBuffer *obj)
{
    int ret = 0;
    //1open
    ret = numEleRVSetNotRedunt(&(m_I0));
    //1endgetNumI0SetInSMOBuffer//2end
    return ret;
}
int nextDatI0setInSMOBuffer(struct SMOBuffer *obj)
{
    int ret = -1;
    void *tmp = NULL;
    //1open
    tmp = getNxtDatInRVSet(&(m_I0));
    if(tmp != NULL)
    {
        ret = (int)(*((long int*)tmp));
    }
    else
    {
        printf(" Error(1) in nextDatI0setInSMOBuffer, cannot get the value in Set, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    //1endnextDatI0setInSMOBuffer//2end
    return ret;
}

int pushReadStateI0SetInSMOBuffer(struct SMOBuffer *obj,unsigned int *segId,unsigned int *id)
{
    int ret = ((obj != NULL) && (segId != NULL) && (id != NULL));
    //3open
    pushStateNxtDat(&(m_I0),segId,id);
    //1endpushReadStateI0SetInSMOBuffer//2end
    return ret;
}

int popReadStateI0SetInSMOBuffer(struct SMOBuffer *obj,const unsigned int segId,const unsigned int id)
{
    int ret = (obj != NULL);
    //3open
    popStateNxtDat(&(m_I0),segId,id);
    //1endpopReadStateI0SetInSMOBuffer//2end
    return ret;
}
int resetIdDatI0setInSMOBuffer(struct SMOBuffer *obj)
{
    int ret = (obj != NULL);
    //3open
    resetGetNxtDat(&(m_I0));
    //1endresetIdDatI0setInSMOBuffer//2end
    return ret;
}


int avrBiasInSMOBuffer(struct SMOBuffer *obj)
{
    int ret = (obj != NULL);
    //3open
    m_Bias = (m_b_up + m_b_low)/2.0;
    //1endavrBiasInSMOBuffer//2end
    return ret;
}

int initialSMOBufEle(struct SMOBufferEle *obj)
{
    int ret = (obj != NULL);
    //3open
    m_alpha = 0.0;
    m_fVal = 0.0; /* or error  */
    m_yCurr = 0; /* 0 is not defined */
    //1endinitialSMOBufEle//2end
    return ret;
}

void prntSMOBuffEle(struct SMOBufferEle *obj)
{
    //1open
    printf("  y:%d, alp:%f, fVal:%f\n",m_yCurr,m_alpha,m_fVal);
    //1endprntSMOBuffEle//2end
}

int constructorSMOBufEle(struct SMOBufferEle *obj)
{
    return (initialSMOBufEle(obj) == 1);
}

int destructorSMOBufEle(struct SMOBufferEle *obj)
{
    return (initialSMOBufEle(obj) == 1);
}
int setYVal2SMOBuffEle(struct SMOBufferEle *obj,int val)
{
    int ret = (obj != NULL);
    //3open
    m_yCurr = val;
    //1endsetYVal2SMOBuffEle//2end
    
    return ret;
}

 

/*
    updateMet  : (update method)
    READ_ALPHA : read  m_alpha
    WRITE_ALPHA: write m_alpha
    READ_FVAL  : read  m_fVal
    WRITE_FVAL : write m_fVal
    READ_YCURR : read m_yCurr
    WRITE_YCURR: write m_yCurr
*/
int updateValInSMoBuffEle(struct SMOBufferEle *obj,int updateMet,double *val)
{
    int ret = ((obj != NULL) && (updateMet >= 0) && (updateMet < 6) && (val != NULL));
    //3open
    
    if ((*val > 18.0) && (*val < 19.9))
    {
        printf("----XXX obj:%p, al:%f, fVal:%f, yCurr:%d\n",obj,m_alpha,m_fVal,m_yCurr);
    }
    switch (updateMet)
    {
        case 0:
            *val = m_alpha;
        break;
        case 1:
            m_alpha = *val;
        break;
        case 2:
            *val = m_fVal;
        break;
        case 3:
            m_fVal = *val;
        break;
        case 4:
            *val = (double)(m_yCurr);
        break;
        case 5:
            m_yCurr = (int)(*val);
        break;
    }
    //1endupdateValInSMoBuffEle//2end
    return ret;
}
int flushAllValOfSMOBuffEle2DefaultInSMOBuff(struct SMOBuffer *obj)
{
    int index = 0;
    int num = 0;
    int ret = (obj != NULL);
    //3open
    num = m_nBuff;
    for (index = 0;index < num;index++)
    {
        ret = ((initialSMOBufEle(&(m_smoBuffEle[index])) == 1) && (ret == 1));
    }
    //1endflushAllValOfSMOBuffEle2DefaultInSMOBuff//2end
    return ret;
}

int clearMemberInAllSetOfSMOBuff(struct SMOBuffer *obj)
{
    int ret = (obj != NULL);
    //3open
    ret = (clearMemberOutInRVSet(&(m_I0)) && (ret == 1));
    ret = (clearMemberOutInRVSet(&(m_I1)) && (ret == 1));
    ret = (clearMemberOutInRVSet(&(m_I2)) && (ret == 1));
    ret = (clearMemberOutInRVSet(&(m_I3)) && (ret == 1));
    ret = (clearMemberOutInRVSet(&(m_I4)) && (ret == 1));
    ret = (clearMemberOutInRVSet(&(m_supportVectSet)) && (ret == 1));
    //1endclearMemberInAllSetOfSMOBuff//2end
    return ret;
}

int resetLoopIndexSMOBuffer(struct SMOBuffer *obj)
{
    int ret = (obj != NULL);
    //3open
    m_currIndex = 0;
    //1endresetLoopIndexSMOBuffer//2end
    return ret;
}

int nxtDatInSMOBuffer(struct SMOBuffer *obj)
{
    int ret = 0;
    int index = 0;
    int num = 0;
    double dTmp = 0.0;
    //1open
    num = m_nBuff;
    for (index = m_currIndex;index < num;index++)
    {
        updateValInSMOBuff(obj,READ_YCURR,index,&dTmp);
        if (dTmp != 0.0)
        {
            m_currIndex = index;
            index = num+1;
        }
        else
        {
            /* do nothing */
        }
    }
    if (index == num)
    {
        /* end of loop */
        m_currIndex = -1;
        ret = -1;
    }
    else
    {
        ret = m_currIndex++;
    }
    //1endnxtDatInSMOBuffer//2end
    return ret;
}
int pushCurrIndexInSmoBuff(struct SMOBuffer *obj, int *id)
{
    int ret = ((obj != NULL) && (id != NULL));
    //3open
    *id = m_currIndex;
    //1endpushCurrIndexInSmoBuff//2end
    return ret;
}
int popCurrIndexInSmoBuff(struct SMOBuffer *obj,const int  id)
{
    int ret = (obj != NULL);
    //3open
    if (id < m_nBuff)
    {
        m_currIndex = id;
    }
    else
    {
        printf(" Error(1) in popCurrIndexInSmoBuff, id(%d) is greater than (%d), ln:%d , file:%s\n",id,m_nBuff,__LINE__,__FILE__);
    }
    //1endpopCurrIndexInSmoBuff//2end
    return ret;
}
int isEndLoopInSmoBuffer(struct SMOBuffer *obj)
{
    int ret = -1;
    //1open
    ret = m_currIndex;
    //1endisEndLoopInSmoBuffer//2end
    return ret;
}
int initialSMOBuff(struct SMOBuffer *obj)
{
    int ret = (obj != NULL);
    //3open
    m_kernelFn1 = NULL;
    m_dtSp = NULL;
    m_smoBuffEle = NULL;
    m_nBuff = 0;
    
    m_tol = 0.00002;
    m_cSVM = 40;
    m_roundNum = 0.00000001;
    m_eps = 0.00001;
    m_i = -1;
    m_j = -1;
    m_Bias  = 0.0;
    m_b_up  =  DBL_MAX; /* Bias Upper bound*/
    m_b_low = -DBL_MAX; /* Bias Lower bound*/
    
    m_y1    = 0.0;
    m_y2    = 0.0;
    m_F1    = 0.0;
    m_F2    = 0.0;
    m_s     = 0.0;
    m_k11   = 0.0;
    m_k22   = 0.0;
    m_k12   = 0.0;
    
    m_alpha1  = 0.0;
    m_alpha2  = 0.0;
    m_currEta = 0.0;
    m_index1 = 0;
    m_index2 = 0;
    m_currIndex = 0;
    //1endinitialSMOBuff//2end
    return ret;
}

int stObjParamsInSMOBuff(struct SMOBuffer *obj, struct kFnHdl *kObj,struct datSpace *dObj)
{

    int ret = ((obj != NULL) && (kObj != NULL) && (dObj != NULL));
    //3open
    m_kernelFn1 = kObj;
    m_dtSp = dObj;
    //1endstObjParamsInSMOBuff//2end
    return ret;
}

int stValParamsInSMoBuff(struct SMOBuffer *obj,const double tol,const double cSVM,const double eps,const double roundN)
{
    int ret = ((obj != NULL) && (cSVM > 0.0));
    //3open
    m_tol = tol;
    m_cSVM = cSVM;
    m_roundNum = roundN;
    m_eps = eps;
 /*
    printf("tol       :%0.15f \n",m_tol);
    printf("roundNum  :%0.15f \n",m_roundNum);
    printf("eps       :%0.15f \n",m_eps);
    printf("C svm     :%7.0f \n",m_cSVM);
    */
    //1endstValParamsInSMoBuff//2end
    return ret;
}

int stNDimParamInSMOBuff(struct SMOBuffer *obj, const int nDim)
{
    int ret = ((obj != NULL) && (nDim > 0));
    //3open
    m_dim = nDim;
    //1endstValParamsInSMoBuff//2end
    return ret;
}

int constructorSMOBuff(struct SMOBuffer *obj, int sizeBuff)
{
    int index = 0;
    int num = 0;
    int tmp = 0;
    int ret = ((initialSMOBuff(obj) == 1) && (sizeBuff > 0));
    //3open
    m_smoBuffEle = (struct SMOBufferEle*)malloc(sizeof(struct SMOBufferEle)*sizeBuff);
    constructorRVSet(&(m_I0),6);
    constructorRVSet(&(m_I1),6);
    constructorRVSet(&(m_I2),6);
    constructorRVSet(&(m_I3),6);
    constructorRVSet(&(m_I4),6);
    constructorRVSet(&(m_supportVectSet),6);
    if (m_smoBuffEle != NULL)
    {
        m_nBuff = sizeBuff;
        num = sizeBuff; 
        for (index = 0; index < num ; index++)
        { 
            tmp = (constructorSMOBufEle(&(m_smoBuffEle[index])) == 1);
            ret = ((ret == 1) && (tmp == 1) );
        }
    }
    else
    {
        ret = 0;
        printf(" Error(1) in constructorSMOBuff, cannot allocate, size:%d, ln:%d, file:%s\n",sizeBuff,__LINE__,__FILE__);
    }
    
    //1endconstructorSMOBuff//2end
    return ret;
}

int destructorSMOBuff(struct SMOBuffer *obj)
{
    int ret = (obj != NULL);
    //3open
    destructorRVSet(&(m_I0));
    destructorRVSet(&(m_I1));
    destructorRVSet(&(m_I2));
    destructorRVSet(&(m_I3));
    destructorRVSet(&(m_I4));
    destructorRVSet(&(m_supportVectSet));
    if (m_smoBuffEle != NULL)
    {
       free(m_smoBuffEle);
    }
    else
    {
        /* do nothing */
    }
    ret = (initialSMOBuff(obj) == 1);
    //1enddestructorSMOBuff//2end
    return ret;
}

void prntSMOBuff(struct SMOBuffer *obj)
{
    int index = 0;
    int num = 0;
    //1open
    printf("SMO Buff:%p, (i,j):(%ld,%ld)\n",obj,m_i,m_j);
    printf("buff size :%d \n",m_nBuff);
    num = m_nBuff;
    for (index = 0;index < num;index++)
    {
        
        printf("i:%d ",index);prntSMOBuffEle(&(m_smoBuffEle[index]));
       
        if (index%10 == 9)
        {
           // printf("\n");
        }
        else
        {
            /* do nothing */
        }
    } 
    //1endprntSMOBuff//2end
}
/*
    updateMet : (update method)
    0         : read  m_alpha
    1         : write m_alpha
    2         : read  m_fVal
    3         : write m_fVal
    4         : read m_yCurr
    5         : write m_yCurr
*/
int updateValInSMOBuff(struct SMOBuffer *obj,int updateMet,int index,double *val)
{
    int ret = ((obj != NULL) && (val != NULL));
    //3open
    if ((index > -1) && (index < m_nBuff))
    {
        if ((*val > 18.0) && (*val < 19.9))
        {
        printf("-- index :%d updateMet:%d ",index,updateMet);
        }
        ret = updateValInSMoBuffEle(&(m_smoBuffEle[index]),updateMet,val);
    }
    else
    {
        printf("Error(1) in updateValInSMOBuff, index is out of valid ranged:%d, ln:%d file:%s\n",index,__LINE__,__FILE__);
    }
    //1endupdateValInSMOBuff//2end
    return ret;
}