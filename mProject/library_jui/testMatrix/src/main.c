#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "simMatDouble.h"
#include "listPvoid.h"
#define MN_SQR_MATRIX 6




void testMatrix();

int main(int argc,char **argv)
{
    srand(time(NULL));
    testMatrix();

    return 0;
}




void testMatrix()
{
    int retGauss = 0;
SetValue vect_rang11 = {1,5,-5};
SetValue vect_rang12 = {3,0,0};
    matrix_double intM1 =  new_matrix_double(MN_SQR_MATRIX,MN_SQR_MATRIX);
    matrix_double retm1 =  new_matrix_double(MN_SQR_MATRIX,MN_SQR_MATRIX);
    matrix_double retm2=  new_matrix_double(MN_SQR_MATRIX,MN_SQR_MATRIX);
    matrix_double retm3=  new_matrix_double(MN_SQR_MATRIX,MN_SQR_MATRIX);
    initial_matrix_double(&intM1,vect_rang11);
    initial_matrix_double(&retm1,vect_rang12);
    intM1.data[0][0] = 0;
    print_matrix_double(&intM1,7);
    retGauss = GaussElimination(&intM1,&retm1,MN_SQR_MATRIX,1);
    print_matrix_double(&retm1,7);
    
        printf("Cal Inverse Matrixt ====================\n");
    matrixInverse2(&intM1,&retm2);
    
        print_matrix_double(&retm2,7);
        multiply_m_m_double(&intM1,&retm2,&retm3);
        
        print_matrix_double(&retm3,7);
    
        printf("Cal Det of Matrixt ====================\n");
    
    printf("det(A):%0.20f \n",determinant2(&intM1,&retm1));
    printf("det(B):%0.20f \n",determinant(&intM1));

    delete_matrix_double(&intM1);
    delete_matrix_double(&retm1);
    delete_matrix_double(&retm2);
    delete_matrix_double(&retm3);
    printf("retGauss : %d\n",retGauss);
}