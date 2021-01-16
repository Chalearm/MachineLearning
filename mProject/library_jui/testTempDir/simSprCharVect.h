#ifndef SIMSPRCHARVECT_H_
#define SIMSPRCHARVECT_H_
#include "simMatChar.h"
#include "initObj.h"
/* 
typedef struct{
	char set;
	double max;
	double min;
} SetValue;
--------set initialize-----
 set =0  all element =0;
 set =1  random range(max,min)
 set =2  a,b  ---> a=max or min ,b=max or min
 set =3  run number (min -->max)
 set =4  Identify matrix or range 

*/
// 0 is false 1 is true
typedef unsigned short usint;
struct sprVect_char 
{
	usint lenght;
	int *id;
	element *data;
};
typedef struct sprVect_char sprVect_char;
int initial_sprVect_char(sprVect_char* rhs,SetValue opt);
sprVect_char new_sprVect_char(int lenght); 
sprVect_char new_sprVect_charCopyVect(vector_char* obj); 
int countEleVect_char(vector_char* obj,int set);
int countSameElesSprVect_char(sprVect_char* rhs,sprVect_char*lhs,int set);
int countSameElesSprVect_vector_char(sprVect_char* rhs,vector_char* lhs,int set);
int copy_sprVect_char(sprVect_char* rhs,sprVect_char* lhs);
int copy_sprVect_vect_char(sprVect_char* rhs,vector_char* lhs);
int check_sprVect_charObj(sprVect_char* obj);
int makeEmptySprVect_char(sprVect_char* obj);
void deleteSprVect_char(sprVect_char* obj);
int convertSpr2Vect_char(vector_char *rhs,sprVect_char* lhs);
int convertVect2Spr_char(sprVect_char* rhs,vector_char* lhs);

void printSprVect_char(sprVect_char* rhs,int opt);

int countIntersectIdSprVect_char(sprVect_char* rhs,sprVect_char* lhs);
int countIntersectIdSprVect_char_vect_char(sprVect_char* rhs,vector_char* lhs);
//arithmetic operation
int compSprVect_char(sprVect_char* rhs,sprVect_char* lhs);
int compSprVect_Vect_char(sprVect_char* rhs,vector_char* lhs);
int dotProduct_sprVect_char(sprVect_char* rhs,sprVect_char* lhs,element *res);
int dotProduct_sprVect_Vect_char(sprVect_char* rhs,vector_char* lhs,element *res);
int plusSprVect_char(sprVect_char* rhs,sprVect_char* lhs,sprVect_char *res);
int plusSprVect_vect_char(sprVect_char* rhs,vector_char* lhs,sprVect_char *res);
int subSprVect_char(sprVect_char* rhs,sprVect_char* lhs,sprVect_char *res);
int subSprVect_vect_char(sprVect_char* rhs,vector_char* lhs,sprVect_char *res);
#endif
