#include "simMatChar.h"
#include <stdio.h>

vector_char 	    new_vector_char(usint size)
{
	vector_char data ={0,0};
	if(size >0)
	{
		data.data = (element*)malloc(sizeof(element)*size);
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
matrix_char	     	new_matrix_char(usint row,usint col)
{
	int i=0;
	printf("newMatrix:r:%d c:%d %d\n",row,col,row*sizeof(element*));
	matrix_char data = {0,0,0};
	if(row ==0 || col==0) return data;
	printf("element size;%d\n",sizeof(element));
	data.data = (element**)malloc(row*sizeof(element*));
	printf("newOK\n");
	if(data.data ==0) return data;
	
	data.row =row;
	data.col =col;
	for(i=0;i<data.row;i++)
	{
		data.data[i] =0;
		data.data[i] = (element*)malloc(sizeof(element)*col);
		if(data.data[i] ==0) data.col--;
	}
return data;
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
void delete_matrix_char(matrix_char *rhs)
{
	printf("del: rhs:%p\n",rhs);
	if(rhs==0)return;
	int i=0;
	printf("row: %d\n",rhs->row);
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

int supervise_matrix_char(matrix_char *rhs)
{
	if(rhs->data ==0){return 1;}  //Null matrix
	if(rhs->col ==0){return 2;} //Construction isn't compelete.
	return 0; //complete !!!
}
int supervise_vector_char(vector_char *rhs)
{
	if(rhs->data ==0) return 1; //Null matrix
	if(rhs->lenght==0) return 2; //Construction isn't complete.
	return 0; //complete !!!
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
/* operation */
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
int multiply_vt_v_char(vector_char *rhs,vector_char *lhs,int *res)//dot product
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
int scalarmultiply_v_char(vector_char *rhs,element *lhs,vector_char *res)
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
int scalarmultiply_m_char(matrix_char *rhs,element *lhs,matrix_char *res)
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
void copy_m_char(matrix_char *rhs,matrix_char *lhs)
{
	printf("core 5\n");
	if(rhs != lhs)
	{
		int index1 = 0;
		int index2 = 0;
		int row	   = lhs->row;
		int col	   = lhs->col;
	printf("core 6\n");
		delete_matrix_char(rhs);
	printf("core 6.5 r:%d c:%d\n",row,col);
		*rhs = new_matrix_char(row,col);
	printf("core 7\n");
		for(index1 =0 ;index1<row;index1++)
		{
			for(index2 =0;index2<col;index2++)
			{
				rhs->data[index1][index2] = lhs->data[index1][index2];
			}
		}
	}
}//end scope copy_m_char
void swap_v_char(vector_char *rhs,vector_char *lhs)
{
	vector_char dummy= new_vector_char(0);
	copy_v_char(&dummy,rhs);
	copy_v_char(rhs,lhs);
	copy_v_char(lhs,&dummy);
	delete_vector_char(&dummy);
}// end scope swap_v_char
void swap_m_char(matrix_char *rhs,matrix_char *lhs)
{
	matrix_char dummy= new_matrix_char(0,0);
	copy_m_char(&dummy,rhs);
	copy_m_char(rhs,lhs);
	copy_m_char(lhs,&dummy);
	delete_matrix_char(&dummy);
}// end scope swap_m_char
void minorMchar(matrix_char *rhs,int row,int col)
{
	matrix_char dummy= new_matrix_char(0,0);
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
	dummy = new_matrix_char(rhs->row-1,rhs->col-1);
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
	delete_matrix_char(rhs);
	*rhs = dummy;
}// end minorMchar(matrix_char *rhs,int row,int col)
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
	matrix_char dummy = new_matrix_char(rhs->row-1,rhs->col);
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
	delete_matrix_char(rhs);
	*rhs = dummy;
} //end cutRowMchar(matrix_char *rhs,int row)
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
	element dummy;
	int index =0;
	int num = rhs->col;
	for(index = 0;index<num;index++)
	{
		dummy = rhs->data[row1][index];
		rhs->data[row1][index] = rhs->data[row2][index];
		rhs->data[row2][index] = dummy;
	}
}// end swapRowMchar
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
int compareEqual_m_char(matrix_char *rhs,matrix_char *lhs)
{
	int index  = 0;
	int index2 = 0;

	printf("core com_m_char\n");
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
vector_char 		rowMatrix2Vectorchar(matrix_char *rhs,int index)
{
	int index2 		=0;
	int col1		=0;
	vector_char dummy = new_vector_char(0);
	if(rhs == NULL || index <0)
	{
		return dummy;
	} //end if(rhs == NULL)
	else
	{
		col1 = rhs->col;
		dummy = new_vector_char(rhs->col);
		for(index2 =0 ;index2 < col1;index2++)
		{
			dummy.data[index2] = rhs->data[index][index2];
		}
	} // end else
	return dummy;
} // end rowMatrix2Vectorchar
