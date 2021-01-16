#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "simReadXML.h"
#include "eleXMLNodeList.h"
#define  FILENAME "xmlSample/ds_uci_Iris.xml"
#define  FILEXML "fileXML.dat"
#define  A_TAG "FILE_NAME"
#define BUFF_SIZE 50
void setReadXMLFile(treeXML* root);
char* getTagFromXMLEle();
int main(int argc,char **argv)
{
    treeXML tXML;
    listElement listXML;
    elementXML *rootXML = NULL;
    char *str = NULL;
    constructorListXMLEle(&listXML);
    initial_treeXML(&tXML);
    setReadXMLFile(&tXML);
    createTreeXML(&tXML);
    rootXML = getRootElementXML(&tXML);
    str =  getTagFromXMLEle();
    generateXMLEleList(&listXML,rootXML,str);
    printXMLList(&listXML);
	printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    printTreeXML(&tXML);
    destructListXMLEle(&listXML);
    destructorTreeXML(&tXML);
    if(str!= NULL)
    {
        free(str);
        str = NULL;
    }
    else
    {
        /* do nothing */
    }
    return 0;
}


void setReadXMLFile(treeXML* root)
{
    FILE* fp = NULL;
    char *str= NULL;
    if(root == NULL)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    fp = fopen(FILEXML,"r");
    if(fp == NULL)
    {
        setReadFile(root,FILENAME);
    }
    else
    {
        str = (char*)malloc((BUFF_SIZE+1)*sizeof(char));
        if(str != NULL)
        {
            fgets(str,BUFF_SIZE,fp);
            str[strlen(str)-1] = '\0';
            setReadFile(root,str);
            free(str);
            str = NULL;
        }
        else
        {
            setReadFile(root,FILENAME); 
        }
        fclose(fp);
        fp = NULL;
    }
}
char* getTagFromXMLEle()
{
    FILE* fp = NULL;
    char *str= NULL;

    fp = fopen(FILEXML,"r");
    if(fp == NULL)
    {
        /*do nothing */
    }
    else
    {
        str = (char*)malloc((BUFF_SIZE+1)*sizeof(char));
        if(str != NULL)
        {
            fgets(str,BUFF_SIZE,fp); /* skip first row */
            fgets(str,BUFF_SIZE,fp);
            if(strlen(str) == 0)
            {
                free(str);
                str = NULL;
            }
            else
            {
                str[strlen(str)-1] = '\0';
            }
        }
        else
        {
            /* do nothing */
        }
        fclose(fp);
        fp = NULL;
    }
    return str;
}
