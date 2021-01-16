/********************************************************************/
/*
      FILE        :   main.c
      Name        :   Chalearm Saelim
      Date        :   19 September 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to implement and make some experiment about the SMO Keerthi modified version 2


      Description :   it is based on SMO K1
      Dependency  :   We use the included library as below 
                        #include "simMatDouble.h"
                        #include "listPvoid.h"
                        #include "setRealV.h"
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        19-09-2017    csaelim    First draft

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
#define TOL 0.00002
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
struct SMOWSS4MBuff
{
    struct inputSet *m_points;
    double *m_alpha;
    double *m_fCache;
    double m_Bias;
    
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
    
     
    
    struct rvSet m_supportVectSet;

    double *m_G;
    double m_GMax;
    double m_GMin;
    int  m_i;
    int  m_j;
    /*
        if (added2RVSet(obj,&tmpI) == 0)
        ret = removedValRVSet(obj,&dObj[index],0);
        unsigned long int  isInRVSet(struct rvSet *obj,void *val);
    */
};

vector_double vBuff;
void initInputSet(struct inputSet *obj,int ndim,double max,double min,double max2,double min2,int type);
void clearInputSet(struct inputSet *obj);
void printInputSet(struct inputSet *obj);

double learnSMOFx(struct SMOWSS4MBuff *obj,int npoint,void *kernelFn);
void initialDoubleArea(double *dat,double val,int num);
double* newDoubleArea(int size,int *ret);
int delDoubleArea(void **dat);

double linearKernelFn(vector_double *va,vector_double *vb);
double polyKernelFn(vector_double *va,vector_double *vb);
double gausRadiusKernelFn(vector_double *va,vector_double *vb);
 
double maxVal(double a,double b);
double minVal(double a,double b);
/************** ---- SMOWSS4MBuff class ************************/

/* Public method */
void initiSMOWSS4MBuff(struct SMOWSS4MBuff *obj,struct inputSet *objP); 
void clearSMOWSS4MBuff(struct SMOWSS4MBuff *obj);  

void selectBWSS3(struct SMOWSS4MBuff *obj);
double Qfn(struct SMOWSS4MBuff *obj,const int index1,const int index2);
  
void printSMOWSS4MBuff(struct SMOWSS4MBuff *obj,unsigned int opt); 
/* Private method */ 
 
/*
    opt - bit set
    1 - no max checking
    2 - no min checking
*/

double setValueInbound(const double max,const double min,const double val,const int option);

/************** ----End of SMOWSS4MBuff class ************************/

double randomVal(double max,double min);
int main(int argc,char **argv)
{ 
    double sum = 0.0;
    double sum1 = 0.0;
    srand(time(NULL));
    double a = 0.0;
    int index = 0; 
    struct SMOWSS4MBuff smoBf;
    struct inputSet inp;
    int num = 0;
    int num2 = 0;
    
    
    int i = 0;
    int j = 0;
    double oldAi = 0.0;
    double oldAj = 0.0;
    double deltaAi = 0.0;
    double deltaAj = 0.0;
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
    initiSMOWSS4MBuff(&smoBf,&inp); 
    printInputSet(&inp);
    printSMOWSS4MBuff(&smoBf,0x1F00);
    /*  main loop wss3 */
    while (1) 
    {
        selectBWSS3(&smoBf);
        i = smoBf.m_i;
        j = smoBf.m_j;
        if ( j != -1)
        {
            a = Qfn(&smoBf,i,i) + Qfn(&smoBf,j,j) -(2.0 *Qfn(&smoBf,j,i));
            if ( a <= 0.0)
            {
                a = TOL;
            }
            else
            {
                /* do nothing */
            }
            smoBf.m_Bias = ((-1.0)*(smoBf.m_points->m_out[i])*(smoBf.m_G[i])) +((smoBf.m_points->m_out[j])*(smoBf.m_G[j]));
            
            /* update alpha */
            oldAi = smoBf.m_alpha[i];
            oldAj = smoBf.m_alpha[j];
            smoBf.m_alpha[i] += (smoBf.m_points->m_out[i])*(smoBf.m_Bias)/a;
            smoBf.m_alpha[j] -= (smoBf.m_points->m_out[j])*(smoBf.m_Bias)/a;
            /* project alpha back to the feasible region */
            sum = ((smoBf.m_points->m_out[i])*oldAi) +((smoBf.m_points->m_out[j])*oldAj);
            
            smoBf.m_alpha[i] =  setValueInbound(C_ALPHA,0,smoBf.m_alpha[i],0);
            smoBf.m_alpha[j] =  (smoBf.m_points->m_out[j])*(sum - ((smoBf.m_points->m_out[i])*(smoBf.m_alpha[i])));
            smoBf.m_alpha[j] =  setValueInbound(C_ALPHA,0,smoBf.m_alpha[j],0);
            smoBf.m_alpha[i] =  (smoBf.m_points->m_out[i])*(sum - ((smoBf.m_points->m_out[j])*(smoBf.m_alpha[j])));
            
            /* update gradient */
            deltaAi = smoBf.m_alpha[i] - oldAi;
            deltaAj = smoBf.m_alpha[j] - oldAj;
            for (index = 0; index < num ;index++)
            {
                smoBf.m_G[index] += (Qfn(&smoBf,index,i)*deltaAi) +(Qfn(&smoBf,index,j)*deltaAj);
            }
        }
        else
        {
            printf("=========== SMO WSS3 is done ===========\n");
            break;
           
        }
    }
    
    printf("=========== XXXXXXXXXXXXXXX Bias is not yet XXXXXXXXXXXXXXXXX ===========\n");
    printf("=========== XXXXXXXXXXXXXXX Bias is not yet XXXXXXXXXXXXXXXXX ===========\n");
    printf("=========== XXXXXXXXXXXXXXX Bias is not yet XXXXXXXXXXXXXXXXX ===========\n");
    printf("Hey jui Biso:%f\n",smoBf.m_Bias);
    for(index = 0;index < num; index++)
    {
        sum1 += smoBf.m_alpha[index]*inp.m_out[index];
        printf("i:%d  y:%d, fx:%f, y*alpha:%0.39f\n",index,(int)inp.m_out[index],learnSMOFx(&smoBf,index,gausRadiusKernelFn),smoBf.m_alpha[index]*inp.m_out[index]);
    }
    printf("SIGMA YiAi = %f \n",sum1);
    printf("Call Select B :%u\n",countCallTask);
    clearInputSet(&inp); 
    clearSMOWSS4MBuff(&smoBf);
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
    if ((int)(max-min)== 0)
    {
        return min;
    }
    else
    {
        return min + rand()%(int)(max-min);
    }
}
 

void selectBWSS3(struct SMOWSS4MBuff *obj)
{
    int t = 0;
    int num = 0;
    double currG = 0.0;
    double b = 0.0;
    double tmp = 0.0;
    double a = 0.0;
    double obj_min = DBL_MAX;
    if (obj != NULL)
    {                
        obj->m_GMax = -DBL_MAX;
        obj->m_GMin = DBL_MAX;
        obj->m_i = -1;
        obj->m_j = -1;
        num =  obj->m_points->m_numInput;
        /*  select i */
        for (t = 0;t < num; t++)
        {
            if (( (obj->m_points->m_out[t] == 1.0) && (obj->m_alpha[t] < C_ALPHA)) ||
                ( (obj->m_points->m_out[t] == -1.0) && (obj->m_alpha[t] > 0.0)))
                {
                    currG = (-1)*(obj->m_points->m_out[t])*obj->m_G[t];
                    if (currG >= obj->m_GMax)
                    {
                        obj->m_i = t;
                        obj->m_GMax = currG;
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
        /* select j */
        for (t = 0; t < num;t++)
        {
            if (( (obj->m_points->m_out[t] == 1.0) && (obj->m_alpha[t] > 0.0)) ||
                ( (obj->m_points->m_out[t] == -1.0) && (obj->m_alpha[t] < C_ALPHA)))
                {
                    b = obj->m_GMax + ((obj->m_points->m_out[t])*obj->m_G[t]);
                    currG = (-1)*(obj->m_points->m_out[t])*obj->m_G[t];
                    if (currG <= obj->m_GMin)
                    { 
                        obj->m_GMin = currG;
                    }
                    else
                    {
                        /* do nothing */
                    }
                    if ( b > 0.0)
                    {
                        a = Qfn(obj,obj->m_i,obj->m_i) + Qfn(obj,t,t) -(2.0 *Qfn(obj,t,obj->m_i));
                        if (a <= 0.0)
                        {
                            a = TOL;
                        }
                        else
                        {
                            /* do nothing */
                        }
                    }
                    tmp = (-1)*( b * b )/a;
                    
                    if (tmp <= obj_min)
                    {
                        obj->m_j = t;
                        obj_min = tmp;
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
        if ( (obj->m_GMax - obj->m_GMin) < EPS)
        {
            obj->m_j = -1;
            obj->m_i = -1;
        }
        else
        {
            /*printf("========== Select B, Found MVP(i,j); (%d,%d) \n",obj->m_i,obj->m_j);*/
        }
         obj->m_Bias = b; 
    }
    else
    {
        printf("Error in selectBWSS3: obj:%p , ln:%d, file:%s\n",obj,__LINE__,__FILE__);
    }
            countCallTask++;
}

double Qfn(struct SMOWSS4MBuff *obj,const int index1,const int index2)
{
    double tmp = 0.0;
    double tmp2 = 0.0;
    int num = 0;
    if ((obj != NULL) && (index1 > -1) && (index2 > -1))
    {
        num =  obj->m_points->m_numInput;
        if ( (index1 < num) && (index2 < num))
        {
            tmp2 = gausRadiusKernelFn(&(obj->m_points->m_dat[index1]),&(obj->m_points->m_dat[index2]));
            tmp = (obj->m_points->m_out[index1])*(obj->m_points->m_out[index2])*tmp2;
        }
        else
        {
            printf("Error in Qfn, index1:%d,index2:%d, ln:%d file:%s\n",index1,index2,__LINE__,__FILE__);
        }
    }
    else
    {
        printf("Error in Qfn, obj:%p, index1:%d,index2:%d, ln:%d file:%s\n",obj,index1,index2,__LINE__,__FILE__);
    }
    return tmp;
}    
void printSMOWSS4MBuff(struct SMOWSS4MBuff *obj,unsigned int opt)
{
    int index = 0;
    int numInput = 0;
    /*
        struct inputSet *m_points;
    double *m_alpha;
    double *m_fCache;
    double m_Bias;
    double m_b_up; 
    double m_b_low; 
    
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
    long int m_i_up;  
    long int m_i_low; 
     
    struct rvSet m_supportVectSet;
    */
    /* bit: 0 -- show i1 and i2 information */
    /* bit: 1 -- show k and s information */
    /* bit: 2 -- show a1 and a2 information */
    /* bit: 3 -- show Bias information */ 
    /* bit: 5 -- show F1 and F2 information */
    /* bit: 6 -- show Alpha set information */
    /* bit: 7 -- show fCache set information */
    /* bit: 8 -- show 0 ground index set information */
   
    /* bit: 13 -- show SVM ground index set information */
    
    if (obj != NULL)
    {
        if (obj->m_points != NULL)
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
        if ((opt&0x04) == 0x04) /* bit 3 */
        {
            printf("Bias:%f \n",obj->m_Bias);
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
    vector_double tempV = new_vector_double(0);
    const double l_input[NUM_INPUT_DEFINE][NUM_ATTRB_INPUT_DEFINE] = INPUT_DEFINE;
    const double l_outp[NUM_INPUT_DEFINE] = OUTPUT_DEFINE;
    if (obj!=NULL)
    {
        if (type == 0)
        {
            obj->m_numInput = NUM_TRAIN_EX;
            num = NUM_TRAIN_EX;
            obj->m_dat = (vector_double*)malloc(sizeof(vector_double)*num); 
            obj->m_out = (double*)malloc(sizeof(double)*num);
            if ((obj->m_dat != NULL) && (obj->m_out != NULL))
            {
                for(index=0;index<num;index++)
                {
                    obj->m_dat[index] = new_vector_double(ndim);
                    if (half>index)
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
            if ((obj->m_dat != NULL) && (obj->m_out != NULL))
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
    if (obj != NULL)
    {
        num = obj->m_numInput;
        for(index = 0;index < num;index++)
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
    if (obj!=NULL)
    {
        num = obj->m_numInput;
        if (obj->m_dat != NULL)
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
        if (obj->m_out != NULL)
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

void initiSMOWSS4MBuff(struct SMOWSS4MBuff *obj,struct inputSet *objP)
{
    int num = 0;
    int ret = 1;
    if ((obj!=NULL)&&(objP!=NULL))
    {
        obj->m_points = objP;
        num = objP->m_numInput;
        if (num > 0)
        {
            obj->m_alpha = newDoubleArea(num,&ret);
            obj->m_fCache = newDoubleArea(num,&ret);
            obj->m_G = newDoubleArea(num,&ret);
            initialDoubleArea(obj->m_alpha,0,num);
            initialDoubleArea(obj->m_fCache,0,num);
            initialDoubleArea(obj->m_G,-1,num);
        }
        else
        {
            obj->m_alpha = NULL;
            obj->m_fCache = NULL;
            obj->m_G = NULL;
        }
        
        if (ret == 0)
        {
            printf("Error in initiSMOWSS4MBuff cannot allocate, ln:%d, file:%s\n",__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
        obj->m_Bias = 0.0; 
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
        
        
        obj->m_GMax = 0.0;
        obj->m_GMin = 0.0;
        obj->m_i = 0;
        obj->m_j = 0;
            /*
        type :
            1 st bit  : 0 long integer , 1 floating-point (double)
            2 nd bit  : 0 dynamic array, 1 not dynamic array
            3 rd bit  : 0 count redundant, 1 not count
            
            type = 6 --- no redundant, Not dynamic array, long integer
    
    */
 
        constructorRVSet(&(obj->m_supportVectSet),6); 
        printSMOWSS4MBuff(obj,0x10);
    }
    else    
    {
        /* do nothing */
    }
}
 

void clearSMOWSS4MBuff(struct SMOWSS4MBuff *obj)
{
    if (obj != NULL)
    {
        
        delDoubleArea((void*)&(obj->m_alpha));
        delDoubleArea((void*)&(obj->m_fCache));
        delDoubleArea((void*)&(obj->m_G));
        
        obj->m_points = NULL; 
        destructorRVSet(&(obj->m_supportVectSet));
    }
    else
    {
        /* do nothing */
    }
}

double learnSMOFx(struct SMOWSS4MBuff *obj,int npoint,void *kernelFn)
{
    int index = 0;
    double ret = 0.0;
    struct inputSet *points = NULL; 
    int num = 0;
    double (*Kfn)(vector_double*,vector_double*) = kernelFn;
    if ((obj!=NULL)&&(kernelFn !=NULL)&&(npoint >= 0))
    {
        points = obj->m_points;
        num = points->m_numInput;
        for(index = 0;index < num;index++)
        {
            if (obj->m_alpha[index] > 0)
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

void initialDoubleArea(double *dat,double val,int num)
{
    int index = 0;
    if ( (dat != NULL) && (num > 0))
    {
        for (index = 0;index < num;index++)
        {
            dat[index] = val;
        }
    }
    else
    {
        printf("Error dat is null, num:%d, ln:%d, file:%s \n",num,__LINE__,__FILE__);
    }
}

double* newDoubleArea(int size,int *ret)
{
    void *pTmp = NULL;
    if ((ret != NULL) && ( size >= 0))
    {
        pTmp = malloc(sizeof(double)*size);
        if ((pTmp == NULL) && (size != 0))
        {
            *ret = 0;
        }
        else 
        {
            /* do nothing */
        }
    }
    else if (ret != NULL)
    {
        *ret = 0;
        printf("Error Cannot allocate space (size:%d), ln:%d, file:%s \n",size,__LINE__,__FILE__);
    }
    else
    {
        printf("Error ret is null, ln:%d, file:%s \n",__LINE__,__FILE__);
    }
    return (double*)pTmp;
}

int delDoubleArea(void **dat)
{
    int ret = 0;
    if (dat != NULL)
    {
        ret = 1;
        if (*dat != NULL)
        {
            free(*dat);
            *dat = NULL;
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Error the pointer is null, ln:%d, File:%s \n",__LINE__,__FILE__);
    }
    return ret;
}
