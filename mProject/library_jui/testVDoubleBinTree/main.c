#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"
void insertVDoubleToTree(binaryTree* t,double* arr,int size);

int main(int argc,char** argv)
{ 
    binaryTree bT;
    double a1[] = {0,1};
    double a2[] = {0,2};
    double a3[] = {0,3};
    double a4[] = {0,4};
    double a5[] = {1,0};
    double a6[] = {1,1};
    double a7[] = {1,2};
    double a8[] = {1,3};
    double a9[] = {1,4};
    double a10[] = {0,2.5};
    double a11[] = {1,3,1};
    double a12[] = {2,0};
    constructorBinaryTree3(&bT,"vector_double",0,sizeof(vector_double));
    setFunctionOfBinaryTree(&bT);
    insertVDoubleToTree(&bT,a1,2);
    insertVDoubleToTree(&bT,a2,2);
    insertVDoubleToTree(&bT,a3,2);
    insertVDoubleToTree(&bT,a4,2);
    insertVDoubleToTree(&bT,a5,2);
    insertVDoubleToTree(&bT,a6,2);
    insertVDoubleToTree(&bT,a7,2);
    insertVDoubleToTree(&bT,a8,2);
    insertVDoubleToTree(&bT,a9,2);
    insertVDoubleToTree(&bT,a10,2);
    insertVDoubleToTree(&bT,a11,3);
    insertVDoubleToTree(&bT,a12,2);
    bT.printTree(&bT,0);
    clearBinaryTree(&bT);
    return 0;
}


void insertVDoubleToTree(binaryTree* t,double* arr,int size)
{
    int index=0;
    vector_double *p = NULL;
    void* result = NULL;
    if((t!=NULL)&&(arr!=NULL)&&(size>0))
    {
        p = (vector_double*)malloc(sizeof(vector_double));
        
    }
    else
    {
        /* do nothing */
    }
    if(p!=NULL)
    {
        *p = new_vector_double(size);
        for(index=0;index<size;index++)
        {
            p->data[index] = arr[index];
        }
        result = t->insertFn(t,&p);
    }
    else
    {
        printf("cannot allocate area to insert vector_double to the tree\n");
    }
    if((p!=NULL)&&(result==NULL))
    {            
        printf("failed to insert to tree\n");
        delete_vector_double(p);
        free(p);
    }
    else
    {
        /* do nothing */    
    }
}
