/********************************************************************/
/*
      FILE        :  vectPHandl.h
      Name     :   Chalearm Saelim
      Date       :   14 Nov 2015
      Purpose :   Vector  (integer)pointer array handle library
                         Adding, Removing, Reblance and destruct tree

      Dependency lib list :  simMatInt.h
      Description :      In this file is make up of following list below :
                                1. data structure to handle array of vector integer
                                2. methods for pluging to AVL tree
                                3  statements about adding Vector integer  pointer key to the tree
                                4. statements about removing Vector integer  pointer key from the node
*/
/*******************************************************************/
#ifndef _VECTPHANDLE_H
#define _VECTPHANDLE_H
#include "simMatInt.h"
#define DEF_NUM_ELE 2
#define DEF_NUM_ARR 12
#define DEF_DIS_STYLE 1
#define DEF_DIS_STYLE_T 1
struct vectIHand
{
    vector_int  *m_dat;
    int m_numVect;
    int m_num;
    int m_numCur;
};

typedef struct vectIHand vectIHand;

void constructVH(vectIHand *obj,int numVect,int numArr);
void addVectorInt(vectIHand *obj,const int* dat);
void addVectorIntRandom(vectIHand *obj,int max,int min);
void removeVectInVectHand(vectIHand *obj);
void* getVectInVH(vectIHand *obj,int index);
void printInfoVH(vectIHand *obj,char style);
void addManyVectInrandomVH(vectIHand *obj,int num,int max,int min);
void randomAllVectVH(vectIHand *obj,int max,int min);
void destructVectHand(vectIHand *obj);


#endif /* _VECTPHANDLE_H */