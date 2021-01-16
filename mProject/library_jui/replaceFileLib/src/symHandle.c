#include "symHandle.h"
 void constructorSymbHand(symbHand *obj)
 {
     if(obj!=NULL)
     {
         obj->m_oldWord=NULL;
         obj->m_newWord=NULL;
         obj->m_oldWLength=0;
         obj->m_newWLength=0;
     }
     else
     {
         /* do nothing */
     }
 }
 
void destructorSymbHand(symbHand* obj)
{
    if(obj->m_oldWord != NULL)
    {
        free(obj->m_oldWord);
        obj->m_oldWord = NULL;
    }
    else
    {
        /* do nothing */
    }
    if(obj->m_newWord != NULL)
    {
        free(obj->m_newWord);
        obj->m_newWord = NULL;
    }
    else
    {
        /* do nothing */
    } 
    obj->m_oldWLength = 0;
    obj->m_newWLength = 0;
}

void  updateAttrbSymBH(symbHand *obj,pVoidList *list)
{
    int ret =(obj!=NULL)&&(list!=NULL);
    int  index=0;
    int count =0;
    symbHand *temp =NULL;
    int itsSize =0;
    int othSize =0;
    char *nwSym =NULL;
    char *oldSym =NULL;
    char buff[MAX_BUFF_SYM]; 
    char buffOld[MAX_BUFF_SYM]; 
    if(ret==1)
    {
        if(MAX_BUFF_SYM<=obj->m_oldWLength)
        {
            printf("error Buff for update Attrb Sym is not enough\n");
            ret =0;
        }
        else
        {
            /* do nothing */
        }
    }
    if(ret==1)
    {
        nwSym = obj->m_newWord;
        oldSym = obj->m_oldWord;
        memset(buff,0,MAX_BUFF_SYM);
        itsSize = obj->m_newWLength;
        count = countPVoidList(list);
        strcpy(buff,nwSym);
        strcpy(buffOld,oldSym);
        printf("count : %d\n",count);
        for(index=0;index<count;index++)
        { 
            temp = (symbHand*)getDataPVoidList(list,index);
            othSize = temp->m_oldWLength;
            if((othSize<=itsSize)&&(obj!=temp)) /* (obj!=temp) means recusion (replace itself)*/
            {
                /* start repace */
                /* buff is newWord
                old is other old
                new is other new 
                */
                ret = setSymbolToBuff(temp,nwSym,buff,MAX_BUFF_SYM);
                if(ret==2)/* 2 is  size is not enough to replace */
                {
                    printf("size of buffer is not enough, updateAttrbFileHand : %s\n ",__FILE__);
                }
                else
                {
                    /* do nothing */
                }
                setSymbHand(obj,buffOld,buff);
                nwSym = obj->m_newWord;
                oldSym = obj->m_oldWord;
                /*  printSysHand(temp);
                printSysHand(obj);*/
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
int setSymbolToBuff(symbHand *obj,const char* oldBuff,char *newBuff,int sizeNewBuff)
{
    int ret = 1; /* 1 is normal */
    int firstPos =0;
    int index =0,index2=0,index3=0;
    int sizeOldBuff= 0;
    int sizeOldWord= 0;
    int sizeNewWord= 0;
    char *old =NULL;
    char *nw =NULL;
    old = obj->m_oldWord;
    nw = obj->m_newWord;
    sizeOldWord= obj->m_oldWLength; /* count '\0' on*/
    sizeNewWord= obj->m_newWLength; /* count '\0' on*/
    sizeOldBuff= strlen(oldBuff);
     /*
        //test1
        printf("----oldWo-:%d------%d----\n",sizeOldWord,sizeOldBuff);
        printf("oldBuff(%d):%s, old(%d):%s, nw(%d):%s  \n",strlen(oldBuff),oldBuff,strlen(old),old,strlen(nw),nw); 
        printf("------xxxx---------\n"); 
        */
    
    for(index = 0;index < sizeOldBuff;index++)
    { 
/*
            //test2
            printf("oldB[%d]:%c == oldW[%d]:%c con1:%d,con2:%d,con3:%d,\n",index,oldBuff[index],index2,old[index2],(oldBuff[index] == old[index2]),(index2 < (sizeOldWord-1)), ((sizeOldBuff - index)>=(sizeOldWord-1)));
    
            printf("con 3: %d > %d\n",(sizeOldBuff - index),(sizeOldWord-1));
       */
        if((oldBuff[index] == old[index2]) && (index2 < (sizeOldWord-1)) )
        {
            /*
            printf("index : %d ,index2 :%d  oldBuffSize:%d  oldWord:%d\n",index,index2,sizeOldBuff,sizeOldWord);
            printf("oldB : %c  , old:%c\n",oldBuff[index],old[index2] );
             */
             if(index2+1 == (sizeOldWord-1)) /* replace */
            {
                for(index2 = 0;index2 < (sizeNewWord-1);index2++)
                {
                    newBuff[index3++] = nw[index2];
                }
                index2=-1;
            }
            else if((index2 == 0) && (sizeOldWord > 1))
            {
                firstPos = index;
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
            newBuff[index3++] = oldBuff[index];
            /*
      printf(" in 1 \n");
      */
        }
        else
        {
            newBuff[index3++] = oldBuff[index];
            index2=0;
            /*
      printf(" in 2 \n");*/
        }
        if(sizeNewBuff <= index3)
        {
            /*
            printf("Size is not enough, sizeNewBuff:%d,index3:%d \n",sizeNewBuff,index3);
            */
            ret =2; /* size is not enough to replace */
            break;
        }
        else
        {
            /* do nothing */
        }
    } 
    if(ret != 2)/* size is not enough to replace */
    {
        newBuff[index3] = '\0';
        /*
        printf("Size is not enough : %s \n",newBuff);
        */
    }
    else
    {
        /* do nothing */
    } 
    /*
    //test 3
    printf("newBuff (%d): %s\n",ret,newBuff); 
    */
    return ret;
}
void setSymbHand(symbHand* obj,const char *oldW,const char *nwW)
{

    destructorSymbHand(obj);
    
    int index=0;
    char *str1=NULL;
    obj->m_oldWLength =1;
    obj->m_newWLength =1;
    if(oldW!=NULL)
    {
        for(index=0;oldW[index]!='\0';index++)
        {
            obj->m_oldWLength++;
        }
    }
    else
    {
        /* do nothing */
    }
    if(nwW!=NULL)
    {
        for(index=0;nwW[index]!='\0';index++)
        {
            obj->m_newWLength++;
        }
    }
    else
    {
        /* do nothing */
    }
    if((obj->m_oldWLength >0)&&(oldW!=NULL))
    {
        obj->m_oldWord = (char*)malloc((obj->m_oldWLength)*sizeof(char));
        str1 =  obj->m_oldWord;
        for(index=0;index<obj->m_oldWLength;index++)
        {
            str1[index] = oldW[index];
        }
        str1[obj->m_oldWLength-1] ='\0';
    }
    else
    {
        obj->m_oldWord  = NULL;
    }
    if((obj->m_newWLength >0)&&(nwW!=NULL))
    {
        obj->m_newWord = (char*)malloc((obj->m_newWLength)*sizeof(char));
        str1 =  obj->m_newWord;
        for(index=0;index<obj->m_newWLength;index++)
        {
            str1[index] = nwW[index];
        }
        str1[obj->m_newWLength-1] ='\0';
    }
    else
    {
        obj->m_newWord  = NULL;
    }
}
void printSysHand(symbHand* obj)
{
    if(obj!=NULL)
    {
        if((obj->m_oldWord!=NULL)&&(obj->m_newWord!=NULL))
        {
            printf("oldW(%d):%s - NewW(%d): %s\n",obj->m_oldWLength,obj->m_oldWord,obj->m_newWLength,obj->m_newWord);
        }
        else
        {
            /* do noting */
        }
    }
    else
    {
        /* do nothing */
    }
}