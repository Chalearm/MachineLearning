#include "convertDataType.h"
#include "convertStr2Digi.h"
#include "string.h"
void constructorDSet(delimiterSet* dSet)
{
    if(dSet !=NULL)
    {
        dSet->ioBegin        = 0;
        dSet->numInput       = 0;
        dSet->numOutput      = 0;
        dSet->delimiterInput = '\0';
        dSet->delimiterOutput= '\0';
        dSet->startSymIn     = -1;
        dSet->stopSymIn      = -1;
        dSet->startSymOut    = -1;
        dSet->stopSymOut     = -1;
    }
    else
    {
        /* do nothing */
    }
}
void initialDSet(delimiterSet* dSet,char ioB,char dI,char dO,int numO,int numI)
{
    dSet->ioBegin        = ioB;
    dSet->numInput       = numI;
    dSet->numOutput      = numO;
    dSet->delimiterInput = dI;
    dSet->delimiterOutput= dO;
}
/* long double str2Double(const char* str); */
int getAttrbDSet(delimiterSet *ds,const char* buff,double* dat)
{
    int numAttrb   =0;
    int index      =0;
    char delimiter = '\0';
    int index2     =0;
    int dummy1;
    char stSym      =-1;
    char spSym      =-1;
    if(buff == NULL || dat == NULL || ds==NULL)
    {
        return -1;
    }
    else
    {
        /* do nothing;*/
    }
    if(ds->numOutput <= 0 && ds->numInput <=0)
    {
        return -1;
    }
    else
    {
        //do nothing
    }
    if(ds->numOutput <=0)
    {
        spSym    = ds->stopSymIn;
        stSym    = ds->startSymIn;
        numAttrb = ds->numInput;
        delimiter= ds->delimiterInput;
    }
    else
    {
        spSym    = ds->stopSymOut;
        stSym    = ds->startSymOut;
        numAttrb = ds->numOutput;
        delimiter= ds->delimiterOutput;
    }
    index2 =0;
    while(index2 < numAttrb)
    {
        dummy1 = get1NumData(stSym,spSym,delimiter,&buff[index],&dat[index2++]);
        if(dummy1 == -1)
        {
            printf("error syntax \n");
        }
        else
        {
            /* do nothing */
        }
        index += dummy1;
        index++;
    }
    return 1; /* ok */
}
int getIODSet(delimiterSet *ds,const char* buff,double *out,double* in)
{
    int index =0;
    int index2=0;
    int index3=0;
    int setIo = -1;
    char fact1,fact2;
    char st,sp,de;
    int dummy1=0;
    if(buff == NULL || out==NULL || in==NULL)
    {
        printf(" error parameter  NULL\n");
        return -1;
    }
    else
    {
        /* do nothing */
    }
    if(ds->numOutput <= 0 || ds->numInput <=0)
    {
        printf(" error parameter  0\n");
        return -1;
    }
    else
    {
        /* do nothing */
    }
    setIo = ds->ioBegin;
    index2 =0;
    for(index =0;index <2;index++) /* 2 = i and o */
    {
    fact1 = (setIo ==0);
    fact1 = fact1 && (ds->startSymOut ==-1||buff[index2] ==ds->startSymOut);
    fact2 = (setIo ==1);
    fact2 = fact2 &&(ds->startSymIn ==-1|| buff[index2] ==ds->startSymIn);

        index3 =0;
        if(fact2 ==1)
        {
            sp = ds->stopSymIn;
            st = ds->startSymIn;
            de = ds->delimiterInput;
            while(index3<ds->numInput)
            {
                dummy1 = get1NumData(st,sp,de,&buff[index2],&in[index3++]);
                if(dummy1 == -1)
                {
                    printf("error systax In\n");
                    return -1;
                }
                else
                {
                    /* do nothing */
                }
                index2 += dummy1;
                index2++;
                
            }
            setIo =0;
        }
        else if(fact1 ==1)
        {
            sp = ds->stopSymOut;
            st = ds->startSymOut;
            de = ds->delimiterOutput;
            while(index3<ds->numOutput)
            {
                dummy1 = get1NumData(st,sp,de,&buff[index2],&out[index3++]);
                if(dummy1 == -1)
                {
                    printf("error systax Out\n");
                    return -1;
                }
                else
                {
                    /* do nothing */
                }
                index2 += dummy1;
                index2++;
                
            }
            setIo =1;
        }
        else
        {
            printf("error io \n");
            return -1;
        }
    }
    return 1; /*ok;*/
}

int dividedDataAttrbByNullChar(delimiterSet* dS,char* buffer,int *listPos,int numEle,int sizeBuff,int shiftOrder)
{
    int res = 0;
    char symStr1,symStr2,symStop1,symStop2;
    char deli1,deli2;
    char ch=0;
    char fact1=0;
    int index=0;
    int num1,num2;
    int count1=0;
    int count2=0;
    int numAttrb =0;
    int states =0; 
    if((dS != NULL)&&(shiftOrder>=0)&&(shiftOrder<numEle)&&(buffer != NULL)&&(listPos!=NULL)&&(numEle>0)&&(sizeBuff > strlen(buffer)))
    {
        res =1;
        numAttrb = dS->numInput + dS->numOutput;
        if(dS->ioBegin ==0)/*0 output before input, 1 input berfore output*/
        {
            symStr1 = dS->startSymOut;
            symStop1=dS->stopSymOut;
            symStr2 = dS->startSymIn;
            symStop2=dS->stopSymIn;
            deli1 = dS->delimiterOutput;
            deli2 = dS->delimiterInput;
            num1 = dS->numOutput;
            num2 = dS->numInput;
        }
        else if(dS->ioBegin ==1)
        {
            symStr2 = dS->startSymOut;
            symStop2=dS->stopSymOut;
            symStr1= dS->startSymIn;
            symStop1=dS->stopSymIn;
            deli2 = dS->delimiterOutput;
            deli1 = dS->delimiterInput;
            num2 = dS->numOutput;
            num1 = dS->numInput;
        }
        else
        {
            res =0;
        }
        if((numEle==numAttrb)&&(res==1))
        {
            /* eliminate junk at the end buffer */
            index = strlen(buffer)-1; /* skip '\0' */
            fact1 = 1;
            while(fact1 ==1)
            {
                ch = buffer[index] ;
                fact1 = (ch==symStr2)||(ch==deli2)||(ch==symStop2)||(ch=='\r')||(ch=='\n')||(ch=='\t')||(ch==' ');
                if(fact1 ==1)
                {
                    buffer[index]  = '\0';
                }
                else
                {
                    /* do nothing */
                }
                index--;
                if(index<0)
                {
                    break;
                }
                else
                {
                    /* do nothing */
                }
            }
            states =1;
            for(index=0;(buffer[index]!='\0')&&(res==1)&&(index<sizeBuff);index++)
            {
                ch = buffer[index] ;
                if(count1<num1)
                {
                    fact1 = (ch==symStr1)||(ch==deli1)||(ch==symStop1);
                }
                else if(count2<num2)
                {
                    fact1 = (ch==symStr2)||(ch==deli2)||(ch==symStop2);
                    if(count2 ==0)
                    {
                        fact1 = fact1||(ch==symStr1)||(ch==deli1)||(ch==symStop1);
                    }
                    else
                    {
                        /* do nothing */
                    }
                }
                if(fact1==1)
                {
                    states=1;
                    buffer[index] = '\0';
                }
                else
                { 
                    /* do nothing */
                }
                if((states==1) && (!fact1))
                {
                    states =0;
                    if(shiftOrder >0)
                    {
                        shiftOrder--;
                    }
                    else if(count1<num1)
                    {
                        if((dS->ioBegin ==1)||(dS->ioBegin ==0))
                        {
                            listPos[count1++] =index;
                        }
                        else
                        {
                            res =0;
                            printf("%d res: %d\n",__LINE__,res);
                        }
                   }
                   else if(count2<num2)
                   {
                        if((dS->ioBegin ==1)||(dS->ioBegin ==0))
                        {
                            listPos[count1+count2++] =index;
                        }
                        else
                        {
                            res =0;
                            printf("%d res: %d\n",__LINE__,res);
                        }
                       
                   }
                   else if((count1==num1)&&(count2==num2))
                   {
                        break;
                   }
                   else
                   {
                        res =0;
                        printf("%d res: %d\n",__LINE__,res);
                   }
                }
                else
                {
                    /* do nothing */
                }
            }
        }
        else
        {
            res=0;
        }
    }
    else
    {
        res =0;
    }
 
    return res;
}

char checkNumberTpyeDSet(char *state,char ch)
{

    if(ch >= '0' && ch <='9')
    {
        if(*state == 0)
        {
            *state = 1;
        }
        else
        {
            
        }
        return 1;
    }
    else if(*state ==0 && ch =='-')
    {
        *state =1;
        return 1;
    }
    else if(*state ==0 && ch =='.')
    {
        *state =2;
        return 1;
    }
    else if(*state ==1 && ch=='.')
    {
        *state =2;
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}
void setStpStrtSymDSet(delimiterSet* dS,char pIn,char pOut,char tIn,char tOut)
{
    dS->startSymIn     = tIn;
    dS->stopSymIn      = pIn; 
    dS->startSymOut    = tOut;
    dS->stopSymOut     = pOut;
}
int get1NumData(char strSym,char stpSym,char deli,const char* buff,double *dat)
{
    int index =0;
    int index2 =0;
    char state2 =0;
    char state =0;
    char fact1 =0;
    char isNum =0;
    char buff2[40];
    index =0;
    do
    {
        fact1 = (strSym == buff[index]);
        fact1 = fact1 && (strSym != -1);
        if(fact1 ==1&& state2==0)
        {
            state2 =1;
            index++;
            continue;
        }
        else if(fact1 ==1 && state2 ==1)
        {
            printf("syntax error\n");
            return -1;
        }
        else
        {
          isNum = checkNumberTpyeDSet(&state,buff[index]);
        }
        fact1 = (buff[index]==stpSym) && (stpSym != -1);
        if(buff[index] ==deli ||fact1 ==1 ||buff[index]=='\0')
        {
            buff2[index2] ='\0';
            *dat=(double)str2Double(buff2);
            return index; // index
            
        }
        else if(isNum ==1)
        {
            buff2[index2++] = buff[index];	
        }
        else if(isNum ==0)
        {
            continue;
        }
        index++;
    }while(buff[index-1]!='\0');
    printf(" failed to convert\n");
    return -1;
}
int delimiterSetValidate(delimiterSet *ds)
{
    int res =0;
    char ioBeginFact=0;
    char isInput =0;
    char isOuput =0;
    char deliInpValid=0;
    char deliOutpValid=0;
    char strStopInValid=0;
    char strStopOutValid=0;
    char numInpMore0=0;
    char numOutpMore0=0;

    if(ds!=NULL)
    {
        isInput=ds->ioBegin==1;
        isOuput=ds->ioBegin==0;
        strStopInValid = (ds->startSymIn>0)||(ds->stopSymIn>0);
        strStopOutValid = (ds->startSymOut>0)||(ds->stopSymOut>0);
        numInpMore0 =ds->numInput>0;
        numOutpMore0 =ds->numOutput>0;
        deliInpValid =ds->delimiterInput;
        deliOutpValid =ds->delimiterOutput;
        ioBeginFact = isInput||isOuput;
        /*
       printf("strIn : %d %c\n",ds->startSymIn,ds->startSymIn);
       printf("stopIn : %d %c\n",ds->stopSymIn,ds->stopSymIn);
       printf("strOut : %d %c\n",ds->startSymOut,ds->startSymOut);
       printf("stopOut: %d %c\n",ds->stopSymOut,ds->stopSymOut);
       */
        /*
        5 facts
            I>0
            O>0
            Deli input valid
            Deli Output valid
            Input before output (no affect)
        */
        res = (!numInpMore0)&&(numOutpMore0)&&(!(deliInpValid||strStopInValid))&&(strStopOutValid||deliOutpValid);
        res = res||((numOutpMore0)&&(deliInpValid||strStopInValid)&&(strStopOutValid||deliOutpValid));
        res = res||((numInpMore0)&&(!numOutpMore0)&&(deliInpValid||strStopInValid));
        res = res&&(ds->numInput>=0)&&(ds->numOutput>=0)&&ioBeginFact;
    }
    else
    {
        /* do nothing */
    }
    return res;
}