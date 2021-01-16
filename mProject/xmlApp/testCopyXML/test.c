#include <stdio.h>
#include <string.h>
#include "simStringList.h"
#include "simReadXML.h"
#include "simWriteXML.h"
#define STRBUFFER 60
#define DEF_WORK 1
#define DEF_FAILED 0
#define DEFAULTXML  "source/xml1.xml"
#define DEFAULTWRITEFILE "source/xmlWrite.xml"
#define DEFAULTFILE "obj.txt"
#define NUMNODE_REQ 2 /* readfile and write file */
int copyNewFile(int argc,char** argv,int isPrint);
int initialAll(int argc,char** argv,treeXML* readRoot,treeXML* writeRoot);
int initialRootXMLs(treeXML* readRoot,treeXML* writeRoot);
int getListFile(simStrList* listFile,const char* str);
void destructAllTreeXML(treeXML* readRoot,treeXML* writeRoot);
/* ./test nameRead nameWrite*/
int main(int argc,char** argv)
{
    int res = DEF_WORK;
    res =copyNewFile(argc,argv,0);
    return res;
}

int copyNewFile(int argc,char** argv,int isPrint)
{
    int res = DEF_FAILED;
    treeXML xmlRead;
    treeXML xmlWrite;
    res = initialAll(argc,argv,&xmlRead,&xmlWrite);
    if(res == DEF_WORK)
    {
        createTreeXML(&xmlRead);
        res = setRootElement(&xmlWrite,xmlRead.root);
        res &= createXMLFile(&xmlWrite);
    }
    else
    {
        /* do nothing */
    }
    if(isPrint == 1 && res == DEF_WORK)
    {
        printTreeXML(&xmlWrite);
    }
    else
    {
        /* do nothing */
    }
    destructAllTreeXML(&xmlRead,&xmlWrite);
    return res;
}

int initialAll(int argc,char** argv,treeXML* readRoot,treeXML* writeRoot)
{
    int res =DEF_WORK;
    int numNode = 0;
    simString *dummyStr = NULL;
    simStrList listFile;
    res  =  initialSimStrList(&listFile);
    res &= initialRootXMLs(readRoot,writeRoot);
    if(res == DEF_WORK)
    {
        if(argc ==3 && argv != NULL)
        {
            res  = setReadFile(readRoot,argv[1]);
            res &= setWriteFileTreeXML(writeRoot,argv[2]);
        }
        else
        {
            res = getListFile(&listFile,DEFAULTFILE);
            numNode = getNumNodeSimStrList(&listFile);
            if(res == DEF_WORK && numNode ==NUMNODE_REQ)
            { 
                dummyStr = getnthNodeSimStrList(&listFile,0);
                res  = setReadFile(readRoot,dummyStr->data);
                dummyStr = getnthNodeSimStrList(&listFile,1);
                res &= setWriteFileTreeXML(writeRoot,dummyStr->data);
            }
            else
            {
                /* do nothing */
            }
        }
    }
    else
    {
        res= DEF_FAILED;
    }
    destructorSimStrList(&listFile);
    return res;
}
int initialRootXMLs(treeXML* readRoot,treeXML* writeRoot)
{
    int res = DEF_FAILED;
    if(readRoot != NULL && writeRoot != NULL)
    {
        res  = initial_treeXML(readRoot);
        res &= initial_treeXML(writeRoot);
    }
    else
    {
        /* do nothing */
    }
    return res;
}
void destructAllTreeXML(treeXML* readRoot,treeXML* writeRoot)
{
    if(readRoot != NULL)
    {
        destructorTreeXML(readRoot);
    }
    else
    {
        /* do nothing */
    }
    if(writeRoot != NULL)
    {
        destructorTreeXML(writeRoot);
    }
    else
    {
        /* do nothing */
    }
}
int getListFile(simStrList* listFile,const char* str)
{
    int res = DEF_WORK;
    char buff[STRBUFFER];
    FILE *fp = NULL;
    fp = fopen(str,"r");
    if(fp != NULL && listFile != NULL)
    {
        res = (int)(fgets(buff,STRBUFFER,fp) !=0);
        buff[strlen(buff)-1] ='\0'; /* cut new line */
        res &= addNodeSimStrListFromCStr(listFile,buff);
        res &= (int)(fgets(buff,STRBUFFER,fp) !=0);
        buff[strlen(buff)-1] ='\0'; /* cut new line */
        res &= addNodeSimStrListFromCStr(listFile,buff);
        fclose(fp);
        fp = NULL;
    }
    else
    {
        res = DEF_FAILED;
    }
    return res;
}
