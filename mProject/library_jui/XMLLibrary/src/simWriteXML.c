#include "simWriteXML.h"
#include <string.h>
#define TABSPACE  4
#define IT_S_OK 1
#define IT_S_FAIL 0
/* ----------- attrbXMLNode-----------*/
int initialAttrbXMLNode(attrbXMLNode* node)
{
    int res = IT_S_FAIL;
    if(node != NULL)
    {
        node->next = NULL;
        res = initial_attrbXML(&(node->data));
    }
    else
    {
        /* do nothing */
    }
    return res;
}
/* ------------attrbXMLList-----------*/
int initialAttrbXMLList(attrbXMLList* list)
{
    int res = IT_S_FAIL;
    if(list != NULL) 
    {
        list->root = NULL;
        list->last = NULL;
        list->numNode = 0;
        res = IT_S_OK;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int shallowCopyAttrbXMLList(attrbXMLList* rhs,attrbXMLList* lhs) /* no saft */
{
    int res = IT_S_FAIL;
    if(rhs != NULL && lhs != NULL) 
    {
        rhs->root = lhs->root;
        rhs->last = lhs->last;
        rhs->numNode = lhs->numNode;
        res = IT_S_OK;
    }
    else
    {
        /* do nothing */
    }
    return res;
}

void makeAttrbXMLListEmpty(attrbXMLList* list)
{
    attrbXMLNode *p = NULL;
    attrbXMLNode *p2 = NULL;
    if(list != NULL)
    {
        for(p=list->root;p!=NULL;) 
        {
            p2 = p;
            p  = p->next;
            destructorAttrbXML(&(p2->data));
            free(p2);
        }
        list->numNode = 0;
        list->root = NULL;
        list->last = NULL;
    }
    else
    {
        /* do nothing */
    }
}

void destructAttrbXMLList(attrbXMLList* list)
{
    makeAttrbXMLListEmpty(list);
}

int addAttrbData2AttrbXMLList(attrbXMLList* list,attrbXML* data)
{
    int res = IT_S_FAIL;
    if(list != NULL && data != NULL)
    {
        if(list->numNode == 0)
        {
            list->root = (attrbXMLNode*)malloc(sizeof(attrbXMLNode));
            list->last = list->root;
            if(list->root != NULL)
            {
                list->numNode++;
                res = initialAttrbXMLNode(list->root);
                res &= copyAttrbXML(&(list->root->data),data);
            } 
            else
            {
                /* do nothing */
            }
        }
        else
        {
            list->last->next = (attrbXMLNode*)malloc(sizeof(attrbXMLNode));
            if(list->last->next != NULL)
            {
                list->numNode++;
                list->last = list->last->next;
                res = initialAttrbXMLNode(list->last);
                res &= copyAttrbXML(&(list->last->data),data);
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
    return res;
}

int readAttrbsFromEleXML2AttrbXMLList(attrbXMLList* list,elementXML* root)
{
    int res = IT_S_FAIL;
    int numAttrb = 0;
    int index = 0;
    attrbXMLList dummyList;
    res = initialAttrbXMLList(&dummyList);
    if(list != NULL && root != NULL && res == IT_S_OK )
    {
        numAttrb = root->numAttrb;
        shallowCopyAttrbXMLList(&dummyList,list);
        initialAttrbXMLList(list);
        res = IT_S_OK;
        for(index =0 ;index < numAttrb;index++)
        {
            res &= addAttrbData2AttrbXMLList(list,&(root->attrb[index]));
        }
        if(res == IT_S_OK)
        {
            destructAttrbXMLList(&dummyList);
        }
        else
        {
            destructAttrbXMLList(list);
            shallowCopyAttrbXMLList(list,&dummyList);
        }
    }
    else
    {
        /* do nothing */
    }

    return res;
}

int removeAttrbNodeAttrbXMLList(attrbXMLList* list,int index)
{
    int res = IT_S_FAIL;
    int num = 0;
    int index2 = 0;
    attrbXMLNode *p= NULL;
    attrbXMLNode *p2= NULL;
    if(list != NULL && index >= 0)
    {
        num = list->numNode;
        if(num >index)
        {
            if(index == 0)
            {
                p = list->root;
                list->root = list->root->next;
                destructorAttrbXML(&(p->data));
                free(p);
                res = IT_S_OK;
            }
            else if(index ==num-1)
            {
                for(p=list->root;p->next->next!=NULL;p=p->next)
                {
                }
                list->root = p;
                list->root->next = NULL;
                p = p->next;  
                destructorAttrbXML(&(p->data));
                free(p);
                res = IT_S_OK;
            }
            else
            {
                p = list->root;
                for(index2 = 0;index2 < num;index2++)
                {
                    if(index2+1 == index)
                    {
                        index2 = num;
                        p2 = p->next;
                        p->next = p2->next;
                        destructorAttrbXML(&(p2->data));
                        free(p2);
                        res = IT_S_OK;
                    }
                    else
                    {
                        p = p->next;
                    }
                } 
            }
            list->numNode--;
            if(list->numNode ==0)
            {
                 list->root = NULL;
                 list->last = NULL;
            }
            else
            {
                /* do nothing */
            }
        }
        else
        {
            /* do nothing*/
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int removeAttrbNodeAttrbXMLListByName(attrbXMLList* list,const char* name)
{
    int res = IT_S_FAIL;
    int num = 0;
    int index2 = 0;
    attrbXMLNode *p= NULL;
    simString simStr;
    initialSimString(&simStr);
    vector_char vName = new_vector_char(0);
    if(list != NULL && name != NULL)
    {
        num = list->numNode;
        if(num >0)
        {
            convertCString2SimString(&simStr,name);
            convertSimString2VectorChar(&vName,&simStr);
            for(p=list->root;p!=NULL;)
            {
                if(compareEqual_v_char(&vName,&(p->data.name))==1)
                {
                    res = removeAttrbNodeAttrbXMLList(list,index2);
                    p =NULL;
                }
                else
                {
                    index2++;
                    p=p->next;
                }
            }
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
    delete_vector_char(&vName);
    destructSimString(&simStr);
    return res;
}
vector_char* getNameOfAttrbWithIndexAttrbXMLList(attrbXMLList* list,int index)
{
    vector_char *vect = NULL;
    attrbXMLNode *p = NULL;
    int index2 = 0;
    int num = 0;
    if(list != NULL && index >= 0)
    {
        num =list->numNode;
        p = list->root;
        for(index2 = 0;index2 < num;index2++)
        {
            if(index2 == index)
            {
                index2 = num;
                vect = &(p->data.name);
            }
            else
            {
                p = p->next;
            }
        }
    }
    else
    {
        /* do nothing */
    }
    return vect;
}
vector_char* getValueOfAttrbWithIndexAttrbXMLList(attrbXMLList* list,int index)
{
    vector_char *vect = NULL;
    attrbXMLNode *p = NULL;
    int index2 = 0;
    int num = 0;
    if(list != NULL && index >= 0)
    {
        num =list->numNode;
        p = list->root;
        for(index2 = 0;index2 < num;index2++)
        {
            if(index2 == index)
            {
                index2 = num;
                vect = &(p->data.value);
            }
            else
            {
                p = p->next;
            }
        }
    }
    else
    {
        /* do nothing */
    }
    return vect;
}
int setRootElement(treeXML *tXML,elementXML* root)
{
    int res = IT_S_FAIL;
    if(tXML !=NULL && root != NULL)
    {
        destructorElementXML(tXML->root);
        if(tXML->root != NULL)
        {
            free(tXML->root);
            tXML->root = NULL;
        }
        else
        {    
            /* do nothing */
        }
        res = new_elementXML(&(tXML->root));
        res &= copyElementXML(tXML->root,root);
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int setAnAttributeToElement(elementXML* root,attrbXML* attrb)
{
    int res = IT_S_FAIL;
    if(root != NULL && attrb != NULL)
    { 
        clearAttrbInElementXML(root);
        root->numAttrb = 1;
        res = new_attrbXML(root);
        copy_v_char(&(root->attrb->name),&(attrb->name));
        copy_v_char(&(root->attrb->value),&(attrb->value));
    }
    else
    {
        /* do nothing */
    }
    return res;
}
int setAttributeListToElement(elementXML* root,attrbXMLList* attrbList)
{
    int res = IT_S_OK;
    int index = 0;
    int num = 0;
    attrbXMLNode *p = 0;
    if(root != NULL && attrbList !=NULL)
    {
        num = attrbList->numNode;
        clearAttrbInElementXML(root);
        root->numAttrb = num;
        res &= new_attrbXML(root);
        if(res == 1)
        {
            p = attrbList->root;
            for(index = 0;index<num;index++)
            {
                copy_v_char(&(root->attrb[index].name),getNameOfAttrbWithIndexAttrbXMLList(attrbList,index));
                copy_v_char(&(root->attrb[index].value),getValueOfAttrbWithIndexAttrbXMLList(attrbList,index));
                root->attrb[index].type = p->data.type;
                p = p->next;
            }
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        res = IT_S_FAIL;
    }
    return res;
}
int setChildXMLElement(treeXML *tXML,elementXML* child,tagXMLAdd* tagXML)
{
    int res = IT_S_FAIL;
    elementXML *p = NULL;
    if(tXML != NULL && child != NULL && tagXML != NULL)
    {
        p = getAnElementXML(tXML,tagXML);
        if(p != NULL)
        {
            if(p->firstChild != NULL && p->typeEle == 0) /* 0 = has value */
            {
                destructorElementXML(p->firstChild);
                free(p->firstChild);
                p->firstChild = NULL;
                res = IT_S_OK;
            }
            else if(p->typeEle == 1 && p->firstChild == NULL)/* 1 = has no value */
            {
                res = IT_S_OK;
                p->typeEle = 0;
            }
            else if(p->typeEle == 0)/* 0 = has value */
            {
                res = IT_S_OK;
            }
            else
            {
                res = IT_S_FAIL;
            }
            if(res != IT_S_OK)
            {
                res = new_elementXML(&(p->firstChild));
                res &= copyElementXML(p->firstChild,child);
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
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int setWriteFileTreeXML(treeXML *tXML,const char* filename)
{
    int res = IT_S_FAIL;
    if(tXML !=  NULL && filename != NULL)
    {
        if(tXML->fp != NULL)
        {
            fclose(tXML->fp);
            tXML->fp = NULL;
        }
        else
        {
            /* do nothing */
        }
        tXML->fp = fopen(filename,"w");
        if(tXML->fp != NULL)
        {
            res = IT_S_OK;
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
    return res;
}
int createXMLFile(treeXML *tXML)
{
    int res = IT_S_FAIL;
    if(tXML != NULL)
    {
        if(tXML->fp != NULL)
        {
            res = generateTextElement(tXML->root,tXML->fp,0);
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
    return res;
}
const char* genTextEndHead(elementXML *child,char type)
{
    if(child != NULL && type == 0)
    {
        return ">\n";
    }
    else if(type == 1)
    {
        return "/>\n";
    }
    else
    {
        return ">";
    }
}
int generateTextHeadElement(elementXML* root,FILE* fp,int level)
{
    int res = IT_S_FAIL;
    int numSpace = level*TABSPACE;
    int typeCom = 0;
    simString space;
    simString nameEle;
    simString attrbStr;
    simString openSym;
    simString closeSym;
    initialSimString(&openSym);
    initialSimString(&closeSym);
    initialSimString(&space);
    initialSimString(&nameEle);
    initialSimString(&attrbStr);
    res = newSimStrWithInitailData(&space,numSpace,' ');
    if(root != NULL && fp != NULL && level >= 0 && (res == 1))
    {
        /* 0 upper Element, 1 behind Element, 2 below Element */
        typeCom =  getTypeCommentInElementXML(root);
        /* comment Upper Element */
        if(typeCom == 0)
        {
            res = writeCommentIntoFpElementXML(root,fp,numSpace,0);
        }
        else
        {
            /* do nothing */
        }
        /* Add attrbs */
        if(res == IT_S_OK)
        {
            res = generateTextAttrbs(root,&attrbStr);
        }
        else
        {
            /* do nothing */
        }
        if(res == IT_S_OK)
        {
            convertVectorChar2SimString(&nameEle,&(root->name));
            convertCString2SimString(&openSym,"<");
            convertCString2SimString(&closeSym,genTextEndHead(root->firstChild,root->typeEle));
            concatSimString(&space,&openSym,&space);
            concatSimString(&space,&nameEle,&space);
            concatSimString(&space,&attrbStr,&space);
            concatSimString(&space,&closeSym,&space);
            fprintf(fp,"%s",space.data);
            
            /* comment behind Element */
            if(typeCom == 1)
            {
                res = writeCommentIntoFpElementXML(root,fp,numSpace,0);
            }
            else
            {
                /* do nothing */
            }
            /* comment below Element */
            if(typeCom == 2)
            {
                res = writeCommentIntoFpElementXML(root,fp,numSpace,0);
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
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&openSym);
    destructSimString(&closeSym);
    destructSimString(&attrbStr);
    destructSimString(&nameEle);
    destructSimString(&space);
    return res;
}

int generateTextEndElement(elementXML* root,FILE* fp,int level)
{
    int res = IT_S_FAIL;
    int numSpace = level*TABSPACE;
    simString space;
    simString nameEle;
    simString valueEle;
    initialSimString(&space);
    initialSimString(&nameEle);
    initialSimString(&valueEle);
    res = newSimStrWithInitailData(&space,numSpace,' ');
    if(root != NULL && fp != NULL && level >= 0 && (res == IT_S_OK))
    {
        if(root->typeEle == 0 && root->firstChild != NULL)
        {
            convertVectorChar2SimString(&nameEle,&(root->name));
            if(space.length != 0)
            {
                fprintf(fp,"%s</%s>\n",space.data,nameEle.data);
            }
            else
            {
                fprintf(fp,"</%s>\n",nameEle.data);
            }
            destructSimString(&space);
        }
        else if(root->typeEle == 0)
        {
            convertVectorChar2SimString(&valueEle,&(root->value));
            convertVectorChar2SimString(&nameEle,&(root->name));
            if(valueEle.length !=0)
            {
                fprintf(fp,"%s</%s>\n",valueEle.data,nameEle.data);
            }
            else
            {
                fprintf(fp,"</%s>\n",nameEle.data);
            }
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
    destructSimString(&nameEle);
    destructSimString(&valueEle);
    destructSimString(&space);
    return res;
}

int generateTextElement(elementXML* root,FILE* fp,int level)
{
    int res = IT_S_FAIL;
    int numSpace = level*TABSPACE;
   // elementXML *p = NULL;
    simString space;
    simString nameEle;
    initialSimString(&space);
    initialSimString(&nameEle);
    res = newSimStrWithInitailData(&space,numSpace,' ');
    if(root != NULL && fp != NULL && level >= 0 && (res == IT_S_OK))
    {
        res  = generateTextHeadElement(root,fp,level); /* <...> */
        /* Recursive Child */
        if(root->firstChild != NULL && res == IT_S_OK)
        {
             res = generateTextElement(root->firstChild,fp,level+1);
        }
        else
        {
            /* do nothing */
        }
        res &= generateTextEndElement(root,fp,level);  /* </...> */
        if((res==IT_S_OK) && (root->next!=NULL))
        {
            res = generateTextElement(root->next,fp,level);
        }
        else
        {
            /* do nothing*/
        }
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&nameEle);
    destructSimString(&space);
    return res;
}

int generateTextAttrbs(elementXML* root,simString *attrb)
{
    int res = IT_S_FAIL;
    int index = 0;
    int num = 0;
    simString buffTxt;
    initialSimString(&buffTxt);
    if(root->numAttrb != 0 && attrb != NULL)
    {
        res = IT_S_OK;
        num = root->numAttrb;
        destructSimString(attrb);
        for(index = 0;(index < num) && (res!=IT_S_FAIL);index++)
        {
            res = generateATextAttrb(&(root->attrb[index]),&buffTxt);
            concatSimString(attrb,&buffTxt,attrb);
        }
    }
    else if(root->numAttrb == 0 && attrb != NULL)
    {
        res = IT_S_OK;
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&buffTxt);
    return res;
}

int generateATextAttrb(attrbXML *attrb,simString *txt)
{
    int res = IT_S_FAIL;
    simString buffTxt;
    simString equ;
    simString spc;
    simString oCSym; /* o = open, C = Close */
    simString nameStr;
    initialSimString(&oCSym);
    initialSimString(&nameStr);
    initialSimString(&equ);
    initialSimString(&spc);
    initialSimString(&buffTxt);
    if(attrb != NULL && txt != NULL)
    {
        destructSimString(txt);
        convertCString2SimString(&equ,"=");
        convertCString2SimString(&spc," ");
        if(attrb->type == 1)
        {
            convertCString2SimString(&oCSym,"\'");
        }
        else
        {
            convertCString2SimString(&oCSym,"\"");
        }
        convertVectorChar2SimString(&nameStr,&(attrb->name));
        concatSimString(&spc,&nameStr,txt);
        convertVectorChar2SimString(&nameStr,&(attrb->value));
        concatSimString(txt,&equ,txt);
        concatSimString(txt,&oCSym,txt);
        concatSimString(txt,&nameStr,txt);
        concatSimString(txt,&oCSym,txt);
        res = 1;
    }
    else
    {
        /* do nothing */
    }
    destructSimString(&oCSym);
    destructSimString(&nameStr);
    destructSimString(&equ);
    destructSimString(&spc);
    destructSimString(&buffTxt);
    return res;
}

int changeNameElementWithCStr(treeXML *tXML,tagXMLAdd *tagXML,const char* msg)
{
    int res = 0;
    simString simStr;
    initialSimString(&simStr);
    convertCString2SimString(&simStr,msg);
    res = changeNameElement(tXML,tagXML,&simStr);
    destructSimString(&simStr);
    return res;
}

int changeNameElementWithVector(treeXML *tXML,tagXMLAdd *tagXML,vector_char* msg)
{
    int res = 0;
    simString simStr;
    initialSimString(&simStr);
    convertVectorChar2SimString(&simStr,msg);
    res = changeNameElement(tXML,tagXML,&simStr);
    destructSimString(&simStr);
    return res;
}

int changeNameElement(treeXML *tXML,tagXMLAdd *tagXML,simString* msg)
{
    int res = 0;
    int numTagXML = 0;
    elementXML* dummyEle=NULL;
    if(tXML != NULL && tagXML != NULL && msg != NULL)
    {
        numTagXML = getNumOfTagXMLAdd(tagXML);
        if(tXML->root != NULL && numTagXML > 0)
        {
            dummyEle = getAnElementXML(tXML,tagXML);
            if(dummyEle != NULL)
            {
                convertSimString2VectorChar(&(dummyEle->name),msg);
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
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int changeValueElementWithCStr(treeXML *tXML,tagXMLAdd *tagXML,const char* msg)
{
    int res = 0;
    simString simStr;
    initialSimString(&simStr);
    convertCString2SimString(&simStr,msg);
    res = changeValueElement(tXML,tagXML,&simStr);
    destructSimString(&simStr);
    return res;
}

int changeValueElementWithVector(treeXML *tXML,tagXMLAdd *tagXML,vector_char* msg)
{
    int res = 0;
    simString simStr;
    initialSimString(&simStr);
    convertVectorChar2SimString(&simStr,msg);
    res = changeValueElement(tXML,tagXML,&simStr);
    destructSimString(&simStr);
    return res;
}

int changeTypeElement(treeXML *tXML,tagXMLAdd *tagXML,const char type)
{
    int res = 0;
    int numTagXML = 0;
    elementXML* dummyEle=NULL;
    if(tXML != NULL && tagXML != NULL && (type ==1 || type ==0))
    {
        numTagXML = getNumOfTagXMLAdd(tagXML);
        if(tXML->root != NULL && numTagXML >0)
        {
            dummyEle = getAnElementXML(tXML,tagXML);
            if(dummyEle != NULL)
            {
                dummyEle->typeEle = type;
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
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int changeValueElement(treeXML *tXML,tagXMLAdd *tagXML,simString* msg)
{
    int res = 0;
    int numTagXML = 0;
    elementXML* dummyEle=NULL;
    if(tXML != NULL && tagXML != NULL && msg != NULL)
    {
        numTagXML = getNumOfTagXMLAdd(tagXML);
        if(tXML->root != NULL && numTagXML >0)
        {
            dummyEle = getAnElementXML(tXML,tagXML);
            if(dummyEle != NULL)
            {
                convertSimString2VectorChar(&(dummyEle->value),msg);
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
    }
    else
    {
        /* do nothing */
    }
    return res;
}

int deleteAttrbInTheElement(treeXML *tXML,tagXMLAdd *tagXML,const char *name)
{
    int res = 0;
    int numTagXML = 0;
    elementXML* dummyEle=NULL;
    attrbXMLList listAttr;
    res = initialAttrbXMLList(&listAttr);
    if(tXML != NULL && tagXML != NULL && name != NULL && res == 1)
    {
        numTagXML = getNumOfTagXMLAdd(tagXML);
        if(tXML->root != NULL && numTagXML >0)
        {
            dummyEle = getAnElementXML(tXML,tagXML);
            if(dummyEle != NULL)
            {
                res = readAttrbsFromEleXML2AttrbXMLList(&listAttr,dummyEle);
            }
            else
            {
                /* do nothing */
            }
            if(res == 1)
            {
                res = removeAttrbNodeAttrbXMLListByName(&listAttr,name);
            }
            else
            {
                /* do nohting */
            }
            if(res==1)
            {
                res = setAttributeListToElement(dummyEle,&listAttr);
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
    }
    else
    {
        /* do nothing */
    }
    destructAttrbXMLList(&listAttr);
    return res;
}
int deleteAttrbInTheElementByOrder(treeXML *tXML,tagXMLAdd *tagXML,int index)
{
    int res = 0;
    int numTagXML = 0;
    elementXML* dummyEle=NULL;
    attrbXMLList listAttr;
    res = initialAttrbXMLList(&listAttr);
    if(tXML != NULL && tagXML != NULL && index >= 0&& res ==1)
    {
        numTagXML = getNumOfTagXMLAdd(tagXML);
        if(tXML->root != NULL && numTagXML >0)
        {
            dummyEle = getAnElementXML(tXML,tagXML);
            if(dummyEle != NULL)
            {
                res = readAttrbsFromEleXML2AttrbXMLList(&listAttr,dummyEle);
            }
            else
            {
                /* do nothing */
            }
            if(res == 1)
            {
                res = removeAttrbNodeAttrbXMLList(&listAttr,index);
            }
            else
            {
                /* do nohting */
            }
            if(res==1)
            {
                res = setAttributeListToElement(dummyEle,&listAttr);
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
    }
    else
    {
        /* do nothing */
    }
    destructAttrbXMLList(&listAttr);
    return res;
}
int addAttrb2TheElementWithDetail(treeXML *tXML,tagXMLAdd *tagXML,const char *name,const char *value,const char type)
{
    int res = 0;
    int numTagXML = 0;
    elementXML* dummyEle=NULL;
    attrbXMLList listAttr;
    attrbXML  atXML;
    simString simStr;
    simString simStr2;
    initialSimString(&simStr);
    initialSimString(&simStr2);
    vector_char vect1 = new_vector_char(0);
    vector_char vect2 = new_vector_char(0);
    res = initialAttrbXMLList(&listAttr);
    res &=initial_attrbXML(&atXML);
    if(tXML != NULL && tagXML != NULL && name != NULL && value != NULL &&(type ==1 || type ==0) && res ==1)
    {
        numTagXML = getNumOfTagXMLAdd(tagXML);
        if(tXML->root != NULL && numTagXML >0)
        {
            dummyEle = getAnElementXML(tXML,tagXML);
            if(dummyEle != NULL)
            {
                res = readAttrbsFromEleXML2AttrbXMLList(&listAttr,dummyEle);  
            }
            else
            {
                /* do nothing */
            }  
            if(res == 1)
            {
                convertCString2SimString(&simStr,name);
                convertSimString2VectorChar(&vect1,&simStr);
                copy_v_char(&(atXML.name),&vect1);                

                convertCString2SimString(&simStr2,value);
                convertSimString2VectorChar(&vect2,&simStr2);
                copy_v_char(&(atXML.value),&vect2);
                
                atXML.type = type;
                res = addAttrbData2AttrbXMLList(&listAttr,&atXML);
            }
            else
            {
                /* do nohting */
            }
            if(res==1)
            {
                res = setAttributeListToElement(dummyEle,&listAttr);
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
    }
    else
    {
        /* do nothing */
    }
    delete_vector_char(&vect1);
    delete_vector_char(&vect2);
    destructSimString(&simStr);
    destructSimString(&simStr2);
    destructorAttrbXML(&atXML);
    destructAttrbXMLList(&listAttr);
    return res;
}
int addAttrb2TheElement(treeXML *tXML,tagXMLAdd *tagXML,attrbXML* data)
{
    int res = 0;
    int numTagXML = 0;
    elementXML* dummyEle=NULL;
    attrbXMLList listAttr;
    res = initialAttrbXMLList(&listAttr);
    if(tXML != NULL && tagXML != NULL && data != NULL && res ==1)
    {
        numTagXML = getNumOfTagXMLAdd(tagXML);
        if(tXML->root != NULL && numTagXML >0)
        {
            dummyEle = getAnElementXML(tXML,tagXML);
            if(dummyEle != NULL)
            {
                res = readAttrbsFromEleXML2AttrbXMLList(&listAttr,dummyEle);  
            }
            else
            {
                /* do nothing */
            }
            if(res == 1)
            {
                res = addAttrbData2AttrbXMLList(&listAttr,data);
            }
            else
            {
                /* do nohting */
            }
            if(res==1)
            {
                res = setAttributeListToElement(dummyEle,&listAttr);
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
    }
    else
    {
        /* do nothing */
    }
    destructAttrbXMLList(&listAttr);
    return res;
}

attrbXML* getAttrbOfTheElement(treeXML *tXML,tagXMLAdd *tagXML,vector_char *name)
{
    attrbXML *attrP = NULL;
    elementXML* dummyEle=NULL;
    int index =0;
    int numTagXML = 0;
    int numNode = 0;
    if(tXML !=NULL && tagXML !=NULL && name !=NULL)
    {
        numTagXML = getNumOfTagXMLAdd(tagXML);
        if(tXML->root != NULL && numTagXML >0)
        {
            dummyEle = getAnElementXML(tXML,tagXML);
            numNode =  dummyEle->numAttrb;
            for(index = 0;index < numNode;index++)
            {
                if(compareEqual_v_char(name,&(dummyEle->attrb[index].name)) == 1)
                {
                    attrP = &(dummyEle->attrb[index]);
                    index = numNode;
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
    }
    else
    {
        /* do nothing */
    }
    return attrP;
}

int changeNameAttrbOfTheElementWithCStr(treeXML *tXML,tagXMLAdd *tagXML,const char *name,const char *newName)
{
    int res = 0;
    simString str1;
    simString str2;
    initialSimString(&str1);
    initialSimString(&str2);
    convertCString2SimString(&str1,name);
    convertCString2SimString(&str2,newName);
    res =changeNameAttrbOfTheElementWithSimStr(tXML,tagXML,&str1,&str2);
    destructSimString(&str1);
    destructSimString(&str2);
    return res;
}
int changeNameAttrbOfTheElementWithSimStr(treeXML *tXML,tagXMLAdd *tagXML,simString *name,simString *newName)
{
    int res = 0;
    vector_char vect = new_vector_char(0);
    vector_char vect2 = new_vector_char(0);
    convertSimString2VectorChar(&vect,name);
    convertSimString2VectorChar(&vect2,newName);
    res = changeNameAttrbOfTheElement(tXML,tagXML,&vect,&vect2);
    delete_vector_char(&vect);
    delete_vector_char(&vect2);
    return res;
}
int changeNameAttrbOfTheElement(treeXML *tXML,tagXMLAdd *tagXML,vector_char *name,vector_char *newName)
{
    int res  = 0;
    attrbXML *pAttrb = NULL;
    if(tXML != NULL && name != NULL && newName != NULL && tagXML != NULL)
    {
        pAttrb = getAttrbOfTheElement(tXML,tagXML,name);
        if(pAttrb != NULL)
        {
            res =1;
            copy_v_char(&(pAttrb->name),newName);
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
    return res;
}

int changeValueAttrbOfTheElement(treeXML *tXML,tagXMLAdd *tagXML,vector_char *name,vector_char *value)
{
    int res  = 0;
    attrbXML *pAttrb = NULL;
    if(tXML != NULL && name != NULL && value != NULL && tagXML != NULL)
    {
        pAttrb = getAttrbOfTheElement(tXML,tagXML,name);
        if(pAttrb != NULL)
        {
            res =1;
            copy_v_char(&(pAttrb->value),value);
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
    return res;
}
int changeValueAttrbOfTheElementWithCstr(treeXML *tXML,tagXMLAdd *tagXML,const char *name,const char *value)
{
    int res = 0;
    simString str1;
    simString str2;
    initialSimString(&str1);
    initialSimString(&str2);
    convertCString2SimString(&str1,name);
    convertCString2SimString(&str2,value);
    res =changeValueAttrbOfTheElementWithSimstr(tXML,tagXML,&str1,&str2);
    destructSimString(&str1);
    destructSimString(&str2);
    return res;
}
int changeValueAttrbOfTheElementWithSimstr(treeXML *tXML,tagXMLAdd *tagXML,simString *name,simString *value)
{
    int res = 0;
    vector_char vect = new_vector_char(0);
    vector_char vect2 = new_vector_char(0);
    convertSimString2VectorChar(&vect,name);
    convertSimString2VectorChar(&vect2,value);
    res = changeValueAttrbOfTheElement(tXML,tagXML,&vect,&vect2);
    delete_vector_char(&vect);
    delete_vector_char(&vect2);
    return res;
}
int changeTypeAttrbOfTheElement(treeXML *tXML,tagXMLAdd *tagXML,vector_char *name,const char type)
{
    int res  = 0;
    attrbXML *pAttrb = NULL;
    if(tXML != NULL && name != NULL && (type == 0 || type ==1) && tagXML != NULL)
    {
        pAttrb = getAttrbOfTheElement(tXML,tagXML,name);
        if(pAttrb != NULL)
        {
            res =1;
            pAttrb->type = type;
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
    return res;
}

int changeTypeAttrbOfTheElementWithSimStr(treeXML *tXML,tagXMLAdd *tagXML,simString *name,const char type)
{
    int res = 0;
    vector_char vect = new_vector_char(0);
    convertSimString2VectorChar(&vect,name);
    res = changeTypeAttrbOfTheElement(tXML,tagXML,&vect,type);
    delete_vector_char(&vect);
    return res;
}
int changeTypeAttrbOfTheElementWithCStr(treeXML *tXML,tagXMLAdd *tagXML,const char *name,const char type)
{
    int res = 0;
    simString str1;
    initialSimString(&str1);
    convertCString2SimString(&str1,name);
    res =changeTypeAttrbOfTheElementWithSimStr(tXML,tagXML,&str1,type);
    destructSimString(&str1);
    return res;
}
