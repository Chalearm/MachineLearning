#include <stdio.h>
#include "simMatDouble.h"
#define NUM_INPUT 5 
#define DIM_INPUT 6
void testTraining(vector_double* a,vector_double* b);
void biasConstraint(vector_double* a,double *b,double *c);
void weightCal(vector_double* lagrange,double* out,vector_double* in,vector_double* w);
int main(int argc,char** argv)
{
	int index = 0,index2 =0;
	double dummyDot = 0.0;
	SetValue set = {2,1,1};
	SetValue set2 = {0,0,0};
	vector_double input[NUM_INPUT];
	matrix_double dualMatrix = new_matrix_double(NUM_INPUT,NUM_INPUT);
	matrix_double matInv = new_matrix_double(NUM_INPUT,NUM_INPUT);
	vector_double anws = new_vector_double(NUM_INPUT);
	vector_double anws2 = new_vector_double(NUM_INPUT);
	vector_double w = new_vector_double(DIM_INPUT);
	double output[NUM_INPUT];
	for(index = 0;index < NUM_INPUT;index++)
	{
		anws2.data[index] = 0;
		input[index] = new_vector_double(DIM_INPUT);
	}
	initial_vector_double(&anws,set);
	initial_vector_double(&w,set2);
	input[0].data[0] = 0.5;
	input[0].data[1] = -2.135;
	input[0].data[2] = 0.442;
	input[0].data[3] = 4;
	input[0].data[4] = 1;
	input[0].data[5] = 2;
	output[0] 	 = 1;
	input[1].data[0] = -0.11;
	input[1].data[1] = -1.11;
	input[1].data[2] = -0.01;
	input[1].data[3] = 1.5;
	input[1].data[4] = -1;
	input[1].data[5] = 0.5;
	output[1] 	 = 1;
	input[2].data[0] = -7;
	input[2].data[1] = 1.2;
	input[2].data[2] = 3;
	input[2].data[3] = 1.9;
	input[2].data[4] = 0.7;
	input[2].data[5] = 0.1;
	output[2] 	 = 1;
	input[3].data[0] = -1;
	input[3].data[1] = -2;
	input[3].data[2] = -3.11;
	input[3].data[3] = -1.0;
	input[3].data[4] = 0.555;
	input[3].data[5] = -1.1;
	output[3] 	 = -1;
	input[4].data[0] = 0.363;
	input[4].data[1] = 2;
	input[4].data[2] = 0.82;
	input[4].data[3] = 1.12;
	input[4].data[4] = 5.55;
	input[4].data[5] = -1.314;
	output[4] 	 = -1;
	
	for(index =0 ;index <dualMatrix.row;index++)
	 for(index2 =0;index2 <dualMatrix.col;index2++)
	 {
	multiply_vt_v_double(&input[index],&input[index2],&dummyDot);
	dualMatrix.data[index][index2] = output[index]*output[index2]*dummyDot;
	 }
//	print_matrix_double(&dualMatrix,2);
//	printf("*---------------------------------------*\n");
	dummyDot = determinant(&dualMatrix);
//	printf("det: %0.13f\n",dummyDot);
	matrixInverse(&dualMatrix,&matInv);
//	printf("*-----------Inver----------------------------*\n");
//	print_matrix_double(&matInv,2);
	multiply_m_v_double(&matInv,&anws,&anws2);
//	printf("*---------Lagrange Multipier----------*\n");
//	print_vector_double(&anws2,2);
//	printf(" sigma alpha*yi \n");
	biasConstraint(&anws2,output,&dummyDot);
//	printf("sigma alpha*yi : %0.8f\n",dummyDot);
	weightCal(&anws2,output,input,&w);
	printf("w : \n");
	print_vector_double(&w,2);
	testTraining(&w,input);
	for(index = 0;index <NUM_INPUT;index++)
	{
		delete_vector_double(&input[index]);
	}
	delete_matrix_double(&dualMatrix);
	delete_matrix_double(&matInv);
	delete_vector_double(&anws);
	delete_vector_double(&anws2);
	delete_vector_double(&w);
return 0;
}
void biasConstraint(vector_double* a,double *b,double *c)
{
	int index =0 ;
	*c = 0.0;
	for(index = 0 ;index < a->lenght;index++)
	{
		*c += a->data[index]*b[index];
	}
}
void weightCal(vector_double* lagrange,double* out,vector_double* in,vector_double* w)
{
	
	vector_double anws = new_vector_double(NUM_INPUT);
	vector_double anws2 = new_vector_double(DIM_INPUT);
	int index =0;
	for(index =0;index < lagrange->lenght;index++)
	{
		anws.data[index] = lagrange->data[index]*out[index];
		scalarmultiply_v_double(&in[index],&anws.data[index],&anws2);
		plus_v_double(w,&anws2,w);
	}
	delete_vector_double(&anws);
}
void testTraining(vector_double* a,vector_double* b)
{
	int index=0;
	double anws =0.0;
	for(index =0 ;index<NUM_INPUT;index++)
	{
		multiply_vt_v_double(a,&b[index],&anws);
		printf("%0.9f \n",anws);
//		print_vector_double(&b[index],4);
	}
		
}
