#include <stdio.h>
#include "intFixedStack.h"

void printPush(struct ifStack *obj,int value);
int main(int argc,char **argv)
{
    struct ifStack istk;
    int a=0;
    constructIfStack(&istk,9);
    printf("Hello World\n");
    printPush(&istk,3);
    printPush(&istk,6);
    printPush(&istk,2);
    printPush(&istk,-3);

    printPush(&istk,-7);
    printPush(&istk,2);
    printPush(&istk,76);
    printPush(&istk,21);
    prntIfStck(&istk);
    printf("%s ",(popIfStack(&istk,&a)==1)?"ok":"nok");printf("pop : %d\n",a);
    printf("%s ",(popIfStack(&istk,&a)==1)?"ok":"nok");printf("pop : %d\n",a);
    printf("%s ",(popIfStack(&istk,&a)==1)?"ok":"nok");printf("pop : %d\n",a);
    printf("%s ",(popIfStack(&istk,&a)==1)?"ok":"nok");printf("pop : %d\n",a);
    printf("%s ",(popIfStack(&istk,&a)==1)?"ok":"nok");printf("pop : %d\n",a);
    printf("%s ",(popIfStack(&istk,&a)==1)?"ok":"nok");printf("pop : %d\n",a);
    printf("%s ",(popIfStack(&istk,&a)==1)?"ok":"nok");printf("pop : %d\n",a);
    printf("%s ",(popIfStack(&istk,&a)==1)?"ok":"nok");printf("pop : %d\n",a);

    destructorIfStack(&istk);
    return 0;
}


void printPush(struct ifStack *obj,int value)
{    
    printf("push :%d %s \n",value,(pushIfStack(obj,value)==1)?"ok":"nok");
}