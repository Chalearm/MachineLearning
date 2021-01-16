/********************************************************************/
/*
      FILE        :   main.c
      Name        :   Chalearm Saelim
      Date        :   24 September 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to implement and make some experiment about the (sequential minimal optimization) SMO 


      Description :  This code is for making some experiment in Feature space, input space and abut SVM
      
                     "Fast Training of Support Vector Machines using Sequential Minimal Optimization"
                     John C. Platt, 2000 Aug
      Dependency  :   We use the included library as below 
                        #include "simMatDouble.h"
                        #include "basicVarArea.h"
                        #include "listPvoid.h"
                        #include "setRealV.h"
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        24-09-2017    csaelim    First draft
      2.        02-10-2017    csaelim    Updated the kernel function
      3.        04-10-2017    csaelim    Added the XML reader feature and design kernel struture
*/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "setRealV.h"

#include "basicVarArea.h"
#include "simStringList.h"
#include "convertStr2Digi.h"
#include "simMatChar.h"
#include "listChar.h"
#include "simReadXML.h"

#define SETTING_CONF "setting.xml"

/* XML tag name define */
#define DEF_KERNEL_FN                         "KERNEL_FN"
#define DEF_POW_FACTOR                        "POW_FACTOR"
#define DEF_GAUSSIAN_VAL                      "GAUSSIAN_VAL"
#define DEF_SIGMOID_GAIN_VAL                  "SIGMOID_GAIN_VAL"
#define DEF_NUM_DIMENSION                     "NUM_DIMENSION"
#define DEF_NUM_SAMPLE                        "NUM_SAMPLE"
#define DEF_PERCEN_TRAINING_SAM               "PERCEN_TRAINING_SAM"
#define DEF_PERCEN_CLASS_A                    "PERCEN_CLASS_A"
#define DEF_SMO_WAY                           "SMO_WAY"
#define DEF_SVM_C_VAL                         "SVM_C_VAL"
#define DEF_TOLERANCE_PARAM                   "TOLERANCE_PARAM"
#define DEF_ESP_PARAM                         "ESP_PARAM"
#define DEF_MAX_RANDOM_VAL_CLASS_A            "MAX_RANDOM_VAL_CLASS_A"
#define DEF_MIN_RANDOM_VAL_CLASS_A            "MIN_RANDOM_VAL_CLASS_A"
#define DEF_MAX_RANDOM_VAL_CLASS_B            "MAX_RANDOM_VAL_CLASS_B"
#define DEF_MIN_RANDOM_VAL_CLASS_B            "MIN_RANDOM_VAL_CLASS_B"

struct kernelFn
{
    int m_nDimen;
    /*
        0 linear, 1 poly nomial, 2 guassian radius, 3 sigmoid, (default == 2) 
    */
    int m_type; 
    
    /* factor */
    double m_polyFactor;     /*   = poly :  (a + XY)^poly */
    double m_offsetFactor;   /*   = a */
    double m_gaussianVal;
    double m_gainSigmoid;
    
    double (*calKernelVal)(struct kernelFn*,const double*,const double*);
    
    /* Private */
    double *m_buff;
    double m_gainBuff;
    double m_guassianDivider;
    
    
};

/*  kernelFn method */
void constructorKFn(struct kernelFn *obj,int type,int numDim,double polyFactor,double guassianVal,double gainSigmoid);
void constructorKFn2(struct kernelFn *obj,void *xmlConfig);
void destructorKFn(struct kernelFn *obj);
const char* printKernelType(int type);
void printKFn(struct kernelFn *obj);
void assignKFntoKFnObj(struct kernelFn *obj);

double linearKFn(struct kernelFn *obj,const double *va,const double *vb);
double RadiusKFn(struct kernelFn *obj,const double *va,const double *vb);
double PolyKFn(struct kernelFn *obj,const double *va,const double *vb);
double sigmoidKFn(struct kernelFn *obj,const double *va,const double *vb);

 


struct kernelSetting
{
    struct rvSet m_datCls1;
    struct rvSet m_datCls2; 
    
/* value from the "setting.xml" configuration file */
    int m_numSample;
    int m_numDimension;
    double m_percenTrainingSam;
    double m_percenClassA;
    int m_smoWay;
    double m_cSvmVal;
    double m_tolParam;
    double m_espParam;
    
    
    /* data input value part */
    double m_maxValClsA;
    double m_minValClsA;
    double m_maxValClsB;
    double m_minValClsB;
    
/* private variable to buffer and keep some converted value */
    int m_nClassA;
    int m_nClassB;
    int m_nTrnClsA;
    int m_nTrnClsB;
    int m_nTstClsA;
    int m_nTstClsB;
    
    /* statistic area */
    double *m_meanOfTrnA;
    double *m_meanOfTrnB;
    double *m_SDOfTrnA;
    double *m_SDOfTrnB;
    
    double *m_distanceA2X;
    double *m_distanceB2X;
    
    double *m_cosVAgaistAMean;
    double *m_cosVAgaistBMean;
    
    double m_distanceMeanAandB;  /* 09-10-2017*/
    int m_nDistNokOfACls;
    int m_nDistNokOfBCls;
    int m_nDistBehideMeanNokOfACls;
    int m_nDistBehideMeanNokOfBCls;
    int m_nDatBehideMeanA;
    int m_nDatBehideMeanB;
    
    
    /* data set space */
    double **m_trnData;
    double *m_trnY;
    double **m_tstData;
    double *m_tstY;
    
    double *m_alphas;

    /* temporary variable to keep the result of calculation */
    double *m_buff;
    double *m_buff2;
    
    /*  space for Kernel calculation*/
    struct kernelFn m_kernerFn;
        
    double m_dotKMeanAAndBpoint;
    double m_distKAndB;
    double m_magnitudeKAmean;
    double m_magnitudeKBmean;
    
    int m_nDistNokOfAClsOnFs;
    int m_nDistNokOfBClsOnFs;
    int m_nDistBehideMeanNokOfAClsOnFs;
    int m_nDistBehideMeanNokOfBClsOnFs;
    int m_nDatBehideMeanAOnFs;
    int m_nDatBehideMeanBOnFs;
    
    double *m_distA2XOnFS;
    double *m_distB2XOnFS;
    
    double *m_cosVAgaistAMeanOnFS;
    double *m_cosVAgaistBMeanOnFS;
    
};

void constructorkernelSetting(struct kernelSetting *obj,const char *fileSetting);
void destructkernelSetting(struct kernelSetting *obj);

void readConfiguration2Ksetting(struct kernelSetting *obj,const char *fileSetting);
void initialTheConfVal2Ksetting(struct kernelSetting *obj);
void setVerifyAndSetTheConfVal2defautlKsetting(struct kernelSetting *obj,const int isShowError);



/* ------ utility  A group*/
/* A1 */double* newDoubleArea(int size,int *ret);
/* A2 */double** newPDoubleDArea(int size,int *ret);
/* A3 */double** new2DimDoubleArea(int size,int dmi,int *ret);
/* A4 */void initialDoubleArea(double *dat,double val,int num);
/* A5 */int delDoubleArea(void **dat);
/* A6 */int del2DimDoubleArea(void **dat,int size);
/* A7 */double randomFn(const double max,const double min);
/* A8 */int intBoundCheck(const int max,const int min,const int val,const int defaultVal,const int isShowError);
/* A9 */double doubleBoundCheck(const double max,const double min,const double val,const double defaultVal,const int isShowError);

    /* ------utility math methods B group */
    double cos2Degree(const double val);
    double calDistanceBetween2Vect(const double *va,const double *vb,double *buff,int numDim);
    double CosOfDotProductFn(const double *va,const double *vb,int numDim);
    double polyKernelFn_2(const double *va,const double *vb,double polyfactor,int numDim);
    void minusVectorDoub(const double *va,const double *vb,double *ret,int numDime);
    double gausRadiusKernelFn_2(const double *va,const double *vb,double *buff,double gussianDivider,int numDim);
    /* ------End of utility math methods  */
/* ------ End of utility */

/*------  Private methods C group*/
/* C1 */void setConfigVal2PrivateValKSetting(struct kernelSetting *obj);
/* C2 */int allocateDatInputSpaceKSetting(struct kernelSetting *obj);
/* C3 */int deallocateDatInputSpaceKSetting(struct kernelSetting *obj);
/* C4 */void setValToDatInputKSetting(struct kernelSetting *obj); 

/*  kernel calculation  D group */
/* D1 */double calMagnitudeMeanPointKsetting(struct kernelSetting *obj,double **points,int numPoint);
/* D2 */double calDotProductBetweenMeanAandB(struct kernelSetting *obj,double **points1,int numPoint1,double **points2,int numPoint2);
/* D3 */double calDistMeanA2BOnFeatureSp(struct kernelSetting *obj);
/* D4 */double calDotProductXpointAndMeanPointOnFSp(struct kernelSetting *obj,double **points,int numPoint,double *point1);
/* D5 */void calDistFromMeanP2XOnFSP(struct kernelSetting *obj);

    /* ------ statistic methods E group */
    /* E1 */int allocateStatisticSpaceKSetting(struct kernelSetting *obj);
    /* E2 */int deallocateStatisticSpaceKSetting(struct kernelSetting *obj);
    /* E3 */void calStatisticVal(struct kernelSetting *obj,int opt);
    /* E4 */void calAllMeanValue(struct kernelSetting *obj);
    /* E5 */void calAllSDValue(struct kernelSetting *obj);
    /* E6 */void calDistFromMeanP2X(struct kernelSetting *obj,double *buff,double *buff2);
    
    
    /* ------ End of statistic methods */
    /* ------ print methods F group */
    /* F1 */void printKSetting(struct kernelSetting *obj);
    /* F2 */void printPrivateValOfKSetting(struct kernelSetting *obj);
    /* F3 */void printConfigValueOfKSetting(struct kernelSetting *obj);
    /* F4 */void prntSample(double **inp,double *out,const int nSam,const int nDim);
    /* F5 */void prntASample(double *sam,const int nDim);
    /*
        bit 1st : show name (if have)
        bit 2nd : show magnitude
        bit 3rd : show unit vector
        bit 4th : include '\n'
    */
    void prntVecotWitOpt(const char *name,double *sam,const int nDim,const int opt);
    
    void prntDatWithStatisVal(struct kernelSetting *obj);
    /* ------ End of print methods */
/*------  End of Private methods */


void testEvaFn(const double *va,const double *vb,int numDim,double *buff);
void printMenu();


int main(int argc,char **argv)
{
    srand(time(NULL));
    struct kernelSetting kSet;
    /*
    double a[] = {1,2,3};
    double b[] = {2,3,4};
    double c[] = {0,0,0};

    printMenu();
    testEvaFn(a,b,3,c);
    
    */
    constructorkernelSetting(&kSet,SETTING_CONF);
    
    destructkernelSetting(&kSet);
    return 0;
}


void printMenu()
{
    printf("Kernel function setting \n");
    
}


void testEvaFn(const double *va,const double *vb,int numDim,double *buff)
{    
    printf("linearKernelFn_2 of a and b:%f \n",linearKernelFn_2(va,vb,numDim));
    printf("linearKernelFn_2 of b and a:%f \n",linearKernelFn_2(vb,va,numDim));
    printf("linearKernelFn_2 of a and a:%f \n",linearKernelFn_2(va,va,numDim));
    printf("linearKernelFn_2 of b and b:%f \n",linearKernelFn_2(vb,vb,numDim));
    printf("gausRadiusKernelFn_2 of a and b:%f \n",gausRadiusKernelFn_2(va,vb,buff,4,numDim));
    printf("gausRadiusKernelFn_2 of b and a:%f \n",gausRadiusKernelFn_2(vb,va,buff,4,numDim));
    printf("gausRadiusKernelFn_2 of a and a:%f \n",gausRadiusKernelFn_2(va,va,buff,4,numDim));
    printf("gausRadiusKernelFn_2 of b and b:%f \n",gausRadiusKernelFn_2(vb,vb,buff,4,numDim));
    printf("polyKernelFn_2 of a and a:%f \n",polyKernelFn_2(va,va,7,numDim));
    printf("polyKernelFn_2 of b and b:%f \n",polyKernelFn_2(vb,vb,7,numDim));
    printf("polyKernelFn_2 of b and a:%f \n",polyKernelFn_2(vb,va,7,numDim));
    printf("polyKernelFn_2 of a and b:%f \n",polyKernelFn_2(va,vb,7,numDim));
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
/*
double polyKernelFn(vector_double *va,vector_double *vb)
{
    double ret = pow(linearKernelFn(va,vb)+1.0,POLYFACTOR);
    
    return ret;
}
*/
/*
double gausRadiusKernelFn(vector_double *va,vector_double *vb)
{
    double ret = 0.0;
    double temp1 =GUASSIAN_DIVIDER;
    minus_v_double(va,vb,&vBuff);
    ret = linearKernelFn(&vBuff,&vBuff); 
    if(ret != 0.0)
    { 
        ret = exp(ret/temp1); 
    }
    else
    {
        ret = 1;
    }
    return ret;
}*/


double calDistanceBetween2Vect(const double *va,const double *vb,double *buff,int numDim)
{
    double tmp = 0.0;
    if ( (va != NULL) && (vb != NULL) && (numDim > 0) && (buff != NULL))
    {
        minusVectorDoub(va,vb,buff,numDim);
        tmp = linearKernelFn_2(buff,buff,numDim);
        tmp = pow(tmp,0.5);
    }
    else
    {
        printf(" Error in calDistanceBetween2Vect, va:%p,vb:%p, buff:%p, numDim:%d ln:%d, file:%s\n",va,vb,buff,numDim,__LINE__,__FILE__);
    }
    return tmp;
}


double cos2Degree(const double val)
{
    return 180.0*acos(val)/3.1415926535897932384626;
}

double CosOfDotProductFn(const double *va,const double *vb,int numDim)
{
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    if ((va != NULL) && (vb != NULL) && (numDim > 0))
    {
        tmp1 = pow(linearKernelFn_2(va,va,numDim),0.5);
        tmp2 = pow(linearKernelFn_2(vb,vb,numDim),0.5);
        if( (tmp1 != 0) && (tmp2 != 0))
        {
            tmp1 = linearKernelFn_2(va,vb,numDim)/(tmp1*tmp2);
        }
        else
        {
            tmp1 = 0.0;
        }
    }
    else
    {
        /* do nothing */
    }
    return tmp1;
}

double polyKernelFn_2(const double *va,const double *vb,double polyfactor,int numDim)
{
    double ret = pow(linearKernelFn_2(va,vb,numDim)+1.0,polyfactor);
    
    return ret;
}
double gausRadiusKernelFn_2(const double *va,const double *vb,double *buff,double gussianDivider,int numDim)
{
    
    double ret = 0.0;
    minusVectorDoub(va,vb,buff,numDim);
    ret = linearKernelFn_2(buff,buff,numDim);
    if ((ret != 0.0) && (gussianDivider != 0))
    { 
        ret = exp(ret/gussianDivider); 
        
    }
    else
    {
        ret = 1;
        if (gussianDivider == 0)
        {
            printf("Error gussianDivide is zero in gausRadiusKernelFn, ln:%d, file:%s \n",__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
    }
    return ret;
}


int intBoundCheck(const int max,const int min,const int val,const int defaultVal,const int isShowError)
{
    int ret = val;
    if (( (val <= max) && ( val >= min) ) == 0 )
    {
        ret = defaultVal;
        if ( isShowError == 1)
        {
            printf("Out of range (%d,%d) from:%d to %d \n",max,min,val,defaultVal);
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
double doubleBoundCheck(const double max,const double min,const double val,const double defaultVal,const int isShowError)
{
    double ret = val;
    if (( (val <= max) && ( val >= min) ) == 0 )
    {
        ret = defaultVal;
        if ( isShowError == 1)
        {
            printf("Out of range (%f,%f) from:%f to %f \n",max,min,val,defaultVal);
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

/* K constructor */
void constructorkernelSetting(struct kernelSetting *obj,const char *fileSetting)
{ 
    
    int ret = ( obj != NULL) && (fileSetting != NULL);
    if ( ret == 1)
    {
        initialTheConfVal2Ksetting(obj);
        readConfiguration2Ksetting(obj,fileSetting);
        setVerifyAndSetTheConfVal2defautlKsetting(obj,1);
        
        setConfigVal2PrivateValKSetting(obj);
        ret = allocateDatInputSpaceKSetting(obj);
        ret =  (ret == 1) && allocateStatisticSpaceKSetting(obj);
        printConfigValueOfKSetting(obj);
        
        printKFn(&(obj->m_kernerFn));
        printPrivateValOfKSetting(obj);
        
        
        obj->m_dotKMeanAAndBpoint = 0.0;
        obj->m_distKAndB = 0.0;
        obj->m_magnitudeKAmean = 0.0;
        obj->m_magnitudeKBmean = 0.0;
        
        if (ret == 0 )
        {
            printf("Error allocateDatInputSpaceKSetting task is not done, ln:%d, file:%s \n",__LINE__,__FILE__);
        }
        else
        { 
            setValToDatInputKSetting(obj); 
            calStatisticVal(obj,0);
            
            obj->m_magnitudeKAmean = calMagnitudeMeanPointKsetting(obj,obj->m_trnData,obj->m_nTrnClsA);
            obj->m_magnitudeKBmean = calMagnitudeMeanPointKsetting(obj,&(obj->m_trnData[obj->m_nTrnClsA]),obj->m_nTrnClsB);
            obj->m_dotKMeanAAndBpoint = calDotProductBetweenMeanAandB(obj,obj->m_trnData,obj->m_nTrnClsA,&(obj->m_trnData[obj->m_nTrnClsA]),obj->m_nTrnClsB);
            obj->m_distKAndB = calDistMeanA2BOnFeatureSp(obj);\
            calDistFromMeanP2XOnFSP(obj);
            prntDatWithStatisVal(obj);
            
            /*
            prntSample(obj->m_trnData,obj->m_trnY,obj->m_nTrnClsA,obj->m_numDimension);
            prntSample(&(obj->m_trnData[obj->m_nTrnClsA]),&(obj->m_trnY[obj->m_nTrnClsA]),obj->m_nTrnClsB,obj->m_numDimension);
            printf(" Test part\n");
            prntSample(obj->m_tstData,obj->m_tstY,obj->m_nTstClsA,obj->m_numDimension);
            prntSample(&(obj->m_tstData[obj->m_nTstClsA]),&(obj->m_tstY[obj->m_nTstClsA]),obj->m_nTstClsB,obj->m_numDimension);
 */
 
            /*
    void prntVecotWitOpt(const char *name,double *sam,const int nDim,const int opt);*/
            prntVecotWitOpt("SD of A Cls  ",obj->m_SDOfTrnA,obj->m_numDimension,0xb);
            prntVecotWitOpt("SD of B Cls  ",obj->m_SDOfTrnB,obj->m_numDimension,0xb);
            prntVecotWitOpt("mean of A Cls",obj->m_meanOfTrnA,obj->m_numDimension,0xb);
            prntVecotWitOpt("mean of B Cls",obj->m_meanOfTrnB,obj->m_numDimension,0xb);
            printf("Dist mean A to mean B :%f \n",obj->m_distanceMeanAandB);
            printf("Dist mean A to mean B   on Feature Sp:%.39f\n",obj->m_distKAndB);
            printf("Dot of mean A ,  mean B on Feature Sp:%.39f\n",obj->m_dotKMeanAAndBpoint);
            printf("Magnitude of mean A     on Feature Sp:%.39f\n",obj->m_magnitudeKAmean);
            printf("Magnitude of mean B     on Feature Sp:%.39f\n",obj->m_magnitudeKBmean);
 
       }
    }
    else
    {
        printf("Error kernelSetting obj is Null, setting file addr:%p ln:%d, file:%s\n",fileSetting,__LINE__,__FILE__);
    }
}
void destructkernelSetting(struct kernelSetting *obj)
{
    if (obj != NULL)
    {
        destructorKFn(&(obj->m_kernerFn));
        deallocateStatisticSpaceKSetting(obj);
        deallocateDatInputSpaceKSetting(obj);
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}
void initialTheConfVal2Ksetting(struct kernelSetting *obj)
{
    if ( obj != NULL)
    {
        obj->m_numDimension = 3;
        obj->m_numSample = 100;
        obj->m_percenTrainingSam = 70.0;
        obj->m_percenClassA = 50.0;
        obj->m_smoWay = 2;

        obj->m_cSvmVal = 12349;
        obj->m_tolParam = 0.001;
        obj->m_espParam = 0.001;
        obj->m_maxValClsA = 1000.0;
        obj->m_minValClsA = 0;
        obj->m_maxValClsB = 0;
        obj->m_minValClsB = -1000.0;
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}
void setVerifyAndSetTheConfVal2defautlKsetting(struct kernelSetting *obj,const int isShowError)
{
    double tmpDouble = 0.0;
    if ( obj != NULL)
    {
        obj->m_numDimension       = intBoundCheck(1000000000,1,obj->m_numDimension,3,isShowError);
        obj->m_numSample          = intBoundCheck(1000000000,3,obj->m_numSample,100,isShowError);
        obj->m_percenTrainingSam  = doubleBoundCheck(100.0,1.0,obj->m_percenTrainingSam,70.0,isShowError);
        obj->m_percenClassA       = doubleBoundCheck(100.0,1.0,obj->m_percenClassA,50.0,isShowError);
        obj->m_smoWay             = intBoundCheck(3,0,obj->m_smoWay,2,isShowError);
        
        obj->m_cSvmVal            = doubleBoundCheck(1000000000.0,0.0001,obj->m_cSvmVal,500.0,isShowError);       
        obj->m_tolParam           = doubleBoundCheck(0.1,0.000001,obj->m_tolParam,0.001,isShowError);         
        obj->m_espParam           = doubleBoundCheck(0.1,0.000001,obj->m_espParam,0.001,isShowError);
        obj->m_maxValClsA         = doubleBoundCheck(1000000000.0,-1000000000.0,obj->m_maxValClsA,1000.0,isShowError);
        obj->m_minValClsA         = doubleBoundCheck(1000000000.0,-1000000000.0,obj->m_minValClsA,-1000.0,isShowError);
        obj->m_maxValClsB         = doubleBoundCheck(1000000000.0,-1000000000.0,obj->m_maxValClsB,1000.0,isShowError);
        obj->m_minValClsB         = doubleBoundCheck(1000000000.0,-1000000000.0,obj->m_minValClsB,-1000.0,isShowError);
        
        
        if ( obj->m_maxValClsA < obj->m_minValClsA)
        {
            printf("Max A val is less than Min A, so swap value !! \n");
            tmpDouble = obj->m_maxValClsA;
            obj->m_maxValClsA = obj->m_minValClsA;
            obj->m_minValClsA = tmpDouble;
        }
        else
        {
            /* do nothing */
        }        
        if ( obj->m_maxValClsB < obj->m_minValClsB)
        {
            printf("Max B val is less than Min B, so swap value !!  \n");
            tmpDouble = obj->m_maxValClsB;
            obj->m_maxValClsB = obj->m_minValClsB;
            obj->m_minValClsB = tmpDouble;
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}

void setConfigVal2PrivateValKSetting(struct kernelSetting *obj)
{
    if ( obj != NULL)
    {
        obj->m_nClassA   = (obj->m_numSample)*(obj->m_percenTrainingSam)/100.0;
        obj->m_nClassB   =  obj->m_numSample - obj->m_nClassA;
        obj->m_nTrnClsA  =  obj->m_nClassA*(obj->m_percenTrainingSam)/100.0;
        obj->m_nTrnClsB  =  obj->m_nClassB*(obj->m_percenTrainingSam)/100.0;
        obj->m_nTstClsA  =  obj->m_nClassA -obj->m_nTrnClsA;
        obj->m_nTstClsB  =  obj->m_nClassB -obj->m_nTrnClsB;
        
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}


void setValToDatInputKSetting(struct kernelSetting *obj)
{
    int index1 = 0;
    int index2 = 0;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    double max = 0.0;
    double min = 0.0;
    
    if ( obj != NULL)
    {
        num2 = obj->m_numDimension;
        /* training data */
        max = obj->m_maxValClsA;
        min = obj->m_minValClsA;
        num1 = obj->m_nTrnClsA;
        num3 = obj->m_nTrnClsA + obj->m_nTrnClsB;
            /* A Class  (1) */
        for (index1 = 0 ;index1 < num1;index1++)
        {
            for(index2 = 0;index2 < num2;index2++)
            {
                obj->m_trnData[index1][index2] = randomFn(max,min);
                obj->m_trnY[index1] = 1.0;
            }
        }
            /* B Class  (-1) */
        max = obj->m_maxValClsB;
        min = obj->m_minValClsB;
        for (index1 = num1 ;index1 < num3;index1++)
        {
            for(index2 = 0;index2 < num2;index2++)
            {
                obj->m_trnData[index1][index2] = randomFn(max,min);
                obj->m_trnY[index1] = -1.0;
            }
        }
        /* Test data */
        num1 = obj->m_nTstClsA;
        num3 = obj->m_nTstClsA + obj->m_nTstClsB;
            /* A Class  (1) */
        max = obj->m_maxValClsA;
        min = obj->m_minValClsA;
        for (index1 = 0 ;index1 < num1;index1++)
        {
            for(index2 = 0;index2 < num2;index2++)
            {
                obj->m_tstData[index1][index2] = randomFn(max,min);
                obj->m_tstY[index1] = 1.0;
            }
        }
            /* B Class  (-1) */
        max = obj->m_maxValClsB;
        min = obj->m_minValClsB;
        for (index1 = num1 ;index1 < num3;index1++)
        {
            for(index2 = 0;index2 < num2;index2++)
            {
                obj->m_tstData[index1][index2] = randomFn(max,min);
                obj->m_tstY[index1] = -1.0;
            }
        }
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}


double calDistMeanA2BOnFeatureSp(struct kernelSetting *obj)
{
    double tmp = 0.0;
    if (obj != NULL)
    {
        tmp = pow(obj->m_magnitudeKAmean,2) + pow(obj->m_magnitudeKBmean,2) - (2*(obj->m_dotKMeanAAndBpoint));
        tmp = pow(tmp,0.5);
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    return tmp;
}

double calDotProductXpointAndMeanPointOnFSp(struct kernelSetting *obj,double **points,int numPoint,double *point1)
{
    double ret = 0.0;
    int index1 = 0;
    struct kernelFn *kobj = NULL;
    if ((obj != NULL) && (points != NULL) && (numPoint > 0) && (point1 != NULL))
    {
        kobj = &(obj->m_kernerFn);
        for (index1 = 0;index1 < numPoint;index1++)
        {
            ret += kobj->calKernelVal(kobj,points[index1],point1);
        }
        ret = ret/numPoint;
    }
    else
    {
        printf("Error kernelSetting obj is %p, points:%p, point1:%p ln:%d, file:%s\n",obj,points,point1,__LINE__,__FILE__);
    }
    return ret;
}
void calDistFromMeanP2XOnFSP(struct kernelSetting *obj)
{
    double tmp = 0.0;
    double tmp2 = 0.0;
    double tmp3 = 0.0;
    double KAmeanP2 = 0.0;
    double KBmeanP2 = 0.0;
    int index1 = 0;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    if (obj != NULL)
    {
        num1 = obj->m_nTrnClsA;
        num2 = obj->m_nTrnClsB;
        num3 = num1 + num2;
        tmp3 = pow(obj->m_distKAndB,2.0);
        KAmeanP2 = pow(obj->m_magnitudeKAmean,2);
        KBmeanP2 = pow(obj->m_magnitudeKBmean,2);
        printf("Start \n");
        for (index1 = 0 ;index1 < num1;index1++)
        {
            tmp = 2*calDotProductXpointAndMeanPointOnFSp(obj,obj->m_trnData,num1,obj->m_trnData[index1]);
            tmp2 = 2*calDotProductXpointAndMeanPointOnFSp(obj,&(obj->m_trnData[num1]),num2,obj->m_trnData[index1]);
    
            obj->m_distA2XOnFS[index1] = pow(KAmeanP2+1-tmp,0.5);
            
            obj->m_distB2XOnFS[index1] = pow(KBmeanP2+1-tmp2,0.5);
            //printf("i:%d %.9f %.9f Ax :%.9f , Bx:%.9f \n",index1,tmp,tmp2,obj->m_distA2XOnFS[index1] ,obj->m_distB2XOnFS[index1]);
            
            
            
            if (obj->m_distA2XOnFS[index1] > obj->m_distB2XOnFS[index1])
            {
                if  ((tmp3 + (pow(obj->m_distB2XOnFS[index1],2.0))) < pow(obj->m_distA2XOnFS[index1],2.0))
                {
                    obj->m_nDistBehideMeanNokOfAClsOnFs++;
                }
                else
                {
                    obj->m_nDistNokOfAClsOnFs = obj->m_nDistNokOfAClsOnFs + 1; 
                }
            }
            else if ((tmp3 + (pow(obj->m_distA2XOnFS[index1],2.0))) < pow(obj->m_distB2XOnFS[index1],2.0))
            {
                obj->m_nDatBehideMeanAOnFs++;
            }
            else
            {
                /* do nothing */
            }
        }
        printf("Half \n");
        for (index1 = num1;index1 < num3;index1++)
        {
            tmp = 2*calDotProductXpointAndMeanPointOnFSp(obj,obj->m_trnData,num1,obj->m_trnData[index1]);
            tmp2 = 2*calDotProductXpointAndMeanPointOnFSp(obj,&(obj->m_trnData[num1]),num2,obj->m_trnData[index1]);

            obj->m_distA2XOnFS[index1] = pow(KAmeanP2+1-tmp,0.5);
            obj->m_distB2XOnFS[index1] = pow(KBmeanP2+1-tmp2,0.5);
            
           if (obj->m_distB2XOnFS[index1] > obj->m_distA2XOnFS[index1])
            {
                
                if  ((tmp3 + (pow((double)obj->m_distA2XOnFS[index1],2.0))) < pow((double)obj->m_distB2XOnFS[index1],2.0))
                {
                    obj->m_nDistBehideMeanNokOfBClsOnFs++;
                }
                else
                {
                    obj->m_nDistNokOfBClsOnFs = obj->m_nDistNokOfBClsOnFs + 1; 
                }
            }
            else if ((tmp3 + (pow((double)obj->m_distB2XOnFS[index1],2.0))) < pow((double)obj->m_distA2XOnFS[index1],2.0))
            {
                obj->m_nDatBehideMeanBOnFs++;
            }
            else
            {
                /* do nothing */
            }
        }
    
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}
double calMagnitudeMeanPointKsetting(struct kernelSetting *obj,double **points,int numPoint)
{
    double sum = 0.0;
    int index1 = 0;
    int index2 = 0;
    struct kernelFn *kobj = NULL;
    if ((obj != NULL) && (points != NULL) && (numPoint > 0))
    {
        kobj = &(obj->m_kernerFn);
        for (index1 = 0;index1 < numPoint;index1++)
        {
            for (index2 = 0;index2 < numPoint;index2++)
            {
                sum += kobj->calKernelVal(kobj,points[index1],points[index2]);
            }
        }
        sum = pow(sum,0.5)/numPoint;
    }
    else
    {
        printf("Error kernelSetting obj is %p, points:%p ln:%d, file:%s\n",obj,points,__LINE__,__FILE__);
    }
    return sum;
}

double calDotProductBetweenMeanAandB(struct kernelSetting *obj,double **points1,int numPoint1,double **points2,int numPoint2)
{
    double sum = 0.0;
    int index1 = 0;
    int index2 = 0;
    struct kernelFn *kobj = NULL;
    if ((obj != NULL) && (points1 != NULL) && (numPoint1 > 0) && (points2 != NULL) && (numPoint2 > 0))
    {
        kobj = &(obj->m_kernerFn);
        for (index1 = 0;index1 < numPoint1;index1++)
        {
            for (index2 = 0;index2 < numPoint2;index2++)
            {
                sum += kobj->calKernelVal(kobj,points1[index1],points2[index2]);
            }
        }
        sum = sum/((double)(numPoint1*numPoint2));
    }
    else
    {
        printf("Error kernelSetting obj is %p, points1:%p points2:%p ln:%d, file:%s\n",obj,points1,points2,__LINE__,__FILE__);
    }
    return sum;
}
int allocateStatisticSpaceKSetting(struct kernelSetting *obj)
{
    int ret = 1;
    int num = 0;
    int num2 = 0;
    if ( obj != NULL)
    {
        num2 = obj->m_nTrnClsA + obj->m_nTrnClsB;
        num = obj->m_numDimension;
        obj->m_meanOfTrnA  = newDoubleArea(num,&ret);
        obj->m_meanOfTrnB  = newDoubleArea(num,&ret);
        obj->m_SDOfTrnA  = newDoubleArea(num,&ret);
        obj->m_SDOfTrnB  = newDoubleArea(num,&ret);
        obj->m_distanceA2X  = newDoubleArea(num2,&ret);
        obj->m_distanceB2X  = newDoubleArea(num2,&ret);
        obj->m_cosVAgaistAMean  = newDoubleArea(num2,&ret);
        obj->m_cosVAgaistBMean  = newDoubleArea(num2,&ret);
        
        obj->m_distA2XOnFS  = newDoubleArea(num2,&ret);
        obj->m_distB2XOnFS  = newDoubleArea(num2,&ret);
        obj->m_cosVAgaistAMeanOnFS  = newDoubleArea(num2,&ret);
        obj->m_cosVAgaistBMeanOnFS  = newDoubleArea(num2,&ret);

        initialDoubleArea(obj->m_distA2XOnFS,0.0,num2);
        initialDoubleArea(obj->m_distB2XOnFS,0.0,num2);
        initialDoubleArea(obj->m_cosVAgaistAMeanOnFS,0.0,num2);
        initialDoubleArea(obj->m_cosVAgaistBMeanOnFS,0.0,num2);
        initialDoubleArea(obj->m_distanceA2X,0.0,num2);
        initialDoubleArea(obj->m_distanceB2X,0.0,num2);
        initialDoubleArea(obj->m_cosVAgaistAMean,0.0,num2);
        initialDoubleArea(obj->m_cosVAgaistBMean,0.0,num2);
        initialDoubleArea(obj->m_meanOfTrnA,0.0,num);
        initialDoubleArea(obj->m_meanOfTrnB,0.0,num);
        initialDoubleArea(obj->m_SDOfTrnA,0.0,num);
        initialDoubleArea(obj->m_SDOfTrnB,0.0,num);
        
        
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    if ( ret == 0)
    {
        printf("Error allocation statistic space is not completed, ln:%d, file:%s  \n",__LINE__,__FILE__);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

int deallocateStatisticSpaceKSetting(struct kernelSetting *obj)
{
    int ret = 1;
    if ( obj != NULL)
    {
        delDoubleArea((void*)&(obj->m_meanOfTrnA));
        delDoubleArea((void*)&(obj->m_meanOfTrnB));
        delDoubleArea((void*)&(obj->m_SDOfTrnA));
        delDoubleArea((void*)&(obj->m_SDOfTrnB));
        delDoubleArea((void*)&(obj->m_distanceA2X));
        delDoubleArea((void*)&(obj->m_distanceB2X));
        delDoubleArea((void*)&(obj->m_cosVAgaistAMean));
        delDoubleArea((void*)&(obj->m_cosVAgaistBMean));
        
        delDoubleArea((void*)&(obj->m_distA2XOnFS));
        delDoubleArea((void*)&(obj->m_distB2XOnFS));
        delDoubleArea((void*)&(obj->m_cosVAgaistAMeanOnFS));
        delDoubleArea((void*)&(obj->m_cosVAgaistBMeanOnFS));
        
        
    }
    else
    {
        ret = 0;
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    return ret;
}


void calStatisticVal(struct kernelSetting *obj,int opt)
{
    double *buff = NULL;
    double *buff2 = NULL;
    int ret = 1;
    int numDim = 0;
    if (obj != NULL)
    {
        obj->m_distanceMeanAandB = 0.0;
        obj->m_nDistNokOfACls = 0;
        obj->m_nDistNokOfBCls = 0;
        obj->m_nDatBehideMeanA = 0;
        obj->m_nDatBehideMeanB = 0;
        obj->m_nDistBehideMeanNokOfACls = 0;
        obj->m_nDistBehideMeanNokOfBCls = 0;        
        obj->m_nDistNokOfAClsOnFs = 0;
        obj->m_nDistNokOfBClsOnFs = 0;
        obj->m_nDistBehideMeanNokOfAClsOnFs = 0;
        obj->m_nDistBehideMeanNokOfBClsOnFs = 0;
        obj->m_nDatBehideMeanAOnFs = 0;
        obj->m_nDatBehideMeanBOnFs = 0;
        numDim = obj->m_numDimension;
        buff = newDoubleArea(numDim,&ret);
        buff2 = newDoubleArea(numDim,&ret);
        calAllMeanValue(obj);
        calAllSDValue(obj);
        obj->m_distanceMeanAandB = calDistanceBetween2Vect(obj->m_meanOfTrnA,obj->m_meanOfTrnB,buff,numDim);
        calDistFromMeanP2X(obj,buff,buff2);
        delDoubleArea((void*)&buff);
        delDoubleArea((void*)&buff2);
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}


void calAllMeanValue(struct kernelSetting *obj)
{
    int index1 = 0;
    int index2 = 0;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0; 
    if ( obj != NULL)
    {
        num2 = obj->m_numDimension;
            /* training data */ 
        num1 = obj->m_nTrnClsA;
        num3 = obj->m_nTrnClsA + obj->m_nTrnClsB;
            /* A Class  (1) */
        for (index1 = 0 ;index1 < num1;index1++)
        {
            for(index2 = 0;index2 < num2;index2++)
            {
                obj->m_meanOfTrnA[index2] += obj->m_trnData[index1][index2];
            }
        }
            /* B Class  (-1) */ 
        for (index1 = num1 ;index1 < num3;index1++)
        {
            for(index2 = 0;index2 < num2;index2++)
            {
                obj->m_meanOfTrnB[index2] += obj->m_trnData[index1][index2];
            }
        }
        if ( (obj->m_nTrnClsA > 0) && (obj->m_nTrnClsB > 0))
        {
            for(index2 = 0;index2 < num2;index2++)
            {
                obj->m_meanOfTrnA[index2] = obj->m_meanOfTrnA[index2]/(obj->m_nTrnClsA);
                obj->m_meanOfTrnB[index2] = obj->m_meanOfTrnB[index2]/(obj->m_nTrnClsB);
            }
        }
        else
        {
            printf("Error divider are 0 nA:%d, nB:%d, ln:%d file:%s\n",obj->m_nTrnClsA,obj->m_nTrnClsB,__LINE__,__FILE__);
        }
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}


void calAllSDValue(struct kernelSetting *obj)
{
    int index1 = 0;
    int index2 = 0;
    int num1 = 0;
    int num2 = 0;
    int num3 = 0; 
    double tmp = 0.0;
    if ( obj != NULL)
    {
        num2 = obj->m_numDimension;
            /* training data */ 
        num1 = obj->m_nTrnClsA;
        num3 = obj->m_nTrnClsA + obj->m_nTrnClsB;
            /* A Class  (1) */
        for (index1 = 0 ;index1 < num1;index1++)
        {
            for(index2 = 0;index2 < num2;index2++)
            {
                tmp = obj->m_meanOfTrnA[index2] - obj->m_trnData[index1][index2];
                tmp = pow(tmp,2.0);
                obj->m_SDOfTrnA[index2] += tmp;
            }
        }
            /* B Class  (-1) */ 
        for (index1 = num1 ;index1 < num3;index1++)
        {
            for(index2 = 0;index2 < num2;index2++)
            {
                tmp = obj->m_meanOfTrnB[index2] - obj->m_trnData[index1][index2];
                tmp = pow(tmp,2.0);
                obj->m_SDOfTrnB[index2]  += tmp;
            }
        }
        if ( (obj->m_nTrnClsA > 0) && (obj->m_nTrnClsB > 0))
        {
            for(index2 = 0;index2 < num2;index2++)
            {
                obj->m_SDOfTrnA[index2] = pow(obj->m_SDOfTrnA[index2]/(obj->m_nTrnClsA),0.5);
                obj->m_SDOfTrnB[index2] = pow(obj->m_SDOfTrnB[index2]/(obj->m_nTrnClsB),0.5);
            }
        }
        else
        {
            printf("Error divider are 0 nA:%d, nB:%d, ln:%d file:%s\n",obj->m_nTrnClsA,obj->m_nTrnClsB,__LINE__,__FILE__);
        }
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}

void calDistFromMeanP2X(struct kernelSetting *obj,double *buff,double *buff2)
{
    int index = 0;
    int num = 0;
    int num2 = 0;
    int numDim = 0;
    double tmp = 0.0;
    if ( (obj != NULL) && (buff != NULL) && (buff2 != NULL))
    {
        tmp = obj->m_distanceMeanAandB;
        tmp = pow(tmp,2.0);
        numDim = obj->m_numDimension;
        num = obj->m_nTrnClsA;
        num2 = obj->m_nTrnClsA +obj->m_nTrnClsB;
        
        minusVectorDoub(obj->m_meanOfTrnB,obj->m_meanOfTrnA,buff2,numDim);
        for ( index = 0;index < num;index++)
        {
            obj->m_distanceA2X[index] = calDistanceBetween2Vect(obj->m_meanOfTrnA,obj->m_trnData[index],buff,numDim);
            obj->m_distanceB2X[index] = calDistanceBetween2Vect(obj->m_meanOfTrnB,obj->m_trnData[index],buff,numDim);
            
            /* cal angle */
            minusVectorDoub(obj->m_trnData[index],obj->m_meanOfTrnA,buff,numDim);
            obj->m_cosVAgaistAMean[index] = CosOfDotProductFn(buff,buff2,numDim);
            minusVectorDoub(obj->m_trnData[index],obj->m_meanOfTrnB,buff,numDim);
            obj->m_cosVAgaistBMean[index] = -1*CosOfDotProductFn(buff,buff2,numDim);
            
            if (obj->m_distanceA2X[index] > obj->m_distanceB2X[index])
            {
                if  (tmp + (pow((double)obj->m_distanceB2X[index],2.0)) < pow((double)obj->m_distanceA2X[index],2.0))
                {
                    obj->m_nDistBehideMeanNokOfACls++;
                }
                else
                {
                    obj->m_nDistNokOfACls = obj->m_nDistNokOfACls + 1; 
                }
            }
            else if (tmp + (pow((double)obj->m_distanceA2X[index],2.0)) < pow((double)obj->m_distanceB2X[index],2.0))
            {
                obj->m_nDatBehideMeanA++;
            }
            else
            {
                /* do nothing */
            }
            /*m_nDatBehideMeanA*/
        }
        for ( index = num;index < num2;index++)
        {
            obj->m_distanceA2X[index] = calDistanceBetween2Vect(obj->m_meanOfTrnA,obj->m_trnData[index],buff,numDim);
            obj->m_distanceB2X[index] = calDistanceBetween2Vect(obj->m_meanOfTrnB,obj->m_trnData[index],buff,numDim);
           
            /* cal angle */
            minusVectorDoub(obj->m_trnData[index],obj->m_meanOfTrnA,buff,numDim);
            obj->m_cosVAgaistAMean[index] = CosOfDotProductFn(buff,buff2,numDim);
            minusVectorDoub(obj->m_trnData[index],obj->m_meanOfTrnB,buff,numDim);
            obj->m_cosVAgaistBMean[index] = -1*CosOfDotProductFn(buff,buff2,numDim);
           if (obj->m_distanceB2X[index] > obj->m_distanceA2X[index])
            {
                
                if  (tmp + (pow((double)obj->m_distanceA2X[index],2.0)) < pow((double)obj->m_distanceB2X[index],2.0))
                {
                    obj->m_nDistBehideMeanNokOfBCls++;
                }
                else
                {
                    obj->m_nDistNokOfBCls = obj->m_nDistNokOfBCls + 1; 
                }
            }
            else if (tmp + (pow((double)obj->m_distanceB2X[index],2.0)) < pow((double)obj->m_distanceA2X[index],2.0))
            {
                obj->m_nDatBehideMeanB++;
            }
            else
            {
                /* do nothing */
            }
        }
    }
    else
    {
        printf("Error kernelSetting obj is Null or buff:%pln:%d, file:%s\n",buff,__LINE__,__FILE__);
    }
}
    /* ------ End of statistic methods */
int allocateDatInputSpaceKSetting(struct kernelSetting *obj)
{
    int nTrnS = 0;
    int nTstS = 0;
    int dim = 0;
    int ret = 1;
    if (obj != NULL)
    {
        dim   = obj->m_numDimension;
        nTrnS = obj->m_nTrnClsA + obj->m_nTrnClsB;
        nTstS = obj->m_nTstClsA + obj->m_nTstClsB;
        obj->m_trnData   =  new2DimDoubleArea(nTrnS,dim,&ret);
        obj->m_trnY      =  newDoubleArea(nTrnS,&ret);
        obj->m_buff      =  newDoubleArea(dim,&ret);
        obj->m_buff2      =  newDoubleArea(dim,&ret);
        obj->m_tstData   =  new2DimDoubleArea(nTstS,dim,&ret);
        obj->m_tstY      =  newDoubleArea(nTstS,&ret);
        obj->m_alphas      =  newDoubleArea(nTrnS,&ret);
        
        
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    if (ret == 0 )
    {
        printf("Error allocateDatInputSpaceKSetting task is not done, ln:%d, file:%s \n",__LINE__,__FILE__);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}


int deallocateDatInputSpaceKSetting(struct kernelSetting *obj)
{
    int ret = 1;
    int nTrnS = 0;
    int nTstS = 0;
    if ( obj != NULL)
    {
        nTrnS = obj->m_nTrnClsA + obj->m_nTrnClsB;
        nTstS = obj->m_nTstClsA + obj->m_nTstClsB;
        del2DimDoubleArea((void*)&(obj->m_trnData),nTrnS);
        delDoubleArea((void*)&(obj->m_trnY));
        del2DimDoubleArea((void*)&(obj->m_tstData),nTstS);
        delDoubleArea((void*)&(obj->m_tstY));
        delDoubleArea((void*)&(obj->m_buff));
        delDoubleArea((void*)&(obj->m_buff2));
        delDoubleArea((void*)&(obj->m_alphas));
    }
    else
    {
        ret = 0;
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    return ret;
}

void printPrivateValOfKSetting(struct kernelSetting *obj)
{
    if ( obj != NULL)
    {
        printf("Private value \n");
        printf("num Class A     : %d \n",obj->m_nClassA);
        printf("num Class B     : %d \n",obj->m_nClassB);
        printf("num Trn Cls A   : %d \n",obj->m_nTrnClsA);
        printf("num Trn Cls B   : %d \n",obj->m_nTrnClsB);
        printf("num Tst Cls A   : %d \n",obj->m_nTstClsA);
        printf("num Tst Cls B   : %d \n",obj->m_nTstClsB);
        printf("------------------------\n");
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}
void readConfiguration2Ksetting(struct kernelSetting *obj,const char *fileSetting)
{
/*  
    use  12 bits  last nibble
    0 = sign   1 = unsign
    0x000 char        0x010 int     0x020 short  0x030 long
    0x040 float       0x050 double  0x060 long double 
    0x070 vector_char 0x080 simString
*/
    int ret = 1;
    treeXML tXML;
    if( (obj != NULL) && (fileSetting != NULL) && getSourceToTreeXML(&tXML,fileSetting) )
    {
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_NUM_DIMENSION,"3",&(obj->m_numDimension),0x010);
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_NUM_SAMPLE,"10",&(obj->m_numSample),0x010); 
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_PERCEN_TRAINING_SAM,"70.0",&(obj->m_percenTrainingSam),0x050);
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_PERCEN_CLASS_A,"50.0",&(obj->m_percenClassA),0x050);
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_SMO_WAY,"2",&(obj->m_smoWay),0x010); 
        
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_SVM_C_VAL,"1000.0",&(obj->m_cSvmVal),0x050); 
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_TOLERANCE_PARAM,"0.001",&(obj->m_tolParam),0x050); 
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_ESP_PARAM,"0.001",&(obj->m_espParam),0x050); 
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_MAX_RANDOM_VAL_CLASS_A,"1000.0",&(obj->m_maxValClsA),0x050); 
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_MIN_RANDOM_VAL_CLASS_A,"0.0",&(obj->m_minValClsA),0x050); 
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_MAX_RANDOM_VAL_CLASS_B,"0.0",&(obj->m_maxValClsB),0x050); 
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML.root,DEF_MIN_RANDOM_VAL_CLASS_B,"-1000.0",&(obj->m_minValClsB),0x050); 
     
        constructorKFn2(&(obj->m_kernerFn),(void*)&tXML);
        destructorTreeXML(&tXML);
        if( ret == 0)
        {
            printf("There is something wrong in reading the configuration in readConfiguration2Ksetting method \n");
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Error kernelSetting obj is Null, setting file addr:%p ln:%d, file:%s\n",fileSetting,__LINE__,__FILE__);
    }
}
void printConfigValueOfKSetting(struct kernelSetting *obj)
{
    if (obj != NULL)
    {
        printf("Configuration value \n");
        printf("Num Dimension   : %d \n",obj->m_numDimension);
        printf("Num Sample      : %d \n",obj->m_numSample);
        printf("Train Sample(%c): %f \n",'%',obj->m_percenTrainingSam);
        printf("Cls Sample(%c)  : %f \n",'%',obj->m_percenClassA);
        printf("SMO Way         : %d \n",obj->m_smoWay);
        printf("C SVM Val       : %f \n",obj->m_cSvmVal);
        printf("tolerance param : %f \n",obj->m_tolParam);
        printf("ESP       param : %f \n",obj->m_espParam);
        printf("MAX val A Cls   : %f \n",obj->m_maxValClsA);
        printf("MIN val A Cls   : %f \n",obj->m_minValClsA);
        printf("MAX val B Cls   : %f \n",obj->m_maxValClsB);
        printf("MIN val B Cls   : %f \n",obj->m_minValClsB);
        printf("------------------------\n");
    }
    else
    {
        printf("Error kernelSetting obj is Null ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}

void prntSample(double **inp,double *out,const int nSam,const int nDim)
{
    int index1 = 0;
    int num1 = nSam;
    
    for (index1 = 0;index1 < num1 ;index1++)
    {
        printf("%d: %d ",index1+1,(int)out[index1]);
        prntASample(inp[index1],nDim);
        printf("\n");
    }
}

void prntASample(double *sam,const int nDim)
{
    int index1 = 0;
    int num1 = nDim;
    printf("[");
    for (index1 = 0;index1 < num1 ;index1++)
    {
        printf("%f ",sam[index1]);
    }
    printf("]");
}

/*
    bit 1st : show name (if have)
    bit 2nd : show magnitude
    bit 3rd : show unit vector
*/
void prntVecotWitOpt(const char *name,double *sam,const int nDim,const int opt)
{
    double tmp = 0.0;
    int index = 0;
    if ((sam != NULL) && (nDim > 0))
    {
        /* prepare the vector magnitude */
        if (((opt&0x02) == 0x02) || ((opt&0x04) == 0x04))
        {
            /* calculate vector magnitude */
            tmp = linearKernelFn_2(sam,sam,nDim);
            tmp = pow(tmp,0.5);
        }
        else
        {
            /* do nothing */
        }
        if (((opt&0x01) == 1) && (name != NULL))
        {
            printf("%s:",name);
        }
        else
        {
            /* do nothing */
        }
        prntASample(sam,nDim);
        if ((opt&0x02) == 0x02)
        {
            printf(" |%f|",tmp);
        }
        else
        {
            /* do nothing */
        }
        if (((opt&0x04) == 0x04) && (tmp != 0))
        {
            printf("\n[");
            for (index = 0;index < nDim ;index++)
            {
                printf("%f ",sam[index]/tmp);
            }
            printf("]");
        }
        else
        {
            /* do nothing */
        }
        if((opt&0x08) == 0x08)
        {
            printf("\n");
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Error vector obj is Null, nDim:%d ln:%d, file:%s\n",nDim,__LINE__,__FILE__);
    }
}
void prntDatWithStatisVal(struct kernelSetting *obj)
{
    int index = 0;
    int num = 0;
    int num2 = 0;
    int numDim = 0;
    int iTmp = 0;
    double dTmp = 0.0;
    if (obj != NULL)
    {
        numDim = obj->m_numDimension;
        num = obj->m_nTrnClsA;
        num2 = obj->m_nTrnClsA + obj->m_nTrnClsB;
        for (index = 0;index < num; index++)
        {
            printf("[%s]",(obj->m_distanceA2X[index]<obj->m_distanceB2X[index])?"OK":"NOK");
            printf(" k[%s]",(obj->m_distA2XOnFS[index]<obj->m_distB2XOnFS[index])?"OK":"NOK");
            prntVecotWitOpt(" 1 ",obj->m_trnData[index],numDim,1);
            printf(" %.2f %.2f,on K(%.2f %.2f), angle (A,B) :(%.2f,%.2f)\n",obj->m_distanceA2X[index],obj->m_distanceB2X[index],obj->m_distA2XOnFS[index],obj->m_distB2XOnFS[index],cos2Degree(obj->m_cosVAgaistAMean[index]),cos2Degree(obj->m_cosVAgaistBMean[index]));
        }
        for (index = num;index < num2; index++)
        {   
            printf("[%s]",(obj->m_distanceB2X[index]<obj->m_distanceA2X[index])?" OK":"NOK");
            printf(" k[%s]",(obj->m_distB2XOnFS[index]<obj->m_distA2XOnFS[index])?"OK":"NOK");
            prntVecotWitOpt("-1 ",obj->m_trnData[index],numDim,1);
            printf(" %.2f %.2f,on K(%.2f %.2f) angle (A,B) :(%.2f,%.2f)\n",obj->m_distanceA2X[index],obj->m_distanceB2X[index],obj->m_distA2XOnFS[index],obj->m_distB2XOnFS[index],cos2Degree(obj->m_cosVAgaistAMean[index]),cos2Degree(obj->m_cosVAgaistBMean[index]));
        }
        printf("===== Violation data in input space \n");
        printf("nACls not Ok is:                  %d\n",obj->m_nDistNokOfACls);
        printf("nACls not ok behide mean BCls is: %d\n",obj->m_nDistBehideMeanNokOfACls);
        iTmp = obj->m_nDistNokOfACls+obj->m_nDistBehideMeanNokOfACls;
        dTmp = ((double)iTmp)*100.0/((double)obj->m_nTrnClsA);
        printf("Sum Not Ok of Cls A             : %d , numACls:%d (%.2f%c)\n",iTmp,obj->m_nTrnClsA,dTmp,'%');
        printf("nBCls not Ok is:                  %d\n",obj->m_nDistNokOfBCls);
        printf("nBCls not ok behide mean ACls is: %d\n",obj->m_nDistBehideMeanNokOfBCls);
        iTmp = obj->m_nDistNokOfBCls+obj->m_nDistBehideMeanNokOfBCls;
        dTmp = ((double)iTmp)*100.0/((double)obj->m_nTrnClsA);
        printf("Sum Not Ok of Cls B             : %d , numACls:%d (%.2f%c)\n",iTmp,obj->m_nTrnClsB,dTmp,'%');
        
        printf("===== Violation data in Feature space \n");
        printf("nACls not Ok is:                  %d\n",obj->m_nDistNokOfAClsOnFs);
        printf("nACls not ok behide mean BCls is: %d\n",obj->m_nDistBehideMeanNokOfAClsOnFs);
        iTmp = obj->m_nDistNokOfAClsOnFs+obj->m_nDistBehideMeanNokOfAClsOnFs;
        dTmp = ((double)iTmp)*100.0/((double)obj->m_nTrnClsA);
        printf("Sum Not Ok of Cls A             : %d , numACls:%d (%.2f%c)\n",iTmp,obj->m_nTrnClsA,dTmp,'%');
        printf("nBCls not Ok is:                  %d\n",obj->m_nDistNokOfBClsOnFs);
        printf("nBCls not ok behide mean ACls is: %d\n",obj->m_nDistBehideMeanNokOfBClsOnFs);
        iTmp = obj->m_nDistNokOfBClsOnFs+obj->m_nDistBehideMeanNokOfBClsOnFs;
        dTmp = ((double)iTmp)*100.0/((double)obj->m_nTrnClsA);
        printf("Sum Not Ok of Cls B             : %d , numACls:%d (%.2f%c)\n",iTmp,obj->m_nTrnClsB,dTmp,'%');
        
        printf("===== Data are defined their alpha = 0.0 \n");
        
        dTmp = ((double)obj->m_nDatBehideMeanA)*100.0/((double)obj->m_nTrnClsA);
        printf("nACls behide mean is %d , numBCls:%d (%.2f%c)\n",obj->m_nDatBehideMeanA,obj->m_nTrnClsA,dTmp,'%');
        dTmp = ((double)obj->m_nDatBehideMeanB)*100.0/((double)obj->m_nTrnClsB);
        printf("nBCls behide mean is %d , numBCls:%d (%.2f%c)\n",obj->m_nDatBehideMeanB,obj->m_nTrnClsB,dTmp,'%');
    }
    else
    {
        printf("Error vector obj is Null, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}

/*  kernelFn method */
void constructorKFn(struct kernelFn *obj,int type,int numDim,double polyFactor,double guassianVal,double gainSigmoid)
{
    int ret = 1;
    int isShowDebug = 0;
    if ( (obj != NULL) && (numDim > 0) && (type > 0) && (type <4))
    {
        obj->m_type = type;
        obj->m_nDimen = numDim;
        obj->m_buff = newDoubleArea(numDim,&ret);
        obj->m_polyFactor = polyFactor;
        obj->m_gaussianVal = guassianVal;
        obj->m_gainSigmoid = gainSigmoid;
        obj->m_polyFactor = doubleBoundCheck(10000.0,0.0000000001,obj->m_polyFactor,1,isShowDebug);
        obj->m_gaussianVal = doubleBoundCheck(10000000.0,0.0,obj->m_gaussianVal,500.0,isShowDebug);
        obj->m_gainSigmoid = doubleBoundCheck(10000000.0,-10000000.0,obj->m_gainSigmoid,1.0,isShowDebug);
        obj->m_guassianDivider = (-2.0)*pow(obj->m_gaussianVal,2);
        obj->m_gainBuff = (-1.0)*obj->m_gainSigmoid;
        
        assignKFntoKFnObj( obj);
        if (obj->m_buff != NULL)
        {
            initialDoubleArea(obj->m_buff,0.0,numDim);
        }
        else
        {
            printf("Cannot allocate the m_buff in constructorKFn, ln:%d, file:%s\n",__LINE__,__FILE__);
            obj->calKernelVal = NULL;
        }
    }
    else
    {
        printf("Error in constructorKFn, obj is failed to create, numDimL%d, type:%d ln:%d, file:%s\n",numDim,type,__LINE__,__FILE__);
    }
}
void constructorKFn2(struct kernelFn *obj,void *xmlConfig)
{
    int ret = 1;
     treeXML *tXML = (treeXML*)xmlConfig;
     int numDim = 0.0;
     double gaussianVal = 0.0;
     double powFactor = 0.0;
     double gainSigmoid = 0.0;
     int kernelFnType = 0;
    if ((obj != NULL) && (tXML != NULL))
    {
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML->root,DEF_KERNEL_FN,"2",&kernelFnType,0x010); 
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML->root,DEF_POW_FACTOR,"5.0",&powFactor,0x050); 
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML->root,DEF_GAUSSIAN_VAL,"500.0",&gaussianVal,0x050);
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML->root,DEF_NUM_DIMENSION,"3",&numDim,0x010);
        ret = ( ret == 1) && getValueOfFirstChildEle2Var(tXML->root,DEF_SIGMOID_GAIN_VAL,"1",&gainSigmoid,0x050);
        constructorKFn(obj,kernelFnType,numDim,powFactor,gaussianVal,gainSigmoid);
    }
    else
    {
        ret = 0;
        printf("Error in constructorKFn2, obj is failed to create, numDimL%d, kernelFnType:%d, tXML:%p ln:%d, file:%s\n",numDim,kernelFnType,tXML,__LINE__,__FILE__);
    }
    if (ret == 1)
    {
    }
    else
    {
        printf("Error in constructorKFn2, obj is failed to create, numDimL%d, kernelFnType:%d tXML:%p ln:%d, file:%s\n",numDim,kernelFnType,tXML,__LINE__,__FILE__);
    }
}


void destructorKFn(struct kernelFn *obj)
{
    if (obj != NULL)
    {
        obj->m_type = 0;
        obj->m_nDimen = 0;
        obj->calKernelVal = NULL;
        obj->m_polyFactor = 0;
        obj->m_gaussianVal = 1;
        obj->m_guassianDivider = 1;
        obj->m_gainSigmoid = 1;
        obj->m_gainBuff = -1;
        if (obj->m_buff != NULL)
        {
            delDoubleArea((void*)&(obj->m_buff));
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Error in destructorKFn, obj is Null, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}

const char* printKernelType(int type)
{
    char *ch = NULL;
    switch(type)
    {
        case 0:
            ch = "linear";
        break;
        case 1:
            ch = "Poly nomial";
        break;
        case 2:
            ch = "Radius Gaussian";
        break;
        case 3:
            ch = "Sigmoid";
        break;
    }
    return ch;
}

void printKFn(struct kernelFn *obj)
{
    if (obj != NULL)
    {
        printf("Kernel type : %s (%d)\n",printKernelType(obj->m_type),obj->m_type);
        printf("Poly val    : %0.2f\n",obj->m_polyFactor);
        printf("Guassian val: %0.2f\n",obj->m_gaussianVal);
        printf("Sigmoid  val: %0.2f\n",obj->m_gainSigmoid);
        printf("SigBuff     : %0.2f\n",obj->m_gainBuff);
        printf("GuassianBuff: %0.2f\n",obj->m_guassianDivider);
        printf("------------------------\n");
    }
    else
    {
        printf("Error in printKFn obj is NULL, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}
void assignKFntoKFnObj(struct kernelFn *obj)
{
    if (obj != NULL)
    {
        switch(obj->m_type)
        {
            case 0: /* 0 -- linear */
                obj->calKernelVal = &linearKFn;
            break;
            
            case 1: /* 1 -- Polynomial */
                obj->calKernelVal = &PolyKFn;
            break;
            
            case 2: /* 2 -- Guassian radius */
                obj->calKernelVal = &RadiusKFn;
            break;
            
            case 3: /* 3 -- sigmoid */
                obj->calKernelVal = &sigmoidKFn;
            break;
            
        }
    }
    else
    {
        printf("Error in assignKFntoKFnObj, obj is Null, ln:%d, file:%s\n",__LINE__,__FILE__);
    }
}

double linearKFn(struct kernelFn *obj,const double *va,const double *vb)
{
    double tmp = 0.0;
    int index = 0;
    int numDim = 0;
    if ((va != NULL) && (obj != NULL) && (vb != NULL))
    {
        numDim = obj->m_nDimen;
        for (index = 0;index < numDim ;index++)
        {
            tmp = va[index]*vb[index] + tmp;
        }
        
    }
    else
    {
        printf("Error in linearKFn, obj is %p, va:%p, vb:%p ln:%d, file:%s\n",obj,va,vb,__LINE__,__FILE__);
    }
    return tmp;
}
double RadiusKFn(struct kernelFn *obj,const double *va,const double *vb)
{
    double ret = 0.0;
    int numDim = 0;
    if (obj !=NULL)
    {
        numDim = obj->m_nDimen;
        minusVectorDoub(va,vb,obj->m_buff,numDim);
        ret = linearKFn(obj,obj->m_buff,obj->m_buff);
        if (obj->m_guassianDivider != 0)
        {
            ret = exp(ret/obj->m_guassianDivider);
        }
        else
        {
            ret = 1.0;
            printf("Error in RadiusKFn, the divider is 0, ln:%d, file:%s\n",__LINE__,__FILE__);
        }
    }
    else
    {
        printf("Error in RadiusKFn, obj is %p, va:%p, vb:%p ln:%d, file:%s\n",obj,va,vb,__LINE__,__FILE__);
    }
    return ret;
}

double PolyKFn(struct kernelFn *obj,const double *va,const double *vb)
{
    double ret = 0.0;
    if (obj !=NULL)
    {
        ret = pow(linearKFn(obj,va,vb)+1.0,obj->m_polyFactor);
    }
    else
    {
        printf("Error in PolyKFn, obj is %p, va:%p, vb:%p ln:%d, file:%s\n",obj,va,vb,__LINE__,__FILE__);
    }
    
    return ret;
}
double sigmoidKFn(struct kernelFn *obj,const double *va,const double *vb)
{
    double ret = 0.0;
    
    if (obj != NULL)
    {
        ret = 1.0/(1.0 + exp((obj->m_gainBuff)*linearKFn(obj,va,vb)));
    }
    else
    {
        printf("Error in sigmoidKFn, obj is %p, va:%p, vb:%p ln:%d, file:%s\n",obj,va,vb,__LINE__,__FILE__);
    }
    
    return ret;
}