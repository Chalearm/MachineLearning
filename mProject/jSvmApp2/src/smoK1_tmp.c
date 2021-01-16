/********************************************************************/
/*
      FILE        :   smoK1.c
      Name        :   Chalearm Saelim
      Date        :   03 January 2018
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to provide the training feature by the modified SMO of Keerthi v. 1 (SMO K1)


      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        03-01-2018    csaelim    First draft 
*/
/*******************************************************************/

#include "smoK1.h"

int mainLearningLoopInSmoK1Learner(struct smoK1Learner *obj)
{
    int ret = (obj != NULL);
    //3open

    unsigned int segId = 0;
    unsigned int id = 0;
    unsigned int tmpSegId = 0;
    unsigned int tmpId = 0;
    //double sum1 = 0.0;
    int index = 0;
    int index2 = 0;
  //  struct inputSet inp;
    int numChanged = 0;
    int examineAll = 1;
    int num = 0;  /* num sample */
    //int num2 = 0; /* dimension */
    
      /*
    if(INPUT_TYPE == INPUT_DEFINED_TYPE)
    { 
        num = NUM_INPUT_DEFINE;
        num2 = NUM_ATTRB_INPUT_DEFINE;
    }
    else
    {
        num = NUM_TRAIN_EX;
        num2 = NUM_ATTRB_EX;
    }
  
    vBuff = new_vector_double(num2);
    initInputSet(&inp,num2,MAX_VAL1,MIN_VAL1,MAX_VAL2,MIN_VAL2,INPUT_TYPE);
    initiSMOKMBuff(obj,&inp);

    printInputSet(&inp);
    printSMOKMBuff(obj,0x1F00);
    */
    /*
    setAllDat2SetSMOKBuff(&smoBf);
    */
    while((numChanged > 0) || (examineAll))
    {
        numChanged = 0;
        if(examineAll)
        {
            for(index = 0;index < num; index++)
            {
                printf("Examine :%d  \n",index);
                /* numChanged += examineExam(obj,index);
               
                printSMOKMBuff(obj,0x1F00);
                */
                printf("numChanged:%d\n",numChanged);
            }
        }
        else
        {
            num = getNumI0SetInSmoK1Learner(obj);
            resetIdDatI0setInSmoK1Learner(obj);
            printf("xxxxxxxxxxxx Else case of examine, num:%d \n",num);
            for(index = 0;index < num; index++)
            {
                index2 = (int)getNumI0SetInSmoK1Learner(obj);
                if(index2 >= 0)
                {
                    /*
                    
    unsigned int tmpSegId = 0;
    unsigned int tmpId = 0;
                    */
                    pushReadStateI0SetInSmoK1Learner(obj,&segId,&id);
                  //  printf("loop ------------index 2 : %d, segId:%u, id:%u \n",index2,segId,id);
                 //   printf("alpha[%d]=%f ,C=%f\n",index,smoBf.m_alpha[index2],(double)C_ALPHA);
                   // numChanged += examineExam(obj,index2);
                    pushReadStateI0SetInSmoK1Learner(obj,&tmpSegId,&tmpId);
                 //   printf("after calling examine tmp SegId : %u, id :%u\n",tmpSegId,tmpId);
                    popReadStateI0SetInSmoK1Learner(obj,segId,id);
                    /*printSMOKMBuff(&smoBf,0x08);*/
                    /*
                    if(m_b_up > (m_b_low - (2.0*(m_tol))))
                    {
                        // exit loop  
                        index = num;
                        numChanged = 0;
                    }
                    */
                }
                else
                {
                    // do nothing  
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
    ret = (avrBiasInSMOBuffer(m_buff1) && (ret == 1));
    /*
    printf("Hey jui Biso:%f\n",smoBf.m_Bias);
    for(index = 0;index < num; index++)
    {
        sum1 += smoBf.m_alpha[index]*inp.m_out[index];
        printf("i:%d  y:%d, fx:%f, y*alpha:%0.39f\n",index,(int)inp.m_out[index],learnSMOFx(&smoBf,index,gausRadiusKernelFn),smoBf.m_alpha[index]*inp.m_out[index]);
    }
    printf("SIGMA YiAi = %f \n",sum1);
    printf("Call taskStep :%u\n",countCallTask);
    clearInputSet(&inp); 
    clearSMOKMBuff(&smoBf);
    delete_vector_double(&vBuff);
    return 0;
    */
    //1endmainLearningLoopInSmoK1Learner//2end
    return ret;
}



int initiSmoK1Learner(struct smoK1Learner *obj)
{
    int ret = (obj != NULL);
    //3open
    m_eps = 0.00001;
    m_roundNum = 0.00000001;
    m_dim = 0;
    m_dtSp = NULL;
    m_buff1 = NULL;
    m_kernelFn = NULL;

    //1endinitiSmoK1Learner//2end
    
    return ret;
}
int constructSmoK1Learner(struct smoK1Learner *obj,struct SMOBuffer *smoBObj,struct datSpace *dtSp, struct kFnHdl *kFn)
{
    int ret = ((initiSmoK1Learner(obj) == 1) && (smoBObj != NULL) && (dtSp != NULL) && (kFn != NULL));
    //3open
    m_dtSp = dtSp;
    m_buff1 = smoBObj;
    m_kernelFn1 = kFn;
    //1endconstructSmoK1Learner//2end
    return ret;
}
int destructSmoK1Learner(struct smoK1Learner *obj)
{
    int ret = (obj != NULL);
    //3open
    m_eps = 0.00001;
    m_roundNum = 0.00000001;
    m_dim = 0;
    m_dtSp = NULL;
    m_buff1 = NULL;
    
    destructorRVSet(&(m_I0));
    destructorRVSet(&(m_I1));
    destructorRVSet(&(m_I2));
    destructorRVSet(&(m_I3));
    destructorRVSet(&(m_I4));
    destructorRVSet(&(m_supportVectSet));
    //1enddestructSmoK1Learner//2end
    return ret;
}
int stErrParamInSmoK1Learner(struct smoK1Learner *obj,const double eps,const double rdNum)
{
    int ret = (obj != NULL);
    //3open
    m_eps = eps;
    m_roundNum = rdNum;
    //1endstErrParamInSmoK1Learner//2end
    return ret;
}
int stSMOParamInSmoK1Learner(struct smoK1Learner *obj,const double cAlpha, const int nDim)
{
    int ret = (obj != NULL);
    //3open
    m_cSMO = cAlpha;
    m_dim = nDim;
    //1endstSMOParamInSmoK1Learner//2end
    return ret;
}

