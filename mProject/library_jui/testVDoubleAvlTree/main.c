#include <stdio.h>
#include <stdlib.h>
#include "simMatDouble.h"
#include "avlTree.h"

void printKeyAvlTree(void* key,char* buff);
void insertTreeVDouble(binaryTree *tree,double* vect,int sizeArr);
int main(int argc,char** argv)
{
    char buff[100];
    double a1[] = {1,3.4,5};  /*size =3*/
    double a2[] = {-3333,3.4,5};    /*size =3*/
    double a3[] = {-2,3.4,5}; /*size =3*/
    double a4[] = {78,-2,3.4,5}; /*size =4*/
    double a5[] = {78,-2,3.4,34}; /*size =4*/
    double a6[] = {-3.4,3};    /*size =2*/
    double a7[] = {-2,3.4,-6}; /*size =3*/
    double a8[] = {1,2,3,4,5,6,7,8,9}; /*size =3*/
    double a9[] = {1,5.842,8.123};    /*size =3*/
    double a10[] = {-3.4,5.2};    /*size =2*/
    double a11[] = {-3.2,5.2};    /*size =2*/
    double a12[] = {-3.45,5.2};    /*size =2*/
    double a13[] = {0};    /*size =1*/
    double a14[] = {-0.22342,-213124.43};    /*size =2*/
    double a15[] = {9};    /*size =1*/
    double a16[] = {8};    /*size =1*/
    double a17[] = {7};    /*size =1*/
    double a18[] = {6};    /*size =1*/
    double a19[] = {5};    /*size =1*/
    binaryTree avlT;
    binaryTree avlT2;
    constructAvlTree((void*)&avlT,0,"vector_double",0,sizeof(vector_double));

    insertTreeVDouble(&avlT,a1,3);
    insertTreeVDouble(&avlT,a2,3);
    insertTreeVDouble(&avlT,a3,3);
    insertTreeVDouble(&avlT,a4,4);
    insertTreeVDouble(&avlT,a5,4);
    insertTreeVDouble(&avlT,a6,2);
    insertTreeVDouble(&avlT,a7,3);
    insertTreeVDouble(&avlT,a8,9);
    insertTreeVDouble(&avlT,a9,3);
    insertTreeVDouble(&avlT,a10,2);
    insertTreeVDouble(&avlT,a11,2);
    insertTreeVDouble(&avlT,a12,2);
    insertTreeVDouble(&avlT,a13,1);
    insertTreeVDouble(&avlT,a14,2);
    insertTreeVDouble(&avlT,a15,1);
    insertTreeVDouble(&avlT,a16,1);
    insertTreeVDouble(&avlT,a17,1);
    insertTreeVDouble(&avlT,a18,1);
    insertTreeVDouble(&avlT,a19,1);
    avlT.parameter3 = buff;
    avlT.printKeyPVoid = printKeyAvlTree;
    copyConstructorBinTree(&avlT2,&avlT);
    avlT2.parameter3 = buff;
    printf("num Node : %d\n",getNumBinaryNodeOfTree(&avlT));
    avlT.printTree(&avlT,0);
    printf("num Node : %d\n",getNumBinaryNodeOfTree(&avlT2));
    avlT2.printTree(&avlT2,0);
    clearBinaryTree(&avlT);
    clearBinaryTree(&avlT2);
    return 0;
}

void insertTreeVDouble(binaryTree *tree,double* vect,int sizeArr)
{
    int index=0;
    void *result = NULL;
    vector_double *pVectD = (vector_double*)malloc(sizeof(vector_double));
    if((pVectD!=NULL)&&(tree!=NULL)&&(vect!=NULL)&&(sizeArr>0))
    {
        *pVectD = new_vector_double(sizeArr);
        printf("inert:%p\n",pVectD);
        for(index=0;index<sizeArr;index++)
        {
            pVectD->data[index] = vect[index];
        }
        result = tree->insertFn(tree,&pVectD);
        if(result == NULL)
        {
            printf("failed to insert to tree\n");
            delete_vector_double(pVectD);
            free(pVectD);
        }
    }
    else
    {
        /* do nothing */
    }
}

void printKeyAvlTree(void* key,char* buff)
{
    int index = 0;
    vector_double *p = NULL;
    if((key!=NULL)&&(buff!=NULL))
    {
        p = (vector_double*)key;
        buff[0] = '[';
        buff[1] = '\0';
        for(index=0;index<p->lenght;index++)
        {
            sprintf(buff,"%s%f ",buff,(double)(p->data[index]));
        }
        sprintf(buff,"%s]",buff);
    }
    else
    {
        /* do nothing */
    }
}