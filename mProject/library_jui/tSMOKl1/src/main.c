/********************************************************************/
/*
      FILE        :   main.c
      Name        :   Chalearm Saelim
      Date        :   15 August 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to implement and make some experiment about SMO Keerthi modified version 1


      Description :   it is based on SMO
      Dependency  :   We use the included library as below 
                        #include "simMatDouble.h"
                        #include "listPvoid.h"
                        #include "setRealV.h"
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        15-08-2017    csaelim    First draft
      2.        14-09-2017    csaelim    Added sub-routine to manage 
                                         I0-I4 set and SMO Buff print function

*/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include "simMatDouble.h"
#include "listPvoid.h"
#include "setRealV.h"
#define POLYFACTOR 3
#define SIGMA 6
#define ROUND_NUM 0.00000001
#define C_ALPHA 26
#define EPS 0.00001
#define TOL 0.0002
#define GUASSIAN_DIVIDER (-2.0)*pow(SIGMA,2)
#define INPUT_RANDOM_TYPE 0
#define INPUT_DEFINED_TYPE 1
#define INPUT_TYPE INPUT_DEFINED_TYPE
#define MAX_VAL1 -1
#define MIN_VAL1 -10
#define MAX_VAL2 10
#define MIN_VAL2 1
#define NUM_TRAIN_EX 4
#define NUM_ATTRB_EX 4

#define INPUT_DEFINE {{1,2,3},\
                      {2,-1,4},\
                      {4,3,-2}}
                      
#define OUTPUT_DEFINE {1,-1,-1}

#define NUM_INPUT_DEFINE 3
#define NUM_ATTRB_INPUT_DEFINE 3


unsigned int countCallTask = 0;
struct inputSet
{
    int m_numInput;
    vector_double *m_dat;
    double *m_out;
    
};
/*[SMO] - [K]eethi [M]odified Buff */
struct SMOKMBuff
{
    struct inputSet *m_points;
    double *m_alpha;
    double *m_fCache;
    double m_Bias;
    double m_b_up; /* Bias Upper bound*/
    double m_b_low; /* Bias Lower bound*/
    
    double m_y1;
    double m_y2;
    double m_F1;
    double m_F2;
    double m_s;
    double m_k11;
    double m_k22;
    double m_k12;
    
    double m_alpha1;
    double m_alpha2;
    double m_currEta;
    long int m_index1;
    long int m_index2;
    long int m_i_up;  /* index Upper bound */
    long int m_i_low; /* index Lower bound */
    
    struct rvSet m_I0;
    struct rvSet m_I1;
    struct rvSet m_I2;
    struct rvSet m_I3;
    struct rvSet m_I4;
    struct rvSet m_supportVectSet;
    /*
    if(added2RVSet(obj,&tmpI) == 0)
    ret = removedValRVSet(obj,&dObj[index],0);
unsigned long int  isInRVSet(struct rvSet *obj,void *val);
    */
};

vector_double vBuff;
void initInputSet(struct inputSet *obj,int ndim,double max,double min,double max2,double min2,int type);
void clearInputSet(struct inputSet *obj);
void printInputSet(struct inputSet *obj);



double linearKernelFn(vector_double *va,vector_double *vb);
double polyKernelFn(vector_double *va,vector_double *vb);
double gausRadiusKernelFn(vector_double *va,vector_double *vb);

double absf(double a);
double maxVal(double a,double b);
double minVal(double a,double b);
/************** ---- SMOKMBuff class ************************/

/* Public method */

double learnSMOFx(struct SMOKMBuff *obj,int npoint,void *kernelFn);
void initiSMOKMBuff(struct SMOKMBuff *obj,struct inputSet *objP);
void initIupAndIlowofSMOKMBuff(struct SMOKMBuff *obj);
void clearSMOKMBuff(struct SMOKMBuff *obj);
int takeStep(struct SMOKMBuff *obj);
int examineExam(struct SMOKMBuff *obj,long int index);

int getNumI0Set(struct SMOKMBuff *obj);
int nextDatI0set(struct SMOKMBuff *obj);
void pushReadStateI0Set(struct SMOKMBuff *obj,unsigned int *segId,unsigned int *id);
void popReadStateI0Set(struct SMOKMBuff *obj,const unsigned int segId,const unsigned int id);
void resetIdDatI0set(struct SMOKMBuff *obj);
void printSMOKMBuff(struct SMOKMBuff *obj,unsigned int opt);
void setAllDat2SetSMOKBuff(struct SMOKMBuff *obj);
/* Private method */
void updateBiasAndIndexLowUp(struct SMOKMBuff *obj, long int index); 
void avrBiasSMOK(struct SMOKMBuff *obj);
void computeLAndHInTakeStep(struct SMOKMBuff *obj,double *L,double *H);
int AddIndex2AllSets(struct SMOKMBuff *obj,double alpha,long int index);
/* from tutorial of Sequential Minimal Optimization for SVM*/
double objectiveFnAlpha(struct SMOKMBuff *obj,double alpha2);
/* origin equation from Platt */
double objectiveFnAlphaOrgn(struct SMOKMBuff *obj,double alpha2);

void checkObjFnAlpha2(double *L1,double *L2,double *H1,double *H2);
void updateCurrentError(struct SMOKMBuff *obj,int index1or2);

/************** ----End of SMOKMBuff class ************************/

double randomVal(double max,double min);
int main(int argc,char **argv)
{
    unsigned int segId = 0;
    unsigned int id = 0;
    unsigned int tmpSegId = 0;
    unsigned int tmpId = 0;
    double sum1 = 0.0;
    srand(time(NULL));
    int index = 0;
    int index2 = 0;
    struct SMOKMBuff smoBf;
    struct inputSet inp;
    int numChanged = 0;
    int examineAll = 1;
    int num = 0;
    int num2 = 0;
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
    initiSMOKMBuff(&smoBf,&inp);
    setAllDat2SetSMOKBuff(&smoBf);
    printInputSet(&inp);
    printSMOKMBuff(&smoBf,0x1F00);
    while((numChanged > 0) || (examineAll))
    {
        numChanged = 0;
        if(examineAll)
        {
            for(index = 0;index < num; index++)
            {
                printf("Examine :%d  \n",index);
                numChanged += examineExam(&smoBf,index);
                printSMOKMBuff(&smoBf,0x1F00);
                printf("numChanged:%d\n",numChanged);
            }
        }
        else
        {
            num = (int)getNumI0Set(&smoBf);
            resetIdDatI0set(&smoBf);
            printf("xxxxxxxxxxxx Else case of examine, num:%d \n",num);
            for(index = 0;index < num; index++)
            {
                index2 = (int)nextDatI0set(&smoBf);
                if(index2 >= 0)
                {
                    /*
                    
    unsigned int tmpSegId = 0;
    unsigned int tmpId = 0;
                    */
                    pushReadStateI0Set(&smoBf,&segId,&id);
                    printf("loop ------------index 2 : %d, segId:%u, id:%u \n",index2,segId,id);
                    printf("alpha[%d]=%f ,C=%f\n",index,smoBf.m_alpha[index2],(double)C_ALPHA);
                    numChanged += examineExam(&smoBf,index2);
                    pushReadStateI0Set(&smoBf,&tmpSegId,&tmpId);
                    printf("after calling examine tmp SegId : %u, id :%u\n",tmpSegId,tmpId);
                    popReadStateI0Set(&smoBf,segId,id);
                    printSMOKMBuff(&smoBf,0x08);
                    if(smoBf.m_b_up > (smoBf.m_b_low - (2.0*TOL)))
                    {
                        /* exit loop */
                        index = num;
                        numChanged = 0;
                    }
                }
                else
                {
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
    avrBiasSMOK(&smoBf);
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
}

double maxVal(double a,double b)
{
    double ret = a;
    if(a<b)
    {
        ret = b;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
double minVal(double a,double b)
{
    double ret = a;
    if(a>b)
    {
        ret = b;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}


void updateBiasAndIndexLowUp(struct SMOKMBuff *obj, long int index)
{
    if ( (obj != NULL) && ( index >= 0 ))
    {
        if(obj->m_fCache[index] < obj->m_b_up)
        {
            obj->m_b_up = obj->m_fCache[index];
            obj->m_i_up = index;
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_fCache[index] > obj->m_b_low)
        {
            obj->m_b_low = obj->m_fCache[index];
            obj->m_i_low = index;
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
double randomVal(double max,double min)
{
    if((int)(max-min)== 0)
    {
        return min;
    }
    else
    {
        return min + rand()%(int)(max-min);
    }
}

double objectiveFnAlpha(struct SMOKMBuff *obj,double alpha2)
{
    double c1 = (0.5)*obj->m_currEta;
    return c1*pow(alpha2,2)+alpha2*((obj->m_points->m_out[obj->m_index2]*(obj->m_F1-obj->m_F2))-(obj->m_currEta*obj->m_alpha2));
}
void checkObjFnAlpha2(double *L1,double *L2,double *H1,double *H2)
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
double objectiveFnAlphaOrgn(struct SMOKMBuff *obj,double alpha2)
{
    double f1 = 0.0;
    double f2 = 0.0;
    double v1 = 0.0;
    double v2 = 0.0;
    double gamma = 0.0;
    double ret = 0.0;
    double delTmp = 0.0;
    if((obj!=NULL)&&(alpha2 >=0.0))
    {
        gamma = (obj->m_alpha1)+((obj->m_s)*(obj->m_alpha2));
        
        delTmp = gamma - ((obj->m_s)*alpha2);
        f1 = learnSMOFx(obj,obj->m_index1,gausRadiusKernelFn);
        f2 = learnSMOFx(obj,obj->m_index2,gausRadiusKernelFn);
        v1 = f1+(obj->m_Bias) - ((obj->m_y1)*(obj->m_alpha1)*(obj->m_k11))-((obj->m_y2)*(obj->m_alpha2)*(obj->m_k12));
        v2 = f2+(obj->m_Bias) - ((obj->m_y1)*(obj->m_alpha1)*(obj->m_k12))-((obj->m_y2)*(obj->m_alpha2)*(obj->m_k22));
        ret = delTmp +(alpha2) - 
              ((0.5)*(obj->m_k11)*delTmp*delTmp) - 
              ((0.5)*(obj->m_k22)*alpha2*alpha2)-
              ((obj->m_s)*(obj->m_k12)*delTmp*alpha2)-
              ((obj->m_y1)*delTmp*v1)-
              ((obj->m_y2)*alpha2*v2);
    }
    else
    {
        printf("objectiveFnAlphaOrgn alp2:%f cannot operate, File:%s ln:%d \n",alpha2,__FILE__,__LINE__);
    }
    return ret;
}

int examineExam(struct SMOKMBuff *obj,long int index)
{
    int optimality = 1;
    int ret = 0;
    obj->m_y2 = obj->m_points->m_out[index];
    obj->m_alpha2 = obj->m_alpha[index];
    obj->m_index2 = index;
    printf("Exam index:%ld \n",index);
    if(isInRVSet(&(obj->m_I0),&(obj->m_index2)) == 1) /* if i2 is in I_0*/
    {
        obj->m_F2 = obj->m_fCache[obj->m_index2];
    }
    else
    {
        obj->m_F2 = learnSMOFx(obj,obj->m_index2,gausRadiusKernelFn) + obj->m_Bias - obj->m_y2;
        obj->m_fCache[obj->m_index2] = obj->m_F2;
    printf("Not is in I0 set, I:%ld F2:%f\n",index,obj->m_fCache[obj->m_index2]);
    printSMOKMBuff(obj,0x28);
        if((isInRVSet(&(obj->m_I1),&(obj->m_index2))||isInRVSet(&(obj->m_I2),&(obj->m_index2)))&&(obj->m_F2 < obj->m_b_up))
        {
            obj->m_b_up = obj->m_F2;
            obj->m_i_up = obj->m_index2;
        }
        else if((isInRVSet(&(obj->m_I3),&(obj->m_index2))||isInRVSet(&(obj->m_I4),&(obj->m_index2)))&&(obj->m_F2 > obj->m_b_low))
        {
            obj->m_b_low = obj->m_F2;
            obj->m_i_low = obj->m_index2;
        }
        else
        {
            printf("not is in I1, I2, I3 and I4 \n");
            /* do nothing */
        }
        printSMOKMBuff(obj,0x39);
    }
    optimality = 1;
    printf("obj->m_F2 - obj->m_b_up = %f , %f \n",(obj->m_F2 - obj->m_b_up),(2.0*TOL));
    if((isInRVSet(&(obj->m_I0),&(obj->m_index2)))||(isInRVSet(&(obj->m_I1),&(obj->m_index2)))||(isInRVSet(&(obj->m_I2),&(obj->m_index2))))
    {
        if((obj->m_b_low-obj->m_F2) > (2.0*TOL))
        {
            optimality = 0;
            obj->m_index1 = obj->m_i_low;
        }
        else
        {
            /* do nothing */
        }
    }
    else if((isInRVSet(&(obj->m_I0),&(obj->m_index2)))||(isInRVSet(&(obj->m_I3),&(obj->m_index2)))||(isInRVSet(&(obj->m_I4),&(obj->m_index2))))
    {
        if((obj->m_F2 - obj->m_b_up) > (2.0*TOL))
        {
            optimality = 0;
            obj->m_index1 = obj->m_i_up;
        }
        else
        {
            /* do nothing */
        }
    }
    printf("optimality :%d\n",optimality);
    if(optimality == 0)
    {
        if(isInRVSet(&(obj->m_I0),&(obj->m_index2)) == 1)
        {
            if((obj->m_b_low-obj->m_F2) > (obj->m_F2-obj->m_b_up))
            {
                obj->m_index1 = obj->m_i_low;
            }
            else
            {
                obj->m_index1 = obj->m_i_up;
            }

        }
        else
        {
            /* do nothing */
        }
        if(takeStep(obj))
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
    return ret;
}
int getNumI0Set(struct SMOKMBuff *obj)
{
    int ret = 0;
    if(obj != NULL)
    {
        ret = numEleRVSetNotRedunt(&(obj->m_I0));
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int nextDatI0set(struct SMOKMBuff *obj)
{
    int ret = -1;
    void *tmp = NULL;
    if(obj != NULL)
    {
        tmp = getNxtDatInRVSet(&(obj->m_I0));
        if(tmp != NULL)
        {
            ret = (int)(*((long int*)tmp));
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
    return ret;
}

void pushReadStateI0Set(struct SMOKMBuff *obj,unsigned int *segId,unsigned int *id)
{
    if((obj != NULL) && (segId != NULL) && (id != NULL))
    {
        pushStateNxtDat(&(obj->m_I0),segId,id);
    }
    else
    {
        printf("== Error (obj,%p), (segId,%p) or (id,%p) point is NULL, ln:%d, fl:%s \n",obj,segId,id,__LINE__,__FILE__);
    }
}
void popReadStateI0Set(struct SMOKMBuff *obj,const unsigned int segId,const unsigned int id)
{
    if(obj != NULL)
    {
        popStateNxtDat(&(obj->m_I0),segId,id);
    }
    else
    {
        printf("== Error obj point is NULL, ln:%d, fl:%s \n",__LINE__,__FILE__);
    }
}
void resetIdDatI0set(struct SMOKMBuff *obj)
{
    if(obj != NULL)
    {
        resetGetNxtDat(&(obj->m_I0));
    }
    else
    {
        /* do nothing */
    }
}
void printSMOKMBuff(struct SMOKMBuff *obj,unsigned int opt)
{
    int index = 0;
    int numInput = 0;
    /*
     
    */
    /* bit: 0 -- show i1 and i2 information */
    /* bit: 1 -- show k and s information */
    /* bit: 2 -- show a1 and a2 information */
    /* bit: 3 -- show Bias information */
    /* bit: 4 -- show index up/low information */
    /* bit: 5 -- show F1 and F2 information */
    /* bit: 6 -- show Alpha set information */
    /* bit: 7 -- show fCache set information */
    /* bit: 8 -- show 0 ground index set information */
    /* bit: 9 -- show 1 ground index set information */
    /* bit: 10 -- show 2 ground index set information */
    /* bit: 11 -- show 3 ground index set information */
    /* bit: 12 -- show 4 ground index set information */
    /* bit: 13 -- show SVM ground index set information */
    
    if (obj != NULL)
    {
        if(obj->m_points != NULL)
        {
            numInput = obj->m_points->m_numInput;
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x01) == 0x01) /* bit 0 */
        {
            printf("i1:%ld, y1:%.1f \n",obj->m_index1,obj->m_y1);
            printf("i2:%ld, y2:%.1f \n",obj->m_index2,obj->m_y2);
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x02) == 0x02) /* bit 1 */
        {
            printf("k11:%f, k12:%f, k22:%f, s:%f \n",obj->m_k11,obj->m_k22,obj->m_k12,obj->m_s);
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x04) == 0x04) /* bit 2 */
        {
            printf("alpha1:%f, alpha2:%f \n",obj->m_alpha1,obj->m_alpha2);
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x08) == 0x08) /* bit 3 */
        {
            printf("Bias:%f, B_low:%f, B_up:%f \n",obj->m_Bias,obj->m_b_low,obj->m_b_up);
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x10) == 0x10) /* bit 4 */
        {
            printf("I_low:%ld, I_up:%ld\n",obj->m_i_low,obj->m_i_up);
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x20) == 0x20) /* bit 5 */
        {
            printf("F1:%f, F2:%f\n",obj->m_F1,obj->m_F2);
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x40) == 0x40) /* bit 6 */
        {
            printf("alpha set : ");
            for (index = 0;index < numInput; index++)
            {
                printf("i%d:%f ",index,obj->m_alpha[index]);
                if ((index%4) == 0)
                {
                    printf("\n");
                }
                else
                {
                    /* do nothing */
                }
            }
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x80) == 0x80) /* bit 7 */
        {
            printf("f cache set : ");
            for (index = 0;index < numInput; index++)
            {
                printf("i%d:%f ",index,obj->m_fCache[index]);
                if ((index%4) == 0)
                {
                    printf("\n");
                }
                else
                {
                    /* do nothing */
                }
            }
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x0100) == 0x0100) /* bit 8 */
        {
            printf("I0 Set :");
            printLinearByIndexSet(&(obj->m_I0));
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x0200) == 0x0200) /* bit 9 */
        {
            printf("I1 Set :");
            printLinearByIndexSet(&(obj->m_I1));
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x0400) == 0x0400) /* bit 10 */
        {
            printf("I2 Set :");
            printLinearByIndexSet(&(obj->m_I2));
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x0800) == 0x0800) /* bit 11 */
        {
            printf("I3 Set :");
            printLinearByIndexSet(&(obj->m_I3));
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x1000) == 0x1000) /* bit 12 */
        {
            printf("I4 Set :");
            printLinearByIndexSet(&(obj->m_I4));
        }
        else
        {
            /* do nothing */
        }
        if ((opt&0x2000) == 0x2000) /* bit 13 */
        {
            printf("SVM Set :");
            printLinearByIndexSet(&(obj->m_supportVectSet));
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

void setAllDat2SetSMOKBuff(struct SMOKMBuff *obj)
{
    int num = 0;
    int index = 0;
    double alpha = 0;
    struct inputSet *objP = NULL;
    if ( obj != NULL)
    {
        objP = obj->m_points;
    }
    else
    {
        /* do nothing */
    }
    if ( objP != NULL)
    {
        num = objP->m_numInput;
        for (index = 0;index < num; index++)
        {
            alpha = obj->m_alpha[index];
            AddIndex2AllSets(obj,alpha,(long int)index);
        }
    }
    else
    {
        /* do nothing */
    }
}
int AddIndex2AllSets(struct SMOKMBuff *obj,double alpha,long int index)
{
    int ret = 1;
    
    struct inputSet *objP = NULL;
    double yTmp = 0.0;
    if ((obj != NULL) && (index > -1))
    {
        objP = obj->m_points;;

    }
    else
    {
        ret = 0;
        printf("Error Parameter in  AddIndex2AllSets (SMOMBuff obj):%p, id:%ld, ln:%d File:%s \n",obj,index,__LINE__,__FILE__);
    }
    if ( objP != NULL)
    {
        yTmp = objP->m_out[index];
        if(alpha > 0.0)
        {
            ret = added2RVSet(&(obj->m_supportVectSet),&index);
        }
        else
        {
            removedValRVSet(&(obj->m_supportVectSet),&index,1);
        }
        if((alpha > 0.0)&&(alpha < C_ALPHA))
        {
            ret =(ret == 1) && added2RVSet(&(obj->m_I0),&index);
        }
        else
        {
            removedValRVSet(&(obj->m_I0),&index,1);
        }
        
        if((alpha == 0.0)&&(yTmp == 1.0))
        {
            ret =(ret == 1) && added2RVSet(&(obj->m_I1),&index);
        }
        else
        {
            removedValRVSet(&(obj->m_I1),&index,1);
        }
        
        if((alpha == C_ALPHA)&&(yTmp == -1.0))
        {
            ret =(ret == 1) && added2RVSet(&(obj->m_I2),&index);
        }
        else
        {
            removedValRVSet(&(obj->m_I2),&index,1);
        }
        if((alpha == C_ALPHA)&&(yTmp == 1.0))
        {
            ret =(ret == 1) && added2RVSet(&(obj->m_I3),&index);
        }
        else
        {
            removedValRVSet(&(obj->m_I3),&index,1);
        }
        if((alpha == 0.0) && (yTmp == -1.0))
        {
            ret =(ret == 1) && added2RVSet(&(obj->m_I4),&index);
        }
        else
        {
            removedValRVSet(&(obj->m_I4),&index,1);
        }
    }
    else
    {
        ret = 0;
        printf("Error Parameter in  AddIndex2AllSets (SMOMBuff obj):%p, id:%ld, ln:%d File:%s \n",obj,index,__LINE__,__FILE__);
    }
    return ret;

}
void updateCurrentError(struct SMOKMBuff *obj,int index1or2)
{
    double *tmp = NULL;
    double *alphaTmp = NULL;
    long int *ind = NULL;
    if(obj!=NULL)
    {
        if(index1or2 ==1)
        {
            tmp = &(obj->m_F1);
            ind = &(obj->m_index1);
            alphaTmp = &(obj->m_alpha1);
        }
        else if(index1or2 == 2)
        {
            tmp = &(obj->m_F2);
            ind = &(obj->m_index2);
            alphaTmp = &(obj->m_alpha2);
        }
        else
        {
            /* do nothing */
        }
        if((tmp != NULL)&&(ind != NULL)&&(alphaTmp != NULL))
        {
            if( (*alphaTmp > 0)&&(*alphaTmp < C_ALPHA))
            {
               // *tmp = obj->m_fCache[*ind];  
               *tmp = learnSMOFx(obj,*ind,gausRadiusKernelFn)-obj->m_points->m_out[*ind];
            }
            else
            {
                *tmp = learnSMOFx(obj,*ind,gausRadiusKernelFn)-obj->m_points->m_out[*ind];
            }
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
double absf(double a)
{
    double ret = 0.0;
    if(a<0)
    {
        ret = -1*a;
    }
    else
    {
        ret = a;
    }
    return ret;
}
/******
    Use scope : in takeStep method
    Precondition :  obj->m_y1 and obj->m_y2 are updated
    
***/
void computeLAndHInTakeStep(struct SMOKMBuff *obj,double *L,double *H)
{
    if((obj!=NULL)&&(L!=NULL)&&(H!=NULL))
    {        
        if(obj->m_y1 == obj->m_y2)
        {
            *L = maxVal(0.0,obj->m_alpha2+obj->m_alpha1-C_ALPHA);
            *H = minVal(C_ALPHA,obj->m_alpha2+obj->m_alpha1);
        }
        else
        {
            *L = maxVal(0.0,obj->m_alpha2-obj->m_alpha1);
            *H = minVal(C_ALPHA,C_ALPHA+obj->m_alpha2-obj->m_alpha1);
        }
    }
    else
    {
        printf("computeLAndHInTakeStep cannot operate, File:%s, ln:%d\n",__FILE__,__LINE__);
    }
}
int takeStep(struct SMOKMBuff *obj)
{
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
    int index = 0;
    int index3 = 0;
    long int num = 0;
    long int index1 = obj->m_index1;
    long int index2 = obj->m_index2;
    if(index1 != index2)
    {
    countCallTask++;
        obj->m_alpha1 = obj->m_alpha[index1];
        obj->m_y1 = obj->m_points->m_out[index1];
        obj->m_s = (obj->m_y1)*(obj->m_y2);
        obj->m_F1 =obj->m_fCache[index1];
        computeLAndHInTakeStep(obj,&L,&H);
printf("(H,L):(%f,%f), (F1,F2):(%f,%f), a1:%f, a2:%f\n",H,L,obj->m_F1,obj->m_F2,obj->m_alpha1,obj->m_alpha2);
        if(L!=H)
        {
            obj->m_k11 = gausRadiusKernelFn(&(obj->m_points->m_dat[index1]),&(obj->m_points->m_dat[index1]));
            obj->m_k22 = gausRadiusKernelFn(&(obj->m_points->m_dat[index2]),&(obj->m_points->m_dat[index2]));
            obj->m_k12 = gausRadiusKernelFn(&(obj->m_points->m_dat[index1]),&(obj->m_points->m_dat[index2]));
            obj->m_currEta = (2*(obj->m_k12))-(obj->m_k11)-(obj->m_k22);
printf("k11:%f, k22:%f, k12:%f, Eta:%f \n",obj->m_k11,obj->m_k22,obj->m_k12,obj->m_currEta);
            if(obj->m_currEta <0)
            {
                a2 = obj->m_alpha2-((obj->m_y2)*(obj->m_F1-obj->m_F2)/obj->m_currEta);
printf("Eta <0 --> a2 : %f ",a2);
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

                printf(" new a2:%f\n",a2);
            }
            else
            {
                tmp1 = objectiveFnAlphaOrgn(obj,L);
                tmp2 = objectiveFnAlphaOrgn(obj,H);
                Lobj = objectiveFnAlpha(obj,L);
                Hobj = objectiveFnAlpha(obj,H);
                /* temporary uesed to compare the result between 2 methods:
                objectiveFnAlphaOrgn and objectiveFnAlpha */
                checkObjFnAlpha2(&Lobj,&tmp1,&Hobj,&tmp2);
                printf("(Lobj,Hobj):(%f,%f)\n",Lobj,Hobj);
                if(Lobj > Hobj+EPS)
                {
                    a2 = L;
                }
                else if(Lobj < Hobj-EPS)
                {
                    a2 = H;
                }
                else 
                {
                    a2 = obj->m_alpha2;
                }
            }
            
            // this is used in original SMO, 31 August 2017
            // make it used, 03 September 2017
            if(a2 < ROUND_NUM)
            {
                a2 = 0.0;
            }
            else if(a2 > C_ALPHA-ROUND_NUM)
            {
                a2 = C_ALPHA;
            }
            else
            {
                /* do nothing */
            }
           
            if(absf(a2-obj->m_alpha2)<EPS*(a2+obj->m_alpha2+EPS))
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
                a1 = obj->m_alpha1+(obj->m_s)*(obj->m_alpha2-a2);
                if(a1 < ROUND_NUM)
                {
                    a1 = 0.0;
                }
                else if(a1 > C_ALPHA-ROUND_NUM)
                {
                    a1 = C_ALPHA;
                }
                else
                {
                    /* do nothing */
                }
                
                tmp1 = (obj->m_y1)*(a1-obj->m_alpha1);
                tmp2 = (obj->m_y2)*(a2-obj->m_alpha2);
                
                /* update sets, 3 september 2017 */
                ret = ret && (AddIndex2AllSets(obj,a1,index1));
                ret = ret && (AddIndex2AllSets(obj,a2,index2));
                obj->m_i_up = -1;
                obj->m_i_low = -1;
                obj->m_b_low = -DBL_MAX;
                obj->m_b_up = DBL_MAX; 
                resetIdDatI0set(obj);
                num = (long int)getNumI0Set(obj);
                printf("the number of member in I0 set is : %ld\n",num);
                for(index = 0; index < num; index++)
                {
                    index3 = nextDatI0set(obj);
                    if (index3 >= 0)
                    {
                        k1i = gausRadiusKernelFn(&(obj->m_points->m_dat[index1]),&(obj->m_points->m_dat[index3]));
                        k2i = gausRadiusKernelFn(&(obj->m_points->m_dat[index2]),&(obj->m_points->m_dat[index3])); 
                        obj->m_fCache[index3] = obj->m_fCache[index3] +(k1i*tmp1)+(k2i*tmp2);
                        updateBiasAndIndexLowUp(obj,index3);
                    }
                    else
                    {
                        /* do nothing */
                    }
                } 
                obj->m_fCache[index1] = (obj->m_F1) +(obj->m_y1)*(obj->m_k11)*(a1-obj->m_alpha1)+((obj->m_y2)*(obj->m_k12)*(a2-obj->m_alpha2));
                obj->m_fCache[index2] = (obj->m_F2) +(obj->m_y1)*(obj->m_k12)*(a1-obj->m_alpha1)+((obj->m_y2)*(obj->m_k22)*(a2-obj->m_alpha2));
                updateBiasAndIndexLowUp(obj,index1);
                updateBiasAndIndexLowUp(obj,index2);
                obj->m_alpha[index1] = a1;
                obj->m_alpha[index2] = a2;
                if(isInRVSet(&(obj->m_I0),&(obj->m_index1)) == 0)
                {
                    if((isInRVSet(&(obj->m_I3),&(obj->m_index1)) == 1)||(isInRVSet(&(obj->m_I4),&(obj->m_index1)) == 1))
                    {
                        if(obj->m_fCache[obj->m_index1] > obj->m_b_low)
                        {
                            obj->m_b_low = obj->m_fCache[obj->m_index1];
                            obj->m_i_low = obj->m_index1;
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    else if (obj->m_fCache[obj->m_index1] < obj->m_b_up)
                    {
                        obj->m_b_up = obj->m_fCache[obj->m_index1];
                        obj->m_i_up = obj->m_index1;
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
                if(isInRVSet(&(obj->m_I0),&(obj->m_index2)) == 0)
                {
                    if((isInRVSet(&(obj->m_I3),&(obj->m_index2)) == 1)||(isInRVSet(&(obj->m_I4),&(obj->m_index2)) == 1))
                    {
                        if(obj->m_fCache[obj->m_index2] > obj->m_b_low)
                        {
                            obj->m_b_low = obj->m_fCache[obj->m_index2];
                            obj->m_i_low = obj->m_index2;
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    else if (obj->m_fCache[obj->m_index2] < obj->m_b_up)
                    {
                        obj->m_b_up = obj->m_fCache[obj->m_index2];
                        obj->m_i_up = obj->m_index2;
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
                avrBiasSMOK(obj);
                if ((obj->m_i_low == -1) || (obj->m_i_up == -1))
                {
                    printf("Error I low/up : %ld/%ld , Ln:%d, File:%s\n",obj->m_i_low,obj->m_i_up,__LINE__,__FILE__);
                }
                else
                {
                    /* do nothing */
                }
for(index = 0; index < num; index++)
{
    printf("error[%d]:%f, alpha:%f \n",index,obj->m_fCache[index],obj->m_alpha[index]);
}
printf("New Bias:%f \n",obj->m_Bias);
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
    return ret;
}

void avrBiasSMOK(struct SMOKMBuff *obj)
{
    if(obj != NULL)
    {   
        obj->m_Bias = (obj->m_b_up+obj->m_b_low)/2;
    }
    else
    {
        /* do nothing */
    }
}
double linearKernelFn(vector_double *va,vector_double *vb)
{
    double ret = 0.0;
    if(multiply_vt_v_double(va,vb,&ret) != 0)
    {
        printf("linearKernelFn error \n");
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
double polyKernelFn(vector_double *va,vector_double *vb)
{
    double ret = pow(linearKernelFn(va,vb)+1.0,POLYFACTOR);
    
    return ret;
}
double gausRadiusKernelFn(vector_double *va,vector_double *vb)
{
    double ret = 0.0;
    double temp1 =GUASSIAN_DIVIDER;
    minus_v_double(va,vb,&vBuff);
    ret = linearKernelFn(&vBuff,&vBuff);
   /* printf("KFn 1 :%f GDIV:%f , ret/GDIV:%lf\n",ret,temp1,ret/temp1);*/
    if (ret != 0.0)
    { 
        ret = exp(ret/temp1);
     /*   printf("ret :%0.20f\n",ret);*/
    }
    else
    {
        ret = 1;
    }
    return ret;
}

void initInputSet(struct inputSet *obj,int ndim,double max,double min,double max2,double min2,int type)
{
    int index  = 0;
    int num = 0;
    int half = NUM_TRAIN_EX/2;
    SetValue vect_rang = {1,max,min};
    SetValue vect_rang2 = {1,max2,min2};
    vector_double tempV = new_vector_double(0);
    const double l_input[NUM_INPUT_DEFINE][NUM_ATTRB_INPUT_DEFINE] = INPUT_DEFINE;
    const double l_outp[NUM_INPUT_DEFINE] = OUTPUT_DEFINE;
    if(obj!=NULL)
    {
        if(type == 0)
        {
            obj->m_numInput = NUM_TRAIN_EX;
            num = NUM_TRAIN_EX;
            obj->m_dat = (vector_double*)malloc(sizeof(vector_double)*num); 
            obj->m_out = (double*)malloc(sizeof(double)*num);
            if((obj->m_dat != NULL) && (obj->m_out != NULL))
            {
                for(index=0;index<num;index++)
                {
                    obj->m_dat[index] = new_vector_double(ndim);
                    if(half>index)
                    {
                        obj->m_out[index] =-1.0;
                        initial_vector_double(&(obj->m_dat[index]),vect_rang2);
                    }
                    else
                    {
                        obj->m_out[index] =1.0;
                        initial_vector_double(&(obj->m_dat[index]),vect_rang);
                    }
                }
             }
             else
             {
                printf("Error cannot allocate *data:%p, *out:%p\n",obj->m_dat,obj->m_out);
             }
        }
        else
        {
            obj->m_numInput = NUM_INPUT_DEFINE;
            num = NUM_INPUT_DEFINE;
            obj->m_dat = (vector_double*)malloc(sizeof(vector_double)*num); 
            obj->m_out = (double*)malloc(sizeof(double)*num);
            if((obj->m_dat != NULL) && (obj->m_out != NULL))
            {
                for(index = 0 ; index < num ; index++)
                {
                    obj->m_out[index] = l_outp[index];
                    obj->m_dat[index] = new_vector_double(0);
                    tempV.lenght = NUM_ATTRB_INPUT_DEFINE;
                    tempV.data = (double*)(void*)&(l_input[index]);
                    copy_v_double(&(obj->m_dat[index]),&tempV); 
                }
             }
             else
             {
                printf("Error cannot allocate *data:%p, *out:%p\n",obj->m_dat,obj->m_out);
             }
        }
    }
    else
    {
        /* do nothing */
    }
}
void printInputSet(struct inputSet *obj)
{
    int index = 0; 
    int num = 0;
    if(obj != NULL)
    {
        num = obj->m_numInput;
        for(index = 0;index < num;index++)
        { 
            if(obj->m_out[index] >-1)
            {
                printf(" +%f ",obj->m_out[index]);
            }
            else
            {
                printf(" %f ",obj->m_out[index]);
            }
            print_vector_double(&(obj->m_dat[index]),6);
            printf("\n");
        }
    }
    else
    {
        /* do nothing */
    }
}
void clearInputSet(struct inputSet *obj)
{
    int index = 0;
    int num = 0;
    if(obj!=NULL)
    {
        num = obj->m_numInput;
        if(obj->m_dat != NULL)
        {
            for(index=0;index<num;index++)
            { 
                delete_vector_double(&(obj->m_dat[index]));
            }
            free(obj->m_dat);
            obj->m_dat = NULL;
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_out != NULL)
        {
            free(obj->m_out);
            obj->m_out = NULL;
        }
        else
        {
            /* do nothing */
        }
        obj->m_numInput = 0;
    }
    else
    {
        /* do nothing */
    }
}

void initiSMOKMBuff(struct SMOKMBuff *obj,struct inputSet *objP)
{
    int num = 0;
    if((obj!=NULL)&&(objP!=NULL))
    {
        obj->m_points = objP;
        num = objP->m_numInput;
        if(num > 0)
        {
            obj->m_alpha = (double*)malloc(sizeof(double)*num);
            obj->m_fCache = (double*)malloc(sizeof(double)*num);
        }
        else
        {
            obj->m_alpha = NULL;
            obj->m_fCache = NULL;
        }
        if(obj->m_alpha != NULL)
        {
            memset(obj->m_alpha,0,sizeof(double)*num);
        }
        else
        {
            printf("Cannot allocate alpha arry ln:%d, fl:%s\n",__LINE__,__FILE__);
        }
        if(obj->m_fCache != NULL)
        {
            memset(obj->m_fCache,0,sizeof(double)*num); 
        }
        else
        {
            printf("Cannot allocate error arry ln:%d, fl:%s\n",__LINE__,__FILE__);
        }/*
    int index = 0;
        for(index = 0;index < num;index++)
        {
            obj->m_alpha[index] = randomVal(C_ALPHA,0);
            obj->m_fCache[index] = randomVal(100,0);
        }*/
        obj->m_Bias = 0.0;
        obj->m_b_up =  DBL_MAX; /* Bias Upper bound*/
        obj->m_b_low= -DBL_MAX; /* Bias Lower bound*/
        obj->m_F1 = 0.0;
        obj->m_F2 = 0.0;
        obj->m_alpha1 = 0.0;
        obj->m_alpha2 = 0.0;
        obj->m_y1 = 0.0;
        obj->m_y2 = 0.0;
        obj->m_currEta = 0.0;
        obj->m_s = 0.0;
        obj->m_k11 = 0.0;
        obj->m_k12 = 0.0;
        obj->m_k22 = 0.0;
        obj->m_index1 = 0;
        obj->m_index2 = 0;
        obj->m_i_up = -1;  /* index Upper bound */
        obj->m_i_low= -1; /* index Lower bound */
            /*
        type :
            1 st bit  : 0 long integer , 1 floating-point (double)
            2 nd bit  : 0 dynamic array, 1 not dynamic array
            3 rd bit  : 0 count redundant, 1 not count
            
            type = 6 --- no redundant, Not dynamic array, long integer
    
    */
        constructorRVSet(&(obj->m_I0),6);
        constructorRVSet(&(obj->m_I1),6);
        constructorRVSet(&(obj->m_I2),6);
        constructorRVSet(&(obj->m_I3),6);
        constructorRVSet(&(obj->m_I4),6);
        constructorRVSet(&(obj->m_supportVectSet),6);
        initIupAndIlowofSMOKMBuff(obj);
        printSMOKMBuff(obj,0x10);
    }
    else    
    {
        /* do nothing */
    }
}

void initIupAndIlowofSMOKMBuff(struct SMOKMBuff *obj)
{
    int index = 0;
    int num = 0;
    struct inputSet *objP = NULL;
    double previousOutPut = 0;
    if (obj != NULL)
    {
        objP = obj->m_points;
    }
    else
    {
        /* do nothing */
    }
    if (objP != NULL)
    {
        num = objP->m_numInput;
        obj->m_i_up  = 0;
        obj->m_i_low = 0;
    }
    else
    {
        /* do nothing */
    }
    if (num > 1)
    {
        previousOutPut = objP->m_out[0];
        for (index = 1 ; index < num ; index++)
        {
            if (previousOutPut != objP->m_out[index])
            {
                obj->m_i_low = index;
                index = num; /* break loop */
            }
            else
            {
                /* do nothing */
            }
        }
    }
    else
    {
        /* do nothing */
    }
}

void clearSMOKMBuff(struct SMOKMBuff *obj)
{
    if(obj != NULL)
    {
        if(obj->m_alpha != NULL)
        {
            free(obj->m_alpha);
            obj->m_alpha = NULL;
        }
        else
        {
            /* do nothing */
        }
        if(obj->m_fCache != NULL)
        {
            free(obj->m_fCache);
            obj->m_fCache = NULL;
        }
        else
        {
            /* do nothing */
        }
        obj->m_points = NULL;
        
        destructorRVSet(&(obj->m_I0));
        destructorRVSet(&(obj->m_I1));
        destructorRVSet(&(obj->m_I2));
        destructorRVSet(&(obj->m_I3));
        destructorRVSet(&(obj->m_I4));
        destructorRVSet(&(obj->m_supportVectSet));
    }
    else
    {
        /* do nothing */
    }
}

double learnSMOFx(struct SMOKMBuff *obj,int npoint,void *kernelFn)
{
    int index = 0;
    double ret = 0.0;
    struct inputSet *points = NULL; 
    int num = 0;
    double (*Kfn)(vector_double*,vector_double*) = kernelFn;
    if((obj!=NULL)&&(kernelFn !=NULL)&&(npoint >= 0))
    {
        points = obj->m_points;
        num = points->m_numInput;
        for(index = 0;index < num;index++)
        {
            if(obj->m_alpha[index] > 0)
            {
                ret +=  obj->m_alpha[index]*points->m_out[index]*Kfn(&(points->m_dat[index]),&(points->m_dat[npoint]));
            }
            else
            {
                /* do nothing */
            }
        }
        ret = ret - obj->m_Bias;
    }
    else
    {
        printf("learnSMOFx is error ln:%d \n",__LINE__);
    }
    return ret;
}