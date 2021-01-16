/********************************************************************/
/*
      FILE        :   clsDetail.h
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
#ifndef _CLSDETAIL_H
#define _CLSDETAIL_H

#include "dDimn.h"

struct clsDetail
{
    int m_nDim;
    int m_nSam;
    int m_nTrnSam;
    int m_nTestSam;
    double m_defMxV;
    double m_defMnV;
    struct dtDim *m_dtDm;
};

int constructorClsDetl(struct clsDetail *obj,int nmDim,void *clsEle);
int initialClsDetl(struct clsDetail *obj);
int destructClsDetl(struct clsDetail *obj);

/* operation */
int generateASmVal(struct clsDetail *obj,double *val);
int newClsDetail(struct clsDetail **obj,int numDim,void *clsListNode);
int gtNsmInAllCls(struct clsDetail *obj,int nCls);
int gtNsmInACls(struct clsDetail *obj);
int gtTrnNsmInACls(struct clsDetail *obj);
void prtClsDetl(struct clsDetail *obj);

#endif /*  _CLSDETAIL_H */