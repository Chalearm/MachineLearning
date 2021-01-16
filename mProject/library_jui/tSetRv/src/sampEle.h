/********************************************************************/
/*
      FILE        :   sampEle.h
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

#ifndef _SAMPELE_H
#define _SAMPELE_H
#include <stdlib.h>
#include <stdio.h> 

struct smpEle
{
    int m_nDim;
    double m_y;
    double *m_dt;
};

int initial2DefaultSmpEle(struct smpEle *obj);
int contructorSmpEle(struct smpEle *obj,int nDim,double yVal);
int destructorSmpEle(struct smpEle *obj);
double gtOtptSmpEle(struct smpEle *obj);
double* gtDtSmpEle(struct smpEle *obj);
void prtSmpEle(struct smpEle *obj);
void prtSmpEle2(void *obj);

#endif /* _SAMPELE_H */

