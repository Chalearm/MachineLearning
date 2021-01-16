#include "simStringList.h"

int addNodeSimStrListFromCStr(simStrList *list,const char* str)
{
    if(list == NULL || str == NULL)
    {
        return 0;
    }
    else
    {
        simStrNode *p = NULL;
        simString str1;
        if(list->root == NULL)
        {
            list->root = (simStrNode*)malloc(sizeof(simStrNode));
            p          = list->root;
            list->last = p;
            p->next    = NULL;
            
        }
        else
        {
            list->last->next = (simStrNode*)malloc(sizeof(simStrNode));
            list->last       = list->last->next;
            p                = list->last;
            p->next          = NULL;
        }
        initialSimString(&(p->data));
        initialSimString(&str1);
        convertCString2SimString(&str1,str);
        copySimStr(&(p->data),&str1);
        list->numOfNode++;
        destructSimString(&str1);

    }
    return 1;
}
int initialSimStrList(simStrList *list)
{
    if(list == NULL)
    {
        return 0;
    }
    else
    {
        list->numOfNode = 0;
        list->root      = NULL;
        list->last      = NULL;
    }
    return 1;
}
void destructorSimStrList(simStrList *list)
{
    if(list == NULL)
    {
        return;
    }
    else if(list->numOfNode == 0)
    {
        return;
    }
    else
    {
        simStrNode *p = list->root;
        while(list->root != NULL)
        {
           list->root = list->root->next;
           destructSimString(&p->data);
           free(p);
           p          = list->root;
        }
        list->last    = NULL; 
        list->numOfNode= 0;
    }
}
int addNodeSimStrListFromVChar(simStrList *list,vector_char *vch)
{
    if(list == NULL || vch == NULL)
    {
        return 0;
    }
    else
    {
        simStrNode *p = NULL;
        if(list->root == NULL)
        {
            list->root = (simStrNode*)malloc(sizeof(simStrNode));
            p          = list->root;
            list->last = p;
            
        }
        else
        {
            list->last->next = (simStrNode*)malloc(sizeof(simStrNode));
            list->last       = list->last->next;
            p                = list->last;
        }
        initialSimString(&(p->data));
        convertVectorChar2SimString(&(p->data),vch);
        list->numOfNode++;

    }
    return 1;
}
int addNodeSimStrList(simStrList *list,simString *str)
{
    if(list == NULL || str == NULL)
    {
        return 0;
    }
    else
    {
        simStrNode *p = NULL;
        if(list->root == NULL)
        {
            list->root = (simStrNode*)malloc(sizeof(simStrNode));
            p          = list->root;
            list->last = p;
            p->next    = NULL;
            
        }
        else
        {
            list->last->next = (simStrNode*)malloc(sizeof(simStrNode));
            list->last       = list->last->next;
            p                = list->last;
            p->next          = NULL;
        }
        initialSimString(&(p->data));
        copySimStr(&(p->data),str);
        list->numOfNode++;

    }
    return 1;
}
simString* getnthNodeSimStrList(simStrList *list,int num)
{
    if(list == NULL)
    {
        return NULL;
    }
    else if(num >= list->numOfNode || num < 0)
    {
        return NULL;
    }
    else
    {
        int index = 0;
        simStrNode *p = NULL;
        p            = list->root;
        for(index =0 ;index < list->numOfNode;index++)
        {
            if(index == num)
            {
                return &(p->data);
            }
            else
            {
                p = p->next; 
            }
        }
    }
    return NULL;
}
void printSimStrList(simStrList *list)
{
    simStrNode *p = NULL;
    if(list == NULL)
    {
         return;
    }
    else
    {
         /* do nothing */
    }
    for(p = list->root;p != NULL;p = p->next)
    {
        printSimString(&p->data);
    }
}
int getNumNodeSimStrList(simStrList *list)
{
    if(list == NULL)
    {
        return 0;
    }
    else
    {
        return list->numOfNode;
    }
}
int copySimStrList(simStrList *listLsh,simStrList *listRsh)
{
    int res = 0;
    int index = 0;
    int num = 0;
    simString *dummyStr = NULL;
    if((listLsh != listRsh)&&(listLsh != NULL) &&(listRsh!=NULL))
    {
        res = 1;
        num = getNumNodeSimStrList(listRsh);
        destructorSimStrList(listLsh);
        for(index=0;index < num;index++)
        {
            dummyStr = getnthNodeSimStrList(listRsh,index);
            res =  addNodeSimStrList(listLsh,dummyStr);
            if(res == 0 )
            {
                destructorSimStrList(listLsh);
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
int deleteNodeSimStrListWithIndex(simStrList *list,int index)
{
    int res = 0; 
    int index2 = 0;
    int num = 0;   
    simStrNode *p = NULL;
    simStrNode *p2 = NULL;
    if(list != NULL && index >= 0)
    {
        num = getNumNodeSimStrList(list);
        if(index < num)
        { 
              p = list->root;
              if(index == 0)
              {
                  if(list->root == list->last)
                  {
                      list->last = NULL;
                  }
                  else
                  {
                      /* do nothing */
                  }
                  list->root = p->next;
                  destructSimString(&p->data);
                  free(p);
                  res = 1;
              }
              else if(index == num-1) 
              {
                  for(p=list->root;p->next->next!=NULL;p=p->next)
                  {}
                  p2 = list->last;
                  list->last = p;
                  list->last->next = NULL;
                  destructSimString(&p2->data);
                  free(p2);
                  res = 1;
              }
              else
              {
                  for(index2 =0;index2 < num;index2++)
                  {
                      if((index2+1) == index)
                      {
                          p2      = p->next;
                          p->next = p->next->next;
                          destructSimString(&p2->data);
                          free(p2);
                          index2 = num;
                          res =1;
                      }
                      else
                      {
                          p = p->next;
                      }
                  }
              }
              list->numOfNode--;
              if(getNumNodeSimStrList(list) == 0)
              {
                  list->root = NULL; 
                  list->last = NULL;
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
    return res;
}
int insertNodeSimStrList(simStrList *list,int index,simString *str)
{
    int index2 = 0;
    int num = 0;
    int res = 0;
    simStrNode *p = NULL;
    simStrNode *p2 = NULL;
    if(list != NULL && str != NULL && index >=0)
    {
        num = getNumNodeSimStrList(list);
        if(index == num-1)
        {
            res = addNodeSimStrList(list,str);
        }
        else if(index == 0)
        {
            p = list->last;
            res = addNodeSimStrList(list,str);
            if(res == 1)
            {
                list->last->next = list->root->next;
                list->root->next = list->last;
                list->last = p;
                p->next = NULL;
            }
            else
            {
                /* do nothing */
            }
        }
        else if(index < num)
        { 
            p = list->root;
            for(index2=0;index2<num;index2++)
            {
                if(index2 == index)
	        {
                    p2 = (simStrNode*)malloc(sizeof(simStrNode));
                    if(p2 != NULL)
                    {
                        res = 1;
                        p2->next = p->next;
                        p->next  = p2;
                        copySimStr(&(p2->data),str);
                        list->numOfNode++;
                    }
                    else
                    {
                        /* do nothing */
                    }
                    index2 = index;
                }
                else
                {
                    p = p->next;
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
        /* do nohting */
    }
    return res;
}
int compareSimStrList(simStrList *listLsh,simStrList *listRsh)
{
    int res =0;
    int index= 0;
    int num =0;
    simStrNode *p1 =NULL;
    simStrNode *p2 =NULL;
    if(listLsh == listRsh)
    {
        res =1;
    }
    else if((listLsh != NULL) && (listRsh != NULL))
    {
        num = listLsh->numOfNode;
        res = (listLsh->numOfNode == listRsh->numOfNode);
        p1 = listRsh->root;
        p2 = listLsh->root;
        for(index=0;(index<num)&&(res==1);index++)
        {
            if(((p1==NULL) ||(p2==NULL))&&(p1 != p2))
            {
                res =0;
                index =num;
            }
            else
            {
                res &=compareSimString(&(p1->data),&(p2->data));
                p1 = p1->next;
                p2 = p2->next;
            }
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}
