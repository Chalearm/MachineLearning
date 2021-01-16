#include "simMatTemp.h"
#include <stdio.h>
#include "debug.h"
vector_temp 	    new_vector_temp(usint size)
{
	vector_temp data ={0,0};
	if(size >0)
	{
		data.data = (element*)malloc(sizeof(element)*size);
	    printOpt(__LINE__-1,"new_vector_temp","simSprTempVect.c",(void*)data.data,0);	
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
matrix_temp	     	new_matrix_temp(usint row,usint col)
{
	int i=0;
	matrix_temp data = {0,0,0};
	if(row ==0 || col==0) return data;

	data.data = (element**)malloc(sizeof(element*)*row);
    printOpt(__LINE__-1,"new_matrix_temp","simSprTempVect.c",(void*)data.data,0);	
	if(data.data ==0) return data;
	
	data.row =row;
	data.col =col;
	for(i=0;i<data.row;i++)
	{
		data.data[i] =0;
		data.data[i] = (element*)malloc(sizeof(element)*col);
    printOpt(__LINE__-1,"new_matrix_temp","simSprTempVect.c",(void*)data.data[i],0);	
		if(data.data[i] ==0) data.col--;
	}
return data;
}
void delete_vector_temp(vector_temp *rhs)
{
	
	if(rhs==0)return;
	if( rhs->lenght >0 && rhs->data!=0)
	{    printOpt(__LINE__+1,"delete_vector_temp","simSprTempVect.c",(void*)rhs->data,1);	
		free(rhs->data);
		rhs->data=0;
		rhs->lenght=0;
	}
}
void delete_matrix_temp(matrix_temp *rhs)
{
	if(rhs==0)return;
	int i=0;
	if(rhs->data !=0)
	{
		for(i=0;i<rhs->row;i++)
		{printOpt(__LINE__+1,"delete_matrix_temp","simSprTempVect.c",(void*)rhs->data[i],1);	
			free(rhs->data[i]);
			rhs->data[i] =0;
		}
printOpt(__LINE__+1,"delete_matrix_temp","simSprTempVect.c",(void*)rhs->data,1);			
		free(rhs->data);
		rhs->data=0;
		rhs->row =0;
		rhs->col =0;
	}	
}

void initial_vector_temp(vector_temp* rhs,SetValue set)
{
	if(rhs->data ==0) return;
	if(rhs->lenght==0)return;
	int i=0;	
	int del=0;
	switch(set.set)
	{
		case 0:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(element)set.max;	
		break;
		case 1:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(element)(set.min+rand()%(int)(1+set.max-set.min));
		break;
		case 2:
			for(i=0;i<rhs->lenght;i++)
				rhs->data[i] =(element)set.max*((i)%2==0)+(element)set.min*(i%2==1);
		break;
		case 3:
			del = (element)((set.max-set.min)/(double)(rhs->lenght));
			set.set=2;
			if(del==0) initial_vector_temp(rhs,set);
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
void initial_matrix_temp(matrix_temp* rhs,SetValue set)
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
				rhs->data[i][j] =(element)set.max;	
		break;
		case 1:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(element)(set.min+rand()%(int)(1+set.max-set.min));
		break;
		case 2:
			for(i=0;i<rhs->row;i++)
			   for(j=0;j<rhs->col;j++)
				rhs->data[i][j] =(element)set.max*((j+i)%2==0)+(element)set.min*((j+i)%2==1);
		break;
		case 3:
			del = (element)((set.max-set.min)/(double)(rhs->row*rhs->col));
			set.set=2;
			if(del==0) initial_matrix_temp(rhs,set);
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

int supervise_matrix_temp(matrix_temp *rhs)
{
	if(rhs == NULL){ return  1;}
	if(rhs->data ==0 && (rhs->row !=0 || rhs->col !=0)){return 1;}  //Null matrix
	if((rhs->col ==0||rhs->row==0) && rhs->data != 0){return 2;} //Construction isn't compelete.
	return 0; //complete !!!
}
int supervise_vector_temp(vector_temp *rhs)
{
	if(rhs == NULL) return 1;	//NULL matrix
	if(rhs->data ==0 && rhs->lenght !=0) return 2; //Null matrix
	if(rhs->lenght==0&& rhs->data !=0) return 3; //Construction isn't complete.
	return 0; //complete !!!
}
void print_vector_temp(vector_temp *rhs,int option)
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
void print_matrix_temp(matrix_temp *rhs,int option)
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
/*
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
			
}*/
/*
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
*/
/* operation */
int multiply_v_m_temp(vector_temp *rhs,matrix_temp *lhs,matrix_temp *res)
{
	int i,j,factor =supervise_matrix_temp(res);
	if(supervise_vector_temp(rhs) || supervise_matrix_temp(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=1)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
	
		*res =new_matrix_temp(rhs->lenght,lhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col !=lhs->col)
		{
			delete_matrix_temp(res);
			*res=new_matrix_temp(rhs->lenght,lhs->col);
		}
	}

	for(i=0;i<rhs->lenght;i++)
	{
		for(j=0;j<lhs->col;j++)
		   res->data[i][j]= rhs->data[i]*lhs->data[0][j];	
	}	

return 0;//complete
}
int multiply_vt_m_temp(vector_temp *rhs,matrix_temp *lhs,matrix_temp *res)
{
	int i,j,factor =supervise_matrix_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_temp(rhs) || supervise_matrix_temp(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_temp(1,lhs->col);
		initial_matrix_temp(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != 1 || res->col !=lhs->col)
		{	
			delete_matrix_temp(res);
			*res=new_matrix_temp(1,lhs->col);
			
		}
		initial_matrix_temp(res,set);
	}

		for(i=0;i<lhs->col;i++)
		 for(j=0;j<rhs->lenght;j++)
		   res->data[0][i]+= rhs->data[j]*lhs->data[j][i];	

return 0;//complete
}
int multiply_v_mt_temp(vector_temp *rhs,matrix_temp *lhs,matrix_temp *res)
{
	int i,j,factor =supervise_matrix_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_temp(rhs) || supervise_matrix_temp(lhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=1)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_temp(rhs->lenght,lhs->row);
		//initial_matrix_temp(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col !=lhs->row)
		{	
			delete_matrix_temp(res);
			*res=new_matrix_temp(rhs->lenght,lhs->row);
			
		}
		//initial_matrix_temp(res,set);
	}

		for(i=0;i<rhs->lenght;i++)
		 for(j=0;j<lhs->row;j++)
		   res->data[i][j]= rhs->data[i]*lhs->data[j][0];	

return 0;//complete
}
int multiply_m_v_temp(matrix_temp *rhs,vector_temp *lhs,vector_temp *res)
{
	int i,j,factor =supervise_vector_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_temp(lhs) || supervise_matrix_temp(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_vector_temp(rhs->row);
		initial_vector_temp(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != lhs->lenght)
		{	
			delete_vector_temp(res);
			*res=new_vector_temp(rhs->row);
			
		}
		initial_vector_temp(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->lenght;j++)
		   res->data[i]+= rhs->data[i][j]*lhs->data[j];	

return 0;//complete
}
int multiply_mt_v_temp(matrix_temp *rhs,vector_temp *lhs,vector_temp *res)
{
	int i,j,factor =supervise_vector_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_temp(lhs) || supervise_matrix_temp(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_vector_temp(rhs->col);
		initial_vector_temp(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != lhs->lenght)
		{	
			delete_vector_temp(res);
			*res=new_vector_temp(rhs->col);
			
		}
		initial_vector_temp(res,set);
	}

		for(i=0;i<rhs->col;i++)
		 for(j=0;j<lhs->lenght;j++)
		   res->data[i]+= rhs->data[j][i]*lhs->data[j];	

return 0;//complete
}
int multiply_m_vt_temp(matrix_temp *rhs,vector_temp *lhs,matrix_temp *res)
{
	int i,j,factor =supervise_matrix_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_temp(lhs) || supervise_matrix_temp(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res=new_matrix_temp(rhs->row,lhs->lenght);
	//	initial_matrix_temp(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->lenght)
		{	
			delete_matrix_temp(res);
			*res=new_matrix_temp(rhs->row,lhs->lenght);
			
		}
		//initial_matrix_temp(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->lenght;j++)
		   	res->data[i][j]= rhs->data[i][0]*lhs->data[j];	

return 0;//complete
} 
int multiply_m_m_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res)
{
	int i,j,k,factor =supervise_matrix_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_temp(lhs) || supervise_matrix_temp(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_temp(rhs->row,lhs->col);
		initial_matrix_temp(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_temp(res);
			*res= new_matrix_temp(rhs->row,lhs->col);
			
		}
		initial_matrix_temp(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
			for(k=0;k<rhs->col;k++)
		   	res->data[i][j]+= rhs->data[i][k]*lhs->data[k][j];	

return 0;//complete
}
int multiply_mt_m_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res)
{
	int i,j,k,factor =supervise_matrix_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_temp(lhs) || supervise_matrix_temp(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->row!=rhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res=new_matrix_temp(rhs->col,lhs->col);
		initial_matrix_temp(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->col || res->col != lhs->col)
		{	
			delete_matrix_temp(res);
			*res=new_matrix_temp(rhs->col,lhs->col);
			
		}
		initial_matrix_temp(res,set);
	}

		for(i=0;i<rhs->col;i++)
		 for(j=0;j<lhs->col;j++)
			for(k=0;k<rhs->row;k++)
		   	res->data[i][j]+= rhs->data[k][i]*lhs->data[k][j];	

return 0;//complete
}
int multiply_m_mt_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res)
{
	int i,j,k,factor =supervise_matrix_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_temp(lhs) || supervise_matrix_temp(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_temp(rhs->row,lhs->row);
		initial_matrix_temp(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->col || res->col != lhs->col)
		{	
			delete_matrix_temp(res);
			*res=new_matrix_temp(rhs->row,lhs->row);
	
		}
		initial_matrix_temp(res,set);
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->row;j++)
			for(k=0;k<rhs->col;k++)
		   	res->data[i][j]+= rhs->data[i][k]*lhs->data[j][k];	

return 0;//complete
}
int multiply_v_vt_temp(vector_temp *rhs,vector_temp *lhs,matrix_temp *res)
{
	int i,j,factor =supervise_matrix_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_temp(lhs) || supervise_vector_temp(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res=new_matrix_temp(rhs->lenght,lhs->lenght);
		initial_matrix_temp(res,set);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->lenght || res->col != lhs->lenght)
		{	
			delete_matrix_temp(res);
			*res=new_matrix_temp(rhs->lenght,lhs->lenght);
			
		}
		initial_matrix_temp(res,set);
	}

		for(i=0;i<rhs->lenght;i++)
		 for(j=0;j<lhs->lenght;j++)
		   	res->data[i][j]= rhs->data[i]*lhs->data[j];	

return 0;//complete
}
int multiply_vt_v_temp(vector_temp *rhs,vector_temp *lhs,int *res)//dot product
{
	int i,j,factor =(res==0);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_temp(lhs) || supervise_vector_temp(rhs))	
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
int dotmultiply_v_temp(vector_temp *rhs,vector_temp *lhs,vector_temp *res)
{
	int i,factor =supervise_vector_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_temp(lhs) || supervise_vector_temp(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_temp(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_temp(res);
			*res=new_vector_temp(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]*lhs->data[i];	

return 0;//complete
}
int dotmultiply_m_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res)
{
	int i,j,factor =supervise_matrix_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_temp(lhs) || supervise_matrix_temp(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_temp(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_temp(res);
			*res=new_matrix_temp(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]*lhs->data[i][j];	

return 0;//complete
}
int scalarmultiply_v_temp(vector_temp *rhs,element *lhs,vector_temp *res)
{
	int i,factor =supervise_vector_temp(res);
	SetValue set={0,0.0,0.0};
	if(lhs==0 || supervise_vector_temp(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res= new_vector_temp(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_temp(res);
			*res=new_vector_temp(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]*(*lhs);	

return 0;//complete
}
int scalarmultiply_m_temp(matrix_temp *rhs,element *lhs,matrix_temp *res)
{
	int i,j,factor =supervise_matrix_temp(res);
	SetValue set={0,0.0,0.0};
	if(lhs==0 || supervise_matrix_temp(rhs))	
	{
		return 1;// failed 
	}
	if(factor==1)
	{
		*res= new_matrix_temp(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != rhs->col)
		{	
			delete_matrix_temp(res);
			*res=new_matrix_temp(rhs->row,rhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<rhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]*(*lhs);	

return 0;//complete
} 
int plus_v_temp(vector_temp *rhs,vector_temp *lhs,vector_temp *res)
{
	int i,factor =supervise_vector_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_temp(lhs) || supervise_vector_temp(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_temp(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_temp(res);
			*res=new_vector_temp(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]+lhs->data[i];	

return 0;//complete
}
int plus_m_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res)
{
	int i,j,factor =supervise_matrix_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_temp(lhs) || supervise_matrix_temp(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_temp(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_temp(res);
			*res=new_matrix_temp(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]+lhs->data[i][j];	

return 0;//complete
}
int minus_v_temp(vector_temp *rhs,vector_temp *lhs,vector_temp *res)
{
	int i,factor =supervise_vector_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_vector_temp(lhs) || supervise_vector_temp(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->lenght!=rhs->lenght)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_vector_temp(rhs->lenght);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->lenght != rhs->lenght)
		{	
			delete_vector_temp(res);
			*res=new_vector_temp(rhs->lenght);
	
		}
	}

		 for(i=0;i<rhs->lenght;i++)
		   	res->data[i]= rhs->data[i]-lhs->data[i];	

return 0;//complete
}
int minus_m_temp(matrix_temp *rhs,matrix_temp *lhs,matrix_temp *res)
{
	int i,j,factor =supervise_matrix_temp(res);
	SetValue set={0,0.0,0.0};
	if(supervise_matrix_temp(lhs) || supervise_matrix_temp(rhs))	
	{
		return 1;// failed 
	}
	if(lhs->col!=rhs->col || rhs->row != lhs->row)
	{
		return 2; //failed size
	}
	if(factor==1)
	{
		*res= new_matrix_temp(rhs->row,rhs->col);
	}
	else if(factor==2) 
	{
		return 3; // failed to get result
	}
	else if(factor==0)
	{
		if(res->row != rhs->row || res->col != lhs->col)
		{	
			delete_matrix_temp(res);
			*res=new_matrix_temp(rhs->row,lhs->col);
	
		}
	}

		for(i=0;i<rhs->row;i++)
		 for(j=0;j<lhs->col;j++)
		   	res->data[i][j]= rhs->data[i][j]-lhs->data[i][j];	

return 0;//complete
}
void copy_v_temp(vector_temp *rhs,vector_temp *lhs)
{
	if(rhs != lhs)
	{
		int index1 = 0;
		int num	   = lhs->lenght;
		delete_vector_temp(rhs);
		*rhs = new_vector_temp(num);
		for(index1 =0 ;index1<num;index1++)
		{
			rhs->data[index1] = lhs->data[index1];
		}
	}
}//end scope copy_v_temp
void copy_m_temp(matrix_temp *rhs,matrix_temp *lhs)
{
	if(rhs != lhs)
	{
		int index1 = 0;
		int index2 = 0;
		int row	   = lhs->row;
		int col	   = lhs->col;
		delete_matrix_temp(rhs);
		*rhs = new_matrix_temp(row,col);
		for(index1 =0 ;index1<row;index1++)
		{
			for(index2 =0;index2<col;index2++)
			{
				rhs->data[index1][index2] = lhs->data[index1][index2];
			}
		}
	}
}//end scope copy_m_temp
void swap_v_temp(vector_temp *rhs,vector_temp *lhs)
{
	vector_temp dummy= new_vector_temp(0);
	copy_v_temp(&dummy,rhs);
	copy_v_temp(rhs,lhs);
	copy_v_temp(lhs,&dummy);
	delete_vector_temp(&dummy);
}// end scope swap_v_temp
void swap_m_temp(matrix_temp *rhs,matrix_temp *lhs)
{
	matrix_temp dummy= new_matrix_temp(0,0);
	copy_m_temp(&dummy,rhs);
	copy_m_temp(rhs,lhs);
	copy_m_temp(lhs,&dummy);
	delete_matrix_temp(&dummy);
}// end scope swap_m_temp
void minorMtemp(matrix_temp *rhs,int row,int col)
{
	matrix_temp dummy= new_matrix_temp(0,0);
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
	dummy = new_matrix_temp(rhs->row-1,rhs->col-1);
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
			dummy.data[index3][index4++] = rhs->data[index][index2];
		}
		index3++;
	}
	delete_matrix_temp(rhs);
	*rhs = dummy;
}// end minorMtemp(matrix_temp *rhs,int row,int col)
void cutRowMtemp(matrix_temp *rhs,int row)
{
	if(rhs == NULL || row < 0)
	{
		return;
	} // end if(rhs == NULL || row < 0)
	else
	{
		//do nothing 
	} // end
	matrix_temp dummy = new_matrix_temp(rhs->row-1,rhs->col);
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
			dummy.data[index3][index2] = rhs->data[index][index2];
		} // end for(index2 = 0;index2<numCol;index2++)
		index3++;
	}
	delete_matrix_temp(rhs);
	*rhs = dummy;
} //end cutRowMtemp(matrix_temp *rhs,int row)
void swapRowMtemp(matrix_temp *rhs,int row1,int row2)
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
	element dummy;
	int index =0;
	int num = rhs->col;
	for(index = 0;index<num;index++)
	{
		dummy = rhs->data[row1][index];
		rhs->data[row1][index] = rhs->data[row2][index];
		rhs->data[row2][index] = dummy;
	}
}// end swapRowMtemp
int compareEqual_v_temp(vector_temp *rhs,vector_temp *lhs)
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
}//end compareEqual_v_temp
int compareEqual_m_temp(matrix_temp *rhs,matrix_temp *lhs)
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
}//end compareEqual_m_temp
vector_temp 		rowMatrix2Vectortemp(matrix_temp *rhs,int index)
{
	int index2 		=0;
	int col1		=0;
	vector_temp dummy = new_vector_temp(0);
	if(rhs == NULL || index <0)
	{
		return dummy;
	} //end if(rhs == NULL)
	else
	{
		col1 = rhs->col;
		dummy = new_vector_temp(rhs->col);
		for(index2 =0 ;index2 < col1;index2++)
		{
			dummy.data[index2] = rhs->data[index][index2];
		}
	} // end else
	return dummy;
} // end rowMatrix2Vectortemp
element determinant(matrix_temp *a)
{
	element det=0;
	int index,index2,index0,index3;
	
	matrix_temp b = new_matrix_temp(0,0);
	if(a->row <1)
	{
		return 	det;
	}
	else if(a->row ==1)
	{
		return a->data[0][0];
	}
	else if(a->row ==2)
	{
		return (a->data[0][0]*a->data[1][1])-(a->data[0][1]*a->data[1][0]);
	}
	else
	{
	   b = new_matrix_temp(a->row-1,a->row-1);
	   for(index0 = 0 ;index0 < a->row;index0++)
	   {
		
		index3 =0 ;
		for(index = 0;index <a->row;index++)
		{
		   if(index0 == index)
		   {
			continue;
		   }
		   else
		   {
			//do nothing
		   }	
		   for(index2 =1;index2 <a->row;index2++)
		   {
			b.data[index3][index2-1] =a->data[index][index2];
		   }
		   index3++;
		}
		det += (((index0%2)==0)?1.0:-1.0)*a->data[index0][0]*determinant(&b);
	    }

	}
	delete_matrix_temp(&b);
	return det;
}
void colFactorMatrix(matrix_temp *a,matrix_temp *c)
{
	int index,index2,index3,index4,index5,index6;
	element det;
	matrix_temp b = new_matrix_temp(0,0);
	for(index =0;index < a->row;index++)
	{
	  for(index2=0;index2<a->col;index2++)
	  {
		b = new_matrix_temp(a->row-1,a->row-1);
		index5 = 0;
		for(index3=0;index3<a->row;index3++)
		{
			if(index3==index2)
			{
				continue;
			}
			else
			{
				//do noting
			}
			index6 = 0;
			for(index4=0;index4<a->col;index4++)
			{
			    if(index4==index)
			    {
				continue;
			    }
			    else
		            {
				//do nothing		
			    }
			    b.data[index5][index6] = a->data[index3][index4];
			    index6++;
			}
			index5++;
		}
		det = determinant(&b);
		c->data[index][index2]  = det*((index+index2)%2==1?-1:1);
		
	  }
	}
	delete_matrix_temp(&b);

}
void matrixInverse(matrix_temp *a,matrix_temp *c)
{
	element detInverse = 1.0/determinant(a);
	colFactorMatrix(a,c);
 	scalarmultiply_m_temp(c,&detInverse,c); 
}
