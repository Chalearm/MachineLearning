#ifndef SVMAPP_H_
#define SVMAPP_H_
#include "simMatDouble.h"
#include "simMatChar.h"
#include "simString.h"


#define UNKNOW_STATIS             -2
#define IGNORE_STATIS             -1 /* it means using default value*/
#define MEAN_STATIS                0
#define MEDIAN_STATIS              1
#define MOD_STATIS                 2
#define RANDOM_DOUBLE_STATIS       3
#define RANDOM_INT_STATIS          4
#define MAX_VAL_STATIS             5
#define MIN_VAL_STATIS             6
#define UNDEFINE_STATIS            7 
struct svmNode /* use only list or binary tree */
{
    vector_double *svmVector;
    int            numSvm;
    double         pConstant;
    double         value;
    struct svmNode *svmLeft;
    struct svmNode *svmRight;
};
struct multiSvm
{
    int numNode;
    struct svmNode *root;
    char type; /* type = 0 list, 1=binary */
    int  depthSvmNode;
    int  dimSize;
    int  numClass;
    double pConstant;/* p = dimension or guessian value */
};
struct svmApp
{
    char uiMode;
    simString abPath;
    simString inputMgrPath;
    simString taskMgrPath;
    struct multiSvm currentMSvm;
    
    
int bbbb;
int cccc;
};

typedef struct svmNode svmNode;
typedef struct multiSvm multiSvm;
typedef struct svmApp svmApp;
int  initialSvmNode(svmNode *node);
int  countSvmNode(svmNode *node);
int  findDepthSvmNode(svmNode *node);
void setDimensionSvmNode(svmNode *node,int dim);
void destructorSvmNode(svmNode *node);
int  setNumSvmInSvmVector(svmNode *node,int num);
void makeSvmVectorEmpty(svmNode *node);
void setValueOfSvmNode(svmNode *node,double val);
void setDoubleVectorValueInSvmNode(svmNode *node,int index,vector_double val);
void setPConstant(svmNode *node,double p);

int  initialMultiSvm(multiSvm *msvm);
void destructorMultiSvm(multiSvm *msvm);
void setTypeMultiSvm(multiSvm *msvm,char t);
int  countSvmNodeMultiSvm(multiSvm *msvm);
int  setNumAttrbMultiSvm(multiSvm *msvm,int num);
int  setNumClassMultiSvm(multiSvm *msvm,int num);
int  getNumAttrbMultiSvm(multiSvm *msvm);
int  getNUmClassMultiSvm(multiSvm *msvm);
int  getDepthMultiSvm(multiSvm *msvm);
int  findDepthMultiSvm(multiSvm *msvm);

int  initialSvmApp(svmApp *app);
void setUiMode(svmApp *app,char uim);
void destructSvmApp(svmApp *app);
void addAbsolutePathSvmApp(svmApp *app,vector_char *dat);
void addInputPathSvmApp(svmApp *app,vector_char *dat);
void addTaskPathSvmApp(svmApp *app,vector_char *dat);
char isUiModeSvmApp(svmApp *app);
char validVariableSvmApp(svmApp *app);
#endif
