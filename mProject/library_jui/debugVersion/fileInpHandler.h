#ifndef FILEINPHANDLER_H__
#define FILEINPHANDLER_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//FIH : file Input handler
struct fileInpHand
{
	FILE* 	fp;
	char* 	filename;
	char*   buffer;
	int     sizeBuff;
};
typedef struct fileInpHand fileInpHand;
void openFileToReadFIH(fileInpHand *FIH);
void updateBuffFIH(fileInpHand *FIH);
void constructorFIH(fileInpHand *FIH);
void initialFIH(fileInpHand *FIH,const char* filename,int sizeBuff);
void clearFileNameFIH(fileInpHand *FIH);
void clearFilePointerFIH(fileInpHand *FIH);
void clearBufferFIH(fileInpHand *FIH);
void clearAllMemberFIH(fileInpHand *FIH);
void destructorFIH(fileInpHand *FIH);
void setFileNameFIH(fileInpHand *FIH,const char* str);
int  countNumAttrbFIH(fileInpHand *FIH,char delimiter);//only data in a line
int  countNumInputFIH(fileInpHand *FIH,char delimiter);

#endif //FILEINPHANDLER_H__
