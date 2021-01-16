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
     
    int m_lengthOld;
    int m_lengthNew;
};
typedef struct replaceW replaceW;
*/
void constructorReplaceW(replaceW* rel)
{
    rel->oldWord = NULL;
    rel->newWord = NULL;
    rel->numReplace   = 0;
    rel->m_lengthOld   = 0;
    rel->m_lengthNew   = 0;

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
	rel->m_lengthOld = 0;
	rel->m_lengthNew = 0;
}
void setAttrb(replaceW *rel,const char* old,const char* nw,int count)
{ 
    int index=0;
    char *str1=NULL;
    makeEmptyReplaceW(rel);
    if(rel == NULL)
    {
        return;
    }
    else
    {
        /* do nothing */
    } 
    rel->m_lengthOld =0;
    rel->m_lengthNew =0;
    for(index=0;old[index]!='\0';index++)
    {
        rel->m_lengthOld++;
    }
    for(index=0;nw[index]!='\0';index++)
    {
        rel->m_lengthNew++;
    }
    rel->oldWord = (char*)malloc((rel->m_lengthOld)*sizeof(char));
    rel->newWord = (char*)malloc((rel->m_lengthNew)*sizeof(char));
    str1 =  rel->oldWord;
    for(index=0;index<rel->m_lengthOld;index++)
    {
        str1[index] = old[index];
    }
    str1 =  rel->newWord;
    for(index=0;index<rel->m_lengthNew;index++)
    {
        str1[index] = old[index];
    }
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
    return replaceNWord(buffer,old,nw,-1);/* -1 is all words; */
}
void replaceAllWithStatBuff(const char *input,char *newBuff,const char *old,const char *nw)
{
    replaceNWordWithStatBuff(input,newBuff,old,nw,-1);
}

void replaceNWordWithStatBuffByRepW(const char *input,char *newBuff,replaceW* rel)
{
    int firstPos =0;
    int index =0,index2=0,index3=0;
    int numRep = 0;
    int sizeOldBuff= 0;
    int sizeOldWord= 0;
    int sizeNewWord= 0;
    int count =0;
    char *old =NULL;
    char *nw =NULL;
    char fact1     = 0;
    if(input == NULL || (rel==NULL)||(newBuff==NULL))
    {
        return;
    }
    else
    {
        /*do nothing */
    }
    old = rel->oldWord;
    nw = rel->newWord;
    count = rel->numReplace;
    sizeOldWord= rel->m_lengthOld;
    sizeNewWord= rel->m_lengthNew;
    sizeOldBuff= strlen(input);

    for(index=0;index <sizeOldBuff;index++)
    {
        fact1 = (numRep <count) || count <0;
        if(input[index] ==old[index2] && index2 < sizeOldWord &&fact1)
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
            newBuff[index3++] = input[index];
        }
        else
        {
            newBuff[index3++] = input[index];
            index2=0;
        }
    } 
    newBuff[index3] = '\0';
}
void replaceNWordWithStatBuff(const char *input,char *newBuff,const char *old,const char *nw,int count)
{
    int firstPos =0;
    int index =0,index2=0,index3=0;
    int numRep = 0;
    int sizeOldBuff= 0;
    int sizeOldWord= 0;
    int sizeNewWord= 0;
    char fact1     = 0;
    if(input == NULL || old == NULL || nw == NULL || count ==0 ||(newBuff==NULL))
    {
        return;
    }
    else
    {
        /*do nothing */
    }
    sizeOldWord= strlen(old);
    sizeNewWord= strlen(nw);
    sizeOldBuff= strlen(input);

    for(index=0;index <sizeOldBuff;index++)
    {
        fact1 = (numRep <count) || count <0;
        if(input[index] ==old[index2] && index2 < sizeOldWord &&fact1)
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
            newBuff[index3++] = input[index];
        }
        else
        {
            newBuff[index3++] = input[index];
            index2=0;
        }
    } 
    newBuff[index3] = '\0';
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
