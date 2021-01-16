/********************************************************************/
/*
      FILE        :   dtStGnHdl.h
      Name        :   Chalearm Saelim
      Date        :   28 Decenber 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Handle the class data


      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        28-12-2017    csaelim    First draft 
*/
/*******************************************************************/
#ifndef _DTSTGNHDL_H
#define _DTSTGNHDL_H
 
#include "clsDetail.h"

struct datSetGenHdl
{
    int m_nDim;
    int m_nSam;
    int m_nCls;
    struct clsDetail *m_clsEle;
    
    /* buffer data*/
    double *m_tmpDtArea;
    double *m_tmpY;
    double *m_tmpDt;
};


int constructorDatStGnHdl(struct datSetGenHdl *obj, void *dtStEle);
int initialDatStHdl(struct datSetGenHdl *obj);
int destructDtStHdl(struct datSetGenHdl *obj);

/* operation */
int gtAllNSmpInDtSHld(struct datSetGenHdl *obj);
int gtNDimInDtSHld(struct datSetGenHdl *obj);
int gtNsmInAClsInDtSHld(struct datSetGenHdl *obj,int index);
int gtNTrnsmInAClsInDtSHld(struct datSetGenHdl *obj,int index);
int gtNClsInDtSHld(struct datSetGenHdl *obj);
void prtStHdl(struct datSetGenHdl *obj);

#endif /*  _DTSTGNHDL_H */