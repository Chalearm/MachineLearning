/********************************************************************/
/*
      FILE        :   intFixedStack.h
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
#ifndef _INTFIXEDSTACK_H
#define _INTFIXEDSTACK_H
#define STCK_NOK 0
#define STCK_OK  1
#define STCK_SIZE 300
struct ifStack
{
    int m_data[STCK_SIZE];
    int m_num;
    int m_top;
};
void constructIfStack(struct ifStack *obj,int size);
void destructorIfStack(struct ifStack *obj);
void prntIfStck(struct ifStack *obj);
int popIfStack(struct ifStack *obj,int *value);
int pushIfStack(struct ifStack *obj,int value);
 
 
#endif /*_INTFIXEDSTACK_H */