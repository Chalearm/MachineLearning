#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "simMatDouble.h"
#include "listPvoid.h"
#define POLYFACTOR 3
#define SIGMA 0.000656
#define C_ALPHA 5000
#define GUASSIAN_DIVIDER (-2.0)*pow(SIGMA,2)

#define MN_SQR_MATRIX 6


#define VECT_DIM 4
#define NUM_DAT 6
SetValue vect_rang = {1,100.0,-100.0};

vector_double vBuff;
vector_double vBuffAlpha;
vector_double vBuffAll1;
matrix_double mBuff;
matrix_double mBuff2;

struct inputSet
{
    vector_double m_dat[NUM_DAT];
    double m_out[NUM_DAT];
    
};

struct outputWAndB
{
    vector_double **m_sv;
    double *m_alpha;
    int m_numSV;
    double m_bias;
};

void initInputSet(struct inputSet *obj);
void clearInputSet(struct inputSet *obj);
void printInputSet(struct inputSet *obj);

double linearKernelFn(vector_double *va,vector_double *vb);
double polyKernelFn(vector_double *va,vector_double *vb);
double gausRadiusKernelFn(vector_double *va,vector_double *vb);
void inputKernelMatrix(struct inputSet *obj,matrix_double *m,void *fn1);
void findAlpha(struct inputSet *obj,void *fn1);
int checkBoundAlpha(const vector_double *output,const vector_double *alphaV);
void initBuff();
void destroyedBuff();
void testMatrix();

int main(int argc,char **argv)
{
    initBuff();
    srand(time(NULL));
    struct inputSet setA;
    initInputSet(&setA);
    
    printInputSet(&setA);
    /*
    inputKernelMatrix(&setA,&mBuff,linearKernelFn);
    print_matrix_double(&mBuff,6);
    inputKernelMatrix(&setA,&mBuff,polyKernelFn);
    print_matrix_double(&mBuff,6);
    inputKernelMatrix(&setA,&mBuff,gausRadiusKernelFn);
    print_matrix_double(&mBuff,5);
    */
    /*testMatrix();*/
    findAlpha(&setA,gausRadiusKernelFn);
    clearInputSet(&setA);
    destroyedBuff();
    return 0;
}


void initInputSet(struct inputSet *obj)
{
    int index = 0;
    int half = NUM_DAT/2;
    if(obj!=NULL)
    {
        for(index=0;index<NUM_DAT;index++)
        {
            obj->m_dat[index] = new_vector_double(VECT_DIM);
            initial_vector_double(&(obj->m_dat[index]),vect_rang);
            if(half>index)
            {
                obj->m_out[index] =-1.0;
            }
            else
            {
                obj->m_out[index] =1.0;
            }
        }
    }
    else
    {
        /* do nothing */
    }
}
void printInputSet(struct inputSet *obj)
{
    int index = 0; 
    if(obj!=NULL)
    {
        for(index=0;index<NUM_DAT;index++)
        { 
            if(obj->m_out[index] >-1)
            {
                printf(" +%f ",obj->m_out[index]);
            }
            else
            {
                printf(" %f ",obj->m_out[index]);
            }
            print_vector_double(&(obj->m_dat[index]),6);
            printf("\n");
        }
    }
    else
    {
        /* do nothing */
    }
}
void clearInputSet(struct inputSet *obj)
{
    int index = 0;
    if(obj!=NULL)
    {
        for(index=0;index<NUM_DAT;index++)
        { 
            delete_vector_double(&(obj->m_dat[index]));
        }
    }
    else
    {
        /* do nothing */
    }
}

double linearKernelFn(vector_double *va,vector_double *vb)
{
    double ret = 0.0;
    if(multiply_vt_v_double(va,vb,&ret) != 0)
    {
        printf("linearKernelFn error \n");
    }
    else
    {
        /* do nothing */
    }
    return ret;
}
double polyKernelFn(vector_double *va,vector_double *vb)
{
    double ret = pow(linearKernelFn(va,vb)+1.0,POLYFACTOR);
    
    return ret;
}
double gausRadiusKernelFn(vector_double *va,vector_double *vb)
{
    double ret = 0.0;
    minus_v_double(va,vb,&vBuff);
    ret = linearKernelFn(&vBuff,&vBuff);
    if(ret != 0)
    {
        ret = exp(ret/GUASSIAN_DIVIDER); 
    }
    else
    {
        ret = 1;
    }
    return ret;
}

void inputKernelMatrix(struct inputSet *obj,matrix_double *m,void *fn1)
{
    int index = 0;
    int index2 = 0;
    int num1 =0;
    int num2 =0;
    double (*calK)(vector_double*,vector_double*) = fn1;
    if((obj!=NULL)&&(m!=NULL)&&(calK !=NULL))
    {
        num1 = m->row;
        num2 = m->col;
        for(index=0;index<num1;index++)
        {
            for(index2=0;index2<num2;index2++)
            {
                m->data[index][index2] = obj->m_out[index2]*obj->m_out[index]*calK(&(obj->m_dat[index]),&(obj->m_dat[index2]));
            }
        }
    }
    else
    {
        printf("Error in inputKernelMatrix\n");
    }
}
void findAlpha(struct inputSet *obj,void *fn1)
{
    vector_double vtemp = {NUM_DAT,obj->m_out};
    SetValue vect_rang1 = {3,1.0,1.0};
    initial_vector_double(&vBuffAll1,vect_rang1);
    inputKernelMatrix(obj,&mBuff,fn1);
    matrixInverse2(&mBuff,&mBuff2);
    multiply_m_v_double(&mBuff2,&vBuffAll1,&vBuffAlpha);
    print_vector_double(&vBuffAlpha,6);printf("\n");
    checkBoundAlpha(&vtemp,&vBuffAlpha);
}

int checkBoundAlpha(const vector_double *output,const vector_double *alphaV)
{
    double ret = 0.0;
    int index = 0;
    int isFoundMinus =0;
    int num = alphaV->lenght;
    multiply_vt_v_double(output,alphaV,&ret);//dot product
    for(index=0;index<num;index++)
    {
        if(alphaV->data[index]< 0.0)
        {
            if(isFoundMinus == 0)
            {
                isFoundMinus =1;
                printf("found minus alpha : [%d]%f ",index,alphaV->data[index]);
            }
            else
            {
                printf("[%d]%f ",index,alphaV->data[index]);
            }
        }
    }
    if(isFoundMinus == 1)
    {
        printf("\n");
    }
    else
    {
        /* do nothign */
    }
    if(ret != 0.0)
    {
        isFoundMinus = 1;    
        printf("sum of Alpha*yi not zero: %f\n",ret);
    }
    else
    {
        printf("sum of Alpha*yi: %f\n",ret);
    }

    return isFoundMinus;
}
void initBuff()
{
    vBuff = new_vector_double(VECT_DIM);
    vBuffAlpha = new_vector_double(NUM_DAT);
    vBuffAll1 = new_vector_double(NUM_DAT);
    mBuff = new_matrix_double(NUM_DAT,NUM_DAT);
    mBuff2 = new_matrix_double(NUM_DAT,NUM_DAT);
}
void destroyedBuff()
{
    delete_vector_double(&vBuff);
    delete_vector_double(&vBuffAlpha);
    delete_vector_double(&vBuffAll1);
    delete_matrix_double(&mBuff);
    delete_matrix_double(&mBuff2);
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