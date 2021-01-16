#include "simString.h"
#include <string.h>
void initialSimString(simString *simStr)
{
    simStr->data   = NULL;
    simStr->length = 0;
}
int newSimStr(simString *simStr,int num)
{
    if(num == 0)
    {
        destructSimString(simStr);
    }
    else if(num < 1)
    {
        return 0;
    }
    else
    {
        destructSimString(simStr);
        simStr->length = num;
        simStr->data = (char*)malloc(sizeof(char)*num);
        simStr->data[num-1] = '\0';
    }
    return 1;
}
int newSimStrWithInitailData(simString *simStr,int num,char dat)
{
    int index = 0;
    if(num == 0)
    {
        destructSimString(simStr);
    }
    else if(num < 1)
    {
        return 0;
    }
    else
    {
        destructSimString(simStr);
        simStr->length = num;
        simStr->data = (char*)malloc(sizeof(char)*num);
        for(index =0 ;index < num ;index++)
        {
            simStr->data[index] = dat;
        }
        simStr->data[num-1] = '\0';
    }
    return 1;
}
void destructSimString(simString *simStr)
{
    if(simStr == NULL)
    {
        return;
    }
    else if(simStr->data != NULL)
    {
        free(simStr->data);
        simStr->data   = NULL;
        simStr->length = 0;
    }
    else
    {
        /* do nothing */
    }
}
void copySimStr(simString *simStr1,simString *simStr2)
{
    int fact = 0;
    int index= 0;
    if(simStr1 == simStr2)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    fact = newSimStr(simStr1,simStr2->length);
    if(fact == 0)
    {
        return;
    }
    else
    {
        for(index =0 ;index<simStr2->length;index++)
        {
            simStr1->data[index] = simStr2->data[index];
        }   
    }
}
void copyNLetterSimStr(simString *simStr1,simString *simStr2,int num)
{
    int fact = 0;
    int index= 0;
    if(simStr1 == simStr2)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    fact = newSimStr(simStr1,num+1);
    if(fact == 0)
    {
        return;
    }
    else
    {
        for(index =0 ;index<num;index++)
        {
            simStr1->data[index] = simStr2->data[index];
        }   
        simStr1->data[num] = '\0';
    }
}
int concatSimString(simString *simStr1,simString *simStr2,simString *res)
{
    int fact = 0;
    int index1 = 0;
    int num =0;
	if(simStr1->length >0 && simStr2->length >0)
	{
		num = simStr1->length + simStr2->length -1; /* have 2 '\0' */
	}
	else
	{
		num = simStr1->length + simStr2->length;
	}
    simString dummy1;
    initialSimString(&dummy1);
	if(num >-1)
	{
		fact = newSimStr(&dummy1,num);
	}
	else
	{
		/* do nothing */
	}
    if(fact == 0)
    {
        return 0;
    }
    else
    {
		if(simStr1->length >0)
		{
			for(index1 = 0;index1 <simStr1->length-1;index1++)
			{ 
				dummy1.data[index1] = simStr1->data[index1];
			}
			for(index1 = 0;index1 <simStr2->length;index1++)
			{
				dummy1.data[index1+simStr1->length-1] = simStr2->data[index1];
			}
		}
		else
		{
			for(index1 = 0;index1 <simStr2->length;index1++)
			{
				dummy1.data[index1] = simStr2->data[index1];
			}
		}

       /* dummy1.data[dummy1.length-1] = '\0';*/
        destructSimString(res);
        res->data = dummy1.data;
        res->length = dummy1.length;
    }
    return 1;
}

int concatSimStringPathDirectory(simString *simStr1,simString *simStr2,simString *res)
{
    int fact = 0;
    int fact2= 0;
    int index1 = 0;
    int num = simStr1->length + simStr2->length -1; /* have 2 '\0' */
    simString dummy1;
    fact = simStr1->data[simStr1->length-2] == '/';
    fact2= simStr2->data[0] =='/';
    if(fact == 0 && fact2 == 0)
    {
        fact2=0;
        num +=1;
    }
    else if(fact ==1 && fact2 ==1)
    {
        num -=1;
        fact2=1;
    }
    else 
    {
        fact2=2;
    }
    initialSimString(&dummy1);
    fact = newSimStr(&dummy1,num);
    if(fact == 0)
    {
        return 0;
    }
    else
    {
        for(index1 = 0;index1 <simStr1->length-1;index1++)
        { 
            dummy1.data[index1] = simStr1->data[index1];
        }
        if(fact2 ==0)
        {
            dummy1.data[index1] = '/';
            fact2 = 0;
            fact  = 1;
        }
    else if(fact2 ==1)
        {
            fact2 = 1;
            fact  = 0;
        }
    else
    {
            fact2 = 0;
            fact  = 0;
        }
        for(index1 = 0;(index1+fact2) <simStr2->length-1;index1++)
        {
            dummy1.data[fact+index1+simStr1->length-1] = simStr2->data[index1+fact2];
        }
        dummy1.data[dummy1.length-1] = '\0';
        destructSimString(res);
        res->data = dummy1.data;
        res->length = dummy1.length;
    }
    return 1;
}

int compareSimString(simString *simStr1,simString *simStr2)
{
    int index = 0;
    int fact  = 1;
    if(simStr1 == simStr2)
    {
        fact=1;
    }
    else if((simStr1 ==NULL)||(simStr2 == NULL))
    {
        fact =0;
    }
    else if(simStr1->length == simStr2->length)
    {
        for(index = 0;index < simStr1->length;index++)
        {
            if(simStr1->data[index] != simStr2->data[index])
            {
                fact = 0;
                break;
            }
            else
            {
                /* do nothing */
            }
        }
    }
    else
    {
        fact = 0;
    }
    return fact;
}
int compareSimStrWithCstr(simString *simStr1,const char *cstr)
{
    int index = 0;
    int fact  = 1;
    if((simStr1 ==NULL)||(cstr == NULL))
    {
        fact =0;
    }
    else if((unsigned int)(simStr1->length-1) ==strlen(cstr))
    {
        for(index = 0;index < simStr1->length;index++)
        {
            if(simStr1->data[index] != cstr[index])
            {
                fact = 0;
                break;
            }
            else
            {
                /* do nothing */
            }
        }
    }
    else
    {
        fact = 0;
    }
    return fact;
}
int compareNLetterSimString(simString *simStr1,simString *simStr2,int num)
{
    int index = 0;
    int fact  = 1;
    if(simStr1->length == simStr2->length && num > 0)
    {
        for(index = 0;index < num;index++)
        {
            if(simStr1->data[index] != simStr2->data[index])
            {
                fact = 0;
                break;
            }
            else
            {
                /* do nothing */
            }
        }
    }
    else
    {
        fact = 0;
    }
    return fact;
}

void convertCString2SimString(simString *simStr,const char *ch)
{
    int num = strlen(ch); 
    int index = 0;
    int fact  = 0;
    destructSimString(simStr);
    fact = newSimStr(simStr,num+1);
    if(fact == 0)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    for(index = 0;index < num;index++)
    {
        simStr->data[index] = ch[index];
    }
    simStr->data[index] = '\0';
}

void printSimString(simString *simStr1)
{
    if(simStr1 == NULL)
    {
        return;
    }
    else if(simStr1->length == 0)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    printf("%s\n",simStr1->data);
}

void convertVectorChar2SimString(simString *simStr,vector_char *vch)
{
    if(vch->lenght <1)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    int fact  = 0;
    char lastChar = 0;
    fact = newSimStr(simStr,vch->lenght + 1);
    if(fact == 0)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    lastChar = vch->data[vch->lenght-1];
    vch->data[vch->lenght-1] = '\0';
    strcpy(simStr->data,vch->data);
    vch->data[vch->lenght-1] = lastChar;
    simStr->data[vch->lenght-1] = lastChar;
    simStr->data[vch->lenght] = '\0';
    /*
    for(index=0;index<vch->lenght;index++)
    {
        simStr->data[index]=vch->data[index];
    } 
    simStr->data[index] = '\0';
    */
}

void convertSimString2VectorChar(vector_char *vch,simString *simStr)
{
    int index = 0;
    int numLoop = 0;
    if(vch != NULL && simStr != NULL)
    {
        if(simStr->data != NULL && simStr->length > 0)
        {
            numLoop = simStr->length-1;
        }
        else
        {
            numLoop = 0;
        }
        delete_vector_char(vch);
        *vch = new_vector_char(numLoop);
        for(index = 0;index < numLoop;index++)
        {
            vch->data[index] = simStr->data[index];
        }

    }
    else
    {
        /* do nothing */
    }
} 
