#ifndef DEBUG_H__
#define DEBUG_H__
#define LOGFILE "logDebug.log"
#define SHOW_LINE 1 //0 = not show, 1 = show
#define SHOW_FILE 1 //0 = not show ,1 = show
#define SHOW_FUNC 1 //0 = not show,1 =show
void printFile(FILE **fp,const char* str)
{
    if(SHOW_FILE ==1)
    {
        fprintf(*fp,"file:%s ",str);
    }
    else
    {
        //do nothing
    }
}
void printLine(FILE **fp,int i)
{
    if(SHOW_LINE ==1)
    {
        fprintf(*fp,"line:%d ",i);
    }
    else
    {
        //do nothing
    }
}
void printFn(FILE **fp,const char* str)
{
    if(SHOW_FUNC ==1)
    {
        fprintf(*fp,"func:%s ",str);
    }
    else
    {
        //do nothing
    }
}

void closeFile(FILE **fp)
{
    if(*fp !=NULL)
    {
        fclose(*fp);
        *fp = NULL;
    }
    else
    {
        //do nothing
    }
}
void updateLog(FILE **fp)
{
    *fp = fopen(LOGFILE,"w+b");
    if(*fp == NULL)
    {
        printf("cannot debug \n");
    }
    else
    {
        //do nothing
    }
}
void printOpt(int i,const char* str,const char* file,void* p,int a)
{
        FILE *fp;
        updateLog(&fp);
        printFile(&fp,file);
        printFn(&fp,str);
        printLine(&fp,i);
        if(a==1)
        {
           fprintf(fp,"free :%p ",p);
        }
        else
        {
           fprintf(fp,"new :%p ",p);
        }
        closeFile(&fp);
}
#endif //DEBUG_H__
