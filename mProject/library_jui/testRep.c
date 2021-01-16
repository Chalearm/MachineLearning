#include <stdio.h>
#include <stdlib.h>
#include "replaceWord.h"

int main(int argc,char** argv)
{
	char *buff = "I like a cat in a farm when a horse goes a house that it is a book";
	char *old ="s";
	char *new1 ="z";
	char *buff2 = replaceNWord(buff,old,new1,-1);
	char *buff3 = NULL;
	char *buff4 = NULL;
	printf("%s \n",buff);
	printf("%s \n",buff2);
	buff3 = replaceNWord(buff2,"a ","the ",-1);
	printf("%s \n",buff3);
	buff4 = replaceNWord(buff3," ","",-1);
	printf("%s \n",buff4);
	free(buff2);
	free(buff3);
	free(buff4);
	return 0;
}
/*
void constructorReplaceW(replaceW* rel);
void destructorReplaceW(replaceW* rel);
int  countWordInBuff(const char *buff,const char *word);
void setAttrb(replaceW *rel,const char* old,const char* nw,int count);
void makeEmptyReplaceW(replaceW *rel);
char* replaceAll(const char *buffer,const char *old,const char *nw);
char* replaceNWord(const char *buffer,const char *old,const char *nw,int count);
*/
