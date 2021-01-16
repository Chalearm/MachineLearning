/*****************************************************************************/
/*	Name          : chalearm saelim                                          */
/*	E-mail        : chalearm33@hotmail.com, chalearm90@gmail.com             */
/*	Date-create   : 18 Aug 2014 23:29 UTC+7 Thailand                         */
/*	Purpose       : To Show how to use tagXMLAdd and how to copy file xml    */
/*                                                                           */
/*****************************************************************************/
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
int copy2TreeXML(int argc,char** argv,treeXML* xmlWrite,int isPrint);
int initialAll(int argc,char** argv,treeXML* readRoot,treeXML* writeRoot);
int initialRootXMLs(treeXML* readRoot,treeXML* writeRoot);
int getListFile(simStrList* listFile,const char* str);
void printAPartOfRootByTagXMLAdd(treeXML* writeRoot);
void editAPartOfRootByTagXMLAdd(treeXML* writeRoot);

/* ./test nameRead nameWrite*/
int main(int argc,char** argv)
{
    int res = DEF_WORK;
    treeXML xmlWrite;
    res =copy2TreeXML(argc,argv,&xmlWrite,0);
    if(res ==DEF_WORK)
    {
        /*printAPartOfRootByTagXMLAdd(&xmlWrite);*/
        /* made file is here */
        editAPartOfRootByTagXMLAdd(&xmlWrite);
       /* printTreeXML(&xmlWrite);*/
        res = createXMLFile(&xmlWrite);
    }
    else
    {
        /* do nothing */
    }
    destructorTreeXML(&xmlWrite);
    return res;
}

void editAPartOfRootByTagXMLAdd(treeXML* writeRoot)
{
    int res = DEF_FAILED;
    tagXMLAdd getterEle;
    initialTagXMLAdd(&getterEle);

    if(writeRoot != NULL)
    {
        res  = addTagXMLvalueWithCStr(&getterEle,"ROOT",0);
        res &= addTagXMLvalueWithCStr(&getterEle,"BODY",0);
        res &= addTagXMLvalueWithCStr(&getterEle,"DIV",2);
        res &= addTagXMLvalueWithCStr(&getterEle,"SELECT",0);
        res &= addTagXMLvalueWithCStr(&getterEle,"MAIN_ELE",0);
        res &= addTagXMLvalueWithCStr(&getterEle,"SUB_ELEMENT",0);
        res &= addTagXMLvalueWithCStr(&getterEle,"JUI",1); 
        if(res == 1)
        {
            changeNameElementWithCStr(writeRoot,&getterEle,"JUICE");
        }
        else
        {
            /* do nothing */
        }
        destructTagXMLAdd(&getterEle);

        
        initialTagXMLAdd(&getterEle);
        res  = addTagXMLvalueWithCStr(&getterEle,"ROOT",0);
        res &= addTagXMLvalueWithCStr(&getterEle,"BODY",0);
        res &= addTagXMLvalueWithCStr(&getterEle,"DIV",2);
        res &= addTagXMLvalueWithCStr(&getterEle,"A",0);

        if(res == 1)
        {
			/* change A tag to ADDRESS tag */
            changeNameElementWithCStr(writeRoot,&getterEle,"ADDRESS");
            res = removeTagXMLValue(&getterEle,getNumOfTagXMLAdd(&getterEle)-1);
            res &= addTagXMLvalueWithCStr(&getterEle,"ADDRESS",0);
            if(res == 1)
            {
                changeValueElementWithCStr(writeRoot,&getterEle,"www.facebook.com");
            }
            else
            {
                /* do nothing */
            }
			
			/* change SELECT 2 tag to CHOOSE tag*/
            res = removeTagXMLValue(&getterEle,getNumOfTagXMLAdd(&getterEle)-1);
            res &= addTagXMLvalueWithCStr(&getterEle,"SELECT",1);	
			if(res ==1)
			{
				changeNameElementWithCStr(writeRoot,&getterEle,"CHOOSE");
				res = removeTagXMLValue(&getterEle,getNumOfTagXMLAdd(&getterEle)-1);
				res &= addTagXMLvalueWithCStr(&getterEle,"CHOOSE",0);
				if(res ==1)
				{
					changeTypeElement(writeRoot,&getterEle,0);
                    res =addAttrb2TheElementWithDetail(writeRoot,&getterEle,"OK_NA","120.5",1);
                    res &=addAttrb2TheElementWithDetail(writeRoot,&getterEle,"PermittedSp","7.2345",1);
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
            /* delete attribute name is "live" */
            if(res ==1)
            {
                res = deleteAttrbInTheElement(writeRoot,&getterEle,"live");
            }
            else
            {
                /* do nothing */
            }
            /* change the Permitted speed to Target speed */
            if(res ==1)
            {
                res = changeNameAttrbOfTheElementWithCStr(writeRoot,&getterEle,"PermittedSp","TargetSp");
            }
            else
            {
                /* do nothing */
            }
            /* change the value of OK_NA  to 192 */
            if(res ==1)
            {
                res = changeValueAttrbOfTheElementWithCstr(writeRoot,&getterEle,"OK_NA","192");
            }
            else
            {
                /* do nothing */
            }
            /* change the type of opt  to double quot */
            if(res ==1)
            {
                res = changeTypeAttrbOfTheElementWithCStr(writeRoot,&getterEle,"opt",0);
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
		
		
        destructTagXMLAdd(&getterEle);
    }
    else
    {
        /* do nothing */
    }
    destructTagXMLAdd(&getterEle);
}

int copy2TreeXML(int argc,char** argv,treeXML* xmlWrite,int isPrint)
{
    int res = DEF_FAILED;
    treeXML xmlRead;

    res = initialAll(argc,argv,&xmlRead,xmlWrite);
    if(res == DEF_WORK)
    {
        createTreeXML(&xmlRead);
        res = setRootElement(xmlWrite,xmlRead.root);
    }
    else
    {
        /* do nothing */
    }
    if(isPrint == 1 && res == DEF_WORK)
    {
        printTreeXML(xmlWrite);
    }
    else
    {
        /* do nothing */
    }
    destructorTreeXML(&xmlRead);
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
void printAPartOfRootByTagXMLAdd(treeXML* writeRoot)
{
    int res = DEF_FAILED;
    tagXMLAdd getterEle;
    elementXML *dummyEle = NULL;
    /* print head */
    initialTagXMLAdd(&getterEle);
    res  = addTagXMLvalueWithCStr(&getterEle,"ROOT",0);
    res &= addTagXMLvalueWithCStr(&getterEle,"HEAD",0);	
    if(res == DEF_WORK)
    {
        dummyEle = getAnElementXML(writeRoot,&getterEle);
        /*printEleXML(dummyEle); */
    }
    else
    {
        /* do nothing */
    }
    destructTagXMLAdd(&getterEle);


    /* print BODY -->DIV2--> SELECT-->MAIN_ELE-->SUB_ELEMENT-->JUI1 */
    initialTagXMLAdd(&getterEle);

    res  = addTagXMLvalueWithCStr(&getterEle,"ROOT",0);
    res &= addTagXMLvalueWithCStr(&getterEle,"BODY",0);
    res &= addTagXMLvalueWithCStr(&getterEle,"DIV",2);
    res &= addTagXMLvalueWithCStr(&getterEle,"SELECT",0);
    res &= addTagXMLvalueWithCStr(&getterEle,"MAIN_ELE",0);
    res &= addTagXMLvalueWithCStr(&getterEle,"SUB_ELEMENT",0);
    res &= addTagXMLvalueWithCStr(&getterEle,"JUI",1);
    if(res == DEF_WORK)
    {
        dummyEle = getAnElementXML(writeRoot,&getterEle);
        printEleXML(dummyEle);
    }
    else
    {
        /* do nothing */
    }
    destructTagXMLAdd(&getterEle);
}
