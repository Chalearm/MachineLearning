#include <stdio.h>
#include <stdlib.h>
#include "svmApp.h"
int  initialSvmNode(svmNode *node)
{
    if(node != NULL)
    {
        node->svmVector = NULL;
        node->numSvm    = 0;
        node->pConstant = 0.0;
        node->value     = 0.0;
        node->svmLeft   = NULL;
        node->svmRight  = NULL;
        return 1;
    }
    else
    {
        /* do nothing */
    }
    return 0;
}
int  countSvmNode(svmNode *node)
{
    if(node == NULL)
    {
        return 0;
    }
    else
    {
        return countSvmNode(node->svmLeft)+countSvmNode(node->svmRight) +1;
    }
}
int  findDepthSvmNode(svmNode *node)
{
    int maxL = 0;
    int maxR = 0;
    if(node == NULL)
    {
        return 0; 
    }
    else
    {
        maxL = findDepthSvmNode(node->svmLeft);
        maxR = findDepthSvmNode(node->svmRight);
    }
    if(maxL > maxR)
    {
        /* do nothing */
    }
    else
    {
        maxL = maxR;
    }
    return maxL+1;
}
void destructorSvmNode(svmNode *node)
{
    if(node != NULL)
    {
        destructorSvmNode(node->svmLeft);
        destructorSvmNode(node->svmRight);
        makeSvmVectorEmpty(node);
        if(node->svmLeft != NULL)
        {
            free(node->svmLeft);
        }
        else
        {
            /* do nothing */
        }
        if(node->svmRight != NULL)
        {
            free(node->svmRight);
        }
        else
        {
            /* do nothing */
        }
        node->svmLeft= NULL;
        node->svmRight=NULL;
    }
    else
    {
        return;
    }
}
int  setNumSvmInSvmVector(svmNode *node,int num)
{
    int index = 0;
    if(node !=NULL && num > 0)
    {
        if(node->svmVector == NULL)
        {
            node->svmVector = (vector_double*)malloc(sizeof(vector_double)*num);
            if(node->svmVector == NULL)
            {
                return 0;
            }
            else
            {
                /*do nothing */
            }
            node->numSvm    = num;
            for(index =0 ;index <num;index++)
            {
                node->svmVector[index] = new_vector_double(0);
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
    return 1;
}
void setDimensionSvmNode(svmNode *node,int dim)
{
    int num  =0;
    int index=0;
    if(node == NULL || dim <1)
    {
        return;   
    }
    else if(node->svmVector==NULL)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    num = node->numSvm;
    for(index =0 ;index<num;index++)
    {
        node->svmVector[index] = new_vector_double(dim);
    }
}
void makeSvmVectorEmpty(svmNode *node)
{
    int index = 0;
    int numSvm= 0;
    numSvm = node->numSvm;
    for(index = 0;index < numSvm;index++)
    {
        delete_vector_double(&(node->svmVector[index]));
    }
    free(node->svmVector);
    node->numSvm = 0;
    node->svmVector=NULL;
}
void setValueOfSvmNode(svmNode *node,double val)
{
    node->value = val;
}
void setDoubleVectorValueInSvmNode(svmNode *node,int index,vector_double val)
{
    copy_v_double(&(node->svmVector[index]),&val);
}
void setPConstant(svmNode *node,double p)
{
    node->pConstant = p;
}
int  initialMultiSvm(multiSvm *msvm)
{
    if(msvm !=NULL)
    {
        msvm->numNode      = 0;
        msvm->root         = NULL;
        msvm->type         = 0; /* 0 = list, 1 = bin tree */
        msvm->depthSvmNode = 0;
        msvm->numClass     = 0;
        msvm->pConstant    = 0.0;
    }
    else
    {
        return 0;
    }
    return 1;
}
void destructorMultiSvm(multiSvm *msvm)
{
    if(msvm != NULL)
    {
        destructorSvmNode(msvm->root);
        initialMultiSvm(msvm);
    }
    else
    {
        /* do nothing */
    }
}
void setTypeMultiSvm(multiSvm *msvm,char t)
{
    if(msvm != NULL && (t == 1 || t==0))
    {
        msvm->type = t;
    }
    else
    {
        /* do nothing */
    }
}
int  countSvmNodeMultiSvm(multiSvm *msvm)
{
    return countSvmNode(msvm->root);
}
int  setNumAttrbMultiSvm(multiSvm *msvm,int num)
{
    if(msvm == NULL || num < 1)
    {
        return 0;
    }
    else
    {
        msvm->dimSize = num;
    }
    return 1;    
}
int  setNumClassMultiSvm(multiSvm *msvm,int num)
{
    if(msvm == NULL || num < 2)
    {
        return 0;
    }
    else if(msvm->root == NULL)
    {
        msvm->numClass = num;
    }
    else
    {
        return 0;
    }
    return 1;
}
int  getNumAttrbMultiSvm(multiSvm *msvm)
{
    if(msvm == NULL)
    {
        return -1;
    }
    else
    {
        /* do nothing */
    }  
    return msvm->dimSize; 
}
int  getNUmClassMultiSvm(multiSvm *msvm)
{
    if(msvm == NULL)
    {
         return -1;
    }
    else
    {
         /* do nothing */
    }
    return msvm->numClass;
}
int  getDepthMultiSvm(multiSvm *msvm)
{
    if(msvm == NULL)
    {
         return -1;
    }
    else
    {
         /* do nothing */
    }
    return msvm->depthSvmNode;
}
int  findDepthMultiSvm(multiSvm *msvm)
{
    return findDepthSvmNode(msvm->root);
}

int initialSvmApp(svmApp *app)
{
    if(app != NULL)
    {
        initialSimString(&(app->abPath));
        initialSimString(&(app->inputMgrPath));
        initialSimString(&(app->taskMgrPath));
        initialMultiSvm(&(app->currentMSvm));
        app->uiMode = 0;
        
app->bbbb = 0;
app->cccc = 0;
    }
    else
    {
        return 0;
    }
    return 1;
}
void destructSvmApp(svmApp *app)
{
    if(app != NULL)
    {
        destructSimString(&(app->abPath));
        destructSimString(&(app->inputMgrPath));
        destructSimString(&(app->taskMgrPath));
        destructorMultiSvm(&(app->currentMSvm));
    }
    else
    {
        /* do nothing  */
    }
}
void addAbsolutePathSvmApp(svmApp *app,vector_char *dat)
{
    if(app != NULL && dat != NULL)
    {
         convertVectorChar2SimString(&(app->abPath),dat);
    }
    else
    {
        /* do nothing */
    }
}
void addInputPathSvmApp(svmApp *app,vector_char *dat)
{
    if(app != NULL && dat != NULL)
    {
         convertVectorChar2SimString(&(app->inputMgrPath),dat);
         concatSimStringPathDirectory(&(app->abPath),&(app->inputMgrPath),&(app->inputMgrPath));
    }
    else
    {
        /* do nothing */
    }
}
void addTaskPathSvmApp(svmApp *app,vector_char *dat)
{
    if(app != NULL && dat != NULL)
    {
         convertVectorChar2SimString(&(app->taskMgrPath),dat);
         concatSimStringPathDirectory(&(app->abPath),&(app->taskMgrPath),&(app->taskMgrPath));
    }
    else
    {
        /* do nothing */
    }
}
void setUiMode(svmApp *app,char uim)
{
    if(app != NULL && ((uim ==0) || (uim ==1)))
    {
        app->uiMode = uim;
    }
    else
    {
        app->uiMode=1; /* normal mode = show ui */
    }
}
char isUiModeSvmApp(svmApp *app)
{
    if(app != NULL && ((app->uiMode ==1) || (app->uiMode==0)))
    {
        return app->uiMode;
    }
    else
    {
        return 1; /* default is ui show status */
    }
}
char validVariableSvmApp(svmApp *app)
{
    FILE *fp=NULL;
    int fact1 = 1;
    if(app == NULL)
    {
        fact1 = 0;
        printf("app is NULL\n");
    }
    else
    {
        /* do nothing */
    }
    fp = fopen(app->taskMgrPath.data,"r");
    if(fp == NULL)
    {
        printf("cannnot open task config\n");
        fact1 = 0;
    }
    else
    {
        fclose(fp);
    }
    fp = fopen(app->inputMgrPath.data,"r");
    if(fp == NULL)
    {
        printf("cannot open input config\n");
        fact1 = 0;
    }
    else
    {
        fclose(fp);
    }
    return fact1;
}
