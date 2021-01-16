#include "fileInpHandler.h"
#include "stdio.h"
#include "debug.h"
/*
//FIH : file Input handler
struct fileInpHand
{
	FILE* 	fp;
	char* 	filename;
	vector_char buffer;
};
*/

void constructorFIH(fileInpHand *FIH)
{	
	if(FIH == NULL)
	{
		return;
	}
	else
	{
		FIH->fp = NULL;
		FIH->filename = NULL;
		FIH->buffer = NULL;
		FIH->sizeBuff= 0;
	}
}// end void constructorFIH(fileInpHand *FIH)
void clearFileNameFIH(fileInpHand *FIH)
{
	if(FIH->filename != NULL)
	{
	    printOpt(__LINE__+1,"clearFileNameFIH","fileInpHandler.c",(void*)FIH->filename,1);
		free(FIH->filename);
		FIH->filename = NULL;
	}
	else
	{
		//do nothing
	}
}// void clearFileNameFIH(fileInpHand *FIH)
void clearFilePointerFIH(fileInpHand *FIH)
{
	if(FIH->fp != NULL)
	{
		fclose(FIH->fp);
		FIH->fp = NULL;
	}
	else
	{
		//do nothing
	}
}// void clearFilePointerFIH(fileInpHand *FIH)
void clearBufferFIH(fileInpHand *FIH)
{
	if(FIH->buffer != NULL)
	{
printOpt(__LINE__+1,"clearBufferFIH","fileInpHandler.c",(void*)FIH->buffer,1);
		free(FIH->buffer);
		FIH->buffer = NULL;
		FIH->sizeBuff=0;
	}
	else
	{
	}
}// void clearBufferFIH(fileInpHand *FIH)
void clearAllMemberFIH(fileInpHand *FIH)
{
	clearFileNameFIH(FIH);
	clearBufferFIH(FIH);
	clearFilePointerFIH(FIH);
}// void clearAllMemberFIH(fileInpHand *FIH)
void destructorFIH(fileInpHand *FIH)
{
	if(FIH != NULL)
	{
		clearAllMemberFIH(FIH);
	}
	else
	{
		//do nothing
	}
		
}// void destructorFIH(fileInpHand *FIH)
void setFileNameFIH(fileInpHand *FIH,const char* str)
{
	int numStr =0;
	if(FIH != NULL && str != NULL)
	{
		clearFileNameFIH(FIH);
		numStr = strlen(str);
		FIH->filename = (char*)malloc((numStr+1)*sizeof(char));
printOpt(__LINE__-1,"setFileNameFIH","fileInpHandler.c",(void*)FIH->filename,0);
		strcpy(FIH->filename,str);
		
		
	}
	else
	{	
		//do nothing
	}
}
int  countNumAttrbFIH(fileInpHand *FIH,char delimiter)// '\0' count on a line
{
	int count = 0;
	int index;
	if(FIH->sizeBuff ==0 || delimiter =='\0' || delimiter =='\n')
	{
		return count;
	}
	else
	{
		updateBuffFIH(FIH);
		for(index =0;FIH->buffer[index] != '\0';index++)
		{
			if(FIH->buffer[index] == '\n')
			{
				return count;
			}
			else if(FIH->buffer[index] == delimiter)
			{
				count++;
			}
			else
			{
				//do nothing
			}
		}
	}
	return count;
}//end int  countNumAttrbFIH(fileInpHand *FIH,char delimiter)
void openFileToReadFIH(fileInpHand *FIH)
{
	clearFilePointerFIH(FIH);
	FIH->fp = fopen(FIH->filename,"r");
	if(FIH->fp == NULL)
	{
		printf("cannot open file\n");
	}
	else
	{
		//do nothing
	}
	
}//end void openFileToReadFIH(fileInpHand *FIH)
	
int  countNumInputFIH(fileInpHand *FIH,char delimiter)
{
	int count =0;
	int index =0;
	char *p   = FIH->buffer;
	if(FIH->sizeBuff ==0)
	{
		return 0;
	}
	else
	{
	   fseek(FIH->fp,0,SEEK_SET);
	   while(fgets(FIH->buffer,FIH->sizeBuff,FIH->fp) != 0)
	   {
		if(delimiter == '\0' || delimiter ==0)
		{
			count++;
			continue;
		}	
		else
		{
			//do nothing
		}
		for(index=0;p[index]!='\0';index++)
		{
			if(p[index] == delimiter)
			{
			 	count++;
			}
			else
			{
				//do nothing
			}
		}
	   }
	}
	fseek(FIH->fp,0,SEEK_SET);
	return count;
}
void initialFIH(fileInpHand *FIH,const char* filename,int sizeBuff)
{
	FIH->buffer      = (char*)malloc(sizeBuff*sizeof(char));
printOpt(__LINE__-1,"initialFIH","fileInpHandler.c",(void*)FIH->buffer,0);
	FIH->sizeBuff    = sizeBuff;
	setFileNameFIH(FIH,filename);
	openFileToReadFIH(FIH);
}
void updateBuffFIH(fileInpHand *FIH)
{
	fgets(FIH->buffer,FIH->sizeBuff,FIH->fp);
}
	
