#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simMatDouble.h"

int main(int argc,char** argv)
{
	usint i,j;
	srand((unsigned int)time(NULL));
	SetValue set1 ={3,30,0.0};
	SetValue set2 ={2,11.0,7};
	double scale1,scale2;
	scale1=2.0;
	scale2=0.5;

	vector_double v1= new_vector_double(5);

	vector_double v2= new_vector_double(5);
	vector_double v3= new_vector_double(5);

	matrix_double m1= new_matrix_double(3,5);
	matrix_double m2= new_matrix_double(3,5);
	matrix_double m3= new_matrix_double(3,5);


	initial_vector_double(&v1,set1);
	initial_vector_double(&v2,set2);

	initial_matrix_double(&m1,set1);
	initial_matrix_double(&m2,set2);
	
	print_vector_double(&v1,0);
	print_vector_double(&v2,0);
	print_matrix_double(&m1,0);
	print_matrix_double(&m2,0);

	dotmultiply_v_double(&v1,&v2,&v3);
	scalarmultiply_v_double(&v3,&scale1,&v3);
	dotmultiply_m_double(&m1,&m2,&m3);
	scalarmultiply_m_double(&m3,&scale2,&m3);

	plus_v_double(&v3,&v1,&v3);
	plus_m_double(&m3,&m1,&m3);

	minus_v_double(&v3,&v1,&v3);
	minus_m_double(&m3,&m1,&m3);
	print_vector_double(&v3,0);
	print_matrix_double(&m3,0);
		
delete_vector_double(&v1);
delete_vector_double(&v2);
delete_vector_double(&v3);
delete_matrix_double(&m1);
delete_matrix_double(&m2);
delete_matrix_double(&m3);
return 0;
}
