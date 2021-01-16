#include <stdio.h>
#include <string.h>
#include "dataTypeAndRoutineDefine.h"


int getDataTypeSize(int type)
{
    int res=0;
    switch(type)
    {
        case CHAR_TYPE:  /* char */ 
            res = sizeof(char);
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = sizeof(unsigned char);
        break;
        case INT_TYPE: /* int */ 
            res = sizeof(int);
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = sizeof(unsigned int);
        break;
        case SHORT_TYPE: /* short */ 
            res = sizeof(short);
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = sizeof(unsigned short);
        break;
        case LINT_TYPE: /* long */ 
            res = sizeof(long);
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = sizeof(unsigned long);
        break;
        case FLOAT_TYPE: /* float */ 
            res = sizeof(float);
        break;
        case DOUBLE_TYPE: /* double */
            res = sizeof(double); 
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = sizeof(long double);
        break;
        case LLINT_TYPE: /* long double */ 
            res = sizeof(long long);
        break;
        case ULLINT_TYPE: /* long double */ 
            res = sizeof(unsigned long long);
        break;
        case VDOUBLE_TYPE: /* vector_char*/
            res = sizeof(vector_double);
        break;
        case SIMSTRING_TYPE: /* simString */
            res = sizeof(simString);
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =0;
        break;
        default:
            res =0;
        break;
    }
    return res;
}
int getDataTypeFromString(const char* str)
{
    int res=0;
    if(str != NULL)
    {
        if(strcmp(str,"char") ==0)
        {
            res = CHAR_TYPE;
        }
        else if(strcmp(str,"unsigned char") ==0)
        {
            res = UCHAR_TYPE;
        }
        else if(strcmp(str,"int") ==0)
        {
            res = INT_TYPE;
        }
        else if(strcmp(str,"unsigned int") ==0)
        {
            res = UINT_TYPE;
        }
        else if(strcmp(str,"short") ==0)
        {
            res = SHORT_TYPE;
        }
        else if(strcmp(str,"unsigned short") ==0)
        {
            res = USHORT_TYPE;
        }
        else if(strcmp(str,"long") ==0)
        {
            res = LINT_TYPE;
        }
        else if(strcmp(str,"long int") ==0)
        {
            res = LINT_TYPE;
        }
        else if(strcmp(str,"unsigned long") ==0)
        {
            res = ULINT_TYPE;
        }
        else if(strcmp(str,"unsigned long int") ==0)
        {
            res = ULINT_TYPE;
        }
        else if(strcmp(str,"float") ==0)
        {
            res = FLOAT_TYPE;
        }
        else if(strcmp(str,"double") ==0)
        {
            res = DOUBLE_TYPE;
        }
        else if(strcmp(str,"long double") ==0)
        {
            res = LDOUBLE_TYPE;
        }
        else if(strcmp(str,"simString") ==0)
        {
            res = SIMSTRING_TYPE;
        }
        else if(strcmp(str,"vector_char") ==0)
        {
            res = VCHAR_TYPE;
        }
        else if(strcmp(str,"vector_double") ==0)
        {
            res = VDOUBLE_TYPE;
        }
        else if(strcmp(str,"long long int") ==0)
        {
            res = LLINT_TYPE;
        }
        else if(strcmp(str,"unsigned long long int") ==0)
        {
            res = ULLINT_TYPE;
        }
        else if(strcmp(str,"long long") ==0)
        {
            res = LLINT_TYPE;
        }
        else if(strcmp(str,"unsigned long long") ==0)
        {
            res = ULLINT_TYPE;
        }        
        else if(strcmp(str,"custom type 1") ==0)
        {
            res = CUS1_TYPE;
        }
        else if(strcmp(str,"custom type 2") ==0)
        {
            res = CUS2_TYPE;
        }
        else if(strcmp(str,"fixed arr") ==0)
        {
            res = FIXED_ARR;
        }
        else if(strcmp(str,"fixed arr no bin") ==0)
        {
            /*    0x110 FIXED_ARR_NBIN (not build in data element)*/
            res = FIXED_ARR_NBIN;
        }
        else
        {
            res = -1;
        }
    }
    else
    {
        /* do nothing */
    }
    return res;
}
/* compare type   */
int compInt(const void* a,const void *b)
{
    int res =UN_DEFINE;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((int*)a)== *((int*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((int*)a)> (*(int*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((int*)a)< (*(int*)b))
        {
            res =LESS_DEFINE;
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
int compUInt(const void* a,const void *b)
{
    int res =UN_DEFINE;
    if((a!=NULL)&&(b!=NULL))
    {
        
/*
printf("comp: %d %d",*((unsigned int*)a),*((unsigned int*)b));
*/
        if(*((unsigned int*)a)== *((unsigned int*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((unsigned int*)a)> *((unsigned int*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((unsigned int*)a)< *((unsigned int*)b))
        {
            res =LESS_DEFINE;
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
int compVDouble(const void* a,const void *b)
{
    int res =UN_DEFINE;
    int index =0;
    int num =0;
    vector_double *va=NULL,*vb=NULL;
    if((a!=NULL)&&(b!=NULL))
    {
        va = *((vector_double**)a);
        vb = *((vector_double**)b);
        if(va->lenght > vb->lenght)
        {
            num = vb->lenght;
        }
        else
        {
            num = va->lenght;
        }
        res =EQUAL_DEFINE;
        for(index=0;index<num;index++)
        {
            if(va->data[index]> vb->data[index])
            {
                index=num;
                res = MORE_DEFINE;
            }
            else if(va->data[index]< vb->data[index])
            {
                index=num;
                res = LESS_DEFINE;
            }
            else
            {
                /* do nothing */
            }
        }
        if((res ==EQUAL_DEFINE)&&(va->lenght == num)&&(vb->lenght>num))
        {
            res = LESS_DEFINE;
        } 
        else if((res ==EQUAL_DEFINE)&&(vb->lenght == num)&&(va->lenght>num))
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

int compSimStr(const void* a,const void *b)
{
    int res =UN_DEFINE;
    int index =0;
    int num =0;
    simString *sa=NULL,*sb=NULL;
    if((a!=NULL)&&(b!=NULL))
    {
        sa = ((simString*)a);
        sb = ((simString*)b);
        if(sa->length > sb->length)
        {
            num = sb->length;
        }
        else
        {
            num = sa->length;
        }
        res =EQUAL_DEFINE;
        for(index=0;index<num;index++)
        {
            if(sa->data[index]> sb->data[index])
            {
                index=num;
                res = MORE_DEFINE;
            }
            else if(sa->data[index]< sb->data[index])
            {
                index=num;
                res = LESS_DEFINE;
            }
            else
            {
                /* do nothing */
            }
        }
        if((res ==EQUAL_DEFINE)&&(sa->length == num)&&(sb->length>num))
        {
            res = LESS_DEFINE;
        } 
        else if((res ==EQUAL_DEFINE)&&(sb->length == num)&&(sa->length>num))
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
int compLInt(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((long int*)a)== *((long int*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((long int*)a)> *((long int*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((long int*)a)< *((long int*)b))
        {
            res =LESS_DEFINE;
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
int compULInt(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((unsigned long int*)a)== *((unsigned long int*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((unsigned long int*)a)> *((unsigned long int*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((unsigned long int*)a)< *((unsigned long int*)b))
        {
            res =LESS_DEFINE;
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
int compLLInt(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((long long int*)a)== *((long long int*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((long long int*)a)> *((long long int*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((long long int*)a)< *((long long int*)b))
        {
            res =LESS_DEFINE;
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
int compULLInt(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((unsigned long long int*)a)== *((unsigned long long int*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((unsigned long long int*)a)> *((unsigned long long int*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((unsigned long long int*)a)< *((unsigned long long int*)b))
        {
            res =LESS_DEFINE;
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
int compChar(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((char*)a)== *((char*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((char*)a)> *((char*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((char*)a)< *((char*)b))
        {
            res =LESS_DEFINE;
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
int compUChar(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((unsigned char*)a)== *((unsigned char*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((unsigned char*)a)> *((unsigned char*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((unsigned char*)a)< *((unsigned char*)b))
        {
            res =LESS_DEFINE;
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
int compShort(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((short*)a)== *((short*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((short*)a)> *((short*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((short*)a)< *((short*)b))
        {
            res =LESS_DEFINE;
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
int compUShort(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((unsigned short*)a)== *((unsigned short*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((unsigned short*)a)> *((unsigned short*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((unsigned short*)a)< *((unsigned short*)b))
        {
            res =LESS_DEFINE;
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
int compFloat(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((float*)a)== *((float*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((float*)a)> *((float*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((float*)a)< *((float*)b))
        {
            res =LESS_DEFINE;
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
int compDouble(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((double*)a)== *((double*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((double*)a)> *((double*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((double*)a)< *((double*)b))
        {
            res =LESS_DEFINE;
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
int compLDouble(const void* a,const void *b)
{
    int res =0;
    if((a!=NULL)&&(b!=NULL))
    {
        if(*((long double*)a)== *((long double*)b))
        {
            res =EQUAL_DEFINE;
        }
        else if(*((long double*)a)> *((long double*)b))
        {
            res =MORE_DEFINE;
        }
        else if(*((long double*)a)< *((long double*)b))
        {
            res =LESS_DEFINE;
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
int (*getCompFn(const int opCode))(const void*, const void*)
{
    int (*res)(const void*,const void*)=NULL;
    switch(opCode)
    {
        case CHAR_TYPE:  /* char */ 
            res = &compChar;
        break;
        case UCHAR_TYPE:  /* unsigned char */ 
            res = &compUChar;
        break;
        case INT_TYPE: /* int */ 
            res = &compInt;
        break;
        case UINT_TYPE: /* unsigned int */ 
            res = &compUInt;
        break;
        case SHORT_TYPE: /* short */ 
            res = &compShort;
        break;
        case USHORT_TYPE: /* unsigned short */ 
            res = &compUShort;
        break;
        case LINT_TYPE: /* long */ 
            res = &compLInt;
        break;
        case ULINT_TYPE: /* unsigned long */ 
            res = &compULInt;
        break;
        case FLOAT_TYPE: /* float */ 
            res = &compFloat;
        break;
        case DOUBLE_TYPE: /* double */
            res = &compDouble;
        break;
        case LDOUBLE_TYPE: /* long double */ 
            res = &compLDouble;
        break;
        case LLINT_TYPE: /* long long */ 
            res = &compLLInt;
        break;
        case ULLINT_TYPE: /* unsigned long long */ 
            res = &compULLInt;
        break;
        case VDOUBLE_TYPE: /* vector_double */
            res = &compVDouble;
        break;
        case SIMSTRING_TYPE: /* simString */
            res =&compSimStr;
        break;
        case VCHAR_TYPE: /* vector_char*/
            /* not now */
            res =NULL;
        break;
        default:
            res =NULL;
        break;
    }
    return res;
}
