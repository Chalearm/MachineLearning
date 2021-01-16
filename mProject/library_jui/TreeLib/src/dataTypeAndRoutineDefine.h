#ifndef DATATYPEANDROUTINE_H_
#define DATATYPEANDROUTINE_H_
#include "simMatDouble.h"
#include "simString.h"
 /* binary tree */
 /*defined 
    use  12 bits
    last nibble
    0 = sign
    1 = unsign
    2 = special (ascii, etc)
    0x000 char
    0x010 int
    0x020 short
    0x030 long
    0x040 float
    0x050 double
    0x060 long double
    0x070 vector_char
    0x080 simString
    0x090 long long int
    0x0D0 custom type 1
    0x0E0 custom type 2
    0x0F0 VDOUBLE_TYPE
    0x100 FIXED_ARR
    0x110 FIXED_ARR_NBIN (not build in data element)
*/
#define CHAR_TYPE 0x000
#define UCHAR_TYPE 0x001
#define INT_TYPE 0x010
#define UINT_TYPE 0x011
#define SHORT_TYPE 0x020
#define USHORT_TYPE 0x021
#define LINT_TYPE 0x030
#define ULINT_TYPE 0x031
#define FLOAT_TYPE 0x040
#define DOUBLE_TYPE 0x050
#define LDOUBLE_TYPE 0x060
#define VCHAR_TYPE 0x070
#define SIMSTRING_TYPE 0x080
#define LLINT_TYPE 0x090
#define ULLINT_TYPE 0x091
#define CUS1_TYPE 0x0D0
#define CUS2_TYPE 0x0E0
#define VDOUBLE_TYPE 0x0F0
#define FIXED_ARR 0x100
#define FIXED_ARR_NBIN 0x110
#define MORE_DEFINE 1
#define LESS_DEFINE -1
#define EQUAL_DEFINE 0
#define UN_DEFINE -2

int getDataTypeSize(int type);
int getDataTypeFromString(const char* str);

int (*getCompFn(const int opCode))(const void*, const void*);
/* compare type  0 equal,-1 less,1 more*/
int compInt(const void* a,const void *b);
int compUInt(const void* a,const void *b);
int compLInt(const void* a,const void *b);
int compULInt(const void* a,const void *b);
int compLLInt(const void* a,const void *b);
int compULLInt(const void* a,const void *b);
int compChar(const void* a,const void *b);
int compUChar(const void* a,const void *b);
int compShort(const void* a,const void *b);
int compUShort(const void* a,const void *b);
int compFloat(const void* a,const void *b);
int compDouble(const void* a,const void *b);
int compLDouble(const void* a,const void *b);
int compVDouble(const void* a,const void *b);
int compSimStr(const void* a,const void *b);
#endif
