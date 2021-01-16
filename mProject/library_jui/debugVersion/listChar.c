#include <stdio.h>
#include "listChar.h"
#include "debug.h"
void constructorCharList(charList *list)
{
    list->first = NULL;
    list->last  = NULL;
    list->cur   = NULL;
    list->numOfNode   = 0;
}
int addDataPt(charList *list,element *data)
{
    if(list == NULL || data == NULL)
    {
        return 0;  /* cannot add Data  */ 
    }
    else
    {
        /* do nothing */
    }
    if(list->numOfNode == 0)
    {
        list->first = (charElement*)malloc(sizeof(charElement));
    printOpt(__LINE__-1,"addDataPt","listChar.c",(void*)list->first,0);
        if(list->first == NULL)
        {
            return 0; /* cannot add Data  */ 
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
        list->last->next = (charElement*)malloc(sizeof(charElement));
        printOpt(__LINE__-1,"addDataPt","listChar.c",(void*)list->last->next ,0);
        if(list->last->next == NULL)
        {    
            return 0; /* cannot add Data; */   
        }
        else
        {
            
            list->last->next->back = list->last;
            list->last           = list->last->next;
            list->last->data       = *data;
            list->last->next = NULL;
            list->numOfNode++;
            
        }
    }
    return 1; /* complete */
}
int addData(charList *list,element data)
{
    return addDataPt(list,&data);
}
void makeEmptyCharList(charList *list)
{
    charElement *p;
    while(list->first)
    {
        p         = list->first;
        list->first = list->first->next;    
        /*delete_something before free
        // free    */
        printOpt(__LINE__+1,"makeEmptyCharList","listChar.c",(void*)p ,1);    
        free(p);
    }
    constructorCharList(list);
}
void destructorCharList(charList *list)
{
    makeEmptyCharList(list);
}    
int searchCharListPt(charList* list,element *data)
{
    charElement *p;
    int index = 0;
    for(p = list->first;p != NULL;p = p->next)
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
int searchCharList(charList* list,element data)
{
    return searchCharListPt(list,&data);
}
element getDataCharList(charList* list,int index)
{
    if(index < 0|| list ==NULL || index >= list->numOfNode)
    {
        element a =0;
        printf("wrong index or list is NULL\n");
        return a;
    }
    else
    {
        charElement *p = list->first;
        while(index--)
        {
            p = p->next;
        }
        return p->data;
    }
}
element getLastDataCharList(charList* list)
{
    return getDataCharList(list,list->numOfNode -1);
}
int countCharList(charList *list)
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
int deleteIndexElementCharList(charList *list,int index)
{
    charElement *p=NULL;
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
            /* do nothing */ 
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
                    list->first->back = NULL;
                }
                else if(index == list->numOfNode -1)
                {
                    list->last      = p->back;
                    list->last->next  = NULL;
                }
                else
                {    
                    return 0;
                    /* do nothing */
                }
                list->numOfNode--;
                /*delete_something before free
                // free  */
                printOpt(__LINE__+1,"deleteIndexElementCharList","listChar.c",(void*)p ,1);
                free(p);
                return 1;
        
            }
            else
            {
                index1++;
            }
        }
    }
    return 0;
}
    
int deleteElementCharListPt(charList *list,element *data)
{
    int index = searchCharListPt(list,data);
        return deleteIndexElementCharList(list,index);
}
int deleteElementCharList(charList *list,element data)
{
    return deleteElementCharListPt(list,&data);
}
element popCharList(charList* list)
{
    element a;
    if(list ==NULL)
    {
        printf("list is NULL\n");
    }
    else
    {
        a = list->last->data;
        deleteIndexElementCharList(list,list->numOfNode-1);
    }
    return a;
}
int pushCharListPt(charList* list,element *data)
{
    return addDataPt(list,data);
}
int pushCharList(charList* list,element data)
{
    return addDataPt(list,&data);
}
int enQueueCharList(charList* list,element data)
{
    return enQueueCharListPt(list,&data);
}
int enQueueCharListPt(charList* list,element *data)
{
    if(list == NULL || data ==NULL)
    {
        return 0;
    }
    else
    {
        charElement *p = (charElement*)malloc(sizeof(charElement));
         printOpt(__LINE__-1,"enQueueCharListPt","listChar.c",(void*)p ,0);        
        if(p == NULL)
        {
            return 0;
        }
        else
        {
            // do nothing
        }
        p->back       = NULL;
        p->next          = list->first;
        list->first->back = p;
        list->first = p;
        list->numOfNode++;
        p->data       = *data;
    }
    return 1;
}
element deQueueCharList(charList* list)
{
    return popCharList(list);
}
int swapElementCharListPt(charList *list,int index1,int index2)
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
    charElement *p1=NULL,*p2=NULL,*p3,*p4;
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
                /* do nothing */
            }
            if(p1->back != NULL)
            {
                p1->back->next = p2;
            }
            else
            {
                /* do nothing */
            }
            if(p2->next != NULL)
            {
                p2->next->back = p1;
            }
            else
            {
                /* do nothing */
            }
            if(p2->back != NULL)
            {
                p2->back->next = p1;
            }
            else
            {
                /* do nothing */
            }

            p1->next = p2->next;
            p1->back = p2->back;

            p2->next = p3;
            p2->back = p4;
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
int swapElementCharList(charList *list,int index1,int index2)
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
    element data1;
    charElement *p1=NULL,*p2=NULL;
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
    for(p2 = list->first;p2 != NULL;p2 = p2->next)
    {
        if(index ==index1)
        {
            p1    = p2;
            data1 = p1->data;    
        }
        else if(index ==index2)
        {
            
            
            p1->data = p2->data;
            p2->data = data1;

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
void printCharList(charList *list,int opt)
{
    if(list == NULL||list->numOfNode == 0)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    charElement *p = list->first;
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
                /* do nothing */
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
                /* do nothing */
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
vector_char convertTovector_char(charList *list)
{
    vector_char dummy = new_vector_char(0);
    int numList = 0;
    if (list != NULL)
    {
        return dummy;
    }
    else
    {
        int index =0;
        charElement *p = list->first;
        numList = list->numOfNode;
        dummy = new_vector_char(numList);
        for (index = 0;index<numList;index++)
        {
            dummy.data[index] = p->data;
            p = p->next;
        }
    }

    return dummy;
}
