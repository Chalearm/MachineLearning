#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
struct countHandle
{
    unsigned long long int m_sum;
    unsigned long long int m_limit;
};

void* count1Fn(void *obj);
void constructCountHandle(struct countHandle *obj,unsigned long long  num);
void countTimeThreadRun(int numThread,unsigned long long  numRound);
int main(int argc,char **argv)
{
    char buff[100];
    int numThread =0;
    unsigned long long  numRound =0;
    sscanf(argv[1],"%d",&numThread);
    sscanf(argv[2],"%ld",&numRound);
    clock_t ckc = clock();
    countTimeThreadRun(numThread,numRound);
    ckc = clock()-ckc;
    printf("time : %f \n",((float)ckc)/CLOCKS_PER_SEC);
    return 0;
}
void* count1Fn(void *obj)
{
    struct countHandle *p = (struct countHandle*)obj;
    int num = p->m_limit;
    unsigned long long int index=0;
    for(index=0;index< num;index++)
    {
        p->m_sum++;
    }
    return NULL;
}
void constructCountHandle(struct countHandle *obj,unsigned long long  num)
{
    if(obj!=NULL)
    {
        obj->m_sum =0;
        obj->m_limit =num;
    }
    else
    {
        /* do nothing */
    }
}
void countTimeThreadRun(int numThread,unsigned long long  numRound)
{
    pthread_t *pThread =(pthread_t*)malloc(sizeof(pthread_t)*numThread);
    struct countHandle *argTemp=(struct countHandle*)malloc(sizeof(struct countHandle)*numThread);
    unsigned long long  numRoundEachThread =0;
    int index=0;
    unsigned long long int sumTemp=0;
    if((pThread!=NULL)&&(numThread>0)&&(numRound>0))
    {
        numRoundEachThread = 0.5+((float)numRound)/((float)numThread);
        for(index =0;index<numThread;index++)
        {
            constructCountHandle(&argTemp[index],numRoundEachThread);
            pthread_create (&pThread[index], NULL, &count1Fn, &argTemp[index]);
        }
        for(index=0;index<numThread;index++)
        {
            pthread_join (pThread[index], NULL);
            sumTemp += argTemp[index].m_sum;
        }
        printf("sum is : %ld\n",sumTemp);
        free(pThread);
        free(argTemp);
    }
    else
    {
        /* do nothing*/
    }
    
}