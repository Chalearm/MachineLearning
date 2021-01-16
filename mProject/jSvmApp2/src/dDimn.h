/********************************************************************/
/*
      FILE        :   dDimn.h
      Name        :   Chalearm Saelim
      Date        :   28 Decenber 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Handle the element of a sample, 
                      in case of generate data by the application

      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        28-12-2017    csaelim    First draft 
*/
/*******************************************************************/
#ifndef _DDIMN_H
#define _DDIMN_H

struct dtDim
{
    double m_mx;
    double m_mn;
};

int initialDtDm(struct dtDim *obj);
int constructorDtDm(struct dtDim *obj,void *dmEle,double defMx,double defMn);
int destructDtDim(struct dtDim *obj);
/* operation */ 
int newDtDms(struct dtDim **obj,int numDim,void *dtDmListNode,double defMx,double defMn);
int generateAnEleInASmVal(struct dtDim *obj,double *val);
void prtDtDm(struct dtDim *obj);

#endif /*  _DDIMN_H  */