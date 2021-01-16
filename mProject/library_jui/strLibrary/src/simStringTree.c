/********************************************************************/
/*
      FILE     :   simStringTree.c
      Name     :   Chalearm Saelim
      Date     :   24 April 2016 15:45
      Email    :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose  :   It is definition part of simStringTree.h
     Description :   This structure is based on the AVL tree which supports keeping and fast accessing 

     Dependency:   We use the included library as below 
                    #include "simStringTree.h"
  How to compile:   - Not update -
*/
/*******************************************************************/
 
#include "simStringTree.h"

int initialSimStrT(simStrTree *obj,void (*delData)(void*,void*),void (*copyDataValue)(void*,void*))
{
    int ret =0;
    if(obj!=NULL)
    {
        ret =1;
        constructAvlTree((void*)&(obj->m_root),1,"custom type 2",sizeof(void*),sizeof(simString));
        setDelKeyAndDelDataAndCompFnForAvlTree(&(obj->m_root),delSimStrKeyInSimStrTree,delData,compSimStrEleInSimStrTree); 
        obj->m_root.printKeyPVoid = &printKeyOfSimStrT;
        obj->m_root.copyKeyValue = &copyKeySimStrTree;
        obj->m_root.copyDataValue = copyDataValue;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
void destructorSimStrT(simStrTree *obj)
{
    if(obj!=NULL)
    {
        clearBinaryTree(&(obj->m_root));
    }
    else
    {
        /* do nothing */
    }
}
int addELeSimStrTFromVChar(simStrTree *obj,vector_char *vch,void *val)
{
    int ret =(obj!=NULL)&&(vch!=NULL);
    struct simString *simStr=NULL;
    void *node=NULL;
    if(ret==1)
    {
        simStr = (struct simString*)malloc(sizeof(struct simString));
        ret = (simStr!=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(ret==1)
    {
        initialSimString(simStr);
        convertVectorChar2SimString(simStr,vch);
        node = obj->m_root.insertFn(&(obj->m_root),&simStr);
        ret = (node!=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(ret==1)
    {
        setDataToAvlNode(node,&val);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int addELeSimStrT(simStrTree *obj,simString *str,void *val)
{
    int ret =(obj!=NULL)&&(str!=NULL);
    struct simString *simStr=NULL;
    void *node=NULL;
    if(ret==1)
    {
        simStr = (struct simString*)malloc(sizeof(struct simString));
        ret = (simStr!=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(ret==1)
    {
        initialSimString(simStr);
        copySimStr(simStr,str);
        node = obj->m_root.insertFn(&(obj->m_root),&simStr);
        ret = (node!=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(ret==1)
    {
        setDataToAvlNode(node,&val);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int addELeSimStrTFromCStr(simStrTree *obj,const char* str,void *val)
{
    int ret =(obj!=NULL)&&(str!=NULL);
    struct simString *simStr=NULL;
    void *node=NULL;
    if(ret==1)
    {
        simStr = (struct simString*)malloc(sizeof(struct simString));
        ret = (simStr!=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(ret==1)
    {
        initialSimString(simStr);
        convertCString2SimString(simStr,str);
        node = obj->m_root.insertFn(&(obj->m_root),&simStr);
        ret = (node!=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(ret==1)
    {
        setDataToAvlNode(node,&val);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
void printSimStrT(simStrTree *obj)
{
    char buff[200];
    if(obj!=NULL)
    {
        obj->m_root.parameter3 = &buff;
        obj->m_root.printTree(&(obj->m_root),0);
    }
    else
    {
        /* do nothing */
    }
}
int getNumEleSimStrT(simStrTree *obj)
{
    int ret=-1;
    if(obj!=NULL)
    {
        ret = getNumBinaryNodeOfTree(&(obj->m_root));
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
void* search2GetValueInSimStrTByCstr(simStrTree *obj,const char *cstr)
{
    void *val =NULL;
    void *node=NULL;
    binaryTree *pt =NULL;
    simString simS1;
    simString *pSimS =NULL;
    if((obj!=NULL)&&(cstr!=NULL))
    {
        pt = &(obj->m_root);
        pSimS = &simS1;
        initialSimString(pSimS);
        convertCString2SimString(pSimS,cstr);
        node = searchDataInBinaryTree(pt,&pSimS);
        val = getDataFromAvlNode(node);
        destructSimString(pSimS);
    }
    else
    {
        /* do nothing */
    }
    return val;
}
void* search2GetValueInSimStrTByVChar(simStrTree *obj,vector_char *vch)
{
    void *val =NULL;
    void *node=NULL;
    binaryTree *pt =NULL;
    simString simS1;
    simString *pSimS =NULL;
    if((obj!=NULL)&&(vch!=NULL))
    {
        pt = &(obj->m_root);
        pSimS = &simS1;
        initialSimString(pSimS);
        convertVectorChar2SimString(pSimS,vch);
        node = searchDataInBinaryTree(pt,&pSimS);
        val = getDataFromAvlNode(node);
        destructSimString(pSimS);
    }
    else
    {
        /* do nothing */
    }
    return val;
}
void* search2GetValueInSimStrTBySimStr(simStrTree *obj,simString *simStr)
{
    void *val =NULL;
    void *node=NULL;
    binaryTree *pt =NULL; 
    if((obj!=NULL)&&(simStr!=NULL))
    {
        pt = &(obj->m_root);
        node = searchDataInBinaryTree(pt,&simStr);
        val = getDataFromAvlNode(node);
    }
    else
    {
        /* do nothing */
    }
    return val;
}
int deleteEleSimStrTByCStr(simStrTree *obj,const char *cstr)
{
    int ret =0;
    binaryTree *pt =NULL;
    simString simS1;
    simString *pSimS =NULL;
    if((obj!=NULL)&&(cstr!=NULL))
    {
        pt = &(obj->m_root);
        pSimS = &simS1;
        initialSimString(pSimS);
        convertCString2SimString(pSimS,cstr);
        ret = pt->deleteNodeByKey(pt,&pSimS);
        destructSimString(pSimS);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int deleteEleSimStrTBySimStr(simStrTree *obj,simString *simStr)
{
    int ret =0;
    binaryTree *pt =NULL;
    if((obj!=NULL)&&(simStr!=NULL))
    {
        pt = &(obj->m_root); 
        ret = pt->deleteNodeByKey(pt,&simStr); 
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int deleteEleSimStrTByVChar(simStrTree *obj,vector_char *vch)
{
    int ret =0;
    binaryTree *pt =NULL;
    simString simS1;
    simString *pSimS =NULL;
    if((obj!=NULL)&&(vch!=NULL))
    {
        pt = &(obj->m_root);
        pSimS = &simS1;
        initialSimString(pSimS);
        convertVectorChar2SimString(pSimS,vch);
        ret = pt->deleteNodeByKey(pt,&pSimS);
        destructSimString(pSimS);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
/*
int compareSimStrList(simStrTree *oLsh,simStrTree *oRsh); 
*/

int copySimStrTree(simStrTree *oLsh,simStrTree *oRsh)
{
    int res = (oLsh!=NULL)&&(oLsh!=oRsh)&&(oRsh!=NULL);
    if(res==1)
    {
        destructorSimStrT(oLsh);
        assignOperatorBinTree(&(oLsh->m_root),&(oRsh->m_root));
    }
    else
    {
        /* do nothing */
    }
    /* start copy */
    if(res==1)
    {
    }
    else
    {
        /* do nothing */
    }
    return res;
}
void* copyKeySimStrTree(binaryTree *obj,void *node)
{
    simString *simStrTemp = NULL;
    simString *simStrTemp2 = NULL;
    void *node2 =NULL;
    if((obj!=NULL)&&(node!=NULL))
    {
        simStrTemp2 = (simString*)malloc(sizeof(simString));
        initialSimString(simStrTemp2);
        simStrTemp= *((simString**)getKeyPVoidNodeBinary(node));
        copySimStr(simStrTemp2,simStrTemp);
        node2 = obj->insertFn(obj,&simStrTemp2);
    }
    else
    {
        /* do nothing */
    }
    return node2;
}
int compSimStrEleInSimStrTree(const void* a,const void *b)
{
    int res =UN_DEFINE;
    int index =0;
    int num =0;
    simString *sa=NULL,*sb=NULL;
    if((a!=NULL)&&(b!=NULL))
    {
        sa = *((simString**)a);
        sb = *((simString**)b);
        if(sa->length > sb->length)
        {
            num = sb->length;
        }
        else
        {
            num = sa->length;
        }
        res =EQUAL_DEFINE;
        for(index=0;index<num;index++)
        {
            if(sa->data[index]> sb->data[index])
            {
                index=num;
                res = MORE_DEFINE;
            }
            else if(sa->data[index]< sb->data[index])
            {
                index=num;
                res = LESS_DEFINE;
            }
            else
            {
                /* do nothing */
            }
        }
        if((res ==EQUAL_DEFINE)&&(sa->length == num)&&(sb->length>num))
        {
            res = LESS_DEFINE;
        } 
        else if((res ==EQUAL_DEFINE)&&(sb->length == num)&&(sa->length>num))
        {
            res = MORE_DEFINE;
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}
void delSimStrKeyInSimStrTree(void *obj,void *key)
{
    struct simString **pStr = (struct simString**)key;
    if(pStr !=NULL)
    {
        if(*pStr!=NULL)
        {
            destructSimString(*pStr);
            free(*pStr);
        }
        else
        {
            /* do nothing */
        }
        *pStr = NULL;
    }
    else
    {
        /* do nothing */
    }
}
void printKeyOfSimStrT(void *key,char *buff) /* with address*/
{
    simString *simS=NULL;
    if((key!=NULL)&&(buff!=NULL))
    {
        simS = (simString*)key;
        if(simS->length == 0)
        {
            return;
        }
        else
        {
            sprintf(buff,"%s ",simS->data);
        } 
    }
    else
    {
        /* do nothing */
    }
}