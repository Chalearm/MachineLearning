#ifndef AVLTREE_H_
#define AVLTREE_H_
#include <stdio.h>
#include <stdlib.h>
#include "listPvoid.h"
#include "binaryTree.h"

struct avlData
{
    int height;
    void* data;
};
typedef struct avlData avlData;
void deleteHeightAvlTreeWithNodata(void *obj,void *data);
void deleteHeightAvlTreeWithNodataDebug(void *obj,void *data);

void deleteAvlDataStruct(binaryTree* avlTree,void *node);
int setDataToAvlNode(void *node,const void* data);
void *getDataFromAvlNode(void *node);
void printAddrOfNodeAtLvAvlT(binaryTree* avlTree,void *node,int depth); 
void printNodeTonDepth(binaryTree* avlTree,void *node,int depth); 
/*
 update to application
void deleteDataAvlTreeWithdata(void* node);
*/
/*No data --: delData is NULL*/
int validateConfigIsOk(binaryTree* avlTree);
void setDelKeyFnForAvlTree(binaryTree* avlTree,void (*delKey)(void*,void*));
void setDelKeyAndDelDataAndCompFnForAvlTree(binaryTree* avlTree,void (*delKey)(void*,void*),void (*delData)(void*,void*),int (*compareType)(const void*,const void*));
void constructAvlTree(void *avlT,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey);
void* insertAvlTreeData(binaryTree* avlTree,const void* key); /* validate compare fn and call insertAvlTreeData2 */
void* insertAvlTreeNoData(binaryTree* avlTree,void** node,const void* key);
void* insertAvlTreeData2(binaryTree* avlTree,void** node,const void* key); 

void* insertAvlT4FixArrNodeBuiltIn(binaryTree* avlTree,const void* key); 
void* insertAvlTreeData3(binaryTree* avlTree,void** node,const void* key);

void* insertAvlT4FixArrNodeNoBuiltIn(binaryTree* avlTree,const void* key); 
void* insertAvlTreeData4(binaryTree* avlTree,void** node,const void* key); 

void* deleteKeyOfAvlNode(binaryTree* avlTree,void* key);
int getHeightAVLNodeWithData(binaryTree* avlTree,void* node);
int getHeightAVLNodeWithNoData(binaryTree* avlTree,void* node);
int getHeightAVLFixArrNode(binaryTree* avlTree,void* node);
int getHeightAVLFixArrNode_NBIn(binaryTree* avlTree,void* node);
int adjustHeightAVLNodeNoData(binaryTree* avlTree,void* node);
int adjustHeightAVLNode(binaryTree* avlTree,void* node);
int adjustHeightAVLNodeFixArr(binaryTree* avlTree,void* node);
int adjustHeightAVLNodeFixArr_NBin(binaryTree* avlTree,void* node);


void swapValOfAvlTFArrNode(void* node,void* node2);
void swapValOfAvlTFArrNode_NBin(void* node,void* node2);
void swapValueOfAvlTreeNodeWithData(void* node,void* node2);
void swapValueOfAvlTreeNodeWithNoData(void* node,void* node2);

/* private method, use for internal method only */
void* swap_and_remove_left_neighbourForAvlTreeNode(binaryTree *avlTree,void* parent,void* chlid);
void* removeNodeForAvlTree(binaryTree *avlTree,void* root);
int removeRecForAvlTree(binaryTree *avlTree,void* root,const void *key);

/* Dangerous method */
int forcetTRoot2NullAvLT(binaryTree *avlTree);

int removeAvlTreeNodeByKey(binaryTree *avlTree,const void *key);
int removeAvlTreeNodeByKey4FixArr2(binaryTree *avlTree,const void *key);
/* public method*/

/* private method */
int deleteNodeAvlNodeWithData(binaryTree* avlTree,void** node);
int delNdFxArrAvlNd(binaryTree* avlTree,void** node);
int deleteNodeAvlNodeWithNoData(binaryTree* avlTree,void** node);
int deleteNodeAvlNodeWithNoDataDebug(binaryTree* avlTree,void** node);
void clearANodeAvlTree(binaryTree* avlTree,void* node);
void clearANodeAvlTreeWithData(binaryTree* avlTree,void* node);
void clearANodeAvlTFixArr(binaryTree* avlTree,void* node);
/*
  Example use of rotate_LL
parent . left ← rotate_LL ( parent . left)
parent . right ← rotate_LL ( parent . right)

*/
int getHeightLL(binaryTree* avlTree,nodeBinaryPVoidWithData* root);
int getHeightLR(binaryTree* avlTree,nodeBinaryPVoidWithData* root);
int getHeightRR(binaryTree* avlTree,nodeBinaryPVoidWithData* root);
int getHeightRL(binaryTree* avlTree,nodeBinaryPVoidWithData* root);

void* reblanceForRemoveNodeAvlTree(binaryTree *avlTree,void *root);
void* rotate_LL(binaryTree* avlTree,void** node);
void* rotate_RR(binaryTree* avlTree,void** node);
void* rotate_LR(binaryTree* avlTree,void** node);
void* rotate_RL(binaryTree* avlTree,void** node);

#endif /* AVLTREE_H_ */