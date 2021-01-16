#include <stdio.h>
#include "listInt.h"
void constructorIntList(intList *list)
{
    list->first = NULL;
    list->last  = NULL;
    list->cur   = NULL;    
    list->currentIndex = 0;
    list->numOfNode   = 0;
}

void setCurrentPointerIntList(intList* list,int index)
{
    getDataIntList(list,index);
}
void resetCurrentPointerIntList(intList* list)
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
int addDataPtIntList(intList *list,int *data)
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
        list->first = (intElement*)malloc(sizeof(intElement));
        if(list->first == NULL)
        {
            return 0; /* cannot add Data */
        }
        else
        {
            list->last = list->first;
            list->first->data = *data;
            list->numOfNode++;
            list->last->next = NULL;
            list->last->back = NULL;
        }
    }
    else
    {
        list->last->next = (intElement*)malloc(sizeof(intElement));
        if(list->last->next == NULL)
        {
            return 0; /* cannot add Data */
        }
        else
        {
            
            list->last->next->back = list->last;
            list->last	       = list->last->next;
            list->last->data       = *data;
            list->last->next = NULL;
            list->numOfNode++;
            
        }
    }
    return 1; /* complete */
}
int getCurrentIndexOfIntList(intList* list)
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
int addDataIntList(intList *list,int data)
{
    return addDataPtIntList(list,&data);
}
void makeEmptyIntList(intList *list)
{
    intElement *p;
    while(list->first)
    {
        p 	    = list->first;
        list->first = list->first->next;
        /* delete_something before free */
        /* free */
        free(p);
    }
    constructorIntList(list);
}
void destructorIntList(intList *list)
{
    makeEmptyIntList(list);
}
int searchIntListPt(intList* list,int *data)
{
    intElement *p=NULL;
    int index = 0;
    if(list->cur != NULL)
    {
        index =list->currentIndex;
        for(p = list->cur;p!=NULL;p=p->next)
        {
            if(p->data == *data)
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
    for(p = list->first;p != list->cur;p = p->next)
    {
        if(p->data == *data)
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
int searchIntList(intList* list,int data)
{
    return searchIntListPt(list,&data);
}
intElement* getAddressElementIntList(intList* list,int index)
{
    intElement *p = NULL;
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
                p = p->next;
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
                p = p->next;
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
int getDataIntList(intList* list,int index)
{
    intElement *p = NULL;
    int dummyValue =0;
    if(index < 0|| list ==NULL || index >= list->numOfNode)
    {
        int a =0;
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
                p = p->next;
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
                p = p->next;
            }
            list->cur = p;
        }
        else
        {
            /* do nothing */
        }
        return p->data;
    }
}
int getLastDataIntList(intList* list)
{
    return getDataIntList(list,list->numOfNode -1);
}
int countIntList(intList *list)
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
int deleteIndexElementIntList(intList *list,int index)
{
    intElement *p=NULL;
    int index1 = 0;
    if(index < 0|| list ==NULL)
    {
        printf("list is NULL or bad index %d\n",index);
        return 0;
    }
    else
    {
        if(index >= list->numOfNode)
        {
            printf("wrong index\n");
            return 0;
        }
        else
        {
            /* do nothing  */
        }
        for(p=list->first;p !=NULL;p = p->next)
        {
            if(index == index1)
            {
                if(index != 0 && index != list->numOfNode -1)
                {
                    p->next->back = p->back;
                    p->back->next = p->next;
                }
                else if(index ==0)
                {
                    list->first       = p->next;
                    if(list->first != NULL)
                    {
                            list->first->back = NULL;
                    }
                    else
                    {
                        /* do nothing */
                    }

                }
                else if(index == list->numOfNode -1)
                {
                    list->last	  = p->back;
                    if(list->last != NULL)
                    {
                        list->last->next  = NULL;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                else
                {
                    return 0;
                }
                list->cur =NULL;
                list->currentIndex = 0;
                list->numOfNode--;
                free(p);
                return 1;
            }
            else
            {
                    index1++;
            }
        }
    }
    if(list->numOfNode == 0)
    {
        list->last = NULL;
        list->cur = NULL;
        list->first= NULL;
        list->currentIndex= 0;
    }
    else
    {
        /* do nothing */
    }
    return 0;
}
int deleteElementIntListPt(intList *list,int *data)
{
    int index = searchIntListPt(list,data);
    return deleteIndexElementIntList(list,index);
}
int deleteElementIntList(intList *list,int data)
{
    return deleteElementIntListPt(list,&data);
}
int popIntList(intList* list)
{
    int a;
    if(list ==NULL)
    {
        printf("list is NULL\n");
    }
    else
    {
        a = list->last->data;
        deleteIndexElementIntList(list,list->numOfNode-1);
    }
    return a;
}
int pushIntListPt(intList* list,int *data)
{
    return addDataPtIntList(list,data);
}
int pushIntList(intList* list,int data)
{
    return addDataPtIntList(list,&data);
}
int enQueueIntList(intList* list,int data)
{
    return enQueueIntListPt(list,&data);
}
int enQueueIntListPt(intList* list,int *data)
{
    if(list == NULL || data ==NULL)
    {
        return 0;
    }
    else
    {
        intElement *p = (intElement*)malloc(sizeof(intElement));
        if(p == NULL)
        {
            return 0;
        }
        else
        {
            // do nothing
        }
        p->back 	  = NULL;
        p->next		  = list->first;
        list->first->back = p;
        list->first = p;
        list->numOfNode++;
        p->data 	  = *data;
    }
    return 1;
}
int deQueueIntList(intList* list)
{
    return popIntList(list);
}
int swapElementIntListPt(intList *list,int index1,int index2)
{
    if(list == NULL)
    {
        return 0;
    }
    else
    {
        //do nothing
    }
    if(list->numOfNode <= index1 || list->numOfNode <=index2 ||
       index1 == index2 || index1 <0 || index2 < 0)
    {
        return 0;
    }
    else
    {
        //do nothing
    }
    intElement *p1=NULL,*p2=NULL,*p3,*p4;
    int index =0;
    if(index1 > index2)
    {
        index =index1;
        index1=index2;
        index2=index;
    }
    else
    {
        //do nothing
    }
    index =0;
    for(p2 = list->first;p2 != NULL;p2 = p2->next)
    {
        if(index ==index1)
        {
            p1    = p2;	
            p3    = p1->next;
            p4    = p1->back;
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
            if(p1->next != NULL)
            {
                p1->next->back = p2;
            }
            else
            {
                //do nothing
            }
            if(p1->back != NULL)
            {
                p1->back->next = p2;
            }
            else
            {
                //do nothing
            }
            if(p2->next != NULL)
            {
                p2->next->back = p1;
            }
            else
            {
                //do nothing
            }
            if(p2->back != NULL)
            {
                p2->back->next = p1;
            }
            else
            {
                //do nothing
            }

            p1->next = p2->next;
            p1->back = p2->back;

            p2->next = p3;
            p2->back = p4;
            break;
        }
        else
        {
            //do nothing
        }
        index++;
    }
    return 1;

}
int swapElementIntList(intList *list,int index1,int index2)
{
    if(list == NULL)
    {
        return 0;
    }
    else
    {
        //do nothing
    }
    if(list->numOfNode <= index1 || list->numOfNode <=index2 ||
       index1 == index2 || index1 <0 || index2 < 0)
    {
        return 0;
    }
    else
    {
        //do nothing
    }
    int data1;
    intElement *p1=NULL,*p2=NULL;
    int index =0;
    if(index1 > index2)
    {
        index =index1;
        index1=index2;
        index2=index;
    }
    else
    {
        //do nothing
    }
    index =0;
    for(p2 = list->first;p2 != NULL;p2 = p2->next)
    {
        if(index ==index1)
        {
            p1    = p2;
            data1 = p2->data;
            
        }
        else if(index ==index2)
        {
            
            
            p1->data = p2->data;
            p2->data = data1;

            break;
        }
        else
        {
            //do nothing
        }
        index++;
    }
    return 1;
}
void printIntList(intList *list,int opt)
{
    if(list == NULL||list->numOfNode == 0)
    {
        return;
    }
    else
    {
        //do nothing
    }
    intElement *p = list->first;
    if(opt < 0)
    {
        opt = -opt;
        for(p=list->first;p!=NULL;p =p->next)
        {
            if(opt ==4)
            {
              printf("%p %p ",p->back,p);
            }
            else 
            {
                //do nothing
            }
            //print Elemet, printf is an example function
            printf("%d",p->data);
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
                printf(" %p\n",p->next);
            
            }
        }
    }
    else
    {
        for(p=list->last;p!=NULL;p =p->back)
        {
            if(opt ==4)
            {
              printf("%p %p ",p->back,p);
            }
            else 
            {
                //do nothing
            }
            //print Elemet, printf is an example function
            printf("%d",p->data);
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
                printf(" %p\n",p->next);
            
            }
        }
    }
    printf("\n");
}
vector_int convertTovector_int(intList *list)
{
    vector_int dummy = new_vector_int(0);
    if(list == NULL)
    {
        return dummy;
    }
    else
    {
        int index =0;
        intElement *p = list->first;
        int numList = list->numOfNode;
        dummy 	    = new_vector_int(numList);
        for(index =0;index<numList;index++)
        {
            dummy.data[index] = p->data;
            p = p->next;
        }
    }

    return dummy;
}
int copyIntList(intList *lsh,intList *rsh)
{
     int res = 0;
     int index=0;
     int num = 0;
     int dat1;
     if((lsh!=rsh) && (lsh!=NULL) &&(rsh !=NULL))
     {
         makeEmptyIntList(lsh);
         num = rsh->numOfNode;
         for(index = 0;index < num;index++)
         {
             dat1 = getDataIntList(rsh,index);
             res = addDataPtIntList(lsh,&dat1);
             if(res == 0)
             {
                 makeEmptyIntList(lsh);
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
int insetWithIndexIntList(intList *list,int data,int index)
{
    int res = 0;
    int num = 0;
    intElement *p = NULL;
    intElement *np = NULL;
    int index2 = 0;
    if(list !=NULL && index >=0)
    {
        num = list->numOfNode;
        if(index == num-1)
        {
           res = addDataPtIntList(list,&data);
        }  
        else if(index == 0)
        {
           res = enQueueIntListPt(list,&data);
           res &= swapElementIntListPt(list,0,1);
        }
        else if(index < num)
        {
            p = list->first;
            for(index2=0;index2<num;index2++)
            {
                if(index==index2)
                {
                    np = (intElement*)malloc(sizeof(intElement));
                    if(np!=NULL)
                    {
                        np->back = p;
                        np->next = p->next;
                        p->next->back = np;
                        p->next = np;
                        np->data= data;
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
                    p=p->next;
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
