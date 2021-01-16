#include "binaryTree.h"


void setDelKeyFlag(binaryTree* bin,char flags)
{
    if(bin!=NULL)
    {
        bin->isNotDelKey = (flags==1);
    }
    else
    {
        /* do nothing */
    }
}
int validateDataTypeOfBinaryTree(int type,int size,int sizeKey)
{
    int res = ((type >= 0x000)&&(type<=0x091))||(type==VDOUBLE_TYPE)||(type==SIMSTRING_TYPE)||(type ==CUS1_TYPE)||(type ==CUS2_TYPE);
    res = res&&((type <= 0x060)|((type>0x060)&&(sizeKey>0)));
    res = res&&(((type==0x0E0)&&(size>0))|(type!=0x0E0)); /*  0x0E0 custom type 2*/
    return res;
}

void setFunctionOfBinaryTree(binaryTree* bin)
{
    if(bin != NULL)
    {
        bin->compareType = getCompFn(bin->typeBT);
        bin->compareTypeWithOpt = NULL; /* use in specific application */
        bin->insertFn = getInsertDataType(bin->typeBT);
        bin->constructNodeDataType = getConstructNodeBinaryFn(bin->typeBT);
        bin->printTree = printBinaryTree(bin->typeBT);
        bin->getNodeAddrLeft = getAddrNodeLeftBinaryFn(bin->typeBT);
        bin->getNodeAddrRight = getAddrNodeRightBinaryFn(bin->typeBT);
        bin->getNodeLeft = getNodeLeftBinaryFn(bin->typeBT);
        bin->getNodeRight = getNodeRightBinaryFn(bin->typeBT);
        bin->getKey = getKeyBinaryFn(bin->typeBT);
        bin->swapValue = swapValueOfNodeBinaryFn(bin->typeBT);
        bin->getNodeHeight = heightDataNodeBinary;
        bin->deleteNode = deleteNodeDataInBinaryTree;
        bin->deleteKey =getDeleteKeyFn(bin->typeBT);
        bin->copyKeyValue = getCopyFnOfBin(bin->typeBT);
        bin->clearNodesBinaryTree = clearANodeBinary;
        bin->setNodeHeight = NULL; /* use in AVLTree */
        
   /* void (*deleteNodeByKey)(struct binaryTree*,const void*); // jui12*/
    }
    else
    {
        /* do nothing */
    }
}
int setDataTypeOfBinaryTree(binaryTree* bin,int type,int size,int sizeKey)
{
    int res =validateDataTypeOfBinaryTree(type,size,sizeKey);
    if((bin != NULL)&&(res==1))
    {
        bin->typeBT = type;
        bin->sizeData = size;
        bin->sizeKey = sizeKey;
        bin->isData = (type==0x0E0);/* 0x0E0 custom type 2*/
        if((type <=0x060)||(type==LLINT_TYPE)||(type==ULLINT_TYPE))
        {
            bin->sizeKey = getDataTypeSize(bin->typeBT);
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        res =0;
    }
    return res;
}

void nullAllMethodsOfBinTree(binaryTree *bin)
{
    if(bin!=NULL)
    {
        bin->insertFn = NULL;
        bin->compareType = NULL;
        bin->compareTypeWithOpt = NULL;
        bin->deleteData = NULL;
        bin->deleteKey = NULL;
        bin->deleteNodeByKey = NULL;
        bin->deleteNode = NULL;
        bin->printTree = NULL; 
        bin->getKey = NULL; 
        bin->getData = NULL; 
        bin->swapValue = NULL; 
        bin->clearNodesBinaryTree = NULL; 
        bin->constructNodeDataType = NULL;
        bin->getNodeAddrLeft = NULL; 
        bin->getNodeAddrRight = NULL; 
        bin->getNodeLeft = NULL; 
        bin->getNodeRight = NULL;
        bin->printDataPVoid = NULL; 
        bin->printKeyPVoid = NULL; 
        bin->getNodeHeight = NULL; 
        bin->setNodeHeight = NULL; /* use in AVLTree */
        bin->copyDataValue = NULL; 
        bin->copyKeyValue = NULL; 
    }
    else
    {
        /* do nothing */
    }
}
void constructorBinaryTree(binaryTree *bin)
{
    /* set default parameter */
    if(bin !=NULL)
    {
        /* type key ; int */
        bin->numNode =0;
        bin->root =NULL;
        bin->isPrint =0;
        bin->isNotDelKey =0;
        bin->parameter1 =NULL;
        bin->parameter2 =NULL;
        bin->parameter3 =NULL;
        bin->parameter4 =NULL;
        bin->parameter5 =NULL;
        nullAllMethodsOfBinTree(bin);
        bin->configRight = setDataTypeOfBinaryTree(bin,0x010,sizeof(int),sizeof(int));
    }
    else
    {
        /* do nothing */
    }
}

void constructorBinaryTree3(binaryTree *bin,const char* type,int size,int sizeKey)
{
    int typeData =0;
    if(bin !=NULL)
    {
        bin->numNode =0;
        bin->root =NULL;
        bin->isPrint =0;
        bin->isNotDelKey =0;
        bin->parameter1 =NULL;
        bin->parameter2 =NULL;
        bin->parameter3 =NULL;
        bin->parameter4 =NULL;
        bin->parameter5 =NULL;
        nullAllMethodsOfBinTree(bin);
        typeData = getDataTypeFromString(type);
        if(typeData==CUS2_TYPE)
        {
            bin->isData = 1;
        }
        else if(typeData==FIXED_ARR)
        {
            bin->isData = 2;
        }
        else if(typeData==FIXED_ARR_NBIN)
        {
            bin->isData = 3;
        }
        else
        {
            bin->isData = 0;
        }
        bin->configRight = setDataTypeOfBinaryTree(bin,typeData,size,sizeKey);
    }
    else
    {
        /* do nothing */
    }
}

void transverseCopyDataInTree(binaryTree *bLhs,void *node,int high)
{
    void *nodeRes =NULL;
    if((node!=NULL)&&(bLhs!=NULL))
    {
        if(high==0)
        {
            nodeRes =bLhs->copyKeyValue(bLhs,node);
            if(bLhs->copyDataValue!=NULL)
            {
                bLhs->copyDataValue(nodeRes,node);
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            transverseCopyDataInTree(bLhs,bLhs->getNodeLeft(node),high-1);
            transverseCopyDataInTree(bLhs,bLhs->getNodeRight(node),high-1);
        }
    }
    else
    {
        /* do nothign */
    }
}
void copyConstructorBinTree(binaryTree *bLhs,binaryTree *bRhs)
{
    int index=0;
    int num =0;
    int res = (bLhs!=NULL)&&(bRhs!=NULL)&&(bLhs!=bRhs);
    if(res ==1)
    {
        res = (bRhs->copyKeyValue !=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(res==1)
    {
        /*clearBinaryTree(bLhs);*/ /* this is for assign operator*/
        memcpy(bLhs,bRhs,sizeof(binaryTree));
        bLhs->parameter1=NULL;
        bLhs->parameter2=NULL;
        bLhs->parameter3=NULL;
        bLhs->parameter4 =NULL;
        bLhs->parameter5 =NULL;
        bLhs->root=NULL;
        bLhs->numNode=0;
        num = heightOfBinaryTree(bRhs)+1;
        for(index=0;index<num;index++)
        {
            transverseCopyDataInTree(bLhs,bRhs->root,index);
        }
    }
    else
    {
        /* do noting */
    }
}
void assignOperatorBinTree(binaryTree *bLhs,binaryTree *bRhs)
{
    int index=0;
    int num =0;
    int res = (bLhs!=NULL)&&(bRhs!=NULL)&&(bLhs!=bRhs);
    if(res ==1)
    {
        res = (bRhs->copyKeyValue !=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(res==1)
    {
        clearBinaryTree(bLhs);
        memcpy(bLhs,bRhs,sizeof(binaryTree));
        bLhs->parameter1=NULL;
        bLhs->parameter2=NULL;
        bLhs->parameter3=NULL;
        bLhs->parameter4 =NULL;
        bLhs->parameter5 =NULL;
        bLhs->root=NULL;
        bLhs->numNode=0;
        num = heightOfBinaryTree(bRhs)+1;
        for(index=0;index<num;index++)
        {
            transverseCopyDataInTree(bLhs,bRhs->root,index);
        }
    }
    else
    {
        /* do noting */
    }
}
int isEmptyOfBinaryTree(binaryTree* bin)
{
    int res=0;
    if(bin !=NULL)
    {
        res = (bin->root ==NULL);
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int getNumBinaryNodeOfTree(binaryTree* binaryTreeObj)
{
    int res = 0;
    if(binaryTreeObj!=NULL)
    {
        res = binaryTreeObj->numNode;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int countAllNodesInBT(binaryTree* bin)
{
    return countNodesOfANodeInBT(bin,bin->root);
}
int countNodesOfANodeInBT(binaryTree* bin,void *node)
{
    if(node ==NULL)
    {
        return 0;
    }
    else
    {
        return 1+ countNodesOfANodeInBT(bin,bin->getNodeLeft(node))+countNodesOfANodeInBT(bin,bin->getNodeRight(node));
    }
}

void* (*getCopyFnOfBin(const int opCode))(struct binaryTree*,void*)
{
    void* (*res)(struct binaryTree*,void*)=NULL;
    switch(opCode)
    {
        case CHAR_TYPE:  /* char */ 
            res = &copyCharKeyValue;
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = &copyUCharKeyValue;
        break;
        case INT_TYPE: /* int */ 
            res = &copyIntKeyValue;
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = &copyUIntKeyValue;
        break;
        case SHORT_TYPE: /* short */ 
            res = &copyShortKeyValue;
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = &copyUShortKeyValue;
        break;
        case LINT_TYPE: /* long */ 
            res = &copyLIntKeyValue;
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = &copyULIntKeyValue;
        break;
        case FLOAT_TYPE: /* float */ 
            res = &copyFloatKeyValue;
        break;
        case DOUBLE_TYPE: /* double */
            res = &copyDoubleKeyValue;
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = &copyLDoubleKeyValue;
        break;
        case LLINT_TYPE: /* long long */ 
            res = &copyLLIntKeyValue;
        break;
        case ULLINT_TYPE: /* unsigned long long */ 
            res = &copyULLIntKeyValue;
        break;        
        case CUS1_TYPE: /* void pointer */ 
            res = NULL;
        break;        
        case CUS2_TYPE: /* void pointer with data */ 
            res = NULL;
        break;
        case VDOUBLE_TYPE: /* vector_double */ 
            res = &copyVDoubleKeyValue;
        break;
        case SIMSTRING_TYPE:  /* simString */ 
            res = &copySimStrKeyValue;
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =NULL;
        break;
        default:
            res =NULL;
        break;
    }
    return res;
}
void* copyIntKeyValue(struct binaryTree *obj,void *nodeA)
{
    int *pInt =NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
         pInt =  (int*)getKeyIntNodeBinary(nodeA);
         node = obj->insertFn(obj,&pInt);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyUIntKeyValue(struct binaryTree *obj,void *nodeA)
{
    unsigned int *pUInt =NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
        pUInt = (unsigned int*)getKeyUIntNodeBinary(nodeA);
        node = obj->insertFn(obj,&pUInt);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyCharKeyValue(struct binaryTree *obj,void *nodeA)
{
    char *pChar =NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
        pChar= (char*)getKeyCharNodeBinary(nodeA);
        node = obj->insertFn(obj,&pChar);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyUCharKeyValue(struct binaryTree *obj,void *nodeA)
{
    unsigned char *pUChar=NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
        pUChar= (unsigned char*)getKeyUCharNodeBinary(nodeA);
        node = obj->insertFn(obj,&pUChar);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyShortKeyValue(struct binaryTree *obj,void *nodeA)
{
    short int *pSint=NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
        pSint= (short*)getKeyShortNodeBinary(nodeA);
        node = obj->insertFn(obj,&pSint);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyUShortKeyValue(struct binaryTree *obj,void *nodeA)
{
    unsigned short *pUSint =NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
        pUSint = (unsigned short*)getKeyUShortNodeBinary(nodeA);
        node = obj->insertFn(obj,&pUSint);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyLIntKeyValue(struct binaryTree *obj,void *nodeA)
{
    long int *pLInt =NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
        pLInt = (long int*)getKeyLIntNodeBinary(nodeA);
        node = obj->insertFn(obj,&pLInt);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyULIntKeyValue(struct binaryTree *obj,void *nodeA)
{
    unsigned long int *pULInt =NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
         pULInt = (unsigned long int*)getKeyULIntNodeBinary(nodeA);
         node = obj->insertFn(obj,&pULInt);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyLLIntKeyValue(struct binaryTree *obj,void *nodeA)
{
    long long int *pLLInt=NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
         pLLInt = (long long int*)getKeyLLIntNodeBinary(nodeA);
         node = obj->insertFn(obj,&pLLInt);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyULLIntKeyValue(struct binaryTree *obj,void *nodeA)
{
    unsigned long long int *pULLInt =NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
         pULLInt = (unsigned long long int*)getKeyULLIntNodeBinary(nodeA);
         node = obj->insertFn(obj,&pULLInt);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyFloatKeyValue(struct binaryTree *obj,void *nodeA)
{
    float *pFloat=NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
         pFloat = (float*)getKeyFloatNodeBinary(nodeA);
         node = obj->insertFn(obj,&pFloat);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyDoubleKeyValue(struct binaryTree *obj,void *nodeA)
{
    double *pDouble =NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
         pDouble = (double*)getKeyDoubleNodeBinary(nodeA);
         node = obj->insertFn(obj,&pDouble);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void* copyLDoubleKeyValue(struct binaryTree *obj,void *nodeA)
{
    long double *pLDouble=NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
         pLDouble = (long double*)getKeyLDoubleNodeBinary(nodeA);
         node = obj->insertFn(obj,&pLDouble);
    }
    else
    {
        /* do nothing */
    }
    return node;
}

void* copyVDoubleKeyValue(struct binaryTree *obj,void *nodeA)
{
    vector_double *vdtemp =NULL;
    vector_double *vdtemp2 =NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    { 
        vdtemp = *((vector_double**)getKeyPVoidNodeBinary(nodeA));
        vdtemp2 = (vector_double*)malloc(sizeof(vector_double));
        *vdtemp2 = new_vector_double(0);
        copy_v_double(vdtemp2,vdtemp);
        node = obj->insertFn(obj,&vdtemp2);
    }
    else
    {
        /* do nothing */
    }
    return node;
}

void* copySimStrKeyValue(struct binaryTree *obj,void *nodeA)
{
    simString *simStrTemp = NULL;
    simString *simStrTemp2 = NULL;
    void *node =NULL;
    if((obj!=NULL)&&(nodeA!=NULL))
    {
        simStrTemp2 = (simString*)malloc(sizeof(simString));
        initialSimString(simStrTemp2);
        simStrTemp= *((simString**)getKeyPVoidNodeBinary(nodeA));
        copySimStr(simStrTemp2,simStrTemp);
        node = obj->insertFn(obj,&simStrTemp2);
    }
    else
    {
        /* do nothing */
    }
    return node;
}
void printBinTree(binaryTree *bin)
{
    if(bin !=NULL)
    {
        printf("configRight : %d\n",bin->configRight);
        printf("sizeKey : %d\n",bin->sizeKey);
        printf("sizeData : %d\n",bin->sizeData);
        printf("isData : %d\n",bin->isData);
        printf("typeBT : %02x\n",bin->typeBT);
    }
    else
    {
        /* do nothing */
    }
}
void constructorBinaryTree2(binaryTree *bin,int type,int size,int sizeKey)
{
    if(bin !=NULL)
    {
        bin->configRight = setDataTypeOfBinaryTree(bin,type,size,sizeKey);
        bin->numNode =0;
        bin->root =NULL;
        bin->isPrint =0;
        bin->isNotDelKey =0;
        bin->parameter1 =NULL;
        bin->parameter2 =NULL;
        bin->parameter3 =NULL;
        bin->parameter4 =NULL;
        bin->parameter5 =NULL;
        nullAllMethodsOfBinTree(bin);
        bin->deleteNodeByKey = deleteKeyOfNodeDataInBinaryTree;
        bin->isData = (type==0x0E0);/* 0x0E0 custom type 2*/
    }
    else
    {
        /* do nothing */
    }
} 

void setParameterValofBinT(void *bin1,int index,void *val)
{
    binaryTree *bin = (binaryTree*)bin1;
    if((bin!=NULL)&&(index>0))
    {
        if(index == 1)
        {
            bin->parameter1 = val;
        }
        else if(index == 2)
        {
            bin->parameter2 = val;
        } 
        else if(index == 3)
        {
            bin->parameter3 = val;
        } 
        else if(index == 4)
        {
            bin->parameter4 = val;
        } 
        else if(index == 5)
        {
            bin->parameter5 = val;
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
}
int (*getConstructNodeBinaryFn(const int opCode))(void*)
{
    int (*res)(void*)=NULL;
    switch(opCode)
    {
        case CHAR_TYPE:  /* char */ 
            res = &constructCharNodeBinary;
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = &constructUCharNodeBinary;
        break;
        case INT_TYPE: /* int */ 
            res = &constructIntNodeBinary;
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = &constructUIntNodeBinary;
        break;
        case SHORT_TYPE: /* short */ 
            res = &constructShortNodeBinary;
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = &constructUShortNodeBinary;
        break;
        case LINT_TYPE: /* long */ 
            res = &constructLIntNodeBinary;
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = &constructULIntNodeBinary;
        break;
        case FLOAT_TYPE: /* float */ 
            res = &constructFloatNodeBinary;
        break;
        case DOUBLE_TYPE: /* double */
            res = &constructDoubleNodeBinary;
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = &constructLDoubleNodeBinary;
        break;
        case LLINT_TYPE: /* long long */ 
            res = &constructLLIntNodeBinary;
        break;
        case ULLINT_TYPE: /* unsigned long long */ 
            res = &constructULLIntNodeBinary;
        break;
        case CUS1_TYPE: /* void pointer */ 
            res = &constructPVoidNodeBinary;
        break;
        case CUS2_TYPE: /* void pointer with data */ 
            res = &constructPVoidWithDataNodeBinary;
        break;
        case FIXED_ARR: /* void pointer with data */ 
            res = &constructFixArrNodeBinary;
        break;
        case FIXED_ARR_NBIN: /* void pointer with data */ 
            res = &constructFixArrNodeNBin_Bin;
        break;
        case VDOUBLE_TYPE: /* void pointer */ 
            res = &constructPVoidNodeBinary;
        break;
        case SIMSTRING_TYPE: /* simString */
            res = &constructPVoidNodeBinary;
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =NULL;
        break;
        default:
            res =NULL;
        break;
    }
    return res;
}
int constructIntNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryInt* tmp = (nodeBinaryInt*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int constructUIntNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryUInt* tmp = (nodeBinaryUInt*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int constructCharNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryChar* tmp = (nodeBinaryChar*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int constructUCharNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryUChar* tmp = (nodeBinaryUChar*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int constructShortNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryShort* tmp = (nodeBinaryShort*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int constructUShortNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryUShort* tmp = (nodeBinaryUShort*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int constructLIntNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryLInt* tmp = (nodeBinaryLInt*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int constructULIntNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryULInt* tmp = (nodeBinaryULInt*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int constructLLIntNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryLLInt* tmp = (nodeBinaryLLInt*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int constructULLIntNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryULLInt* tmp = (nodeBinaryULLInt*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int constructFloatNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryFloat* tmp = (nodeBinaryFloat*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int constructDoubleNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryDouble* tmp = (nodeBinaryDouble*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int constructLDoubleNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryLDouble* tmp = (nodeBinaryLDouble*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int constructPVoidNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryPVoid* tmp = (nodeBinaryPVoid*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = NULL;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int constructPVoidWithDataNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeBinaryPVoidWithData* tmp = (nodeBinaryPVoidWithData*)node;
    if(tmp != NULL)
    {
            tmp->left = NULL;
            tmp->right = NULL;
            tmp->key = NULL;
            tmp->data = NULL;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int constructFixArrNodeBinary(void* node)
{
    int res = (node!=NULL);
    nodeFixedArr *tmp = (nodeFixedArr*)node;
    if(tmp != NULL)
    {
            tmp->m_lf = NULL;
            tmp->m_rt = NULL;
            tmp->m_dat2 = NULL;
            tmp->m_height = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int constructFixArrNodeNBin_Bin(void* node)
{
    int res = (node!=NULL);
    nodeFixedArrNBIn *tmp = (nodeFixedArrNBIn*)node;
    if(tmp != NULL)
    {
            tmp->m_lf = NULL;
            tmp->m_rt = NULL;
            tmp->m_dat = NULL;
            tmp->m_dat2 = NULL;
            tmp->m_height = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

void clearBinaryTree(binaryTree* bin)
{
    if(bin!=NULL)
    {
        if(bin->root!=NULL)
        {
            bin->clearNodesBinaryTree(bin,bin->root);
            bin->root = NULL;
            bin->numNode = 0; 
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
}
void clearANodeBinary(binaryTree* bin,void* node)
{
    if(node!=NULL)
    {
        clearANodeBinary(bin,bin->getNodeLeft(node));
        clearANodeBinary(bin,bin->getNodeRight(node));
        if(bin->deleteKey != NULL)
        {
            bin->deleteKey((void*)bin,bin->getKey(node));
        }
        else
        {
            /* do nothing */
        }
        if(bin->deleteData!=NULL)
        {
            bin->deleteData((void*)bin,&(((nodeBinaryPVoidWithData*)node)->data));
        }
        else
        {
            /* do nothing */
        }
        free(node);
    }
    else
    {
        /* do nothing */
    }
}
void* insertIntDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryInt *prep=NULL,*p =NULL;
    nodeBinaryInt *new1 = (nodeBinaryInt*)malloc(sizeof(nodeBinaryInt));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        p = (nodeBinaryInt*)bin->root;
        res =bin->constructNodeDataType(new1);
        new1->key = *((int*)key);
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1 = NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}

void* insertUIntDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryUInt *prep=NULL,*p = NULL;
    nodeBinaryUInt *new1 = (nodeBinaryUInt*)malloc(sizeof(nodeBinaryUInt));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        p = (nodeBinaryUInt*)bin->root;
        res =bin->constructNodeDataType(new1);
        new1->key = *((unsigned int*)key);
        res =1;
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}

void* insertCharDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryChar *prep=NULL,*p = NULL;
    nodeBinaryChar *new1 = (nodeBinaryChar*)malloc(sizeof(nodeBinaryChar));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        res =bin->constructNodeDataType(new1);
        p = (nodeBinaryChar*)bin->root;
        new1->key = *((char*)key);
        res =1;
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}

void* insertUCharDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryUChar *prep=NULL,*p = NULL;
    nodeBinaryUChar *new1 = (nodeBinaryUChar*)malloc(sizeof(nodeBinaryUChar));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        p = (nodeBinaryUChar*)bin->root;
        res =bin->constructNodeDataType(new1);
        new1->key = *((unsigned char*)key);
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}

void* insertShortDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryShort *prep=NULL,*p =NULL;
    nodeBinaryShort *new1 = (nodeBinaryShort*)malloc(sizeof(nodeBinaryShort));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        p = (nodeBinaryShort*)bin->root;
        res =bin->constructNodeDataType(new1);
        new1->key = *((short*)key);
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}

void* insertUShortDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryUShort *prep=NULL,*p =NULL;
    nodeBinaryUShort *new1 = (nodeBinaryUShort*)malloc(sizeof(nodeBinaryUShort));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        p = (nodeBinaryUShort*)(bin->root);
        res =bin->constructNodeDataType(new1);
        new1->key = *((unsigned short*)key);
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}

void* insertLIntDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryLInt *prep=NULL,*p = NULL;
    nodeBinaryLInt *new1 = (nodeBinaryLInt*)malloc(sizeof(nodeBinaryLInt));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        res =bin->constructNodeDataType(new1);
        p = (nodeBinaryLInt*)bin->root;
        new1->key = *((long int*)key);
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}
void* insertULIntDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryULInt *prep=NULL,*p = NULL;
    nodeBinaryULInt *new1 = (nodeBinaryULInt*)malloc(sizeof(nodeBinaryULInt));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        res =bin->constructNodeDataType(new1);
        p = (nodeBinaryULInt*)(bin->root);
        new1->key = *((unsigned long int*)key);
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}

void* insertLLIntDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryLLInt *prep=NULL,*p = NULL;
    nodeBinaryLLInt *new1 = (nodeBinaryLLInt*)malloc(sizeof(nodeBinaryLLInt));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        res =bin->constructNodeDataType(new1);
        p = (nodeBinaryLLInt*)(bin->root);
        new1->key = *((long long int*)key);
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1 = NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}
void* insertULLIntDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryULLInt *prep=NULL,*p = NULL;
    nodeBinaryULLInt *new1 = (nodeBinaryULLInt*)malloc(sizeof(nodeBinaryULLInt));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        res =bin->constructNodeDataType(new1);
        p = (nodeBinaryULLInt*)bin->root;
        new1->key = *((unsigned long long int*)key);
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}

void* insertFloatDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryFloat *prep=NULL,*p = NULL;
    nodeBinaryFloat *new1 = (nodeBinaryFloat*)malloc(sizeof(nodeBinaryFloat));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        res =bin->constructNodeDataType(new1);
        p = (nodeBinaryFloat*)bin->root;
        new1->key = *((float*)key);
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}

void* insertDoubleDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryDouble *prep=NULL,*p = NULL;
    nodeBinaryDouble *new1 = (nodeBinaryDouble*)malloc(sizeof(nodeBinaryDouble));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        res =bin->constructNodeDataType(new1);
        p = (nodeBinaryDouble*)bin->root;
        new1->key = *((double*)key);
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
            bin->numNode = bin->numNode+res;
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}
void* insertLDoubleDataToBinaryTree(binaryTree* bin,const void* key)
{        
    nodeBinaryLDouble *prep=NULL,*p = NULL;
    nodeBinaryLDouble *new1 = (nodeBinaryLDouble*)malloc(sizeof(nodeBinaryLDouble));
    int res = (bin !=NULL)&&(key !=NULL);
    int dummyInt=0;
    if((new1 != NULL)&&(res==1))
    {
        p = (nodeBinaryLDouble*)bin->root;
        res =bin->constructNodeDataType(new1);
        new1->key = *((long double*)key);
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}
void* insertPVoidToBinaryTree(binaryTree* bin,const void* key)
{ 
    int dummyInt=0;
    void** pKey = (void**)key;
    nodeBinaryPVoid *prep=NULL,*p = NULL;
    nodeBinaryPVoid *new1 = (nodeBinaryPVoid*)malloc(sizeof(nodeBinaryPVoid));
    int res = (bin !=NULL)&&(key !=NULL);
    res = res&&(bin->compareType!=NULL);
    res = res&&(bin->constructNodeDataType!=NULL);
    if((new1 != NULL)&&(res==1))
    {
        p = (nodeBinaryPVoid*)bin->root;
        res =bin->constructNodeDataType(new1);
        new1->key = *pKey;
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(p->key,*pKey);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(prep->key,*pKey);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}
void* insertPVoidWithDataToBinaryTree(binaryTree* bin,const void* key)
{       
    int dummyInt=0;
    void** pKey = (void**)key;
    nodeBinaryPVoidWithData *prep=NULL,*p = NULL;
    nodeBinaryPVoidWithData *new1 = (nodeBinaryPVoidWithData*)malloc(sizeof(nodeBinaryPVoidWithData));
    int res = (bin !=NULL)&&(key !=NULL);
    res = res&&(bin->compareType!=NULL);
    res = res&&(bin->constructNodeDataType!=NULL);

    if((new1 != NULL)&&(res==1))
    {
        p = (nodeBinaryPVoidWithData*)bin->root;
        res =bin->constructNodeDataType(new1); 
        new1->key = *pKey;
    }
    else
    {
        res =0;
    }
    if(res ==1)
    {
        while(p!= NULL)
        {
            prep = p;
            dummyInt = bin->compareType(&(p->key),key);
            switch(dummyInt)
            {
                case MORE_DEFINE:
                    p = p->left;
                break;
                case LESS_DEFINE:
                    p = p->right;
                break;
                default:
                    res =0;
                    p=NULL;
                break;
            }
        }
        if(res ==1)
        {
            if(bin->root ==NULL)
            {
                bin->root = new1;
            }
            else
            {
                dummyInt = bin->compareType(&(prep->key),key);
                if(dummyInt == LESS_DEFINE)
                {
                    prep->right = new1;
                }
                else if(dummyInt == MORE_DEFINE)
                {
                    prep->left = new1;
                }
                else
                {
                    res=0; 
                }
            } 
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
    if((res==0)&&(new1!=NULL))
    {
        free(new1);
        new1=NULL;
    }
    else
    {
        /* do nothing */
    }
    return new1;
}
void* (*getInsertDataType(const int opCode))(binaryTree*, const void*)
{
    void* (*res)(binaryTree*, const void*)=NULL;
    switch(opCode)
    {
        case CHAR_TYPE:  /* char */ 
            res = &insertCharDataToBinaryTree;
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = &insertUCharDataToBinaryTree;
        break;
        case INT_TYPE: /* int */ 
            res = &insertIntDataToBinaryTree;
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = &insertUIntDataToBinaryTree;
        break;
        case SHORT_TYPE: /* short */ 
            res = &insertShortDataToBinaryTree;
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = &insertUShortDataToBinaryTree;
        break;
        case LINT_TYPE: /* long */ 
            res = &insertLIntDataToBinaryTree;
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = &insertULIntDataToBinaryTree;
        break;
        case FLOAT_TYPE: /* float */ 
            res = &insertFloatDataToBinaryTree;
        break;
        case DOUBLE_TYPE: /* double */
            res = &insertDoubleDataToBinaryTree;
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = &insertLDoubleDataToBinaryTree;
        break;
        case LLINT_TYPE: /* long long */ 
            res = &insertLLIntDataToBinaryTree;
        break;
        case ULLINT_TYPE: /* unsigned long long */ 
            res = &insertULLIntDataToBinaryTree;
        break;
        case CUS1_TYPE: /* void pointer */ 
            res = &insertPVoidToBinaryTree;
        break;
        case CUS2_TYPE: /* void pointer with data */ 
            res = &insertPVoidWithDataToBinaryTree;
        break;
        case VDOUBLE_TYPE: /* void pointer */ 
            res = &insertPVoidToBinaryTree;
        break;
        case SIMSTRING_TYPE: /* simString */
            res = &insertPVoidToBinaryTree;
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =NULL;
        break;
        default:
            res =NULL;
        break;
    }
    return res;
}

void* searchDataInBinaryTreeWithOpt(binaryTree* bin,void *opt,const void* key)
{
    int res = (bin!=NULL)&&(key!=NULL)&&(opt!=NULL);
    void *p =NULL;
    void *target =NULL;
    int dummyInt=0;
    res = res&&(bin->compareTypeWithOpt !=NULL);
    if(res ==1)
    {
        p = bin->root;
        while(p!=NULL)
        {
            dummyInt = bin->compareTypeWithOpt(opt,bin->getKey(p),key);
            switch(dummyInt)
            {
                case EQUAL_DEFINE:
                   target = p;
                    p=NULL;
                break;
                case LESS_DEFINE:
                    p = bin->getNodeRight(p);
                break;
                default:
                    p = bin->getNodeLeft(p);
                break;
            }
        }
    }
    else
    {
        /* do nothing */
    }
    return target;
}
void* searchDataInBinaryTree(binaryTree* bin,const void* key)
{
    int res = (bin!=NULL)&&(key!=NULL);
    void *p =NULL;
    void *target =NULL;
    int dummyInt=0;
    if(res ==1)
    {
        p = bin->root;
        while(p!=NULL)
        {
            dummyInt = bin->compareType(bin->getKey(p),key);
            switch(dummyInt)
            {
                case EQUAL_DEFINE:
                   target = p;
                    p=NULL;
                break;
                case LESS_DEFINE: 
                    p = bin->getNodeRight(p);
                break;
                default: 
                    p = bin->getNodeLeft(p);
                break;
            }
        }
    }
    else
    {
        /* do nothing */
    }
    return target;
}

int deleteNodeDataInBinaryTree(struct binaryTree *bin,void** node)
{
    int res =0;
    void* tmp =  *node;
    void* prev =NULL;
    if((node != NULL)&&(bin!=NULL))
    {
        res = (bin->swapValue!=NULL);
    }
    else
    {
        printf("Swap function is null at line: %d\n",__LINE__);
    }
    if(res ==1)
    {
        if(bin->getNodeRight(*node) == NULL)
        {
            *node = bin->getNodeLeft(*node);
        }
        else if(bin->getNodeLeft(*node) == NULL)
        {
            *node = bin->getNodeRight(*node);
        }
        else
        {
            tmp = bin->getNodeLeft(*node);
            prev = *node;
            while(bin->getNodeRight(tmp) !=NULL)
            {
                prev = tmp;
                tmp =  bin->getNodeRight(tmp);
            }
            /* swap value */
            bin->swapValue(*node,tmp);
            if(prev == *node)
            {
                *(bin->getNodeAddrLeft(prev)) = bin->getNodeLeft(tmp);
            }
            else
            {
                *(bin->getNodeAddrRight(prev)) = bin->getNodeLeft(tmp);
            }
        }
        if(bin->deleteKey!=NULL)
        { 
            bin->deleteKey((void*)bin,bin->getKey(tmp));
        }
        else
        {
            /* do nothing */
        }
        if(bin->deleteData!=NULL)
        {
            bin->deleteData((void*)bin,tmp);
        }
        else
        {
            /* do nothing */
        }
        bin->numNode--;
        free(tmp);
        res =1;
    }
    return res;
}

int deleteKeyOfNodeDataInBinaryTree(binaryTree* bin,const void* key)
{
    int res = (bin!=NULL)&&(key!=NULL);
    void *node =NULL;
    void *prev =NULL;
    int compResult =2;/* 1 is equal */ 
    if(res ==1)
    {
        node = bin->root;
        while(node != NULL)
        {
            compResult = bin->compareType(bin->getKey(node),key);
            if(compResult == EQUAL_DEFINE)
            {
                break;
            }
            else
            {
                prev = node;
            }
            if(compResult == MORE_DEFINE)
            {
                node = bin->getNodeLeft(node);
            }
            else
            {
                node = bin->getNodeRight(node);
            }
        }
        if(compResult == EQUAL_DEFINE)
        {         
             if(node == bin->root)
             {
                bin->deleteNode(bin,&(bin->root));
             }
             else if(bin->getNodeLeft(prev) == node)
             {
                bin->deleteNode(bin,bin->getNodeAddrLeft(prev));
             }
             else 
             {
                bin->deleteNode(bin,bin->getNodeAddrRight(prev));
             }
        }
        else if(bin->root != NULL)
        {
            printf("no key in the tree \n");
        }
        else
        {
            printf("Tree is empty\n");
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int heightDataNodeBinary(binaryTree* bin,void* node)
{
    int res=0;
    int res2=0;
    if(node==NULL)
    {
        res=0;
    }
    else
    {
        res = heightDataNodeBinary(bin,bin->getNodeLeft(node));
        res2 = heightDataNodeBinary(bin,bin->getNodeRight(node));
        if(res >res2)
        {
            res = res+1;
        }
        else
        {
            res =res2+1;
        }
    }
    return res;
}

int heightOfBinaryTree(binaryTree* bin)
{
    int res=-1;
    if(bin!=NULL)
    {
        res =bin->getNodeHeight(bin,bin->root);
    }
    else
    {
        /* do nothing */
    }
    return res;
}
void (*printBinaryTree(const int opCode))(binaryTree*,char style)
{
    void (*res)(binaryTree*,char)=NULL;
    switch(opCode)
    {
        case CHAR_TYPE:  /* char */ 
            res = &printCharDataInBinaryTree;
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = &printUCharDataInBinaryTree;
        break;
        case INT_TYPE: /* int */ 
            res = &printIntDataInBinaryTree;
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = &printUIntDataInBinaryTree;
        break;
        case SHORT_TYPE: /* short */ 
            res = &printShortDataInBinaryTree;
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = &printUShortDataInBinaryTree;
        break;
        case LINT_TYPE: /* long */ 
            res = &printLIntDataInBinaryTree;
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = &printULIntDataInBinaryTree;
        break;
        case FLOAT_TYPE: /* float */ 
            res = &printFloatDataInBinaryTree;
        break;
        case DOUBLE_TYPE: /* double */
            res = &printDoubleDataInBinaryTree;
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = &printLDoubleDataInBinaryTree;
        break;
        case LLINT_TYPE: /* long long */ 
            res = &printLLIntDataInBinaryTree;
        break;
        case ULLINT_TYPE: /* unsigned long long */ 
            res = &printULLIntDataInBinaryTree;
        break;
        case CUS1_TYPE: /* void pointer */ 
            res = &printPVoidDataInBinaryTree;
        break;
        case CUS2_TYPE: /* void pointer with data */ 
            res = &printPVoidWithDataInBinaryTree;
        break;
        case FIXED_ARR: /* void pointer with data */ 
            res = &printFixArrNodeBinaryT;
        break;
        case FIXED_ARR_NBIN: /* void pointer with data */ 
            res = &printFixArrNodeBinaryT_NBin;
        break;
        case VDOUBLE_TYPE: /* vector_double */ 
            res = &printVDoubleInBinaryTree;
        break;
        case SIMSTRING_TYPE: /* simString */
            res = &printSimStrInBinaryTree;
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =NULL;
        break;
        default:
            res =NULL;
        break;
    }
    return res;
}

void printIntDataInNode(nodeBinaryInt* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%d ",node->key);
    }
    else if(node!=NULL)
    {
        printIntDataInNode(node->left,high-1);
        printIntDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printUIntDataInNode(nodeBinaryUInt* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%u ",node->key);
    }
    else if(node!=NULL)
    {
        printUIntDataInNode(node->left,high-1);
        printUIntDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printCharDataInNode(nodeBinaryChar* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%d ",node->key);
    }
    else if(node!=NULL)
    {
        printCharDataInNode(node->left,high-1);
        printCharDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printUCharDataInNode(nodeBinaryUChar* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%u ",node->key);
    }
    else if(node!=NULL)
    {
        printUCharDataInNode(node->left,high-1);
        printUCharDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printShortDataInNode(nodeBinaryShort* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%d ",node->key);
    }
    else if(node!=NULL)
    {
        printShortDataInNode(node->left,high-1);
        printShortDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printUShortDataInNode(nodeBinaryUShort* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%u ",node->key);
    }
    else if(node!=NULL)
    {
        printUShortDataInNode(node->left,high-1);
        printUShortDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printLIntDataInNode(nodeBinaryLInt* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%ld ",node->key);
    }
    else if(node!=NULL)
    {
        printLIntDataInNode(node->left,high-1);
        printLIntDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printULIntDataInNode(nodeBinaryULInt* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%lu ",node->key);
    }
    else if(node!=NULL)
    {
        printULIntDataInNode(node->left,high-1);
        printULIntDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printLLIntDataInNode(nodeBinaryLLInt* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%lld ",node->key);
    }
    else if(node!=NULL)
    {
        printLLIntDataInNode(node->left,high-1);
        printLLIntDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printULLIntDataInNode(nodeBinaryULLInt* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%llu ",node->key);
    }
    else if(node!=NULL)
    {
        printULLIntDataInNode(node->left,high-1);
        printULLIntDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printFloatDataInNode(nodeBinaryFloat* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%f ",node->key);
    }
    else if(node!=NULL)
    {
        printFloatDataInNode(node->left,high-1);
        printFloatDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}

void printVDoubleDataInNode(nodeBinaryPVoid* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        /*6 = print in vector form */
        print_vector_double((vector_double*)node->key,6);
    }
    else if(node!=NULL)
    {
        printVDoubleDataInNode(node->left,high-1);
        printVDoubleDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printSimStrDataInNode(nodeBinaryPVoid* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        /*6 = print in vector form */
        printSimString((simString*)node->key);
    }
    else if(node!=NULL)
    {
        printSimStrDataInNode(node->left,high-1);
        printSimStrDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printDoubleDataInNode(nodeBinaryDouble* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%lf .. ",node->key);
    }
    else if(node!=NULL)
    {
        printDoubleDataInNode(node->left,high-1);
        printDoubleDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printLDoubleDataInNode(nodeBinaryLDouble* node,int high)
{
    if((node !=NULL)&&(high==0))
    {
        printf("%Lf ",node->key);
    }
    else if(node!=NULL)
    {
        printLDoubleDataInNode(node->left,high-1);
        printLDoubleDataInNode(node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printPVoidDataInNode(binaryTree* bin,nodeBinaryPVoid* node,int high)
{
    /*
        parameter1 = style
        parameter2 = size
        parameter3 = char* (buffer)
    */ 
    if((node !=NULL)&&(high==0))
    {
        if((bin->parameter3!=NULL)&&(bin->printKeyPVoid!=NULL))
        {
            bin->printKeyPVoid(node->key,(char*)bin->parameter3);
            printf("%s ",(char*)bin->parameter3);
        }
        else if(bin->printKeyPVoid==NULL)
        {
            printf("can not print please assign printKeyPVoid fn \n");
        }
        else
        {
            /* do nothing */
        }
    }
    else if(node!=NULL)
    {
        printPVoidDataInNode(bin,node->left,high-1);
        printPVoidDataInNode(bin,node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printPVoidWithDataInNode(binaryTree* bin,nodeBinaryPVoidWithData* node,int high)
{
    /*
        parameter1 = style
        parameter2 = size
        parameter3 = char* (buffer)
    */ 
    if((node !=NULL)&&(high==0))
    {
        if((bin->parameter3!=NULL)&&(bin->printKeyPVoid!=NULL))
        {
            bin->printKeyPVoid(node->key,(char*)bin->parameter3);
            printf("%s ",(char*)bin->parameter3);
        }
        else if(bin->parameter3==NULL)
        {
            printf("cannot print please assign buffer in para3\n");
        }
        else
        {
            /* do nothing */
        }
        if((bin->parameter3!=NULL)&&(bin->printDataPVoid!=NULL)&&(bin->getData !=NULL))
        {
            bin->printDataPVoid(bin->getData(node),(char*)bin->parameter3);
            printf("%s ",(char*)bin->parameter3);
        }
 
    }
    else if(node != NULL)
    {
        printPVoidWithDataInNode(bin,node->left,high-1);
        printPVoidWithDataInNode(bin,node->right,high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printFixArrNodeBinaryNode(binaryTree* bin,void* node,int high)
{
    /*
        parameter1 = style
        parameter2 = buffer 
    */ 
    if((node != NULL)&&(high == 0))
    {
        if((bin->parameter3!=NULL)&&(bin->printKeyPVoid!=NULL))
        {
            bin->printKeyPVoid(bin->getKey(node),(char*)bin->parameter3);
            printf("%s ",(char*)bin->parameter3);
        }
        else if(bin->parameter3==NULL)
        {
            printf("cannot print please assign buffer in para3\n");
        }
        else
        {
            /* do nothing */
        }
        if((bin->parameter3!=NULL)&&(bin->printDataPVoid!=NULL))
        {
            bin->printDataPVoid(node,(char*)bin->parameter3);
            printf("%s ",(char*)bin->parameter3);
        }
 
    }
    else if(node!=NULL)
    {
        printFixArrNodeBinaryNode(bin,bin->getNodeLeft(node),high-1);
        printFixArrNodeBinaryNode(bin,bin->getNodeRight(node),high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printFixArrNodeBinaryNode_NBin(binaryTree* bin,void* node,int high)
{
    /*
        parameter1 = style
        parameter2 = size
        parameter3 = char* (buffer)
    */ 
    if((node !=NULL)&&(high==0))
    {
        if((bin->parameter3 != NULL)&&(bin->printKeyPVoid != NULL))
        {
            bin->printKeyPVoid(bin->getKey(node),(char*)bin->parameter3);
            printf("%s ",(char*)bin->parameter3);
        }
        else if(bin->parameter3==NULL)
        {
            printf("cannot print please assign buffer in para3\n");
        }
        else
        {
            /* do nothing */
        }
        if((bin->parameter3!=NULL)&&(bin->printDataPVoid!=NULL))
        {
            bin->printDataPVoid(node,(char*)bin->parameter3);
            printf("%s ",(char*)bin->parameter3);
        }
        else
        {
            /* do nothing */
        }
 
    }
    else if(node!=NULL)
    {
        printFixArrNodeBinaryNode_NBin(bin,bin->getNodeLeft(node),high-1);
        printFixArrNodeBinaryNode_NBin(bin,bin->getNodeRight(node),high-1);
    }
    else
    {
        /* do nothing */
    }
}
void printIntDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                printIntDataInNode((nodeBinaryInt*)bin->root,index);
                printf("\n");
            }
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
}
void printUIntDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    nodeBinaryUInt *pNodeInt=NULL;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                pNodeInt = (nodeBinaryUInt*)bin->root;
                printUIntDataInNode(pNodeInt,index);
                printf("\n");
            }
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
}
void printCharDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                printCharDataInNode((nodeBinaryChar*)bin->root,index);
                printf("\n");
            }
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
}
void printUCharDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                printUCharDataInNode((nodeBinaryUChar*)bin->root,index);
                printf("\n");
            }
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
}
void printShortDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                printShortDataInNode((nodeBinaryShort*)bin->root,index);
                printf("\n");
            }
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
}
void printUShortDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                printUShortDataInNode((nodeBinaryUShort*)bin->root,index);
                printf("\n");
            }
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
}
void printLIntDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                printLIntDataInNode((nodeBinaryLInt*)bin->root,index);
                printf("\n");
            }
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
}
void printULIntDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                printULIntDataInNode((nodeBinaryULInt*)bin->root,index);
                printf("\n");
            }
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
}
void printLLIntDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                printLLIntDataInNode((nodeBinaryLLInt*)bin->root,index);
                printf("\n");
            }
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
}
void printULLIntDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                printULLIntDataInNode((nodeBinaryULLInt*)bin->root,index);
                printf("\n");
            }
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
}
void printFloatDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                printFloatDataInNode((nodeBinaryFloat*)bin->root,index);
                printf("\n");
            }
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
}
void printDoubleDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);

           printf("height : %d\n",height);
            for(index=0;index<height;index++)
            {
                printDoubleDataInNode((nodeBinaryDouble*)bin->root,index);
                printf("\n");
            }
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
}
void printVDoubleInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);

           printf("height : %d\n",height);
            for(index=0;index<height;index++)
            {
                printVDoubleDataInNode((nodeBinaryPVoid*)bin->root,index);
                printf("\n");
            }
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
}

void printSimStrInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);

           printf("height : %d\n",height);
            for(index=0;index<height;index++)
            {
                printVDoubleDataInNode((nodeBinaryPVoid*)bin->root,index);
                printf("\n");
            }
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
}
void printLDoubleDataInBinaryTree(binaryTree* bin,char style)
{
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightOfBinaryTree(bin);
            for(index=0;index<height;index++)
            {
                printLDoubleDataInNode((nodeBinaryLDouble*)bin->root,index);
                printf("\n");
            }
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
}
void printPVoidDataInBinaryTree(binaryTree* bin,char style)
{    /*
        parameter1 = style
        parameter2 = size
        parameter3 = char* (buffer)
    */ 
    int height =0;
    int index=0;
    int sizeBuff =100;
    char *buffer=NULL;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            buffer = (char*)malloc(sizeof(char)*sizeBuff);
            height = heightOfBinaryTree(bin);
            bin->parameter1 =(void*)&style;
            bin->parameter1 =(void*)&sizeBuff;
            bin->parameter3 =(void*)buffer;
            
            for(index=0;index<height;index++)
            {
                printPVoidDataInNode(bin,(nodeBinaryPVoid*)bin->root,index);
                printf("\n");
            }
            if(buffer!=NULL)
            {
                free(buffer);
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
    }
    else
    {
        /* do nothing */
    }
}
void printPVoidWithDataInBinaryTree(binaryTree* bin,char style)
{    /*
        parameter1 = style
        parameter2 = size
        parameter3 = char* (buffer)
    */ 
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            height = heightDataNodeBinary(bin,bin->root);
            bin->parameter1 =(void*)&style;
            for(index=0;index<height;index++)
            {  
                printPVoidWithDataInNode(bin,(nodeBinaryPVoidWithData*)bin->root,index);
                printf("\n");
            }
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
}

void printFixArrNodeBinaryT(binaryTree* bin,char style)
{    /*
        parameter1 = style
        parameter2 = size
        parameter3 = char* (buffer)
    */ 
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            if((bin->root!=NULL)&&(bin->numNode>0))
            {
                height = heightDataNodeBinary(bin,bin->root);
            }
            else
            {
                /* do nothing */
            }
            bin->parameter1 =(void*)&style;
            for(index = 0;index < height;index++)
            {  
                printFixArrNodeBinaryNode(bin,bin->root,index);
                printf("\n");
            }
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
}

void printFixArrNodeBinaryT_NBin(binaryTree* bin,char style)
{    /*
        parameter1 = style
        parameter2 = size
        parameter3 = char* (buffer)
    */ 
    int height =0;
    int index=0;
    if(bin!=NULL)
    {
        if((style&0x0F) ==0)
        {
            if((bin->root!=NULL)&&(bin->numNode>0))
            {
                height = ((struct nodeFixedArrNBIn*)bin->root)->m_height;
            }
            else
            {
                /* do nothing */
            }
            bin->parameter1 =(void*)&style;

            for(index=0;index<height;index++)
            {  
                printFixArrNodeBinaryNode_NBin(bin,bin->root,index);
                printf("\n");
            }
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
}

void** getAddrLeftIntNodeBinary(void* node)
{
    nodeBinaryLInt** p = (nodeBinaryLInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftUIntNodeBinary(void* node)
{
    nodeBinaryULInt** p = (nodeBinaryULInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftCharNodeBinary(void* node)
{
    nodeBinaryChar** p = (nodeBinaryChar**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftUCharNodeBinary(void* node)
{
    nodeBinaryUChar** p = (nodeBinaryUChar**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftShortNodeBinary(void* node)
{
    nodeBinaryShort** p = (nodeBinaryShort**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftUShortNodeBinary(void* node)
{
    nodeBinaryUShort** p = (nodeBinaryUShort**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftLIntNodeBinary(void* node)
{
    nodeBinaryLInt** p = (nodeBinaryLInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftULIntNodeBinary(void* node)
{
    nodeBinaryULInt** p = (nodeBinaryULInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftLLIntNodeBinary(void* node)
{
    nodeBinaryLLInt** p = (nodeBinaryLLInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftULLIntNodeBinary(void* node)
{
    nodeBinaryULLInt** p = (nodeBinaryULLInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftFloatNodeBinary(void* node)
{
    nodeBinaryFloat** p = (nodeBinaryFloat**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftDoubleNodeBinary(void* node)
{
    nodeBinaryDouble** p = (nodeBinaryDouble**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftLDoubleNodeBinary(void* node)
{
    nodeBinaryLDouble** p = (nodeBinaryLDouble**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftPVoidNodeBinary(void* node)
{
    nodeBinaryPVoid** p = (nodeBinaryPVoid**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
 
void** getAddrLeftPVoidWithDataNodeBinary(void* node)
{
    nodeBinaryPVoidWithData** p = (nodeBinaryPVoidWithData**)&node;
    if(node!=NULL)
    {
        p = &((*p)->left);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftFixArrAvlNd_NBIn(void* node)
{
    struct nodeFixedArrNBIn **p = (struct nodeFixedArrNBIn**)&node;
    if(node!=NULL)
    {
        p = &((*p)->m_lf);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrLeftFixArrAvlNd(void* node)
{
    struct nodeFixedArr **p = (struct nodeFixedArr**)&node;
    if(node!=NULL)
    {
        p = &((*p)->m_lf);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
 
void** (*getAddrNodeLeftBinaryFn(const int opCode))(void*)
{
    void** (*res)(void*)=NULL;
    switch(opCode)
    {
        case CHAR_TYPE:  /* char */ 
            res = &getAddrLeftCharNodeBinary;
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = &getAddrLeftUCharNodeBinary;
        break;
        case INT_TYPE: /* int */ 
            res = &getAddrLeftIntNodeBinary;
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = &getAddrLeftUIntNodeBinary;
        break;
        case SHORT_TYPE: /* short */ 
            res = &getAddrLeftShortNodeBinary;
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = &getAddrLeftUShortNodeBinary;
        break;
        case LINT_TYPE: /* long */ 
            res = &getAddrLeftLIntNodeBinary;
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = &getAddrLeftULIntNodeBinary;
        break;
        case FLOAT_TYPE: /* float */ 
            res = &getAddrLeftFloatNodeBinary;
        break;
        case DOUBLE_TYPE: /* double */
            res = &getAddrLeftDoubleNodeBinary;
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = &getAddrLeftLDoubleNodeBinary;
        break;
        case LLINT_TYPE: /* long long */ 
            res = &getAddrLeftLLIntNodeBinary;
        break;
        case ULLINT_TYPE: /* unsigned long long */ 
            res = &getAddrLeftULLIntNodeBinary;
        break;        
        case CUS1_TYPE: /* void pointer */ 
            res = &getAddrLeftPVoidNodeBinary;
        break;        
        case CUS2_TYPE: /* void pointer with data */ 
            res = &getAddrLeftPVoidWithDataNodeBinary;
        break; 
        case FIXED_ARR: /* void pointer with data */ 
            res = &getAddrLeftFixArrAvlNd;
        break;
        case FIXED_ARR_NBIN: /* void pointer with data */ 
            res = &getAddrLeftFixArrAvlNd_NBIn;
        break;
        case VDOUBLE_TYPE: /* void pointer with data */ 
            res = &getAddrLeftPVoidNodeBinary;
        break;
        case SIMSTRING_TYPE:  /* void pointer with data */ 
            res = &getAddrLeftPVoidNodeBinary;
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =NULL;
        break;
        default:
            res =NULL;
        break;
    }
    return res;
}

void** getAddrRightIntNodeBinary(void* node)
{
    nodeBinaryLInt** p = (nodeBinaryLInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightUIntNodeBinary(void* node)
{
    nodeBinaryULInt** p = (nodeBinaryULInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightCharNodeBinary(void* node)
{
    nodeBinaryChar** p = (nodeBinaryChar**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightUCharNodeBinary(void* node)
{
    nodeBinaryUChar** p = (nodeBinaryUChar**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightShortNodeBinary(void* node)
{
    nodeBinaryShort** p = (nodeBinaryShort**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightUShortNodeBinary(void* node)
{
    nodeBinaryUShort** p = (nodeBinaryUShort**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightLIntNodeBinary(void* node)
{
    nodeBinaryLInt** p = (nodeBinaryLInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightULIntNodeBinary(void* node)
{
    nodeBinaryULInt** p = (nodeBinaryULInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightLLIntNodeBinary(void* node)
{
    nodeBinaryLLInt** p = (nodeBinaryLLInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightULLIntNodeBinary(void* node)
{
    nodeBinaryULLInt** p = (nodeBinaryULLInt**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightFloatNodeBinary(void* node)
{
    nodeBinaryFloat** p = (nodeBinaryFloat**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightDoubleNodeBinary(void* node)
{
    nodeBinaryDouble** p = (nodeBinaryDouble**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightLDoubleNodeBinary(void* node)
{
    nodeBinaryLDouble** p = (nodeBinaryLDouble**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightPVoidNodeBinary(void* node)
{
    nodeBinaryPVoid** p = (nodeBinaryPVoid**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightPVoidWithDataNodeBinary(void* node)
{
    nodeBinaryPVoidWithData** p = (nodeBinaryPVoidWithData**)&node;
    if(node!=NULL)
    {
        p = &((*p)->right);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightFixArrAvlNd_NBin(void* node)
{
    struct nodeFixedArrNBIn **p = (struct nodeFixedArrNBIn**)&node;
    if(node!=NULL)
    {
        p = &((*p)->m_rt);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** getAddrRightFixArrAvlNd(void* node)
{
    struct nodeFixedArr **p = (struct nodeFixedArr**)&node;
    if(node!=NULL)
    {
        p = &((*p)->m_rt);
    }
    else
    {
        /* do nothing */
    }
    return (void**)p;
}
void** (*getAddrNodeRightBinaryFn(const int opCode))(void*)
{
    void** (*res)(void*)=NULL;
    switch(opCode)
    {
        case CHAR_TYPE:  /* char */ 
            res = &getAddrRightCharNodeBinary;
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = &getAddrRightUCharNodeBinary;
        break;
        case INT_TYPE: /* int */ 
            res = &getAddrRightIntNodeBinary;
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = &getAddrRightUIntNodeBinary;
        break;
        case SHORT_TYPE: /* short */ 
            res = &getAddrRightShortNodeBinary;
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = &getAddrRightUShortNodeBinary;
        break;
        case LINT_TYPE: /* long */ 
            res = &getAddrRightLIntNodeBinary;
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = &getAddrRightULIntNodeBinary;
        break;
        case FLOAT_TYPE: /* float */ 
            res = &getAddrRightFloatNodeBinary;
        break;
        case DOUBLE_TYPE: /* double */
            res = &getAddrRightDoubleNodeBinary;
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = &getAddrRightLDoubleNodeBinary;
        break;
        case LLINT_TYPE: /* long long */ 
            res = &getAddrRightLLIntNodeBinary;
        break;
        case ULLINT_TYPE: /* unsigned long long */ 
            res = &getAddrRightULLIntNodeBinary;
        break;        
        case CUS1_TYPE: /* void pointer */ 
            res = &getAddrRightPVoidNodeBinary;
        break;        
        case CUS2_TYPE: /* void pointer with data */ 
            res = &getAddrRightPVoidWithDataNodeBinary;
        break;
        case FIXED_ARR: /* void pointer with data */ 
            res = &getAddrRightFixArrAvlNd;
        break;
        case FIXED_ARR_NBIN: /* void pointer with data */ 
            res = &getAddrRightFixArrAvlNd_NBin;
        break;
        case VDOUBLE_TYPE: /* void pointer with data */ 
            res = &getAddrRightPVoidNodeBinary;
        break;
        case SIMSTRING_TYPE: /* simString */ 
            res = &getAddrRightPVoidNodeBinary;
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =NULL;
        break;
        default:
            res =NULL;
        break;
    }
    return res;
}

void* getRightIntNodeBinary(void* node)
{
    nodeBinaryLInt* p = (nodeBinaryLInt*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightUIntNodeBinary(void* node)
{
    nodeBinaryULInt* p = (nodeBinaryULInt*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightCharNodeBinary(void* node)
{
    nodeBinaryChar* p = (nodeBinaryChar*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightUCharNodeBinary(void* node)
{
    nodeBinaryUChar* p = (nodeBinaryUChar*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightShortNodeBinary(void* node)
{
    nodeBinaryShort* p = (nodeBinaryShort*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightUShortNodeBinary(void* node)
{
    nodeBinaryUShort* p = (nodeBinaryUShort*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightLIntNodeBinary(void* node)
{
    nodeBinaryLInt* p = (nodeBinaryLInt*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightULIntNodeBinary(void* node)
{
    nodeBinaryULInt* p = (nodeBinaryULInt*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightLLIntNodeBinary(void* node)
{
    nodeBinaryLLInt* p = (nodeBinaryLLInt*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightULLIntNodeBinary(void* node)
{
    nodeBinaryULLInt* p = (nodeBinaryULLInt*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightFloatNodeBinary(void* node)
{
    nodeBinaryFloat* p = (nodeBinaryFloat*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightDoubleNodeBinary(void* node)
{
    nodeBinaryDouble* p = (nodeBinaryDouble*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightLDoubleNodeBinary(void* node)
{
    nodeBinaryLDouble* p = (nodeBinaryLDouble*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightPVoidNodeBinary(void* node)
{
    nodeBinaryPVoid* p = (nodeBinaryPVoid*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightPVoidWithDataNodeBinary(void* node)
{
    nodeBinaryPVoidWithData* p = (nodeBinaryPVoidWithData*)node;
    if(node!=NULL)
    {
        p = (p->right);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightFixArrAvlTNode(void* node)
{
    struct nodeFixedArr *p = (struct nodeFixedArr*)node;
    if(node!=NULL)
    {
        p = (p->m_rt);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getRightFixArrAvlTNode_NBin(void* node)
{
    struct nodeFixedArrNBIn *p = (struct nodeFixedArrNBIn*)node;
    if(node!=NULL)
    {
        p = (p->m_rt);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* (*getNodeRightBinaryFn(const int opCode))(void*)
{
    void* (*res)(void*)=NULL;
    switch(opCode)
    {
        case CHAR_TYPE:  /* char */ 
            res = &getRightCharNodeBinary;
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = &getRightUCharNodeBinary;
        break;
        case INT_TYPE: /* int */ 
            res = &getRightIntNodeBinary;
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = &getRightUIntNodeBinary;
        break;
        case SHORT_TYPE: /* short */ 
            res = &getRightShortNodeBinary;
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = &getRightUShortNodeBinary;
        break;
        case LINT_TYPE: /* long */ 
            res = &getRightLIntNodeBinary;
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = &getRightULIntNodeBinary;
        break;
        case FLOAT_TYPE: /* float */ 
            res = &getRightFloatNodeBinary;
        break;
        case DOUBLE_TYPE: /* double */
            res = &getRightDoubleNodeBinary;
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = &getRightLDoubleNodeBinary;
        break;
        case LLINT_TYPE: /* long long */ 
            res = &getRightLLIntNodeBinary;
        break;
        case ULLINT_TYPE: /* unsigned long long */ 
            res = &getRightULLIntNodeBinary;
        break;        
        case CUS1_TYPE: /* void pointer */ 
            res = &getRightPVoidNodeBinary;
        break;
        case CUS2_TYPE: /* void pointer with data */ 
            res = &getRightPVoidWithDataNodeBinary;
        break;
        case FIXED_ARR: /* void pointer with data */ 
            res = &getRightFixArrAvlTNode;
        break;
        case FIXED_ARR_NBIN: /* void pointer with data */ 
            res = &getRightFixArrAvlTNode_NBin;
        break;
        case VDOUBLE_TYPE: /* void pointer */ 
            res = &getRightPVoidNodeBinary;
        break;
        case SIMSTRING_TYPE: /* simString */ 
            res = &getRightPVoidNodeBinary;
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =NULL;
        break;
        default:
            res =NULL;
        break;
    }
    return res;
}

void* getLeftIntNodeBinary(void* node)
{
    nodeBinaryLInt* p = (nodeBinaryLInt*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftUIntNodeBinary(void* node)
{
    nodeBinaryULInt* p = (nodeBinaryULInt*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftCharNodeBinary(void* node)
{
    nodeBinaryChar* p = (nodeBinaryChar*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftUCharNodeBinary(void* node)
{
    nodeBinaryUChar* p = (nodeBinaryUChar*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftShortNodeBinary(void* node)
{
    nodeBinaryShort* p = (nodeBinaryShort*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftUShortNodeBinary(void* node)
{
    nodeBinaryUShort* p = (nodeBinaryUShort*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftLIntNodeBinary(void* node)
{
    nodeBinaryLInt* p = (nodeBinaryLInt*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftULIntNodeBinary(void* node)
{
    nodeBinaryULInt* p = (nodeBinaryULInt*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftLLIntNodeBinary(void* node)
{
    nodeBinaryLLInt* p = (nodeBinaryLLInt*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftULLIntNodeBinary(void* node)
{
    nodeBinaryULLInt* p = (nodeBinaryULLInt*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftFloatNodeBinary(void* node)
{
    nodeBinaryFloat* p = (nodeBinaryFloat*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftDoubleNodeBinary(void* node)
{
    nodeBinaryDouble* p = (nodeBinaryDouble*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftLDoubleNodeBinary(void* node)
{
    nodeBinaryLDouble* p = (nodeBinaryLDouble*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftPVoidNodeBinary(void* node)
{
    nodeBinaryPVoid* p = (nodeBinaryPVoid*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftPVoidWithDataNodeBinary(void* node)
{
    nodeBinaryPVoidWithData* p = (nodeBinaryPVoidWithData*)node;
    if(node!=NULL)
    {
        p = (p->left);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftFixArrAvlTNode_NBin(void* node)
{
    struct nodeFixedArrNBIn *p = (struct nodeFixedArrNBIn*)node;
    if(node!=NULL)
    {
        p = (p->m_lf);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* getLeftFixArrAvlTNode(void* node)
{
    struct nodeFixedArr *p = (struct nodeFixedArr*)node;
    if(node!=NULL)
    {
        p = (p->m_lf);
    }
    else
    {
        /* do nothing */
    }
    return (void*)p;
}
void* (*getNodeLeftBinaryFn(const int opCode))(void*)
{
    void* (*res)(void*)=NULL;
    switch(opCode)
    {
        case CHAR_TYPE:  /* char */ 
            res = &getLeftCharNodeBinary;
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = &getLeftUCharNodeBinary;
        break;
        case INT_TYPE: /* int */ 
            res = &getLeftIntNodeBinary;
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = &getLeftUIntNodeBinary;
        break;
        case SHORT_TYPE: /* short */ 
            res = &getLeftShortNodeBinary;
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = &getLeftUShortNodeBinary;
        break;
        case LINT_TYPE: /* long */ 
            res = &getLeftLIntNodeBinary;
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = &getLeftULIntNodeBinary;
        break;
        case FLOAT_TYPE: /* float */ 
            res = &getLeftFloatNodeBinary;
        break;
        case DOUBLE_TYPE: /* double */
            res = &getLeftDoubleNodeBinary;
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = &getLeftLDoubleNodeBinary;
        break;
        case LLINT_TYPE: /* long long */ 
            res = &getLeftLLIntNodeBinary;
        break;
        case ULLINT_TYPE: /* unsigned long long */ 
            res = &getLeftULLIntNodeBinary;
        break;        
        case CUS1_TYPE: /* void pointer */ 
            res = &getLeftPVoidNodeBinary;
        break;
        case CUS2_TYPE: /* void pointer with data */ 
            res = &getLeftPVoidWithDataNodeBinary;
        break;
        case FIXED_ARR: /* void pointer with data */ 
            res = &getLeftFixArrAvlTNode;
        break;
        case FIXED_ARR_NBIN: /* void pointer with data */ 
            res = &getLeftFixArrAvlTNode_NBin;
        break;
        case VDOUBLE_TYPE: /* void pointer */ 
            res = &getLeftPVoidNodeBinary;
        break;
        case SIMSTRING_TYPE: /* simString */
            res = &getLeftPVoidNodeBinary;
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =NULL;
        break;
        default:
            res =NULL;
        break;
    }
    return res;
}

void* getKeyIntNodeBinary(void* node)
{
    nodeBinaryLInt* p = (nodeBinaryLInt*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyUIntNodeBinary(void* node)
{
    nodeBinaryULInt* p = (nodeBinaryULInt*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyCharNodeBinary(void* node)
{
    nodeBinaryChar* p = (nodeBinaryChar*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyUCharNodeBinary(void* node)
{
    nodeBinaryUChar* p = (nodeBinaryUChar*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyShortNodeBinary(void* node)
{
    nodeBinaryShort* p = (nodeBinaryShort*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyUShortNodeBinary(void* node)
{
    nodeBinaryUShort* p = (nodeBinaryUShort*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyLIntNodeBinary(void* node)
{
    nodeBinaryLInt* p = (nodeBinaryLInt*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyULIntNodeBinary(void* node)
{
    nodeBinaryULInt* p = (nodeBinaryULInt*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyLLIntNodeBinary(void* node)
{
    nodeBinaryLLInt* p = (nodeBinaryLLInt*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyULLIntNodeBinary(void* node)
{
    nodeBinaryULLInt* p = (nodeBinaryULLInt*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyFloatNodeBinary(void* node)
{
    nodeBinaryFloat* p = (nodeBinaryFloat*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyDoubleNodeBinary(void* node)
{
    nodeBinaryDouble* p = (nodeBinaryDouble*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyLDoubleNodeBinary(void* node)
{
    nodeBinaryLDouble* p = (nodeBinaryLDouble*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyPVoidNodeBinary(void* node)
{
    nodeBinaryPVoid* p = (nodeBinaryPVoid*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyFixArrAvlTNode_NBin(void* node)
{
    void* key=NULL;
    struct nodeFixedArrNBIn *p = (struct nodeFixedArrNBIn*)node;
    if(node!=NULL)
    {
        key = (void*)&(p->m_dat);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyFixArrAvlTNode(void* node)
{
    void* key=NULL;
    struct nodeFixedArr *p = (struct nodeFixedArr*)node;
    if(node!=NULL)
    {
        key = (void*)(p->m_ref);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* getKeyPVoidWithDataNodeBinary(void* node)
{
    nodeBinaryPVoidWithData* p = (nodeBinaryPVoidWithData*)node;
    void* key=NULL;
    if(node!=NULL)
    {
        key = (void*)&(p->key);
    }
    else
    {
        /* do nothing */
    }
    return key;
}
void* (*getKeyBinaryFn(const int opCode))(void*)
{
    void* (*res)(void*)=NULL;
    switch(opCode)
    {
        case CHAR_TYPE:  /* char */ 
            res = &getKeyCharNodeBinary;
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = &getKeyUCharNodeBinary;
        break;
        case INT_TYPE: /* int */ 
            res = &getKeyIntNodeBinary;
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = &getKeyUIntNodeBinary;
        break;
        case SHORT_TYPE: /* short */ 
            res = &getKeyShortNodeBinary;
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = &getKeyUShortNodeBinary;
        break;
        case LINT_TYPE: /* long */ 
            res = &getKeyLIntNodeBinary;
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = &getKeyULIntNodeBinary;
        break;
        case FLOAT_TYPE: /* float */ 
            res = &getKeyFloatNodeBinary;
        break;
        case DOUBLE_TYPE: /* double */
            res = &getKeyDoubleNodeBinary;
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = &getKeyLDoubleNodeBinary;
        break;
        case LLINT_TYPE: /* long long */ 
            res = &getKeyLLIntNodeBinary;
        break;
        case ULLINT_TYPE: /* unsigned long long */ 
            res = &getKeyULLIntNodeBinary;
        break;        
        case CUS1_TYPE: /* void pointer */ 
            res = &getKeyPVoidNodeBinary;
        break;        
        case CUS2_TYPE: /* void pointer with data */ 
            res = &getKeyPVoidWithDataNodeBinary;
        break;
        case VDOUBLE_TYPE: /* vector_double */ 
            res = &getKeyPVoidNodeBinary;
        break;
        case SIMSTRING_TYPE: /* simString */
            res = &getKeyPVoidNodeBinary;
        break;
        case FIXED_ARR: /* simString */
            res = &getKeyFixArrAvlTNode;
        break;
        case FIXED_ARR_NBIN: /* simString */
            res = &getKeyFixArrAvlTNode_NBin;
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =NULL;
        break;
        default:
            res =NULL;
        break;
    }
    return res;
}
void (*getDeleteKeyFn(const int opCode))(void*,void*)
{
    void (*res)(void*,void*)=NULL;
    switch(opCode)
    {
        case VDOUBLE_TYPE: /* vector_double */ 
            res = &deleteVectorDoubleKey;
        break;
        case SIMSTRING_TYPE: /* simString */ 
            res = &deleteSimStrKey;
        break;
        default:
        res = NULL;
        break;
    }
    return res;
}
void (*swapValueOfNodeBinaryFn(const int opCode))(void*,void*)
{
    void (*res)(void*,void*)=NULL;
    switch(opCode)
    {
        case CHAR_TYPE:  /* char */ 
            res = &swapValueOfCharNodeBinary;
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = &swapValueOfUCharNodeBinary;
        break;
        case INT_TYPE: /* int */ 
            res = &swapValueOfIntNodeBinary;
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = &swapValueOfUIntNodeBinary;
        break;
        case SHORT_TYPE: /* short */ 
            res = &swapValueOfShortNodeBinary;
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = &swapValueOfUShortNodeBinary;
        break;
        case LINT_TYPE: /* long */ 
            res = &swapValueOfLIntNodeBinary;
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = &swapValueOfULIntNodeBinary;
        break;
        case FLOAT_TYPE: /* float */ 
            res = &swapValueOfFloatNodeBinary;
        break;
        case DOUBLE_TYPE: /* double */
            res = &swapValueOfDoubleNodeBinary;
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = &swapValueOfLDoubleNodeBinary;
        break;
        case LLINT_TYPE: /* long long */ 
            res = &swapValueOfLLIntNodeBinary;
        break;
        case ULLINT_TYPE: /* unsigned long long */ 
            res = &swapValueOfULIntNodeBinary;
        break;
        case CUS1_TYPE: /* void pointer */ 
            res = &swapValueOfPVoidNodeBinary;
        break;
        case CUS2_TYPE: /* void pointer with data */ 
            res =&swapValueOfPVoidWithDataNodeBinary;
        case VDOUBLE_TYPE: /* vector_double */ 
            res = &swapValueOfPVoidNodeBinary;
        break;
        case SIMSTRING_TYPE: /* simString */ 
            res = &swapValueOfPVoidNodeBinary;
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =NULL;
        break;
        default:
            res =NULL;
        break;
    }
    return res;
}
void swapValueOfIntNodeBinary(void* node,void* node2)
{
    int tmp=0;
    nodeBinaryInt* a= (nodeBinaryInt*)node;
    nodeBinaryInt* b= (nodeBinaryInt*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfUIntNodeBinary(void* node,void* node2)
{
    unsigned int tmp=0;
    nodeBinaryUInt* a= (nodeBinaryUInt*)node;
    nodeBinaryUInt* b= (nodeBinaryUInt*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfCharNodeBinary(void* node,void* node2)
{
    char tmp=0;
    nodeBinaryChar* a= (nodeBinaryChar*)node;
    nodeBinaryChar* b= (nodeBinaryChar*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfUCharNodeBinary(void* node,void* node2)
{
    unsigned char tmp=0;
    nodeBinaryUChar* a= (nodeBinaryUChar*)node;
    nodeBinaryUChar* b= (nodeBinaryUChar*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfShortNodeBinary(void* node,void* node2)
{
    short int tmp=0;
    nodeBinaryShort* a= (nodeBinaryShort*)node;
    nodeBinaryShort* b= (nodeBinaryShort*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfUShortNodeBinary(void* node,void* node2)
{
    unsigned short tmp=0;
    nodeBinaryUShort* a= (nodeBinaryUShort*)node;
    nodeBinaryUShort* b= (nodeBinaryUShort*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfLIntNodeBinary(void* node,void* node2)
{
    long int tmp=0;
    nodeBinaryLInt* a= (nodeBinaryLInt*)node;
    nodeBinaryLInt* b= (nodeBinaryLInt*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfULIntNodeBinary(void* node,void* node2)
{
    unsigned long int tmp=0;
    nodeBinaryLInt* a= (nodeBinaryLInt*)node;
    nodeBinaryLInt* b= (nodeBinaryLInt*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfLLIntNodeBinary(void* node,void* node2)
{
    long long int tmp=0;
    nodeBinaryLLInt* a= (nodeBinaryLLInt*)node;
    nodeBinaryLLInt* b= (nodeBinaryLLInt*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfULLIntNodeBinary(void* node,void* node2)
{
    unsigned long long int tmp=0;
    nodeBinaryULLInt* a= (nodeBinaryULLInt*)node;
    nodeBinaryULLInt* b= (nodeBinaryULLInt*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfFloatNodeBinary(void* node,void* node2)
{
    float tmp=0;
    nodeBinaryFloat* a= (nodeBinaryFloat*)node;
    nodeBinaryFloat* b= (nodeBinaryFloat*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfDoubleNodeBinary(void* node,void* node2)
{
    double tmp=0;
    nodeBinaryDouble* a= (nodeBinaryDouble *)node;
    nodeBinaryDouble* b= (nodeBinaryDouble*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfLDoubleNodeBinary(void* node,void* node2)
{
    long double tmp=0;
    nodeBinaryLDouble* a= (nodeBinaryLDouble *)node;
    nodeBinaryLDouble* b= (nodeBinaryLDouble*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfPVoidNodeBinary(void* node,void* node2)
{
    void* tmp=NULL;
    nodeBinaryPVoid* a= (nodeBinaryPVoid *)node;
    nodeBinaryPVoid* b= (nodeBinaryPVoid*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nothing */
    }
}
void swapValueOfPVoidWithDataNodeBinary(void* node,void* node2)
{
    void* tmp=NULL;
    void* tmp2=NULL;
    nodeBinaryPVoidWithData* a= (nodeBinaryPVoidWithData *)node;
    nodeBinaryPVoidWithData* b= (nodeBinaryPVoidWithData*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        tmp2= a->data;
        a->key = b->key;
        a->data = b->data;
        b->key = tmp;
        b->data = tmp2;
    }
    else
    {
        /* do nothing */
    }
}
void deleteVectorDoubleKey(void *obj,void *key)
{
    void **p = (void**)key;
/* printf("del : %p \n",p); */
    if(key!=NULL)
    {
        delete_vector_double((vector_double*)(*p));
        free(*p);
        *p = NULL;
    }
    else
    {
        /* do nothing */
    }
}

void deleteSimStrKey(void *obj,void *key)
{
    void **p = (void**)key;
/* printf("del : %p \n",p); */
    if(key!=NULL)
    {
        destructSimString((simString*)(*p));
        free(*p);
        *p = NULL;
    }
    else
    {
        /* do nothing */
    }
}


/*  tree traversals*/ /* return node*//* 0 - inorder, 1 - preOrder, 2 - postOrder */
void* traversalTBin(binaryTree *bin,int limit,int opt)
{
    void *node = NULL;
    if((bin != NULL)&&(limit > 0))
    {
        switch(opt)
        {
            case 0:
                node = inOrderTranverseTBin(bin,limit-1);
            break;
            case 1:
                node = preOrderTranverseTBin(bin,limit-1);
            break;
                node = postOrderTranverseTBin(bin,limit-1);
            case 2:
            break;
            default:
                node = inOrderTranverseTBin(bin,limit-1);
            break;
        }
    }
    else
    {
        /* do nothing */
    }
    return node;
} 
void* inOrderTranverseTBin(binaryTree *bin,int limit)
{
    if(limit == 0)
    {
    
    }
    else
    {
        // Do nothing
    }
    return bin;
}
void* preOrderTranverseTBin(binaryTree *bin,int limit)
{
    if(limit == 0)
    {
    
    }
    else
    {
        // Do nothing
    }
    return bin;
}
void* postOrderTranverseTBin(binaryTree *bin,int limit)
{
    if(limit == 0)
    {
    
    }
    else
    {
        // Do nothing
    }
    return bin;
}