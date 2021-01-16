#include "replaceWord.h"
#include <stdlib.h>
#include <string.h>
#include  <stdio.h>

/*
struct replaceW
{
	char *oldWord;
	char *newWord;
	int  numReplace;
};
typedef struct replaceW replaceW;
*/
void constructorReplaceW(replaceW* rel)
{
	rel->oldWord = NULL;
	rel->newWord = NULL;
	rel->numReplace   = 0;
}
void destructorReplaceW(replaceW* rel)
{
	makeEmptyReplaceW(rel);
}
void makeEmptyReplaceW(replaceW *rel)
{
	if(rel == NULL)
	{
		return;
	}
	else
	{
		/*do nothing*/
	}
	if(rel->oldWord != NULL)
	{
		free(rel->oldWord);
		rel->oldWord = NULL;
	}
	else
	{
		/* do nothing */
	}
	if(rel->newWord != NULL)
	{
		free(rel->newWord);
		rel->newWord = NULL;
	}
	else
	{
		/* do nothing */
	}
	rel->numReplace = 0;
}
void setAttrb(replaceW *rel,const char* old,const char* nw,int count)
{
	int count1 =0,count2=0;
	makeEmptyReplaceW(rel);
	if(rel == NULL)
	{
		return;
	}
	else
	{
		/* do nothing */
	}
	count1 = strlen(old);
	count2 = strlen(nw);
	rel->oldWord = (char*)malloc(count1*sizeof(char));
	rel->newWord = (char*)malloc(count2*sizeof(char));
	strcpy(rel->oldWord,old);
	strcpy(rel->newWord,nw);
	rel->numReplace = count;
	
	if(rel->numReplace < -1)
	{
		rel->numReplace = -1;
	}
	else
	{
		/* do nothing */
	}
}
char* replaceAll(const char *buffer,const char *old,const char *nw)
{
	return replaceNWord(buffer,old,nw,-1);//-1 is all words;
}
char* replaceNWord(const char *buffer,const char *old,const char *nw,int count)
{
	int numOldWord = 0;
	int firstPos =0;
	int index =0,index2=0,index3=0;
	int numRep = 0;
	char *newBuff  = NULL;
	int sizeOldBuff= 0;
	int sizeOldWord= 0;
	int sizeNewBuff= 0;
	int sizeNewWord= 0;
	char fact1     = 0;
	if(buffer == NULL || old == NULL || nw == NULL || count ==0)
	{
		return NULL;
	}
	else
	{
		/*do nothing */
	}
	sizeOldWord= strlen(old);
	sizeNewWord= strlen(nw);
	sizeOldBuff= strlen(buffer);
	numOldWord = countWordInBuff(buffer,old);
	if(count >0 && count <= numOldWord)
	{
		numOldWord = count;
	}
	else
	{
		/* do nothing*/
	}
	
	if(numOldWord == 0)
	{
		return 0;
	}
	else
	{
		/*do nothing*/
	}
	sizeNewBuff= 1+sizeOldBuff +(sizeNewWord-sizeOldWord)*numOldWord;
	newBuff = (char*)malloc(sizeof(char)*sizeNewBuff);
	if(newBuff == NULL)
	{
		return NULL;
	}
	else
	{
		/*do nothing*/	
	}
	for(index=0;index <sizeOldBuff;index++)
	{
		fact1 = (numRep <count) || count <0;
		if(buffer[index] ==old[index2] && index2 < sizeOldWord &&fact1)
		{
			if(index2 == 0 && sizeOldWord > 1)
			{
				firstPos = index;
			}
			else if(index2+1 == sizeOldWord) //replace
			{
				for(index2=0;index2<sizeNewWord;index2++)
				{
					newBuff[index3++] =nw[index2];	
				}
				numRep++;
			}
			else
			{
				/*do nothing*/
			}
			index2++;
		}
		else if(index2 <sizeOldWord && index2 >0)
		{	
			index = firstPos;
			index2   = 0;
			newBuff[index3++] = buffer[index];
		}
		else
		{
			newBuff[index3++] = buffer[index];
			index2=0;
		}
	} 
	newBuff[index3] = '\0';
	return newBuff;
}
int countWordInBuff(const char *buff,const char *word)
{
	int count =0;
	int index = 0;
	int wordLength = 0;
	int buffLength = 0;
	int index2= 0;
	if(buff == NULL || word == NULL)
	{
		return 0;
	}
	else
	{
		/* do nothing */
	}
	buffLength = strlen(buff);
	wordLength = strlen(word);
	for(index =0;index <= buffLength;index++)
	{
		if(buff[index] == word[index2])
		{
			index2++;
		}
		else
		{
			index2 =0;
		}
		if(index2 == wordLength)
		{
			count++;
			index2 =0;
		}
		else
		{
			/*do nothing*/
		}
	}
	return count;
}
int findNthFirstIndexOfWord(const char *buff,const char *word,int indexN)
{
	int count =0;
	int index = 0;
	int wordLength = 0;
	int buffLength = 0;
	int index2= 0;
	if(buff == NULL || word == NULL)
	{
		return 0;
	}
	else
	{
		/* do nothing */
	}
	buffLength = strlen(buff);
	wordLength = strlen(word);
	for(index =0;index < buffLength;index++)
	{
		if(buff[index] == word[index2])
		{
			index2++;
		}
		else
		{
			index2 =0;
		}
		if(index2 == wordLength)
		{
			if(count == indexN)
			{
			      return 1+index-wordLength;	
			}
			else
			{
			      count++;
		              index2 =0;
			}
		}
		else
		{
			/*do nothing*/
		}
	}
	return -1;
}
