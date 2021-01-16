#ifndef CONVERTDATATYPE_H__
#define CONVERTDATATYPE_H__

struct delimiterSet
{
    char ioBegin; /*0 output before input, 1 input berfore output*/
    int numInput;
    int numOutput;
    char delimiterInput;
    char delimiterOutput;
    char startSymIn;
    char stopSymIn;
    char startSymOut;
    char stopSymOut;
};
typedef struct delimiterSet delimiterSet;
char checkNumberTpyeDSet(char *state,char ch);
void setStpStrtSymDSet(delimiterSet* dS,char pIn,char pOut,char tIn,char tOut);
void constructorDSet(delimiterSet* dSet);
void initialDSet(delimiterSet* dS,char ioB,char dI,char dO,int numO,int numI);
int getAttrbDSet(delimiterSet *ds,const char* buff,double* dat);
int getIODSet(delimiterSet *ds,const char *buff,double *out,double* in);
int get1NumData(char strSym,char stpSym,char deli,const char* buff,double *dat);

int dividedDataAttrbByNullChar(delimiterSet* dS,char* buffer,int *listPos,int numEle,int sizeBuff,int shiftOrder);

int delimiterSetValidate(delimiterSet *ds);

#endif //CONVERTDATATYPE_H__
