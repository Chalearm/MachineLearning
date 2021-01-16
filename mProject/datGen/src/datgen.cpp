#include <cstring>
#include <iostream>
#include "datgen.h"
#include "eleXMLNodeList.h"
using namespace std;
///////////////////////////////////////////////////
////////////// CONSTANT DEFINE/////////////////////
///////////////////////////////////////////////////
#define DIVIDED_PART 17
#define ARR_SIZE_DIVIDED_PART DIVIDED_PART+1
#define MODE_PERCENT 8
#define BOUND_MEDIAN_PERCENT 4
#define SWAP_POSITION_PERCENT 45
/////////////////////////////////////////////////
// XML TAG DEFINE //////////////////////////////
////////////////////////////////////////////////
#define FILE_NAME_XML       "FILE_NAME"
#define NUM_CLASS_XML       "NUM_CLASS"
#define NUM_ATTRB_XML       "NUM_ATTRB"  //only input , and output is 1 
#define MAX_GOBAL_XML       "MAX_GOBAL"
#define MIN_GOBAL_XML       "MIN_GOBAL"
#define NUM_REDUN_XML       "NUM_REDUN"
#define NUM_CONFLIC_XML     "NUM_CONFLIC"
#define NUM_SAMPLE_XML      "NUM_SAMPLE"
#define NUM_INCOMPLETE_XML  "NUM_INCOMPLETE"
#define DEFAULT_TYPE_XML    "DEFAULT_TYPE"
#define ATTRB_DETAIL_XML    "ATTRB_DETAIL" 
#define ORDER_ATTRB_XML     "order" 
#define MISS_RATE_XML       "MISS_RATE" //probability to missing value(?) when randomization works 1% - 100%
#define MAX_XML             "MAX"    
#define MIN_XML             "MIN"    
#define TYPE_XML            "TYPE"

#define CLASS_DETAIL_XML        "CLASS_DETAIL"
#define REDUN_SAMPLE_XML        "REDUN_SAMPLE"
#define MISS_SAMPLE_XML         "MISS_SAMPLE" 
#define MEDIAN_VALUE_XML        "MEDIAN_VALUE" 
#define MODE_VALUE_XML          "MODE_VALUE"
#define ATTRB_NO_XML            "no"
datGen::datGen(const char *xmlfile)
{
    m_classes =NULL;
    m_numClass =0;
/*
int getValueOfFirstChildEle2Var(elementXML *root,const char *str,const char *defaultStr,void *var,unsigned int typeVar);
int getAttrbValueOfFirstChildEle2Var(elementXML *root,const char *tagName,const char* attrb,const char* defaultVal,void *var,unsigned int typeVar);
*/
    int ret=0;
    treeXML tXML;
    elementXML *rootXML=NULL;
    ret = getSourceToTreeXML(&tXML,xmlfile);
    
    if(ret ==1)
    {
        rootXML  = getRootElementXML(&tXML);
        readConfiguration(rootXML);

    }
    else
    {
        cout<<"Not ok cannot read file \n";
    }

    destructorTreeXML(&tXML);
}
datGen::~datGen()
{
    m_numClass =0;
    if(m_classes !=NULL)
    {
        delete[] m_classes;
        m_classes =NULL;
    }
    else
    {
        // Do nothing
    }
}
void datGen::readConfiguration(elementXML *rootXML)
{ 
    int index = 0;
    int ret =0;
    int tempInt=0;
    simString tempStr;
    int no =-1;
    Valueequilizer nEachCls;
    Valueequilizer nMisEachCls;
    Valueequilizer nRedunEachCls;
    initialSimString(&tempStr);
    listElement listEle;
    elementXML tempEle; 
    ret = getValueOfFirstChildEle2Var(rootXML,FILE_NAME_XML,"",(void*)&tempStr,0x080);
    if(ret==1)
    {
        memcpy(m_filename,tempStr.data,tempStr.length);
        m_filename[tempStr.length] ='\0';
        destructSimString(&tempStr);
        initialSimString(&tempStr);
    }
    else
    {
        // Do nothing
    }
    ret += getSourceToXMLList(&listEle,rootXML,CLASS_DETAIL_XML);
    ret += getValueOfFirstChildEle2Var(rootXML,NUM_CLASS_XML,"2",(void*)&m_numClass,0x010);
    ret += getValueOfFirstChildEle2Var(rootXML,NUM_ATTRB_XML,"1",(void*)&m_numAttrb,0x010);
    ret += getValueOfFirstChildEle2Var(rootXML,MAX_GOBAL_XML,"1",(void*)&m_maxOfAll,0x050);
    ret += getValueOfFirstChildEle2Var(rootXML,DEFAULT_TYPE_XML,"",(void*)&tempStr,0x080);
    ret += getValueOfFirstChildEle2Var(rootXML,MIN_GOBAL_XML,"1",(void*)&m_minOfAll,0x050);
    ret += getValueOfFirstChildEle2Var(rootXML,NUM_REDUN_XML,"0",(void*)&m_numRed,0x010);
    ret += getValueOfFirstChildEle2Var(rootXML,NUM_SAMPLE_XML,"0",(void*)&m_sample,0x010);
    ret += getValueOfFirstChildEle2Var(rootXML,NUM_INCOMPLETE_XML,"0",(void*)&m_numInComp,0x010);
    ret += getValueOfFirstChildEle2Var(rootXML,NUM_CONFLIC_XML,"0",(void*)&m_numConflic,0x010);
    cout<<"valid result :"<<ret<<endl;
    if(compareSimStrWithCstr(&tempStr,"continue")==1)
    {
        m_typeDefault = 0;
    }
    else if(compareSimStrWithCstr(&tempStr,"discrete")==1)
    {
        m_typeDefault = 1;
    }
    else
    {
        // Do nothing
    }
    if(m_numClass != 0)
    {
        m_classes = new classDetail[m_numClass]; 
        tempInt = m_sample-m_numConflic;
        initialValueequilizerWithEle((void*)&listEle,MISS_SAMPLE_XML,&m_numInComp,&nMisEachCls);
        initialValueequilizerWithEle((void*)&listEle,NUM_SAMPLE_XML,&tempInt,&nEachCls); 
        initialValueequilizerWithEle((void*)&listEle,REDUN_SAMPLE_XML,&m_numRed,&nRedunEachCls); 
        
        for(index=0;index<m_numClass;index++)
        {  
            tempEle.firstChild = getXMLElement(&listEle,index);
            if(tempEle.firstChild!=NULL)
            {
                getAttrbValueOfFirstChildEle2Var(&tempEle,CLASS_DETAIL_XML,ATTRB_NO_XML,"-1",(void*)&no,0x010);
            }
            else
            {
                // Do nothing 
            } 
            if(no ==-1)
            {
                // Do nothing
            }
            else if(m_classes[no].isSetData() ==0)
            { 
                m_classes[index].setAllAttrb(&nEachCls,
                                             &nMisEachCls,
                                             &nRedunEachCls,
                                             m_numAttrb,
                                             m_maxOfAll,
                                             m_minOfAll,
                                             m_typeDefault,tempEle.firstChild);
                no =-1;
            }
            else
            {
                // Do nothing
            }
            
            if(m_classes[index].isSetData() ==0)
            {
                m_classes[index].setAllAttrb(&nEachCls,
                                             &nMisEachCls,
                                             &nRedunEachCls,
                                             m_numAttrb,
                                             m_maxOfAll,
                                             m_minOfAll,
                                             m_typeDefault,NULL);
            }
            else
            {
                // Do nothing 
            }
            tempEle.firstChild = NULL;
        }
    }
    else
    {
        // Do nothing
    }
    makeNodeXMLEleEmpty(&listEle);
    destructSimString(&tempStr);
}
void datGen::sumNumSamFromClassDetail(void *eleList,const char *tagName,int *pnumCls,int *pnumSam)
{
    int ret = (eleList!=NULL)&&(pnumCls!=NULL)&&(pnumSam!=NULL);
    int index =0;
    int numS=0;
    int count =0;
    elementXML *tempEle=NULL;
    listElement *plistEle = NULL;
    if(ret ==1)
    {
        *pnumSam =0;
        plistEle = (listElement*)eleList;
        count = getNumOfXMLNode(plistEle);
        *pnumCls = count;
        for(index=0;index<count;index++)
        {
            tempEle = getXMLElement(plistEle,index); 
            getValueOfFirstChildEle2Var(tempEle,tagName,"-1",(void*)&numS,0x010);
            if(numS ==0)
            {
                *pnumCls -= 1;
            }
            else if(numS!=-1)
            {
                *pnumSam += numS;
            }
            else
            {
                *pnumCls -= 1;
            }
        }
        
    }
    else
    {
        // Do nothing
    }
}
void datGen::initialValueequilizerWithEle(void *eleList,const char *tagName,int *numSam,Valueequilizer *obj)
{
    int numClsInCfg =0;
    int numSamInClsCfg=0;
    sumNumSamFromClassDetail(eleList,tagName,&numClsInCfg,&numSamInClsCfg);
    //cout<<"num "<<tagName<<" :"<<numClsInCfg<<" numS cls:"<<numSamInClsCfg<<endl;
    if(numSamInClsCfg >*numSam)
    {
        obj->initial(*numSam,m_numClass);
    }
    else
    {
        obj->initial(*numSam-numSamInClsCfg,m_numClass-numClsInCfg);
    }
}
datGen::datGen(const datGen& rhs)
{
    memcpy(m_filename,rhs.m_filename,NAME_FILE_SIZE);
    m_maxOfAll = rhs.m_maxOfAll;
    m_minOfAll = rhs.m_minOfAll;
    m_typeDefault = rhs.m_typeDefault; //0 is continue , 1 is discrete
    m_numClass = rhs.m_numClass;
    m_numAttrb = rhs.m_numAttrb;
    m_sample   = rhs.m_sample;
    m_numRed = rhs.m_numRed;       //The number of redundant sample
    m_numConflic = rhs.m_numConflic;   //The number of conflict sample
    m_numInComp = rhs.m_numInComp; 
}
datGen& datGen::operator=(datGen& rhs)
{
    if(this != &rhs)
    {
        memcpy(m_filename,rhs.m_filename,NAME_FILE_SIZE);
        m_maxOfAll = rhs.m_maxOfAll;
        m_minOfAll = rhs.m_minOfAll;
        m_typeDefault = rhs.m_typeDefault; //0 is continue , 1 is discrete
        m_numClass = rhs.m_numClass;
        m_numAttrb = rhs.m_numAttrb;
        m_sample   = rhs.m_sample;
        m_numRed = rhs.m_numRed;       //The number of redundant sample
        m_numConflic = rhs.m_numConflic;   //The number of conflict sample
        m_numInComp = rhs.m_numInComp; 
    }
    else
    {
        // Do nothing 
    }
    return *this;
}
void datGen::startGenDat()
{
    int index=0;
    for(index=0;index<m_numClass;index++)
    {
        m_classes[index].startGenData();
    }
    cout<<"start Generate data set\n";
}
void datGen::printGenAttrb()
{
    cout<<"Filename : "<<m_filename<<".dat"<<endl;
    cout<<"G (max,min) value : "<<"("<<m_maxOfAll<<","<<m_minOfAll<<")"<<endl; 
    if(m_typeDefault==0)
    {
        cout<<"G type : "<<"continue"<<endl;
    }
    else if(m_typeDefault==1)
    {
        cout<<"G type : "<<"discrete"<<endl;
    }
    cout<<"the number of classes    :"<<m_numClass<<endl;
    cout<<"the number of attributes :"<<m_numAttrb<<endl;
    cout<<"the number of samples    :"<<m_sample<<endl;
    cout<<"the number of redundancy :"<<m_numRed<<endl;
    cout<<"the number of conflict   :"<<m_numConflic<<endl;
    cout<<"the number of incomplete :"<<m_numInComp<<endl;
    
}

double randomizedFn(double max,double min)
{
    return ((max-min)*((double)rand()/RAND_MAX))+min;
}
classDetail::classDetail(int numSam,int numRedun,int numMiss,int numAttrb,double max,double min):
m_isSet(0),
m_numSam(numSam),
m_numMiss(numMiss),
m_numRedun(numRedun),
m_numAttrb(numAttrb),
m_attrb(NULL)
{}
classDetail::classDetail(const classDetail& rhs)
{
    int index=0;
    m_attrb = NULL;
    m_isSet   = rhs.m_isSet;
    m_numSam  = rhs.m_numSam;
    m_numMiss  = rhs.m_numMiss;
    m_numRedun  = rhs.m_numRedun;
    m_numAttrb  = rhs.m_numAttrb;
    newAttrbArea(m_numAttrb);
    if(m_attrb !=NULL)
    { 
        for(index=0;index<m_numAttrb;index++)
        {
            m_attrb[index] = rhs.m_attrb[index];
        } 
    }
    else
    {
        // Do nothing 
    }
}
classDetail& classDetail::operator=(classDetail& rhs)
{
    int index=0;
    if(this != &rhs)
    {
        m_isSet   = rhs.m_isSet;
        m_numSam  = rhs.m_numSam;
        m_numMiss  = rhs.m_numMiss;
        m_numRedun  = rhs.m_numRedun;
        m_numAttrb  = rhs.m_numAttrb;
        newAttrbArea(m_numAttrb);
        if(m_attrb !=NULL)
        { 
            for(index=0;index<m_numAttrb;index++)
            {
                m_attrb[index] = rhs.m_attrb[index];
            } 
        }
        else
        {
            // Do nothing 
        }
    }
    else
    {
        // Do nothing
    }
    return *this;
}
int classDetail::isSetData()
{
    return m_isSet;
}
void classDetail::startGenData()
{
    int index =0;
    //cout<<"class called\n";
    for(index=0;index<m_numAttrb;index++)
    {
     cout<<"========== 1111 \n";
        m_attrb[index].startGenAttrbVal(m_numRedun);
       cout<<"========== 2222 \n";
    }
}
classDetail::~classDetail()
{
    if(m_attrb != NULL)
    {
        delete[] m_attrb;
        m_attrb= NULL;
    }
    else
    {
        // Do nothing
    }
    m_numAttrb = 0;
}

void classDetail::newAttrbArea(int num)
{
    if(num ==0)
    {
        if(m_attrb !=NULL)
        {
            delete[] m_attrb;
            m_attrb =NULL;
            m_numAttrb =0;
        }
        else
        {
            // Do nothing
        }
    }
    else if(num >0)
    {
        if(m_attrb !=NULL)
        {
            delete[] m_attrb;
            m_attrb =NULL;
            m_numAttrb=0;
        }
        else
        {
            // Do nothing
        }
        m_attrb = new attrbDetail[num];
        if(m_attrb!=NULL)
        {
            m_numAttrb = num;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        // Do nothing 
    }
}
void classDetail::setAllAttrb(Valueequilizer *numSam,Valueequilizer *numMiss,Valueequilizer *numRed,int numAttrb,double max,double min,char type,elementXML *rootXML)
{
    int ret =0;
    int index=0;
    m_numAttrb =numAttrb;
    listElement listEle;
    elementXML tempEle;
    int order =0;
    if(rootXML ==NULL)
    {
        m_numSam =numSam->numEachCls();
        m_numMiss =numMiss->numEachCls();
        m_numRedun =numRed->numEachCls();
        newAttrbArea(numAttrb);
        if(m_attrb!=NULL)
        {
            // Default set
            for(index=0;index<m_numAttrb;index++)
            {
                m_attrb[index].setAttrb(m_numSam,type,max,min,NULL);
            }
        }
        else
        {
            m_numAttrb =0;
        }
    }
    else
    {
        //printEleXML(rootXML);
        ret += getValueOfFirstChildEle2Var(rootXML,NUM_SAMPLE_XML,"-1",(void*)&m_numSam,0x010);
        ret += getValueOfFirstChildEle2Var(rootXML,REDUN_SAMPLE_XML,"-1",(void*)&m_numRedun,0x010);
        ret += getValueOfFirstChildEle2Var(rootXML,MISS_SAMPLE_XML,"-1",(void*)&m_numMiss,0x010);
        m_isSet=(ret ==3);
        ret += getSourceToXMLList(&listEle,rootXML,ATTRB_DETAIL_XML);
        if(m_numSam ==-1)
        {
            m_numSam =numSam->numEachCls();
        }
        else
        {
            // Do nothing 
        }
        if(m_numRedun ==-1)
        {
            m_numRedun =numRed->numEachCls();
        }
        else
        {
            // Do nothing 
        }
        if(m_numMiss ==-1)
        {
            m_numMiss =numMiss->numEachCls();
        }
        else
        {
            // Do nothing
        }
        newAttrbArea(numAttrb);
        if(m_attrb!=NULL)
        {
            // Default set
            for(index=0;index<m_numAttrb;index++)
            {
                tempEle.firstChild = getXMLElement(&listEle,index);
                if(tempEle.firstChild!=NULL)
                {
                    getAttrbValueOfFirstChildEle2Var(&tempEle,ATTRB_DETAIL_XML,ORDER_ATTRB_XML,"-1",(void*)&order,0x010);
                }
                else
                {
                    // Do nothing
                }
                if(order ==-1)
                {
                    // Do nothing
                }
                else if(order <m_numAttrb)
                {
                    m_attrb[order].setAttrb(m_numSam,type,max,min,tempEle.firstChild);
                    order =-1;
                }
                else
                {
                    // Do nothing
                }
                if(m_attrb[index].isSetData()==0)
                {
                    m_attrb[index].setAttrb(m_numSam,type,max,min,NULL);
                }
                else
                {
                    // Do nothing
                }
                tempEle.firstChild =NULL;
            }
        }
        else
        {
            m_numAttrb =0;
        }
        makeNodeXMLEleEmpty(&listEle);
    }
    /*
    cout<<"Sam:"<<m_numSam<<" nMiss:"<<m_numMiss<<" nRed:"<<m_numRedun<<" max:"<<max<<" min:"<<min<<" nAttrb:"<<m_numAttrb;
    cout<<endl;*/
}
attrbDetail::attrbDetail(int numSam,double max,double min,double missRate,char type):
m_isSet(0),
m_missRate(missRate),
m_max(max),
m_min(min),
m_median((max+min)/2),
m_modeVal((max+min)/2),
m_mean(0.0),
m_sum(0.0),
m_type(type),
m_numResult(numSam),
m_numPerfectSam(0),
m_result(NULL)
{
    setResultSpace(numSam);
}

attrbDetail::attrbDetail(const attrbDetail& rhs)
{
    m_result =NULL;
    m_isSet = rhs.m_isSet;
    m_missRate  =rhs.m_missRate;
    m_max  =rhs.m_max;
    m_min  =rhs.m_min;
    m_median  =rhs.m_median;
    m_modeVal  =rhs.m_modeVal;
    m_type  =rhs.m_type;
    m_mean  = rhs.m_mean;
    m_sum   = rhs.m_sum;
    m_numPerfectSam = rhs.m_numPerfectSam;
    setResultSpace(rhs.m_numResult);
    copyResultSpace(rhs.m_result,rhs.m_numResult);
}

attrbDetail& attrbDetail::operator=(attrbDetail& rhs)
{
    if(this != &rhs)
    {
        m_isSet = rhs.m_isSet;
        m_missRate  =rhs.m_missRate;
        m_max  =rhs.m_max;
        m_min  =rhs.m_min;
        m_median  =rhs.m_median;
        m_modeVal  =rhs.m_modeVal;
        m_type  =rhs.m_type;
        m_mean  = rhs.m_mean;
        m_sum   = rhs.m_sum;
        m_numPerfectSam = rhs.m_numPerfectSam;
        setResultSpace(rhs.m_numResult);
        copyResultSpace(rhs.m_result,rhs.m_numResult);
    }
    else
    {
        // Do nothing
    }
    return *this;
}
attrbDetail::~attrbDetail()
{
    setResultSpace(0);
}
void attrbDetail::setAttrb(int numEle,char type,double max,double min,void *ele)
{ 
    simString tempStr;
    initialSimString(&tempStr);
    elementXML *eletemp = NULL;
    char buff[20];
    int ret = (max>=min)&&((type==0)||(type==1))&&(numEle>0);
    if((ret ==1)&&(ele!=NULL))
    {
        eletemp = (elementXML*)ele;
        ret =0;
      //  printEleXML(eletemp);
        ret += getValueOfFirstChildEle2Var(eletemp,MISS_RATE_XML,"-1.0",(void*)&m_missRate,0x050);
        sprintf(buff,"%f",max);
        ret += getValueOfFirstChildEle2Var(eletemp,MAX_XML,buff,(void*)&m_max,0x050);
        sprintf(buff,"%f",min);
        ret += getValueOfFirstChildEle2Var(eletemp,MIN_XML,buff,(void*)&m_min,0x050);
        ret += getValueOfFirstChildEle2Var(eletemp,TYPE_XML,"0",(void*)&tempStr,0x080);
        m_isSet = (ret ==4);
        sprintf(buff,"%f",max+min);
        ret += getValueOfFirstChildEle2Var(eletemp,MEDIAN_VALUE_XML,buff,(void*)&m_median,0x050);
        ret += getValueOfFirstChildEle2Var(eletemp,MODE_VALUE_XML,buff,(void*)&m_modeVal,0x050);
        if(compareSimStrWithCstr(&tempStr,"continue")==1)
        {
            m_type = 0;
        }
        else if(compareSimStrWithCstr(&tempStr,"discrete")==1)
        {
            m_type = 1;
        }
        else
        {
            m_type = type;
        }
        check2SetDefault(&m_missRate,randomizedFn(100.0,0.0));
        setResultSpace(numEle);
    }
    else if(ret==1)
    {
        m_max = max;
        m_min =min;
        m_type = type; 
        m_median = randomizedFn(max,min);
        m_modeVal = randomizedFn(max,min);
        m_missRate = randomizedFn(100.0,0.0);
        setAllDataDiscrete();
        setResultSpace(numEle);
        //cout<<"No element :"<<max<<" "<<min<<" "<<(int)type<<" "<<numEle<<" "<<m_median<<" "<<m_modeVal<<" "<<m_missRate<<endl;
    }
    else
    {
        // Do nothing
    }
    //print();
    destructSimString(&tempStr);
}
void attrbDetail::check2SetDefault(double *val,double defaultVal)
{
    if(val ==NULL)
    {
        // Do nothing
    }
    else if(*val <0)
    {
        *val = defaultVal;
    }
    else
    {
        // Do nothing
    }
}
void attrbDetail::setAllDataDiscrete()
{
    int index=0;
    if(m_type ==1)//0 is continue , 1 is discrete
    {
        m_max = (int)m_max;
        m_min = (int)m_min;
        m_median = (int)m_median;
        m_modeVal = (int)m_modeVal;
        m_mean    = (int)m_mean;
        for(index=0;index<m_numResult;index++)
        {
            m_result[index] = (int)m_result[index];
        }
    }
    else
    {
        // Do nothing
    }
}
void attrbDetail::setResultSpace(int num)
{
    if((num >=0)&&(m_result!=NULL))
    {
        delete[] m_result;
        m_result = NULL;
        m_numResult =0;
    }
    else
    {
        // Do nothing
    }
    if((num>0)&&(m_result==NULL))
    {
        m_result = new double[num];
        if(m_result !=NULL)
        {
            m_numResult = num;
        }
        else
        {
            // Do nothing
        }
    }
    else
    {
        // Do nothing
    }
}
int attrbDetail::isSetData()
{
    return m_isSet;
}
void attrbDetail::print()
{
    if(m_isSet == 1)
    {
        cout<<"Arb(s) ";
    }
    else
    {
        cout<<"Arb(ns) ";
    }
    cout<<"MisRat("<<m_missRate<<"),mx("<<m_max<<"),mn("<<m_min<<"),medi("<<m_median<<"),mod("<<m_modeVal<<"),numSame:("<<m_numResult<<")";
    if(m_type ==0)
    {
        cout<<" typ:cont";
    }
    else if(m_type ==1)
    {
        cout<<" typ:dis";
    }
    else
    {
        cout<<" typ:unkn";
    }
    cout<<endl;
    
}
void attrbDetail::copyResultSpace(double *rhs,int size)
{
    int index=0;
    if((rhs!=NULL)&&(size >=0))
    {
        if(m_numResult == size)
        {
            // Start copy
            for(index=0;index<m_numResult;index++)
            {
                m_result[index] = rhs[index];
            }
        }
        else
        {
            setResultSpace(size); 
            if(m_numResult == size)
            {
                // Start copy
                for(index=0;index<m_numResult;index++)
                {
                    m_result[index] = rhs[index];
                }
            }
            else
            {
                // Do nothing
            }
        }
    }
    else
    {
        // Do nothing
    }
}

void attrbDetail::dividedArr(int st,int numSam,int numDiv,vector_int *vect)
{
    int partSize = numSam/numDiv;
    int fraction = numSam%numDiv;
    int index=0; 
    int endP = st+numDiv;
   // cout<<"st :"<<st<<" numSam:"<<numSam<<" numD:"<<numDiv<<" fc:"<<fraction<<endl;
    for(index=st;index<endP;index++)
    {
        vect->data[index] = vect->data[index-1]+partSize+(fraction>0);
        fraction--;
    } 
}
void attrbDetail::startGenAttrbVal(int numRed)
{ 
    //DIVIDED_PART
    //SWAP_POSITION_PERCENT
    m_sum =0;
    m_numPerfectSam =m_numResult-numRed;
    vector_int vPartIndex = new_vector_int(0);
    int numDividedVal =DIVIDED_PART;
    int indexModeArea1 =-1;
    int indexModeArea2 = -1;
    int halfPart =numDividedVal/2;
    int halfPart2 = DIVIDED_PART-halfPart; 
    int endPart =0;
    double endPart1=halfPart2;
    double endPart2=halfPart;
    int startPart =0;
    int index=0; 
    double maxTemp =0.0;
    double minTemp =0.0;
    double delTemp =0.0;
 
    int st1=0;
    int l1=0;
    int st2=0;
    int l2=m_numPerfectSam;
    char isOddNum =(m_numPerfectSam%2==1);
    vPartIndex = new_vector_int(DIVIDED_PART+2); 
    int numSamHalf=0;
    if(isOddNum==1)
    {
        l1 = m_numPerfectSam/2;
        st2 = l1+1;
        numSamHalf = (m_numPerfectSam-1)/2;
    }
    else 
    {
        l1 = (m_numPerfectSam/2)-1;
        l1 = (l1>0)*l1;
        st2 = l1+2;
        numSamHalf = (m_numPerfectSam-2)/2;
    }
    vPartIndex.data[0]=st1;
    vPartIndex.data[vPartIndex.lenght-1]=l2;
    vPartIndex.data[halfPart2+1]=st2;
 
    dividedArr(1,numSamHalf,halfPart2,&vPartIndex);
    dividedArr(halfPart2+2,numSamHalf,halfPart,&vPartIndex);
   /* endPart = DIVIDED_PART+2;
    
    for(index =0;index<endPart;index++)
    {
        cout<<vPartIndex.data[index]<<" ";
    }*/
    //cout<<"\nep1:"<<endPart1<<" ep2:"<<endPart2<<endl;
  //  cout<<"end1:"<<endPart1<<" end2:"<<endPart2;
 //   cout<<" numdiv :"<<numDividedVal;
 //cout<<" pfsam:"<<m_numPerfectSam<<" halfPart :"<<halfPart<<" medain:"<<m_median<<" mode :"<<m_modeVal<<endl;
    minTemp =m_min;
    delTemp = (m_median-m_min)/endPart1;
    maxTemp = delTemp+minTemp;
  //  cout<<"delT1: "<<delTemp<<" min:"<<m_min<<endl;
    for(index=0;index<endPart1;index++)
    {
        endPart = vPartIndex.data[index+1];
        startPart =vPartIndex.data[index];
   //   cout<<index<<"_st:"<<startPart<<" end:"<<endPart<<" max :"<<maxTemp<<" min:"<<minTemp<<endl;
        // Check mode value zone
      //  cout<<" max:"<<maxTemp<<endl;
        if((m_modeVal>=minTemp)&&(m_modeVal<=maxTemp))
        {
            indexModeArea1 = index;
        }
        else
        {
            // Do nothing 
        } 
        setValueInLoop(startPart,endPart,maxTemp,minTemp);
        minTemp = maxTemp;
        maxTemp +=delTemp;
        //if((maxTemp ==m_median)||(index==(halfPart-1))) cout<<"Max is Median1 :"<<m_median<<" "<<maxTemp<<endl;
    } 
    minTemp = m_median;
    delTemp = (m_max-m_median)/endPart2;
    maxTemp = delTemp+minTemp; 
  //  cout<<"----------------------\n";
   // cout<<"delT2: "<<delTemp<<" min:"<<m_median<<endl;
    endPart2 = numDividedVal+1;
    for(index=endPart1+1;index<endPart2;index++)
    {
        endPart = vPartIndex.data[index+1];
        startPart =vPartIndex.data[index];
       // if(minTemp ==m_median) cout<<"Max is Median2 :"<<m_median<<endl;
      // cout<<index<<"_st:"<<startPart<<" end:"<<endPart<<" max :"<<maxTemp<<" min:"<<minTemp<<endl;

        // Check mode value zone
        if((m_modeVal>=minTemp)&&(m_modeVal<=maxTemp))
        {
            indexModeArea2 = index;
        }
        else
        {
            // Do nothing 
        }
        setValueInLoop(startPart,endPart,maxTemp,minTemp); 
        minTemp = maxTemp;
        maxTemp +=delTemp;
    }
    // fill value for redundancy area
    setValueInLoop(m_numPerfectSam,m_numResult,m_max,m_min);
    // fill mode
    fillMode2Arr(&vPartIndex,indexModeArea1,indexModeArea2,MODE_PERCENT);
    // file median
    fillMedian();
    swapPosition();
    for(index=0;index<m_numPerfectSam;index++)
    {
        m_sum += m_result[index];
    }
    m_mean = m_sum/m_numPerfectSam;
    
   cout<<"attr start \n";
    for(index=0;index<m_numPerfectSam;index++)
    {
        cout<<m_result[index]<<" ";
    }
    cout<<endl<<"numSam:"<<m_numPerfectSam<<" md:"<<m_median<<" mode:"<<m_modeVal<<" mean:"<<m_mean<<endl; 
  
   delete_vector_int(&vPartIndex);
}

void attrbDetail::swapPosition()
{
    int index=0;
    int index1=0;
    int index2=0;
    double tmp =0.0;
    int numSwap = (int)(((double)m_numPerfectSam)*(((double)SWAP_POSITION_PERCENT)/100.0));
    for(index=0;index<numSwap;index++)
    {
        index1 = (int)randomizedFn(m_numPerfectSam-1,0);
        index2 = (int)randomizedFn(m_numPerfectSam-1,0);
        
        tmp = m_result[index1];
        m_result[index1] = m_result[index2];
        m_result[index2] = tmp;
        
    }
}
void attrbDetail::setValueInLoop(int startP,int endP,double max,double min)
{
    int index=0;
    for(index=startP;index<endP;index++)
    {
        m_result[index] =randomizedFn(max,min);
    }
}
void attrbDetail::fillMedian()
{
    char isOdd = (m_numPerfectSam%2==1);
    int position = m_numPerfectSam/2;
    int position2 = position-1;
    position = position*((position>=0)&&(position<m_numResult));
    position2 = position2*((position2>=0)&&(position2<m_numResult));
    if(isOdd==1)
    {
        m_result[position] = m_median;
    }
    else
    {
        m_result[position] = m_median;
        m_result[position-1] = m_median;
    }
}
void attrbDetail::fillMode2Arr(vector_int  *vArr,int index,int index2,int percentile)
{  
//MODE_PERCENT
    int limit1  =0;
    int limit2  =0;
    int startMid=0;
    int startFilMode=0;
    int numFillModeVal = (int)(((double)vArr->data[vArr->lenght-1])*((double)percentile)/100.0);
//  cout<<"mode zone :"<<index<<" "<<index2<<endl;
    char isOdd = (vArr->data[vArr->lenght-1]%2 ==1);
 //   int indexStart;
    int endFillMode =0;

    if(isOdd ==0) //even 
    {
        // find limit1 
        limit1 = vArr->data[vArr->lenght-1]/2;
        limit1 = limit1-1;
        limit1 = limit1*(limit1>=0);
        
        // find startMid
        startMid = limit1+2;
        
    }
    else
    {
        // find limit1 
        limit1 = vArr->data[vArr->lenght-1]/2;
        startMid = limit1+1;
    }
    // find limit2
    limit2 =vArr->data[vArr->lenght-1];

    if((index!=-1)&&(index2!=-1))
    {
        /*
        if(m_modeVal>=m_median)
        {
            cout<<"Found ==999=========== ";
            cout<<" mode:"<<m_modeVal<<" median:"<<m_median<<endl;
        } */
        fillMode2Arr(vArr,index,-1,percentile/2);
        fillMode2Arr(vArr,-1,index2,percentile/2);
        //cout<<" modeVal:"<<m_modeVal<<" middle zone:"<<index<<" "<<index2<<" \n";
        //cout<<"lenght :"<<vArr->lenght;
        //cout<<" nAll ::"<<vArr->data[vArr->lenght-1]<<" numFill:"<<numFillModeVal<<" "<<(int)limit1<<" startMid:"<<startMid<<" l2:"<<limit2<<endl;
    }
    else if(index!=-1)
    {
        endFillMode =vArr->data[index]+numFillModeVal;
        startFilMode =vArr->data[index];
        if((m_modeVal>=m_median)&&(percentile==MODE_PERCENT)&&(percentile>0))
        {
            fillMode2Arr(vArr,index,index,percentile);
        }
        else if(endFillMode<=limit1)
        {
            setValueInLoop(startFilMode,endFillMode,m_modeVal,m_modeVal);
        }
        else
        {
           // cout<<"Special "<<"sart :"<<startFilMode<< "endFillMode:"<<endFillMode<<" l1:"<<limit1<<" numFill:"<<numFillModeVal<<endl;
            startFilMode = limit1-numFillModeVal;
            startFilMode = startFilMode*(startFilMode>0);
            endFillMode = limit1;
            setValueInLoop(startFilMode,endFillMode,m_modeVal,m_modeVal);
        }
        //cout<<"aa1 :"<<"srt :"<<startFilMode<<" ed:"<<endFillMode<<" l1:"<<limit1;
      //  cout<<" mode:"<<m_modeVal<<" median:"<<m_median<<endl;
    }
    else if(index2!=-1)
    {
        endFillMode =vArr->data[index2]+numFillModeVal;
        startFilMode =vArr->data[index2];
        
        if(startMid>startFilMode)
        {
            //cout<<"Special 3: start:"<<startFilMode<<" end:"<<endFillMode;
            //cout<<" newSt:"<<startMid<<" newEnd:"<<(startMid+numFillModeVal)<<endl;
            startFilMode = startMid;
            endFillMode = startMid+numFillModeVal;
        }
        else
        {
            // Do nothing
        }
        if((m_modeVal<=m_median)&&(percentile==MODE_PERCENT)&&(percentile>0))
        {
           // cout<<"Found ===== i1: "<<index<<" i2:"<<index2;
           // cout<<" mode:"<<m_modeVal<<" median:"<<m_median<<endl;
            fillMode2Arr(vArr,index2,index2,percentile);
            //DIVIDED_PART
        }
        else if(endFillMode<=limit2)
        {
            setValueInLoop(startFilMode,endFillMode,m_modeVal,m_modeVal);
        }
        else
        {
           // cout<<"Special2 "<<"sart :"<<startFilMode<< "endFillMode:"<<endFillMode<<" l2:"<<limit2<<" numFill:"<<numFillModeVal<<endl;
            startFilMode = limit2-numFillModeVal;
            startFilMode = startFilMode*(startFilMode>0);
            endFillMode = limit2;
            setValueInLoop(startFilMode,endFillMode,m_modeVal,m_modeVal);
        }
        //cout<<"aa1 :"<<"srt :"<<startFilMode<<" ed:"<<endFillMode<<" l1:"<<limit1;
      //  cout<<" mode:"<<m_modeVal<<" median:"<<m_median<<endl;
    }
    else
    {
        cout<<m_modeVal<<" error mode \n";
    }
}
void divideValue2EachMember(int number,int divider,int *numEach,int *fraction)
{
    double tempDouble =0.0;
    if((numEach!=NULL)&&(fraction!=NULL)&&(divider>0)&&(number>0)&&(number>divider))
    {
        *numEach =(int)tempDouble;
        *fraction = (int)((tempDouble - (double)(*numEach))*(double)divider);
    }
    else if((numEach!=NULL)&&(fraction!=NULL))
    {
        *numEach =0;
        *fraction =0;
    }
    else
    {
        // Do nothing
    }
}
Valueequilizer::Valueequilizer()
{
    m_fraction =0;
    m_eachMembeNumber =0; 
    m_countFraction =0; 
}
void Valueequilizer::initial(int numAll,int divider)
{
    double tempDouble =0.0;
    if((numAll>0)&&(divider>0))
    {
        tempDouble = (double)numAll/(double)divider;
        m_eachMembeNumber =(int)tempDouble;
        tempDouble = ((tempDouble - (double)(m_eachMembeNumber))*(double)divider);
        m_fraction =  (int)(tempDouble+0.5);
        m_countFraction = m_fraction;
        /*
        cout<<"m_eachMembeNumber :"<<m_eachMembeNumber<<" "<<tempDouble<<endl;
        cout<<"m_fraction :"<<m_fraction<<endl;*/
    }
    else
    {
        /* do nothing */
    }
}
int Valueequilizer::numEachCls()
{
    return m_eachMembeNumber+((m_countFraction--) >0);
}