/********************************************************************/
/*
      FILE        :  iVtHandle.c
      Name     :   Chalearm Saelim
      Date       :   10 Dec 2015
      Purpose :   To handle AVL Tree (defination part iVtHandle.h)
                         Adding, Removing and compare any node in the tree

      Dependency lib list :  -
      Description :      In this file is make up of following list below :
                                1. the necessary methods for AVL tree
*/
/*******************************************************************/
#include "iVtHandle.h"
#include <stdio.h>

void constructIVTH(iVtH *obj ,int numArr,int numEle)
{
    binaryTree *tp = NULL;
    if(obj!=NULL)
    {
        tp = &(obj->m_t);
        obj->m_max =MAX_DEF;
        obj->m_min =MIN_DEF;
        obj->m_displyVectSet =1;
        obj->m_displyT =1;
        constructVH(&(obj->m_vSet),numEle,numArr);
        /* void constructAvlTree(binaryTree* avlTree,char isWithData,const char* KeyTypeConfig,int sizeData,int sizeKey) */
        constructAvlTree((void*)tp,0,"vector_int",0,sizeof(vector_int)); 
        setDelKeyAndDelDataAndCompFnForAvlTree(tp,NULL,NULL,compVIntIVTH);
        setDelKeyFnForAvlTree(tp,NULL);
        setDelKeyFlag(tp,1); 
        tp->printKeyPVoid = &printKeyVInTIVTH;
    }
    else
    {
        /* do nothing */
    }
}

void destructIVTH(iVtH *obj)
{
    binaryTree *tp = NULL;
    if(obj!=NULL)
    {
        obj->m_max =MAX_DEF;
        obj->m_min =MIN_DEF;
        obj->m_displyVectSet =1;
        obj->m_displyT =1;
        tp = &(obj->m_t);
        destructVectHand(&(obj->m_vSet));
        clearBinaryTree(tp);
    }
    else
    {
        /* do nothing */
    }
}

void clearTIVTH(iVtH *obj)
{
    binaryTree *tp = NULL;
    if(obj!=NULL)
    {
        tp = &(obj->m_t);
        clearBinaryTree(tp);
    }
    else
    {
        /* do nothing */
    }
}

void clearAnodeInTIVTH(iVtH *obj,int indexNode)
{
    void *data4Del = NULL;
    int res =-1;
    if((indexNode>-1)&&(obj !=NULL))
    {
        data4Del = getVectInVH(&(obj->m_vSet),indexNode);
        printf("get %d to remove:%p, &:%p \n",indexNode,data4Del,&data4Del);
    }
    else
    {
        /* do nothing */
    }
    if(data4Del != NULL) /* start delete*/
    {
        res = obj->m_t.deleteNodeByKey(&(obj->m_t),(void*)&data4Del);
    }
    else
    {
        printf("index is invalid\n");
    }
    if(res==0)
    {
        printf("the Node cannot be removed\n");
    }
    else if(res==1)
    {
        printf("the Node is removed\n");
    }
    else
    {
        /* do nothing */
    }
}
void setNumArrAndNumEle(iVtH *obj,int numArr,int numEle)
{    
    if(obj!=NULL)
    {
        destructIVTH(obj);
        constructVH(&(obj->m_vSet),numEle,numArr);
    }
    else
    {
        /* do nothing */
    }
}

void setStyleOfIVTH(iVtH *obj,char  styleVect,char styleTree)
{
    if(obj!=NULL)
    {
        obj->m_displyVectSet = styleVect;
        obj->m_displyT = styleTree;
        if((obj->m_displyT&0x2)==2)
        {
            obj->m_t.printKeyPVoid = &printKeyVInTIVTH2;
        }
        else
        {
            obj->m_t.printKeyPVoid = &printKeyVInTIVTH;
        }
    }
    else
    {
        /* do nothing */
    }
}
void setMaxMinValueIVTH(iVtH *obj,int max,int min)
{
    if(obj!=NULL)
    {
        obj->m_max = max;
        obj->m_min = min;
    }
    else
    {
        /* do nothing */
    }
}

void setAllVectValueIVTH(iVtH *obj)
{
    if(obj!=NULL)
    {
         randomAllVectVH(&(obj->m_vSet),obj->m_max,obj->m_min);
    }
    else
    {
        /* do nothing */
    }
}

void AddAllValue2TIVTH(iVtH *obj)
{
    if(obj!=NULL)
    {
        vectIHand *vS = &(obj->m_vSet);
        binaryTree *pB =  &(obj->m_t);
        void *p =NULL;
        int index=0; 
        int num = vS->m_num;
        for(index=0;index<num;index++)
        {
            p = getVectInVH(vS,index);
            pB->insertFn(pB,&p);
        }
    }
    else
    {
        /* do nothing */
    }
}
void viewVListIVTH(iVtH *obj)
{
    if(obj!=NULL)
    {  /*m_displyVectSet*/
        printInfoVH(&(obj->m_vSet),obj->m_displyVectSet);
    }
    else
    {
        /* do nothing */
    }
}
void viewTIVTH(iVtH *obj)
{
    char buff[200];
    if(obj!=NULL)
    {
        obj->m_t.parameter3 = &buff;
        obj->m_t.printTree(&(obj->m_t),0);
    }
    else
    {
        /* do nothing */
    }
}
void viewIVTH(iVtH *obj)
{
    if(obj!=NULL)
    {
        viewVListIVTH(obj);
        printf("\n");
        viewTIVTH(obj);
    }
    else
    {
        /* do nothing */
    }
}

void printKeyVInTIVTH(void *key,char *buff)
{
    vector_int *va=NULL;
    int index=0;
    int num =0;
    char buff1[18];
    if((key!=NULL)&&(buff!=NULL))
    {
        va = (vector_int*)key;
        num = (int)(va)->lenght;
        buff[0] ='[';
        buff[1] ='\0';
        buff1[0]= '\0';
        for(index=0;index<num;index++)
        {
            buff1[0] ='\0'; 
            sprintf(buff1,"%d ",(va)->data[index]);
            strcat(buff,buff1);
        }
        buff1[0] =']';
        buff1[1]= '\0';
        strcat(buff,buff1);
    }
    else
    {
        /* do nothing */
    }
}
void printKeyVInTIVTH2(void *key,char *buff) /* with address*/
{
    vector_int *va=NULL;
    int index=0;
    int num =0;
    char buff1[18];
    if((key!=NULL)&&(buff!=NULL))
    {
        va = (vector_int*)key;
        num = (int)(va)->lenght;
        buff[0] ='[';
        buff[1] ='\0';
        buff1[0]= '\0';
        for(index=0;index<num;index++)
        {
            buff1[0] ='\0'; 
            sprintf(buff1,"%d ",(va)->data[index]);
            strcat(buff,buff1);
        }
        buff1[0] =']';
        buff1[1]= '\0';
        strcat(buff,buff1);
        sprintf(buff1," %p ",va);
        strcat(buff,buff1);
    }
    else
    {
        /* do nothing */
    }
}
int compVIntIVTH(const void* a,const void *b)
{
    int res =UN_DEFINE;
    int index =0;
    int num =0;
    vector_int **va=NULL,**vb=NULL;
    if((a==NULL)||(b==NULL))
    {
        /* do noting */
    }
    else if((*((vector_int**)a)!=NULL)&&(*((vector_int**)b)!=NULL))
    {
        va = ((vector_int**)a);
        vb = ((vector_int**)b);
        if((*va)->lenght > (*vb)->lenght)
        {
            num = (*vb)->lenght;
        }
        else
        {
            num =(*va)->lenght;
        }
        res =EQUAL_DEFINE;
        for(index=0;index<num;index++)
        {
            if((*va)->data[index]> (*vb)->data[index])
            {
                index=num;
                res = MORE_DEFINE;
            }
            else if((*va)->data[index]< (*vb)->data[index])
            {
                index=num;
                res = LESS_DEFINE;
            }
            else
            {
                /* do nothing */
            }
        }
        if((res ==EQUAL_DEFINE)&&((*va)->lenght == (*vb)->lenght))
        {
            /* do noting */
        }
        else if((res ==EQUAL_DEFINE)&&((*va)->lenght == num)&&((*vb)->lenght>num))
        {
            res = LESS_DEFINE;
        } 
        else if((res ==EQUAL_DEFINE)&&((*vb)->lenght == num)&&((*va)->lenght>num))
        {
            res = MORE_DEFINE;
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

/*   User Interface method part */

void constructVHSetting(vhSettingParam *obj)
{
    obj->m_defaultNumEle = DEF_NUM_ELE;
    obj->m_defaultNumArr = DEF_NUM_ARR;
    obj->m_defaultDisplayStyle = DEF_DIS_STYLE;/*  first bit show value , second bit  show address */
    obj->m_defaultDisplayStyleT = DEF_DIS_STYLE_T;  /*  first bit show value , second bit  show address */
}

void displayValueVHSetting(vhSettingParam *obj)
{
    if(obj!=NULL)
    {
        printf("default element size    : %d\n",obj->m_defaultNumEle);
        printf("default array   size    : %d\n",obj->m_defaultNumArr);
        printf("default display VectSet :");
        if((obj->m_defaultDisplayStyle&0x1)==1)
        {
            printf("show value,");
        }
        else
        {
            printf("not show value,");
        }
        if((obj->m_defaultDisplayStyle&0x2)==2)
        {
            printf("show @,");
        }
        else
        {
            printf("not show @,");
        }
        printf("\n");
        printf("default display Tree :");
        if((obj->m_defaultDisplayStyleT&0x1)==1)
        {
            printf("show value,");
        }
        else
        {
            printf("not show value,");
        }
        if((obj->m_defaultDisplayStyleT&0x2)==2)
        {
            printf("show @,");
        }
        else
        {
            printf("not show @,");
        }
        printf("\n");
    }
    else
    {
        /* do nothing */
    }
}

void setVectEleVHSetting(vhSettingParam *obj)
{
    int val=0;
    if(obj!=NULL)
    {
        printf("current ele size : %d , (0 or -1 ) to cancel and back to menu\n",obj->m_defaultNumEle);
        printf("Please insert positive integer value : ");
        scanf("%d",&val);
        if(val >0)
        {
            obj->m_defaultNumEle = val;
        }
        else
        {
            /* do nothing */
        }
        menuSettingVHset();
        scanf("\n");
    }
    else
    {
        /* do nothing */
    }
}
void setArrSizeVHSetting(vhSettingParam *obj)
{
    int val=0;
    if(obj!=NULL)
    {
        printf("current Arr size : %d , (0 or -1 ) to cancel and back to menu\n",obj->m_defaultNumArr);
        printf("Please insert positive integer value : ");
        scanf("%d",&val);
        if(val >0)
        {
            obj->m_defaultNumArr = val;
        }
        else
        {
            /* do nothing */
        }
        menuSettingVHset();
        scanf("\n");
    }
    else
    {
        /* do nothing */
    }
}

int setIndex2RemNodeVHSetting()
{
    int index=0;
    printf("Please Insert Node index : ");
    scanf("%d\n",&index);
    return index;
}

void setDisplayStyleVectSetVHSetting(vhSettingParam *obj)
{
    int oldValue =0;
    if(obj!=NULL)
    {
        oldValue = obj->m_defaultDisplayStyle;
        printf("current Display style of Vect Set :Show ");
        if((oldValue&0x1)==1)
        {
            printf("value");
        }
        if((oldValue&0x2)==2)
        {
            printf(" and @");
        }
        printf("\n");
        printf("Please input  1) Show only value or 2) Show value and Address, \nother) to cancel and back to menu \n");
        scanf("%d",&oldValue);
        if(oldValue==1)
        {
            obj->m_defaultDisplayStyle=1;
        }
        else if(oldValue==2)
        {
            obj->m_defaultDisplayStyle=3;
        }
        else
        {
            /* do nothing */
        }
        menuSettingVHset();
        scanf("\n");
    }
    else
    {
        /* do nothing */
    }
}
void setDisplayStyleTVHSetting(vhSettingParam *obj)
{
    int oldValue =0;
    if(obj!=NULL)
    {
        oldValue = obj->m_defaultDisplayStyleT;
        printf("current Display style of T :Show ");
        if((oldValue&0x1)==1)
        {
            printf("value");
        }
        if((oldValue&0x2)==2)
        {
            printf(" and @");
        }
        printf("\n");
        printf("Please input  1) Show only value or 2) Show value and Address, \nother) to cancel and back to menu \n");
        scanf("%d",&oldValue);
        if(oldValue==1)
        {
            obj->m_defaultDisplayStyleT=1;
        }
        else if(oldValue==2)
        {
            obj->m_defaultDisplayStyleT=3;
        }
        else
        {
            /* do nothing */
        }
        menuSettingVHset();
        scanf("\n");
    }
    else
    {
        /* do nothing */
    }
}

void initialedVHByVHSet(vhSettingParam *obj,iVtH *obj2)
{
    if((obj !=NULL)&&(obj2 !=NULL))
    {
        destructIVTH(obj2);
        constructIVTH(obj2,obj->m_defaultNumArr,obj->m_defaultNumEle);
        setAllVectValueIVTH(obj2); 
    }
    else
    {
        /* do nothing */
    }
}

void initialedStyleByVHSet(vhSettingParam *obj,iVtH *obj2)
{
    if((obj !=NULL)&&(obj2 !=NULL))
    {
        setStyleOfIVTH(obj2,obj->m_defaultDisplayStyle,obj->m_defaultDisplayStyleT);
    }
    else
    {
        /* do nothing */
    }
}
void menuDisplayOfVH()
{
    int index =97;
    printf(">>>>>>>>>>Set Vector Int Tree>>Menu>>>>>>>>>>>>>>>>>>>\n");
    printf("%c# Display Menu\n",index++);
    printf("%c# Initial All\n",index++);
    printf("%c# Initial Style\n",index++);
    printf("%c# Initial Vector element\n",index++);
    printf("%c# Add the Vector 2 Tree\n",index++);
    printf("%c# Add the all vectors 2 Tree\n",index++);
    printf("%c# remove the vectors from Tree\n",index++);
    printf("%c# remove the all vectors from Tree\n",index++);
    printf("%c# view Vector Set\n",index++);
    printf("%c# view Tree\n",index++);
    printf("%c# Setting\n",index++); 
    printf("%c# Quit\n",index++); 
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

void menuSettingVHset()
{ 
    int index =97;
    printf(">>>>>>>>>>Setting>>Menu>>>>>>>>>>>>>>>>>>>\n");
    printf("%c# Display Menu\n",index++);
    printf("%c# view default value\n",index++);
    printf("%c# Set Default Vect Element\n",index++);
    printf("%c# Set Default Vect Arr Size\n",index++);
    printf("%c# Set Display vect Set Style\n",index++);
    printf("%c# Set Display Tree Style\n",index++);
    printf("%c# Exit program\n",index++);
    printf("%c or other keys# Back to main menu\n",index++); 
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

int  mainSettingMenu(vhSettingParam *obj)
{
    char ch =0;
    char isLoop =1;
    char fact1=1;
    while(isLoop==1)
    {
        ch = getchar();
        switch(ch)
        {
             case 'a':
                menuSettingVHset();
            break;
            case 'b':
                displayValueVHSetting(obj);
            break;
            case 'c':
                setVectEleVHSetting(obj);
            break;
            case 'd':
                setArrSizeVHSetting(obj);
            break;
            case 'e':
                setDisplayStyleVectSetVHSetting(obj);
            break;
            case 'f':
                setDisplayStyleTVHSetting(obj);
            break;
             case 'g':
                fact1 =0;
                isLoop =0;
            break;
             case 'h':
                menuSettingVHset();
                isLoop=0;
                menuDisplayOfVH();
            break;
        }
    }
    return fact1;
}
void mainDisplayLoopVHSetting(iVtH *obj)
{
    char ch =0;
    char isLoop =1;
    int indexNode =0;
    vhSettingParam vhSetParam;
    constructVHSetting(&vhSetParam);
    while(isLoop==1)
    {
         ch = getchar();
         switch(ch)
         {
             case 'a':
             menuDisplayOfVH();
              break;
             case 'b':
              initialedVHByVHSet(&vhSetParam,obj);
              break;
             case 'c':
              initialedStyleByVHSet(&vhSetParam,obj);
              break;
             case 'i':
              viewVListIVTH(obj);
              break;
             case 'f':
              AddAllValue2TIVTH(obj);
              break;
             case 'g': /*   remove the vectors from Tree */ 
             indexNode =setIndex2RemNodeVHSetting();
             clearAnodeInTIVTH(obj,indexNode);
              break;
             case 'h':
              clearTIVTH(obj);
              break;
             case 'j':
              viewTIVTH(obj);
              break;
             case 'k':
             menuSettingVHset();
             isLoop =mainSettingMenu(&vhSetParam);
              break;
             case 'l':
             isLoop =0;
              break;
         }
    }
}
