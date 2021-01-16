#include "eleXMLNodeList.h"
#include "stdlib.h"
/* methods of nodeEle class */
void constructorEleNode(nodeEle* anode)
{
    if(anode == NULL)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    anode->next =  NULL;
    anode->back =  NULL;
    anode->data =  NULL;
}
int  addNodeEleXMLData(nodeEle* anode,elementXML* dat)
{
    if(anode == NULL)
    {   
        return 0; /* error */
    }
    else if(anode->next != NULL)
    {
        return 0; /* error */
    }
    else
    {
        anode->next = (nodeEle*)malloc(sizeof(nodeEle));
    }
    if(anode->next == NULL)
    {
        return 0; /* error */
    }
    else
    {
        anode->next->data = dat;
        anode->next->back = anode;
        anode->next->next = NULL;
    }
    
    return 1;
}
elementXML* getXMLEleData(nodeEle* anode)
{
    if(anode == NULL)
    {
        return NULL;
    }
    else
    {
       /* do nothing */
    }
     return anode->data;
}
int setXMLEleData(nodeEle* anode,elementXML* dat)
{
    if(anode == NULL)
    {
        return 0;
    }
    else
    {
       anode->data = dat;
    }
    return 1;
}
/* methods of listElement */
int constructorListXMLEle(listElement* alist)
{
    int res = 0;
    if(alist != NULL)
    {
        res =1;
        alist->first       = NULL;
        alist->last        = NULL;
        alist->cur         = NULL;
        alist->curIndex    = -1;
        alist->numOfNode   = 0;
    }
    else
    {
        /* do nothing */
    }
    return res;
}
void makeNodeXMLEleEmpty(listElement* alist)
{
    nodeEle *p = NULL;
    if(alist == NULL)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    while(alist->first != NULL)
    {
        p=alist->first;
        alist->first = p->next;
        free(p);
    }
    constructorListXMLEle(alist);
}
void destructListXMLEle(listElement* alist)
{
    makeNodeXMLEleEmpty(alist);
}
int addNodeEleXML(listElement* alist,elementXML* dat)
{
    if(alist == NULL)
    {
        return 0; /* failed to add */
    }
    else
    {
        /* do nothing */
    }
    if(alist->numOfNode == 0)
    {
                
                alist->first = (nodeEle*)malloc(sizeof(nodeEle));

                if(alist->first != NULL)
                {
                    alist->numOfNode++;
                    alist->last  = alist->first;
                    alist->cur   = alist->first;
                    constructorEleNode(alist->first);
                    setXMLEleData(alist->first,dat);
                    
                }
                else
                {
                    return 0; /* failed to add */
                }
    }
    else
    {
        if(addNodeEleXMLData(alist->last,dat) == 1)
        {
            alist->numOfNode++;
            alist->last = alist->last->next;
        }
        else
        {
            return 0; /* failed to add */
        }
    }
    return 1;
}
int deleteNodeXMLEleByIndex(listElement* alist,int index)
{
    nodeEle* p = NULL;
    int index2 = 0;
    if(alist == NULL)
    {
        return 0;
    }
    else if(alist->numOfNode <= index)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    p = alist->first;
    if(alist->numOfNode ==1)
    {
        alist->numOfNode = 0;
        free(p);
        constructorListXMLEle(alist);
        return 1;
    }
    else if(alist->curIndex == index)
    {
        p = alist->cur;
        index2 = index;
    }
    else
    {
        while(index2 < alist->numOfNode)
        {
            if(index2 == index)
            {
                break;
            }
            else
            {
                p = p->next;
                index2++;
            }
        }
    }

    if(index2 == alist->numOfNode)
    {
        return 0;
    }
    else
    {
        if(p == alist->first)
        {
            alist->first = p->next;
            p->next->back = p->back;
            if(alist->curIndex == index)
            {
                alist->cur    = alist->first;
            }
            else
            {
                /* do nothing */
            }
        }
        else if(p == alist->last)
        {
            alist->last   = p->back;
            p->back->next = p->next;
            if(alist->curIndex == index)
            {
                alist->cur    = alist->last;
                alist->curIndex--;
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {

            p->next->back = p->back;  
            p->back->next = p->next;
            if(alist->curIndex == index)
            {
                alist->cur    = p->next;
            }
            else
            {
                /* do nothing */
            }
        }
        free(p);
        alist->numOfNode--;
    }
    return 1;
}
int generateXMLEleList(listElement* alist,elementXML *dat,const char *str)
{
    int res = 0;
    elementXML *p = NULL;
    if(dat == NULL || alist == NULL ||str == NULL)
    {
        /* do nothing */
    }
    else
    {
        res = 1;
    }
    if(res ==1)
    {
        for(p=dat->firstChild;p!=NULL;p = p->next)
        {
            if(compNameElemetVsCstr(&(p->name),str) == 1)
            {
                addNodeEleXML(alist,p);
            }
            else
            {
                /* do nothing */
            }
        }
    }
    else
    {
        /* do nnothing */
    }
    return res;
}
int getNumOfXMLNode(listElement* alist)
{
    if(alist == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    return alist->numOfNode;
}

int gtNXMLNd2(void *alist)
{
    return getNumOfXMLNode((listElement*)alist);
}
char isXMLNodeEmpty(listElement* alist)
{
    if(alist == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    return (char)(alist->numOfNode == 0);
}

void* getXMLElement2(void *alist,int index)
{
    return (void*)getXMLElement((listElement*)alist,index);
}
elementXML* getXMLElement(listElement* alist,int index)
{
    nodeEle *p = NULL;
    int index2 = 0;
    if(alist == NULL)
    {
        return NULL;
    }
    else if(index >= alist->numOfNode)
    {
        return NULL;
    }
    else
    {
        /* do nothing */
    }
    if(index == alist->curIndex)
    {
        return getXMLEleData(alist->cur);
    }
    else if(index == 0)
    {
        alist->cur = alist->first;
        alist->curIndex = 0;
        return getXMLEleData(alist->cur);
    }
    else if(index == alist->numOfNode-1)
    {
        alist->cur = alist->last;
        alist->curIndex = index;
        return getXMLEleData(alist->cur);
    }
    else if(index > alist->curIndex)
    {
        index2 =  alist->curIndex;
        for(p = alist->cur;index2 < index;index2++)
        {
            p = p->next;
        }
        alist->curIndex = index;
        alist->cur      = p;
        return getXMLEleData(alist->cur);
    }
    else if(index < alist->curIndex)
    {
        index2 =  alist->curIndex;
        for(p = alist->cur;index2 > index;index2--)
        {
            p = p->back;
        }
        alist->curIndex = index;
        alist->cur      = p;
        return getXMLEleData(alist->cur);  
    }
    else
    {
    /*do nothing */
    printf("do nothing-----------------------\n");
    }
    return NULL;
}
nodeEle getXMLNode(listElement* alist,int index)
{
    elementXML *p = getXMLElement(alist,index);
    nodeEle anode;
    constructorEleNode(&anode);
    if(alist != NULL)
    {
        addNodeEleXMLData(&anode,p);
    }
    else
    {
        /* do nothing */
    }
    return anode;  
}
void printXMLList(listElement* alist)
{
    nodeEle *p = NULL;
    int numNode= 0;
    if(alist == NULL)
    {
        return;
    }
    else
    {
        numNode = getNumOfXMLNode(alist);
        p       = alist->first;
    }
    printf("the num of XML Nodes:%d \n",numNode);
    while(p!= NULL)
    {
        printEleXML(getXMLEleData(p));
        p = p->next;
    }
}

void printXMLList2(void* alist)
{
    printXMLList((listElement*)alist);
}

int getSourceToXMLList(listElement* alist,elementXML *dat,const char *str)
{
    int res = constructorListXMLEle(alist);
    res &=generateXMLEleList(alist,dat,str);
    if(res ==0)
    {     
        destructListXMLEle(alist);
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int getSrc2XMLList2(void **list1,void *xmlEle,const char *tagName)
{
    int ret = 0;
    listElement *obj = NULL;
    elementXML *dat = (elementXML*)xmlEle;
    if (list1 != NULL)
    {
        obj = (struct listElement*)malloc(sizeof(struct listElement));
        if (getSourceToXMLList(obj,dat,tagName) == 1)
        {
            *list1 = (void*)obj;
            ret = 1;
        }
        else
        {
            printf("Error(1) in getSrc2XMLList2, obj:%p, ln :%d, file:%s\n",obj,__LINE__,__FILE__);
        }
    }
    else
    {
        printf("Error(0) in getSrc2XMLList2, list:%p, ln :%d, file:%s\n",list1,__LINE__,__FILE__);
    }
    return ret;
}

int getAttrbValXMLEle2Var(void *list1,int index,const char* attrb,const char* defaultVal,void *var,unsigned int typeVar)
{
    int ret = 0;
    listElement *alist = (listElement*)list1;
    if ((alist != NULL) && (index > -1) && (attrb != NULL) && (defaultVal != NULL) && (var != NULL))
    {
        ret = getAttrbValXMLEle2Var2((void*)getXMLElement(alist,index),attrb,defaultVal,var,typeVar);
    }
    else
    {
        printf("Error(0) in getAttrbValXMLEle2Var, input parameters are invalid , ln:%d, file:%s\n",__LINE__,__FILE__);
    }
    return ret;
}
void destructXMLList2(void **list1)
{
    if (list1 != NULL)
    {
        if (*list1 != NULL)
        {
            destructListXMLEle((struct listElement*)(*list1));
            free(*list1);
            *list1 = NULL;
        }
        else
        {
            printf("Error(1) in destructXMLList2, there is the free command to null pointer, ln:%d, file:%s\n",__LINE__,__FILE__);
        }
    }
    else
    {
        printf("Error(0) in destructXMLList2, list:%p, ln :%d, file:%s\n",list1,__LINE__,__FILE__);
    }
}