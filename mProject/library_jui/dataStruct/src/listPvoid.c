#include "listPvoid.h"
#include "simMat2.h"
void constructorPVoidList(pVoidList *list)
{/*
    list->first = NULL;
    list->last  = NULL;
    list->cur   = NULL;
    list->currentIndex = 0;
    list->numOfNode   = 0;
    list->isFreeData = 1;
    list->deleteData = NULL;
    list->otherSrc = NULL;
    */
    void *paraFunct[8];
    paraFunct[0] = &getNxpVoidEle;
    paraFunct[1] = &getBkpVoidEle;
    paraFunct[2] = &getDatpVoidEle;
    paraFunct[3] = &setNxpVoidEle;
    paraFunct[4] = &setBkpVoidEle;
    paraFunct[5] = &setDatpVoidEle;
    paraFunct[6] = &getAllocatePVoidEle;
    paraFunct[7] = &freeAllocPVoidEle;
    /*
    list->getNext = paraFunct[0];
    list->getBack = paraFunct[1];
    list->getDat =  paraFunct[2];
    list->setNext = paraFunct[3];
    list->setBack = paraFunct[4];
    list->setDat =  paraFunct[5];
    list->getAllocate = paraFunct[6];*/
    
    constrPVL2((void*)list,NULL,paraFunct);
    
}

void constrPVL2(void *list1,void *othSrc,void **paraFunct)
{
    pVoidList *list = (pVoidList*)list1;
    list->first = NULL;
    list->last  = NULL;
    list->cur   = NULL;
    list->currentIndex = 0;
    list->numOfNode   = 0;
    list->isFreeData = 1;
    list->deleteData = NULL;
    list->otherSrc = othSrc;
    
    list->getNext = (paraFunct[0]);
    list->getBack = (paraFunct[1]);
    list->getDat = (paraFunct[2]);
    list->setNext = (paraFunct[3]);
    list->setBack = (paraFunct[4]);
    list->setDat = (paraFunct[5]);
    list->getAllocate = (paraFunct[6]);
    list->freeAlloc = (paraFunct[7]);
    
}

void setIsFreeDataOfPVoidList(void *obj,int value,void *delDatFunct)
{
    pVoidList *list = (pVoidList*)obj;
    if(list!=NULL)
    {
        if((value==0)||(value==1))
        {
            list->isFreeData = value;
            list->deleteData = delDatFunct;
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
void setCurrentPointerPVoidList(pVoidList* list,int index)
{
    getDataPVoidList(list,index);
}
void resetCurrentPointerPVoidList(pVoidList* list)
{
    if(list!=NULL)
    {
        list->cur = NULL;
        list->currentIndex =0;
    }
    else
    {
        /* do nothing */
    }
}
int addDataPtPVoidList(pVoidList *list,void **data)
{
    if(list == NULL || data == NULL)
    { 
        return 0; /* cannot add Data */
    }
    else
    {
        /* do nothing */
    }
    if(list->numOfNode == 0)
    {
        list->first = list->getAllocate(list->otherSrc);
        if(list->first == NULL)
        { 
            return 0; /* cannot add Data */
        }
        else
        {
            list->last = list->first;
            list->setDat(list->first,*data);
            list->setNext(list->last,NULL);
            list->setBack(list->last,NULL);
            list->numOfNode++;
        }
    }
    else
    {
        list->setNext(list->last,list->getAllocate(list->otherSrc));
        if(list->getNext(list->last) == NULL)
        { 
            return 0; /* cannot add Data */
        }
        else
        {
            setNB(list,list->last,list->last);
            list->last = list->getNext(list->last);
            list->setDat(list->last,*data);
            list->setNext(list->last,NULL);
            list->numOfNode++;
        }
    }
    return 1; /* complete */
}
int getCurrentIndexOfPVoidList(pVoidList* list)
{
    int index =0;
    if(list != NULL)
    {
        index = list->currentIndex;
    }
    else
    {
        /* do nothing */
    }
    return index;
}
int addDataPVoidList(pVoidList *list,void* data)
{
    return addDataPtPVoidList(list,&data);
}

void freeNode(void *list1,void *node)
{
    pVoidList *pVL = (pVoidList*)list1;
    void *p =NULL;
    if((pVL != NULL)&&(node != NULL))
    {
        p = pVL->getDat(node);
        if((pVL->isFreeData == 1)&&(p!=NULL))
        {
            if(pVL->deleteData != NULL)
            {
                pVL->deleteData(p);
            }
            else
            {
                free(p);
            }
            p = NULL;
        }
        else
        {
            /* do nothing */
        }
        pVL->setDat(node,NULL);
        pVL->freeAlloc(pVL->otherSrc,node);
    }
    else
    {
        /* do nothing */
    }
}
void makeEmptyPVoidList(pVoidList *list)
{
    void *p=NULL;
    void *p2=NULL;
    p = list->first;
    while(p!=NULL)
    { 
        /* delete_something before free */
        /* free */
        p2 =p;
        p= list->getNext(p);
        freeNode(list,p2);
    }
    list->first =NULL;
    list->last =NULL;
    list->numOfNode = 0;
    list->cur = NULL;
    list->currentIndex =0;
}
void destructorPVoidList(pVoidList *list)
{
    makeEmptyPVoidList(list);
}
int searchPVoidListPt(pVoidList* list,void** data)
{
    void *p=NULL;
    int index = 0;
    if(list->cur != NULL)
    {
        index =list->currentIndex;
        for(p = list->cur;p!=NULL;p=list->getNext(p))
        {
            if(list->getDat(p) == *data)
            {
                return index;
            }
            else
            {
                index++;
            }
        }
    }
    else
    {
        /* do nothing */
    }
    index =0;
    for(p = list->first;p != list->cur;p=list->getNext(p))
    {
        if(list->getDat(p)== *data)
        {
            return index;
        }
        else
        {
            index++;
        }
    }
    return -1;
}
int searchPVoidList(pVoidList* list,void* data)
{
    return searchPVoidListPt(list,&data);
}
pVoidElement* getAddressElementPVoidList(pVoidList* list,int index)
{
    void *p = NULL;
    int dummyValue =0;
    if(index < 0|| list ==NULL || index >= list->numOfNode)
    { 
        list->cur = NULL;
        list->currentIndex=0;
        printf("wrong index or int list is NULL(%p) , index(%d): %d\n",list,list->numOfNode,index);
    }
    else
    {
        if(list->currentIndex > index)
        {
            p = list->first;
            dummyValue = index;
            list->currentIndex = index;
            while((dummyValue--)&&(p!=NULL))
            {
                p = list->getNext(p);
            }
            list->cur = p;
        }
        else if(list->currentIndex <=index)
        {
            if(list->cur != NULL)
            {
                p = list->cur;
            }
            else
            {
                p = list->first;
            }
            dummyValue = index-list->currentIndex;
            list->currentIndex = index;
            while((dummyValue--)&&(p!=NULL))
            {
                p = list->getNext(p);
            }
            list->cur = p;
        }
        else
        {
            /* do nothing */
        }
    }
    return p;
} 
int replaceValInPVoidList(pVoidList *list,void *data,int index)
{
    void *node=NULL;
    int fact1 = (list!=NULL)&&(data!=NULL)&&(index>=0);
    if(fact1 ==1)
    {
        fact1 = (int)(index<countPVoidList(list));
    }
    else
    {
        printf("Error replaceValInPVoidList: Parameter are invalid : %d \n",__LINE__);
    }
    if (fact1 == 1)
    {
        node =  getAddressElementPVoidList(list,index);
        fact1 = (int)(node!=NULL);
    }
    else
    {
        printf("Error replaceValInPVoidList: Index exceed :%d\n",__LINE__);
    }
    if (fact1 == 1)
    {        /* delete_something before free */
        /* free */
        if((list->isFreeData == 1)&&(list->getDat(node)!= NULL))
        {
            if(list->deleteData==NULL)
            {
                /* do nothing*/
            }
            else
            {
                list->deleteData(list->getDat(node));
            }
            list->setDat(node,NULL);
        }
        else
        {
            /* do nothing */
        }
        list->setDat(node,data);
    }
    else
    {
        /* do nohting */
    }
    return fact1;
}
void* getDataPVoidList(pVoidList* list,int index)
{
    void *p = NULL;
    int dummyValue =0;
    if(index < 0|| list ==NULL || index >= list->numOfNode)
    {
        void* a =NULL;
        list->cur = NULL;
        list->currentIndex=0;
        printf("wrong index or int list is NULL(%p) , index(%d): %d\n",list,list->numOfNode,index);
        return a;
    }
    else
    {
        if(list->currentIndex > index)
        {
            p = list->first;
            dummyValue = index;
            list->currentIndex = index;
            while((dummyValue--)&&(p!=NULL))
            {
                p = list->getNext(p);
            }
            list->cur = p;
        }
        else if(list->currentIndex <=index)
        {
            if(list->cur != NULL)
            {
                p = list->cur;
            }
            else
            {
                p = list->first;
            }
            dummyValue = index-list->currentIndex;
            list->currentIndex = index;
            while((dummyValue--)&&(p!=NULL))
            {
                p = list->getNext(p);
            }
            list->cur = p;
        }
        else
        {
            /* do nothing */
        }
        return list->getDat(p);
    }
}
void* getLastDataPVoidList(pVoidList *list)
{
    return getDataPVoidList(list,list->numOfNode -1);
}
int countPVoidList(pVoidList *list)
{
    if(list == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    return list->numOfNode;
}

void pullNodeOutFromPVoidList(pVoidList* list,pVoidElement* node1)
{
    if((node1!=NULL)&&(list!=NULL)&&(list->numOfNode>0))
    {
        if((node1 !=list->first)&&(node1 !=list->last))
        {
            setBN(list,node1,list->getNext(node1));
            setNB(list,node1,list->getBack(node1));
        }       
        else if((node1 == list->first) &&(node1 != list->last))
        {
            list->first = list->getNext(list->first);
            list->setBack(list->first,NULL);
        }
        else if((node1 !=list->first) &&(node1 == list->last))
        {
            list->last = list->getBack(list->last);
            list->setNext(list->last,NULL);
        }
        else
        {
            list->last = NULL;
            list->first=NULL;
        }        
        list->cur = NULL;
        list->currentIndex= 0;
        list->numOfNode--;
    }
    else
    {
        /* do nothing */
    }
}
int deleteIndexElementPVoidList(pVoidList *list,int index)
{
    void *p=NULL;
    int index1 = 0;
    if(index < 0|| list ==NULL)
    {
        printf("list is NULL or bad index %d\n",index);
        return 0;
    }
    else if((index >= list->numOfNode) ||(list->first ==NULL))
    {
        printf("index >= list->numOfNode %d %d\n",index,list->numOfNode);
        return 0;
    }
    else if(index==0)
    {
        p=list->first;
    }
    else if(index==(list->numOfNode-1))
    {
        p=list->last;
    }
    else
    {
        for(p=list->first;p !=NULL;p = list->getNext(p))
        {
            if(index == index1)
            {
                break;
            }
            else
            {
                index1++;
            }
        }
    }       
    if(p!=NULL)
    {
        pullNodeOutFromPVoidList(list,p);
        freeNode(list,p);
        p = NULL;
    }
    else
    {
        /* do nothing */
    }
    return 1;
}
int deleteElementPVoidListPt(pVoidList *list,void** data)
{
    int index = searchPVoidListPt(list,data);
    return deleteIndexElementPVoidList(list,index);
}
int deleteElementPVoidList(pVoidList *list,void* data)
{
    return deleteElementPVoidListPt(list,&data);
}
void* popPVoidList(pVoidList* list)
{
    void* a =NULL;
    if(list ==NULL)
    {
        printf("list is NULL\n");
    }
    else if(list->numOfNode!=0)
    { 
        a = list->getDat(list->last);
        list->setDat(list->last,NULL);
        deleteIndexElementPVoidList(list,list->numOfNode-1);
    }
    return a;
}
int pushPVoidListPt(pVoidList* list,void** data)
{
    return addDataPtPVoidList(list,data);
}
int pushPVoidList(pVoidList* list,void* data)
{
    return addDataPtPVoidList(list,&data);
}
int enQueuePVoidList(pVoidList* list,void* data)
{
    return enQueuePVoidListPt(list,&data);
}
int enQueuePVoidListPt(pVoidList* list,void** data)
{
    if(list == NULL || data ==NULL)
    {
        return 0;
    }
    else
    {
        void *p  = list->getAllocate(list->otherSrc);
        if(p == NULL)
        {
            return 0;
        }
        else
        {
            list->setDat(p,*data);
        }
        list->setBack(p,NULL);
        list->setNext(p,list->first);
        list->setBack(list->first,p);
        list->first = p;
        if(list->last ==NULL)
        {
            list->last =p;
        }
        else
        {
            /* do nothing */
        }
        list->numOfNode++;
    }
    return 1;
}
void* deQueuePVoidList(pVoidList* list)
{
    return popPVoidList(list);
}
int swapElementPVoidListPt(pVoidList *list,int index1,int index2)
{
    if(list == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    if(list->numOfNode <= index1 || list->numOfNode <=index2 ||
       index1 == index2 || index1 <0 || index2 < 0)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    void *p1=NULL,*p2=NULL,*p3,*p4;
    int index =0;
    if(index1 > index2)
    {
        index =index1;
        index1=index2;
        index2=index;
    }
    else
    {
        /* do nothing */
    }
    index =0;
    for(p2 = list->first;p2 != NULL;p2 =list->getNext(p2))
    {
        if(index ==index1)
        {
            p1    = p2; 
            p3    = list->getNext(p1);
            p4    = list->getBack(p1);
        }
        else if(index ==index2)
        {
            if(p1 == list->first)
            {
                list->first = p2;
            }
            else if(p2 == list->first)
            {
                list->first = p1;
            }
            if(p1 == list->last)
            {
                list->last = p2;
            }
            else if(p2 == list->last)
            {
                list->last = p1;
            }
            if(list->getNext(p1)!= NULL)
            {
                setNB(list,p1,p2);
            }
            else
            {
                /* do nothing */
            }
            if(list->getBack(p1) != NULL)
            {
                setBN(list,p1,p2);
            }
            else
            {
                //do nothing
            }
            if(list->getNext(p2) != NULL)
            {
                setNB(list,p2,p1);
            }
            else
            {
                /* do nothing */
            }
            if(list->getBack(p2) != NULL)
            {
                setBN(list,p2,p1);
            }
            else
            {
                /* do nothing */
            }
            
            list->setNext(p1,list->getNext(p2));
            list->setBack(p1,list->getBack(p2));
            list->setNext(p2,p3);
            list->setBack(p2,p4);
            
            break;
        }
        else
        {
            /* do nothing */
        }
        index++;
    }
    return 1;

}
int swapElementPVoidList(pVoidList *list,int index1,int index2)
{
    if(list == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    if(list->numOfNode <= index1 || list->numOfNode <=index2 ||
       index1 == index2 || index1 <0 || index2 < 0)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    void *data1 = NULL;
    void *p1=NULL,*p2=NULL;
    int index =0;
    if(index1 > index2)
    {
        index =index1;
        index1=index2;
        index2=index;
    }
    else
    {
        /* do nothing */
    }
    index =0;
    for(p2 = list->first;p2 != NULL;p2 = list->getNext(p2))
    {
        if(index ==index1)
        {
            p1    = p2;
            data1 = list->getDat(p2);
            
        }
        else if(index ==index2)
        {
            
            list->setDat(p1,list->getDat(p2));
            list->setDat(p2,data1);
            break;
        }
        else
        {
            /* do nothing */
        }
        index++;
    }
    return 1;
}
void printPVoidList(pVoidList *list,int opt)
{
    if(list == NULL||list->numOfNode == 0)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    void *p = list->first;
    if(opt < 0)
    {
        opt = -opt;
        for(p=list->first;p!=NULL;p =list->getNext(p))
        {
            if(opt ==4)
            {
              printf("B:%p O:%p ",list->getBack(p),p);
            }
            else 
            {
                /* do nothing */
            }
            //print Elemet, printf is an example function
            printf("D:%p",list->getDat(p));
            if(opt ==1)
            {
                printf(" ");
            }
            else if(opt ==2)
            {
                printf("\n");
            }
            else if(opt ==3)
            {
                printf("->");
            }
            else if(opt ==4)
            {
                printf(" N:%p\n",list->getNext(p));
            
            }
        }
    }
    else
    {
        for(p=list->last;p!=NULL;p =list->getBack(p))
        {
            if(opt ==4)
            {
              printf("B:%p O:%p ",list->getBack(p),p);
            }
            else 
            {
                //do nothing
            }
            //print Elemet, printf is an example function
            printf("D:%p",list->getDat(p));
            if(opt ==1)
            {
                printf(" ");
            }
            else if(opt ==2)
            {
                printf("\n");
            }
            else if(opt ==3)
            {
                printf("->");
            }
            else if(opt ==4)
            {
                printf(" N:%p\n",list->getNext(p));
            
            }
        }
    }
    printf("\n");
}
/*
vector_int convertTovector_int(pVoidList *list)
{
    vector_int dummy = new_vector_int(0);
    if(list == NULL)
    {
        return dummy;
    }
    else
    {
        int index =0;
        pVoidElement *p = list->first;
        int numList = list->numOfNode;
        dummy       = new_vector_int(numList);
        for(index =0;index<numList;index++)
        {
            dummy.data[index] = p->data;
            p = p->next;
        }
    }

    return dummy;
}*/
int copyPVoidList(pVoidList *lsh,pVoidList *rsh)
{
     int res = 0;
     int index=0;
     int num = 0;
     void* dat1;
     if((lsh!=rsh) && (lsh!=NULL) &&(rsh !=NULL))
     {
         makeEmptyPVoidList(lsh);
         num = rsh->numOfNode;
         for(index = 0;index < num;index++)
         {
             dat1 = getDataPVoidList(rsh,index);
             res = addDataPtPVoidList(lsh,&dat1);
             if(res == 0)
             {
                 makeEmptyPVoidList(lsh);
                 index = num;
             }
             else
             {
                  /* do nothing */
             }
         }
     }
     else
     {
         /* do nothing */
     }
     return res;
}
int insetWithIndexPVoidList(pVoidList *list,void* data,int index)
{
    int res = 0;
    int num = 0;
    void *p = NULL;
    void *np = NULL;
    int index2 = 0;
    if(list !=NULL && index >=0)
    {
        num = list->numOfNode;
        if(index == num-1)
        {
           res = addDataPtPVoidList(list,&data);
        }  
        else if(index == 0)
        {
           res = enQueuePVoidListPt(list,&data);
           res &= swapElementPVoidListPt(list,0,1);
        }
        else if(index < num)
        {
            p = list->first;
            for(index2=0;index2<num;index2++)
            {
                if(index==index2)
                {
                    np = list->getAllocate(list->otherSrc);
                    if(np!=NULL)
                    { 
                        list->setBack(np,p);
                        list->setNext(np,list->getNext(p));
                        setNB(list,p,np);
                        list->setNext(p,np);
                        list->setDat(np,data);
                        list->numOfNode++;
                        res = 1;
                    }
                    else
                    {
                        /* do nothing */
                    }
                    index2 =  num;
                }
                else
                {
                    p=list->getNext(p);
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
    return res;
}

/* private method ------ */
void* getNN(void *obj,void *node)
{
    return getNAt(obj,1,node);
}
void* getNB(void *obj,void *node)
{
    void *p = NULL;
    if((obj!=NULL)&&(node !=NULL))
    {
        p = ((struct pVoidList*)obj)->getBack(((struct pVoidList*)obj)->getNext(node));
    }
    else
    {
        /* do nothing */
    }
    return p;
}
void* getBB(void *obj,void *node)
{
    return getBAt(obj,1,node);
}
void* getBN(void *obj,void *node)
{
    void *p = NULL;
    if((obj!=NULL)&&(node !=NULL))
    {
        p = ((struct pVoidList*)obj)->getNext(((struct pVoidList*)obj)->getBack(node));
    }
    else
    {
        /* do nothing */
    }
    return p;
}
void* getNAt(void *obj,int index,void *node)
{
    void *p = NULL;
    if((obj!=NULL)&&(index>=0)&&(node!=NULL))
    {
        p = node;
        while((index >=0)&&(p!=NULL))
        {
            p = ((struct pVoidList*)obj)->getNext(p);
            index--;
        }
    }
    else
    {
        /* do nothing */
    }
    return p;
}
void* getBAt(void *obj,int index,void *node)
{
    void *p = NULL;
    if((obj!=NULL)&&(index>=0)&&(node!=NULL))
    {
        p = node;
        while((index >=0)&&(p!=NULL))
        {
            p = ((struct pVoidList*)obj)->getBack(p);
            index--;
        }
    }
    else
    {
        /* do nothing */
    }
    return p;
}

int setNN(void *obj,void *node1,void *node2)
{
    int ret =0;
    if((obj!=NULL)&&(node1!=NULL))
    {
        ret = ((struct pVoidList*)obj)->setNext(((struct pVoidList*)obj)->getNext(node1),node2);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int setNB(void *obj,void *node1,void *node2)
{
    int ret =0;
    if((obj!=NULL)&&(node1!=NULL))
    {
        ret = ((struct pVoidList*)obj)->setBack(((struct pVoidList*)obj)->getNext(node1),node2);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int setBB(void *obj,void *node1,void *node2)
{
    int ret =0;
    if((obj!=NULL)&&(node1!=NULL))
    {
        ret = ((struct pVoidList*)obj)->setBack(((struct pVoidList*)obj)->getBack(node1),node2);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int setBN(void *obj,void *node1,void *node2)
{
    int ret =0;
    if((obj!=NULL)&&(node1!=NULL))
    {
        ret = ((struct pVoidList*)obj)->setNext(((struct pVoidList*)obj)->getBack(node1),node2);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int setNAt(void *obj,void *node1,void *node2,int index)
{
    int ret = 0;
    if((obj!=NULL)&&(node1!=NULL)&&(index>=0))
    {
        if(index==0)
        {
            ret = ((struct pVoidList*)obj)->setNext(node1,node2);
        }
        else 
        {
            ret = ((struct pVoidList*)obj)->setNext(getNAt(obj,index-1,node1),node2);
        }
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int setBAt(void *obj,void *node1,void *node2,int index)
{
    int ret = 0;
    if((obj!=NULL)&&(node1!=NULL)&&(index>=0))
    {
        if(index==0)
        {
            ret = ((struct pVoidList*)obj)->setBack(node1,node2);
        }
        else 
        {
            ret = ((struct pVoidList*)obj)->setBack(getBAt(obj,index-1,node1),node2);
        }
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

/* for struct pVoidElement*/
void* getNxpVoidEle(void *node)
{
    void *p = NULL;
    if(node!=NULL)
    {
        p = ((pVoidElement*)node)->next;
    }
    else
    {
        /* do nothing */
    }
    return p;
}

void* getBkpVoidEle(void *node)
{
    void *p = NULL;
    if(node!=NULL)
    {
        p = ((pVoidElement*)node)->back;
    }
    else
    {
        /* do nothing */
    }
    return p;
}

void* getDatpVoidEle(void *node)
{
    void *p = NULL;
    if(node!=NULL)
    {
        p = ((pVoidElement*)node)->data;
    }
    else
    {
        /* do nothing */
    }
    return p;
}

int setNxpVoidEle(void *node1,void *node2)
{
    int ret = 0;
    if(node1!=NULL)
    {
        ((pVoidElement*)node1)->next = node2;
        ret = 1;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

int setBkpVoidEle(void *node1,void *node2)
{
    int ret = 0;
    if(node1!=NULL)
    {
        ((pVoidElement*)node1)->back = node2;
        ret = 1;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int setDatpVoidEle(void *node1,void *node2)
{
    int ret = 0;
    if(node1 != NULL)
    {
        ((pVoidElement*)node1)->data = node2;
        ret = 1;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

void* getAllocatePVoidEle(void *obj)
{
    return malloc(sizeof(pVoidElement));
}

void freeAllocPVoidEle(void *obj,void *node)
{
    /* obj is not used in this case */
    if(node != NULL)
    {
        free(node);
    }
    else
    {
        /* do nothing */
    }
}
/* End of for struct pVoidElement*/
/* end of private method ----- */