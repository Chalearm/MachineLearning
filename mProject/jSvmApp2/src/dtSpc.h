/********************************************************************/
/*
      FILE        :   dtSpc.h
      Name        :   Chalearm Saelim
      Date        :   28 Decenber 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to keep samples

      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        28-12-2017    csaelim    First draft 
*/
/*******************************************************************/
#ifndef _DTSPC_H
#define _DTSPC_H

#include "setRealV.h"

struct datSpace
{
    struct rvSet m_dt;
};

 
int constructDatSpc(struct datSpace *obj,int numDim);
int destructDatSpc(struct datSpace *obj);
void prtDatSpace(struct datSpace *obj);
/* operation */ 
int swapValueEachRangeInDtSp(struct datSpace *obj,int maxPos,int minPos);
int st2SetInDtSp(struct datSpace *obj,double *val);
int gtSampleInputDtInDtSp(struct datSpace *obj,int index,double **val);

#endif /*  _DTSPC_H  */