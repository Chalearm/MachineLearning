#ifndef _DATGEN_H
#define _DATGEN_H
#include <stdlib.h>  /* srand, rand */
#include <time.h>     /* time */
#define NAME_FILE_SIZE 80
#include "simReadXML.h"
#include "simMatInt.h"


/////////////////// Utility method and data structure /////////////////
class Valueequilizer
{
    int m_fraction;
    int m_eachMembeNumber;
    // internel used
    int m_countFraction;
public:
    Valueequilizer();
    void initial(int numAll,int divider);
    int numEachCls();
};
double randomizedFn(double max,double min);
void divideValue2EachMember(int number,int divider,int *numEach,int *fraction);

/////////////////// End of Utility method and data structure /////////////////
class attrbDetail;
class classDetail;
class datGen
{
private:
    char m_filename[NAME_FILE_SIZE];
    double m_maxOfAll;
    double m_minOfAll;
    char m_typeDefault; //0 is continue , 1 is discrete
    int m_numClass;
    int m_numAttrb;
    int m_sample;
    
    int m_numRed;       //The number of redundant sample
    int m_numConflic;   //The number of conflict sample
    int m_numInComp;   //The number of incomplete sample
    
    classDetail *m_classes;

    void readConfiguration(elementXML *rootXML);
    void sumNumSamFromClassDetail(void *eleList,const char *tagName,int *pnumCls,int *pnumSam);
    void initialValueequilizerWithEle(void *eleList,const char *tagName,int *numSam,Valueequilizer *obj);
public:
    datGen(const char *xmlfile); 
    datGen(const datGen& rhs);
    datGen& operator=(datGen& rhs);
    ~datGen();
    void startGenDat();
    
    void printGenAttrb();
    
};

class classDetail
{
    char m_isSet;
    int m_numSam;
    int m_numMiss;
    int m_numRedun;
    int m_numAttrb;
    attrbDetail *m_attrb;
    
    void newAttrbArea(int num);
public:
    classDetail(int numSam=0,int numRedun=0,int numMiss=0,int numAttrb=0,double max=0.0,double min=0.0);
    classDetail(const classDetail& rhs);
    classDetail& operator=(classDetail& rhs);
    ~classDetail();
    void setAllAttrb(Valueequilizer *numSam,Valueequilizer *numMiss,Valueequilizer *numRed,int numAttrb,double max,double min,char type,elementXML *rootXML);
    int isSetData();
    void startGenData();
};
class attrbDetail
{
    char m_isSet;
    double m_missRate;
    double m_max;
    double m_min;
    double m_median;
    double m_modeVal;
    double m_mean;
    double m_sum;
    char m_type;//0 is continue , 1 is discrete
    int m_numResult;
    int m_numPerfectSam;
    double *m_result;
     
    void swapPosition();
    void dividedArr(int st,int numSam,int numDiv,vector_int *vect);
    void fillMode2Arr(vector_int  *vArr,int index,int index2,int percentile);
    void fillMedian();
    void check2SetDefault(double *val,double defaultVal);
    void setAllDataDiscrete();
    void setResultSpace(int num);
    void copyResultSpace(double *rhs,int size);
    void setValueInLoop(int startP,int endP,double max,double min);
public: 
    attrbDetail(int numSam=0,double max=0,double min=0,double missRate=0,char type=0); //0 is continue , 1 is discrete
    attrbDetail(const attrbDetail& rhs);
    attrbDetail& operator=(attrbDetail& rhs);
    ~attrbDetail(); 
    void setAttrb(int numEle,char type,double max,double min,void *ele);
    int isSetData();
    void print();
    void startGenAttrbVal(int numRed);
};

#endif //_DATGEN_H