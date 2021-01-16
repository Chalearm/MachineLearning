#include <stdio.h>
#include <string.h>
#include "simReadXML.h"
// 2 : '<' 3: '>' 4:'=' 5:'\"' 6:' ' 7:'\n' 8:'\t' 9: '\0'
#define OPEN_TAG_XML '<'
#define CLOSE_TAG_XML '>'
#define END_SYMBOL_XML '/'
#define EQUAL_SYMBOL_XML '='
#define DOUBLE_QUOT_SYMBOL '\"'
#define SINGLE_QUOT_SYMBOL '\''
#define SPACE_SYMBOL ' '
#define BACK_SLASH_SYMBOL '\\'
#define NEWLINE_SYMBOL '\n'
#define RETURN_CURSOR_SYMBOL '\r'
#define NULL_CHAR '\0'
#define TAB_SPACE_SYMBOL '\t'
#define EXCLAM_SYMBOL 33
#define MINUS_SYMBOL '-'

int initial_attrbXML(attrbXML* atXML)
{
    if(atXML == NULL)
    {
        return 0;
    }
    else
    {
        /*do nothing */
    }
    atXML->name = new_vector_char(0);
    atXML->value= new_vector_char(0);
    atXML->type = 0;
    return 1;
}

int initial_elementXML(elementXML* eleXML)
{
    if(eleXML == NULL)
    {
        return 0;
    }
    else
    {
        /*do nothing */
    }
    eleXML->name = new_vector_char(0);
    eleXML->value= new_vector_char(0);
    eleXML->next = NULL;
    eleXML->firstChild = NULL;
    eleXML->attrb = NULL;
    eleXML->com = NULL;
    eleXML->numAttrb = 0; 
    eleXML->typeEle = 0;
    return 1;
}

FILE* readFile2XMLTree(elementXML* root,const char* filename)
{
    if(root == NULL || filename == NULL)
    {
        return NULL;
    }
    else
    {
        /* do nothing */
    }
    FILE *fp = fopen(filename,"r");
    if(fp == NULL)
    {
        return NULL;
    }
    else
    {
        /* do nothing */
    }
    return fp;
}
int spaceExeception(int state,char reserveWord) /* 0 = execept, 1= not*/
{
    int ret =1;
    if (((state ==5)||(state==7)||(state==10))&&((reserveWord==7)||(reserveWord==9)))
    {
        ret = 0;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int parserXML(treeXML *root,elementXML *rootEle)
{
    int ret = 0;
    char ch = 0;
    int newState = 0;
    int oldState = 0;
    int index2;
    elementXML **nextDummy=NULL;
    if(root == NULL)
    {
        /* do nothing */
    }
    else if(root->fp == NULL)
    {
        /* do nothing */
    }
    else
    {
        ret = 1;
    }
    if(ret ==1)
    {
        nextDummy=&(rootEle->firstChild);
        /* printf("rootEle:%p \n",rootEle); */
        newState = (int)getLastDataCharList(&(root->state));
        do
        {
            if( (newState == 0) || (newState == 1)|| (newState==12) || (newState ==14) || (newState==18))
            {
                checkCommentXML(root,0);
            }
            else if(newState == 9)
            {
                rootEle->numAttrb++;
            }
            else if((newState == 2) && (oldState != 18)) /* tag name */
            {
                rootEle->name      = getLastValueVchar(&(root->stackParser));
            }
            else if((newState == 2) && oldState==18) //<P>[<]child
            {
                /*(root->index)++; */
                if(new_elementXML(nextDummy)==1)
                {
                    ret = parserXML(root,*nextDummy);
                    nextDummy = &((*nextDummy)->next);
                    /* return; */
                }
                else
                {
                    /* failed to getXML Element stop work */
                    return 0;
                }
            }
            else if(newState == 11)
            {
                rootEle->value      = getLastValueVchar(&(root->stackParser));
            }
            else if(((newState == 10) || (newState == 13)) && rootEle->numAttrb !=0)
            {
                /* add data to attribute */
                if(addData2Attrb(root,rootEle) ==0)
                {
                    return 0;
                }
                else
                {
                    /*do nothing */
                }
            }
            else
            {
                /* do nothing */
            }
            if (newState == -1)
            {
                 //printListVchar(&(root->stackParser),11); 
                 printTreeXML(root);
                 printCharList(&(root->state),0);
                ret = 0;
                break;
            }
            else
            {
                /* do nothing */
            }
            oldState = (int)getLastDataCharList(&(root->state));
            ch = reserveWord(root->str[root->index]);
            if (spaceExeception(oldState,ch) == 0)
            {
                if(oldState != 10)
                {
                    ch =0;
                }
                else
                {
                    index2 = root->index;
                    while(root->str[index2] !='\0')
                    {
                        if(root->str[index2] =='<')
                        {                        
                            if(root->str[index2+1] =='/')
                            {   ch =0;
                                
                            }
                            else
                            {
                                /* do nothing*/
                            }
                            break;
                        }
                        else
                        {
                            /* do nothing */
                        }
                        index2++;
                    }
                }
            }
            else
            {
                /* do nothing */
            }
            while( (ch >= 7) && (ch <= 10))
            {
                if(ch != 10)
                {
                    root->index++;
                }
                else
                {
                    /* do nothing */
                }
                if (ch == 10)
                {
                    index2= getStringFile(root->str,&(root->index),&(root->fp),BUFFER_SIZE);
                    if(index2==0)
                    {   /*printf("eeeeeeeeeeeeeeexit\n");*/
                        return 0;
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                ch = reserveWord(root->str[root->index]);
            }
            if((ch == 4) && (oldState ==10))/* special case <tag>[/...]</tag>*/
            {
                ch = 0;
            }
            else
            {
                /* do nothing */
            }
            if( ch != 0)
            {
                addNodeElement(&(root->stackParser),&(root->str[root->index]),1);
                newState = assignStateReadXML(root,ch);
                setTypeEleInTreeXML(rootEle,newState);
                /*push state to stack*/
                addData(&(root->state),newState);
                if(newState == 17)
                {
                    root->index++;
                    popXMLElement(root);
                    return 1;
                }
                else
                {
                    /* do nothing */
                }
            }
            else if(alphabetAndDigiCheck(root->str[root->index])==1 ||specialCharCheck(root->str[root->index],newState)==1)
            {
                index2 = findWord(root,newState);
                newState = assignStateReadXML(root,ch);
                /*push state to stack*/
                addData(&(root->state),newState);
                root->index = index2-1;
                /* to current step, index2 keeps next step for code line 223 (root)->index)++ */
            }
            else
            {
                /* do nothing */
            }
            /* to next step */
            (root->index)++;

        }
        while(getStringFile(root->str,&(root->index),&(root->fp),BUFFER_SIZE)!=0);
        /*printf("numList: %d\n",root->stackParser.numOfNode);*/
        /*printListVchar(&(root->stackParser),11);*/
        /*printCharList(&(root->state),-3);*/

        /*destructorListVchar(&(root->stackParser));*/
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

int initial_treeXML(treeXML *tXML)
{
    int ret = 0;
    if(tXML != NULL)
    {
        constructListVchar(&(tXML->stackParser));
        constructorCharList(&(tXML->state));  
        tXML->root = NULL;
        tXML->fp   = NULL;
        tXML->index = 0;
        ret =1;
    }
    else
    {
        /* do nothing */
    }

    return ret;
}

int setReadFile(treeXML *tXML,const char* filename)
{
    if(tXML == NULL || filename == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    tXML->fp = fopen(filename,"r");
    if(tXML->fp == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */ 
    }
    return 1;
}

int createTreeXML(treeXML *tXML)
{
    int ret =0;
    if(tXML == NULL)
    {
        /*do nothing */
    }
    else if(tXML->fp == NULL)
    {
        /*do nothing */
    }
    else
    {
        ret =1;
    }
    if(ret == 1)
    {
        tXML->root = (elementXML*)malloc(sizeof(elementXML));
        initial_elementXML(tXML->root);
        if(tXML->root == NULL)
        {
            return 0;
        }
        else
        {
            tXML->index = 0;
            addData(&(tXML->state),0);
            tXML->str[0] = '\0';
            ret = parserXML(tXML,tXML->root);
            popCharList(&(tXML->state));
        }
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

    /* 1 true 0 false */
char alphabetCheck(char in)
{
    char fact1 = (in >= 'a' ) && (in <= 'z');
    char fact2 = (in >= 'A' ) && (in <= 'Z');
    return (char)(fact1 || fact2);
}

char digiCheck(char in)
{
    return (char)(in >= '0' && in <= '9');
}

char alphabetAndDigiCheck(char in)
{
    return (char)(alphabetCheck(in)|| digiCheck(in));
}
    /* 2 : '<' 3: '>' 4:'/' 5:'=' 6:'\"' 7:' ' 8:'\n' 9: '\t' 10: '\0' 11: '\\' */
char reserveWord(char in)
{
    switch(in)
    {
        case OPEN_TAG_XML:
            return 2;
        case CLOSE_TAG_XML:
            return 3;
        case END_SYMBOL_XML:
            return 4;
        case EQUAL_SYMBOL_XML:
            return 5;
        case DOUBLE_QUOT_SYMBOL:
            return 6;
        case SPACE_SYMBOL:
            return 7;
        case NEWLINE_SYMBOL:
            return 8;
        case RETURN_CURSOR_SYMBOL:
            return 8;
        case TAB_SPACE_SYMBOL:
            return 9;
        case NULL_CHAR: 
            return 10;
        case BACK_SLASH_SYMBOL:
            return 11;
        case SINGLE_QUOT_SYMBOL:
            return 12;
        default:
            break;
    }
    return 0;
}
char  findPredefinedEntity(treeXML *root,int *index)
{
    char ch = (char)(0xFF);
    if(root != NULL && index != NULL)
    {
        if(root->str[*index] == '&')
        {
            if(memcmp("&quot",&root->str[*index],strlen("&quot"))==0)
            {
                ch = '\"';
                *index +=strlen("&quot");
            }
            else if(memcmp("&bslash",&root->str[*index],strlen("&bslash"))==0)
            {
                ch = '\\';
                *index +=strlen("&bslash");
            }
            else if(memcmp("&slash",&root->str[*index],strlen("&slash"))==0)
            {
                ch = '/';
                *index +=strlen("&slash");
            }
            else if(memcmp("&star",&root->str[*index],strlen("&star"))==0)
            {
                ch = '*';
                *index +=strlen("&star");
            }
            else if(memcmp("&perc",&root->str[*index],strlen("&perc"))==0)
            {
                ch = '%';
                *index +=strlen("&perc");
            }
            else if(memcmp("&amp",&root->str[*index],strlen("&amp"))==0)
            {
                ch = '&';
                *index +=strlen("&amp");
            }
            else if(memcmp("&apos",&root->str[*index],strlen("&apos"))==0)
            {
                ch = '\'';
                *index +=strlen("&apos");
            }
            else if(memcmp("&lt",&root->str[*index],strlen("&lt"))==0)
            {
                ch = '<';
                *index +=strlen("&lt");
            }
            else if(memcmp("&gt",&root->str[*index],strlen("&gt"))==0)
            {
                ch = '>';
                *index +=strlen("&gt");
            }
            else if(memcmp("&dl",&root->str[*index],strlen("&dl"))==0)
            {
                ch = '$';
                *index +=strlen("&dl");
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            /* do nothing*/
        }
    }
    else
    {
        /* do nothing */
    }
    return ch;
}
int  findWord(treeXML *root,char state)
{
    int index = root->index;
    int isBreak = 0;
/*int index2=0;*/
    char ch=(char)-1;
    const int isValue = (state == 5) || (state == 7) || (state == 10);
    charList chList;
    vector_char dummyVect = new_vector_char(0);
    constructorCharList(&chList);
    isBreak = (isValue == 1);
    while (isBreak == 1)
    {
        ch = (char)findPredefinedEntity(root,&index);/* it set next step by default*/
        if (ch != ((char)-1))
        {
            addData(&chList,ch);
        }
        else
        {
            isBreak = 0;
        }
    }
    while ((alphabetAndDigiCheck(root->str[index]) == 1) || (specialCharCheck(root->str[index],state) == 1))
    {
        addData(&chList,root->str[index]);
        index++;
        isBreak = (isValue == 1);
        while (isBreak == 1)
        {
            ch = (char)findPredefinedEntity(root,&index);/* it set next step by default*/
            if (ch != ((char)-1))
            {
                addData(&chList,ch);
            }
            else
            {
                isBreak = 0;
            }
        }

        if ((root->str[index] == ((char)13)) && (isValue == 1)) /* window case */
        {
            index++;
            if (index >= BUFFER_SIZE)
            {
                addData(&chList,'\n');
            }
            else if (root->str[index] ==10)
            {
                addData(&chList,'\n');
                index++;
            }
            if (root->str[index] == '\0')
            {
                root->index = index;
                getStringFile(root->str,&(root->index),&(root->fp),BUFFER_SIZE);
                index = root->index;
            }
            else
            {
                /* do nothing */
            }
        }
        else if ((root->str[index] == '\n') && (isValue == 1) )    /* linux case */
        {
            addData(&chList,'\n');
            index++;
            if(root->str[index] =='\0')
            {
                root->index = index;
                getStringFile(root->str,&(root->index),&(root->fp),BUFFER_SIZE);
                index = root->index;
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
    dummyVect = convertTovector_char(&chList);
/*    
for(index2=0;index2<dummyVect.lenght;index2++)
{
    printf("%d ",dummyVect.data[index2]);
}
printf("L[%d %c], %d ",root->str[index],root->str[index],index);
print_vector_char(&dummyVect,11);
*/
    addNodeVchar(&(root->stackParser),&dummyVect);
    delete_vector_char(&dummyVect);
    destructorCharList(&chList);
    return index;
}

void printReserveWord(char in)
{
    switch(in)
    {
        case OPEN_TAG_XML:
            printf("OPEN_TAG_XML\n");
            break;
        case CLOSE_TAG_XML:
            printf("CLOSE_TAG_XML\n");
            break;
        case END_SYMBOL_XML:
            printf("END_SYMBOL_XML\n");
            break;
        case EQUAL_SYMBOL_XML:
            printf("EQUAL_SYMBOL_XML\n");
            break;
        case DOUBLE_QUOT_SYMBOL:
            printf("DOUBLE_QUOT_SYMBOL\n");
            break;
        case SPACE_SYMBOL:
            printf("SPACE_SYMBOL\n");
            break;
        case NEWLINE_SYMBOL:
            printf("NEWLINE_SYMBOL\n");
            break;
        case RETURN_CURSOR_SYMBOL:
            printf("RETURN_CURSOR_SYMBOL\n");
            break;
        case TAB_SPACE_SYMBOL:
            printf("TAB_SPACE_SYMBOL\n");
            break;
        case NULL_CHAR: 
            printf("NULL_CHAR\n");
            break;
        case BACK_SLASH_SYMBOL:
           printf("BACK_SLASH_SYMBOL\n");
            break;
        case SINGLE_QUOT_SYMBOL:
            printf("SINGLE_QUOT_SYMBOL\n");
            break;
        default:
            /*printf("NO char %d\n",in);*/
            break;
    }
}

char getStringFile(element *str,int* index,FILE** fp,int size_buf)
{
    int isAscii13 = 0;
    int index2 =0;
    int num =0;
    if(str[*index] == '\0')
    {
        if(fgets((char*)str,size_buf,*fp) == 0)
        {
            *index = 0;
            fclose(*fp);
            *fp = NULL;
            return 0;
        }
        else
        {
            /* eliminate ascii 13 */
            num = strlen(str);
            for(index2=0;index2<num-1;index2++)
            {
                if(str[index2] == 13)
                {
                    isAscii13 =1;
                }
                else
                {
                    
                }
                if(isAscii13 ==1)
                {   
                    str[index2] = str[index2+1];
                }
                else
                {
                    
                }
            }
            if(isAscii13==1)
            {
                str[index2] = '\0';
            }
            else
            {
                /* do nothing */
            }
            /* end eliminate ascii 13 */
            *index = 0;
            return 1;
        }
    }
    else
    {
        /*do nothing */
    }
    return 1;
}
    
void destructorTreeXML(treeXML *tXML)
{
    if(tXML == NULL)
    {
        return;
    }
    else
    {
        tXML->index = 0;
        destructorCharList(&(tXML->state));
        if(tXML->fp !=NULL)
        {
            fclose(tXML->fp);
            tXML->fp = NULL;
        }
        else
        {
            /* do nothing */
        }
        if(tXML->root !=NULL)
        {
            destructorElementXML(tXML->root);
            free(tXML->root);
            tXML->root = NULL;
        }
        else
        {
            /* do nothing */
        }
    }
}

void destructorAttrbXML(attrbXML* attrb)
{
    if(attrb == NULL)
    {
        return;
    }
    else
    {
        delete_vector_char(&(attrb->name));
        delete_vector_char(&(attrb->value));
    }
}

void destructorElementXML(elementXML* elemXML)
{
    if(elemXML == NULL)
    {
        return;
    }
    else
    {
        delete_vector_char(&(elemXML->name));
        delete_vector_char(&(elemXML->value));
        int index = 0;
        elementXML *p = NULL,*p2=NULL;
        if(elemXML->com != NULL)
        {
            destructorSimStrList(&(elemXML->com->text));
            free(elemXML->com);
            elemXML->com = NULL;
        }
        else
        {
            /* do nothing */
        }
        if(elemXML->attrb != NULL)
        {
            for(index = 0;index < elemXML->numAttrb;index++)
            {
                destructorAttrbXML(&(elemXML->attrb[index]));
            }
            free(elemXML->attrb);
            elemXML->numAttrb = 0;
            elemXML->attrb  = NULL;
        }
        else
        {
            /* do nothing */
        }
        p = elemXML->firstChild;
        while(p !=NULL)
        {
            destructorElementXML(p);
            p2 = p;
            p = p->next;
            free(p2);
        }
        elemXML->firstChild = NULL;
    }
}

char assignStateReadXML(treeXML *tXML,char num)
{
    if(tXML == NULL)
    {
        return 0;
    }
    else
    {
        /* do nothing */
    }
    char oldState = getLastDataCharList(&(tXML->state));
    if(oldState == 0 && num ==2) /* OPEN_TAG_XML  [<]root no="1" value='2'>*/
    {                   /*<item no="0">0</item> */
                        /*<item no="1"></item></root>*/
        return 1;
    }
    else if( (oldState ==1|| oldState==14)&& num ==0)	// <[root] no="1" value='2'>
    {
        return 2;
    }
    else if(oldState ==2 && num==0)         /*<root [no]="1" value='2'>*/
    {
        /* name attribute   */
        return 3;
    }
    else if(oldState ==3 && num==5) /* see equal //<root no[=]"1" value='2'>    */
    {
        return 4;
    }
    else if(oldState ==4 && num==6) /* see double quot " ... no=["]1".. */
    {
        return 5;
    }
    else if(oldState ==5 && num==0) /*  see value  ... no="[1]" ... */
    {
        return 6;
    }
    else if(oldState ==5 && num==6) /*  see double quot close ... no="["] */
    {
        return 9;
    }
    else if(oldState ==6 && num==6) /*  see double quot close ... no="1["] */
    {
        return 9;
    }
    else if(oldState ==4 && num==12) /*see single quot open ... value=[']2' */
    {
        return 7;
    }
    else if(oldState ==7 && num==0) /* see value */
    {
        /*  ... value='[2]'... */
        return 8;
    }
    else if(oldState ==7 && num==12) /* see value */
    {
        /*  ... value='[']... */
        return 9;
    }
    else if(oldState ==8 && num==12) /* see single quot close   */
    {
                /* value='2[']  */
        return 9;
    }
    else if( oldState ==9 && num ==0) /* next attribute */
    {
         /* no="1" [value]='2' */
        return 3;
    }
    else if( (oldState ==9||oldState==2) && num ==4) /* see  end sysbol'/'  */
    {
            /* <item no='1' [/]> */
        return 13;
    }
    else if( oldState == 13 && num ==3 )/* see close > */
    {
        /* <item no='1' /[>] */
        return 17;
    }
    else if( (oldState ==9||oldState ==2) && num ==3 ) /* see  close >  */
    {
        /* addData(&(tXML->state),10);  <root no="1" value='2' [>] */
        return 10;
    }
    else if( oldState ==10 && (num ==0||num ==4)) /* see value of tag */
    {
        /* addData(&(tXML->state),11);//<root ..>[123]</... */
        return 11;
    }
    else if( oldState ==11 && num ==2) /* see open of close  tag  */
    {
            /* addData(&(tXML->state),12); // <root..>aa[<] */
        return 12;
    }
    else if( (oldState==18||oldState==12) && num ==4) /* see end sys */
    {
        /*  addData(&(tXML->state),15);// <root..>aa<[/]> */
        return 15;
    }
    else if(oldState ==15 && num ==0) /*  see name tag close  */
    {
            /* addData(&(tXML->state),16); // <root>aa</[root]> */
        return 16;
    }
    else if(oldState ==16 && num ==3) //<root>aaa</root[>]
    {
            /* addData(&(tXML->state),17); */
        return 17;
    }
    else if( (oldState ==10) && num == 2) // see close tag or new tag
    {
            /* addData(&(tXML->state),18); //<root..>[<] */
        return 18;
    }
    else if( oldState ==17 && num==2) /* <item /> [<] */
    {
        return 14;
    }
    else if(oldState ==18 && num ==0)/*sse <root..><[feed]*/
    {
        /*addData(&(tXML->state),2);*/
        return 2;
    }
    else
    {
        /*addData(&(tXML->state),-1);*/
        printf("num ---------------:%d %d\n",oldState,num);
        return -1;
    }
}

/* element getLastDataCharList(charList* list); */
int addData2Attrb(treeXML *root,elementXML *rootEle)
{
    int index=0,index2=0;
    char isValue = 0;
    int numPop = 0;
    vector_char dummyVCh = new_vector_char(0);
    if(root == NULL || rootEle==NULL)
    {
        return 0;
    }
    else if(rootEle->numAttrb <= 0)
    {
        return 0;
    }
    else
    {
        index = new_attrbXML(rootEle);
    }
    if(index == 0)
    {
        return 0;
    }
    else
    {
         /* do nothing */
    }
    /* keep   [/]> or <root no="2" ... [>]  */
    char oldState = getLastDataCharList(&(root->state));
    vector_char oldInput = getLastValueVchar(&(root->stackParser));
    popCharList(&(root->state));
    deleteLastNodeVchar(&(root->stackParser));
    /* end kepp [/].........        */
    /*for(index=0;index<rootEle->numAttrb;index++) */
    index = rootEle->numAttrb;
    while(index--)
    {
        /*pop " or ' */
        dummyVCh =  getLastValueVchar(&(root->stackParser));
        deleteLastNodeVchar(&(root->stackParser));
        popCharList(&(root->state));
        isValue = getLastDataCharList(&(root->state));
        if(isValue ==8 || isValue==6) /* 8= data in '...' 6 = data in "..." */
        {
            rootEle->attrb[index].value = getLastValueVchar(&(root->stackParser));
            numPop =3;
        }
        else
        {
            numPop=2;
            rootEle->attrb[index].value = new_vector_char(0);
        }
        if(dummyVCh.data != NULL && dummyVCh.lenght != 0)
        {
            if(dummyVCh.data[0] =='\'')
            {
                rootEle->attrb[index].type = 1;
            }
            else if(dummyVCh.data[0] =='\"')
            {
                rootEle->attrb[index].type = 0;
            }
            else
            {
                /* do nothing */
            }
            delete_vector_char(&dummyVCh);
        }
        else
        {
            /* do nothing */
        }
        for(index2 =0 ;index2<numPop;index2++)
        {     /*pop   = "(') value*/
            deleteLastNodeVchar(&(root->stackParser));
            popCharList(&(root->state));
        }
        rootEle->attrb[index].name = getLastValueVchar(&(root->stackParser));
        /* pop name */ 
        deleteLastNodeVchar(&(root->stackParser));
        popCharList(&(root->state));
    }
    addData(&(root->state),oldState);
    addNodeVchar(&(root->stackParser),&oldInput);
    delete_vector_char(&oldInput);
    delete_vector_char(&dummyVCh);
    return 1;
}

int new_elementXML(elementXML** eleXML)
{
    if(eleXML == NULL)
    {
        return 0;
    }
    else
    {
        /*do nothing  */
    }

    *eleXML = (elementXML*)malloc(sizeof(elementXML));
    if(*eleXML == NULL)
    {
        return 0;
    }
    else
    {
        initial_elementXML(*eleXML);
    }
    return 1;
}

int new_attrbXML(elementXML* eleXML)
{
    if(eleXML == NULL )
    {
        return 0;
    }
    else if(eleXML->numAttrb <0)
    {
        return 0;
    }
    else if(eleXML->numAttrb ==0)
    {
        return 1;
    }
    else
    {
        /*do nothing  */
    }
    int index =0;
    eleXML->attrb =(attrbXML*)malloc((eleXML->numAttrb)*sizeof(attrbXML));
    if(eleXML->attrb == NULL)
    {
        return 0;
    }
    else
    {
        for(index=0;index<eleXML->numAttrb;index++)
        {   
            initial_attrbXML(&(eleXML->attrb[index]));
        }
    }
    return 1;
}

void popXMLElement(treeXML *root)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        /*do nothing */
    }
    char oldState = getLastDataCharList(&(root->state));
    if(oldState != 17)
    {
        return;
    }
    else
    {
        deleteLastNodeVchar(&(root->stackParser));
        popCharList(&(root->state));
    }
    oldState = getLastDataCharList(&(root->state));
    int index=0;
    if(oldState == 13)
    {
        for(index=0;index<3;index++)
        {
            deleteLastNodeVchar(&(root->stackParser));
            popCharList(&(root->state));
        }
    }
    else if(oldState == 16)
    {
        for(index=0;index<3;index++)
        {
            deleteLastNodeVchar(&(root->stackParser));
            popCharList(&(root->state));
        }
        oldState = getLastDataCharList(&(root->state));
        if(oldState ==11)
        {
            deleteLastNodeVchar(&(root->stackParser));
            popCharList(&(root->state));
        }
        else
        {
            /* do nothing   */
        }
        for(index=0;index<3;index++)
        {
            deleteLastNodeVchar(&(root->stackParser));
            popCharList(&(root->state));
        }
    }
    else
    {
        return;
    }
}

void printTreeXML(treeXML *root)
{
    printf("stackParser num:%d\n",root->stackParser.numOfNode);
    printListVchar(&(root->stackParser),11);
    printf("state num:%d\n",root->state.numOfNode);
    if(root->state.numOfNode >0)
    {
        printCharList(&(root->state),-1);
    }
    else
    {
        /* do nothing */
    }
    printEleXML(root->root);
}

void printEleXML(elementXML *root)
{
    int index =0;
    printf("name:");
    print_vector_char(&(root->name),11);
    printf("value:");
    print_vector_char(&(root->value),11);
    if(root->typeEle == 0)
    {   
        printf("type : has value\n");
    }
    else
    {
        printf("type : non value\n");
    }
    elementXML *p = root->next;
	if(root->attrb != NULL)
	{
		printf("    Attrb :\n");
		for(index =0 ;index < root->numAttrb;index++)
		{
			printAttrbXML(&(root->attrb[index]));
		}
	}
	else
	{
		/* do nothing */
	}
    printf("--------------------------------------------\n");
	if(root->firstChild !=NULL)
	{
		for(p = root->firstChild;p!=NULL;p = p->next)
		{
			printf("next: %p\n",p);
			printEleXML(p);
		}
	}
	else
	{
		/* do nothing */
	}
}

void printAttrbXML(attrbXML *root)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        /*do nothing  */
    }
    if(root->type == 0)
    {
        printf("double quote\n");
    }
    else if(root->type == 1)
    {
        printf("single quote\n");
    }
    else
    {
        /* do nothing */
    }
    printf("name:");
    print_vector_char(&(root->name),11);
    printf("value:");
    print_vector_char(&(root->value),11);
}

void checkCommentXML(treeXML *tXML,char opt) 
/* opt 0 =  newState == 1||newState==12||newState ==14 ||newState==18
    opt 1 otherwise  */
{
    if(tXML == NULL)
    {
        return;
    }
    else if(tXML->fp == NULL)
    {
        return;
    }
    int index1 = 0;
    int numCheck = 0;
    if( opt==0)
    {
        numCheck =3;
    }
    else
    {
        numCheck =4;
    }
    while(index1 <numCheck)
    {
        if(tXML->str[tXML->index+index1] == '\0')
        {
            return;
        }
        else
        {
            index1++;
        }
    }
    int fact1 = 0;
    if(numCheck ==3)
    {
        fact1 = tXML->str[tXML->index] == EXCLAM_SYMBOL;
        fact1 &= tXML->str[tXML->index+1]  == MINUS_SYMBOL;
        fact1 &= tXML->str[tXML->index+2]  == MINUS_SYMBOL;
    }
    else if(numCheck ==4)
    {
        fact1  = tXML->str[tXML->index]    == OPEN_TAG_XML;
        fact1 &= tXML->str[tXML->index+1]  == EXCLAM_SYMBOL;
        fact1 &= tXML->str[tXML->index+2]  == MINUS_SYMBOL;
        fact1 &= tXML->str[tXML->index+3]  == MINUS_SYMBOL;
    }
    else
    {
        /*do nothing  */
    }
    if(fact1 ==0)
    {
        return;
    }
    else
    {
        if(numCheck ==3)
        {
            deleteLastNodeVchar(&(tXML->stackParser));
            popCharList(&(tXML->state));
        }
        else
        {
            /* do nothing */
        }
    }
    tXML->index += numCheck;
    index1 =0;
    while(getStringFile(tXML->str,&(tXML->index),&(tXML->fp),BUFFER_SIZE)!=0)
    {

        if(index1 ==0 && (tXML->str[tXML->index] == MINUS_SYMBOL))
        {
            index1 =1;
        }
        else if(index1 !=0 && (tXML->str[tXML->index] == MINUS_SYMBOL))
        {
            index1 =2;
        }
        else if(index1 ==2&&(tXML->str[tXML->index] == CLOSE_TAG_XML))
        {
            tXML->index++;
            return;
        }
        else
        {
            index1 = 0;
        }
        tXML->index++;
    }
}

elementXML* getRootElementXML(treeXML *root)
{
    if(root == NULL)
    {
        return NULL;
    }
    else
    {
        /*do nothing */
    }
    return root->root;
}

const void* getRootElementXML2(const void *obj)
{
    void *r = NULL;
    const treeXML *tObj = (const treeXML*)obj;
    if (tObj != NULL)
    {
        r = (void*)(tObj->root);
    }
    else
    {
        /*do nothing */
    }
    return r;
}

elementXML* getfirstChildXML(elementXML* root,const char *str)
{
    if(root == NULL)
    {
        return NULL;
    }
    else
    {
        /*do nothing */
    }
    elementXML *p = NULL;
    if (root->firstChild != NULL)
    {
        for (p = root->firstChild;p!=NULL;p = p->next)
        {
            if(compNameElemetVsCstr(&(p->name),str) == 1)
            {
                return p;
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
    return NULL;
}

void* getfirstChildXML2(const void *root,const char *str)
{
    elementXML *p = NULL;
    const elementXML *rt = (const elementXML*)root;
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        /*do nothing */
    }
    if (rt->firstChild != NULL)
    {
        for (p = rt->firstChild;p!=NULL;p = p->next)
        {
            if (compNameElemetVsCstr(&(p->name),str) == 1)
            {
                return p;
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
    return NULL;
}

int compNameElemetVsCstr(vector_char *a,const char *str)
{
    int index =0;
    if(a == NULL || str==NULL)
    {
        return 0;
    }
    else
    {
        /*do nothing  */
    }
    if(a->lenght != strlen(str))
    {
        return 0;
    }
    else
    {
        /*do nothing */
    }
    for(index =0;index <a->lenght && str[index] !='\0';index++)
    {
        if(a->data[index] != str[index])
        {
            return 0;
        }
        else
        {
            /*do nothing */
        }
    }
    return 1;
}
char specialCharCheck(char in,char state)
{  
    char ch = (state == 5) || (state == 7) || (state == 10);/* "..." or '...' or >...< */
    return (char)((in =='.')||(in=='_')||(in=='-') || (in==',')|| (in=='/')||(ch&&((in==' ')||(in=='&')||(in=='\r')||(in =='=')||(in=='\n')||(in=='!')||(in =='\t')||(in==':')||(in =='?')||(in=='(')||(in==')'))));
}
int isFirstChildXML(elementXML *root,const char *str)
{    
    int ret =0;
    if(root == NULL)
    {
        return ret;
    }
    else
    {
        /*do nothing */
    }
    elementXML *p=NULL;
    for(p=root->firstChild;p!=NULL;p = p->next)
    {
        if(compNameElemetVsCstr(&(p->name),str) == 1)
        {
            ret =1;
            return ret;
        }
        else
        {
            /* do nothing */
        }
    }
    return ret;
}
int isAttrbFromXMLEle(elementXML *root,const char *str,const char *strAttrb)
{
    int ret =0;
    elementXML *ele   = NULL;
    int index         = 0;
    ele = getfirstChildXML(root,str); 
    if(ele !=NULL)
    {
        for(index = 0;index < ele->numAttrb;index++)
        {
            if(compNameElemetVsCstr(&(ele->attrb[index].name),strAttrb) == 1)
            {
                ret =1;
                break;
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
    return ret;
}
vector_char getValueFirstChildXML(elementXML *root,const char *str,const char *defaultStr)
{
    vector_char vdata =new_vector_char(0);
    if(root == NULL || str == NULL ||defaultStr == NULL)
    {
        return vdata;
    }
    else if(root != NULL && str == NULL)
    {
        return cStr2V_char(defaultStr);  
    }
    else
    {
        /*do nothing */
    }  
    if(getfirstChildXML(root,str) != NULL)
    {
        copy_v_char(&vdata,&(getfirstChildXML(root,str)->value));
    }
    else
    {
        /* do nothing */
    }
    return vdata;
}

vector_char getAttrbFromXMLEle(elementXML *root,const char *str,const char *strAttrb,const char *defaultStr)
{
    vector_char vdata = new_vector_char(0);
    elementXML *ele   = NULL;
    int index         = 0;
    if(root == NULL || str == NULL ||defaultStr == NULL)
    {
        return vdata;
    }
    else if(root != NULL && str == NULL)
    {
        return cStr2V_char(defaultStr);  
    }
    else
    {
        /*do nothing */
    }
    ele = getfirstChildXML(root,str); 
    if(ele !=NULL)
    {
        for(index = 0;index < ele->numAttrb;index++)
        {
            if(compNameElemetVsCstr(&(ele->attrb[index].name),strAttrb) == 1)
            {
                copy_v_char(&vdata,&(ele->attrb[index].value));
                break;
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
    return vdata;
}
vector_char getAttrbFromXMLEle2(elementXML *root,const char *strAttrb,const char *defaultStr)
{
    vector_char vdata = new_vector_char(0);
    int index         = 0;
    int num = 0;
    if ((root == NULL)|| (defaultStr == NULL))
    {
        return vdata;
    }
    else if ((root == NULL)&&(defaultStr != NULL))
    {
        return cStr2V_char(defaultStr);  
    }
    else
    {
        /*do nothing */
    } 
    if(root != NULL)
    {
        num = root->numAttrb;
        for(index = 0;index < num;index++)
        {
            if(compNameElemetVsCstr(&(root->attrb[index].name),strAttrb) == 1)
            {
                copy_v_char(&vdata,&(root->attrb[index].value));
                break;
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
    return vdata;
}
void setTypeElement(elementXML* eleXML,char cmd)
{
    if(eleXML != NULL && ((cmd ==1) || (cmd ==0)))
    {
        eleXML->typeEle = cmd;
    }
    else
    {
        /* do nothing */
    }
}

void setTypeEleInTreeXML(elementXML *rootEle,char state)
{
    if(state == 13) /*<.... [/]> */
    {
        setTypeElement(rootEle,1);
    }
    else
    {
        /* do nothing */
    }
}

int getIntValueOfAttrbFromXMLEle(elementXML *root,const char *tagName,const char* attrb,const char* defaultVal)
{
    int value = 0;
    vector_char tagEle = new_vector_char(0);
    if(root != NULL && tagName != NULL && attrb != NULL)
    {

        tagEle    = getAttrbFromXMLEle(root,tagName,attrb,defaultVal);
        value     = (int)str2IntV_char(&tagEle);

    }
    else
    {
        /* do nothing */
    }
    delete_vector_char(&tagEle);
    return value;
}

double getDoubleValueOfAttrbFromXMLEle(elementXML *root,const char *tagName,const char* attrb,const char* defaultVal)
{
    double value = 0;
    vector_char tagEle = new_vector_char(0);
    if(root != NULL && tagName != NULL && attrb != NULL)
    {
        tagEle    = getAttrbFromXMLEle(root,tagName,attrb,defaultVal);
        value     = (double)str2DoubleV_char(&tagEle);
        delete_vector_char(&tagEle);
    }
    else
    {
        /* do nothing */
    }
    return value;
}

vector_char getValueDeepFirstChildXML(elementXML *root,simStrList *strList,const char *defaultStr)
{
    int numNode = 0;
    simString *str1 = NULL;
    int index = 0;
    vector_char vdata = new_vector_char(0);
    elementXML *rootDummy = root;
    if(root == NULL || strList == NULL)
    {
        /* do nothing */
    }
    else 
    {
        numNode = getNumNodeSimStrList(strList);
    }

    if(root != NULL && strList == NULL && defaultStr != NULL)
    {
        return cStr2V_char(defaultStr);  
    }
    else if(numNode > 0)
    {
        for(index =0 ;index < numNode-1;index++)
        {
           str1 = getnthNodeSimStrList(strList,index);
           rootDummy = getfirstChildXML(rootDummy,str1->data);
        }
        if(rootDummy != NULL && index == (numNode-1))
        {
            str1 = getnthNodeSimStrList(strList,numNode-1);
            if(getfirstChildXML(rootDummy,str1->data) != NULL)
            {
                copy_v_char(&vdata,&(getfirstChildXML(rootDummy,str1->data)->value));
            }
            else
            {
                /* do nohting */
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
    return vdata;
}

vector_char getAttrbDeepFromXMLEle(elementXML *root,simStrList *strList,const char *strAttrb,const char *defaultStr)
{
    vector_char vdata = new_vector_char(0);
    int index = 0;
    int numNode = 0;
    elementXML *rootDummy = root;
    simString *str1 = NULL;
    if((root == NULL || strList == NULL) && defaultStr == NULL)
    {
        return vdata;
    }
    else if(strList == NULL && defaultStr != NULL)
    {
        return cStr2V_char(defaultStr);  
    }
    else
    {
        numNode = getNumNodeSimStrList(strList);
    }  
    if(numNode >0)
    {
        for(index =0 ;index < numNode-1;index++)
        {
           str1 = getnthNodeSimStrList(strList,index);
           rootDummy = getfirstChildXML(rootDummy,str1->data);
        }
        if(rootDummy != NULL && index == (numNode-1))
        {
            str1 = getnthNodeSimStrList(strList,numNode-1);
            vdata = getAttrbFromXMLEle(rootDummy,str1->data,strAttrb,defaultStr);
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
    return vdata;
}

int getIntValueOfAttrbDeepFromXMLEle(elementXML *root,simStrList *strList,const char* attrb,const char* defaultVal)
{
    int value = 0;
    int index = 0;
    elementXML *rootDummy = root;
    simString *str1 = NULL;
    int numNode = 0;
    if(strList == NULL && defaultVal == NULL)
    {
        value =0;
    }
    else if(strList == NULL && defaultVal != NULL)
    {
        value = str2Int(defaultVal);
    }
    else
    { 
        numNode = getNumNodeSimStrList(strList);
    }
    if(numNode > 0)
    {
        for(index =0 ;index < numNode-1;index++)
        {
           str1 = getnthNodeSimStrList(strList,index);
           rootDummy = getfirstChildXML(rootDummy,str1->data);
        }
        if(rootDummy != NULL && index == (numNode -1))
        {
            str1 = getnthNodeSimStrList(strList,numNode-1);
            value = getIntValueOfAttrbFromXMLEle(rootDummy,str1->data,attrb,defaultVal);
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
    return value;
}

double getDoubleValueOfAttrbDeepFromXMLEle(elementXML *root,simStrList *strList,const char* attrb,const char* defaultVal)
{
    double value = 0.0;
    int index =0;
    int numNode = 0;
    simString *str1 = NULL;
    elementXML *rootDummy = root;
    if(strList == NULL && defaultVal == NULL)
    {
        value =0;
    }
    else if(strList == NULL && defaultVal != NULL)
    {
        value = str2Double(defaultVal);
    }
    else
    {
        numNode = getNumNodeSimStrList(strList);
    }
    if(numNode > 0)
    {
        for(index =0 ;index < numNode-1;index++)
        {
            str1 = getnthNodeSimStrList(strList,index);
            rootDummy = getfirstChildXML(rootDummy,str1->data);
        }
        if(rootDummy != NULL && index == numNode-1)
        {
            str1 = getnthNodeSimStrList(strList,numNode-1);
            value = getDoubleValueOfAttrbFromXMLEle(rootDummy,str1->data,attrb,defaultVal);
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
    return value;
}

int copyAttrbXML(attrbXML* rhs,attrbXML* lhs)
{
    int ret = 0;
    if((rhs != lhs) && (rhs != NULL) && (lhs != NULL))
    {  
        ret = 1;
        delete_vector_char(&(rhs->name));
        delete_vector_char(&(rhs->value));
        copy_v_char(&(rhs->name),&(lhs->name));
        copy_v_char(&(rhs->value),&(lhs->value));
        rhs->type = lhs->type;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

void clearAttrbInElementXML(elementXML* elemXML)
{
    if(elemXML != NULL)
    {
        int index = 0;
        if(elemXML->attrb != NULL)
        {
            for(index = 0;index < elemXML->numAttrb;index++)
            {
                destructorAttrbXML(&(elemXML->attrb[index]));
            }
            free(elemXML->attrb);
            elemXML->numAttrb = 0;
            elemXML->attrb  = NULL;
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

int copyElementXML(elementXML *rhs,elementXML *lhs)
{
    int ret = 0;
    int index = 0;
    int num = 0;
    if ((rhs != lhs) && (lhs != NULL) && (rhs != NULL))
    {
        rhs->typeEle = lhs->typeEle;
        copy_v_char(&(rhs->name),&(lhs->name));
        copy_v_char(&(rhs->value),&(lhs->value));
        rhs->numAttrb = lhs->numAttrb;	
        ret = new_attrbXML(rhs);
        if( ret == 1)
        {
            num = rhs->numAttrb;
            for(index = 0;index <num;index++)
            {
                copyAttrbXML(&(rhs->attrb[index]),&(lhs->attrb[index]));
            }
            if((rhs->next != NULL) && (lhs->next != NULL))
            {
                destructorElementXML(rhs->next);
                free(rhs->next);
                rhs->next = NULL;
            }
            else
            {
                /* do nothig */
            }
            if((rhs->next == NULL) && (lhs->next !=NULL))
            {
                ret  = new_elementXML(&(rhs->next));
                if(ret ==1)
                {
                    ret = copyElementXML(rhs->next,lhs->next);
                }
                else
                {
                    /* do nothig */
                }
            }
            else
            {
                /* do nothing */
            }
            if(ret ==1 && lhs->firstChild != NULL)
            {
                ret = new_elementXML(&(rhs->firstChild));
                if(ret == 1)
                {
                    ret = copyElementXML(rhs->firstChild,lhs->firstChild);
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
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
elementXML* getNextELementXML(elementXML *root,const char *str,int order)
{
    elementXML *p = NULL;
    int index = 0;
    int ret = 0;
    if(root != NULL && str != NULL && order >= 0)
    {
        for(p=root;p!=NULL;p=p->next)
        {
            if(compNameElemetVsCstr(&(p->name),str) == 1)
            {       
                if(index == order)
                {
                    ret = 1;
                    break;
                }
                else
                {
                    index++;
                }
            }
            else
            {
                /* do nothing */
            }
        }
        if(ret == 0)
        {
            p = NULL;
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
    return p;
}

void* getNextELementXML2(void *root,const char *str,int order)
{
    elementXML *p = NULL;
    elementXML *r1 = NULL;
    void *p2 = NULL;
    int index = 0;
    int ret = 0;
    if ((root != NULL) && (str != NULL) && (order >= 0))
    {
        r1 = (elementXML*)root;
        for (p = r1;p != NULL;p = p->next)
        {
            if (compNameElemetVsCstr(&(p->name),str) == 1)
            {       
                if (index == order)
                {
                    ret = 1;
                    break;
                }
                else
                {
                    index++;
                }
            }
            else
            {
                /* do nothing */
            }
        }
        if (ret == 0)
        {
            p = NULL;
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
    p2 = (void*)p;
    return p2;
}
elementXML* getAnElementXML(treeXML *root,tagXMLAdd* searcher)
{
    int num = 0;
    int index = 0;
    int ret = 0;
    elementXML *p = NULL;
    simString msg;
    char order = 0;
    initialSimString(&msg);
    if(root != NULL && searcher != NULL)
    {
        num = getNumOfTagXMLAdd(searcher);
        if(root->root != NULL && num >0)
        {
            p = root->root;
            for(index = 0;index <num;index++)
            {
                ret = getTagXMLValue(searcher,index,&msg,&order);
                if(ret == 1)
                {
                    p = getNextELementXML(p,msg.data,(int)order);
                    if(p != NULL && index != (num-1))
                    {
                        p = p->firstChild;
                    }
                    else if(p==NULL)
                    {
                        ret = 0;
                        index = num;
                    }
                }
                else
                {
                    index=num;
                    p = NULL;
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
    destructSimString(&msg);
    return p;
}
/* ------------ tagXMLAdd --------------*/
void initialTagXMLAdd(tagXMLAdd* tagXML)
{
    if(tagXML != NULL)
    {
        constructorCharList(&(tagXML->arrayOrder));
        initialSimStrList(&(tagXML->tagName));
    }
    else
    {
        /* do nothing */
    }
}
void makeTagXMLAddEmpty(tagXMLAdd* tagXML)
{
    if(tagXML != NULL)
    {
        destructorSimStrList(&(tagXML->tagName));
        destructorCharList(&(tagXML->arrayOrder));
    }
    else
    {
        /* do nothing */
    }
}
int copyTagXMLAdd(tagXMLAdd* tagXMLLsh,tagXMLAdd* tagXMLRsh)
{
    int ret = 0;
    if( (tagXMLLsh != tagXMLRsh) && (tagXMLLsh !=NULL) && (tagXMLRsh != NULL))
    {
        ret  = copySimStrList(&(tagXMLLsh->tagName),&(tagXMLRsh->tagName));
        ret &= copyCharList(&(tagXMLLsh->arrayOrder),&(tagXMLRsh->arrayOrder));
    }
    else
    {
        /* do nothing */  
    } 
    return ret;
}

int addTagXMLvalueWithCStr(tagXMLAdd* tagXML,const char *msg,char val)
{
    int ret = 0;
    simString msg1;
    initialSimString(&msg1);
    convertCString2SimString(&msg1,msg);
    ret = addTagXMLValue(tagXML,&msg1,val);
    destructSimString(&msg1);
    return ret;
}

int addTagXMLValue(tagXMLAdd* tagXML,simString *msg,char val)
{
    int ret =0;
    if(tagXML != NULL && msg != NULL)
    { 
        ret  = addDataPt(&(tagXML->arrayOrder),&val);
        ret &= addNodeSimStrList(&(tagXML->tagName),msg);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
int removeTagXMLValue(tagXMLAdd* tagXML,int index)
{
    int ret = 0;
    if(tagXML != NULL && index >= 0)
    {
        ret = deleteIndexElementCharList(&(tagXML->arrayOrder),index);
        ret &= deleteNodeSimStrListWithIndex(&(tagXML->tagName),index);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

int insertTagXMLValueAfterIndexWithCStr(tagXMLAdd* tagXML,int index,const char *msg,char val)
{
    int ret = 0;
    simString msg1;
    initialSimString(&msg1);
    convertCString2SimString(&msg1,msg);
    ret = insertTagXMLValueAfterIndex(tagXML,index,&msg1,val);
    destructSimString(&msg1);
    return ret;
}

int insertTagXMLValueAfterIndex(tagXMLAdd* tagXML,int index,simString *msg,char val)
{
    int ret = 0;
    if(tagXML != NULL && index >= 0)
    {
        ret = insetWithIndexCharList(&(tagXML->arrayOrder),val,index);
        ret &= insertNodeSimStrList(&(tagXML->tagName),index,msg);
    }
    else
    {
        /* do nothing */
    }
    return ret;
}

int getTagXMLValue(tagXMLAdd* tagXML,int index,simString *msg,char *val)
{
    int ret = 0;
    simString *p = NULL;
    if(tagXML != NULL && index >= 0 && msg!=NULL && val !=NULL)
    {
        *val = getDataCharList(&(tagXML->arrayOrder),index);
        p = getnthNodeSimStrList(&(tagXML->tagName),index);
        copySimStr(msg,p);
        ret = 1;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
void destructTagXMLAdd(tagXMLAdd* tagXML)
{
    if(tagXML != NULL)
    { 
        destructorSimStrList(&(tagXML->tagName));
        destructorCharList(&(tagXML->arrayOrder));
    }
    else
    {
        /* do nothing */
    }
}

int getNumOfTagXMLAdd(tagXMLAdd* tagXML)
{
    int num = 0;
    if(tagXML != NULL)
    { 
        num = getNumNodeSimStrList(&(tagXML->tagName));
        if(num > countCharList(&(tagXML->arrayOrder)))
        {
            num = countCharList(&(tagXML->arrayOrder));
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
    return num;
}

/* comment operation */
/* 0 upper Element, 1 behind Element, 2 below Element */
int makeACommentInElementXML(elementXML* root,int type)
{
    int ret =0;
    if(root != NULL)
    {
        root->com = (struct commentText*)malloc(sizeof(struct commentText));
        if(root->com != NULL)
        {
            ret = initialSimStrList(&(root->com->text));
            root->com->type = type*((type > -1) && (type < 3)); 
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
    return ret;
}

int addCommentInElementXML(elementXML* root,simString* data)
{
    int ret = 0;
    if(root !=NULL)
    {
        if(root->com != NULL)
        {
            ret = addNodeSimStrList(&(root->com->text),data);
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
    return ret;
}

int getTypeCommentInElementXML(elementXML* root)
{
    int ret = 0;
    if(root != NULL)
    {
        if(root->com != NULL)
        {
            ret = root->com->type;
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
    return ret;
}

/* 0 upper Element, 1 behind Element, 2 below Element */
int writeCommentIntoFpElementXML(elementXML* root,FILE* fp,int disSpace,int startIndex)
{
    int ret = 0;
    int index = 0;
    int num = 0;
    simString dummyTxt;
    simString dummyBuff;
    simString dummyComTxt;
    simString *source = NULL;
    initialSimString(&dummyTxt);
    initialSimString(&dummyBuff);
    initialSimString(&dummyComTxt);
    const char *comStr = "<!--";
    const char *comEnd = "-->";
    ret = newSimStrWithInitailData(&dummyTxt,disSpace,' ');
    if(ret == 1 && root != NULL && fp != NULL && (disSpace > -1) && (startIndex >0))
    {
        if(root->com != NULL)
        {
            convertCString2SimString(&dummyComTxt,comStr);
            ret = concatSimString(&dummyTxt,&dummyComTxt,&dummyBuff);
            convertCString2SimString(&dummyComTxt,comEnd);
            num = getNumNodeSimStrList(&(root->com->text));
            if(ret == 1 && num >0 && (startIndex < num))
            {
                if(startIndex ==0)
                {
                    source = getnthNodeSimStrList(&(root->com->text),0);
                    ret = concatSimString(&dummyBuff,source,&dummyBuff);
                    fprintf(fp,"%s",dummyBuff.data);
                    startIndex = 1;
                }
                else
                {
                    /* do nothing */
                }
                for(index = startIndex;(index <(num-1))&&(ret == 1);index++)
                {
                    source = getnthNodeSimStrList(&(root->com->text),index);
                    ret = concatSimString(&dummyTxt,source,&dummyBuff);
                    if(ret == 1)
                    {
                        fprintf(fp,"%s",dummyBuff.data);
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                if(ret ==1)
                {
                    source = getnthNodeSimStrList(&(root->com->text),num-1);
                    ret = concatSimString(&dummyTxt,source,&dummyBuff);
                    if(ret == 1)
                    {
                        ret = concatSimString(&dummyBuff,&dummyComTxt,&dummyBuff);
                    }
                    else
                    {
                        /* do nothing */
                    }
                    if(ret ==1)
                    {
                        fprintf(fp,"%s",dummyBuff.data);
                    }
                }
                else
                {
                    /* do nothing */
                }
            }
            else
            {
                if(num==0)
                {
                    ret =1;
                }
                else
                {
                    /* do nothing */
                }
            }
        }
        else
        {
            ret =1;
        }
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&dummyTxt);
    destructSimString(&dummyBuff);
    destructSimString(&dummyComTxt);
    return ret;
}

int getSourceToTreeXML(treeXML *treeObj,const char *namefile)
{
    int ret =initial_treeXML(treeObj);
    if(namefile != NULL && ret == 1)
    {
        ret = setReadFile(treeObj,namefile);
        if(ret ==1)
        {
            ret = createTreeXML(treeObj);
        }
        else
        {
            /* do nothing */
        }
        if(ret == 0)
        {
            destructorTreeXML(treeObj);
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
    return ret;
}

int initialComment(commentText* comment)
{
    int ret = 0;
    if(comment != NULL)
    {
        initialSimStrList(&(comment->text));
        comment->type = 0;
        ret =1;
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
/*defined 
    use  12 bits
    last nibble
    0 = sign
    1 = unsign
    0x000 char
    0x010 int
    0x020 short
    0x030 long
    0x040 float
    0x050 double
    0x060 long double
    0x070 vector_char
    0x080 simString
    
*/
int getValueOfFirstChildEle2Var(elementXML *root,const char *str,const char *defaultStr,void *var,unsigned int typeVar)
{
    int ret = 0;
    vector_char dummyVal = new_vector_char(0);
    if(root != NULL && str !=NULL && defaultStr !=NULL)
    {
        dummyVal = getValueFirstChildXML(root,str,defaultStr);
        ret = getVectorToVar(&dummyVal,var,typeVar);
    }
    else
    {
        /* do noting */
    }
    delete_vector_char(&dummyVal);
    return ret;
}

int getValueOfFirstChildEle2Var2(const void *root,const char *str,const char *defaultStr,void *var,unsigned int typeVar)
{
    int ret = 0;
    elementXML *rt = NULL;
    vector_char dummyVal = new_vector_char(0);
    if(root != NULL && str !=NULL && defaultStr !=NULL)
    {
        rt = (elementXML*)root;
        dummyVal = getValueFirstChildXML(rt,str,defaultStr);
        ret = getVectorToVar(&dummyVal,var,typeVar);
    }
    else
    {
        /* do noting */
    }
    delete_vector_char(&dummyVal);
    return ret;
}
int getAttrbValueOfFirstChildEle2Var(elementXML *root,const char *tagName,const char* attrb,const char* defaultVal,void *var,unsigned int typeVar)
{
    int ret = 0;
    vector_char dummyVal = new_vector_char(0);
    if(root != NULL && tagName !=NULL && defaultVal !=NULL && var != NULL && attrb != NULL)
    {
        dummyVal = getAttrbFromXMLEle(root,tagName,attrb,defaultVal);
        ret = getVectorToVar(&dummyVal,var,typeVar);
        if(ret ==0)
        {
            printf("     ret =0;\n");
        }
    }
    else
    {
        /* do noting */
    }
    delete_vector_char(&dummyVal);
    return ret;
}
int getAttrbValueOfFirstChildEle2Var2(const void *root,const char *tagName,const char* attrb,const char* defaultVal,void *var,unsigned int typeVar)
{
    int ret = 0;
    elementXML *rt = (elementXML*)root;
    vector_char dummyVal = new_vector_char(0);
    if ( (root != NULL) && (tagName !=NULL) && (defaultVal != NULL) && (var != NULL) && (attrb != NULL))
    {
        dummyVal = getAttrbFromXMLEle(rt,tagName,attrb,defaultVal);
        ret = getVectorToVar(&dummyVal,var,typeVar);
        if (ret == 0)
        {
            printf("ret =0;\n");
        }
    }
    else
    {
        /* do noting */
    }
    delete_vector_char(&dummyVal);
    return ret;
}

int getAttrbValXMLEle2Var2(const void *ele,const char* attrb,const char* defaultVal,void *var,unsigned int typeVar)
{
    int ret = 0;
    elementXML *rt = (elementXML*)ele;
    vector_char dummyVal = new_vector_char(0);
    if ( (ele != NULL)  && (defaultVal != NULL) && (var != NULL) && (attrb != NULL))
    {
        dummyVal = getAttrbFromXMLEle2(rt,attrb,defaultVal);
        ret = getVectorToVar(&dummyVal,var,typeVar);
        if (ret == 0)
        {
            printf("ret =0;\n");
        }
    }
    else
    {
        /* do noting */
    }
    delete_vector_char(&dummyVal);
    return ret;
}
int getVectorToVar(vector_char *dummyVal,void* var,unsigned int typeVar)
{
    int ret = 1;
    if(dummyVal != NULL && var != NULL)
    {
        switch (typeVar)
        {
            case 0x000: /* char */
                *((char*)var) = (char)str2IntV_char(dummyVal);
                break;
            case 0x002: /* char ascii */
                if(dummyVal->lenght >0)
                {
                    *((char*)var) = (char)dummyVal->data[0];
                }
                else
                {
                    *((char*)var) =0;
                }
                break;
            case 0x001: /* unsigned char */
                *((unsigned char*)var) = (unsigned char)str2IntV_char(dummyVal);
                break;
            case 0x010: /* int */
                *((int*)var) = (int)str2IntV_char(dummyVal);
            break;
            case 0x011: /*unsigned int */
                *((unsigned int*)var) = (unsigned int)str2IntV_char(dummyVal);
            break;
            case 0x020: /*short */
                *((short*)var)  = (short)str2IntV_char(dummyVal);
            break;
            case 0x021: /*unsigned short */
                *((unsigned short*)var) = (unsigned short)str2IntV_char(dummyVal);
            break;
            case 0x030: /*long*/
                *((long*)var) = (long)str2IntV_char(dummyVal);
            break;
            case 0x031: /*unsigned long */
                *((unsigned long*)var) = (unsigned long)str2IntV_char(dummyVal);
            break;
            case 0x040: /*float*/
                *((float*)var) = (float)str2DoubleV_char(dummyVal);
            break;
            case 0x050: /*double */
                *((double*)var) = (double)str2DoubleV_char(dummyVal);
            break;
            case 0x060: /* long double */
                *((long double*)var) = (long double)str2DoubleV_char(dummyVal);
            break;
            case 0x070: /* vector_char */
                copy_v_char((vector_char*)var,dummyVal);
            break;
            case 0x080: /* simString */
                convertVectorChar2SimString((simString *)var,dummyVal);
            break;
            default:
                ret = 0;
            break;
        }   
    }
    else
    {
        ret = 0;
    }
    return ret;    
}
