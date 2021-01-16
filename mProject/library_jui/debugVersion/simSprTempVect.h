#ifndef SIMSPRTEMPVECT_H_
#define SIMSPRTEMPVECT_H_
#include "simMatTemp.h"
#include "initObj.h"
/* 
typedef struct{
	temp set;
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
struct sprVect_temp 
{
	usint lenght;
	int *id;
	element *data;
};
typedef struct sprVect_temp sprVect_temp;
int initial_sprVect_temp(sprVect_temp* rhs,SetValue opt);
sprVect_temp new_sprVect_temp(int lenght); 
sprVect_temp new_sprVect_tempCopyVect(vector_temp* obj); 
int countEleVect_temp(vector_temp* obj,int set);
int countSameElesSprVect_temp(sprVect_temp* rhs,sprVect_temp*lhs,int set);
int countSameElesSprVect_vector_temp(sprVect_temp* rhs,vector_temp* lhs,int set);
int copy_sprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs);
int copy_sprVect_vect_temp(sprVect_temp* rhs,vector_temp* lhs);
int check_sprVect_tempObj(sprVect_temp* obj);
int makeEmptySprVect_temp(sprVect_temp* obj);
void deleteSprVect_temp(sprVect_temp* obj);
int convertSpr2Vect_temp(vector_temp *rhs,sprVect_temp* lhs);
int convertVect2Spr_temp(sprVect_temp* rhs,vector_temp* lhs);

void printSprVect_temp(sprVect_temp* rhs,int opt);

int countIntersectIdSprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs);
int countIntersectIdSprVect_temp_vect_temp(sprVect_temp* rhs,vector_temp* lhs);
//arithmetic operation
int compSprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs);
int compSprVect_Vect_temp(sprVect_temp* rhs,vector_temp* lhs);
int dotProduct_sprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs,element *res);
int dotProduct_sprVect_Vect_temp(sprVect_temp* rhs,vector_temp* lhs,element *res);
int plusSprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs,sprVect_temp *res);
int plusSprVect_vect_temp(sprVect_temp* rhs,vector_temp* lhs,sprVect_temp *res);
int subSprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs,sprVect_temp *res);
int subSprVect_vect_temp(sprVect_temp* rhs,vector_temp* lhs,sprVect_temp *res);
#endif
