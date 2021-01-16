#include <stdio.h>
#include "simMatChar.h"
#include "simReadXML.h"
#include "simStringList.h"
#include "listChar.h"
#define  FILENAME "xmlSample/ds_uci_Iris.xml"
#define  FILEXML "fileXML.dat"

int inputTags(simStrList *strList,elementXML *root);
int initialWork(treeXML *tXML,const char* filename,int argc,char** argv);
void fileMgr(treeXML *tXML,const char* filename,int argc,char** argv);
int main(int argc,char **argv)
{
	treeXML tXML;
        simStrList strList;
	elementXML *rootXML = NULL;
        initialSimStrList(&strList);
        initialWork(&tXML,FILEXML,argc,argv);
	rootXML = getRootElementXML(&tXML);
        inputTags(&strList,rootXML);
//	rootEve = getfirstChildXML(rootXML,"body");
//	printEleXML(rootEve);
	printTreeXML(&tXML);
        destructorSimStrList(&strList);
	destructorTreeXML(&tXML);
	return 0;
}
int inputTags(simStrList *strList,elementXML *root)
{
        int res = 0;
        const char* ch1 = "back";
        const char* ch2 = "come";
        double valueD = 0.0;
        int valueI = 0;
        vector_char vdata = new_vector_char(0);
        if(strList != NULL && root != NULL)
        {
            res = 1;
            res &= addNodeSimStrListFromCStr(strList,"jui");
            res &= addNodeSimStrListFromCStr(strList,"book");
            res &= addNodeSimStrListFromCStr(strList,"OK");
            res &= addNodeSimStrListFromCStr(strList,"NOT_OK");
            res &= addNodeSimStrListFromCStr(strList,"EVE");
            res &= addNodeSimStrListFromCStr(strList,"YOU");
        }
        else
        {
            /* do nothing */
        }
        if(res == 1)
        {
            valueD = getDoubleValueOfAttrbDeepFromXMLEle(root,strList,ch1,"0");
            valueI = getIntValueOfAttrbDeepFromXMLEle(root,strList,ch2,"0");
            vdata = getValueDeepFirstChildXML(root,strList,"");
            printf("--value: %lf \n",valueD);
            printf("--value: %d \n",valueI);
            print_vector_char(&vdata,11);
        }
        else
        {
            /* do nothing */
        }
        delete_vector_char(&vdata);
        return res;
}
void fileMgr(treeXML *tXML,const char* filename,int argc,char** argv)
{
	FILE *fp = NULL;
        char *name = NULL;
        int fsize = 0;
	fp = fopen(filename,"r");
        if(fp != NULL)
	{
            fseek(fp,0,SEEK_END);
            fsize = ftell(fp);
            rewind(fp);
            name = (char*)malloc(fsize*sizeof(char));
            if(name != NULL)
            {
               fread(name,1,fsize,fp);
	       name[fsize-1] = '\0';
	       printf("file name:%s\n",name);
               setReadFile(tXML,name);
               free(name);
               name = NULL;
            }
            else
            {
               setReadFile(tXML,FILENAME);
            }
           
	}
	else if(argc == 1)
	{
		setReadFile(tXML,FILENAME);
	}
	else
	{
		setReadFile(tXML,argv[1]);
	}
	if(fp != NULL)
	{
	    fclose(fp);
        }
	else
        {
	    /* do nothing */
        }
}
int initialWork(treeXML *tXML,const char* filename,int argc,char** argv)
{
    int work = 0;
    if(tXML != NULL && filename != NULL && argv != NULL)
    {
	initial_treeXML(tXML);
        fileMgr(tXML,FILEXML,argc,argv);
	createTreeXML(tXML);
        work =1;
    }
    else
    {
        /* do nothing */
    }
    return work;
}
/*
// 1 true 0 false
char alphabetCheck(char in);
char digiCheck(char in);
char alphabetAndDigiCheck(char in);
// 2 : '<' 3: '>' 4:'/' 5:'=' 6:'\"' 7:' ' 8:'\n' 9: '\t' 10: '\0' 11: '\\'
char reserveWord(char in);
int  findWord(char* in);
void printReserveWord(char in);
*/
