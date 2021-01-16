/********************************************************************/
/*
      FILE        :   intFixedStack.c
      Name        :   Chalearm Saelim
      Date        :   05 December 2016
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Integer fixed stack

      Description :    -
      Dependency     :   We use the included library as below 
                                                #include -
      How to compile: gcc intFixedStack.c -o  a
      How to run        : -
      
      revision-history
      version   date          author     Description
      1.        05-12-2016    csaelim    First draft
*/


/*******************************************************************/
#include <stdio.h>
#include "intFixedStack.h"

void constructIfStack(struct ifStack *obj,int size)
{
    if(obj !=NULL)
    {
        obj->m_top=-1;
        obj->m_num=0;
        if(size>0)
        {
            obj->m_num=size;
        }
        else
        {
            obj->m_num = STCK_SIZE;
        }
    }
    else
    {
        /* do nothing */
    }
}
void destructorIfStack(struct ifStack *obj)
{
    if(obj !=NULL)
    {
        obj->m_top=-1;
        obj->m_num=0;
    }
    else
    {
        /* do nothing */
    }
}
void prntIfStck(struct ifStack *obj)
{
    int index=0;
    if(obj!=NULL)
    {
        for(index=0;index<=obj->m_top;index++)
        {
            printf("%d ",obj->m_data[index]);
        }
        printf("\n");
    }
    else
    {
        /* do nothing */
    }
}
int popIfStack(struct ifStack *obj,int *value)
{
    int status = STCK_NOK;
    if((obj!=NULL)&&(value!=NULL))
    {
        if(obj->m_top >-1)
        {
            *value = obj->m_data[obj->m_top--];
            status = STCK_OK;
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
    return status;
}
int pushIfStack(struct ifStack *obj,int value)
{
    int status = STCK_NOK;
    if(obj!=NULL)
    {
        if(obj->m_top <(obj->m_num-1))
        {
            obj->m_data[++(obj->m_top)] = value;
            status = STCK_OK;
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
    return status;
}