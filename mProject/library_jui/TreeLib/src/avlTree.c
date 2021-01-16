#include "avlTree.h"

int deleteNodeAvlNodeWithNoData(binaryTree* avlTree,void** node)
{
    int res =0;
    nodeBinaryPVoidWithData** p = (nodeBinaryPVoidWithData**)node;
    char fact1 = (avlTree!=NULL)&&(node !=NULL);
    if(fact1 ==1)
    {
        fact1 = (*node !=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(fact1 ==1)
    {
        if(((*p)->key !=NULL)&&(avlTree->deleteKey!=NULL))
        { 
            avlTree->deleteKey((void*)avlTree,&((*p)->key));
        }
        else
        {
            /* do nothing */
        }
        if(avlTree->deleteData!=NULL)
        {
            avlTree->deleteData((void*)avlTree,&((*p)->data));
        }
        else
        {
            /* do nothing */
        }
        free(*node);
        res =1;
        *node = NULL;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int deleteNodeAvlNodeWithNoDataDebug(binaryTree* avlTree,void** node)
{
    int res =0;
    nodeBinaryPVoidWithData** p = (nodeBinaryPVoidWithData**)node;
    char fact1 = (avlTree!=NULL)&&(node !=NULL);
    if(fact1 ==1)
    {
        fact1 = (*node !=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(fact1 ==1)
    {
        if(((*p)->key !=NULL)&&(avlTree->deleteKey!=NULL))
        { 
            avlTree->deleteKey((void*)avlTree,&((*p)->key));
        }
        else
        {
            /* do nothing */
        }
        if(avlTree->deleteData!=NULL)
        {
            avlTree->deleteData((void*)avlTree,&((*p)->data));
        }
        else
        {
            printf("The data is not delete XXXXXX--------------------------XXXX\n");
            /* do nothing */
        }
        free(*node);
        res =1;
        *node = NULL;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int deleteNodeAvlNodeWithData(binaryTree* avlTree,void** node)
{
    int res =0;
    char fact1 = (avlTree!=NULL)&&(node !=NULL);
    nodeBinaryPVoidWithData** p =(nodeBinaryPVoidWithData**)node;
    if(fact1 ==1)
    {
        fact1 = (*node !=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(fact1 ==1)
    {
        if(((*p)->key !=NULL)&&(avlTree->deleteKey!=NULL))
        { 
            avlTree->deleteKey((void*)avlTree,&((*p)->key));
        }
        else
        {
            (*p)->key =NULL;
        }
        if((avlTree->deleteData!=NULL)&&((*p)->data!=NULL))
        {
            deleteAvlDataStruct(avlTree,*node);
            free((*p)->data);
        }
        else if((*p)->data!=NULL)
        {
            free((*p)->data);
        }
        else
        {
            /* do nothing */
        }
        (*p)->data = NULL;
        free(*node);
        res =1;
        *node = NULL;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int delNdFxArrAvlNd(binaryTree* avlTree,void** node)
{
    int res =0;
    char fact1 = (avlTree!=NULL)&&(node !=NULL); 
    if(fact1 ==1)
    {
        fact1 = (*node !=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(fact1 ==1)
    {
        if((avlTree->deleteData!=NULL)&&(avlTree->getData !=NULL))
        {
            avlTree->deleteData(avlTree,avlTree->getData(*node));
        }
        else
        {
            /* do nothing */
        }
        rmEleMt22d(avlTree->parameter3,*node);
    }
    else
    {
        /* do nothing */
    }
    return res;
}

void clearANodeAvlTree(binaryTree* avlTree,void* node)
{ 
    if(node != NULL)
    {   
        clearANodeAvlTree(avlTree,avlTree->getNodeLeft(node));
        clearANodeAvlTree(avlTree,avlTree->getNodeRight(node));
        deleteNodeAvlNodeWithNoData(avlTree,&node);
    }
    else
    {
        /* do nothing */
    }
}
void clearANodeAvlTreeWithData(binaryTree* avlTree,void* node)
{
    if(node != NULL)
    { 
        clearANodeAvlTreeWithData(avlTree,avlTree->getNodeLeft(node));
        clearANodeAvlTreeWithData(avlTree,avlTree->getNodeRight(node));
        deleteNodeAvlNodeWithData(avlTree,&node);
    }
    else
    {
        /* do nothing */
    }
}
void clearANodeAvlTFixArr(binaryTree* avlTree,void* node)
{
    if( avlTree != NULL)
    {
        clearMt22d(avlTree->parameter3);
        avlTree->root = NULL;
        avlTree->numNode = 0;
    }
    else
    {
        /* do nothing */
    }
}
int validateConfigIsOk(binaryTree* avlTree)
{
    int res = (avlTree!=NULL);
    if(res==1)
    {
        res = res&&(avlTree->compareType!=NULL); 
    }
    else
    {
        res =0;
    }
    return res;
}

void deleteAvlDataStruct(binaryTree* avlTree,void *node)
{
    char fact1 = (avlTree !=NULL)&&(node!=NULL);
    avlData *p =NULL;
    if(fact1 ==1)
    {
        p = (avlData*)((nodeBinaryPVoidWithData*)node)->data;
        fact1 = (p->data!=NULL)&&(avlTree->deleteData!=NULL);
        if(fact1==1)
        {
            avlTree->deleteData((void*)avlTree,&(p->data));
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
void constructAvlTree(void *avlT,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey)
{
    char fact1 = (avlT!=NULL);
    binaryTree *avlTree = (binaryTree*)avlT;
    if(fact1 ==1)
    {
        constructorBinaryTree3(avlTree,KeyTypeConfig,sizeData,sizeKey);
       /* setFunctionOfBinaryTree(avlTree);*/
        avlTree->isData = isWithData; 
        avlTree->deleteNodeByKey = removeAvlTreeNodeByKey;
        avlTree->getNodeLeft = getLeftPVoidWithDataNodeBinary;
        avlTree->getNodeRight= getRightPVoidWithDataNodeBinary;
        avlTree->getNodeAddrLeft= getAddrLeftPVoidWithDataNodeBinary;
        avlTree->getNodeAddrRight =getAddrRightPVoidWithDataNodeBinary;
        avlTree->insertFn = insertAvlTreeData;
        avlTree->printTree = printPVoidWithDataInBinaryTree;
        avlTree->constructNodeDataType = constructPVoidWithDataNodeBinary;
        avlTree->getKey = getKeyBinaryFn(getDataTypeFromString(KeyTypeConfig));
        avlTree->deleteKey = getDeleteKeyFn(getDataTypeFromString(KeyTypeConfig));
        avlTree->copyKeyValue = getCopyFnOfBin(getDataTypeFromString(KeyTypeConfig));
        avlTree->compareType = getCompFn(getDataTypeFromString(KeyTypeConfig));
        avlTree->configRight = validateConfigIsOk(avlTree);
        /* isWithData==0 , data = height */
        if (avlTree->isData == 0)
        {
            avlTree->deleteData = deleteHeightAvlTreeWithNodata;
            avlTree->getNodeHeight = getHeightAVLNodeWithNoData;
            avlTree->setNodeHeight = adjustHeightAVLNodeNoData;
            avlTree->deleteNode = deleteNodeAvlNodeWithNoData;
            avlTree->clearNodesBinaryTree =clearANodeAvlTree;
            avlTree->swapValue = swapValueOfAvlTreeNodeWithNoData;
            avlTree->getKey = getKeyPVoidWithDataNodeBinary;
        }
        else if (avlTree->isData == 1)
        {
            avlTree->getNodeHeight = getHeightAVLNodeWithData;
            avlTree->setNodeHeight = adjustHeightAVLNode;
            avlTree->swapValue = swapValueOfAvlTreeNodeWithData;
            avlTree->deleteNode = deleteNodeAvlNodeWithData;
            
            avlTree->getKey = getKeyPVoidWithDataNodeBinary;
            avlTree->clearNodesBinaryTree =clearANodeAvlTreeWithData;
        }
        else if(avlTree->isData == 2)
        {
            avlTree->printKeyPVoid = NULL;
            avlTree->getNodeHeight = getHeightAVLFixArrNode;
            avlTree->clearNodesBinaryTree =clearANodeAvlTFixArr;
            avlTree->getNodeLeft = getLeftFixArrAvlTNode;
            avlTree->getNodeRight= getRightFixArrAvlTNode;
            avlTree->getNodeAddrLeft= getAddrLeftFixArrAvlNd;
            avlTree->getNodeAddrRight =getAddrRightFixArrAvlNd;
            avlTree->constructNodeDataType=constructFixArrNodeBinary;

            avlTree->deleteNode = delNdFxArrAvlNd;
            avlTree->setNodeHeight = adjustHeightAVLNodeFixArr;
            avlTree->printTree = printFixArrNodeBinaryT;
            avlTree->swapValue = swapValOfAvlTFArrNode;
            avlTree->insertFn = insertAvlT4FixArrNodeBuiltIn;
            avlTree->deleteNodeByKey = removeAvlTreeNodeByKey4FixArr2;
            setDelKeyFlag(avlTree,1);
        }
        else if(avlTree->isData ==3)
        {
            avlTree->printKeyPVoid = NULL;
            avlTree->getNodeHeight = getHeightAVLFixArrNode_NBIn;
            avlTree->clearNodesBinaryTree =clearANodeAvlTFixArr;
            avlTree->getNodeLeft = getLeftFixArrAvlTNode_NBin;
            avlTree->getNodeRight= getRightFixArrAvlTNode_NBin;
            avlTree->getNodeAddrLeft= getAddrLeftFixArrAvlNd_NBIn;
            avlTree->getNodeAddrRight =getAddrRightFixArrAvlNd_NBin;
            avlTree->constructNodeDataType=constructFixArrNodeNBin_Bin;
            
            avlTree->deleteNode = delNdFxArrAvlNd;
            avlTree->setNodeHeight = adjustHeightAVLNodeFixArr_NBin;
            avlTree->printTree = printFixArrNodeBinaryT_NBin;
            avlTree->swapValue = swapValOfAvlTFArrNode_NBin;
            avlTree->insertFn = insertAvlT4FixArrNodeNoBuiltIn;
            avlTree->deleteNodeByKey = removeAvlTreeNodeByKey;
            setDelKeyFlag(avlTree,1);
        }
    

    }
    else
    {
        printf("Can not Construct AVL tree\n");
    }
}

/* isWithData==0 , data = height */
void deleteHeightAvlTreeWithNodata(void *obj,void *data)
{
    void **p = (void**)data;
    if(data != NULL)
    {
        if(*p!=NULL)
        { 
            free(*p);
            *p =NULL;
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

void deleteHeightAvlTreeWithNodataDebug(void *obj,void *data)
{
    void **p = (void**)data;
    if(data != NULL)
    {
        if(*p!=NULL)
        { 
            printf("del : %p\n",*p);
            free(*p);
            *p =NULL;
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

void printAddrOfNodeAtLvAvlT(binaryTree* avlTree,void *node,int depth)
{
    if((depth==0)&&(node!=NULL))
    {
        printf("%p ",node);
    }
    else if((depth>0)&&(node!=NULL))
    {
        printAddrOfNodeAtLvAvlT(avlTree,avlTree->getNodeLeft(node),depth-1);
        printAddrOfNodeAtLvAvlT(avlTree,avlTree->getNodeRight(node),depth-1);
    }
    else
    {
        /* do nothing */
    }
}
void printNodeTonDepth(binaryTree* avlTree,void *node,int depth)
{
    int i =0;
    for(i=0;i<depth;i++)
    {
        printAddrOfNodeAtLvAvlT(avlTree,node,i);
        printf("\n");
    }
}
int setDataToAvlNode(void *node,const void* data)
{
    int res = (node!=NULL)&&(data!=NULL);
    nodeBinaryPVoidWithData *p = (nodeBinaryPVoidWithData*)node;
    void **p2 =(void**)data;
    if(res==1)
    {
        res = (p->data !=NULL);
        if(res==1)
        {
            ((avlData*)p->data)->data = *p2;
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

void *getDataFromAvlNode(void *node)
{
    int res = (node!=NULL);
    nodeBinaryPVoidWithData *p = (nodeBinaryPVoidWithData*)node;
    void *p2 =NULL;
    if(res==1)
    {
        res = (p->data !=NULL);
        if(res==1)
        {
            p2 = ((avlData*)p->data)->data;
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
    return p2;
}
int getHeightAVLNodeWithData(binaryTree* avlTree,void* node)
{
    int res =-1;
    nodeBinaryPVoidWithData* p =(nodeBinaryPVoidWithData*)node;
    avlData* avlDataObj=NULL;
    if(node!=NULL)
    {            
        if(p->data!=NULL)
        {
            avlDataObj = (avlData*)p->data;
            res = avlDataObj->height;
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
int getHeightAVLNodeWithNoData(binaryTree* avlTree,void* node)
{
    int res =-1;
    nodeBinaryPVoidWithData* p =(nodeBinaryPVoidWithData*)node;
    if(node!=NULL)
    {            
        if(p->data!=NULL)
        {
            res = *((int*)p->data);
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
int getHeightAVLFixArrNode(binaryTree* avlTree,void* node)
{
    int ret =-1;
    if(node!=NULL)
    {            
        ret = ((struct nodeFixedArr*)node)->m_height;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int getHeightAVLFixArrNode_NBIn(binaryTree* avlTree,void* node)
{
    int ret =-1;
    if(node!=NULL)
    {            
        ret = ((struct nodeFixedArrNBIn*)node)->m_height;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int adjustHeightAVLNodeNoData(struct binaryTree* avlTree,void* node)
{
    int* pInt =NULL;
    int res =-1;
    int res2=0;
    int res3=0;
    char fact1 = (avlTree!=NULL);
    nodeBinaryPVoidWithData* p = (nodeBinaryPVoidWithData*)node;
    if(fact1 ==1)
    {
        if(p!=NULL)
        {
            if(p->data!=NULL)
            {
                pInt = (int*)p->data;
                res2 = avlTree->getNodeHeight(avlTree,avlTree->getNodeLeft(node));
                res3 = avlTree->getNodeHeight(avlTree,avlTree->getNodeRight(node));

                if(res3 > res2)
                {
                    *pInt = res3+1;
                }
                else
                {
                    *pInt = res2+1;
                }
                res = *pInt;
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
    return res;
}

int getHeightLL(binaryTree* avlTree,nodeBinaryPVoidWithData* root)
{
    int res =0;
    void *p = NULL;
    if((root!=NULL)&&(avlTree!=NULL))
    {
        p = avlTree->getNodeLeft(root);
        if(p !=NULL)
        {
            p = avlTree->getNodeLeft(p);
            if(p != NULL)
            {
                res = avlTree->getNodeHeight(avlTree,p);
            }
            else
            {
                res = -1;
            }
        }
        else
        {
            res = -2;
        }
    }
    else
    {
        res = -3; /* null 3 steps */
    }
    return res;
}
int getHeightLR(binaryTree* avlTree,nodeBinaryPVoidWithData* root)
{
    int res =0;
    void *p = NULL;
    if((root!=NULL)&&(avlTree!=NULL))
    {
        p = avlTree->getNodeLeft(root);
        if(p !=NULL)
        {
            p = avlTree->getNodeRight(p);
            if(p!=NULL)
            {
                res = avlTree->getNodeHeight(avlTree,p);
            }
            else
            {
                res = -1;
            }
        }
        else
        {
            res = -2;
        }
    }
    else
    {
        res = -3; /* null 3 steps */
    }
    return res;
}
int getHeightRR(binaryTree* avlTree,nodeBinaryPVoidWithData* root)
{
    int res =0; 
    void *p = NULL;
    if((root!=NULL)&&(avlTree!=NULL))
    {
        p = avlTree->getNodeRight(root);
        if(p !=NULL)
        {
            p = avlTree->getNodeRight(p);
            if(p != NULL)
            {
                res = avlTree->getNodeHeight(avlTree,p);
            }
            else
            {
                res = -1;
            }
        }
        else
        {
            res = -2;
        }
    }
    else
    {
        res = -3; /* null 3 steps */
    }
    return res;
}
int getHeightRL(binaryTree* avlTree,nodeBinaryPVoidWithData* root)
{
    int res =0;
    void *p = NULL;
    if((root!=NULL)&&(avlTree!=NULL))
    {
        p = avlTree->getNodeRight(root);
        if(p !=NULL)
        {
            p = avlTree->getNodeLeft(p);
            if(p != NULL)
            {
                res = avlTree->getNodeHeight(avlTree,p);
            }
            else
            {
                res = -1;
            }
        }
        else
        {
            res = -2;
        }
    }
    else
    {
        res = -3; /* null 3 steps */
    }
    return res;
}

void* reblanceForRemoveNodeAvlTree(binaryTree *avlTree,void *root)
{
    void* result=NULL;
    int hAL,hBL,hCL,hAR,hBR,hCR;
    if(root!=NULL)
    {
        hAL = getHeightLL(avlTree,root);
        hAR=getHeightRR(avlTree,root);
        hBL = getHeightLR(avlTree,root);
        hBR=getHeightRL(avlTree,root);
        hCL = avlTree->getNodeHeight(avlTree,avlTree->getNodeRight(root));
        hCR=avlTree->getNodeHeight(avlTree,avlTree->getNodeLeft(root));
        if((hAL >= hBL)&&(hBL>=hCL))
        {
            result = rotate_LL(avlTree,&root);
        }
        else if((hAR >= hBR)&&(hBR>=hCR))
        { 
            result = rotate_RR(avlTree,&root);
        }
        else if((hBL >= hAL)&&(hAL>=hCL))
        {
            result = rotate_LR(avlTree,&root);
        }
        else if((hBR >= hAR)&&(hAR>=hCR))
        {
            result = rotate_RL(avlTree,&root);
        }
        else
        {
            result = root;
        }
    }
    else
    {
        /* do nothing */
    }
    return result;
}

void* removeNodeForAvlTree(binaryTree *avlTree,void* root)
{
    void *result = root;
    void *child = NULL;
    char fact1 = (root!=NULL);
    if(fact1 == 1)
    { 
        if(avlTree->getNodeLeft(root) == NULL)
        {
              result = avlTree->getNodeRight(root);
              avlTree->deleteNode(avlTree,&root);
        }
        else if(avlTree->getNodeRight(root) ==NULL)
        {
                result = avlTree->getNodeLeft(root);
                avlTree->deleteNode(avlTree,&root);
        }
        else
        {
            child = avlTree->getNodeLeft(root);
            if(avlTree->getNodeRight(child) ==NULL)
            {
                avlTree->swapValue(root,child);
                *(avlTree->getNodeAddrLeft(root)) = avlTree->getNodeLeft(child);
                /* delete child */
                avlTree->deleteNode(avlTree,&child);
            }
            else
            {
                root = swap_and_remove_left_neighbourForAvlTreeNode(avlTree,root,child);
            }
            avlTree->setNodeHeight(avlTree,root);
            result = reblanceForRemoveNodeAvlTree(avlTree,root);

        } 
    }
    else
    {
        /* do nothing */
    }
    return result;
}

void* swap_and_remove_left_neighbourForAvlTreeNode(binaryTree *avlTree,void* parent,void* chlid)
{
    char fact1 = (avlTree!=NULL)&&(parent!=NULL)&&(chlid!=NULL);
    void *result =NULL;
    void *delNode =NULL;
   // nodeBinaryPVoidWithData *chlidNode =(nodeBinaryPVoidWithData*)chlid;
    if(fact1 ==1)
    { 
        fact1 = (avlTree->getNodeRight(chlid) != NULL);
    }
    else
    {
        /* do nothing */
    }
    
    if(fact1 ==1)
    {
        if(avlTree->getNodeRight(avlTree->getNodeRight(chlid)) != NULL)
        {
            parent = swap_and_remove_left_neighbourForAvlTreeNode(avlTree,parent,avlTree->getNodeRight(chlid));
        }
        else
        { 
            avlTree->swapValue(parent,avlTree->getNodeRight(chlid));
            delNode = avlTree->getNodeRight(chlid);
            *(avlTree->getNodeAddrRight(chlid)) = avlTree->getNodeLeft(avlTree->getNodeRight(chlid));
            /* delete old childNpde->right */
            avlTree->deleteNode(avlTree,&delNode);
        }
        avlTree->setNodeHeight(avlTree,chlid);
        avlTree->setNodeHeight(avlTree,parent);
        result = reblanceForRemoveNodeAvlTree(avlTree,parent);
    }
    else
    {
        /* do nothing */
    }
    return result;
}
  

int removeRecForAvlTree(binaryTree *avlTree,void* root,const void *key)
{
    int res =0;
    int resComp =-1;
    char fact1 = ((root!=NULL)&&(avlTree!=NULL)&&(key!=NULL));
    if(fact1==1)
    {
        resComp = avlTree->compareType(avlTree->getKey(root),key);
        switch(resComp)
        {
            case MORE_DEFINE:
                if(avlTree->getNodeLeft(root) != NULL)
                {
                    if( avlTree->compareType(avlTree->getKey(avlTree->getNodeLeft(root)),key) ==EQUAL_DEFINE)
                    {
                        res =1;
                         *(avlTree->getNodeAddrLeft(root)) = removeNodeForAvlTree(avlTree,avlTree->getNodeLeft(root)); 
                        avlTree->numNode--;
                    }
                    else
                    {
                        res = removeRecForAvlTree(avlTree,avlTree->getNodeLeft(root),key);
                        avlTree->setNodeHeight(avlTree,avlTree->getNodeLeft(root));
                        *(avlTree->getNodeAddrLeft(root)) = reblanceForRemoveNodeAvlTree(avlTree,avlTree->getNodeLeft(root));
                    }
                }
                else
                {
                    res = 0;
                }
            break;
            case LESS_DEFINE:
                if(avlTree->getNodeRight(root) != NULL)
                {
                    if( avlTree->compareType(avlTree->getKey(avlTree->getNodeRight(root)),key) ==EQUAL_DEFINE)
                    {
                        res = 1;
                        *(avlTree->getNodeAddrRight(root))= removeNodeForAvlTree(avlTree,avlTree->getNodeRight(root));
                        avlTree->numNode--;
                    }
                    else
                    {
                        res= removeRecForAvlTree(avlTree,avlTree->getNodeRight(root),key);
                        avlTree->setNodeHeight(avlTree,avlTree->getNodeRight(root));
                        *(avlTree->getNodeAddrRight(root)) =  reblanceForRemoveNodeAvlTree(avlTree,avlTree->getNodeRight(root));
                    }
                }
                else
                {
                    res = 0;
                }
            break;
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int removeAvlTreeNodeByKey4FixArr2(binaryTree *avlTree,const void *key)
{
    struct nodeFixedArr4SpecialUsed aNode = {0,0,0,0,0,key,0}; 
    struct nodeFixedArr4SpecialUsed *bNode = &aNode;
    struct mat2_2d *m2Obj=NULL;
    if(avlTree!=NULL)
    {
        if(avlTree->isData>1)
        {
            m2Obj = (struct mat2_2d*)avlTree->parameter3;
            aNode.m_length = m2Obj->m_dat[0]->m_col;
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
    return removeAvlTreeNodeByKey(avlTree,(void*)&bNode);
}
 
 
int forcetTRoot2NullAvLT(binaryTree *avlTree)
{
    int ret = (avlTree != NULL);
    if (ret == 1)
    {
        avlTree->root = NULL;
        avlTree->numNode = 0;
    }
    else
    {
        printf("Error in forcetTRoot2NullAvLT, avlTree is null. ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    return ret;
}
int removeAvlTreeNodeByKey(binaryTree *avlTree,const void *key)
{
    int ret =0;
    char fact1 = (avlTree !=NULL)&&(key!=NULL);
    char fact2= 0;
    if(fact1 ==1)
    {
        fact2 =    (avlTree->isNotDelKey==1)||(((avlTree->deleteKey!=NULL))&&(avlTree->isNotDelKey==0));
        fact1 =    fact2&&(avlTree->compareType != NULL)&&(avlTree->getKey != NULL);
    }
    else
    {
        if(avlTree==NULL)
        {
            printf("avlTree is NULL\n");
        }
        else
        {
            /* do nohting */
        }
        if(key==NULL)
        {
            printf("key is NULL\n");
        }
        else
        {
            /* do nothing */
        }
    }
    if(fact1==1)
    {
        if(avlTree->root == NULL)
        {
            ret =0;
        }
        else
        {
            ret = avlTree->compareType(avlTree->getKey(avlTree->root),key); 
            if(ret == EQUAL_DEFINE)
            {
                ret = 1;
                avlTree->root = removeNodeForAvlTree(avlTree,avlTree->root);
                avlTree->numNode--; 
            }
            else
            {
                ret = removeRecForAvlTree(avlTree,avlTree->root,key);
            }
            avlTree->setNodeHeight(avlTree,avlTree->root);
            avlTree->root= reblanceForRemoveNodeAvlTree(avlTree,avlTree->root);
 
        }
    } 
    else
    {
        if(avlTree->compareType==NULL)
        {
            printf("compareType method is NULL\n");
        }
        else
        {
            /* do nohting */
        } 
        if((avlTree->deleteData==NULL)&&(avlTree->isData<2))
        {
            printf("deleteData method is NULL\n");
        }
        else
        {
            
        }
         if(avlTree->getKey == NULL)
         {
             printf("get Key method of AVLTree is NULL\n");
         }
         else
         {
             /* do nothing */
         }
        if((avlTree->deleteKey==NULL)&&(avlTree->isData<2))
        {
            printf("deleteKey method is NULL\n");
    /*
                 p =avlTree->root;
                void **k = (void**)key;
               void **b = (void**)p->key;
          printf("deleteKey method is NULL - %p %p  key:%p %p\n",p->key,avlTree,(void*)*k,(void*)*b);
       */ }
        else
        {
            
        } 
    }
    return ret;
}
int adjustHeightAVLNode(struct binaryTree* avlTree,void* node)
{
    int res =-1;
    int res2=0;
    int res3=0;
    char fact1 = (avlTree!=NULL);
    avlData *avlDataObj=NULL;
    nodeBinaryPVoidWithData* p = (nodeBinaryPVoidWithData*)node;
    if(fact1 ==1)
    {
        if(p!=NULL)
        {
            if(p->data!=NULL)
            {
                res2 = avlTree->getNodeHeight(avlTree,avlTree->getNodeLeft(node));
                res3 = avlTree->getNodeHeight(avlTree,avlTree->getNodeRight(node));
                avlDataObj = (avlData*)p->data;
                if(res3 > res2)
                {
                    avlDataObj->height = res3+1;
                }
                else
                {
                    avlDataObj->height = res2+1;
                }
                res = avlDataObj->height;
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
    return res;
}

int adjustHeightAVLNodeFixArr(struct binaryTree* avlTree,void* node)
{
    int res =-1;
    int res2=0;
    int res3=0;
    char fact1 = (avlTree!=NULL);
    nodeFixedArr *p = (nodeFixedArr*)node;
    if(fact1 ==1)
    {
        if(p!=NULL)
        {
            res2 = avlTree->getNodeHeight(avlTree,avlTree->getNodeLeft(node));
            res3 = avlTree->getNodeHeight(avlTree,avlTree->getNodeRight(node));
            if(res3 > res2)
            {
                p->m_height = res3+1;
            }
            else
            {
                p->m_height = res2+1;
            }
            res = p->m_height;
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

int adjustHeightAVLNodeFixArr_NBin(struct binaryTree* avlTree,void* node)
{
    int res =-1;
    int res2=0;
    int res3=0;
    char fact1 = (avlTree!=NULL);
    nodeFixedArrNBIn *p = (nodeFixedArrNBIn*)node;
    if(fact1 ==1)
    {
        if(p!=NULL)
        {
            res2 = avlTree->getNodeHeight(avlTree,avlTree->getNodeLeft(node));
            res3 = avlTree->getNodeHeight(avlTree,avlTree->getNodeRight(node));
            if(res3 > res2)
            {
                p->m_height = res3+1;
            }
            else
            {
                p->m_height = res2+1;
            }
            res = p->m_height;
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

void setDelKeyFnForAvlTree(binaryTree* avlTree,void (*delKey)(void*,void*))
{
    avlTree->deleteKey = delKey;
}
void setDelKeyAndDelDataAndCompFnForAvlTree(binaryTree* avlTree,void (*delKey)(void*,void*),void (*delData)(void*,void*),int (*compareType)(const void*,const void*))
{
    if(avlTree!=NULL)
    {
        if((avlTree->isData>=1)&&(delData != NULL))
        {
            avlTree->deleteData = delData;
        }
        else
        {
            /* do nothing */
        }
        if(delKey!=NULL)
        {
            avlTree->deleteKey = delKey;
        }
        else
        {
            /* do nothing */
        }
        if(compareType!=NULL)
        {
            avlTree->compareType = compareType;
        }
        else
        {
            /* do nothing */
        }
        avlTree->configRight = validateConfigIsOk(avlTree);
    }
    else
    {
        /* do nothing */
    }
}
void* insertAvlTreeNoData(binaryTree* avlTree,void** node,const void* key) 
{
    int res =-1;
    void** pKey = (void**)key;
    nodeBinaryPVoidWithData **p = (nodeBinaryPVoidWithData**)node;
    nodeBinaryPVoidWithData *p2 =NULL;
    if(p!=NULL)
    {
        if(*p==NULL)
        {
            *p = (nodeBinaryPVoidWithData*)malloc(sizeof(nodeBinaryPVoidWithData));
            avlTree->constructNodeDataType(*p);
            p2 = *p;
            if(p2 != NULL)
            { 
                p2->key = *pKey; 
                p2->data = (int*)malloc(sizeof(int));
                if(p2->data != NULL)
                {
                    *((int*)p2->data)=0; /* height */
                }
                else
                {
                    *p = NULL;
                    free(p2);
                    p2 = NULL;
                    printf("allocation null1\n");
                }
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            res = avlTree->compareType(&((*p)->key),key); 
            switch(res)
            {
                case MORE_DEFINE:
                    p2 = (nodeBinaryPVoidWithData*)insertAvlTreeNoData(avlTree,(void**)&((*p)->left),key);
                    res = avlTree->getNodeHeight(avlTree,(*p)->left)- avlTree->getNodeHeight(avlTree,(*p)->right);
                    if((res ==2)&&((*p)->left!=NULL))
                    {
                        res = avlTree->compareType(&((*p)->left->key),key);
                        switch(res)
                        {
                            case MORE_DEFINE:
                                *p = (nodeBinaryPVoidWithData*)rotate_LL(avlTree,(void**)p);
                            break;
                            case LESS_DEFINE:
                                *p = (nodeBinaryPVoidWithData*)rotate_LR(avlTree,(void**)p);
                            break;
                        }
                    }
                    else
                    {
                        /* do nothing */
                    }
                break;
                case LESS_DEFINE:
                    p2 = (nodeBinaryPVoidWithData*)insertAvlTreeNoData(avlTree,(void**)&((*p)->right),key);
                    res = avlTree->getNodeHeight(avlTree,(*p)->right)- avlTree->getNodeHeight(avlTree,(*p)->left);
                    if((res ==2)&&((*p)->right!=NULL))
                    {
                        res = avlTree->compareType(&((*p)->right->key),key);
                        switch(res)
                        {
                            case MORE_DEFINE:
                                *p = (nodeBinaryPVoidWithData*)rotate_RL(avlTree,(void**)p);
                            break;
                            case LESS_DEFINE:
                                *p = (nodeBinaryPVoidWithData*)rotate_RR(avlTree,(void**)p);
                            break;
                        }
                    }
                    else
                    {
                        /* do nothing */
                    } 
                break;
                default:
                    res =0;
                    p2=NULL;
                break;
            }
            avlTree->setNodeHeight(avlTree,*p);
        }
    }
    else
    {
        /* do nothing */
    } 
    return p2;
}
void* insertAvlTreeData2(binaryTree* avlTree,void** node,const void* key)
{
    int res = -1;    
    void** pKey = (void**)key;
    nodeBinaryPVoidWithData **p = (nodeBinaryPVoidWithData**)node;
    nodeBinaryPVoidWithData *p2 =NULL;
    if(p != NULL)
    {
        if(*p==NULL)
        {
            *p = (nodeBinaryPVoidWithData*)malloc(sizeof(nodeBinaryPVoidWithData));
            avlTree->constructNodeDataType(*p);
            p2 = *p;
            if(p2 != NULL)
            {
                p2->key = *pKey;
                p2->data = (avlData*)malloc(sizeof(avlData));
                if(p2->data != NULL)
                {
                    ((avlData*)(p2->data))->data = NULL;
                    ((avlData*)(p2->data))->height = 0;
                }
                else
                {
                    *p = NULL;
                    free(p2);
                    p2 =NULL;
                    printf("allocation null2\n");
                }
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            res = avlTree->compareType(&((*p)->key),key);
            switch(res)
            {
                case MORE_DEFINE:
                    p2 = (nodeBinaryPVoidWithData*)insertAvlTreeData2(avlTree,(void**)&((*p)->left),key);
                    res = avlTree->getNodeHeight(avlTree,(*p)->left)- avlTree->getNodeHeight(avlTree,(*p)->right);
                    if((res == 2)&&((*p)->left!=NULL))
                    {
                        res = avlTree->compareType(&((*p)->left->key),key);
                        switch(res)
                        {
                            case MORE_DEFINE:
                                *p = (nodeBinaryPVoidWithData*)rotate_LL(avlTree,(void**)p);
                            break;
                            case LESS_DEFINE:
                                *p = (nodeBinaryPVoidWithData*)rotate_LR(avlTree,(void**)p);
                            break;
                        }
                    }
                    else
                    {
                        /* do nothing */
                    }
                break;
                case LESS_DEFINE:
                    p2 = (nodeBinaryPVoidWithData*)insertAvlTreeData2(avlTree,(void**)&((*p)->right),key);
                    res = avlTree->getNodeHeight(avlTree,(*p)->right)- avlTree->getNodeHeight(avlTree,(*p)->left);
                    if((res == 2)&&((*p)->right!=NULL))
                    {
                        res = avlTree->compareType(&((*p)->right->key),key);
                        switch(res)
                        {
                            case MORE_DEFINE:
                                *p = (nodeBinaryPVoidWithData*)rotate_RL(avlTree,(void**)p);
                            break;
                            case LESS_DEFINE:
                                *p = (nodeBinaryPVoidWithData*)rotate_RR(avlTree,(void**)p);
                            break;
                        }
                    }
                    else
                    {
                        /* do nothing */
                    }
                break;
                default:
                    res =0;
                    printf("Cannot Inserted key is redundant : avlTree.h : %d\n",__LINE__);
                    printf("key1:%p  key2 : %p - p2=%p\n",(*p)->key,*pKey,p2);
                    p2=NULL;
                break;
            }
            avlTree->setNodeHeight(avlTree,*p);
        }
    }
    else
    {
        /* do nothing */
    }
    return p2;
}

void* insertAvlTreeData3(binaryTree* avlTree,void** node,const void* key)
{
    int res =-1;    
    void** pKey = (void**)key;
    nodeFixedArr **p = (nodeFixedArr**)node;
    nodeFixedArr *p2 =NULL;
    if(p!=NULL)
    {
        if(*p==NULL)
        {
            *p = (nodeFixedArr*)*pKey;
            p2 = *p;
        }
        else
        {
            
            res = avlTree->compareType(p,key);
            switch(res)
            {
                case MORE_DEFINE:
                    p2 = (nodeFixedArr*)insertAvlTreeData3(avlTree,(void**)&((*p)->m_lf),key);
                    res = avlTree->getNodeHeight(avlTree,(*p)->m_lf)- avlTree->getNodeHeight(avlTree,(*p)->m_rt);
                    if((res == 2)&&((*p)->m_lf!=NULL))
                    {
                        res = avlTree->compareType(&((*p)->m_lf),key);
                        switch(res)
                        {
                            case MORE_DEFINE:
                                *p = (nodeFixedArr*)rotate_LL(avlTree,(void**)p);
                            break;
                            case LESS_DEFINE:
                                *p = (nodeFixedArr*)rotate_LR(avlTree,(void**)p);
                            break;
                        }
                    }
                    else
                    {
                        /* do nothing */
                    }
                break;
                case LESS_DEFINE:
                    p2 = (nodeFixedArr*)insertAvlTreeData3(avlTree,(void**)&((*p)->m_rt),key);
                    res = avlTree->getNodeHeight(avlTree,(*p)->m_rt)- avlTree->getNodeHeight(avlTree,(*p)->m_lf);
                    if((res == 2)&&((*p)->m_rt!=NULL))
                    {
                        res = avlTree->compareType(&((*p)->m_rt),key);
                        switch(res)
                        {
                            case MORE_DEFINE:
                                *p = (nodeFixedArr*)rotate_RL(avlTree,(void**)p);
                            break;
                            case LESS_DEFINE:
                                *p = (nodeFixedArr*)rotate_RR(avlTree,(void**)p);
                            break;
                        }
                    }
                    else
                    {
                        /* do nothing */
                    }
                break;
                default:
                    res =0;
                    printf("Cannot Inserted key is redundant : avlTree.h : %d\n",__LINE__);
                    printf("key1:%p  key2 : %p - p2=%p\n",(*p)->m_dat,*pKey,p2);
                    p2=NULL;
                break;
            }
            avlTree->setNodeHeight(avlTree,*p);
        }
    }
    else
    {
        /* do nothing */
    }
    return p2;
}

void* insertAvlTreeData4(binaryTree* avlTree,void** node,const void* key)
{
    int res =-1;    
    void** pKey = (void**)key;
    void **p = (void**)node;
    nodeFixedArrNBIn *p2 =NULL;
    if((p!=NULL)&&(pKey !=NULL))
    {
        if(*p==NULL)
        {
            *p =  getDatNextMt22d((void*)(avlTree->parameter3));
            constructFixArrNodeNBin_Bin(*p);
            p2 = *p;
            if(*p !=NULL)
            {
                
                *((void**)(avlTree->getKey(*p))) = (void*)*pKey;
            }
            else
            {
                printf("Inserted nodeFixedArrNBIn error ln:%d, Fl:%s\n",__LINE__,__FILE__);
            }
            if(*((void**)(avlTree->getKey(*p))) ==NULL)
            {
                printf("Key is null in Insertion nodeFixedArrNBIn error ln:%d, Fl:%s\n",__LINE__,__FILE__);
            }
            else
            {
                /* do nothign */
            }
        }
        else
        {
            
            res = avlTree->compareType(avlTree->getKey(*p),key);
            switch(res)
            {
                case MORE_DEFINE:
                    p2 = (nodeFixedArrNBIn*)insertAvlTreeData4(avlTree,avlTree->getNodeAddrLeft(*p),key);
                    res = avlTree->getNodeHeight(avlTree,avlTree->getNodeLeft(*p))- avlTree->getNodeHeight(avlTree,avlTree->getNodeRight(*p));
                    if((res ==2)&&(avlTree->getNodeLeft(*p) != NULL))
                    {
                        res = avlTree->compareType(avlTree->getKey(avlTree->getNodeLeft(*p)),key);
                        switch(res)
                        {
                            case MORE_DEFINE:
                                *p = (nodeFixedArrNBIn*)rotate_LL(avlTree,(void**)p);
                            break;
                            case LESS_DEFINE:
                                *p = (nodeFixedArrNBIn*)rotate_LR(avlTree,(void**)p);
                            break;
                        }
                    }
                    else
                    {
                        /* do nothing */
                    }
                break;
                case LESS_DEFINE:
                    p2 = (nodeFixedArrNBIn*)insertAvlTreeData4(avlTree,avlTree->getNodeAddrRight(*p),key);
                    res = avlTree->getNodeHeight(avlTree,avlTree->getNodeRight(*p))- avlTree->getNodeHeight(avlTree,avlTree->getNodeLeft(*p));
                    if((res == 2)&&(avlTree->getNodeRight(*p) != NULL))
                    {
                        res = avlTree->compareType(avlTree->getKey(avlTree->getNodeRight(*p)),key);
                        switch(res)
                        {
                            case MORE_DEFINE:
                                *p = (nodeFixedArrNBIn*)rotate_RL(avlTree,(void**)p);
                            break;
                            case LESS_DEFINE:
                                *p = (nodeFixedArrNBIn*)rotate_RR(avlTree,(void**)p);
                            break;
                        }
                    }
                    else
                    {
                        /* do nothing */
                    }
                break;
                default:
                    res =0;
                    printf("Cannot Inserted key is redundant : avlTree.h : %d\n",__LINE__);
                    printf("key1:%p  key2 : %p - p2=%p\n",*((void**)(avlTree->getKey(*p))),*pKey,p2);
                    p2=NULL;
                break;
            }
            avlTree->setNodeHeight(avlTree,*p);
        }
    }
    else
    {
        printf("Inserted nodeFixedArrNBIn error ln:%d, Fl:%s\n",__LINE__,__FILE__);
    }
    return p2;
}

void* insertAvlTreeData(binaryTree* avlTree,const void* key)
{
    char fact1 = (avlTree != NULL)&&(key!=NULL);
    void* p = NULL;
    if(fact1 == 1)
    {
        fact1 = (avlTree->compareType !=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(fact1 == 1)
    {        
        /* isWithData==0 , data = height */
        if (avlTree->isData == 0)
        {
            p =insertAvlTreeNoData(avlTree,&(avlTree->root),key);
        }
        else if (avlTree->isData == 1)
        {
            p = insertAvlTreeData2(avlTree,&(avlTree->root),key);
        }
        if(p!= NULL)
        {
            avlTree->numNode++;
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
    return p;
}
void* insertAvlT4FixArrNodeBuiltIn(binaryTree* avlTree,const void* key)
{
    char fact1 = (avlTree != NULL)&&(key!=NULL);
    void* p = NULL;
    if(fact1 == 1)
    {
        fact1 = (avlTree->compareType !=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(fact1 == 1)
    {       
        p = insertAvlTreeData3(avlTree,&(avlTree->root),key);
        if(p!= NULL)
        {
            avlTree->numNode++;
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        printf("Error insertAVL T 3 mehtod, Comp fn addr:%p, ln:%d file:%s\n",avlTree->compareType,__LINE__,__FILE__);
    }
    return p;
}

void* insertAvlT4FixArrNodeNoBuiltIn(binaryTree* avlTree,const void* key)
{
    char fact1 = (avlTree != NULL)&&(key!=NULL);
    void* p = NULL;
    if(fact1 == 1)
    {
        fact1 = (avlTree->compareType !=NULL);
    }
    else
    {
        /* do nothing */
    }
    if(fact1 ==1)
    {       
        p =insertAvlTreeData4(avlTree,&(avlTree->root),key);
        if(p!= NULL)
        {
            avlTree->numNode++;
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
    return p;
}


void* rotate_LL(binaryTree* avlTree,void** node)
{
    void *p = avlTree->getNodeLeft(*node);
    *(avlTree->getNodeAddrLeft(*node)) = avlTree->getNodeRight(p);
    *(avlTree->getNodeAddrRight(p)) = *node;
    /* adjustHeight of node, node.left and p*/

    avlTree->setNodeHeight(avlTree,*node);
    avlTree->setNodeHeight(avlTree,avlTree->getNodeLeft(*node));
    avlTree->setNodeHeight(avlTree,p);
    *node = p;
    return *node;
}
void* rotate_RR(binaryTree* avlTree,void** node)
{
    void *p = avlTree->getNodeRight(*node);
    *(avlTree->getNodeAddrRight(*node)) = avlTree->getNodeLeft(p);
    *(avlTree->getNodeAddrLeft(p)) =*node;
    /* adjustHeight of node, node.right and p*/
    avlTree->setNodeHeight(avlTree,*node);
    avlTree->setNodeHeight(avlTree,avlTree->getNodeRight(*node));
    avlTree->setNodeHeight(avlTree,p);
    *node =p;
    return *node;
}
void* rotate_LR(binaryTree* avlTree,void** node)
{
    void *leftChild = avlTree->getNodeLeft(*node);
    void *resultNode = avlTree->getNodeRight(leftChild);
    *(avlTree->getNodeAddrLeft(*node)) = avlTree->getNodeRight(resultNode);
    *(avlTree->getNodeAddrRight(leftChild)) = avlTree->getNodeLeft(resultNode);
    *(avlTree->getNodeAddrRight(resultNode))  =*node;
    *(avlTree->getNodeAddrLeft(resultNode)) =leftChild;
    /* adjust Height of node,leftChild,resultNode*/
    avlTree->setNodeHeight(avlTree,*node);
    avlTree->setNodeHeight(avlTree,leftChild);
    avlTree->setNodeHeight(avlTree,resultNode);
    return resultNode;
}
void* rotate_RL(binaryTree* avlTree,void** node)
{
    void *rightChild =  avlTree->getNodeRight(*node);
    void *resultNode =  avlTree->getNodeLeft(rightChild);
    *(avlTree->getNodeAddrRight(*node)) = avlTree->getNodeLeft(resultNode);
    *(avlTree->getNodeAddrLeft(rightChild)) = avlTree->getNodeRight(resultNode);
    *(avlTree->getNodeAddrLeft(resultNode))=  *node;
    *(avlTree->getNodeAddrRight(resultNode)) = rightChild;
    /* adjust Height of node,rightChild,resultNode*/
    avlTree->setNodeHeight(avlTree,*node);
    avlTree->setNodeHeight(avlTree,rightChild);
    avlTree->setNodeHeight(avlTree,resultNode);
    return resultNode;
}
 
void swapValOfAvlTFArrNode(void* node,void* node2)
{
    void *tmp=NULL;
    struct nodeFixedArr *a= (struct nodeFixedArr *)node;
    struct nodeFixedArr *b= (struct nodeFixedArr*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->m_dat;
        a->m_dat = b->m_dat;
        b->m_dat = tmp;
        tmp = a->m_dat2;
        a->m_dat2 = b->m_dat2;
        b->m_dat2 = tmp;
    }
    else
    {
        /* do nohting */
    }
}
void swapValOfAvlTFArrNode_NBin(void* node,void* node2)
{
    void *tmp=NULL;
    struct nodeFixedArrNBIn *a= (struct nodeFixedArrNBIn *)node;
    struct nodeFixedArrNBIn *b= (struct nodeFixedArrNBIn*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->m_dat;
        a->m_dat = b->m_dat;
        b->m_dat = tmp;
        tmp = a->m_dat2;
        a->m_dat2 = b->m_dat2;
        b->m_dat2 = tmp;
    }
    else
    {
        /* do nohting */
    }
}
void swapValueOfAvlTreeNodeWithData(void* node,void* node2)
{
    avlData *avlNode =NULL;
    avlData *avlNode2 =NULL;
    void *tmp2=NULL;
    void *tmp=NULL;
    nodeBinaryPVoidWithData *a= (nodeBinaryPVoidWithData *)node;
    nodeBinaryPVoidWithData *b= (nodeBinaryPVoidWithData*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        avlNode = (avlData*)a->data;
        avlNode2 = (avlData*)b->data;
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
        if((avlNode!=NULL)&&(avlNode2!=NULL))
        {
            tmp2= avlNode->data;
            avlNode->data = avlNode2->data;
            avlNode2->data = (avlData*)tmp2;
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
void swapValueOfAvlTreeNodeWithNoData(void* node,void* node2)
{    
    void *tmp=NULL;
    nodeBinaryPVoidWithData *a= (nodeBinaryPVoidWithData *)node;
    nodeBinaryPVoidWithData *b= (nodeBinaryPVoidWithData*)node2;
    if((node!=NULL)&&(node2!=NULL))
    {
        tmp = a->key;
        a->key = b->key;
        b->key = tmp;
    }
    else
    {
        /* do nohting */
    }
}