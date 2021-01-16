#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"
#define NODATA 0
void treeEmpty(binaryTree* bin);
void deleteKeyNodeForAvlTree(void *obj,void *key);
void printKeyAvlTree(void* key,char* bufff);
void addData(binaryTree* tree,unsigned int key);
void removeData(binaryTree* tree,unsigned int key);
int main(int argc,char** argv)
{
    unsigned int i = 0;
    unsigned int *pVal = NULL;
    binaryTree avlTree;
    printf("jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj\n");
    constructAvlTree((void*)&avlTree,NODATA,"unsigned int",0,sizeof(unsigned int)); 
    setDelKeyAndDelDataAndCompFnForAvlTree(&avlTree,deleteKeyNodeForAvlTree,NULL,NULL);
    avlTree.printKeyPVoid = printKeyAvlTree;
    for(i=0;i<8;i++) /* it can be 3,000,000*/
    {
        pVal = (unsigned int*)malloc(sizeof(unsigned int));
        *pVal = i;
         avlTree.insertFn(&avlTree,&pVal);
    }
   
    avlTree.printTree(&avlTree,0);
    printf("------Start Delete 0,1,2------%d \n",avlTree.getNodeHeight(&avlTree,avlTree.root));
    removeData(&avlTree,0);
    removeData(&avlTree,1);
    removeData(&avlTree,2);
    addData(&avlTree,8);
    removeData(&avlTree,3);
    removeData(&avlTree,8);
    removeData(&avlTree,5);
    addData(&avlTree,9);
    addData(&avlTree,5);
    removeData(&avlTree,7);
    removeData(&avlTree,6);
    addData(&avlTree,0);
    addData(&avlTree,3);
    addData(&avlTree,11);
    addData(&avlTree,18);
    addData(&avlTree,15);
    removeData(&avlTree,5);
    addData(&avlTree,25);
    addData(&avlTree,22);
    addData(&avlTree,10);
    addData(&avlTree,23);
    addData(&avlTree,8);
    addData(&avlTree,2);
    removeData(&avlTree,11);
    
    removeData(&avlTree,0);
    removeData(&avlTree,3);
    removeData(&avlTree,8);
    removeData(&avlTree,9);
    removeData(&avlTree,2);
    removeData(&avlTree,4);
    removeData(&avlTree,15);
    removeData(&avlTree,10);
    removeData(&avlTree,22);
    removeData(&avlTree,23);
    addData(&avlTree,26);
    removeData(&avlTree,18);
    removeData(&avlTree,26);
    removeData(&avlTree,25);
 printf("please wait for nodes created more than a million\n");

    for(i=500000;i<1000000;i++) 
    {
        pVal = (unsigned int*)malloc(sizeof(unsigned int));
        *pVal = i;
         avlTree.insertFn(&avlTree,&pVal);
         
    }
    for(i=2000000;i>1000000;i--) 
    {
        pVal = (unsigned int*)malloc(sizeof(unsigned int));
        *pVal = i;
         avlTree.insertFn(&avlTree,&pVal);
         
    } 
    for(i=0;i<500000;i++) 
    {
        pVal = (unsigned int*)malloc(sizeof(unsigned int));
        *pVal = i;
         avlTree.insertFn(&avlTree,&pVal);
         
    }   
    for(i=0;i<2000000;i++)
    {
        if(i%2 ==0)
        avlTree.deleteNodeByKey(&avlTree,&i); 
    }   
    for(i=2000001;i<5000001;i++) 
    {
        pVal = (unsigned int*)malloc(sizeof(unsigned int));
        *pVal = i;
         avlTree.insertFn(&avlTree,&pVal);
         
    }     
   printf("root:%p %d\n",avlTree.root,avlTree.getNodeHeight(&avlTree,avlTree.root));
    clearBinaryTree(&avlTree);
    return 0;
}
void removeData(binaryTree* tree,unsigned int key)
{
    tree->deleteNodeByKey(tree,&key); 
    tree->printTree(tree,0);
    printf("---------------- %d \n",tree->getNodeHeight(tree,tree->root));
}
void addData(binaryTree* tree,unsigned int key)
{
    unsigned int *pVal = (unsigned int*)malloc(sizeof(unsigned int));
   *pVal = key;
    tree->insertFn(tree,&pVal);
    tree->printTree(tree,0);
    printf("----------------%d \n",tree->getNodeHeight(tree,tree->root));   
}
void printKeyAvlTree(void* key,char* buff)
{
    if((key != NULL )&&(buff != NULL))
    {
        sprintf(buff,"%u",*((unsigned int*)key));
    }
    else
    {
        /* do nothing */
    }
}
void deleteKeyNodeForAvlTree(void *obj,void *key)
{
    void **p = (void**)key;
    if(*p!=NULL)
    {
        free(*p);
    }
    else
    {
        /* do nothing */
    }
}
