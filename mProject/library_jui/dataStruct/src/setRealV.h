/********************************************************************/
/*
      FILE        :   setRealV.h
      Name        :   Chalearm Saelim
      Date        :   28 July 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to as a Set structure, element is long integer value (32 bits) 
                      setRealV = (Real value = floating point or number) set

      Description :   it keeps element in the way of AVL tree and Fixed sized array (semi-dynamic array)
      Dependency     :   We use the included library as below 
                                                #include "simMat2.h" 
                                                #include "avlTree.h"
      How to compile: gcc setLInt.c -o  a
      How to run        : -
      
      revision-history
      version   date          author     Description
      1.        28-07-2017    csaelim    First draft
      2.        14-08-2017    csaelim    Defined type of SetRV
      3.        25-09-2017    csaelim    Added the vector feature
      */


/*******************************************************************/
#ifndef _SETREALV_H
#define _SETREALV_H
#include "avlTree.h"
#include "simMat2.h"

#define FLOATING_POINT_BIT 0x01
#define NOT_DYNAMIC_ARR_BIT 0x02
#define NOT_COUNT_REDUNDANT_BIT 0x04
#define VECT_BIT 0x08
/* data structure */
struct vector_lint
{
    unsigned int m_lenght;
    long int *m_data;
};

/*
    can be kept redundant value
 */
/*
        m_type  
            1 st bit  : 0 long integer , 1 floating-point (double)
            2 nd bit  : 0 dynamic array, 1 not dynamic array
            3 rd bit  : 0 count redundant, 1 not count
            4 th bit  : 0 not vector, 1 vector
            5 th bit  : (spare)
            6 th bit  : (spare)
            7 th bit  : (spare)
            8 th bit  : (spare)
            9 th bit  : (void*) set, igore first bit to 8 th bit.
                                  Must provide compare method, (option): de-allocation and print method
 */
/*m_buff :in case of no using dynamic arrar, this is used (mat2_2d structure) */
/*m_numMember : include redundant value */
struct rvSet
{
    int m_dimen;   /*default = -1 in case not vector */
    unsigned long int m_type;
    binaryTree m_tree;
    void *m_buff;
    unsigned long int m_numMember;
};

/* private method */
    /* for struct vector_lint */
    struct vector_lint new_vect_lint(unsigned int size);
    void del_vect_lint(struct vector_lint *obj);
    void setDat2VLint(struct vector_lint *obj,const long int *dat);
    void getDatFromVLint(const struct vector_lint *obj,long int *dat);

    /* other function */
    double randomVal(double max,double min);
    
/* print key of tree*/
void prntKeyTFixedArryBInIntNoCountStRV(void* key,char* buff);
void prntKeyTFixedArryBInDoubleNoCountStRV(void* key,char* buff);
void prntKeyTFixedArryBInIntCountStRV(void* key,char* buff);
void prntKeyTFixedArryBInDoubleCountStRV(void* key,char* buff);

void prntLintKeyAvlT(void* key,char* buf);
void prntVLintKeyAvlT(void* key,char* buf);
void prntDoubleKeyAvlT(void* key,char* buf);
void prntVDoubleKeyAvlT(void* key,char* buf);

void delKeyNode4AvlT(void *obj,void *key);
void delDatNode4AvlT(void *obj,void *dat);

void prntDatIntCountStRV(void *dat,char *buff);
void prntDatDoubleCountStRV(void *dat,char *buff);

int compDouble4StRV(const void *a,const void *b);
int compLongInt4StRV(const void *a,const void *b);
int compDouble4AVLTFixedArrBIn(const void* a,const void *b);
int compLint4AVLTFixedArrBIn(const void* a,const void *b);
int compVLint4CountDatAVLTFixedArrBIn(const void* a,const void *b);
int compVLint4NotCountDatAVLTFixedArrBIn(const void* a,const void *b);
int compVDouble4CountDatAVLTFixedArrBIn(const void* a,const void *b);
int compVDouble4NotCountDatAVLTFixedArrBIn(const void* a,const void *b);

int compVLint4StRV(const void *a,const void *b);
int compVDouble4StRV(const void *a,const void *b);
void*  isInRVSetPrvt(struct rvSet *obj,const void *val);
int clearMemberOutInRVSet(struct rvSet *obj);
void delVLintNodeRVSet(void *obj,void *key);
void delVLintCountDatRVSet(void *obj,void *data);
void delVDoubleNodeRVSet(void *obj,void *key);

/* used only, not dynmic array case */
void* getDatInRVSetByIndex(struct rvSet *obj,int index);
void* getNxtDatInRVSet(struct rvSet *obj);
void resetGetNxtDat(struct rvSet *obj);
void pushStateNxtDat(struct rvSet *obj, unsigned int *segId,unsigned int *id);
int isCanPopStateNxtDat(struct rvSet *obj,const unsigned int segId,const unsigned int id);
int popStateNxtDat(struct rvSet *obj,const unsigned int segId,const unsigned int id);


/* public method */

/* operation */
void constructorRVSetVect(struct rvSet *obj,unsigned long int type,int dimenVal);
void constructorRVSet(struct rvSet *obj,unsigned long int type);
void destructorRVSet(struct rvSet *obj);
unsigned long int  isInRVSet(struct rvSet *obj,void *val);
/* *val = (long int *) or (double *) (array or one element) */
unsigned long int  added2RVSet(struct rvSet *obj,const void *val);
/* 1 = is remove all, 0 is count--, in case not redundant, opt is ignored. */
unsigned long int removedValRVSet(struct rvSet *obj,void *val,unsigned long int opt);
unsigned long int numEleRVSet(struct rvSet *obj);
unsigned long int numEleRVSetNotRedunt(struct rvSet *obj);
unsigned long int numDimenVSet(struct rvSet *obj);
unsigned long int merged2ThisRvSet(struct rvSet *lhs,struct rvSet *rhs);
void printRvSet(struct rvSet *obj);
void printLinearByIndexSet(struct rvSet *obj);
unsigned long int getTypeOfRVSet(struct rvSet *obj);
void swapRandomPosOfRVSet(struct rvSet *obj,int minPos,int maxPos);

#endif /*_SETREALV_H */