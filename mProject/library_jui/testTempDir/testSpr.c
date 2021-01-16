#include "stdio.h"
#include "simMatChar.h"
#include "simSprCharVect.h"
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
/*
int initial_sprVect_temp(sprVect_temp* rhs,SetValue opt);
int countNonZeroEleVect_temp(vector_temp* obj);
int copy_sprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs);
int copy_sprVect_vect_temp(sprVect_temp* rhs,vector_temp* lhs);
int check_sprVect_tempObj(sprVect_temp* obj);
int makeEmptySprVect_temp(sprVect_temp* obj);
void deleteSprVect_temp(sprVect_temp* obj);
int convertSpr2Vect_temp(vector_temp *rhs,sprVect_temp* lhs);
int convertVect2Spr_temp(sprVect_temp* rhs,vector_temp* lhs);

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
*/
int main(int argc,char** argv)
{
	char res1  	  = 0;
	vector_char v1	  = new_vector_char(0);
	vector_char v2	  = new_vector_char(0);
	sprVect_char spr1 = new_sprVect_char(0);
	sprVect_char spr2 = new_sprVect_char(0);
	v1		  = new_vector_char(24);
	v2		  = new_vector_char(16);
	SetValue set	  = {3,2,0};
	initial_vector_char(&v1,set);
	set.min = 5;
	set.max = 0;
	initial_vector_char(&v2,set);
	v2.data[8] =5;
	v2.data[14] = 31;

	printf("v1 :");
	print_vector_char(&v1,4);
	printf("v2 :");
	print_vector_char(&v2,4);
	printf("\n--------------------------------------\n");

	spr1 		  = new_sprVect_charCopyVect(&v1); 
	spr2 		  = new_sprVect_charCopyVect(&v2); 
	
	printf("spr1 :");
	printSprVect_char(&spr1,0x00da);
	printf("spr2 :");
	printSprVect_char(&spr2,0x00da);
	printf("\n--------------------------------------\n");
	
	printf("plus spr1 = spr2+spr1 \n");
	plusSprVect_char(&spr2,&spr1,&spr1);
	printSprVect_char(&spr1,0x004a);
	printf("\n--------------------------------------\n");

	spr2.data[3] = 10;
	printf("spr2.data: %d index:%d\n",spr2.data[3],spr2.id[3]);
	printf("spr2 = spr1-spr2 \n");
	subSprVect_char(&spr2,&spr1,&spr2);
	printSprVect_char(&spr2,0x004a);
	printf("\n--------------------------------------\n");

	printf("spr2 = spr2 -v1 \n");
	subSprVect_vect_char(&spr2,&v1,&spr2);
	printSprVect_char(&spr2,0x004a);
	printf("\n-------------%p-------------------------\n",spr2.data);

	printf(":dot : res1 = <spr2,spr1>\n");
	dotProduct_sprVect_char(&spr2,&spr1,&res1);
	printf("dot Pro: %d\n",res1);
	printf("\n--------------------------------------\n");

	v2.data[3] = -v2.data[3];
	v2.data[7] = -v2.data[7];
	v2.data[11] = -v2.data[11];
	v2.data[15] = -v2.data[15];
	printf(":dot : res1 = <spr2,v2>\n");
	dotProduct_sprVect_Vect_char(&spr2,&v2,&res1);
	printf("dot Pro: %d\n",res1);
	printf("\n--------------------------------------\n");
	printf("plus spr1 = spr2+spr1 \n");
	plusSprVect_char(&spr2,&spr1,&spr1);
	printSprVect_char(&spr1,0x004a);
	printf("\n--------------------------------------\n");

	printf("plus spr1 = spr1+spr1 \n");
	plusSprVect_char(&spr1,&spr1,&spr1);
	printSprVect_char(&spr1,0x004a);
	printf("\n--------------------------------------\n");

	printf("sub spr2 = spr2-spr1 \n");
	subSprVect_char(&spr2,&spr1,&spr2);
	printSprVect_char(&spr2,0x004a);
	printf("\n--------------------------------------\n");
	printf("sub spr1 = spr1-spr1 \n");
	subSprVect_char(&spr1,&spr1,&spr1);
	printSprVect_char(&spr1,0x004a);
	printf("\n--------------------------------------\n");
	printf("comp spr1 vs spr1\n");
	printf(" %s\n",(compSprVect_char(&spr1,&spr1)==1)?"equal":"not equal");
	printf("\n--------------------------------------\n");
	printf("comp spr2 vs spr1\n");
	printf(" %s\n",(compSprVect_char(&spr2,&spr1)==1)?"equal":"not equal");
	printf("\n--------------------------------------\n");

	printf(":dot : res1 = <spr2,spr1>\n");
	dotProduct_sprVect_char(&spr2,&spr1,&res1);
	printf("dot Pro: %d\n",res1);
	printf("\n--------------------------------------\n");

	printf("spr1 = spr1 -v1 \n");
	subSprVect_vect_char(&spr1,&v1,&spr1);
	printSprVect_char(&spr1,0x004a);
	printf("\n--------------------------------------\n");

	printf("comp v1 vs spr1\n");
	printf(" %s\n",(compSprVect_Vect_char(&spr1,&v1)==1)?"equal":"not equal");
	printf("\n--------------------------------------\n");
	printf("comp spr1 vs spr1\n");
	printf(" %s\n",(compSprVect_char(&spr1,&spr1)==1)?"equal":"not equal");
	printf("\n--------------------------------------\n");

	deleteSprVect_char(&spr2);
	delete_vector_char(&v1);
	delete_vector_char(&v2);
	deleteSprVect_char(&spr1);
	return 0;
}
