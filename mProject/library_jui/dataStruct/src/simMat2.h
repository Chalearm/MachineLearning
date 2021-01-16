/********************************************************************/
/*
      FILE        :   simMat2.h
      Name        :   Chalearm Saelim
      Date        :   25 October 2016
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Vector manager 

      Description :    -
      Dependency     :   We use the included library as below 
                                                #include -
      How to compile: gcc tcpSvr.c -o  a
      How to run        : -
      
      revision-history
      version   date          author     Description
      1.        25-10-2016    csaelim    First draft
      2         29-10-2016    csaelim    Added member variable: m_usedCount 
                                         in struct mat2
                30-10-2016    csaelim    Added mat2_2d struct and its methods
                                         Added struct mat2Ele
      3         31-10-2016    csaelim    Added new methods ofr mat2 struct 
      4         13-02-2017    csaelim    Added new element for AVL tree and print methods of mat2_2d
*/


/*******************************************************************/
#ifndef _SIMMAT2_H
#define _SIMMAT2_H
#define NUMMULTIPLER_ARR 25
#define NUM_ARR NUMMULTIPLER_ARR+1
#define NUMUNSIGNED_MAT2 5
#define NUMUNSIGNED_VECT2 2

struct vect2
{
    unsigned int m_length;
    unsigned int m_dataSize;
};

struct mat2Ele
{
    void *m_pointRef;
    unsigned int m_length;
    void *m_startP;
}; 

struct nodeFixedArr
{
    void *m_ref; /* void *m_pointRef; */
    unsigned int m_length; /* unsigned int m_length */
    unsigned int m_height;
    struct nodeFixedArr *m_lf;
    struct nodeFixedArr *m_rt;
    /* point at data */
    void *m_dat;
    void *m_dat2;
};
struct nodeFixedArr4SpecialUsed
{
    void *m_ref; /* void *m_pointRef; */
    unsigned int m_length; /* unsigned int m_length */
    unsigned int m_height;
    struct nodeFixedArr *m_lf;
    struct nodeFixedArr *m_rt;
    /* point at data */
    const void *m_dat;
    const void *m_dat2;
};
struct nodeFixedArrNBIn /* not build in not need to know col and length*/
{
    void *m_ref; /* void *m_pointRef; */
    unsigned int m_height;
    struct nodeFixedArrNBIn *m_lf;
    struct nodeFixedArrNBIn *m_rt;
    /* point at data */
    void *m_dat;
    void *m_dat2;
};

struct mat2
{
    /*
        type =2 : added length 
        type =3 : avlTree node element
    */
    unsigned int m_type;
    unsigned int m_row;
    unsigned int m_col;
    unsigned int m_dataSize;
    unsigned int m_currenIndex;
    unsigned int m_usedCount;
    void **rowP;
};

struct mat2_2d
{    
    unsigned int m_segmentCur;
    unsigned int m_segmentCurIndex;
    unsigned int m_numUsed;
    struct mat2 *m_dat[NUM_ARR];
};

struct pVoidEle2
{
    void *m_ref;
    struct pVoidEle2 *m_next;
    struct pVoidEle2 *m_back;
    void *m_data;
};

typedef struct vect2 vect2;
typedef struct mat2 mat2;
typedef struct mat2_2d mat2_2d;

vect2* newVt2(unsigned int num,unsigned int valSize);
unsigned int calSizeVt2(struct vect2 *obj);
void clearVt2(struct vect2 **obj);
void* getDatVt2(struct vect2 *obj);

mat2* newMt2(unsigned int row,unsigned int col,unsigned int valSize,unsigned int type);
unsigned int calSizeMt2(struct mat2 *obj);
unsigned int calRowSizeMt2(unsigned int col,unsigned int dataSize,unsigned int type);
unsigned int calAllocateSize(unsigned int row,unsigned int col,unsigned int valSize,unsigned int type);
unsigned int getNumUsedMt2(struct mat2 *obj);
void clearMt2(struct mat2 **obj);
void** getDatMt2(struct mat2 *obj);
void* getDatNextMt2(void *obj);
void* go2DatMt2(struct mat2 *obj,unsigned int index);
void* readDatNextMt2(struct mat2 *obj);
int resetDatStoreInMt2(struct mat2 *obj);
unsigned int getCurIndexMt2(struct mat2 *obj);
unsigned int isCanSetCurIdMt2(struct mat2 *obj,unsigned int dat);
unsigned int setCurIndexMt2(struct mat2 *obj,unsigned int dat);

void resetReaderDatMt2(struct mat2 *obj);
void printMt2(struct mat2 *obj);
void rmEleMt2(void *obj1,void *dat);
void printMt24Double(struct mat2 *obj);
void swapMt2(struct mat2Ele *rhs,struct mat2Ele *lhs);
void swapMt2t3(struct nodeFixedArr *rhs,struct nodeFixedArr *lhs);
void swapMt2t4(struct nodeFixedArrNBIn *rhs,struct nodeFixedArrNBIn *lhs);
void swapMt2t5(struct pVoidEle2 *rhs,struct pVoidEle2 *lhs);
void swapRandomMt2(struct mat2 *obj);
void swapRandomMt2WithNum(struct mat2 *obj,unsigned int numRandom);

struct mat2_2d newMt22d(unsigned int row,unsigned int col,unsigned int valSize,unsigned int type);
void initiValInMt22d(struct mat2_2d *obj);
void clearMt22d(struct mat2_2d *obj);
unsigned int getTypeMt22d(struct mat2_2d *obj);
void** getDatMt22d(struct mat2_2d *obj,unsigned int indexSegment);
void* getDatNextMt22d(void *obj1);
void* readDatNextMt22d(struct mat2_2d *obj);

int resetDatStoreInMt22d(struct mat2_2d *obj);
void* go2ReadDatMt22d(struct mat2_2d *obj,unsigned int indexSegment,unsigned int offset);
int convertIndex2IdSegAndOfSt4Mt22d(struct mat2_2d *obj,const unsigned int id,unsigned int *indexSegment,unsigned int *offset);
void expandMt22dSize(struct mat2_2d *obj);
void resetReaderDatMt22d(struct mat2_2d *obj);
unsigned int getCurSegIdMt22d(struct mat2_2d *obj,unsigned int *segId,unsigned int *id);
unsigned int setCurSegIdMt22d(struct mat2_2d *obj,const unsigned int  segId,const unsigned int id);
unsigned int isCanSetCurSegIdMt22d(struct mat2_2d *obj,const unsigned int  segId,const unsigned int id);

unsigned int getUsedNumDatMt22d(struct mat2_2d *obj);
unsigned int getUsedOffsetNumDatMt22d(struct mat2_2d *obj,unsigned int indexSegment);
unsigned int getNumOfUsedDatMt22d(struct mat2_2d *obj);
void rmEleMt22d(void *obj1,void *dat);
void printMt22d(struct mat2_2d *obj);
void printHeadFixedArrNode(struct nodeFixedArr *obj);
void printHeadFixedArrNode2(struct nodeFixedArrNBIn *obj);
void printHeadPvEle2(struct pVoidEle2 *obj);
void printMt22d4Double(struct mat2_2d *obj);
void swapRandomMt22dWithNum(struct mat2_2d *obj,unsigned int numRandom);
void swapByIndex4Mt22D(struct mat2_2d *obj,unsigned int idA,unsigned int idB);
void expandMt22dSizeWithSize(struct mat2_2d *obj,unsigned int numNewRow);

/* private method of struct pVoidEle2 */

void* getNxpVd2Ele(void *node);
void* getBkpVd2Ele(void *node);
void* getDatpVd2Ele(void *node);
    
int setNxpVd2Ele(void *node1,void *node2);
int setBkpVd2Ele(void *node1,void *node2);
int setDatpVd2Ele(void *node1,void *node2);
void freeAlcPEle2(void *obj,void *node);
/* void constructorPVoidList2(pVoidList *list,void *othSrc,void **paraFunct);*/
void constructPVList4PVEle2(void *node,void *src,void *funct);
void initialPVList4PVEle2_1(void *obj,int val,void *funct1,void *funct2);
/* end of private method of struct pVoidEle2 */
/*void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey);*/
void construAvlT4SmMt2(void *bin,char isWD,const char *key,int sizeDt,int sizeKy,void *fnt);
#endif /*_SIMMAT2_H */