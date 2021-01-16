#include <stdio.h>
#include "simReadXML.h"
#include "simMatChar.h"
#include "listMatChar.h"
#include "listChar.h"
#include "debug.h"
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
		//do nothing
	}
	atXML->name = new_vector_char(0);
	atXML->value= new_vector_char(0);
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
		//do nothing
	}
	eleXML->name = new_vector_char(0);
	eleXML->value= new_vector_char(0);
	eleXML->next = NULL;
	eleXML->firstChild = NULL;
	eleXML->attrb = NULL;
	eleXML->numAttrb = 0; 
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
		//do nothing
	}
	FILE *fp = fopen(filename,"r");
	if(fp == NULL)
	{
		return NULL;
	}
	else
	{
		//do nothing
	}
	return fp;
}
void parserXML(treeXML *root,elementXML *rootEle)
{
	if(root == NULL)
	{
		return;
	}
	else if(root->fp == NULL)
	{
		return;
	}
	else
	{
		//do nohting
	}
	char ch;
	char newState=0,oldState=0;
	int index2;
	elementXML **nextDummy=NULL;
	nextDummy=&(rootEle->firstChild);
	//printf("rootEle:%p \n",rootEle);
	newState = getLastDataCharList(&(root->state));
	do
	{
		if( newState == 1||newState==12||newState ==14 ||newState==18)
		{
			checkCommentXML(root,0);
		}
		else if(newState == 9)
		{
			rootEle->numAttrb++;
		}	
	/*
		else if(oldState ==14 && newState ==2)
		{
			printf("next ele %p ",*nextDummy);
				nextDummy = &((*nextDummy)->next);
			if(new_elementXML(nextDummy)==0)
			{
				printf("newState=1 newEle\n");
				//failed to getXML Element stop work
				return;
			}
			else
			{
				//do nothing
			}
			printf("%p \n",*nextDummy);
		}
	*/
		else if(newState == 2 && oldState==18) //<P>[<]child
		{	
		//	(root->index)++;
			if(new_elementXML(nextDummy)==1)
			{
			//	printf("ro:%p %p\n",rootEle,*nextDummy);
				parserXML(root,*nextDummy);
				nextDummy = &((*nextDummy)->next);
				//return;
			}
			else
			{
				//failed to getXML Element stop work
				return;
			}
		}
		else if(newState == 2) // tag name
		{
			rootEle->name      = getLastValueVchar(&(root->stackParser));
			/*
			printf("name .....%p\n",rootEle);
			printListVchar(&(root->stackParser),11);
			printf("-------------\n");
			printf("add nameState \n");
			*/
		}
		else if(newState ==11)
		{
			/*
			printf("value .....\n");
			printListVchar(&(root->stackParser),11);
			printf("-------------\n");
			*/
			rootEle->value      = getLastValueVchar(&(root->stackParser));	
		}
		else if(newState == 17)
		{
		//	printf(" 17 177 171 7\n");
/*	
	printCharList(&(root->state),-3);
	printListVchar(&(root->stackParser),11);
	printf("1---------\n");*/
			popXMLElement(root);
	/*
	printCharList(&(root->state),-3);
	printListVchar(&(root->stackParser),11);
	printf("2---------\n");
		*/
			return;
		}
		else if((newState == 10||newState==13) && rootEle->numAttrb !=0)
		{
			//add data to attribute
			if(addData2Attrb(root,rootEle) ==0)
			{
				return;
			}
			else
			{
				//do nothing
			}
		}
		if(newState==-1)
		{
			break;
		}
		oldState = getLastDataCharList(&(root->state));
		ch = reserveWord(root->str[root->index]);
		while(ch >= 7 && ch <= 10)
		{		
			if(ch != 10)
			{
				root->index++;	
			}
			else
			{
				//do nothing
			}
			if(ch == 10)
			{
		        index2=	getStringFile(root->str,&(root->index),&(root->fp),BUFFER_SIZE);
				if(index2==0)
				{	printf("eeeeeeeeeeeeeeexit\n");
					return;
				}
			}
			ch = reserveWord(root->str[root->index]);
		}
		if(ch != 0)
		{
			addNodeElement(&(root->stackParser),&(root->str[root->index]),1);
			newState = assignStateReadXML(root,ch);
		//push state to stack
			addData(&(root->state),newState);
		}
	//	else if(alphabetAndDigiCheck(root->str[root->index]) == 1)
	        else if(alphabetAndDigiCheck(root->str[root->index])==1 ||specialCharCheck(root->str[root->index])==1)
		{
			index2 = findWord(&(root->str[root->index]));
			addNodeElement(&(root->stackParser),&(root->str[root->index]),index2);
			newState = assignStateReadXML(root,ch);
			//push state to stack
			addData(&(root->state),newState);
			root->index = root->index+index2-1;
		}
		//ch = getLastDataCharList(&(root->state));
		(root->index)++;
		
	}
	while(getStringFile(root->str,&(root->index),&(root->fp),BUFFER_SIZE)!=0);
//	printf("numList: %d\n",root->stackParser.numOfNode);
//	printListVchar(&(root->stackParser),11);
//	printCharList(&(root->state),-3);
	
//	destructorListVchar(&(root->stackParser));
}
int initial_treeXML(treeXML *tXML)
{
	if(tXML == NULL)
	{
		return 0;
	}
	else
	{
		//do nothing
	}
	constructListVchar(&(tXML->stackParser));
	constructorCharList(&(tXML->state));
	tXML->root = NULL;
	tXML->fp   = NULL;
	tXML->index = 0;
	return 1;
}
int setReadFile(treeXML *tXML,const char* filename)
{
	if(tXML == NULL || filename == NULL)
	{
		return 0;
	}
	else
	{
		//do nothing
	}
	tXML->fp = fopen(filename,"r");
	if(tXML->fp == NULL)
	{
		return 0;
	}
	else
	{
		//do nothing
	}
	return 1;	
}
void createTreeXML(treeXML *tXML)
{
	if(tXML == NULL)
	{
		return;
	}
	else if(tXML->fp == NULL)
	{
		return;
	}
	else
	{
		//do nothing
	}
	tXML->root = (elementXML*)malloc(sizeof(elementXML));
	printOpt(__LINE__-1,"createTreeXML","simReadXML.c",(void*)tXML->root,0);
	initial_elementXML(tXML->root);
	if(tXML->root == NULL)
	{
		return;
	}
	else
	{
		tXML->index = 0;
		addData(&(tXML->state),0);
		tXML->str[0] = '\0';
		printf("tXML->root: %p\n",tXML->root);
		parserXML(tXML,tXML->root);
	}
}
// 1 true 0 false
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
// 2 : '<' 3: '>' 4:'/' 5:'=' 6:'\"' 7:' ' 8:'\n' 9: '\t' 10: '\0' 11: '\\'
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
int  findWord(char* in)
{
    int index = 0;
    while ((alphabetAndDigiCheck(in[index]) == 1) || (specialCharCheck(in[index]) == 1))
    {
        index++;	
    }
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
		//	printf("NO char %d\n",in);
			break;
	}

}
char getStringFile(element *str,int* index,FILE** fp,int size_buf)
{
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
			*index = 0;
			return 1;
		}
	}
	else
	{
		//do nothing
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
			printf("delelte fp");
			fclose(tXML->fp);	
			tXML->fp = NULL;
		}
		else
		{
			//do nothing
		}
		if(tXML->root !=NULL)
		{
			destructorElementXML(tXML->root);
            printOpt(__LINE__+1,"destructorTreeXML","simReadXML.c",(void*)tXML->root,1);	
			free(tXML->root);
			tXML->root = NULL;
		}
		else
		{
			//do nothing
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
		if(elemXML->attrb != NULL)
		{
			for(index = 0;index < elemXML->numAttrb;index++)
			{
				destructorAttrbXML(&(elemXML->attrb[index]));
			}
            printOpt(__LINE__+1,"destructorElementXML","simReadXML.c",(void*)elemXML->attrb,1);	
			free(elemXML->attrb);
			elemXML->numAttrb = 0;
			elemXML->attrb 	  = NULL;	
		}
		else
		{
			//do nothing
		}
		p = elemXML->firstChild;
		while(p !=NULL)
		{
			destructorElementXML(p);
			p2 = p;
			p = p->next;
			 printOpt(__LINE__+1,"destructorElementXML","simReadXML.c",(void*)p2,1);	
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
		//do nothing
	}
	char oldState = getLastDataCharList(&(tXML->state));
	if(oldState == 0 && num ==2) // OPEN_TAG_XML  [<]root no="1" value='2'>
	{			     //			<item no="0">0</item>
				     //		<item no="1"></item></root>
		return 1;
	}
	else if( (oldState ==1|| oldState==14)&& num ==0)	// <[root] no="1" value='2'>
	{
		return 2;
	}
	else if(oldState ==2 && num==0)		// <root [no]="1" value='2'>
	{
		// name attribute
		return 3;
	}
	else if(oldState ==3 && num==5) //see equal //<root no[=]"1" value='2'>
	{
		return 4;
	}
	else if(oldState ==4 && num==6) // see double quot " ... no=["]1"..
	{
		return 5;
	}
	else if(oldState ==5 && num==0) // see value  ... no="[1]" ...
	{
		return 6;
	}
	else if(oldState ==6 && num==6) // see double quot close ... no="1["]
	{
		return 9;
	}
	else if(oldState ==4 && num==12) //see single quot open ... value=[']2'
	{
		return 7;
	}
	else if(oldState ==7 && num==0) // see value 
	{
		// ... value='[2]'...
		return 8;
	}
	else if(oldState ==8 && num==12) // see single quot close
	{
		// ... value='2[']
		return 9;
	}
	else if( oldState ==9 && num ==0) // next attribute
	{
		 // no="1" [value]='2'
		return 3;
	}
	else if( (oldState ==9||oldState==2) && num ==4) // see  end sysbol'/'
	{
		// <item no='1' [/]>
		return 13;
	}
	else if( oldState == 13 && num ==3 )// see close >
	{
		// <item no='1' /[>]
		return 17;
	}
	else if( (oldState ==9||oldState ==2) && num ==3 ) // see  close >
	{
		//addData(&(tXML->state),10); // <root no="1" value='2' [>]
		return 10;
	}
	else if( oldState ==10 && num ==0) // see value of tage
	{
		//addData(&(tXML->state),11);//<root ..>[123]</...	
		return 11;
	}
	else if( oldState ==11 && num ==2) // see open of close  tag
	{
//		addData(&(tXML->state),12); // <root..>aa[<]/
		return 12;
	}
	else if( (oldState==18||oldState==12) && num ==4) //see end sys
	{
	//	addData(&(tXML->state),15);// <root..>aa<[/]>
		return 15;
	}
	else if(oldState ==15 && num ==0) //see name tag close
	{
//		addData(&(tXML->state),16); // <root>aa</[root]>
		return 16;
	}	
	else if(oldState ==16 && num ==3) //<root>aaa</root[>]
	{
	//	addData(&(tXML->state),17);
		return 17;
	}	
	else if( (oldState ==10) && num == 2) // see close tag or new tag
	{
	//	addData(&(tXML->state),18); //<root..>[<]
		return 18;
	}
	else if( oldState ==17 && num==2) // <item /> [<]
	{
		return 14;
	}
	else if(oldState ==18 && num ==0)//sse <root..><[feed]
	{
//		addData(&(tXML->state),2);
		return 2;
	}
	else
	{
	//	addData(&(tXML->state),-1);
		printf("num ---------------:%d %d\n",oldState,num);
		return -1;
	}
}
//element getLastDataCharList(charList* list);
int addData2Attrb(treeXML *root,elementXML *rootEle)
{
	if(root == NULL || rootEle==NULL)
	{	
		return 0;
	}		
	else if(rootEle->numAttrb <= 0)
	{	
		return 0;
		//do nothing
	}
	else
	{
		//do nothing
	}
	int index=0,index2=0;
	index = new_attrbXML(rootEle);
	if(index == 0)
	{
		return 0;
	}
	else
	{
		//do nothing
	}
	// keep   [/]> or <root no="2" ... [>]
	char oldState = getLastDataCharList(&(root->state));
	vector_char oldInput = getLastValueVchar(&(root->stackParser));
		popCharList(&(root->state));
		deleteLastNodeVchar(&(root->stackParser));
	// end kepp [/].........
	//for(index=0;index<rootEle->numAttrb;index++)
	index = rootEle->numAttrb;
	while(index--)
	{
		//pop " or '
		deleteLastNodeVchar(&(root->stackParser));
		popCharList(&(root->state));

	rootEle->attrb[index].value = getLastValueVchar(&(root->stackParser));
		
		for(index2 =0 ;index2<3;index2++)
		{	// pop   = "(') value
			deleteLastNodeVchar(&(root->stackParser));
			popCharList(&(root->state));
		}
	rootEle->attrb[index].name = getLastValueVchar(&(root->stackParser));
		//pop name 
		deleteLastNodeVchar(&(root->stackParser));
		popCharList(&(root->state));
	}
	addData(&(root->state),oldState);
	addNodeVchar(&(root->stackParser),&oldInput);
	delete_vector_char(&oldInput);
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
		//do nothing
	}

	*eleXML = (elementXML*)malloc(sizeof(elementXML));
		printOpt(__LINE__-1,"new_elementXML","simReadXML.c",(void*)*eleXML,0);
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
	else if(eleXML->numAttrb <=0)
	{
		return 0;
	}
	else
	{
		//do nothing
	}
	int index =0;
	eleXML->attrb =(attrbXML*)malloc((eleXML->numAttrb)*sizeof(attrbXML));
		printOpt(__LINE__-1,"new_attrbXML","simReadXML.c",(void*)eleXML->attrb,0);	
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
		//do nothing
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
			//do nothing
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
	printCharList(&(root->state),-1);
	printEleXML(root->root);
}
void printEleXML(elementXML *root)
{
	printf("name:");
	print_vector_char(&(root->name),11);
	printf("value:");
	print_vector_char(&(root->value),11);
	int index =0;
	elementXML *p = root->next;
	printf("	Attrb :\n");
	for(index =0 ;index < root->numAttrb;index++)
	{
		printAttrbXML(&(root->attrb[index]));
	}
	printf("--------------------------------------------\n");
	for(p = root->firstChild;p!=NULL;p = p->next)
	{
		printf("next: %p\n",p);
		printEleXML(p);
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
		//do nothing	
	}
	printf("name:");
	print_vector_char(&(root->name),11);
	printf("value:");
	print_vector_char(&(root->value),11);
}
void checkCommentXML(treeXML *tXML,char opt) 
// opt 0 =  newState == 1||newState==12||newState ==14 ||newState==18
// opt 1 otherwise
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
	int fact1;
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
		//do nothing
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
			//do nothing
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
		//do nothing
	}
	return root->root;
}
elementXML* getfirstChildXML(elementXML* root,const char *str)
{
    if(root == NULL)
    {
        return NULL;
    }
    else
    {
        //do nothing
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
int compNameElemetVsCstr(vector_char *a,const char *str)
{
    int index =0;
    if(a == NULL || str==NULL)
    {
        return 0;
    }
    else
    {
        //do nothing
    }
    for(index =0;index <a->lenght && str[index] !='\0';index++)
    {
        if(a->data[index] != str[index])
        {
            return 0;
        }
        else
        {
            //do nothing
        }
    }
    return 1;
}
char specialCharCheck(char in)
{
	return (char)((in =='.')||(in=='_')||(in=='-'));
}
