#include <stdio.h>
#include <string.h>
#include "simRexical.h"

int main(int argc,char **argv)
{
    struct aRex ab;
    struct rexSet abc;
    char *simpA = "NUMBER             [\'-\'][DIGI+]|[DIGI+]|[\'-\'][DIGI+][\'.\'][DIGI+]|[DIGI+][\'.\'][DIGI+] \t   \n \n";
    printf("Hello world\n");
    constructorARex(&ab);
    constructorRexS(&abc);
    readStatement2Arex(&ab,simpA);
    int state1 =0;
    char ctemp=0;
    char name[10],buff[30];
    char *simpB = "A    \'A\'2\'Z\' ";
    char *simpC = ";.\'c\'|     .._4sedkf_ls;f40";
    sscanf(simpB,"%s %s",name,buff);
    strcpy(ab.m_name,name);
    printf("simB : %s - %s - %s\n",simpB,ab.m_name,buff);
    int index=0;
    for(index=0;buff[index]!='\0';index++)
    {
        printf("buff[%d] = %c\n",index,buff[index]);
        if((state1==0)&&(buff[index] == '\''))
        {
            state1=1;
            printf("state : %d\n",state1);
        }
        else if((state1==3)&&(buff[index] == '2'))
        {
            state1=0;
            printf("state : %d\n",state1);
        }          
        else if((state1==2)&&(buff[index] == '\''))
        {
            state1=3;
            printf("state : %d\n",state1);
        }
        else if(state1==1)
        {
            state1=2;
            ctemp = buff[index];
            printf("state : %d\n",state1);
        }
    }
    char *nxtVal =NULL;
    char wordd[30];
    int idStr=0;
    int long1 =0;
    int isString = 0;
    int isChar =0;
    char ch2=0;
    printf("text :%s\n",simpC);
    isChar = getCharRex(simpC,&nxtVal,&ch2);
    printf("isChar:%d , c:%c, %s\n",isChar,ch2,nxtVal);
    isString = isStringRex(nxtVal,&idStr,&long1);
    printf("isString: %d, idS:%d, lg:%d\n",isString,idStr,long1);
    isString = isVarNameRex(nxtVal,&idStr,&long1);
    printf("isVar: %d, idS:%d, lg:%d\n",isString,idStr,long1);
    
    isString = getStringRex(nxtVal,&nxtVal,wordd);
    printf("isString: %d, Next-:%s, w:%s\n",isString,nxtVal,wordd);
    
    readLexicalFileRexS(&abc,"setting.dat");
    destructorRexS(&abc);
    destructorARex(&ab);
    return 0; 
}