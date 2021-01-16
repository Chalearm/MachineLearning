#include "SimpleMatrix.h"
#include <stdio.h>

vector_int 	new_vector_int(usint size)
{
	vector_int data ={0,0};
	if(size >0)
	{
		data.data = (int*)malloc(sizeof(int)*size);
		if(data.data !=0) 
		{
			data.lenght = size;
		}	
		else
		{
			/* do nothing */
		}
	}
return data;
}

vector_double 	new_vector_double(usint size)
{
	vector_double data ={0,0};
	if(size >0)
	{
		data.data = (double*)malloc(sizeof(double)*size);
		if(data.data !=0) 
		{
			data.lenght = size;
		}	
		else
		{
			/* do nothing */
		}
	}
return data;
}

vector_char 	new_vector_char(usint size)
{
	vector_char data ={0,0};
	if(size >0)
	{
		data.data = (char*)malloc(sizeof(char)*size);
		if(data.data !=0) 
		{
			data.lenght = size;
		}	
		else
		{
			/* do nothing */
		}
	}
return data;
}

vector_float 	new_vector_float(usint size)
{
	vector_float data ={0,0};
	if(size >0)
	{
		data.data = (float*)malloc(sizeof(float)*size);
		if(data.data !=0) 
		{
			data.lenght = size;
		}	
		else
		{
			/* do nothing */
		}
	}
return data;
}

void delete_vector_int(vector_int *rhs)
{
	
	if(rhs==0)return;
	if( rhs->lenght >0 && rhs->data!=0)
	{
		free(rhs->data);
		rhs->data=0;
		rhs->lenght=0;
	}
}

void delete_vector_char(vector_char *rhs)
{
	
	if(rhs==0)return;
	if( rhs->lenght >0 && rhs->data!=0)
	{
		free(rhs->data);
		rhs->data=0;
		rhs->lenght=0;
	}
}

void delete_vector_double(vector_double *rhs)
{
	
	if(rhs==0)return;
	if( rhs->lenght >0 && rhs->data!=0)
	{
		free(rhs->data);
		rhs->data=0;
		rhs->lenght=0;
	}
}

void delete_vector_float(vector_float *rhs)
{
	if(rhs==0)return;
	if( rhs->lenght >0 && rhs->data!=0)
	{
		free(rhs->data);
		rhs->data=0;
		rhs->lenght=0;
	}
}

matrix_int	new_matrix_int(usint row,usint col)
{
	int i=0;
	matrix_int data = {0,0,0};
	if(row ==0 || col==0) return data;

	data.data = (int**)malloc(sizeof(int*)*row);
	if(data.data ==0) return data;
	
	data.row =row;
	data.col =col;
	for(i=0;i<data.row;i++)
	{
		data.data[i] =0;
		data.data[i] = (int*)malloc(sizeof(int)*col);
		if(data.data[i] ==0) data.col--;
	}
return data;
}

matrix_double	new_matrix_double(usint row,usint col)
{
	int i=0;
	matrix_double data = {0,0,0};
	if(row ==0 || col==0) return data;

	data.data = (double**)malloc(sizeof(double*)*row);
	if(data.data ==0){return data;}
	
	data.row =row;	
	data.col = col;
	for(i=0;i<data.row;i++)
	{
		data.data[i] =0;
		data.data[i] = (double*)malloc(sizeof(double)*col);
		if(data.data[i] ==0){ data.col--;}
	
	}
return data;
}

matrix_char	new_matrix_char(usint row,usint col)
{
	int i=0;
	matrix_char data = {0,0,0};
	if(row ==0 || col==0) return data;

	data.data = (char**)malloc(sizeof(char*)*row);
	if(data.data ==0) return data;
	
	data.row =row;	
	data.col = col;
	for(i=0;i<data.row;i++)
	{
		data.data[i] =0;
		data.data[i] = (char*)malloc(sizeof(char)*col);
		if(data.data[i] ==0) data.col--;
	
	}
return data;
}

matrix_float	new_matrix_float(usint row,usint col)
{
	int i=0;
	matrix_float data = {0,0,0};
	if(row ==0 || col==0) return data;

	data.data = (float**)malloc(sizeof(float*)*row);
	if(data.data ==0) return data;
	
	data.row =row;	
	data.col = col;
	for(i=0;i<data.row;i++)
	{
		data.data[i] =0;
		data.data[i] = (float*)malloc(sizeof(float)*col);
		if(data.data[i] ==0) data.col--;
	
	}
return data;
}
void delete_matrix_int(matrix_int *rhs)
{
	if(rhs==0)return;
	int i=0;
	if(rhs->data !=0)
	{
		for(i=0;i<rhs->row;i++)
		{
			free(rhs->data[i]);
			rhs->data[i] =0;
		}	
		free(rhs->data);
		rhs->data=0;
		rhs->row =0;
		rhs->col =0;
	}	
}

void delete_matrix_char(matrix_char *rhs)
{
	if(rhs==0)return;
	int i=0;
	if(rhs->data !=0)
	{
		for(i=0;i<rhs->row;i++)
		{
			free(rhs->data[i]);
			rhs->data[i] =0;
		}	
		free(rhs->data);
		rhs->data=0;
		rhs->row =0;
		rhs->col =0;
	}	
}
void delete_matrix_double(matrix_double *rhs)
{
	if(rhs==0)return;
	int i=0;
	if(rhs->data !=0)
	{
		for(i=0;i<rhs->row;i++)
		{
			free(rhs->data[i]);
			rhs->data[i] =0;
		}	
		free(rhs->data);
		rhs->data=0;
		rhs->row =0;
		rhs->col =0;
	}	
}
void delete_matrix_float(matrix_float *rhs)
{
	if(rhs==0)return;
	int i=0;
	if(rhs->data !=0)
	{
		for(i=0;i<rhs->row;i++)
		{
			free(rhs->data[i]);
			rhs->data[i] =0;
		}	
		free(rhs->data);
		rhs->data=0;
		rhs->row =0;
		rhs->col =0;
	}	
}
/* 
--------set initialize-----
 set =0  all element is one value;
 set =1  random range(max,min)
 set =2  a,b  ---> a=max or min ,b=max or min
 set =3  run number (min -->max)
 set =4  Identify matrix or range 
*/
void initial_matrix_float(matrix_float* rhs,SetValue set)
{
	if(rhs->data ==0) return;
	if(rhs->row==0 ||rhs->col==0)return;
	int i=0,j=0;	
	float del=0.0;
	switch(set.set)
	{
		case 0: 
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(float)set.max;	
		break;
		case 1:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =set.min+(float)rand()/((float)RAND_MAX/(set.max-set.min));
		break;
		case 2:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(float)set.max*((j+i)%2==0)+(float)set.min*((j+i)%2==1);
		break;
		case 3:
			del = (set.max-set.min)/(float)(rhs->row*rhs->col);
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =set.min+i*rhs->col*(del)+del*(1+j);
		break;
		case 4:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(float)(i==j)*1;
		break;
		default:
		break;

	}
}
void initial_matrix_double(matrix_double* rhs,SetValue set)
{
	if(rhs->data ==0) return;
	if(rhs->row==0 ||rhs->col==0)return;
	int i=0,j=0;	
	double del=0.0;
	switch(set.set)
	{
		case 0:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =set.max;	
		break;
		case 1:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =set.min+(double)rand()/((double)RAND_MAX/(set.max-set.min));
		break;
		case 2:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =set.max*(double)((j+i)%2==0)+set.min*(double)((j+i)%2==1);
		break;
		case 3:
			del = (set.max-set.min)/(double)(rhs->row*rhs->col);
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j]=(set.min+(double)i*rhs->col*(del)+del*(1+j));

				
		break;
		case 4:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(double)(i==j)*1;
		break;
		default:
		break;

	}
}
void initial_matrix_int(matrix_int* rhs,SetValue set)
{
	if(rhs->data ==0) return;
	if(rhs->row==0 ||rhs->col==0)return;
	int i=0,j=0;	
	int del=0;
	switch(set.set)
	{
		case 0:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(int)set.max;	
		break;
		case 1:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(int)(set.min+rand()%(int)(1+set.max-set.min));
		break;
		case 2:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(int)set.max*((j+i)%2==0)+(int)set.min*(double)((j+i)%2==1);
		break;
		case 3:
			del = (int)((set.max-set.min)/(double)(rhs->row*rhs->col));
			set.set=2;
			if(del==0) initial_matrix_int(rhs,set);
			else
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =set.min+(i)*rhs->col*(del)+del*(j+1);
		break;
		case 4:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(i==j)*1;
		break;
		default:
		break;

	}
}
void initial_matrix_char(matrix_char* rhs,SetValue set)
{
	if(rhs->data ==0) return;
	if(rhs->row==0 ||rhs->col==0)return;
	int i=0,j=0;	
	char del=0;
	switch(set.set)
	{
		case 0:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(char)set.max;	
		break;
		case 1:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(char)(set.min+rand()%(char)(1+set.max-set.min));
		break;
		case 2:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(char)set.max*((j+i)%2==0)+(char)set.min*((j+i)%2==1);
		break;
		case 3:
			del = (char)((set.max-set.min)/(double)(rhs->row*rhs->col));
			set.set=2;
			if(del==0) initial_matrix_char(rhs,set);
			else
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =set.min+(i+1)*rhs->col*(del)+del*(1+j);
		break;
		case 4:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(i==j)*1;
		break;
		default:
		break;

	}
}
void initial_vector_int(vector_int* rhs,SetValue set)
{
	if(rhs->data ==0) return;
	if(rhs->lenght==0)return;
	int i=0;	
	int del=0;
	switch(set.set)
	{
		case 0:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(int)set.max;	
		break;
		case 1:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(int)(set.min+rand()%(int)(1+set.max-set.min));
		break;
		case 2:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(int)set.max*((i)%2==0)+(int)set.min*(i%2==1);
		break;
		case 3:
			del = (int)((set.max-set.min)/(double)(rhs->lenght));
			set.set=2;
			if(del==0) initial_vector_int(rhs,set);
			else
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =set.min+(i+1)*(del);
		break;
		case 4:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(i==0)*1;
		break;
		default:
		break;

	}
}
void initial_vector_char(vector_char* rhs,SetValue set)
{
	if(rhs->data ==0) return;
	if(rhs->lenght==0)return;
	int i=0;	
	int del=0;
	switch(set.set)
	{
		case 0:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(char)set.max;	
		break;
		case 1:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(char)(set.min+rand()%(char)(1+set.max-set.min));
		break;
		case 2:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(char)set.max*((i)%2==0)+(char)set.min*(char)((i)%2==1);
		break;
		case 3:
			del = (char)((set.max-set.min)/(double)(rhs->lenght));
			set.set=2;
			if(del==0) initial_vector_char(rhs,set);
			else
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =set.min+(i+1)*(del);
		break;
		case 4:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(i==0)*1;
		break;
		default:
		break;

	}
}


void initial_vector_double(vector_double* rhs,SetValue set)
{
	if(rhs->data ==0) return;
	if(rhs->lenght==0)return;
	int i=0;	
	double del=0.0;
	switch(set.set)
	{
		case 0:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =set.max;	
		break;
		case 1:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =set.min+(double)rand()/((double)RAND_MAX/(set.max-set.min));
		break;
		case 2:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =set.max*(double)(i%2==0)+set.min*(double)(i%2==1);
		break;
		case 3:
			del = (set.max-set.min)/(double)(rhs->lenght);
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i]=(set.min+(double)(i+1)*(del));

				
		break;
		case 4:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(double)(i==0)*1;
		break;
		default:
		break;

	}
}
void initial_vector_float(vector_float* rhs,SetValue set)
{
	if(rhs->data ==0) return;
	if(rhs->lenght==0)return;
	int i=0;	
	double del=0.0;
	switch(set.set)
	{
		case 0:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =set.max;	
		break;
		case 1:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =set.min+(float)rand()/((float)RAND_MAX/(set.max-set.min));
		break;
		case 2:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =set.max*(float)(i%2==0)+set.min*(float)(i%2==1);
		break;
		case 3:
			del = (set.max-set.min)/(float)(rhs->lenght);
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i]=(set.min+(float)(i+1)*(del));

				
		break;
		case 4:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(float)(i==0)*1;
		break;
		default:
		break;

	}
}
int supervise_matrix_int(matrix_int *rhs)
{
	if(rhs->data ==0){return 1;}  //Null matrix
	if(rhs->col ==0){return 2;} //Construction isn't compelete.
	return 0; //complete !!!
}
int supervise_matrix_char(matrix_char *rhs)
{
	if(rhs->data  ==0) return 1;  //Null matrix
	if(rhs->col ==0) return 2; //Construction isn't complete.
	return 0; //complete !!!
}
int supervise_matrix_double(matrix_double *rhs)
{
	if(rhs->data  ==0) return 1;  //Null matrix
	if(rhs->col ==0) return 2; //Construction isn't complete.
	return 0; //complete !!!
}
int supervise_matrix_float(matrix_float *rhs)
{
	if(rhs->data  ==0) return 1;  //Null matrix
	if(rhs->col ==0) return 2; //Construction isn't complete.
	return 0; //complete !!!
}
int supervise_vector_int(vector_int *rhs)
{
	if(rhs->data ==0) return 1; //Null matrix
	if(rhs->lenght==0) return 2; //Construction isn't complete.
	return 0; //complete !!!
}
int supervise_vector_char(vector_char *rhs)
{
	if(rhs->data ==0) return 1; //Null matrix
	if(rhs->lenght==0) return 2; //Construction isn't complete.
	return 0; //complete !!!
}
int supervise_vector_double(vector_double *rhs)
{
	if(rhs->data ==0) return 1; //Null matrix
	if(rhs->lenght==0) return 2; //Construction isn't complete.
	return 0; //complete !!!
}
int supervise_vector_float(vector_float *rhs)
{
	if(rhs->data ==0) return 1; //Null matrix
	if(rhs->lenght==0) return 2; //Construction isn't complete.
	return 0; //complete !!!
}

void print_vector_int(vector_int *rhs,int option)
{
	int i;
	switch(option)
	{
		case 3:
		case 0:
			printf("lenght:%d\n",rhs->lenght);
			for(i=0;i<rhs->lenght;i++)
			 printf("%d\n",rhs->data[i]);
			break;
		case 1:
			printf("lenght:%d\n",rhs->lenght);
			break;
		case 2:
			for(i=0;i<rhs->lenght;i++)
			 printf("%d\n",rhs->data[i]);
			break;
		case 4: 
			for(i=0;i<rhs->lenght;i++)
			 printf("%d ",rhs->data[i]);
			printf("\n");	
			break;
		case 5:
			printf("lenght:%d\n",rhs->lenght);
			for(i=0;i<rhs->lenght;i++)
			 printf("%d ",rhs->data[i]);
			printf("\n");
			break;
		default: break;
	}
			
}
void print_vector_float(vector_float *rhs,int option)
{
	int i;
	switch(option)
	{
		case 3:
		case 0:
			printf("lenght:%d\n",rhs->lenght);
			for(i=0;i<rhs->lenght;i++)
			 printf("%f\n",rhs->data[i]);
			break;
		case 1:
			printf("lenght:%d\n",rhs->lenght);
			break;
		case 2:
			for(i=0;i<rhs->lenght;i++)
			 printf("%f\n",rhs->data[i]);
			break;
		case 4: 
			for(i=0;i<rhs->lenght;i++)
			 printf("%f ",rhs->data[i]);
			printf("\n");	
			break;
		case 5:
			printf("lenght:%d\n",rhs->lenght);
			for(i=0;i<rhs->lenght;i++)
			 printf("%f ",rhs->data[i]);
			printf("\n");
			break;
		default: break;
	}
			
}
void print_vector_double(vector_double *rhs,int option)
{
	int i;
	switch(option)
	{
		case 3:
		case 0:
			printf("lenght:%d\n",rhs->lenght);
			for(i=0;i<rhs->lenght;i++)
			 printf("%lf\n",rhs->data[i]);
			break;
		case 1:
			printf("lenght:%d\n",rhs->lenght);
			break;
		case 2:
			for(i=0;i<rhs->lenght;i++)
			 printf("%lf\n",rhs->data[i]);
			break;
		case 4: 
			for(i=0;i<rhs->lenght;i++)
			 printf("%lf ",rhs->data[i]);
			printf("\n");	
			break;
		case 5:
			printf("lenght:%d\n",rhs->lenght);
			for(i=0;i<rhs->lenght;i++)
			 printf("%lf ",rhs->data[i]);
			printf("\n");
			break;
		default: break;
	}
			
}
void print_vector_char(vector_char *rhs,int option)
{
	int i;
	switch(option)
	{
		case 3:
		case 0:
			printf("lenght:%d\n",rhs->lenght);
			for(i=0;i<rhs->lenght;i++)
			 printf("%d\n",rhs->data[i]);
			break;
		case 1:
			printf("lenght:%d\n",rhs->lenght);
			break;
		case 2:
			for(i=0;i<rhs->lenght;i++)
			 printf("%d\n",rhs->data[i]);
			break;
		case 4: 
			for(i=0;i<rhs->lenght;i++)
			 printf("%d ",rhs->data[i]);
			printf("\n");	
			break;
		case 5:
			printf("lenght:%d\n",rhs->lenght);
			for(i=0;i<rhs->lenght;i++)
			 printf("%d ",rhs->data[i]);
			printf("\n");
			break;
		case 8:
			for(i=0;i<rhs->lenght;i++)
			 printf("%c\n",rhs->data[i]);
			break;
		case 9: 
			for(i=0;i<rhs->lenght;i++)
			 printf("%c ",rhs->data[i]);
			break;
		case 10:
			for(i=0;i<rhs->lenght;i++)
			printf("%d ",rhs->data[i]);
		default: break;
	}
			
}
void print_matrix_int(matrix_int *rhs,int option)
{
	int i,j;
	switch(option)
	{
		case 3:
		case 0:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			for(i=0;i<rhs->row;i++)
			{
			 for(j=0;j<rhs->col;j++)
			 	printf("%d ",rhs->data[i][j]);
			 printf("\n");
			}
			break;
		case 1:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			break;
		case 2:
			for(i=0;i<rhs->row;i++)
			{
			 for(j=0;j<rhs->col;j++)
			 	printf("%d ",rhs->data[i][j]);
			 printf("\n");
			}
			break;
		case 4: 
			for(i=0;i<rhs->col;i++)
			{
			 for(j=0;j<rhs->row;j++)
			 	printf("%d ",rhs->data[j][i]);
			 printf("\n");
			}
			break;
		case 5:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			for(i=0;i<rhs->col;i++)
			{
			 for(j=0;j<rhs->row;j++)
			 	printf("%d ",rhs->data[j][i]);
			 printf("\n");
			}
			break;
		default: break;
	}
}	
void print_matrix_float(matrix_float *rhs,int option)
{
	int i,j;
	switch(option)
	{
		case 3:
		case 0:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			for(i=0;i<rhs->row;i++)
			{
			 for(j=0;j<rhs->col;j++)
			 	printf("%f ",rhs->data[i][j]);
			 printf("\n");
			}
			break;
		case 1:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			break;
		case 2:
			for(i=0;i<rhs->row;i++)
			{
			 for(j=0;j<rhs->col;j++)
			 	printf("%f ",rhs->data[i][j]);
			 printf("\n");
			}
			break;
		case 4: 
			for(i=0;i<rhs->col;i++)
			{
			 for(j=0;j<rhs->row;j++)
			 	printf("%f ",rhs->data[j][i]);
			 printf("\n");
			}
			break;
		case 5:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			for(i=0;i<rhs->col;i++)
			{
			 for(j=0;j<rhs->row;j++)
			 	printf("%f ",rhs->data[j][i]);
			 printf("\n");
			}
			break;
		default: break;
	}
}	
void print_matrix_double(matrix_double *rhs,int option )
{
	int i,j;
	switch(option)
	{
		case 3:
		case 0:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			for(i=0;i<rhs->row;i++)
			{
			 for(j=0;j<rhs->col;j++)
			 	printf("%lf ",rhs->data[i][j]);
			 printf("\n");
			}
			break;
		case 1:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			break;
		case 2:
			for(i=0;i<rhs->row;i++)
			{
			 for(j=0;j<rhs->col;j++)
			 	printf("%lf ",rhs->data[i][j]);
			 printf("\n");
			}
			break;
		case 4: 
			for(i=0;i<rhs->col;i++)
			{
			 for(j=0;j<rhs->row;j++)
			 	printf("%lf ",rhs->data[j][i]);
			 printf("\n");
			}
			break;
		case 5:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			for(i=0;i<rhs->col;i++)
			{
			 for(j=0;j<rhs->row;j++)
			 	printf("%lf ",rhs->data[j][i]);
			 printf("\n");
			}
			break;
		default: break;
	}
}	
void print_matrix_char(matrix_char *rhs,int option)
{
	int i,j;
	switch(option)
	{
		case 3:
		case 0:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			for(i=0;i<rhs->row;i++)
			{
			 for(j=0;j<rhs->col;j++)
			 	printf("%d ",rhs->data[i][j]);
			 printf("\n");
			}
			break;
		case 1:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			break;
		case 2:
			for(i=0;i<rhs->row;i++)
			{
			 for(j=0;j<rhs->col;j++)
			 	printf("%d ",rhs->data[i][j]);
			 printf("\n");
			}
			break;
		case 4: 
			for(i=0;i<rhs->col;i++)
			{
			 for(j=0;j<rhs->row;j++)
			 	printf("%d ",rhs->data[j][i]);
			 printf("\n");
			}
			break;
		case 5:
			printf("row:%d col:%d\n",rhs->row,rhs->col);
			for(i=0;i<rhs->col;i++)
			{
			 for(j=0;j<rhs->row;j++)
			 	printf("%d ",rhs->data[j][i]);
			 printf("\n");
			}
			break;
		case 8:
			for(i=0;i<rhs->row;i++)
			{
			 for(j=0;j<rhs->col;j++)
			 	printf("%c ",rhs->data[i][j]);
			 printf("\n");
			}
			break;
		case 9:
			for(i=0;i<rhs->col;i++)
			{
			 for(j=0;j<rhs->row;j++)
			 	printf("%c ",rhs->data[j][i]);
			 printf("\n");
			}
		default: break;
	}
}	
int multiply_v_m_int(vector_int *rhs,matrix_int *lhs,matrix_int *res)
{
	int i,j,factor =supervise_matrix_int(res);
	if(supervise_vector_int(rhs) || supervise_matrix_int(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=1)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
	
		*res =new_matrix_int(rhs->lenght,lhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col !=lhs->col)
		{
			delete_matrix_int(res);
			*res=new_matrix_int(rhs->lenght,lhs->col);
		}
	}

	for(i=0;i<rhs->lenght;i++)
	{
		for(j=0;j<lhs->col;j++)
		   res->data[i][j]= rhs->data[i]*lhs->data[0][j];	
	}	

return 0;//complete
}
int multiply_vt_m_int(vector_int *rhs,matrix_int *lhs,matrix_int *res)
{
	int i,j,factor =supervise_matrix_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_int(rhs) || supervise_matrix_int(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_int(1,lhs->col);
		initial_matrix_int(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != 1 || res->col !=lhs->col)
		{	
			delete_matrix_int(res);
			*res=new_matrix_int(1,lhs->col);
			
		}
		initial_matrix_int(res,set);
	}

		for(i=0;i<lhs->col;i++)
		 for(j=0;j<rhs->lenght;j++)
		   res->data[0][i]+= rhs->data[j]*lhs->data[j][i];	

return 0;//complete
}
int multiply_v_mt_int(vector_int *rhs,matrix_int *lhs,matrix_int *res)
{
	int i,j,factor =supervise_matrix_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_int(rhs) || supervise_matrix_int(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=1)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_int(rhs->lenght,lhs->row);
		//initial_matrix_int(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col !=lhs->row)
		{	
			delete_matrix_int(res);
			*res=new_matrix_int(rhs->lenght,lhs->row);
			
		}
		//initial_matrix_int(res,set);
	}

		for(i=0;i<rhs->lenght;i++)
		 for(j=0;j<lhs->row;j++)
		   res->data[i][j]= rhs->data[i]*lhs->data[j][0];	

return 0;//complete
}
int multiply_m_v_int(matrix_int *rhs,vector_int *lhs,vector_int *res)
{
	int i,j,factor =supervise_vector_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_int(lhs) || supervise_matrix_int(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_vector_int(rhs->row);
		initial_vector_int(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != lhs->lenght)
		{	
			delete_vector_int(res);
			*res=new_vector_int(rhs->row);
			
		}
		initial_vector_int(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->lenght;j++)
		   res->data[i]+= rhs->data[i][j]*lhs->data[j];	

return 0;//complete
}
int multiply_mt_v_int(matrix_int *rhs,vector_int *lhs,vector_int *res)
{
	int i,j,factor =supervise_vector_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_int(lhs) || supervise_matrix_int(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_vector_int(rhs->col);
		initial_vector_int(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != lhs->lenght)
		{	
			delete_vector_int(res);
			*res=new_vector_int(rhs->col);
			
		}
		initial_vector_int(res,set);
	}

		for(i=0;i<rhs->col;i++)
		 for(j=0;j<lhs->lenght;j++)
		   res->data[i]+= rhs->data[j][i]*lhs->data[j];	

return 0;//complete
}
 
int multiply_m_vt_int(matrix_int *rhs,vector_int *lhs,matrix_int *res)
{
	int i,j,factor =supervise_matrix_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_int(lhs) || supervise_matrix_int(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res=new_matrix_int(rhs->row,lhs->lenght);
	//	initial_matrix_int(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->lenght)
		{	
			delete_matrix_int(res);
			*res=new_matrix_int(rhs->row,lhs->lenght);
			
		}
		//initial_matrix_int(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->lenght;j++)
		   	res->data[i][j]= rhs->data[i][0]*lhs->data[j];	

return 0;//complete
} 
int multiply_m_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res)
{
	int i,j,k,factor =supervise_matrix_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_int(lhs) || supervise_matrix_int(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_int(rhs->row,lhs->col);
		initial_matrix_int(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_int(res);
			*res= new_matrix_int(rhs->row,lhs->col);
			
		}
		initial_matrix_int(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
			for(k=0;k<rhs->col;k++)
		   	res->data[i][j]+= rhs->data[i][k]*lhs->data[k][j];	

return 0;//complete
}

int multiply_mt_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res)
{
	int i,j,k,factor =supervise_matrix_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_int(lhs) || supervise_matrix_int(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_int(rhs->col,lhs->col);
		initial_matrix_int(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->col || res->col != lhs->col)
		{	
			delete_matrix_int(res);
			*res=new_matrix_int(rhs->col,lhs->col);
			
		}
		initial_matrix_int(res,set);
	}

		for(i=0;i<rhs->col;i++)
		 for(j=0;j<lhs->col;j++)
			for(k=0;k<rhs->row;k++)
		   	res->data[i][j]+= rhs->data[k][i]*lhs->data[k][j];	

return 0;//complete
}
int multiply_m_mt_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res)
{
	int i,j,k,factor =supervise_matrix_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_int(lhs) || supervise_matrix_int(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_int(rhs->row,lhs->row);
		initial_matrix_int(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->col || res->col != lhs->col)
		{	
			delete_matrix_int(res);
			*res=new_matrix_int(rhs->row,lhs->row);
	
		}
		initial_matrix_int(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->row;j++)
			for(k=0;k<rhs->col;k++)
		   	res->data[i][j]+= rhs->data[i][k]*lhs->data[j][k];	

return 0;//complete
}
int multiply_v_vt_int(vector_int *rhs,vector_int *lhs,matrix_int *res)
{
	int i,j,factor =supervise_matrix_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_int(lhs) || supervise_vector_int(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res=new_matrix_int(rhs->lenght,lhs->lenght);
		initial_matrix_int(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col != lhs->lenght)
		{	
			delete_matrix_int(res);
			*res=new_matrix_int(rhs->lenght,lhs->lenght);
			
		}
		initial_matrix_int(res,set);
	}

		for(i=0;i<rhs->lenght;i++)
		 for(j=0;j<lhs->lenght;j++)
		   	res->data[i][j]= rhs->data[i]*lhs->data[j];	

return 0;//complete
}
int multiply_vt_v_int(vector_int *rhs,vector_int *lhs,int *res)//dot product
{
	int i,j,factor =(res==0);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_int(lhs) || supervise_vector_int(rhs))	
	{
		return 1;// failed 
	}
	if(rhs->lenght != lhs->lenght)
	{
		return 2; // size failed
	}
	if(factor==1)
	{
		return 2; // res is null
	}
		*res =0;
		for(i=0;i<rhs->lenght;i++)
		   	*res+= rhs->data[i]*lhs->data[i];	

return 0;//complete
}
int multiply_v_m_double(vector_double *rhs,matrix_double *lhs,matrix_double *res)
{
	int i,j,factor =supervise_matrix_double(res);
	if(supervise_vector_double(rhs) || supervise_matrix_double(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=1)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
	
		*res =new_matrix_double(rhs->lenght,lhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col !=lhs->col)
		{
			delete_matrix_double(res);
			*res=new_matrix_double(rhs->lenght,lhs->col);
		}
	}

	for(i=0;i<rhs->lenght;i++)
	{
		for(j=0;j<lhs->col;j++)
		   res->data[i][j]= rhs->data[i]*lhs->data[0][j];	
	}	

return 0;//complete
}
int multiply_vt_m_double(vector_double *rhs,matrix_double *lhs,matrix_double *res)
{
	int i,j,factor =supervise_matrix_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_double(rhs) || supervise_matrix_double(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_double(1,lhs->col);
		initial_matrix_double(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != 1 || res->col !=lhs->col)
		{	
			delete_matrix_double(res);
			*res=new_matrix_double(1,lhs->col);
			
		}
		initial_matrix_double(res,set);
	}

		for(i=0;i<lhs->col;i++)
		 for(j=0;j<rhs->lenght;j++)
		   res->data[0][i]+= rhs->data[j]*lhs->data[j][i];	

return 0;//complete
}
int multiply_v_mt_double(vector_double *rhs,matrix_double *lhs,matrix_double *res)
{
	int i,j,factor =supervise_matrix_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_double(rhs) || supervise_matrix_double(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=1)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_double(rhs->lenght,lhs->row);
		//initial_matrix_int(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col !=lhs->row)
		{	
			delete_matrix_double(res);
			*res=new_matrix_double(rhs->lenght,lhs->row);
			
		}
		//initial_matrix_int(res,set);
	}

		for(i=0;i<rhs->lenght;i++)
		 for(j=0;j<lhs->row;j++)
		   res->data[i][j]= rhs->data[i]*lhs->data[j][0];	

return 0;//complete
}
int multiply_m_v_double(matrix_double *rhs,vector_double *lhs,vector_double *res)
{
	int i,j,factor =supervise_vector_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_double(lhs) || supervise_matrix_double(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_vector_double(rhs->row);
		initial_vector_double(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != lhs->lenght)
		{	
			delete_vector_double(res);
			*res=new_vector_double(rhs->row);
			
		}
		initial_vector_double(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->lenght;j++)
		   res->data[i]+= rhs->data[i][j]*lhs->data[j];	

return 0;//complete
}
int multiply_mt_v_double(matrix_double *rhs,vector_double *lhs,vector_double *res)
{
	int i,j,factor =supervise_vector_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_double(lhs) || supervise_matrix_double(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_vector_double(rhs->col);
		initial_vector_double(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != lhs->lenght)
		{	
			delete_vector_double(res);
			*res=new_vector_double(rhs->col);
			
		}
		initial_vector_double(res,set);
	}

		for(i=0;i<rhs->col;i++)
		 for(j=0;j<lhs->lenght;j++)
		   res->data[i]+= rhs->data[j][i]*lhs->data[j];	

return 0;//complete
}
 
int multiply_m_vt_double(matrix_double *rhs,vector_double *lhs,matrix_double *res)
{
	int i,j,factor =supervise_matrix_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_double(lhs) || supervise_matrix_double(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res=new_matrix_double(rhs->row,lhs->lenght);
	//	initial_matrix_int(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->lenght)
		{	
			delete_matrix_double(res);
			*res=new_matrix_double(rhs->row,lhs->lenght);
			
		}
		//initial_matrix_int(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->lenght;j++)
		   	res->data[i][j]= rhs->data[i][0]*lhs->data[j];	

return 0;//complete
} 
int multiply_m_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
	int i,j,k,factor =supervise_matrix_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_double(rhs->row,lhs->col);
		initial_matrix_double(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_double(res);
			*res= new_matrix_double(rhs->row,lhs->col);
			
		}
		initial_matrix_double(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
			for(k=0;k<rhs->col;k++)
		   	res->data[i][j]+= rhs->data[i][k]*lhs->data[k][j];	

return 0;//complete
}
int multiply_mt_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
	int i,j,k,factor =supervise_matrix_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_double(rhs->col,lhs->col);
		initial_matrix_double(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->col || res->col != lhs->col)
		{	
			delete_matrix_double(res);
			*res=new_matrix_double(rhs->col,lhs->col);
			
		}
		initial_matrix_double(res,set);
	}

		for(i=0;i<rhs->col;i++)
		 for(j=0;j<lhs->col;j++)
			for(k=0;k<rhs->row;k++)
		   	res->data[i][j]+= rhs->data[k][i]*lhs->data[k][j];	

return 0;//complete
}
int multiply_m_mt_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
	int i,j,k,factor =supervise_matrix_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_double(rhs->row,lhs->row);
		initial_matrix_double(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->col || res->col != lhs->col)
		{	
			delete_matrix_double(res);
			*res=new_matrix_double(rhs->row,lhs->row);
	
		}
		initial_matrix_double(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->row;j++)
			for(k=0;k<rhs->col;k++)
		   	res->data[i][j]+= rhs->data[i][k]*lhs->data[j][k];	

return 0;//complete
}
int multiply_v_vt_double(vector_double *rhs,vector_double *lhs,matrix_double *res)
{
	int i,j,factor =supervise_matrix_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_double(lhs) || supervise_vector_double(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res=new_matrix_double(rhs->lenght,lhs->lenght);
		initial_matrix_double(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col != lhs->lenght)
		{	
			delete_matrix_double(res);
			*res=new_matrix_double(rhs->lenght,lhs->lenght);
			
		}
		initial_matrix_double(res,set);
	}

		for(i=0;i<rhs->lenght;i++)
		 for(j=0;j<lhs->lenght;j++)
		   	res->data[i][j]= rhs->data[i]*lhs->data[j];	

return 0;//complete
}
int multiply_vt_v_double(vector_double *rhs,vector_double *lhs,double *res) //dot product
{
	int i,j,factor =(res==0);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_double(lhs) || supervise_vector_double(rhs))	
	{
		return 1;// failed 
	}
	if(rhs->lenght != lhs->lenght)
	{
		return 2; // size failed
	}
	if(factor==1)
	{
		return 2; // res is null
	}
		*res =0.0;
		for(i=0;i<rhs->lenght;i++)
		   	*res+= rhs->data[i]*lhs->data[i];	

return 0;//complete
}
int multiply_v_m_float(vector_float *rhs,matrix_float *lhs,matrix_float *res)
{
	int i,j,factor =supervise_matrix_float(res);
	if(supervise_vector_float(rhs) || supervise_matrix_float(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=1)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
	
		*res =new_matrix_float(rhs->lenght,lhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col !=lhs->col)
		{
			delete_matrix_float(res);
			*res=new_matrix_float(rhs->lenght,lhs->col);
		}
	}

	for(i=0;i<rhs->lenght;i++)
	{
		for(j=0;j<lhs->col;j++)
		   res->data[i][j]= rhs->data[i]*lhs->data[0][j];	
	}	

return 0;//complete
}
int multiply_vt_m_float(vector_float *rhs,matrix_float *lhs,matrix_float *res)
{
	int i,j,factor =supervise_matrix_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_float(rhs) || supervise_matrix_float(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_float(1,lhs->col);
		initial_matrix_float(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != 1 || res->col !=lhs->col)
		{	
			delete_matrix_float(res);
			*res=new_matrix_float(1,lhs->col);
			
		}
		initial_matrix_float(res,set);
	}

		for(i=0;i<lhs->col;i++)
		 for(j=0;j<rhs->lenght;j++)
		   res->data[0][i]+= rhs->data[j]*lhs->data[j][i];	

return 0;//complete
}
int multiply_v_mt_float(vector_float *rhs,matrix_float *lhs,matrix_float *res)
{
	int i,j,factor =supervise_matrix_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_float(rhs) || supervise_matrix_float(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=1)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_float(rhs->lenght,lhs->row);
		//initial_matrix_float(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col !=lhs->row)
		{	
			delete_matrix_float(res);
			*res=new_matrix_float(rhs->lenght,lhs->row);
			
		}
		//initial_matrix_float(res,set);
	}

		for(i=0;i<rhs->lenght;i++)
		 for(j=0;j<lhs->row;j++)
		   res->data[i][j]= rhs->data[i]*lhs->data[j][0];	

return 0;//complete
}
int multiply_m_v_float(matrix_float *rhs,vector_float *lhs,vector_float *res)
{
	int i,j,factor =supervise_vector_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_float(lhs) || supervise_matrix_float(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_vector_float(rhs->row);
		initial_vector_float(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != lhs->lenght)
		{	
			delete_vector_float(res);
			*res=new_vector_float(rhs->row);
			
		}
		initial_vector_float(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->lenght;j++)
		   res->data[i]+= rhs->data[i][j]*lhs->data[j];	

return 0;//complete
}
int multiply_mt_v_float(matrix_float *rhs,vector_float *lhs,vector_float *res)
{
	int i,j,factor =supervise_vector_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_float(lhs) || supervise_matrix_float(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_vector_float(rhs->col);
		initial_vector_float(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != lhs->lenght)
		{	
			delete_vector_float(res);
			*res=new_vector_float(rhs->col);
			
		}
		initial_vector_float(res,set);
	}

		for(i=0;i<rhs->col;i++)
		 for(j=0;j<lhs->lenght;j++)
		   res->data[i]+= rhs->data[j][i]*lhs->data[j];	

return 0;//complete
}
 
int multiply_m_vt_float(matrix_float *rhs,vector_float *lhs,matrix_float *res)
{
	int i,j,factor =supervise_matrix_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_float(lhs) || supervise_matrix_float(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res=new_matrix_float(rhs->row,lhs->lenght);
	//	initial_matrix_float(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->lenght)
		{	
			delete_matrix_float(res);
			*res=new_matrix_float(rhs->row,lhs->lenght);
			
		}
		//initial_matrix_float(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->lenght;j++)
		   	res->data[i][j]= rhs->data[i][0]*lhs->data[j];	

return 0;//complete
} 
int multiply_m_m_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res)
{
	int i,j,k,factor =supervise_matrix_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_float(lhs) || supervise_matrix_float(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_float(rhs->row,lhs->col);
		initial_matrix_float(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_float(res);
			*res= new_matrix_float(rhs->row,lhs->col);
			
		}
		initial_matrix_float(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
			for(k=0;k<rhs->col;k++)
		   	res->data[i][j]+= rhs->data[i][k]*lhs->data[k][j];	

return 0;//complete
}

int multiply_mt_m_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res)
{
	int i,j,k,factor =supervise_matrix_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_float(lhs) || supervise_matrix_float(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_float(rhs->col,lhs->col);
		initial_matrix_float(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->col || res->col != lhs->col)
		{	
			delete_matrix_float(res);
			*res=new_matrix_float(rhs->col,lhs->col);
			
		}
		initial_matrix_float(res,set);
	}

		for(i=0;i<rhs->col;i++)
		 for(j=0;j<lhs->col;j++)
			for(k=0;k<rhs->row;k++)
		   	res->data[i][j]+= rhs->data[k][i]*lhs->data[k][j];	

return 0;//complete
}
int multiply_m_mt_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res)
{
	int i,j,k,factor =supervise_matrix_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_float(lhs) || supervise_matrix_float(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_float(rhs->row,lhs->row);
		initial_matrix_float(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->col || res->col != lhs->col)
		{	
			delete_matrix_float(res);
			*res=new_matrix_float(rhs->row,lhs->row);
	
		}
		initial_matrix_float(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->row;j++)
			for(k=0;k<rhs->col;k++)
		   	res->data[i][j]+= rhs->data[i][k]*lhs->data[j][k];	

return 0;//complete
}
int multiply_v_vt_float(vector_float *rhs,vector_float *lhs,matrix_float *res)
{
	int i,j,factor =supervise_matrix_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_float(lhs) || supervise_vector_float(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res=new_matrix_float(rhs->lenght,lhs->lenght);
		initial_matrix_float(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col != lhs->lenght)
		{	
			delete_matrix_float(res);
			*res=new_matrix_float(rhs->lenght,lhs->lenght);
			
		}
		initial_matrix_float(res,set);
	}

		for(i=0;i<rhs->lenght;i++)
		 for(j=0;j<lhs->lenght;j++)
		   	res->data[i][j]= rhs->data[i]*lhs->data[j];	

return 0;//complete
}
int multiply_vt_v_float(vector_float *rhs,vector_float *lhs,float *res)//dot product
{
	int i,j,factor =(res==0);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_float(lhs) || supervise_vector_float(rhs))	
	{
		return 1;// failed 
	}
	if(rhs->lenght != lhs->lenght)
	{
		return 2; // size failed
	}
	if(factor==1)
	{
		return 2; // res is null
	}
		*res =0;
		for(i=0;i<rhs->lenght;i++)
		   	*res+= rhs->data[i]*lhs->data[i];	

return 0;//complete
}
int multiply_v_m_char(vector_char *rhs,matrix_char *lhs,matrix_char *res)
{
	int i,j,factor =supervise_matrix_char(res);
	if(supervise_vector_char(rhs) || supervise_matrix_char(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=1)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
	
		*res =new_matrix_char(rhs->lenght,lhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col !=lhs->col)
		{
			delete_matrix_char(res);
			*res=new_matrix_char(rhs->lenght,lhs->col);
		}
	}

	for(i=0;i<rhs->lenght;i++)
	{
		for(j=0;j<lhs->col;j++)
		   res->data[i][j]= rhs->data[i]*lhs->data[0][j];	
	}	

return 0;//complete
}
int multiply_vt_m_char(vector_char *rhs,matrix_char *lhs,matrix_char *res)
{
	int i,j,factor =supervise_matrix_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_char(rhs) || supervise_matrix_char(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_char(1,lhs->col);
		initial_matrix_char(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != 1 || res->col !=lhs->col)
		{	
			delete_matrix_char(res);
			*res=new_matrix_char(1,lhs->col);
			
		}
		initial_matrix_char(res,set);
	}

		for(i=0;i<lhs->col;i++)
		 for(j=0;j<rhs->lenght;j++)
		   res->data[0][i]+= rhs->data[j]*lhs->data[j][i];	

return 0;//complete
}
int multiply_v_mt_char(vector_char *rhs,matrix_char *lhs,matrix_char *res)
{
	int i,j,factor =supervise_matrix_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_char(rhs) || supervise_matrix_char(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=1)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_char(rhs->lenght,lhs->row);
		//initial_matrix_char(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col !=lhs->row)
		{	
			delete_matrix_char(res);
			*res=new_matrix_char(rhs->lenght,lhs->row);
			
		}
		//initial_matrix_char(res,set);
	}

		for(i=0;i<rhs->lenght;i++)
		 for(j=0;j<lhs->row;j++)
		   res->data[i][j]= rhs->data[i]*lhs->data[j][0];	

return 0;//complete
}
int multiply_m_v_char(matrix_char *rhs,vector_char *lhs,vector_char *res)
{
	int i,j,factor =supervise_vector_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_char(lhs) || supervise_matrix_char(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_vector_char(rhs->row);
		initial_vector_char(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != lhs->lenght)
		{	
			delete_vector_char(res);
			*res=new_vector_char(rhs->row);
			
		}
		initial_vector_char(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->lenght;j++)
		   res->data[i]+= rhs->data[i][j]*lhs->data[j];	

return 0;//complete
}
int multiply_mt_v_char(matrix_char *rhs,vector_char *lhs,vector_char *res)
{
	int i,j,factor =supervise_vector_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_char(lhs) || supervise_matrix_char(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_vector_char(rhs->col);
		initial_vector_char(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != lhs->lenght)
		{	
			delete_vector_char(res);
			*res=new_vector_char(rhs->col);
			
		}
		initial_vector_char(res,set);
	}

		for(i=0;i<rhs->col;i++)
		 for(j=0;j<lhs->lenght;j++)
		   res->data[i]+= rhs->data[j][i]*lhs->data[j];	

return 0;//complete
}
 
int multiply_m_vt_char(matrix_char *rhs,vector_char *lhs,matrix_char *res)
{
	int i,j,factor =supervise_matrix_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_char(lhs) || supervise_matrix_char(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res=new_matrix_char(rhs->row,lhs->lenght);
	//	initial_matrix_char(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->lenght)
		{	
			delete_matrix_char(res);
			*res=new_matrix_char(rhs->row,lhs->lenght);
			
		}
		//initial_matrix_char(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->lenght;j++)
		   	res->data[i][j]= rhs->data[i][0]*lhs->data[j];	

return 0;//complete
} 
int multiply_m_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res)
{
	int i,j,k,factor =supervise_matrix_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_char(lhs) || supervise_matrix_char(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_char(rhs->row,lhs->col);
		initial_matrix_char(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_char(res);
			*res= new_matrix_char(rhs->row,lhs->col);
			
		}
		initial_matrix_char(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
			for(k=0;k<rhs->col;k++)
		   	res->data[i][j]+= rhs->data[i][k]*lhs->data[k][j];	

return 0;//complete
}

int multiply_mt_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res)
{
	int i,j,k,factor =supervise_matrix_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_char(lhs) || supervise_matrix_char(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_char(rhs->col,lhs->col);
		initial_matrix_char(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->col || res->col != lhs->col)
		{	
			delete_matrix_char(res);
			*res=new_matrix_char(rhs->col,lhs->col);
			
		}
		initial_matrix_char(res,set);
	}

		for(i=0;i<rhs->col;i++)
		 for(j=0;j<lhs->col;j++)
			for(k=0;k<rhs->row;k++)
		   	res->data[i][j]+= rhs->data[k][i]*lhs->data[k][j];	

return 0;//complete
}
int multiply_m_mt_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res)
{
	int i,j,k,factor =supervise_matrix_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_char(lhs) || supervise_matrix_char(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_char(rhs->row,lhs->row);
		initial_matrix_char(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->col || res->col != lhs->col)
		{	
			delete_matrix_char(res);
			*res=new_matrix_char(rhs->row,lhs->row);
	
		}
		initial_matrix_char(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->row;j++)
			for(k=0;k<rhs->col;k++)
		   	res->data[i][j]+= rhs->data[i][k]*lhs->data[j][k];	

return 0;//complete
}
int multiply_v_vt_char(vector_char *rhs,vector_char *lhs,matrix_char *res)
{
	int i,j,factor =supervise_matrix_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_char(lhs) || supervise_vector_char(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res=new_matrix_char(rhs->lenght,lhs->lenght);
		initial_matrix_char(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col != lhs->lenght)
		{	
			delete_matrix_char(res);
			*res=new_matrix_char(rhs->lenght,lhs->lenght);
			
		}
		initial_matrix_char(res,set);
	}

		for(i=0;i<rhs->lenght;i++)
		 for(j=0;j<lhs->lenght;j++)
		   	res->data[i][j]= rhs->data[i]*lhs->data[j];	

return 0;//complete
}
int multiply_vt_v_char(vector_char *rhs,vector_char *lhs,char *res)//dot product
{
	int i,j,factor =(res==0);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_char(lhs) || supervise_vector_char(rhs))	
	{
		return 1;// failed 
	}
	if(rhs->lenght != lhs->lenght)
	{
		return 2; // size failed
	}
	if(factor==1)
	{
		return 2; // res is null
	}
		*res =0;
		for(i=0;i<rhs->lenght;i++)
		   	*res+= rhs->data[i]*lhs->data[i];	

return 0;//complete
}
int dotmultiply_v_int(vector_int *rhs,vector_int *lhs,vector_int *res)
{
	int i,factor =supervise_vector_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_int(lhs) || supervise_vector_int(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_int(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_int(res);
			*res=new_vector_int(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]*lhs->data[i];	

return 0;//complete
}
int dotmultiply_v_char(vector_char *rhs,vector_char *lhs,vector_char *res)
{
	int i,factor =supervise_vector_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_char(lhs) || supervise_vector_char(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_char(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_char(res);
			*res=new_vector_char(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]*lhs->data[i];	

return 0;//complete
}
int dotmultiply_v_float(vector_float *rhs,vector_float *lhs,vector_float *res)
{
	int i,factor =supervise_vector_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_float(lhs) || supervise_vector_float(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_float(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_float(res);
			*res=new_vector_float(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]*lhs->data[i];	

return 0;//complete
}
int dotmultiply_v_double(vector_double *rhs,vector_double *lhs,vector_double *res)
{
	int i,factor =supervise_vector_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_double(lhs) || supervise_vector_double(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_double(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_double(res);
			*res=new_vector_double(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]*lhs->data[i];	

return 0;//complete
}
int dotmultiply_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res)
{
	int i,j,factor =supervise_matrix_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_int(lhs) || supervise_matrix_int(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_int(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_int(res);
			*res=new_matrix_int(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]*lhs->data[i][j];	

return 0;//complete
}
int dotmultiply_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res)
{
	int i,j,factor =supervise_matrix_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_char(lhs) || supervise_matrix_char(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_char(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_char(res);
			*res=new_matrix_char(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]*lhs->data[i][j];	

return 0;//complete
}
int dotmultiply_m_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res)
{
	int i,j,factor =supervise_matrix_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_float(lhs) || supervise_matrix_float(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_float(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_float(res);
			*res=new_matrix_float(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]*lhs->data[i][j];	

return 0;//complete
}
int dotmultiply_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
	int i,j,factor =supervise_matrix_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_double(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_double(res);
			*res=new_matrix_double(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]*lhs->data[i][j];	

return 0;//complete
}
int scalarmultiply_v_int(vector_int *rhs,int *lhs,vector_int *res)
{
	int i,factor =supervise_vector_int(res);
	SetValue set={0,0.0,0.0};
	if(lhs==0 || supervise_vector_int(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res= new_vector_int(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_int(res);
			*res=new_vector_int(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]*(*lhs);	

return 0;//complete
}
int scalarmultiply_v_char(vector_char *rhs,char *lhs,vector_char *res)
{
	int i,factor =supervise_vector_char(res);
	SetValue set={0,0.0,0.0};
	if(lhs==0 || supervise_vector_char(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res= new_vector_char(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_char(res);
			*res=new_vector_char(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]*(*lhs);	

return 0;//complete
}
int scalarmultiply_v_float(vector_float *rhs,float *lhs,vector_float *res)
{
	int i,factor =supervise_vector_float(res);
	SetValue set={0,0.0,0.0};
	if(lhs==0 || supervise_vector_float(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res= new_vector_float(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_float(res);
			*res=new_vector_float(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]*(*lhs);	

return 0;//complete
}
int scalarmultiply_v_double(vector_double *rhs,double *lhs,vector_double *res)
{
	int i,factor =supervise_vector_double(res);
	SetValue set={0,0.0,0.0};
	if(lhs==0 || supervise_vector_double(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res= new_vector_double(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_double(res);
			*res=new_vector_double(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]*(*lhs);	

return 0;//complete
}
int scalarmultiply_m_int(matrix_int *rhs,int *lhs,matrix_int *res) 
{
	int i,j,factor =supervise_matrix_int(res);
	SetValue set={0,0.0,0.0};
	if(lhs==0 || supervise_matrix_int(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res= new_matrix_int(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != rhs->col)
		{	
			delete_matrix_int(res);
			*res=new_matrix_int(rhs->row,rhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<rhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]*(*lhs);	

return 0;//complete
}
int scalarmultiply_m_char(matrix_char *rhs,char *lhs,matrix_char *res) 
{
	int i,j,factor =supervise_matrix_char(res);
	SetValue set={0,0.0,0.0};
	if(lhs==0 || supervise_matrix_char(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res= new_matrix_char(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != rhs->col)
		{	
			delete_matrix_char(res);
			*res=new_matrix_char(rhs->row,rhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<rhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]*(*lhs);	

return 0;//complete
}
int scalarmultiply_m_float(matrix_float *rhs,float *lhs,matrix_float *res) 
{
	int i,j,factor =supervise_matrix_float(res);
	SetValue set={0,0.0,0.0};
	if(lhs==0 || supervise_matrix_float(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res= new_matrix_float(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != rhs->col)
		{	
			delete_matrix_float(res);
			*res=new_matrix_float(rhs->row,rhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<rhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]*(*lhs);	

return 0;//complete
}
int scalarmultiply_m_double(matrix_double *rhs,double *lhs,matrix_double *res) 
{
	int i,j,factor =supervise_matrix_double(res);
	SetValue set={0,0.0,0.0};
	if(lhs==0 || supervise_matrix_double(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res= new_matrix_double(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != rhs->col)
		{	
			delete_matrix_double(res);
			*res=new_matrix_double(rhs->row,rhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<rhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]*(*lhs);	

return 0;//complete
}
int plus_v_int(vector_int *rhs,vector_int *lhs,vector_int *res)
{
	int i,factor =supervise_vector_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_int(lhs) || supervise_vector_int(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_int(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_int(res);
			*res=new_vector_int(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]+lhs->data[i];	

return 0;//complete
}
int plus_v_char(vector_char *rhs,vector_char *lhs,vector_char *res)
{
	int i,factor =supervise_vector_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_char(lhs) || supervise_vector_char(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_char(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_char(res);
			*res=new_vector_char(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]+lhs->data[i];	

return 0;//complete
}
int plus_v_float(vector_float *rhs,vector_float *lhs,vector_float *res)
{
	int i,factor =supervise_vector_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_float(lhs) || supervise_vector_float(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_float(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_float(res);
			*res=new_vector_float(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]+lhs->data[i];	

return 0;//complete
}
int plus_v_double(vector_double *rhs,vector_double *lhs,vector_double *res)
{
	int i,factor =supervise_vector_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_double(lhs) || supervise_vector_double(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_double(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_double(res);
			*res=new_vector_double(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]+lhs->data[i];	

return 0;//complete
}
int plus_m_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res)
{
	int i,j,factor =supervise_matrix_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_float(lhs) || supervise_matrix_float(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_float(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_float(res);
			*res=new_matrix_float(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]+lhs->data[i][j];	

return 0;//complete
}
int plus_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res)
{
	int i,j,factor =supervise_matrix_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_int(lhs) || supervise_matrix_int(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_int(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_int(res);
			*res=new_matrix_int(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]+lhs->data[i][j];	

return 0;//complete
}
int plus_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res)
{
	int i,j,factor =supervise_matrix_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_char(lhs) || supervise_matrix_char(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_char(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_char(res);
			*res=new_matrix_char(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]+lhs->data[i][j];	

return 0;//complete
}
int plus_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
	int i,j,factor =supervise_matrix_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_double(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_double(res);
			*res=new_matrix_double(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]+lhs->data[i][j];	

return 0;//complete
}
int minus_v_int(vector_int *rhs,vector_int *lhs,vector_int *res)
{
	int i,factor =supervise_vector_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_int(lhs) || supervise_vector_int(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_int(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_int(res);
			*res=new_vector_int(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]-lhs->data[i];	

return 0;//complete
}
int minus_v_char(vector_char *rhs,vector_char *lhs,vector_char *res)
{
	int i,factor =supervise_vector_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_char(lhs) || supervise_vector_char(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_char(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_char(res);
			*res=new_vector_char(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]-lhs->data[i];	

return 0;//complete
}
int minus_v_float(vector_float *rhs,vector_float *lhs,vector_float *res)
{
	int i,factor =supervise_vector_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_float(lhs) || supervise_vector_float(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_float(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_float(res);
			*res=new_vector_float(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]-lhs->data[i];	

return 0;//complete
}
int minus_v_double(vector_double *rhs,vector_double *lhs,vector_double *res)
{
	int i,factor =supervise_vector_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_double(lhs) || supervise_vector_double(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_double(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_double(res);
			*res=new_vector_double(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]-lhs->data[i];	

return 0;//complete
}
int minus_m_int(matrix_int *rhs,matrix_int *lhs,matrix_int *res)
{
	int i,j,factor =supervise_matrix_int(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_int(lhs) || supervise_matrix_int(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_int(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_int(res);
			*res=new_matrix_int(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]-lhs->data[i][j];	

return 0;//complete
}
int minus_m_char(matrix_char *rhs,matrix_char *lhs,matrix_char *res)
{
	int i,j,factor =supervise_matrix_char(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_char(lhs) || supervise_matrix_char(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_char(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_char(res);
			*res=new_matrix_char(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]-lhs->data[i][j];	

return 0;//complete
}
int minus_m_float(matrix_float *rhs,matrix_float *lhs,matrix_float *res)
{
	int i,j,factor =supervise_matrix_float(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_float(lhs) || supervise_matrix_float(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_float(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_float(res);
			*res=new_matrix_float(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]-lhs->data[i][j];	

return 0;//complete
}
int minus_m_double(matrix_double *rhs,matrix_double *lhs,matrix_double *res)
{
	int i,j,factor =supervise_matrix_double(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_double(lhs) || supervise_matrix_double(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_double(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_double(res);
			*res=new_matrix_double(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]-lhs->data[i][j];	

return 0;//complete
}

void copy_v_int(vector_int *rhs,vector_int *lhs)
{
	if(rhs != lhs)
	{
		int index1 = 0;
		int num	   = lhs->lenght;
		delete_vector_int(rhs);
		*rhs = new_vector_int(num);
		for(index1 =0 ;index1<num;index1++)
		{
			rhs->data[index1] = lhs->data[index1];
		}
	}
}//end scope copy_v_int
void copy_v_char(vector_char *rhs,vector_char *lhs)
{
	if(rhs != lhs)
	{
		int index1 = 0;
		int num	   = lhs->lenght;
		delete_vector_char(rhs);
		*rhs = new_vector_char(num);
		for(index1 =0 ;index1<num;index1++)
		{
			rhs->data[index1] = lhs->data[index1];
		}
	}
}//end scope copy_v_char
void copy_v_double(vector_double *rhs,vector_double *lhs)
{
	if(rhs != lhs)
	{
		int index1 = 0;
		int num	   = lhs->lenght;
		delete_vector_double(rhs);
		*rhs = new_vector_double(num);
		for(index1 =0 ;index1<num;index1++)
		{
			rhs->data[index1] = lhs->data[index1];
		}
	}
}//end scope copy_v_double
void copy_v_float(vector_float *rhs,vector_float *lhs)
{
	if(rhs != lhs)
	{
		int index1 = 0;
		int num	   = lhs->lenght;
		delete_vector_float(rhs);
		*rhs = new_vector_float(num);
		for(index1 =0 ;index1<num;index1++)
		{
			rhs->data[index1] = lhs->data[index1];
		}
	}
}//end scope copy_v_float

void copy_m_int(matrix_int *rhs,matrix_int *lhs)
{
	if(rhs != lhs)
	{
		int index1 = 0;
		int index2 = 0;
		int row	   = lhs->row;
		int col	   = lhs->col;
		delete_matrix_int(rhs);
		*rhs = new_matrix_int(row,col);
		for(index1 =0 ;index1<row;index1++)
		{
			for(index2 =0;index2<col;index2++)
			{
				rhs->data[index1][index2] = lhs->data[index1][index2];
			}
		}
	}
}//end scope copy_m_int
void copy_m_char(matrix_char *rhs,matrix_char *lhs)
{
	if(rhs != lhs)
	{
		int index1 = 0;
		int index2 = 0;
		int row	   = lhs->row;
		int col	   = lhs->col;
		delete_matrix_char(rhs);
		*rhs = new_matrix_char(row,col);
		for(index1 =0 ;index1<row;index1++)
		{
			for(index2 =0;index2<col;index2++)
			{
				rhs->data[index1][index2] = lhs->data[index1][index2];
			}
		}
	}
}//end scope copy_m_char

void copy_m_float(matrix_float *rhs,matrix_float *lhs)
{
	if(rhs != lhs)
	{
		int index1 = 0;
		int index2 = 0;
		int row	   = lhs->row;
		int col	   = lhs->col;
		delete_matrix_float(rhs);
		*rhs = new_matrix_float(row,col);
		for(index1 =0 ;index1<row;index1++)
		{
			for(index2 =0;index2<col;index2++)
			{
				rhs->data[index1][index2] = lhs->data[index1][index2];
			}
		}
	}
}//end scope copy_m_float

void copy_m_double(matrix_double *rhs,matrix_double *lhs)
{
	if(rhs != lhs)
	{
		int index1 = 0;
		int index2 = 0;
		int row	   = lhs->row;
		int col	   = lhs->col;
		delete_matrix_double(rhs);
		*rhs = new_matrix_double(row,col);
		for(index1 =0 ;index1<row;index1++)
		{
			for(index2 =0;index2<col;index2++)
			{
				rhs->data[index1][index2] = lhs->data[index1][index2];
			}
		}
	}
}//end scope copy_m_double

void swap_v_int(vector_int *rhs,vector_int *lhs)
{
	vector_int temp = new_vector_int(0);
	copy_v_int(&temp,rhs);
	copy_v_int(rhs,lhs);
	copy_v_int(lhs,&temp);
	delete_vector_int(&temp);
}// end scope swap_v_int

void swap_v_char(vector_char *rhs,vector_char *lhs)
{
	vector_char temp = new_vector_char(0);
	copy_v_char(&temp,rhs);
	copy_v_char(rhs,lhs);
	copy_v_char(lhs,&temp);
	delete_vector_char(&temp);
}// end scope swap_v_char

void swap_v_double(vector_double *rhs,vector_double *lhs)
{
	vector_double temp = new_vector_double(0);
	copy_v_double(&temp,rhs);
	copy_v_double(rhs,lhs);
	copy_v_double(lhs,&temp);
	delete_vector_double(&temp);
}// end scope swap_v_double

void swap_v_float(vector_float *rhs,vector_float *lhs)
{
	vector_float temp = new_vector_float(0);
	copy_v_float(&temp,rhs);
	copy_v_float(rhs,lhs);
	copy_v_float(lhs,&temp);
	delete_vector_float(&temp);
}// end scope swap_v_float

void swap_m_int(matrix_int *rhs,matrix_int *lhs)
{
	matrix_int temp = new_matrix_int(0,0);
	copy_m_int(&temp,rhs);
	copy_m_int(rhs,lhs);
	copy_m_int(lhs,&temp);
	delete_matrix_int(&temp);
}// end scope swap_m_int

void swap_m_char(matrix_char *rhs,matrix_char *lhs)
{
	matrix_char temp = new_matrix_char(0,0);
	copy_m_char(&temp,rhs);
	copy_m_char(rhs,lhs);
	copy_m_char(lhs,&temp);
	delete_matrix_char(&temp);
}// end scope swap_m_char

void swap_m_double(matrix_double *rhs,matrix_double *lhs)
{
	matrix_double temp = new_matrix_double(0,0);
	copy_m_double(&temp,rhs);
	copy_m_double(rhs,lhs);
	copy_m_double(lhs,&temp);
	delete_matrix_double(&temp);
}// end scope swap_m_double

void swap_m_float(matrix_float *rhs,matrix_float *lhs)
{
	matrix_float temp = new_matrix_float(0,0);
	copy_m_float(&temp,rhs);
	copy_m_float(rhs,lhs);
	copy_m_float(lhs,&temp);
	delete_matrix_float(&temp);
}// end scope swap_m_float

int compareEqual_v_int(vector_int *rhs,vector_int *lhs)
{
	int index =0;
	if(rhs->lenght != lhs->lenght)
	{
		return 0;
	}
	for(index =0 ;index<rhs->lenght;index++)
	{
		if(rhs->data[index] != lhs->data[index])
		{
			return 0;
		}
	}
	return 1;
}//end compareEqual_v_int
int compareEqual_v_char(vector_char *rhs,vector_char *lhs)
{
	int index =0;
	if(rhs->lenght != lhs->lenght)
	{
		return 0;
	}
	for(index =0 ;index<rhs->lenght;index++)
	{
		if(rhs->data[index] != lhs->data[index])
		{
			return 0;
		}
	}
	return 1;
}//end compareEqual_v_char
int compareEqual_v_float(vector_float *rhs,vector_float *lhs)
{
	int index =0;
	if(rhs->lenght != lhs->lenght)
	{
		return 0;
	}
	for(index =0 ;index<rhs->lenght;index++)
	{
		if(rhs->data[index] != lhs->data[index])
		{
			return 0;
		}
	}
	return 1;
}//end compareEqual_v_float
int compareEqual_v_double(vector_double *rhs,vector_double *lhs)
{
	int index =0;
	if(rhs->lenght != lhs->lenght)
	{
		return 0;
	}
	for(index =0 ;index<rhs->lenght;index++)
	{
		if(rhs->data[index] != lhs->data[index])
		{
			return 0;
		}
	}
	return 1;
}//end compareEqual_v_double
int compareEqual_m_int(matrix_int *rhs,matrix_int *lhs)
{
	int index  = 0;
	int index2 = 0;
	if(rhs->row != lhs->row || rhs->col != lhs->col)
	{
		return 0;
	}
	for(index =0 ;index<rhs->row;index++)
	{
		for(index2 =0;index2<rhs->col;index2++)
		{
			if(rhs->data[index][index2] != lhs->data[index][index2])
			{
				return 0;
			}
		}
	}
	return 1;
}//end compareEqual_m_int
int compareEqual_m_char(matrix_char *rhs,matrix_char *lhs)
{
	int index  = 0;
	int index2 = 0;
	if(rhs->row != lhs->row || rhs->col != lhs->col)
	{
		return 0;
	}
	for(index =0 ;index<rhs->row;index++)
	{
		for(index2 =0;index2<rhs->col;index2++)
		{
			if(rhs->data[index][index2] != lhs->data[index][index2])
			{
				return 0;
			}
		}
	}
	return 1;
}//end compareEqual_m_char
int compareEqual_m_float(matrix_float *rhs,matrix_float *lhs)
{
	int index  = 0;
	int index2 = 0;
	if(rhs->row != lhs->row || rhs->col != lhs->col)
	{
		return 0;
	}
	for(index =0 ;index<rhs->row;index++)
	{
		for(index2 =0;index2<rhs->col;index2++)
		{
			if(rhs->data[index][index2] != lhs->data[index][index2])
			{
				return 0;
			}
		}
	}
	return 1;
}//end compareEqual_m_float
int compareEqual_m_double(matrix_double *rhs,matrix_double *lhs)
{
	int index  = 0;
	int index2 = 0;
	if(rhs->row != lhs->row || rhs->col != lhs->col)
	{
		return 0;
	}
	for(index =0 ;index<rhs->row;index++)
	{
		for(index2 =0;index2<rhs->col;index2++)
		{
			if(rhs->data[index][index2] != lhs->data[index][index2])
			{
				return 0;
			}
		}
	}
	return 1;
}//end compareEqual_m_double
vector_int 		rowMatrix2Vectorint(matrix_int *rhs,int index)
{
	int index2 		=0;
	int col1		=0;
	vector_int temp = new_vector_int(0);
	if(rhs == NULL || index <0)
	{
		return temp;
	} //end if(rhs == NULL)
	else
	{
		col1 = rhs->col;
		temp = new_vector_int(rhs->col);
		for(index2 =0 ;index2 < col1;index2++)
		{
			temp.data[index2] = rhs->data[index][index2];
		}
	} // end else
	return temp;
} // end rowMatrix2Vectorint
vector_char 		rowMatrix2Vectorchar(matrix_char *rhs,int index)
{
	int index2 		=0;
	int col1		=0;
	vector_char temp = new_vector_char(0);
	if(rhs == NULL || index <0)
	{
		return temp;
	} //end if(rhs == NULL)
	else
	{
		col1 = rhs->col;
		temp = new_vector_char(rhs->col);
		for(index2 =0 ;index2 < col1;index2++)
		{
			temp.data[index2] = rhs->data[index][index2];
		}
	} // end else
	return temp;
} // end rowMatrix2Vectorchar
vector_float 		rowMatrix2Vectorfloat(matrix_float *rhs,int index)
{
	int index2 		=0;
	int col1		=0;
	vector_float temp = new_vector_float(0);
	if(rhs == NULL || index <0)
	{
		return temp;
	} //end if(rhs == NULL)
	else
	{
		col1 = rhs->col;
		temp = new_vector_float(rhs->col);
		for(index2 =0 ;index2 < col1;index2++)
		{
			temp.data[index2] = rhs->data[index][index2];
		}
	} // end else
	return temp;
} // end rowMatrix2Vectorfloat
vector_double 		rowMatrix2Vectordouble(matrix_double *rhs,int index)
{
	int index2 		=0;
	int col1		=0;
	vector_double temp = new_vector_double(0);
	if(rhs == NULL || index <0)
	{
		return temp;
	} //end if(rhs == NULL)
	else
	{
		col1 = rhs->col;
		temp = new_vector_double(rhs->col);
		for(index2 =0 ;index2 < col1;index2++)
		{
			temp.data[index2] = rhs->data[index][index2];
		}
	} // end else
	return temp;
} // end rowMatrix2Vectordouble

void swapRowMint(matrix_int *rhs,int row1,int row2)
{
	if(rhs == NULL)
	{
		return;
	}
	else
	{
		//do nothing
	}
	if(rhs->row <= row1 || rhs->row <= row2)
	{
		return;
	}
	else
	{
		//do nothing
	}
	int temp;
	int index =0;
	int num = rhs->col;
	for(index = 0;index<num;index++)
	{
		temp = rhs->data[row1][index];
		rhs->data[row1][index] = rhs->data[row2][index];
		rhs->data[row2][index] = temp;
	}
}// end swapRowMint
void swapRowMchar(matrix_char *rhs,int row1,int row2)
{
	if(rhs == NULL)
	{
		return;
	}
	else
	{
		//do nothing
	}
	if(rhs->row <= row1 || rhs->row <= row2)
	{
		return;
	}
	else
	{
		//do nothing
	}
	char temp;
    int index =0;
	int num = rhs->col;
	for(index = 0;index<num;index++)
	{
		temp = rhs->data[row1][index];
		rhs->data[row1][index] = rhs->data[row2][index];
		rhs->data[row2][index] = temp;
	}
} // end swapRowMchar

void swapRowMfloat(matrix_float *rhs,int row1,int row2)
{
	if(rhs == NULL)
	{
		return;
	}
	else
	{
		//do nothing
	}
	if(rhs->row <= row1 || rhs->row <= row2)
	{
		return;
	}
	else
	{
		//do nothing
	}
	float temp;
    int index =0;
	int num = rhs->col;
	for(index = 0;index<num;index++)
	{
		temp = rhs->data[row1][index];
		rhs->data[row1][index] = rhs->data[row2][index];
		rhs->data[row2][index] = temp;
	}
}//end swapRowMfloat
void swapRowMdouble(matrix_double *rhs,int row1,int row2)
{
	if(rhs == NULL)
	{
		return;
	}
	else
	{
		//do nothing
	}
	if(rhs->row <= row1 || rhs->row <= row2)
	{
		return;
	}
	else
	{
		//do nothing
	}
	double temp;
    int index =0;
	int num = rhs->col;
	for(index = 0;index<num;index++)
	{
		temp = rhs->data[row1][index];
		rhs->data[row1][index] = rhs->data[row2][index];
		rhs->data[row2][index] = temp;
	}
}//end swapRowMdouble
void minorMchar(matrix_char *rhs,int row,int col)
{
	matrix_char temp = new_matrix_char(0,0);
	int index,index2,index3=0,index4=0;
	int nCol = rhs->col;
	int nRow = rhs->row;
	if(rhs == NULL || row <0 || col <0)
	{
		return;
	} // end if(rhs == NULL || row <0 || col <0)
	else
	{
		// do nothing
	} //end else
	temp = new_matrix_char(rhs->row-1,rhs->col-1);
	for(index =0 ;index<nRow;index++)
	{
		if(index ==row)
		{
			continue;
		}
		else
		{
			//do nothing
		}
		index4 =0;
		for(index2 =0;index2<nCol;index2++)
		{	
			if(index2 == col)
			{
				continue;
			}
			else
			{
				// do nothing
			}
			temp.data[index3][index4++] = rhs->data[index][index2];
		}
		index3++;
	}
	delete_matrix_char(rhs);
	*rhs = temp;
}// end minorMchar(matrix_char *rhs,int row,int col)
void minorMint(matrix_int *rhs,int row,int col)
{
	matrix_int temp = new_matrix_int(0,0);
	int index,index2,index3=0,index4=0;
	int nCol = rhs->col;
	int nRow = rhs->row;
	if(rhs == NULL || row <0 || col <0)
	{
		return;
	} // end if(rhs == NULL || row <0 || col <0)
	else
	{
		// do nothing
	} //end else
	temp = new_matrix_int(rhs->row-1,rhs->col-1);
	for(index =0 ;index<nRow;index++)
	{
		if(index ==row)
		{
			continue;
		}
		else
		{
			//do nothing
		}
		index4 =0;
		for(index2 =0;index2<nCol;index2++)
		{	
			if(index2 == col)
			{
				continue;
			}
			else
			{
				// do nothing
			}
			temp.data[index3][index4++] = rhs->data[index][index2];
		}
		index3++;
	}
	delete_matrix_int(rhs);
	*rhs = temp;
}// end minorMint(matrix_int *rhs,int row,int col)
void minorMfloat(matrix_float *rhs,int row,int col)
{
	matrix_float temp = new_matrix_float(0,0);
	int index,index2,index3=0,index4=0;
	int nCol = rhs->col;
	int nRow = rhs->row;
	if(rhs == NULL || row <0 || col <0)
	{
		return;
	} // end if(rhs == NULL || row <0 || col <0)
	else
	{
		// do nothing
	} //end else
	temp = new_matrix_float(rhs->row-1,rhs->col-1);
	for(index =0 ;index<nRow;index++)
	{
		if(index ==row)
		{
			continue;
		}
		else
		{
			//do nothing
		}
		index4 =0;
		for(index2 =0;index2<nCol;index2++)
		{	
			if(index2 == col)
			{
				continue;
			}
			else
			{
				// do nothing
			}
			temp.data[index3][index4++] = rhs->data[index][index2];
		}
		index3++;
	}
	delete_matrix_float(rhs);
	*rhs = temp;
}// end minorMfloat(matrix_float *rhs,int row,int col)
void minorMdouble(matrix_double *rhs,int row,int col)
{
	matrix_double temp = new_matrix_double(0,0);
	int index,index2,index3=0,index4=0;
	int nCol = rhs->col;
	int nRow = rhs->row;
	if(rhs == NULL || row <0 || col <0)
	{
		return;
	} // end if(rhs == NULL || row <0 || col <0)
	else
	{
		// do nothing
	} //end else
	temp = new_matrix_double(rhs->row-1,rhs->col-1);
	for(index =0 ;index<nRow;index++)
	{
		if(index ==row)
		{
			continue;
		}
		else
		{
			//do nothing
		}
		index4 =0;
		for(index2 =0;index2<nCol;index2++)
		{	
			if(index2 == col)
			{
				continue;
			}
			else
			{
				// do nothing
			}
			temp.data[index3][index4++] = rhs->data[index][index2];
		}
		index3++;
	}
	delete_matrix_double(rhs);
	*rhs = temp;
}// end minorMdouble(matrix_double *rhs,int row,int col)
void cutRowMchar(matrix_char *rhs,int row)
{
	if(rhs == NULL || row < 0)
	{
		return;
	} // end if(rhs == NULL || row < 0)
	else
	{
		//do nothing 
	} // end
	matrix_char temp = new_matrix_char(rhs->row-1,rhs->col);
	int index,index2,index3=0;
	int numRow = rhs->row;
	int numCol = rhs->col;
	for(index=0;index<numRow;index++)
	{
		if(row == index)
		{
			continue;
		}//end 	if(row == index)
		else
		{
			// do nothing
		}//end else if(row == index)
		for(index2 = 0;index2<numCol;index2++)
		{
			temp.data[index3][index2] = rhs->data[index][index2];
		} // end for(index2 = 0;index2<numCol;index2++)
		index3++;
	}
	delete_matrix_char(rhs);
	*rhs = temp;
} //end cutRowMchar(matrix_char *rhs,int row)
void cutRowMint(matrix_int *rhs,int row)
{
	if(rhs == NULL || row < 0)
	{
		return;
	} // end if(rhs == NULL || row < 0)
	else
	{
		//do nothing 
	} // end
	matrix_int temp = new_matrix_int(rhs->row-1,rhs->col);
	int index,index2,index3=0;
	int numRow = rhs->row;
	int numCol = rhs->col;
	for(index=0;index<numRow;index++)
	{
		if(row == index)
		{
			continue;
		}//end 	if(row == index)
		else
		{
			// do nothing
		}//end else if(row == index)
		for(index2 = 0;index2<numCol;index2++)
		{
			temp.data[index3][index2] = rhs->data[index][index2];
		} // end for(index2 = 0;index2<numCol;index2++)
		index3++;
	}
	delete_matrix_int(rhs);
	*rhs = temp;
} //end cutRowMint(matrix_int *rhs,int row)
void cutRowMfloat(matrix_float *rhs,int row)
{
	if(rhs == NULL || row < 0)
	{
		return;
	} // end if(rhs == NULL || row < 0)
	else
	{
		//do nothing 
	} // end
	matrix_float temp = new_matrix_float(rhs->row-1,rhs->col);
	int index,index2,index3=0;
	int numRow = rhs->row;
	int numCol = rhs->col;
	for(index=0;index<numRow;index++)
	{
		if(row == index)
		{
			continue;
		}//end 	if(row == index)
		else
		{
			// do nothing
		}//end else if(row == index)
		for(index2 = 0;index2<numCol;index2++)
		{
			temp.data[index3][index2] = rhs->data[index][index2];
		} // end for(index2 = 0;index2<numCol;index2++)
		index3++;
	}
	delete_matrix_float(rhs);
	*rhs = temp;
} //end cutRowMfloat(matrix_float *rhs,int row)

void cutRowMdouble(matrix_double *rhs,int row)
{
	if(rhs == NULL || row < 0)
	{
		return;
	} // end if(rhs == NULL || row < 0)
	else
	{
		//do nothing 
	} // end
	matrix_double temp = new_matrix_double(rhs->row-1,rhs->col);
	int index,index2,index3=0;
	int numRow = rhs->row;
	int numCol = rhs->col;
	for(index=0;index<numRow;index++)
	{
		if(row == index)
		{
			continue;
		}//end 	if(row == index)
		else
		{
			// do nothing
		}//end else if(row == index)
		for(index2 = 0;index2<numCol;index2++)
		{
			temp.data[index3][index2] = rhs->data[index][index2];
		} // end for(index2 = 0;index2<numCol;index2++)
		index3++;
	}
	delete_matrix_double(rhs);
	*rhs = temp;
} //end cutRowMdouble(matrix_double *rhs,int row)