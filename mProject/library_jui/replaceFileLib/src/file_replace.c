#include "file_replace.h" 
 
void constructorFileHand(fileHand *obj)
{
    if(obj!=NULL)
    {
        memset(obj->oldFile,0,MAX_CHAR);
        memset(obj->newFile,0,MAX_CHAR);
    }
    else
    {
        /* do nothing */
    }
}
void destructorFileHand(fileHand *obj)
{
    constructorFileHand(obj);
}
void setFileHand(fileHand *obj,const char *nameold,const char *newName)
{
    char *oldF =NULL;
    char *nwF =NULL;
    if(obj!=NULL)
    {
        oldF = obj->oldFile;
        nwF = obj->newFile;
        memcpy(oldF,nameold,strlen(nameold));
        memcpy(nwF,newName,strlen(newName)); 
        oldF[strlen(nameold)] ='\0';
        nwF[strlen(newName)] ='\0';
    }
    else
    {
        /* do nothing */
    }
}
void  updateAttrbFileHand(fileHand *obj,pVoidList *list)
{
    symbHand *sym1 = NULL;
    int count =0;
    int index=0;
    int ret =0;
    char nwFile[MAX_CHAR];
    char *nw=NULL;
    char *old=NULL;
    if((obj!=NULL)&&(list!=NULL))
    {
        nw = obj->newFile;
        old = obj->oldFile;
        strcpy(nwFile,nw);
        count = countPVoidList(list);
        /* update nw name file*/
        for(index=0;index <count;index++)
        {
            sym1 = (symbHand*)getDataPVoidList(list,index);
            /*
            //test 6
            printSysHand(sym1);
            */
            ret =setSymbolToBuff(sym1,nwFile,nw,MAX_CHAR);
            if(ret ==2)/* 2 is  size is not enough to replace */
            {
                strcpy(nw,nwFile);
                printf("size of buffer is not enough, updateAttrbFileHand : %s\n ",__FILE__);
            }
            else
            {
                strcpy(nwFile,nw);
            }
            /*
            //test4
            printf("nw: %s -- %s\n",nw,obj->newFile);
            */
        }
        /* update old name file*/
        strcpy(nwFile,old);
        for(index=0;index <count;index++)
        {
            sym1 = (symbHand*)getDataPVoidList(list,index);
            /*
            //test 6
            printSysHand(sym1);
            */
            ret =setSymbolToBuff(sym1,nwFile,old,MAX_CHAR);
            if(ret ==2)/* 2 is  size is not enough to replace */
            {
                strcpy(old,nwFile);
            }
            else
            {
                strcpy(nwFile,old);
            }
            /*
            //test4.2
            printf("old: %s -- %s\n",old,obj->newFile);
            */
        }
    }
    else
    {
        /* do nothing */
    }
}

void processReplacingWordFileHande(fileHand *obj,pVoidList *list)
{
    symbHand *sym1 = NULL;
    int count =0;
    int sizeBuff =MAX_BUFF-1;
    int index=0;
    int ret =0;
    char *nw =NULL;
    char *old =NULL;
    char type =0; /* 1 oldFile !=  new, 2 old == new , 0 is failed process */
    FILE *fpOld =NULL;
    FILE *fpNw =NULL;
    char buffFile[MAX_BUFF];
    char buffNew[MAX_BUFF];
    /* verify and open file  to read and write*/
    if((obj!=NULL)&&(list!=NULL))
    {
        count = countPVoidList(list);
        nw = obj->newFile;
        old= obj->oldFile;
        fpOld = fopen(old,"r");
        printf("open file name : %s\n",old);
        memset(buffFile,0,MAX_BUFF);
        memset(buffNew,0,MAX_BUFF);
        if(strcmp(nw,old)==0)
        {
            type = 2; /* old == new */
        }
        else
        {
            type = 1;
            fpNw = fopen(nw,"w");
        } 
        if((type==1)&&((fpOld==NULL)||(fpNw==NULL)))
        { 
    printf("nothing Fold:%p FNew:%p \n",fpOld,fpNw);
            if(fpOld!=NULL)
            {
                fclose(fpOld);
                fpOld=NULL;
            }
            else
            {
                /* do nothing */
            } 
            if(fpNw!=NULL)
            {
                fclose(fpNw);
                fpNw = NULL;
            }
            else
            {
                /* do nothing */
            }
            type =0; /* failed */
        }
        else if(fpOld ==NULL)
        {
            type =0; /* failed */
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
    if(type==1)
    {
        while(fgets(buffFile,sizeBuff,fpOld)!= 0)
        {
            for(index = 0;index<count;index++)
            {
                sym1 = (symbHand*)getDataPVoidList(list,index);
                while(setSymbolToBuff(sym1,buffFile,buffNew,MAX_BUFF) ==3) /* there is more 1*/
                {
                    strcpy(buffFile,buffNew);
                }
                if(ret == 2)/* 2 is size is not enough to replace */
                {
                    strcpy(buffNew,buffFile);
                }
                else
                {
                    strcpy(buffFile,buffNew);
                }
            }
            fprintf(fpNw,"%s",buffNew);
        }
    }
    else if(type ==2) /* old == new */
    {
        /* TBD */
    }
    else
    {
        /* do nothing */
    } 
    if(fpNw!=NULL)
    {
        fclose(fpNw);
    }
    else
    {
        /* do nothing */
    }
    if(fpOld!=NULL)
    {
        fclose(fpOld);
    }
    else
    {
        /* do nothing */
    }
}