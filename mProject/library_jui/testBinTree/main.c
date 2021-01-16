#include <stdio.h>
#include "binaryTree.h"
void treeEmpty(binaryTree* bin);


int main(int argc,char** argv)
{
    int num=22;
    int i =0;
    double aa[] ={28,35,20,15,26,30,37,4,16,24,27,26.78,33,39,38.43,54,2,1,0,7,43,34};  
    double bb = 2343.32432;
    printf(" hello world \n");
    binaryTree btData;
    constructorBinaryTree3(&btData,"double",0,0);
    printBinTree(&btData);
    setFunctionOfBinaryTree(&btData);
    if(btData.compareType!=NULL)
    printf("%d\n",btData.compareType(&bb,&aa));
    for(i=0;i<num;i++)
    {
       btData.insertFn(&btData,&aa[i]);
    }
    btData.printTree(&btData,0);
    bb = 16;
    deleteKeyOfNodeDataInBinaryTree(&btData,&bb);
    btData.printTree(&btData,0);
    bb = 35;
    deleteKeyOfNodeDataInBinaryTree(&btData,&bb);
    btData.printTree(&btData,0);
    bb = 28;
    deleteKeyOfNodeDataInBinaryTree(&btData,&bb);    
    btData.printTree(&btData,0);
    bb = 39;
    deleteKeyOfNodeDataInBinaryTree(&btData,&bb);
    btData.printTree(&btData,0);
    bb = 0;
    deleteKeyOfNodeDataInBinaryTree(&btData,&bb);
    btData.printTree(&btData,0);
    bb = 27;
    deleteKeyOfNodeDataInBinaryTree(&btData,&bb);
    btData.printTree(&btData,0);
    bb = 54;
    deleteKeyOfNodeDataInBinaryTree(&btData,&bb);
    btData.printTree(&btData,0);
    treeEmpty(&btData);
    clearBinaryTree(&btData);
    return 0;
}



void treeEmpty(binaryTree* bin)
{
    int res = isEmptyOfBinaryTree(bin);
    if(res ==1)
    {
        printf("Tree is empty\n");
    }
    else
    {
        printf("Tree is %d nodes\n",getNumBinaryNodeOfTree(bin));
    }
}
