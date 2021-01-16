#include "XmlUi.h"
/*-------------------------------- DEFINED XML KEY SESSION -------------*/
#define STR_ELE_TAG                         "ELE_TAG"
#define STR_SAVE_NAME                        "SAVE_NAME"
#define STR_ID                              "ID"
#define STR_ID_PARENT                       "ID_PARENT"
#define STR_IS_LIST                         "IS_LIST"
#define STR_NAME                            "NAME"
#define STR_COMMENT                         "COMMENT"
#define STR_DEFAULT_VALUE                   "DEFAULT_VALUE"
#define STR_DESCRIPTION                     "DESCRIPTION"
#define STR_ATTRB                           "ATTRB"
#define STR_pos                             "pos"
#define STR_on                              "on"
#define STR_type                            "type"
#define STR_overide                         "overide"
#define STR_TYPE                            "TYPE"
#define STR_prefix                          "prefix"
#define STR_suffix                          "suffix"

void initialAttrbUi(attrbUi* attrbUiObj)
{
    if(attrbUiObj != NULL)
    {
        attrbUiObj->name  = new_vector_char(0); 
        attrbUiObj->value = new_vector_char(0); 
        initialSimString(&(attrbUiObj->desp));
        attrbUiObj->type = 0;
        attrbUiObj->typeVal = 0;
    }
    else
    {
        /* do noting */
    }
}

void destructAttrbUi(attrbUi* attrbUiObj)
{
    if(attrbUiObj != NULL)
    {
        delete_vector_char(&(attrbUiObj->name));
        delete_vector_char(&(attrbUiObj->value));
        destructSimString(&(attrbUiObj->desp)); 
    }
    else
    {
        /* do noting */
    }
}

void initialTagEleUi(tagEleUi* tagEleUiObj)
{
    if(tagEleUiObj != NULL)
    {
        tagEleUiObj->name  = new_vector_char(0); 
        tagEleUiObj->value = new_vector_char(0); 
        initialSimString(&(tagEleUiObj->desp));
        tagEleUiObj->id = -1;
        tagEleUiObj->idP= -1;
        tagEleUiObj->isList = 0;
        tagEleUiObj->type = 0;
        tagEleUiObj->numAttrb = 0;
        tagEleUiObj->attrbUiObj = NULL;
        tagEleUiObj->next = NULL;
    }
    else
    {
        /* do nothing */
    }
}
void destructTagEleUi(tagEleUi* tagEleUiObj)
{
    int index = 0;
    int num = 0;
    if(tagEleUiObj != NULL)
    {
        destructTagEleUi(tagEleUiObj->next);
        num = tagEleUiObj->numAttrb;
        delete_vector_char(&(tagEleUiObj->name));
        delete_vector_char(&(tagEleUiObj->value));
        destructSimString(&(tagEleUiObj->desp));  
        tagEleUiObj->id = -1;
        tagEleUiObj->idP= -1;
        tagEleUiObj->isList = 0;
        tagEleUiObj->type = 0;
        initialComment(&(tagEleUiObj->comtxt));
        tagEleUiObj->hasComment = 0;
        tagEleUiObj->numAttrb = 0;
        for(index=0;index <num;index++)
        {
            destructAttrbUi(&(tagEleUiObj->attrbUiObj[index]));
        }
        free(tagEleUiObj->attrbUiObj);
        tagEleUiObj->attrbUiObj = NULL;
        tagEleUiObj->next = NULL;
    }
    else
    {
        /* do noting */
    }  
}

void initialXMLUi(XMLUi *XMLUiObj)
{
    if(XMLUiObj != NULL)
    {   
        XMLUiObj->eleUi = NULL;
        XMLUiObj->formFile = NULL;
        XMLUiObj->numTag = 0;
        initialFileNameHandle(&(XMLUiObj->fileName));
    }
    else
    {
        /* do nothing */
    }
}

void destructXMLUi(XMLUi *XMLUiObj)
{
    int index = 0;
    int num = 0;
    if(XMLUiObj != NULL)
    {   
        num = XMLUiObj->numTag;
        destructFileNameHandle(&(XMLUiObj->fileName));
        if(XMLUiObj->formFile != NULL)
        {
            fclose(XMLUiObj->formFile);
        }
        else
        {
            /* do nothing */
        }
        for(index=0;index<num;index++)
        {
            destructTagEleUi(&(XMLUiObj->eleUi[index])); 
        }
        free(XMLUiObj->eleUi);
        XMLUiObj->numTag = 0;
        XMLUiObj->eleUi = NULL;
        XMLUiObj->formFile = NULL;
    }
    else
    {
        /* do nothing */
    }   
}
int alloNumEleUiXMLUi(XMLUi *XMLUiObj,int numb)
{
    int res = 0;
    int index=0;
    if(XMLUiObj != NULL && numb >-1)
    {
        XMLUiObj->numTag = numb;
        XMLUiObj->eleUi = (tagEleUi*)malloc(numb*sizeof(tagEleUi));
        if(XMLUiObj->eleUi != NULL)
        {
            res =1;
            for(index = 0;index < numb;index++)
            {
                initialTagEleUi(&(XMLUiObj->eleUi[index]));
            }
        }
        else
        {
            XMLUiObj->numTag = 0;
        }
    }
    else
    {   
        /* do nothing */
    }
    return res;
}

int loadSourceToXMLUi(XMLUi *XMLUiObj,const char *namefile)
{
    treeXML tXML;
    simString dummyName;
    simString dummyType;
    char saveT = 0;
    char prefix =0;
    char suffix=0;
    listElement listXML;
    elementXML *pEle=NULL;
    int numNode = 0;
    int index = 0;
    int res =  getSourceToTreeXML(&tXML,namefile);
    res &= getSourceToXMLList(&listXML,tXML.root,STR_ELE_TAG);
    initialSimString(&dummyName);
    initialSimString(&dummyType);
    /* allocate the number of tagEles */
    if(res == 1)
    {
        numNode = getNumOfXMLNode(&listXML);
        res = alloNumEleUiXMLUi(XMLUiObj,numNode);
    }
    else
    {
        /* do nothing */
    }
    /* get tag Ele */
    if(res ==1)
    {
        for(index= 0;index <numNode;index++)
        {
            pEle = getXMLElement(&listXML,index);
            res &= loadNode2TagEle(&(XMLUiObj->eleUi[index]),pEle);
            if(res ==0) /* read tag failed */
            {
                printf("read tag res[%d]:%d\n",index,res);
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
    /* get File Name Handle */
    if(res ==1)
    {
        res  = getValueOfFirstChildEle2Var(tXML.root,STR_SAVE_NAME,"",(void*)&dummyName,0x080); /* simString*/      
        res &= getAttrbValueOfFirstChildEle2Var(tXML.root,STR_SAVE_NAME,STR_overide,"1",(void*)&saveT,0x00); /* char */     
        res &= getAttrbValueOfFirstChildEle2Var(tXML.root,STR_SAVE_NAME,STR_type,"xml",(void*)&dummyType,0x080);/* simString*/
        getAttrbValueOfFirstChildEle2Var(tXML.root,STR_SAVE_NAME,STR_prefix,"-1",(void*)&prefix,0x00);/*optional attrb char*/
        getAttrbValueOfFirstChildEle2Var(tXML.root,STR_SAVE_NAME,STR_suffix,"-1",(void*)&suffix,0x00);/*optional attrb  char*/
        res &= setAllValueOfFileNameHandle(&(XMLUiObj->fileName),&dummyName,&dummyType,saveT,prefix,suffix);
    }
    else
    {
        /* do nothing */
    }
    if(res != 1)
    {
        destructXMLUi(XMLUiObj);
    }
    else
    {
        /* do nothing */
    }
    destructListXMLEle(&listXML);
    destructorTreeXML(&tXML);
    destructSimString(&dummyName);
    destructSimString(&dummyType);
    return res;
}

int alloNumAttrbTagEleUi(tagEleUi *tagEleUiObj,int numb)
{
    int res = 0;
    int index=0;
    if(tagEleUiObj != NULL && numb >-1)
    {
        tagEleUiObj->numAttrb = numb;
        tagEleUiObj->attrbUiObj = (attrbUi*)malloc(numb*sizeof(attrbUi));
        if(tagEleUiObj->attrbUiObj != NULL)
        {
            res =1;
            for(index = 0;index < numb;index++)
            {
                initialAttrbUi(&(tagEleUiObj->attrbUiObj[index]));
            }
        }
        else
        {
            tagEleUiObj->numAttrb = 0;
        }
    }
    else
    {   
        /* do nothing */
    }
    return res;
}

int loadNode2TagEle(tagEleUi *tagEleUiObj,elementXML *pEle)
{
    listElement listXML;
    elementXML *pEleN=NULL;
    simString dummyType;
    int numNode = 0;
    int index = 0;
    int res =0;
    int isList = getSourceToXMLList(&listXML,pEle,STR_ATTRB);
    initialSimString(&dummyType);
    if(tagEleUiObj != NULL && pEle != NULL)
    {
        res  = getValueOfFirstChildEle2Var(pEle,STR_ID,"1",(void*)&(tagEleUiObj->id),0x010);
        res &= getValueOfFirstChildEle2Var(pEle,STR_ID_PARENT,"0",(void*)&(tagEleUiObj->idP),0x010);
      /* opt */getValueOfFirstChildEle2Var(pEle,STR_IS_LIST,"0",(void*)&(tagEleUiObj->isList),0x000);
        res &= getValueOfFirstChildEle2Var(pEle,STR_NAME,"",(void*)&(tagEleUiObj->name),0x070);
        res &= getValueOfFirstChildEle2Var(pEle,STR_COMMENT,"",(void*)&dummyType,0x080);
        addNodeSimStrList(&(tagEleUiObj->comtxt.text),&dummyType);
        destructSimString(&dummyType);
        initialSimString(&dummyType);
        res &= getValueOfFirstChildEle2Var(pEle,STR_DEFAULT_VALUE,"",(void*)&(tagEleUiObj->value),0x070);
        res &= getValueOfFirstChildEle2Var(pEle,STR_DESCRIPTION,"",(void*)&(tagEleUiObj->desp),0x080);
        res &= getAttrbValueOfFirstChildEle2Var(pEle,STR_COMMENT,STR_on,"0",(void*)&(tagEleUiObj->hasComment),0x00);
        res &= getAttrbValueOfFirstChildEle2Var(pEle,STR_COMMENT,STR_pos,"0",(void*)&(tagEleUiObj->comtxt.type),0x00);
        res &= getAttrbValueOfFirstChildEle2Var(pEle,STR_DEFAULT_VALUE,STR_type,"-1",(void*)&dummyType,0x080);
        tagEleUiObj->type = mappingTypeXMLUi(dummyType.data);
        if(res ==0)
        {
            printf("    after read element res=0\n");
        }
        else
        {
            /* do nothing */
        }
        if(isList != 0 && res != 0)
        {
            numNode = getNumOfXMLNode(&listXML);
            alloNumAttrbTagEleUi(tagEleUiObj,numNode);
            for(index= 0;index <numNode;index++)
            {
                pEleN = getXMLElement(&listXML,index);
                res &= loadNode2AttrbUi(&(tagEleUiObj->attrbUiObj[index]),pEleN);
                if(res ==0)
                {
                    printf("   attrb[%d] :%d\n",index,res);
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
        if(res==0)
        {
            destructTagEleUi(tagEleUiObj);
        }
        else
        {
            /* do nothing*/
        }
    }
    else
    {   
        printf("faile tagEleUiObj\n");
        /* do nohting */
    }    
    destructSimString(&dummyType);
    destructListXMLEle(&listXML);
    return res;
    /*defined 
    use  12 bits
    last nibble
    0 = sign
    1 = unsign
    0x000 char
    0x010 int
    0x020 short
    0x030 long
    0x040 float
    0x050 double
    0x060 long double
    0x070 vector_char
    0x080 simString
    
*/
}

int loadNode2AttrbUi(attrbUi *attrbUiObj,elementXML *pEle)
{
    int res = 0;
    simString dummyType;
    initialSimString(&dummyType);
    if(attrbUiObj != NULL && pEle!=NULL)
    {
        res  = getValueOfFirstChildEle2Var(pEle,STR_NAME,"",(void*)&(attrbUiObj->name),0x070);
        res &= getValueOfFirstChildEle2Var(pEle,STR_TYPE,"0",(void*)&(attrbUiObj->type),0x000);
        res &= getValueOfFirstChildEle2Var(pEle,STR_DEFAULT_VALUE,"",(void*)&(attrbUiObj->value),0x070);  
        res &= getAttrbValueOfFirstChildEle2Var(pEle,STR_DEFAULT_VALUE,STR_type,"-1",(void*)&dummyType,0x080);
        attrbUiObj->typeVal = mappingTypeXMLUi(dummyType.data);
        res &= getValueOfFirstChildEle2Var(pEle,STR_DESCRIPTION,"",(void*)&(attrbUiObj->desp),0x080);  
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&dummyType);
    return res;
}
void printAttrbUi(attrbUi *attrbUiObj)
{
    if(attrbUiObj != NULL)
    {
        printf("name:");
        print_vector_char(&(attrbUiObj->name),11);
        printf("value:");
        print_vector_char(&(attrbUiObj->value),11);
        printf("typeVal:%s\n",valueTypeName(attrbUiObj->typeVal));
        if(attrbUiObj->type ==0)
        {
            printf("double quote\n");
        }
        else
        {
            printf("single quote\n");
        }
        printf("despription:%s\n",attrbUiObj->desp.data);
        printf("---------------------------------------------------\n");
    }
    else
    {
        /* do nothing */
    }
}

void printTagEleUi(tagEleUi *eleUiObj)
{
    int index = 0;
    int numAttrb = 0;
    if(eleUiObj != NULL)
    {
        numAttrb =eleUiObj->numAttrb;
        printf("id : %d\n",eleUiObj->id);
        printf("pid : %d\n",eleUiObj->idP);
        printf("List:");
        if(eleUiObj->isList==1)
        {
            printf(" yes\n");
        }
        else
        {
            printf(" No\n");
        }
        printf("name:");
        print_vector_char(&(eleUiObj->name),11);
        printf("value:");
        print_vector_char(&(eleUiObj->value),11);
        printf("typeVal:%s\n",valueTypeName(eleUiObj->type));
        printf("hasComment:");
        if(eleUiObj->hasComment==1)
        {
            printf(" yes\n");
            
            printSimStrList(&(eleUiObj->comtxt.text));
        }
        else
        {
            printf(" No\n");
        }  
        printf("despription:%s\n",eleUiObj->desp.data);
        for(index=0;index<numAttrb;index++)
        {
            printAttrbUi(&(eleUiObj->attrbUiObj[index]));
        }
        printTagEleUi(eleUiObj->next);
        printf("*************************************************\n");
    }
    else
    {
        /* do nothing */
    }
}

void printXMLUi(XMLUi *XMLUiObj)
{
    int index =0;
    int numTag=0;
    simString dummyName;
    initialSimString(&dummyName);
    if(XMLUiObj != NULL)
    {
        dummyName = getFileName(&(XMLUiObj->fileName));
        numTag = XMLUiObj->numTag;
        printf("nameFile: %s\n",dummyName.data);
        printf("numTag:%d\n",XMLUiObj->numTag);
        for(index=0;index<numTag;index++)
        {
            printTagEleUi(&(XMLUiObj->eleUi[index]));
        }
        
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&dummyName);
}
const char* valueTypeName(char type)
{
    if(type ==0)
    {
        return "text";
    }
    else if(type==1)
    {
        return "sub-ele";
    }
    else if(type == 2)
    {
        return "int";
    }
    else if(type ==3)
    {
        return "double";
    }
    else
    {
        /* do nothing */
    }
    return "NULL"; 
}
int mappingTypeXMLUi(const char* type)
{
    int res=-1;
    if(type != NULL)
    {
        if(strcmp(type,"text") ==0)
        {
            res = 0;
        }
        else if(strcmp(type,"sub-ele") ==0)
        {
            res = 1;
        }
        else if(strcmp(type,"int") ==0)
        {
            res = 2;
        }
        else if(strcmp(type,"double") ==0)
        {
            res = 3;
        }
   
    }
    else
    {
        /* do nothing */
    }
    return res;
}
