/********************************************************************/
/*
      FILE        :   simRexical.c
      Name        :   Chalearm Saelim
      Date        :   5 December 2016
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   Rexical

      Description :    -
      Dependency     :   We use the included library as below 
                                                #include -
      How to compile: gcc simRexical.c -o  a
      How to run        : -
      
      revision-history
      version   date          author     Description
      1.        05-12-2016    csaelim    First draft
*/


/*******************************************************************/
#include <stdio.h>
#include <string.h>
#include "simRexical.h"
char g_operator[] = {OR_SYM,PLUS_SYM,COMPLE_SYM,STAR_SYM,RANGE_SYM};
char g_oper4Exp[] = {OR_SYM,PLUS_SYM,COMPLE_SYM,STAR_SYM,CONCAT};
void constructorExpRex(struct expRex *obj)
{
    if(obj!=NULL)
    {
        obj->m_type = DEFUALT_TYPE;
        obj->m_operator= DEFUALT_OPER;
        obj->m_charA= DEFUALT_CHAR;
        obj->m_charB= DEFUALT_CHAR;
        obj->m_expA = NULL;
        obj->m_expB = NULL;
    }
    else
    {
        /* do nothing */
    }
}
void constructorARex(struct aRex *obj)
{
    int index=0;
    if(obj!=NULL)
    {
        obj->m_name[0] = '\0';
        for(index=0;index< EXP_SIZE;index++)
        {
            constructorExpRex(&(obj->m_expR[index]));
        }
        obj->m_numRexExp =0;
    }
    else
    {
        /* do nothing */
    }
}
void constructorRexS(struct rexSet*obj)
{
    int index=0;
    if(obj!=NULL)
    {
        for(index=0;index< MAX_REX;index++)
        {
            constructorARex(&(obj->m_rexs[index]));
        }
        obj->m_numRex = 0;
    }
    else
    {
        /* do nothing */
    }
}
void destructorExpRex(struct expRex *obj)
{
    constructorExpRex(obj);
}
void destructorARex(struct aRex *obj)
{
    constructorARex(obj);
}
void destructorRexS(struct rexSet*obj)
{
    constructorRexS(obj);
}

void readLexicalFileRexS(struct rexSet*obj,const char *filename)
{
    FILE *fp = fopen(filename,"r");
    char buff[BUFF_SIZE+1]; 
    int index=0;
    while(fgets(buff,BUFF_SIZE,fp) !=NULL)
    {
        readStatement2Arex(&(obj->m_rexs[index]),buff);
    }
}
void cleanResSInput(char *input)
{
    int index=0;
    int len =strlen(input);
    for(index =len-1;index >-1;index--)
    {
        if((input[index]== W2_SYM)||(input[index]== W1_SYM)||(input[index]== W3_SYM))
        {
            input[index] = END_STR;
        }
        else
        {
            break;
        }
    }
}
void readStatement2Exp(struct expRex *obj,const char *input)
{
    
}
void findOperator(const char *input,int *nextStr,int *oper)
{
    int index =0;
    int index2=0;
    int state1 =DEF_NOT_FOUND;
    for(index=0;input[index]!=END_STR;index++)
    {
        
        printf("%c ",input[index]);
        if(input[index] ==LEFT_PAR )
        {
            *oper = 4;
            *nextStr =-1;
            state1 = DEF_FOUND;
        }
        else if(state1!=DEF_FOUND)
        {
            
            for(index2=0;index2<5;index2++)
            {
                if(g_oper4Exp[index2] ==input[index])
                {
                    *oper = index2;
                    *nextStr =index;
                    state1 = DEF_FOUND;
                }
                else
                {
                    /* do nothing */
                }
            }
        }
        if(state1 == DEF_FOUND)
        {
            break;
        }
        else
        {
            /* do nothing */
        }
    }
}
void findPairPar(const char *input,int *strPos,int *stopPos,int *stateO)
{
    int index=0;
    int state1 =DEF_NOT_FOUND;
    *strPos =-1;
    *stopPos =-1;
    for(index=0;input[index]!=END_STR;index++)
    {
        printf("%c ",input[index]);
        if((state1==DEF_NOT_FOUND)&&(input[index]==LEFT_PAR))
        {
            *strPos = index;
            state1 = DEF_FOUND_LT_PAR;
        }
        else if((state1==DEF_FOUND_LT_PAR)&&(input[index]==LEFT_PAR))
        {
            stateO   = DEF_NOK;
            *strPos  =-1;
            *stopPos =-1;
            break;
        }
        else if((state1==DEF_FOUND_LT_PAR)&&(input[index]==RIGHT_PAR))
        {
            *stopPos = index;
            state1 = DEF_FOUND_RT_PAR;
            break;
        }
        else
        {
            /* do nothing */
        }
    }
    printf("..");
}
void readStatement2Arex(struct aRex *obj,const char *input)
{
    int oldStop =0;
    int tempOper=0;
    int strPos =0;
    int strExp =0;
    int stopPos=0;
    int index=0;
    int state1 =DEF_OK; 
    char buff[EXP_SIZE][WORD_SIZE];
    char name[NAME_SIZE];
    char buffExp[BUFF_SIZE]; 
    strcpy(buffExp,input);
    cleanResSInput(buffExp);
    sscanf(buffExp,"%s %s",name,buffExp);
    printf("%s : %s\n",name,buffExp); 
    
    /* check syntax */
    if(name[0]!=END_STR)
    {
        strcpy(obj->m_name,name);
    }
    else
    {
        state1 =DEF_NOK;
    }    
    if(buffExp[0]==END_STR)
    {
        state1 =DEF_NOK;
    }
    else
    {   
        /* do nothing */
    }
    /* list or statement*/
    
    if(state1 == DEF_OK)
    {
        /*
        oldStop=0;
        strPos =0;
        strExp =0;
        for(index=0;buffExp[index] !=END_STR;)
        {
            findPairPar(&buffExp[strPos],&strPos,&stopPos,&state1);
            
            oldStop = oldStop+stopPos+1;
            strPos= oldStop;
            
            findOperator(&buffExp[strPos],&stopPos,&tempOper);

            
            printf("found : %d %d %d oo:%d on:%d ope :%d\n",strPos,stopPos,state1,strExp,oldStop+stopPos+1,tempOper);
            oldStop = oldStop+stopPos+1;
            strPos= oldStop;
            index = oldStop;
            if(tempOper == 0)
            {
                strExp = oldStop;
            }
            else
            {
            
            }
        }*/
    }
    else
    {
        /* do nothing */
    }
}
void inputAnalyze2Arex(struct expRex *obj,const char *expression)
{
    int index=0;
    int stage=0;
    for(index=0;expression[index]!='\0';index++)
    {
        if(isStartStopCharExpRex(expression[index]) ==DEF_OK)
        {
            
        }
        else if(isLtParExpRex(expression[index]) ==DEF_OK)
        {
            
        }
        else if(isRtParExpRex(expression[index]) ==DEF_OK)
        {
            
        }
        else if(isStartWordExpRex(expression[index]) ==DEF_OK)
        {
            
        }
        else if(isOperatorExpRex(expression[index]) ==DEF_OK)
        {
            
        }
        else if(isWordRex(expression[index]) ==DEF_OK)
        {
            
        }
        else
        {
            /* */
        }
    }
}

int isStartStopCharExpRex(char ch)
{
    return (ch==CHAR_SYM);
}
int isLtParExpRex(char ch)
{
    return (ch==LEFT_PAR);
}
int isRtParExpRex(char ch)
{
    return (ch==RIGHT_PAR);
}
int isStartWordExpRex(char ch)
{
    return (isAlphaRex(ch)==1)||(ch=='_');
}
int isAlphaRex(char ch)
{
    return ((ch>='a')&&(ch<='z'))||((ch>='A')&&(ch<='Z'));
}
int isWordRex(char ch)
{
    return (isStartWordExpRex(ch))||(isNumRex(ch));
}

int isNumRex(char ch)
{
    return ((ch>='0')&&(ch<='9'));
}
int isStringRex(const char *text,int *strIndex,int *lenght)
{
    int l_state =0;
    int index=0;
    char ch =0;
    char isString =0;
    *strIndex =0;
    *lenght =0;
    for(index=0;text[index]!='\0';index++)
    {
        ch = text[index];
        isString = ((isAlphaRex(ch))||(isNumRex(ch))||(ch=='_'));
        if((l_state==0)&&(isString==1))
        {
            l_state=1;
            *lenght = *lenght +1;
            *strIndex=index;
        }
        else if((l_state==1)&&(isString!=1))
        {
            isString = 1;
            break;
        }
        else if(l_state==1)
        {
            *lenght = *lenght +1;
        }
        else
        {
            /* do nothing */
        }
    }
    return isString;
}
int isVarNameRex(const char *text,int *strIndex,int *lenght)
{
    int isString = isStringRex(text,strIndex,lenght);
    char ch =0;
    int index=0;
    if(isString==1)
    {
        for(index=*strIndex;text[index]!='\0';index++)
        {
            ch = text[index];
            if(isNumRex(ch)==0)
            {
                isString=1;
                break;
            }
            else
            {
                *strIndex = *strIndex+1;
                *lenght   = *lenght -1;
                isString=0;
            } 
        }
    }
    else
    {
        /* do nothing */
    }
    return isString;
}

int getCharRex(char *text,char **nxtAddr,char *ch1)
{
    char ch=0;
    int isChar = (text[0]==CHAR_SYM)&&(text[2]==CHAR_SYM);
    *nxtAddr = text;
    if(isChar==1)
    {
        *ch1 = text[1];
        *nxtAddr = &(text[3]);
    }
    else if((text[0]==CHAR_SYM)&&(text[1]==BSLASH_SYM)&&(text[3]==CHAR_SYM))
    {
        ch =text[1];
        *nxtAddr = &(text[4]);
        switch(ch)
        {
            case 't':
                *ch1 = W2_SYM;
            break;
            case 'n':
                *ch1 = W3_SYM;
            break;
            case 'r':
                *ch1 = W4_SYM;
            break;
            case '0':
                *ch1 = END_STR;
            break;
            default:
                isChar =0;
            break;
        }
    }
    return isChar;
}
int getStringRex(char *text,char **nxtAddr,char *word)
{
    int indStd =0;
    int long1=0;
    int isStr =(isStringRex(text,&indStd,&long1)==1);
    if(isStr==1)
    {
        *nxtAddr = &(text[indStd+long1]);
        memcpy(word,&(text[indStd]),long1);
        word[long1] = '\0';
    }
    else
    {
        /* do nothing */
    }
    return isStr;
}
int getVarNameRex(char *text,char **nxtAddr,char *var)
{
    int indStd =0;
    int long1=0;
    int isVar =(isVarNameRex(text,&indStd,&long1)==1);
    if(isVar==1)
    {
        *nxtAddr = &(text[indStd+long1]);
        memcpy(var,&(text[indStd]),long1);
        var[long1] = '\0';
    }
    else
    {
        /* do nothing */
    }
    return isVar;
}

int isOperatorExpRex(char ch)
{
    return (ch==PLUS_SYM)||(ch==COMPLE_SYM)||(ch==STAR_SYM)||(ch==CONCAT)||(ch==RANGE_SYM)||(ch==Q_SYM);
}