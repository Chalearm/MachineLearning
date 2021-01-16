#include <stdio.h>
#include "listChar.h"
void constructorCharList(charList *list)
{
    list->first = NULL;
    list->last  = NULL;
    list->cur   = NULL;
    list->currentIndex = 0;
    list->numOfNode   = 0;
}
int addDataPt(charList *list,element *data)
{
    if ((list == NULL) || (data == NULL))
    {
        return 0; /*cannot add Data*/
    }
    else
    {
        /* do nothing */
    }
    if(list->numOfNode == 0)
    {
        list->first = (charElement*)malloc(sizeof(charElement));
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
        list->last->next = (charElement*)malloc(sizeof(charElement));
        if(list->last->next == NULL)
        {
            return 0; /* cannot add Data */
        }
        else
        {
            
            list->last->next->back = list->last;
            list->last        = list->last->next;
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
        p 	    = list->first;
        list->first = list->first->next;
        /* delete_something before free */
        /* free*/
        free(p);
    }
    list->cur=NULL;
    list->currentIndex= 0;
    constructorCharList(list);
}
void resetCurrentPointerCharList(charList* list)
{
    if(list!=NULL)
    {
        list->cur =NULL;
        list->currentIndex =0;
    }
    else
    {
        /* do nothing */
    }
}
void destructorCharList(charList *list)
{
    makeEmptyCharList(list);
}
int searchCharListPt(charList* list,element *data)
{
    charElement *p;
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
int searchCharList(charList* list,element data)
{
    return searchCharListPt(list,&data);
}
int getCurrentIndexOfCharList(charList* list)
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
charElement* getAddressElementCharList(charList* list,int index)
{
    charElement *p = NULL;
    int dummyValue =0;
    if((index < 0)||(list ==NULL)||(index >= list->numOfNode))
    {
        list->cur = NULL;
        list->currentIndex=0;
        printf("wrong index or list is NULL\n");
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
element getDataCharList(charList* list,int index)
{
    charElement *p = NULL;
    int dummyValue =0;
    if((index < 0)||(list ==NULL)||(index >= list->numOfNode))
    {
        element a =0;
        list->cur = NULL;
        list->currentIndex=0;
        printf("wrong index or list is NULL\n");
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
void setCurrentPointerCharList(charList* list,int index)
{
    getDataCharList(list,index);
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
        //do nothing
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
            //do nothing 
        }
        for(p=list->first;p !=NULL;p = p->next)
        {
            if(index == index1)
            {
                if((index != 0) && (index != list->numOfNode -1))
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
                    //do nothing
                }
                list->numOfNode--;
                /*delete_something before free
                  free*/
                list->cur = NULL;
                list->currentIndex = 0;
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
        list->currentIndex = 0;
        list->first= NULL;
    }
    else
    {
        /* do nothing */
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
void printCharList(charList *list,int opt)
{
    if(list == NULL||list->numOfNode == 0)
    {
        return;
    }
    else
    {
        //do nothing
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
            /* print Elemet, printf is an example function */
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
    int index = 0;
    int numList = 0;
    vector_char dummy = new_vector_char(0);
    if(list == NULL)
    {
        return dummy;
    }
    else
    {
        charElement *p = list->first;
        numList = list->numOfNode;
        dummy   = new_vector_char(numList);
        for (index = 0;index<numList;index++)
        {
            dummy.data[index] = p->data;
            p = p->next;
        }
    }

    return dummy;
}
int copyCharList(charList *lsh,charList *rsh)
{
     int res = 0;
     int index=0;
     int num = 0;
     element dat1;
     if((lsh!=rsh) && (lsh!=NULL) &&(rsh !=NULL))
     {
         makeEmptyCharList(lsh);
         num = rsh->numOfNode;
         for(index = 0;index < num;index++)
         {
             dat1 = getDataCharList(rsh,index);
             res = addDataPt(lsh,&dat1);
             if(res == 0)
             {
                 makeEmptyCharList(lsh);
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
int insetWithIndexCharList(charList *list,element data,int index)
{
    int res = 0;
    int num = 0;
    charElement *p = NULL;
    charElement *np = NULL;
    int index2 = 0;
    if(list !=NULL && index >=0)
    {
        num = list->numOfNode;
        if(index == num-1)
        {
           res = addDataPt(list,&data);
        }  
        else if(index == 0)
        {
           res = enQueueCharListPt(list,&data);
           res &= swapElementCharListPt(list,0,1);
        }
        else if(index < num)
        {
            p = list->first;
            for(index2=0;index2<num;index2++)
            {
                if(index==index2)
                {
                    np = (charElement*)malloc(sizeof(charElement));
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
