
#include <stdio.h>
#include <string.h>
#include "convertStr2Digi.h"
long long str2Int3(const char* str,int size,char* isNum)
{
    long long ret=0;
    int  sign  = 1;
    long long place =1;
    int index;
    int c;
	if(isNum!=NULL)
	{
	    for(index =size-1;index >=0;index--,place *=10)
	    {
	        c= str[index];
	        switch(c)
	        {
	            case '-':
	                if(index==0)
	                    {
	                    sign = -1;
	                    }
	                else
	                {
	                    *isNum=0;
	                    return -1;
	                }
	                break;
	            default:
	                if(c >= '0' && c<='9')
	                {
	                    ret += (c-'0')*place;
	                }
	                else
	                {
	                    *isNum=0;
	                    return -1;
	                }
	        }
	    }
		*isNum=1;
	}
	else
	{
		/* do nothing */
	}
    return sign*ret;
}
long long str2Int2(const char* str,int size)
{
    long long ret=0;
    int  sign  = 1;
    long long place =1;
    int index;
    int c;
    for(index =size-1;index >=0;index--,place *=10)
    {
        c= str[index];
        switch(c)
        {
            case '-':
                if(index==0)
                    {
                    sign = -1;
                    }
                else
                {
                    printf("Error1 this %c is not number\n",c);
                    return -1;
                }
                break;
            default:
                if(c >= '0' && c<='9')
                {
                    ret += (c-'0')*place;
                }
                else
                {
                    printf("Error2 this %c is not number\n",c);
                    return -1;
                }
        }
    }
    return sign*ret;
}
long long str2Int(const char* str)
{
    int size =  strlen(str);
    return str2Int2(str,size);
}
long long str2IntV_char(vector_char* vec)
{
    return str2Int2(vec->data,vec->lenght);
}

long double _double_fraction(const char* str,int size)
{
    long double place = 0.1;
    long double ret = 0.0;
    int index = 0;
    for(index =0;index <size;index++,place /= 10.0)
    {
        int c = str[index];
        ret += (c-'0')*place;
    }
    return ret;
}
long double str2Double2(const char* str,int size)
{
    int n =0;
    int sign = 1;
    int d = -1;
    long double ret =0;
    while(n<size)
    {
        switch(str[n])
        {
            case '-':
                if(n==0)
                {	
                    sign =-1;
                }
                else
                {
                    return -1;
                }
                break;
            case '.':
                if(d == -1)
                {
                    d =n;
                }
                else
                {
                    return -1;
                }
                break;
            default:
                if(str[n] <'0' && str[n] >'9')
                {
                    return -1;
                }
                else
                {
                    //do nothing
                }
        }
        n++;
    }
    if(d ==-1)
    {
        return (long double)str2Int2(str,n);
    }
    else if(d==0)
    {
        return _double_fraction((str+d+1),(n-d-1));
    }
    else if(sign ==-1 && d ==1)
    {
        return (-1.0)*_double_fraction((str+1+d),(n-d-1));
    }
    else if(sign == -1)
    {
        ret = (long double)str2Int2(str+1,d-1);
        return (-1.0)*(ret + _double_fraction((str+d+1),(n-d-1)));
    }
    else
    {
        
        ret = (long double)str2Int2(str,d);
        return ret + _double_fraction((str+d+1),(n-d-1));
    }
    return -1.0;
}
long double str2Double(const char* str)
{
    int size = strlen(str);
    return str2Double2(str,size);
}
long double str2DoubleWithBoolean(const char* str,char *isConvert)
{
    int size = strlen(str);
    return str2Double3(str,size,isConvert);
}
long double str2DoubleV_char(vector_char* vec)
{
    return str2Double2(vec->data,vec->lenght);
}
vector_char cStr2V_char(const char *str)
{
    vector_char vdata = new_vector_char(0);
    int lengthChar    = strlen(str);
    int index         = 0;
    if(str == NULL)
    {
        /* do nothing */
    }
    else
    {
        vdata = new_vector_char(lengthChar);
        for(index = 0;index < lengthChar;index++)
        {
            vdata.data[index] = str[index];
        }   
    }
    return vdata;
}
long double str2Double3(const char* str,int size,char* isConvert)
{
    int n =0;
    int sign = 1;
    int d = -1;
    long double ret =0;
    *isConvert = 1;
    while(n<size)
    {
        switch(str[n])
        {
            case '-':
                if(n==0)
                {	
                    sign =-1;
                }
                else
                {
                    return -1;
                }
                break;
            case '.':
                if(d == -1)
                {
                    d =n;
                }
                else
                {
                    return -1;
                }
                break;
            default:
                if(str[n] <'0' && str[n] >'9')
                {
                    *isConvert  = 0;
                    return -1;
                }
                else
                {
                    /* do nothing */
                }
        }
        n++;
    }
    if(d ==-1)
    {
        return (long double)str2Int3(str,n,isConvert);
    }
    else if(d == 0)
    {
        return _double_fraction((str+d+1),(n-d-1));
    }
    else if(sign ==-1 && d ==1)
    {
                printf("val1 -------------:%f \n",(double)_double_fraction((str+d+1),(n-d-1)));
        return (-1.0)*_double_fraction((str+1+d),(n-d-1));
    }
    else if(sign == -1)
    {
        printf("val2 -------------:%f \n",(double)_double_fraction((str+d+1),(n-d-1)));
        ret = (long double)str2Int3(str+1,d-1,isConvert);
        return (-1.0)*(ret + _double_fraction((str+d+1),(n-d-1)));
    }
    else
    {
        printf("val3 -------------:%f \n",(double)_double_fraction((str+d+1),(n-d-1)));
        
        ret = (long double)str2Int3(str,d,isConvert);
        return ret + _double_fraction((str+d+1),(n-d-1));
    }
    *isConvert=0;
    return -1.0;
}
