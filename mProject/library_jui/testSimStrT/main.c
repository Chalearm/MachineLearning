#include <stdio.h>
#include <stdlib.h>
#include "simStringTree.h" 
void* newValueInt(int a);
void delDataOfSim(void *val);
void copyIntDatOfSimT(void *nodeL,void *nodeR);
void searchTheWordInSimStrT(simStrTree *obj,const char* str);
void addDataToSimTByCstr(simStrTree *obj,const char* str,int val);
void addDataToSimTByVchar(simStrTree *obj,vector_char *vchar,int val);
int main(int argc,char** argv)
{
    vector_char vStr;
    simString simStr1;
    simStrTree simStrT;
    simStrTree simStrT2;
    initialSimStrT(&simStrT,delDataOfSim,copyIntDatOfSimT);
    initialSimStrT(&simStrT2,delDataOfSim,copyIntDatOfSimT);
    printf("Hello jui\n");
    initialSimString(&simStr1);
    vStr=new_vector_char(0);

    convertCString2SimString(&simStr1,"Chalearm33");
    convertSimString2VectorChar(&vStr,&simStr1);
    addDataToSimTByCstr(&simStrT,"juiLove",5);
    addDataToSimTByCstr(&simStrT,"AjuiLove",4);
    addDataToSimTByCstr(&simStrT,"CjuiLove",12);
    addDataToSimTByCstr(&simStrT,"DjudfdLove",127);
    addDataToSimTByCstr(&simStrT,"BjuiLove",9);
    addDataToSimTByVchar(&simStrT,&vStr,192);
    printSimStrT(&simStrT);
    printf("Copy Tree \n");
    copySimStrTree(&simStrT2,&simStrT);
    printSimStrT(&simStrT2);
    searchTheWordInSimStrT(&simStrT,"DjudfdLove");
    searchTheWordInSimStrT(&simStrT,"DjudfdLovde");
    searchTheWordInSimStrT(&simStrT,"Chalearm33");
    printf("-------- Search words from copying tree -------------\n");
    searchTheWordInSimStrT(&simStrT2,"DjudfdLove");
    searchTheWordInSimStrT(&simStrT2,"DjudfdLovde");
    searchTheWordInSimStrT(&simStrT2,"Chalearm33");
    destructorSimStrT(&simStrT);
    destructorSimStrT(&simStrT2);
    delete_vector_char(&vStr);
    destructSimString(&simStr1); 
    return 0;
}
void delDataOfSim(void *val)
{
    int **pi = (int**)val;
    if(pi == NULL)
    {
        /* do nothing */
    }
    else if(*pi !=NULL)
    {
        free(*pi);
        *pi = NULL;
    }
    else
    {
        /* do nothing */
    }
}

void* newValueInt(int a)
{
    int *pI = (int*)malloc(sizeof(int));
    *pI = a;
    return (void*)pI;
}

void copyIntDatOfSimT(void *nodeL,void *nodeR)
{
    int *pInt =NULL;
    void *pI1=NULL;
    if((nodeL!=NULL)&&(nodeR!=NULL))
    {
        pInt = (int*)getDataFromAvlNode(nodeR);
        pI1 =newValueInt(*pInt);
        setDataToAvlNode(nodeL,&pI1);
    }
    else
    {
        /* do nothing*/
    }
}
void addDataToSimTByCstr(simStrTree *obj,const char* str,int val)
{
    void *pI1=NULL;
    pI1 =newValueInt(val);
    addELeSimStrTFromCStr(obj,str,pI1);
}
void addDataToSimTByVchar(simStrTree *obj,vector_char *vchar,int val)
{
    void *pI1=NULL;
    pI1 =newValueInt(val);
    addELeSimStrTFromVChar(obj,vchar,pI1);
}
void searchTheWordInSimStrT(simStrTree *obj,const char* str)
{
    int *pI3=NULL;
    printf("Search Word : %s \n",str);
    pI3 = (int*)search2GetValueInSimStrTByCstr(obj,str);
    if(pI3 !=NULL)
    {
        printf("Result : %d\n",*pI3);
    }
    else
    {
        printf("Not found : %s in the tree\n",str);
    }
}