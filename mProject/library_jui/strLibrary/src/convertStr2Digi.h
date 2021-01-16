#ifndef CONVERTSTR2DIGI_H__
#define CONVERTSTR2DIGI_H__

#include <stdio.h>
#include "simMatChar.h"
long long str2Int(const char* str);
long long str2Int2(const char* str,int size);
long long str2IntV_char(vector_char* vec);
long long str2Int3(const char* str,int size,char* isNum);

long double _double_fraction(const char* str,int size);
long double str2Double(const char* str);
long double str2Double2(const char* str,int size);
long double str2Double3(const char* str,int size,char* isConvert);
long double str2DoubleWithBoolean(const char* str,char *isConvert);
long double str2DoubleV_char(vector_char* vec);

vector_char cStr2V_char(const char *str);
#endif //CONVERTSTR2DIGI_H__

