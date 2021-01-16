/********************************************************************/
/*
      FILE        :   preprocML.h
      Name        :   Chalearm Saelim
      Date        :   28 Decenber 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Handle the preprocessing data


      Description :  to use with other application specially Machine learning
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        28-12-2017    csaelim    First draft 
*/
/*******************************************************************/
#ifndef _PREPROCML_H
#define _PREPROCML_H

struct preProcDat
{
    int m_nFoldMx;
    int m_nFoldMn;
    int m_nFoldStep;
    int m_isScale;
};

int constructorPrePro(struct preProcDat *obj, void *preProEle);
int initialDefPrePro(struct preProcDat *obj);
int destructPreproDt(struct preProcDat *obj); 

/* operation */
int gtFoldSizeInPrepro(struct preProcDat *obj,int index);
int gtNFoldSetInPrepro(struct preProcDat *obj);

void prtPrePro(struct preProcDat *obj);

#endif /*  _PREPROCML_H */