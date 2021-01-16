/********************************************************************/
/*
      FILE        :  iVtHandle.h
      Name     :   Chalearm Saelim
      Date       :   10 Dec 2015
      Purpose :   To handle AVL Tree for vector integer
                         Adding, Removing and compare any node in the tree

      Dependency lib list :  -
      Description :      In this file is make up of following list below :
                                1. the necessary methods for AVL tree
*/
/*******************************************************************/
#ifndef _IVTHANDLE_H
#define _IVTHANDLE_H
#include "vectPHandle.h"
#include "avlTree.h"

#define MAX_DEF 100
#define MIN_DEF 0
struct iVtH
{
    vectIHand m_vSet;
    binaryTree m_t;
    int m_max;
    int m_min;
    char m_displyVectSet;
    char m_displyT;
};

struct vhSettingParam
{
    int m_defaultNumEle;
    int m_defaultNumArr;
    char m_defaultDisplayStyle; /*  first bit show value , second bit  show address */
    char m_defaultDisplayStyleT;  /*  first bit show value , second bit  show address */
};
typedef struct iVtH iVtH;
typedef struct vhSettingParam vhSettingParam;
void constructIVTH(iVtH *obj ,int numArr,int numEle);
void destructIVTH(iVtH *obj);
void clearTIVTH(iVtH *obj);
void clearAnodeInTIVTH(iVtH *obj,int indexNode);
void setNumArrAndNumEle(iVtH *obj,int numArr,int numEle);
void setStyleOfIVTH(iVtH *obj,char  styleVect,char styleTree);
void setMaxMinValueIVTH(iVtH *obj,int max,int min);
void setAllVectValueIVTH(iVtH *obj);
void AddAllValue2TIVTH(iVtH *obj);
void viewVListIVTH(iVtH *obj);
void viewTIVTH(iVtH *obj);
void viewIVTH(iVtH *obj);

void printKeyVInTIVTH(void *key,char *buff);
void printKeyVInTIVTH2(void *key,char *buff); /* with address*/
int compVIntIVTH(const void* a,const void *b);

/*   User Interface method part */
void constructVHSetting(vhSettingParam *obj);
void displayValueVHSetting(vhSettingParam *obj);
void setVectEleVHSetting(vhSettingParam *obj);
void setArrSizeVHSetting(vhSettingParam *obj);
int setIndex2RemNodeVHSetting();
void setDisplayStyleVectSetVHSetting(vhSettingParam *obj);
void setDisplayStyleTVHSetting(vhSettingParam *obj);
void initialedVHByVHSet(vhSettingParam *obj,iVtH *obj2);
void initialedStyleByVHSet(vhSettingParam *obj,iVtH *obj2);
void menuDisplayOfVH();
void menuSettingVHset();
int mainSettingMenu(vhSettingParam *obj);
void mainDisplayLoopVHSetting(iVtH *obj);
#endif /*_IVTHANDLE_H*/