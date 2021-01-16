/********************************************************************/
/*
      FILE        :   main.c
      Name        :   Chalearm Saelim
      Date        :   24 September 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to implement and make some experiment about the (sequential minimal optimization) SMO 


      Description :   This code is based on Psudo code in the paper : 
                     "Fast Training of Support Vector Machines using Sequential Minimal Optimization"
                     John C. Platt, 2000 Aug
      Dependency  :   We use the included library as below 
                        #include "simMatDouble.h"
                        #include "listPvoid.h"
                        #include "setRealV.h"
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        24-09-2017    csaelim    First draft

*/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "simMatDouble.h"
#include "listPvoid.h"
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
struct SMOBuff
{
    struct inputSet *m_points;
    double *m_alpha;
    double *m_error;
    double m_Bias;
    
    double m_y1;
    double m_y2;
    double m_E1;
    double m_E2;
    double m_s;
    double m_k11;
    double m_k22;
    double m_k12;
    
    double m_alpha1;
    double m_alpha2;
    double m_currEta;
    int m_index1;
    int m_index2;
};
vector_double vBuff;
void initInputSet(struct inputSet *obj,int ndim,double max,double min,double max2,double min2,int type);
void clearInputSet(struct inputSet *obj);
void printInputSet(struct inputSet *obj);

void initiSMOBuff(struct SMOBuff *obj,struct inputSet *objP);
void clearSMOBuff(struct SMOBuff *obj);

double learnSMOFx(struct SMOBuff *obj,int npoint,void *kernelFn);

double linearKernelFn(vector_double *va,vector_double *vb);
double polyKernelFn(vector_double *va,vector_double *vb);
double gausRadiusKernelFn(vector_double *va,vector_double *vb);

double absf(double a);
double maxVal(double a,double b);
double minVal(double a,double b);
int takeStep(struct SMOBuff *obj);
void calCurrentEta(struct SMOBuff *obj);
double setValueInbound(const double max,const double min,const double val,const int option);
void computeLAndHInTakeStep(struct SMOBuff *obj,double *L,double *H);
int examineExam(struct SMOBuff *obj,const int index);
/* from tutorial of Sequential Minimal Optimization for SVM*/
double objectiveFnAlpha(struct SMOBuff *obj,double alpha2);
/* origin equation from Platt */
double objectiveFnAlphaOrgn(struct SMOBuff *obj,double alpha2);
void updateCurrentError(struct SMOBuff *obj,int index1or2);
double randomVal(double max,double min);
int main(int argc,char **argv)
{
    double sum1 = 0.0;
    srand(time(NULL));
    int index = 0;
    struct SMOBuff smoBf;
    struct inputSet inp;
    int numChanged = 0;
    int examineAll = 1;
    int num = 0;
    int num2 = 0;
    if (INPUT_TYPE == INPUT_DEFINED_TYPE)
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
    initiSMOBuff(&smoBf,&inp);
    printInputSet(&inp);
    while((numChanged > 0) || (examineAll))
    {
        numChanged = 0;
        if (examineAll)
        {
            for (index = 0;index < num; index++)
            {
                printf("XXXXXX-------------XXXXX Examine :%d  \n",index);
                numChanged += examineExam(&smoBf,index);
                printf("---------------------- numChanged:%d\n",numChanged);
            }
        }
        else
        {
            for (index = 0;index < num; index++)
            {
                printf("alpha[%d]=%f ,C=%f\n",index,smoBf.m_alpha[index],(double)C_ALPHA);
                if ((smoBf.m_alpha[index] > 0.0)&&(smoBf.m_alpha[index] < (double)C_ALPHA))
                {
                    numChanged += examineExam(&smoBf,index);
                }
                else
                {
                    /* do nothing */
                }
            }
        }
        if (examineAll == 1)
        {
            examineAll = 0;
        }
        else if (numChanged == 0)
        {
            examineAll = 1;
        }
        else
        {
            /* do nothing */
        }
    }
    printf("Hey jui Biso:%f\n",smoBf.m_Bias);
    for (index = 0;index < num; index++)
    {
        sum1 += smoBf.m_alpha[index]*inp.m_out[index];
        printf("i:%d  y:%d, fx:%f, y(%d)*alph(%d):%0.12f\n",index,(int)inp.m_out[index],learnSMOFx(&smoBf,index,gausRadiusKernelFn),index,index,smoBf.m_alpha[index]*inp.m_out[index]);
    }
    printf("SIGMA(y*alpha) = %f \n",sum1);
    printf("Call taskStep :%u\n",countCallTask);
    clearInputSet(&inp); 
    clearSMOBuff(&smoBf);
    delete_vector_double(&vBuff);
    return 0;
}

double maxVal(double a,double b)
{
    double ret = a;
    if (a<b)
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
    if (a>b)
    {
        ret = b;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

double randomVal(double max,double min)
{
    if (((int)(max-min)) ==  0)
    {
        return min;
    }
    else
    {
        return min + rand()%(int)(max-min);
    }
}

double objectiveFnAlphaOrgn(struct SMOBuff *obj,double alpha2)
{
    double f1 = 0.0;
    double f2 = 0.0;
    double v1 = 0.0;
    double v2 = 0.0;
    double gamma = 0.0;
    double ret = 0.0;
    double delTmp = 0.0;
    if ((obj != NULL)&&(alpha2 >=0.0))
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
double objectiveFnAlpha(struct SMOBuff *obj,double alpha2)
{
    double c1 = (0.5)*obj->m_currEta;
    return c1*pow(alpha2,2)+alpha2*((obj->m_points->m_out[obj->m_index2]*(obj->m_E1-obj->m_E2))-(obj->m_currEta*obj->m_alpha2));
}

int examineExam(struct SMOBuff *obj,const int index)
{
    int num = 0;
    int index1 = 0;
    int index3 = 0;
    double temp1 = 0.0;
    double temp2 = 0.0;
    int ret = 0;
    double r2 = 0.0;
    if (obj != NULL)
    {
        obj->m_y2 = obj->m_points->m_out[index];
        obj->m_alpha2 = obj->m_alpha[index];
        obj->m_index2 = index;
        updateCurrentError(obj,2);
        r2 = (obj->m_E2)*(obj->m_y2);
        ret = 1;
        printf("E2:%f, r2 : %f, a2:%f\n",obj->m_E2,r2,obj->m_alpha2);
    }
    else
    {
        printf("== Error obj is Null in examineExam, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    if ((ret == 1) && (( (r2 < -TOL) && (obj->m_alpha2 < (double)C_ALPHA)) || ((r2 > TOL) && (obj->m_alpha2 > 0.0))))
    {
        ret = 0;
        num = obj->m_points->m_numInput;
        for (index1 =0 ;index1 < num; index1++)
        {
                if ((obj->m_alpha[index1] >0)&&(obj->m_alpha[index1] <C_ALPHA))
                {
                    temp2 = absf(obj->m_E2 - obj->m_error[index1]);
                    if (temp2 > temp1)
                    {
                        temp1 = temp2;
                        index3 = index1;
                        
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
        if (index3 >= 0)
        {
        printf("Examine do case 1, id1:%d\n",index3);
            obj->m_index1 = index3;
            if (takeStep(obj))
            {
                ret = 1;
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
        if (ret == 0)
        {
            printf("Examine do case 2\n");
            temp2 =  randomVal((double)(obj->m_points->m_numInput),0.0);
            num = ((int)temp2) + (obj->m_points->m_numInput); 
            
            printf("Examine do case 2, start:%d to %d , numI:%d\n",(int)temp2,num,(int)(obj->m_points->m_numInput));
            for (index1=(int)temp2;index1 < num;index1++)
            {
                index3 = index1%(obj->m_points->m_numInput); 
                if ((obj->m_alpha[index3] >0)&&(obj->m_alpha[index3] <C_ALPHA))
                {
                    printf("    i:%d, alph:%f, takeStep \n",index3,obj->m_alpha[index3]);
                    obj->m_index1 = index3;
                    if (takeStep(obj))
                    {
                        ret = 1;
                        index1 = num;
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
        }
        else
        {
            /* do nothing */
        }
        if (ret == 0)
        {
            temp2 =  randomVal((double)(obj->m_points->m_numInput),0.0);
            num = ((int)temp2) + (obj->m_points->m_numInput);
            printf("Examine do case 3, start:%d to %d , numI:%d\n",(int)temp2,num,(int)(obj->m_points->m_numInput));
            for (index1=(int)temp2;index1 < num;index1++)
            {
                index3 = index1%(obj->m_points->m_numInput);
                obj->m_index1 = index3;
                printf("    i:%d, alph:%f, takeStep \n",index3,obj->m_alpha[index3]);
                if (takeStep(obj))
                {
                    ret = 1;
                    index1 = num;
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
    else
    {
        ret = 0;
    }
    return ret;
}
void updateCurrentError(struct SMOBuff *obj,int index1or2)
{
    double *tmp = NULL;
    double *alphaTmp = NULL;
    int *ind = NULL;
    if (obj!=NULL)
    {
        if (index1or2 ==1)
        {
            tmp = &(obj->m_E1);
            ind = &(obj->m_index1);
            alphaTmp = &(obj->m_alpha1);
        }
        else if (index1or2 == 2)
        {
            tmp = &(obj->m_E2);
            ind = &(obj->m_index2);
            alphaTmp = &(obj->m_alpha2);
        }
        else
        {
            /* do nothing */
        }
        if ((tmp != NULL)&&(ind != NULL)&&(alphaTmp != NULL))
        {
            if ( (*alphaTmp > 0)&&(*alphaTmp < C_ALPHA))
            {
               *tmp = obj->m_error[*ind];  
              // *tmp = learnSMOFx(obj,*ind,gausRadiusKernelFn)-obj->m_points->m_out[*ind];
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
    if (a<0)
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
void computeLAndHInTakeStep(struct SMOBuff *obj,double *L,double *H)
{
    if ((obj!=NULL)&&(L!=NULL)&&(H!=NULL))
    {        
        if (obj->m_y1 == obj->m_y2)
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
void calCurrentEta(struct SMOBuff *obj)
{
    int index1 = 0;
    int index2 = 0;
    if (obj != NULL)
    {
        index1 = obj->m_index1;
        index2 = obj->m_index2;
        obj->m_k11 = gausRadiusKernelFn(&(obj->m_points->m_dat[index1]),&(obj->m_points->m_dat[index1]));
        obj->m_k22 = gausRadiusKernelFn(&(obj->m_points->m_dat[index2]),&(obj->m_points->m_dat[index2]));
        obj->m_k12 = gausRadiusKernelFn(&(obj->m_points->m_dat[index1]),&(obj->m_points->m_dat[index2]));
        obj->m_currEta = (2*(obj->m_k12))-(obj->m_k11)-(obj->m_k22);
        printf("k11:%f, k22:%f, k12:%f, Eta:%f \n",obj->m_k11,obj->m_k22,obj->m_k12,obj->m_currEta);
    }
    else
    {
        printf("Error in calCurrentEta, obj :%p, ln:%d , file:%s\n",obj,__LINE__,__FILE__);
    }
}
/*
    opt - bit set
    1 - no max checking
    2 - no min checking
    
    No set bit (option = 0) : check max and min
*/
double setValueInbound(const double max,const double min,const double val,const int option)
{
    double tmp = val;
    if ( (max < val) && ((option&0x1)== 0))
    {
        tmp = max;
    }
    else if ( (min > val) && ((option&0x2)== 0))
    {
        tmp = min;
    }
    else
    {
        /* do nothing */
    }
    return tmp;
}
int takeStep(struct SMOBuff *obj)
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
    double b1 = 0.0;
    double b2 = 0.0;
    double bNew = 0.0;
    double bDel = 0.0;
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    int index = 0;
    int num = 0;
    int index1 = obj->m_index1;
    int index2 = obj->m_index2;
    if (index1 != index2)
    {
    countCallTask++;
        obj->m_alpha1 = obj->m_alpha[index1];
        obj->m_y1 = obj->m_points->m_out[index1];
        obj->m_s = (obj->m_y1)*(obj->m_y2);
        updateCurrentError(obj,1);
        computeLAndHInTakeStep(obj,&L,&H);
 printf("(H,L):(%f,%f), (E1,E2):(%f,%f), a1:%f, a2:%f\n",H,L,obj->m_E1,obj->m_E2,obj->m_alpha1,obj->m_alpha2);
        if (L!=H)
        {
            calCurrentEta(obj);
      
            if (obj->m_currEta <0)
            {
                a2 = obj->m_alpha2-((obj->m_y2)*(obj->m_E1-obj->m_E2)/obj->m_currEta);
         printf("Eta <0 --> a2 : %f ",a2);
                a2 = setValueInbound(H,L,a2,0);
                printf(" new a2:%f\n",a2);
            }
            else
            {
                Lobj = objectiveFnAlpha(obj,L);
                tmp1 = objectiveFnAlphaOrgn(obj,L);
                tmp2 = objectiveFnAlphaOrgn(obj,H);
                Hobj = objectiveFnAlpha(obj,H);
                printf("(Lobj,Hobj):(%f,%f)\n",Lobj,Hobj);
                if ((Lobj!=tmp1)||(Hobj!=tmp2))
                {
                    printf("i357: Found something wrong \n");
                    printf("Lobj : %f, org:%f\n",Lobj,tmp1);
                    printf("Hobj : %f, org:%f\n",Hobj,tmp2);
                    printf("End of i357: Found something wrong \n");
                }
                else
                {
                    // Do nothing
                }
                if (Lobj > Hobj+EPS)
                {
                    a2 = L;
                }
                else if (Lobj < Hobj-EPS)
                {
                    a2 = H;
                }
                else 
                {
                    a2 = obj->m_alpha2;
                }
            }
            if (a2 < ROUND_NUM)
            {
                a2 = 0;
            }
            else if (a2 > C_ALPHA-ROUND_NUM)
            {
                a2 = C_ALPHA;
            }
            else
            {
                /* do nothing */
            }
            if (absf(a2-obj->m_alpha2)<EPS*(a2+obj->m_alpha2+EPS))
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
                tmp1 = (obj->m_y1)*(a1-obj->m_alpha1);
                tmp2 = (obj->m_y2)*(a2-obj->m_alpha2);
                a1 = obj->m_alpha1+(obj->m_s)*(obj->m_alpha2-a2);
                if ((obj->m_alpha1 > 0)&&(obj->m_alpha1 < C_ALPHA))
                {
                    bNew = (obj->m_E1)+((obj->m_k11)*tmp1)+(tmp2*(obj->m_k12))+obj->m_Bias;
                }
                else if ((obj->m_alpha2 > 0)&&(obj->m_alpha2 < C_ALPHA))
                {
                    bNew = (obj->m_E2)+((obj->m_k12)*tmp1)+(tmp2*(obj->m_k22))+obj->m_Bias;
                }
                else
                {
                    b1 = (obj->m_E1)+((obj->m_k11)*tmp1)+(tmp2*(obj->m_k12))+obj->m_Bias;
                    b2 = (obj->m_E2)+((obj->m_k12)*tmp1)+(tmp2*(obj->m_k22))+obj->m_Bias;
                    bNew = (b1+b2)*0.5;
                }
                bDel = bNew-obj->m_Bias;
                obj->m_Bias = bNew;
                num = obj->m_points->m_numInput;
                for (index = 0; index < num; index++)
                {
                    k1i = obj->m_alpha[index];
                    if ((k1i > 0)&&(k1i < C_ALPHA))
                    {
                        k1i = gausRadiusKernelFn(&(obj->m_points->m_dat[index1]),&(obj->m_points->m_dat[index]));
                        k2i = gausRadiusKernelFn(&(obj->m_points->m_dat[index2]),&(obj->m_points->m_dat[index])); 
                        obj->m_error[index] = obj->m_error[index] +(k1i*tmp1)+(k2i*tmp2)-bDel;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                obj->m_error[index1] = 0;
                obj->m_error[index2] = 0;
                obj->m_alpha[index1] = a1;
                obj->m_alpha[index2] = a2;
for (index = 0; index < num; index++)
{
    printf("error[%d]:%f, alpha:%f \n",index,obj->m_error[index],obj->m_alpha[index]);
}
printf("b1:%f, b2:%f New Bias:%f \n",b1,b2,obj->m_Bias);
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

double linearKernelFn(vector_double *va,vector_double *vb)
{
    double ret = 0.0;
    if (multiply_vt_v_double(va,vb,&ret) != 0)
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
    vector_double tempV =  new_vector_double(0);
    const double l_input[NUM_INPUT_DEFINE][NUM_ATTRB_INPUT_DEFINE] = INPUT_DEFINE;
    const double l_outp[NUM_INPUT_DEFINE] = OUTPUT_DEFINE;
    if (obj != NULL)
    {
        obj->m_numInput = 0;
        obj->m_dat = NULL;
        obj->m_out = NULL; 
        if (type == 0)
        {
            obj->m_numInput = NUM_TRAIN_EX;
            num = NUM_TRAIN_EX;
            obj->m_dat = (vector_double*)malloc(sizeof(vector_double)*num); 
            obj->m_out = (double*)malloc(sizeof(double)*num);
            if ((obj->m_dat != NULL) && (obj->m_out != NULL))
            {
                for (index = 0;index < num;index++)
                {
                    obj->m_dat[index] = new_vector_double(ndim);
                    if (half > index)
                    {
                        obj->m_out[index] =-1.0;
                        initial_vector_double(&(obj->m_dat[index]),vect_rang2);
                    }
                    else
                    {
                        obj->m_out[index] = 1.0;
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
            if ((obj->m_dat != NULL) && (obj->m_out != NULL))
            {
                for (index = 0 ; index < num ; index++)
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
    if (obj!=NULL)
    {
        num = obj->m_numInput;
        for (index = 0;index < num;index++)
        { 
            if (obj->m_out[index] >-1)
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
    if (obj != NULL)
    {
        num = obj->m_numInput;
        if (obj->m_dat != NULL)
        {
            for (index = 0 ;index < num;index++)
            { 
                delete_vector_double(&(obj->m_dat[index]));
            }
            printf("clearInputSet 1\n");
            free(obj->m_dat);
            obj->m_dat = NULL;
        }
        else
        {
            /* do nothing */
        }
        if (obj->m_out != NULL)
        {
            printf("clearInputSet 2\n");
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

void initiSMOBuff(struct SMOBuff *obj,struct inputSet *objP)
{
    int num = 0;
    int index = 0;
    if ((obj != NULL) && (objP != NULL))
    {
        obj->m_points = objP;
        num = objP->m_numInput;
        if (num > 0)
        {
            obj->m_alpha = (double*)malloc(sizeof(double)*num);
            obj->m_error = (double*)malloc(sizeof(double)*num);
        }
        else
        {
            obj->m_alpha = NULL;
            obj->m_error = NULL;
        }
        if (obj->m_alpha != NULL)
        {
            for (index = 0 ;index < num;index++)
            {
                obj->m_alpha[index] = 0.0;
            }
        }
        else
        {
            printf("Cannot allocate alpha arry ln:%d, fl:%s\n",__LINE__,__FILE__);
        }
        if (obj->m_error != NULL)
        { 
            for (index = 0 ;index < num;index++)
            {
                obj->m_error[index] = 0.0;
            }
        }
        else
        {
            printf("Cannot allocate error arry ln:%d, fl:%s\n",__LINE__,__FILE__);
        }/*
    int index = 0;
        for (index = 0;index < num;index++)
        {
            obj->m_alpha[index] = randomVal(C_ALPHA,0);
            obj->m_error[index] = randomVal(100,0);
        }*/
        obj->m_Bias = 0.0;
        obj->m_E1 = 0.0;
        obj->m_E2 = 0.0;
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
    }
    else
    {
        /* do nothing */
    }
}
void clearSMOBuff(struct SMOBuff *obj)
{
    if (obj != NULL)
    {
        if (obj->m_alpha != NULL)
        {
            free(obj->m_alpha);
            obj->m_alpha = NULL;
        }
        else
        {
            /* do nothing */
        }
        if (obj->m_error != NULL)
        {
            free(obj->m_error);
            obj->m_error = NULL;
        }
        else
        {
            /* do nothing */
        }
        obj->m_points = NULL;
    }
    else
    {
        /* do nothing */
    }
}

double learnSMOFx(struct SMOBuff *obj,int npoint,void *kernelFn)
{
    int index = 0;
    double ret = 0.0;
    struct inputSet *points = NULL; 
    int num = 0;
    double (*Kfn)(vector_double*,vector_double*) = kernelFn;
    double tmp = 0;
    if ((obj!=NULL)&&(kernelFn !=NULL)&&(npoint >= 0))
    {
        points = obj->m_points;
        num = points->m_numInput;
        for (index = 0;index < num;index++)
        {
            if (obj->m_alpha[index] > 0.0)
            {
                if ((index == npoint) && (kernelFn == gausRadiusKernelFn))
                {
                    tmp = 1.0;
                }
                else
                {
                    tmp = Kfn(&(points->m_dat[index]),&(points->m_dat[npoint]));
                }
                ret +=  obj->m_alpha[index]*points->m_out[index]*tmp;
            }
            else
            {
                /* do nothing */
            }
        }
        printf("ret :%f \n",ret);
        ret = ret - obj->m_Bias;
    }
    else
    {
        printf("learnSMOFx is error ln:%d \n",__LINE__);
    }
    return ret;
}