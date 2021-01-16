#ifndef TREEDEFINE_H_
#define TREEDEFINE_H_

#include "simMat2.h"
struct nodeBinaryInt 
{
    struct nodeBinaryInt *left;
    struct nodeBinaryInt *right;
    int key;
}; 
struct nodeBinaryLInt 
{
    struct nodeBinaryLInt *left;
    struct nodeBinaryLInt *right;
    long int key;
};  
struct nodeBinaryULInt 
{
    struct nodeBinaryULInt *left;
    struct nodeBinaryULInt *right;
    unsigned long int key;
}; 
 struct nodeBinaryChar
{
    struct nodeBinaryChar *left;
    struct nodeBinaryChar *right;
    char key;
};
struct nodeBinaryUInt
{
    struct nodeBinaryUInt *left;
    struct nodeBinaryUInt *right;
    unsigned int key;
}; 
 struct nodeBinaryUChar
{
    struct nodeBinaryUChar *left;
    struct nodeBinaryUChar *right;
    unsigned char key;
};

struct nodeBinaryFloat
{
    struct nodeBinaryFloat *left;
    struct nodeBinaryFloat *right;
    float key;
}; 
struct nodeBinaryShort
{
    struct nodeBinaryShort *left;
    struct nodeBinaryShort *right;
    short key;
};
struct nodeBinaryUShort
{
    struct nodeBinaryUShort *left;
    struct nodeBinaryUShort *right;
    unsigned short key;
};
struct nodeBinaryULLInt
{
    struct nodeBinaryULLInt *left;
    struct nodeBinaryULLInt *right;
    unsigned long long int key;
};
struct nodeBinaryLLInt
{
    struct nodeBinaryLLInt *left;
    struct nodeBinaryLLInt *right;
    long long int key;
};
struct nodeBinaryDouble
{
    struct nodeBinaryDouble *left;
    struct nodeBinaryDouble *right;
    double key;
};
struct nodeBinaryLDouble
{
    struct nodeBinaryLDouble *left;
    struct nodeBinaryLDouble *right;
    long double key;
};
/* customize */
struct nodeBinaryPVoid
{
    struct nodeBinaryPVoid *left;
    struct nodeBinaryPVoid *right;
    void* key;
};
struct nodeBinaryPVoidWithData
{
    struct nodeBinaryPVoidWithData *left;
    struct nodeBinaryPVoidWithData *right;
    void* key;
    void* data;
}; 

typedef struct nodeBinaryInt nodeBinaryInt;
typedef struct nodeBinaryLInt nodeBinaryLInt;
typedef struct nodeBinaryULInt nodeBinaryULInt;
typedef struct nodeBinaryChar nodeBinaryChar;
typedef struct nodeBinaryUInt nodeBinaryUInt;
typedef struct nodeBinaryUChar nodeBinaryUChar;
typedef struct nodeBinaryFloat nodeBinaryFloat;
typedef struct nodeBinaryShort nodeBinaryShort;
typedef struct nodeBinaryUShort nodeBinaryUShort;
typedef struct nodeBinaryULLInt nodeBinaryULLInt;
typedef struct nodeBinaryLLInt nodeBinaryLLInt;
typedef struct nodeBinaryDouble nodeBinaryDouble;
typedef struct nodeBinaryLDouble nodeBinaryLDouble;
typedef struct nodeBinaryPVoid nodeBinaryPVoid;
typedef struct nodeBinaryPVoidWithData nodeBinaryPVoidWithData;
typedef struct nodeFixedArr nodeFixedArr;
typedef struct nodeFixedArrNBIn nodeFixedArrNBIn;

#endif