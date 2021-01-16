#ifndef BINARYTREE_H_
#define BINARYTREE_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "listPvoid.h"
#include "dataTypeAndRoutineDefine.h"
#include "treeDefine.h"

struct binaryTree
{
    int configRight;
    int sizeKey;
    int sizeData;
    char isData;
    char isNotDelKey; /* 0 is delete key , 1 is not delete key*/
    char isPrint;
    int typeBT;
    
    int numNode;
    void* root;
    
    void* parameter1; /* key */
    void* parameter2; /* data */
    void* parameter3; /* node */ /* mat2d2 obj */
    void* parameter4; /* node */ /* mat2d2 obj 2*/
    void* parameter5; /* node */ /* mat2d2 obj 3*/
    
    /* comparsion method */
    int (*compareType)(const void*,const void*);
    int (*compareTypeWithOpt)(void*,const void*,const void*);
    
    /* deletion method */
    int (*deleteNode)(struct binaryTree*,void**);
    void (*deleteKey)(void*,void*);
    void (*deleteData)(void*,void*);
    int (*deleteNodeByKey)(struct binaryTree*,const void*); /* jui12*/
    void (*clearNodesBinaryTree)(struct binaryTree*,void*);
    
    /* insert method */
    void* (*insertFn)(struct binaryTree*,const void*);
    int (*insertFn2)(void*);
    
    /* get method */
    int (*getNodeHeight)(struct binaryTree*,void*);
    void* (*getKey)(void*);
    void* (*getData)(void*);
    void* (*getNodeLeft)(void*);
    void* (*getNodeRight)(void*);
    void** (*getNodeAddrLeft)(void*);
    void** (*getNodeAddrRight)(void*);
    
    /* display method */
    void (*printTree)(struct binaryTree*,char);
    void (*printDataPVoid)(void*,char*);
    void (*printKeyPVoid)(void*,char*);

    /* other */
    int (*constructNodeDataType)(void*);
    void (*swapValue)(void*,void*);
    int (*setNodeHeight)(struct binaryTree*,void*); /* use for AVL tree */
    
    void (*copyDataValue)(void*,void*); /* parameter is to pass the data */
    void* (*copyKeyValue)(struct binaryTree*,void*); /* parameter is to pass the data */
};
typedef struct binaryTree binaryTree;

void printBinTree(binaryTree *bin);
/* initial tree*/
void nullAllMethodsOfBinTree(binaryTree *bin);
void setParameterValofBinT(void *bin1,int index,void *val);
void constructorBinaryTree(binaryTree *bin);
void constructorBinaryTree2(binaryTree *bin,int type,int size,int sizeKey);
void constructorBinaryTree3(binaryTree *bin,const char* type,int size,int sizeKey);

void transverseCopyDataInTree(binaryTree *bLhs,void *node,int high);
void copyConstructorBinTree(binaryTree *bLhs,binaryTree *bRhs);
void assignOperatorBinTree(binaryTree *bLhs,binaryTree *bRhs);

void setDelKeyFlag(binaryTree* bin,char flags);
int validateDataTypeOfBinaryTree(int type,int size,int sizeKey);
int setDataTypeOfBinaryTree(binaryTree* bin,int type,int size,int sizeKey);
void setFunctionOfBinaryTree(binaryTree* bin);
/* get data from tree */
int isEmptyOfBinaryTree(binaryTree* bin);
int heightOfBinaryTree(binaryTree* bin);
int getNumBinaryNodeOfTree(binaryTree* binaryTreeObj);

int countAllNodesInBT(binaryTree* bin);
int countNodesOfANodeInBT(binaryTree* bin,void *node);

/* get Copy key */
void* (*getCopyFnOfBin(const int opCode))(struct binaryTree*,void*);
void* copyIntKeyValue(struct binaryTree *obj,void *nodeA);
void* copyUIntKeyValue(struct binaryTree *obj,void *nodeA);
void* copyCharKeyValue(struct binaryTree *obj,void *nodeA);
void* copyUCharKeyValue(struct binaryTree *obj,void *nodeA);
void* copyShortKeyValue(struct binaryTree *obj,void *nodeA);
void* copyUShortKeyValue(struct binaryTree *obj,void *nodeA);
void* copyLIntKeyValue(struct binaryTree *obj,void *nodeA);
void* copyULIntKeyValue(struct binaryTree *obj,void *nodeA);
void* copyLLIntKeyValue(struct binaryTree *obj,void *nodeA);
void* copyULLIntKeyValue(struct binaryTree *obj,void *nodeA);
void* copyFloatKeyValue(struct binaryTree *obj,void *nodeA);
void* copyDoubleKeyValue(struct binaryTree *obj,void *nodeA);
void* copyLDoubleKeyValue(struct binaryTree *obj,void *nodeA);
void* copyVDoubleKeyValue(struct binaryTree *obj,void *nodeA);
void* copySimStrKeyValue(struct binaryTree *obj,void *nodeA);
/* get Node left address */
void** (*getAddrNodeLeftBinaryFn(const int opCode))(void*);
void** getAddrLeftIntNodeBinary(void* node);
void** getAddrLeftUIntNodeBinary(void* node);
void** getAddrLeftCharNodeBinary(void* node);
void** getAddrLeftUCharNodeBinary(void* node);
void** getAddrLeftShortNodeBinary(void* node);
void** getAddrLeftUShortNodeBinary(void* node);
void** getAddrLeftLIntNodeBinary(void* node);
void** getAddrLeftULIntNodeBinary(void* node);
void** getAddrLeftLLIntNodeBinary(void* node);
void** getAddrLeftULLIntNodeBinary(void* node);
void** getAddrLeftFloatNodeBinary(void* node);
void** getAddrLeftDoubleNodeBinary(void* node);
void** getAddrLeftLDoubleNodeBinary(void* node);
void** getAddrLeftPVoidNodeBinary(void* node);
void** getAddrLeftPVoidWithDataNodeBinary(void* node);
void** getAddrLeftFixArrAvlNd(void* node);
void** getAddrLeftFixArrAvlNd_NBIn(void* node);
/* get Node right address */
void** (*getAddrNodeRightBinaryFn(const int opCode))(void*);
void** getAddrRightIntNodeBinary(void* node);
void** getAddrRightUIntNodeBinary(void* node);
void** getAddrRightCharNodeBinary(void* node);
void** getAddrRightUCharNodeBinary(void* node);
void** getAddrRightShortNodeBinary(void* node);
void** getAddrRightUShortNodeBinary(void* node);
void** getAddrRightLIntNodeBinary(void* node);
void** getAddrRightULIntNodeBinary(void* node);
void** getAddrRightLLIntNodeBinary(void* node);
void** getAddrRightULLIntNodeBinary(void* node);
void** getAddrRightFloatNodeBinary(void* node);
void** getAddrRightDoubleNodeBinary(void* node);
void** getAddrRightLDoubleNodeBinary(void* node);
void** getAddrRightPVoidNodeBinary(void* node);
void** getAddrRightPVoidWithDataNodeBinary(void* node);
void** getAddrRightFixArrAvlNd(void* node);
void** getAddrRightFixArrAvlNd_NBin(void* node);
/* get Node key */
void* (*getKeyBinaryFn(const int opCode))(void*);
void* getKeyIntNodeBinary(void* node);
void* getKeyUIntNodeBinary(void* node);
void* getKeyCharNodeBinary(void* node);
void* getKeyUCharNodeBinary(void* node);
void* getKeyShortNodeBinary(void* node);
void* getKeyUShortNodeBinary(void* node);
void* getKeyLIntNodeBinary(void* node);
void* getKeyULIntNodeBinary(void* node);
void* getKeyLLIntNodeBinary(void* node);
void* getKeyULLIntNodeBinary(void* node);
void* getKeyFloatNodeBinary(void* node);
void* getKeyDoubleNodeBinary(void* node);
void* getKeyLDoubleNodeBinary(void* node);
void* getKeyPVoidNodeBinary(void* node);
void* getKeyPVoidWithDataNodeBinary(void* node);
void* getKeyFixArrAvlTNode(void* node);
void* getKeyFixArrAvlTNode_NBin(void* node);

/* get Node left */
void* (*getNodeLeftBinaryFn(const int opCode))(void*);
void* getLeftIntNodeBinary(void* node);
void* getLeftUIntNodeBinary(void* node);
void* getLeftCharNodeBinary(void* node);
void* getLeftUCharNodeBinary(void* node);
void* getLeftShortNodeBinary(void* node);
void* getLeftUShortNodeBinary(void* node);
void* getLeftLIntNodeBinary(void* node);
void* getLeftULIntNodeBinary(void* node);
void* getLeftLLIntNodeBinary(void* node);
void* getLeftULLIntNodeBinary(void* node);
void* getLeftFloatNodeBinary(void* node);
void* getLeftDoubleNodeBinary(void* node);
void* getLeftLDoubleNodeBinary(void* node);
void* getLeftPVoidNodeBinary(void* node);
void* getLeftPVoidWithDataNodeBinary(void* node);
void* getLeftFixArrAvlTNode(void* node);
void* getLeftFixArrAvlTNode_NBin(void* node);

/* get Node right */
void* (*getNodeRightBinaryFn(const int opCode))(void*);
void* getRightIntNodeBinary(void* node);
void* getRightUIntNodeBinary(void* node);
void* getRightCharNodeBinary(void* node);
void* getRightUCharNodeBinary(void* node);
void* getRightShortNodeBinary(void* node);
void* getRightUShortNodeBinary(void* node);
void* getRightLIntNodeBinary(void* node);
void* getRightULIntNodeBinary(void* node);
void* getRightLLIntNodeBinary(void* node);
void* getRightULLIntNodeBinary(void* node);
void* getRightFloatNodeBinary(void* node);
void* getRightDoubleNodeBinary(void* node);
void* getRightLDoubleNodeBinary(void* node);
void* getRightPVoidNodeBinary(void* node);
void* getRightPVoidWithDataNodeBinary(void* node);
void* getRightFixArrAvlTNode(void* node);
void* getRightFixArrAvlTNode_NBin(void* node);
/*clear tree*/
void clearBinaryTree(binaryTree* bin);
void clearANodeBinary(binaryTree* bin,void* node);
/* delete and clear tree */

/* node function */
int (*getConstructNodeBinaryFn(const int opCode))(void*);
int constructIntNodeBinary(void* node);
int constructUIntNodeBinary(void* node);
int constructCharNodeBinary(void* node);
int constructUCharNodeBinary(void* node);
int constructShortNodeBinary(void* node);
int constructUShortNodeBinary(void* node);
int constructLIntNodeBinary(void* node);
int constructULIntNodeBinary(void* node);
int constructLLIntNodeBinary(void* node);
int constructULLIntNodeBinary(void* node);
int constructFloatNodeBinary(void* node);
int constructDoubleNodeBinary(void* node);
int constructLDoubleNodeBinary(void* node);
int constructPVoidNodeBinary(void* node);
int constructPVoidWithDataNodeBinary(void* node);
int constructFixArrNodeBinary(void* node);
int constructFixArrNodeNBin_Bin(void* node);

/* inset function group */
void* (*getInsertDataType(const int opCode))(binaryTree*, const void*);
void* insertIntDataToBinaryTree(binaryTree* bin,const void* key);
void* insertUIntDataToBinaryTree(binaryTree* bin,const void* key);
void* insertCharDataToBinaryTree(binaryTree* bin,const void* key);
void* insertUCharDataToBinaryTree(binaryTree* bin,const void* key);
void* insertShortDataToBinaryTree(binaryTree* bin,const void* key);
void* insertUShortDataToBinaryTree(binaryTree* bin,const void* key);
void* insertLIntDataToBinaryTree(binaryTree* bin,const void* key);
void* insertULIntDataToBinaryTree(binaryTree* bin,const void* key);
void* insertLLIntDataToBinaryTree(binaryTree* bin,const void* key);
void* insertULLIntDataToBinaryTree(binaryTree* bin,const void* key);
void* insertFloatDataToBinaryTree(binaryTree* bin,const void* key);
void* insertDoubleDataToBinaryTree(binaryTree* bin,const void* key);
void* insertLDoubleDataToBinaryTree(binaryTree* bin,const void* key);
void* insertPVoidToBinaryTree(binaryTree* bin,const void* key);
void* insertPVoidWithDataToBinaryTree(binaryTree* bin,const void* key);
/* search function */
void* searchDataInBinaryTree(binaryTree* bin,const void* key);

void* searchDataInBinaryTreeWithOpt(binaryTree* bin,void *opt,const void* key);

/* delete Node function */

int deleteNodeDataInBinaryTree(struct binaryTree *bin,void** node);
int deleteKeyOfNodeDataInBinaryTree(binaryTree* bin,const void* key); 

int heightDataNodeBinary(binaryTree* bin,void* node);

void (*printBinaryTree(const int opCode))(binaryTree*,char style);
void printIntDataInBinaryTree(binaryTree* bin,char style);
void printUIntDataInBinaryTree(binaryTree* bin,char style);
void printCharDataInBinaryTree(binaryTree* bin,char style);
void printUCharDataInBinaryTree(binaryTree* bin,char style);
void printShortDataInBinaryTree(binaryTree* bin,char style);
void printUShortDataInBinaryTree(binaryTree* bin,char style);
void printLIntDataInBinaryTree(binaryTree* bin,char style);
void printULIntDataInBinaryTree(binaryTree* bin,char style);
void printLLIntDataInBinaryTree(binaryTree* bin,char style);
void printULLIntDataInBinaryTree(binaryTree* bin,char style);
void printFloatDataInBinaryTree(binaryTree* bin,char style);
void printDoubleDataInBinaryTree(binaryTree* bin,char style);
void printLDoubleDataInBinaryTree(binaryTree* bin,char style);
void printPVoidDataInBinaryTree(binaryTree* bin,char style);
void printVDoubleInBinaryTree(binaryTree* bin,char style);
void printSimStrInBinaryTree(binaryTree* bin,char style);
void printPVoidWithDataInBinaryTree(binaryTree* bin,char style);
void printFixArrNodeBinaryT(binaryTree* bin,char style);
void printFixArrNodeBinaryT_NBin(binaryTree* bin,char style);


void printIntDataInNode(nodeBinaryInt* node,int high);
void printUIntDataInNode(nodeBinaryUInt* node,int high);
void printCharDataInNode(nodeBinaryChar* node,int high);
void printUCharDataInNode(nodeBinaryUChar* node,int high);
void printShortDataInNode(nodeBinaryShort* node,int high);
void printUShortDataInNode(nodeBinaryUShort* node,int high);
void printLIntDataInNode(nodeBinaryLInt* node,int high);
void printULIntDataInNode(nodeBinaryULInt* node,int high);
void printLLIntDataInNode(nodeBinaryLLInt* node,int high);
void printULLIntDataInNode(nodeBinaryULLInt* node,int high);
void printFloatDataInNode(nodeBinaryFloat* node,int high);
void printDoubleDataInNode(nodeBinaryDouble* node,int high);
void printVDoubleDataInNode(nodeBinaryPVoid* node,int high);
void printSimStrDataInNode(nodeBinaryPVoid* node,int high);
void printLDoubleDataInNode(nodeBinaryLDouble* node,int high);
void printPVoidDataInNode(binaryTree* bin,nodeBinaryPVoid* node,int high);
void printPVoidWithDataInNode(binaryTree* bin,nodeBinaryPVoidWithData* node,int high);
void printFixArrNodeBinaryNode(binaryTree* bin,void* node,int high);
void printFixArrNodeBinaryNode_NBin(binaryTree* bin,void* node,int high);

/* swap value of node  */
void (*swapValueOfNodeBinaryFn(const int opCode))(void*,void*);
void swapValueOfIntNodeBinary(void* node,void* node2);
void swapValueOfUIntNodeBinary(void* node,void* node2);
void swapValueOfCharNodeBinary(void* node,void* node2);
void swapValueOfUCharNodeBinary(void* node,void* node2);
void swapValueOfShortNodeBinary(void* node,void* node2);
void swapValueOfUShortNodeBinary(void* node,void* node2);
void swapValueOfLIntNodeBinary(void* node,void* node2);
void swapValueOfULIntNodeBinary(void* node,void* node2);
void swapValueOfLLIntNodeBinary(void* node,void* node2);
void swapValueOfULLIntNodeBinary(void* node,void* node2);
void swapValueOfFloatNodeBinary(void* node,void* node2);
void swapValueOfDoubleNodeBinary(void* node,void* node2);
void swapValueOfLDoubleNodeBinary(void* node,void* node2);
void swapValueOfPVoidNodeBinary(void* node,void* node2);
void swapValueOfPVoidWithDataNodeBinary(void* node,void* node2);
/* delete key and data */

void (*getDeleteKeyFn(const int opCode))(void*,void*);
void deleteVectorDoubleKey(void *obj,void *key);
void deleteSimStrKey(void *obj,void *key);
void (*deleteDataOrKeyOfNodeBinaryFn(const int opCode))(void*,void*);
void deleteDataOrKeyOfPVoidNodeBinary(void* node,void* node2);\

/*  tree traversals*/ /* return node*/
void* traversalTBin(binaryTree *bin,int limit,int opt);
void* inOrderTranverseTBin(binaryTree *bin,int limit);
void* preOrderTranverseTBin(binaryTree *bin,int limit);
void* postOrderTranverseTBin(binaryTree *bin,int limit);
#endif
