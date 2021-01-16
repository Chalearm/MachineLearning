/********************************************************************/
/*
      FILE        :   sampEle.c
      Name        :   Chalearm Saelim
      Date        :   06 December 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Provide a data structure for a sample data in a class


      Description :  this is to use for testing with setRealV data struct
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        06-12-2017    csaelim    First draft 
*/
/*******************************************************************/
#include "sampEle.h"


int initial2DefaultSmpEle(struct smpEle *obj)
{
    int ret = (obj != NULL);
    if (ret == 1 )
    {
        obj->m_nDim = 0;
        obj->m_y = 0.0;
        obj->m_dt = NULL;
    }
    else
    {
        printf("Error(0) in initial2DefaultSmpEle, obj is NULL, ln:%d file:%s\n",__LINE__,__FILE__);
    }
    return ret;
}

int contructorSmpEle(struct smpEle *obj,int nDim,double yVal)
{
    int ret = (initial2DefaultSmpEle(obj) == 1) && (nDim > 0);
    if (ret == 1)
    {
        obj->m_nDim = nDim;
        obj->m_dt = malloc(sizeof(double)*nDim);
        obj->m_y = yVal;
        if (obj->m_dt == NULL)
        {
            initial2DefaultSmpEle(obj);
            printf("Error(1) in contructorSmpEle, cannot allocate the area for a sample, ln:%d, file:%s\n",__LINE__,__FILE__);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Error(0) in contructorSmpEle, obj is %p, nDim:%d, ln:%d file:%s\n",obj,nDim,__LINE__,__FILE__);
    }
    return ret;
}
int destructorSmpEle(struct smpEle *obj)
{
    int ret = (obj != NULL);
    if (ret == 1 )
    {
        if( obj->m_dt != NULL)
        {
            free(obj->m_dt);
            obj->m_dt = NULL;
        }
        else
        {
            /* do nothing */
        }
        initial2DefaultSmpEle(obj);
    }
    else
    {
        printf("Error(0) in destructorSmpEle, obj is NULL, ln:%d file:%s\n",__LINE__,__FILE__);
    }
    return ret;
}

double gtOtptSmpEle(struct smpEle *obj)
{
    double tmp = 0;
    if (obj != NULL)
    {
        tmp = obj->m_y;
    }
    else
    {
        printf("Error(0) in gtOtptSmpEle, obj is NULL, ln:%d file:%s\n",__LINE__,__FILE__);
    }
    return tmp;
}
double* gtDtSmpEle(struct smpEle *obj)
{
    double *tmp = NULL;
    if (obj != NULL)
    {
        tmp = obj->m_dt;
    }
    else
    {
        printf("Error(0) in gtDtSmpEle, obj is NULL, ln:%d file:%s\n",__LINE__,__FILE__);
    }
    return tmp;
}
void prtSmpEle(struct smpEle *obj)
{
    int num = 0;
    int index = 0;
    if (obj != NULL)
    {
        num = obj->m_nDim;
        printf("[");
        for (index = 0;index < num ;index++)
        {
            printf("%f ",obj->m_dt[index]);
        }
        printf("]");
    }
    else
    {
        printf("Error(0) in prtSmpEle, obj is NULL, ln:%d file:%s\n",__LINE__,__FILE__);
    }
}
void prtSmpEle2(void *obj)
{
    prtSmpEle((struct smpEle*)obj);
}


