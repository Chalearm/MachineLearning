#include "simSprTempVect.h"
#include "simMatTemp.h"
#include "debug.h"
int check_sprVect_tempObj(sprVect_temp* obj)
{
	// 0 is false 1 is true
	if(obj !=NULL)
	{
		if(obj->id != NULL && obj->data !=NULL && obj->lenght >0)
		{
			return 1;
		}
		else if(obj->id == NULL && obj->data == NULL && obj->lenght ==0)
		{	
			return 1;
		}
		else
		{
			//do nothing
		}
	}
	else
	{
		//do nothing
	}
	return 0;
}
int makeEmptySprVect_temp(sprVect_temp* obj)
{	
	if(check_sprVect_tempObj(obj) == 0)
	{
		return 0;
	}
	else
	{
		printOpt(__LINE__+1,"makeEmptySprVect_temp","simSprTempVect.c",(void*)obj->data ,1);		
		free(obj->data);
		printOpt(__LINE__+1,"makeEmptySprVect_temp","simSprTempVect.c",(void*)obj->id ,1);	
		free(obj->id);
		obj->lenght = 0;
		obj->data   = NULL;
		obj->id     = NULL;
	}
	return 1;
}
// 0 is false 1 is true, -1 is count fail
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

*/
/*
typedef struct{
	temp set;
	double max;
	double min;
*/

int initial_sprVect_temp(sprVect_temp* rhs,SetValue opt)
{
	int index =0 ;
	double factor1;
	// 0 is false 1 is true, -1 is count fail
	if(check_sprVect_tempObj(rhs) == 0)
	{
		return 0;
	}
	else
	{
		//do nothing
	}
	switch(opt.set)
	{	
		case 0:  //all element 0
			for(index = 0;index<rhs->lenght;index++)
			{	
				rhs->data[index] = 0;
			}
			break;
		case 1: //random max - min
			for(index = 0;index<rhs->lenght;index++)
			{
	   			rhs->data[index] =(element)(opt.min+rand()%(int)(1+opt.max-opt.min));
			}
			break;
		case 2:
			for(index = 0;index<rhs->lenght;index++)
			{
				rhs->data[index] = (index%2==0)?opt.max:opt.min;
			}
			break;
		case 3:
			factor1 = opt.max-opt.min;
			factor1 = factor1/(double)rhs->lenght;
			for(index =0;index<rhs->lenght;index++)
			{
				rhs->data[index] = (index ==0)?opt.min:(((double)rhs->data[index-1])+factor1);
			}
			break;
	}
	return 1;
}
// 0 is false 1 is true
sprVect_temp new_sprVect_temp(int lenght)
{
	sprVect_temp data = {0,NULL,NULL};
	if(lenght > 0) //is constructor
	{
		// lenght>0; using after called constructor already
		data.lenght = lenght;
		data.data   = (element*)malloc(sizeof(element)*lenght);
        printOpt(__LINE__-1,"new_sprVect_temp","simSprTempVect.c",(void*)data.data ,0);	
		data.id     = (int*)malloc(sizeof(int)*lenght);
	    printOpt(__LINE__-1,"new_sprVect_temp","simSprTempVect.c",(void*)data.id ,0);	
	}
	else
	{
		//do nothing
	}
	return data;
		
}
int countEleVect_temp(vector_temp* obj,int set) //0 count no zero, 1 count zero
{
	int index,count = 0;
	if(supervise_vector_temp(obj) != 0 )
	{
		return -1;
	}
	else
	{
		//do nothing
	}
	if(set == 0) //count no zero
	{
		for(index = 0;index <obj->lenght;index++)
		{
			if(obj->data[index] !=0)
			{
				count++;
			}
			else
			{
				//do nothing
			}
		}
	}
	else if(set ==1) //count zero
	{
		for(index = 0;index <obj->lenght;index++)
		{
			if(obj->data[index] ==0)
			{
				count++;
			}
			else
			{
				//do nothing
			}
		}
	}
	return  count;
}
sprVect_temp new_sprVect_tempCopyVect(vector_temp* obj)
{
	sprVect_temp data = new_sprVect_temp(0);
	int index,count =countEleVect_temp(obj,0);
	int index2 =0;
	if(count < 1)
	{
		return data;
	}
	else
	{
		data = new_sprVect_temp(count);
	}
	for(index =0 ;index<obj->lenght;index++)
	{
		if(obj->data[index]!= 0)
		{
			data.id[index2] = index;
			data.data[index2] = obj->data[index];
			index2++;
		}
		else
		{
			//do nothing
		}
	}
	return data;
}
int copy_sprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs)
{
	int index;	
	// 0 is false 1 is true
	if(rhs == lhs)
	{
		return 0;
	}	
	else if(check_sprVect_tempObj(rhs) ==0 ||
	   check_sprVect_tempObj(lhs) ==0 )
	{
		return 0;
	}
	else if(rhs->lenght > 0 && rhs->lenght != lhs->lenght)
	{
		makeEmptySprVect_temp(rhs);	
		*rhs = new_sprVect_temp(lhs->lenght);
	}
	for(index =0 ;index <lhs->lenght;index++)
	{
		rhs->data[index] = lhs->data[index];
		rhs->id[index]   = lhs->id[index];
	}

	return 1;
}
int copy_sprVect_vect_temp(sprVect_temp* rhs,vector_temp* lhs)
{
	if(check_sprVect_tempObj(rhs) ==0 ||
	   supervise_vector_temp(lhs) !=0 )
	{
		return 0;
	}
	else
	{
		//do nothing
	}
	int index,index2;
	int numArr = countEleVect_temp(lhs,0);	
	if(numArr == rhs->lenght)
	{
		for(index = 0 ;index<numArr;index++)
		{
			rhs->id[index] = index;
			rhs->data[index] = lhs->data[index];
		}
	}
	else
	{
		if(rhs->data != NULL && rhs->lenght != 0)
		{
			makeEmptySprVect_temp(rhs);
			*rhs = new_sprVect_temp(numArr);
			index2= 0;
			for(index=0;index<numArr;index++)
			{
				if(lhs->data[index] !=0)
				{
					rhs->data[index2] = lhs->data[index];
					rhs->data[index2] = index;
					index2++;
				}
				else
				{
					//do nothing
				}
			}
		}
		else
		{
			//do nothing
		}
	}
return 1;	
}
void deleteSprVect_temp(sprVect_temp* obj)
{
	makeEmptySprVect_temp(obj);
}
int convertSpr2Vect_temp(vector_temp *rhs,sprVect_temp* lhs)
{
	if(check_sprVect_tempObj(lhs) ==0 ||
	   supervise_vector_temp(rhs) !=0 )
	{
		return 0;
	}
	else
	{
		int index =0 ;
		int numArr = lhs->id[lhs->lenght-1] +1;
		delete_vector_temp(rhs);
		*rhs = new_vector_temp(numArr);
		for(index =0 ;index < rhs->lenght;index++)
		{
			if(index == lhs->id[index])
			{
				rhs->data[index] = lhs->data[lhs->id[index]];
			}
			else
			{
				rhs->data[index] = 0;
			}	
		}
		
	}
	return 1;
}
int convertVect2Spr_temp(sprVect_temp* rhs,vector_temp* lhs)
{
	if(check_sprVect_tempObj(rhs) ==0 ||
	   supervise_vector_temp(lhs) !=0 )
	{
		return 0;
	}
	else
	{
		int index = 0,index2=0;
		int numArr = countEleVect_temp(lhs,0);
		if(rhs->lenght != numArr)
		{	
			makeEmptySprVect_temp(rhs);
			*rhs = new_sprVect_temp(numArr);
		}
		else
		{
			//do nothing
		}
		for(index = 0;index<lhs->lenght;index++)
		{
			if(lhs->data[index] !=0)
			{
				rhs->id[index2] = index;
				rhs->data[index2] = lhs->data[index];
				index2++;
			}
			else
			{
				//do nothing
			}
		}
				
	}
	return 1;
}
//arithmetic operation
int compSprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs)
{
	if(check_sprVect_tempObj(rhs) ==0 ||
	   check_sprVect_tempObj(lhs) ==0 )
	{
		return 0;
	}
	else if(lhs->lenght != rhs->lenght)
	{
		return 0;
	}
	else
	{
		int index;
		for(index =0 ;index < lhs->lenght;index++)
		{
			if(rhs->id[index] != lhs->id[index])
			{
				return 0;
			}
			else if(rhs->data[index] != lhs->data[index])	
			{
				return 0;
			}
			else	
			{
				//do nothing
			}
		}
	}
	return 1;
}
int compSprVect_Vect_temp(sprVect_temp* rhs,vector_temp* lhs)
{
	if(check_sprVect_tempObj(rhs) ==0 ||
	   supervise_vector_temp(lhs) !=0 )
	{
		return 0;
	}
	else if(rhs->lenght > lhs->lenght)
	{
		return 0;
	}
	else
	{
		int index,index2=0;
		for(index = 0;index<lhs->lenght;index++)	
		{
			if(rhs->id[index2] == index)
			{
				if(rhs->data[index2] != lhs->data[index])
				{
					return 0;
				}
				else
				{
					index2++;
				}
			}
			else if(lhs->data[index] != 0)
			{
				return 0;
			}	
			else if(rhs->id[index2] < index)
			{
				return 0;
			}
			else
			{
				//do nothing
			}
		}
	}
	return 1;
}
int dotProduct_sprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs,element *res)
{
	if(check_sprVect_tempObj(rhs) ==0 ||check_sprVect_tempObj(lhs)==0 ||res == NULL)
	{
		return 0;
	}
	else
	{	
		int index1=0,index2=0;
		*res = 0;
		while(index1 < rhs->lenght && index2 <lhs->lenght)
		{
			if(rhs->id[index1] == lhs->id[index2])
			{
				*res += rhs->data[index1]*lhs->data[index2];
				index1++;
				index2++;	
			}
			else if(rhs->id[index1] >lhs->id[index2])
			{
				index2++;	
			}
			else if(rhs->id[index1] <lhs->id[index2])
			{
				index1++;
			}
			else
			{
				//do nothing
			}
		}
	
	}
	return 1;
}
int dotProduct_sprVect_Vect_temp(sprVect_temp* rhs,vector_temp* lhs,element *res)
{
	if(check_sprVect_tempObj(rhs) ==0 ||supervise_vector_temp(lhs)!=0 ||res == NULL)
	{
		return 0;
	}
	else
	{	
		int index1=0,index2=0;	
		while(index1 <rhs->lenght && index2 <lhs->lenght)
		{
			if(rhs->id[index1] ==index2)
			{
				*res += rhs->data[index1]*lhs->data[index2];
				index1++;
				index2++;
			}
			else if(rhs->id[index1] < index2)
			{
				index1++;
			}
			else if(rhs->id[index1] > index2)
			{
				index2++;
			}
			else
			{
				//do nothing
			}
			
		}
	}
	return 1;
}
int plusSprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs,sprVect_temp *res)
{

	if(check_sprVect_tempObj(rhs) ==0 ||
	   check_sprVect_tempObj(lhs) ==0 ||
	   check_sprVect_tempObj(res) ==0 )
	{
		return 0;
	}
	else
	{
		int numSame=0;
		int index1= 0;
		int index2 =0,index3=0;
		int fact1 =0;
		int sum = 0;
		sprVect_temp dummy,*dummy1 =NULL;
		numSame = countIntersectIdSprVect_temp(rhs,lhs);
		sum     = rhs->lenght +lhs->lenght - numSame;
		sum     = sum - countSameElesSprVect_temp(rhs,lhs,1);
		dummy = new_sprVect_temp(sum);
		index1 =0;
		index2 =0;
		while(index1 < rhs->lenght && index2 <lhs->lenght)
		{
			fact1 = rhs->id[index1]>lhs->id[index2];
			if(fact1 == 1)
			{	
				dummy.id[index3] = lhs->id[index2];
				dummy.data[index3] = lhs->data[index2];
				index2++;
			
			}
			else if(rhs->id[index1] == lhs->id[index2])
			{		
				dummy.id[index3] = rhs->id[index1];
				dummy.data[index3] = rhs->data[index1]+lhs->data[index2];
				index1++;
				index2++;
			
			}
			else 
			{
				dummy.id[index3] = rhs->id[index1];
				dummy.data[index3] = rhs->data[index1];
				index1++;
			}
			index3++;
		}
		if(index1 <rhs->lenght)
		{
			dummy1 = rhs;	
		}
		else if(index2 < lhs->lenght)
		{
			dummy1 = lhs;
			index1 = index2;
		}
		else
		{
			//do nothing
		}
		if(dummy1 != NULL)
		{
			while(index1 <dummy1->lenght)
			{
				dummy.id[index3] = dummy1->id[index1];
				dummy.data[index3] = dummy1->data[index1];
				index1++;
				index3++;
			}	
		}
		else
		{
			//do nothing
		}
		makeEmptySprVect_temp(res);
		*res = dummy;
	}
	return 1;
}
int plusSprVect_vect_temp(sprVect_temp* rhs,vector_temp* lhs,sprVect_temp *res)
{
	
	if(check_sprVect_tempObj(rhs) ==0 ||
	   supervise_vector_temp(lhs)!=0 ||
	   check_sprVect_tempObj(res) ==0)
	{
		return 0;
	}
	else
	{
		int isWork =0;
		sprVect_temp dummy = new_sprVect_temp(0);
		isWork = convertVect2Spr_temp(&dummy,lhs);
		if(isWork ==0)
		{
			return 0;
		}
		else
		{
			//do nothing
		}
		plusSprVect_temp(rhs,&dummy,res);
		makeEmptySprVect_temp(&dummy);
		
	}
	return 1;
}
int subSprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs,sprVect_temp *res)
{
	if(check_sprVect_tempObj(rhs) ==0 ||
	   check_sprVect_tempObj(lhs) ==0 ||
	   check_sprVect_tempObj(res) ==0 )
	{
		return 0;
	}
	else
	{
		int numSame=0;
		int index1= 0;
		int index2 =0,index3=0;
		int fact1 =0,fact2=0;
		int sum = 0;
		sprVect_temp dummy,*dummy1 =NULL;
		numSame = countIntersectIdSprVect_temp(rhs,lhs);
		sum     = rhs->lenght + lhs->lenght - numSame;
		sum     = sum - countSameElesSprVect_temp(rhs,lhs,0);
	
		dummy   = new_sprVect_temp(sum);
		index1  = 0;
		index2  = 0;
		while(index1 < rhs->lenght && index2 <lhs->lenght)
		{
			fact1 = rhs->id[index1]>lhs->id[index2];
			fact2 = ((rhs->id[index1] == lhs->id[index2]) &&
				(rhs->data[index1]== lhs->data[index2]));
			if(fact2 == 1)
			{	
				index2++;
				index1++;
				index3--;
			}
			else if(fact1 == 1)
			{	
				dummy.id[index3] = lhs->id[index2];
				dummy.data[index3] = -(lhs->data[index2]);
				index2++;
			
			}
			else if(rhs->id[index1] == lhs->id[index2])
			{	
				dummy.id[index3] = rhs->id[index1];
				dummy.data[index3] = rhs->data[index1]-lhs->data[index2];
				index1++;
				index2++;
			
			}
			else 
			{
				dummy.id[index3] = rhs->id[index1];
				dummy.data[index3] = rhs->data[index1];
				index1++;
			}
			index3++;
		}
		if(index1 <rhs->lenght)
		{
			dummy1 = rhs;	
			//index4 = &index1;
		}
		else if(index2 < lhs->lenght)
		{
			dummy1 = lhs;
			index1 = index2;
		}
		else
		{
			//do nothing
		}
		if(dummy1 != NULL)
		{
			while(index1 <dummy1->lenght)
			{
				dummy.id[index3] = dummy1->id[index1];
				if(dummy1 == lhs)
				{
				 	dummy.data[index3] = -(dummy1->data[index1]);
				}
				else
				{
				 	dummy.data[index3] = dummy1->data[index1];
				}
				index1++;
				index3++;
			}	
		}
		else
		{
			//do nothing	
		}
		makeEmptySprVect_temp(res);
		*res = dummy;
	}
	return 1;
}
int subSprVect_vect_temp(sprVect_temp* rhs,vector_temp* lhs,sprVect_temp *res)
{
	if(check_sprVect_tempObj(rhs) ==0 ||
	   supervise_vector_temp(lhs)!=0 ||
	   check_sprVect_tempObj(res) ==0)
	{
		return 0;
	}
	else
	{
		int isWork =0;
		sprVect_temp dummy = new_sprVect_temp(0);
		isWork = convertVect2Spr_temp(&dummy,lhs);
		if(isWork ==0)
		{
			return 0;
		}
		else
		{
			//do nothing
		}
		subSprVect_temp(rhs,&dummy,res);
		makeEmptySprVect_temp(&dummy);
		
	}
	return 1;
}
int countIntersectIdSprVect_temp(sprVect_temp* rhs,sprVect_temp* lhs)
{
	if(check_sprVect_tempObj(rhs) ==0 || check_sprVect_tempObj(lhs) ==0 )
	{
		return 0;
	}
	else
	{
		//do nothing
	}
	int index=0,index2=0,sum =0;
	while(rhs->lenght > index && lhs->lenght > index2)
	{
		if(rhs->id[index] == lhs->id[index2])
		{	
			sum++;
			index++;
		}
		else if(rhs->id[index] > lhs->id[index2])
		{
			index2++;
		}
		else
		{
			index++;
		}
	}
	return sum;
}
int countIntersectIdSprVect_temp_vect_temp(sprVect_temp* rhs,vector_temp* lhs)
{
	
	if(check_sprVect_tempObj(rhs) ==0 ||
	   supervise_vector_temp(lhs)!=0 )
	{
		return 0;
	}
	else
	{
		//do nothing 
	}
	int index=0,index2=0,sum =0;
	while(rhs->lenght > index && lhs->lenght > index2)
	{
		if(rhs->id[index] == index2)
		{	
			sum++;
			index++;
		}
		else if(rhs->id[index] > index2)
		{
			index2++;
		}
		else
		{
			index++;
		}
	}
}
void printSprVect_temp(sprVect_temp* rhs,int opt)
{
	
	if(check_sprVect_tempObj(rhs) ==0 )
	{
		return;
	}
	else
	{
		//do nothing
	}
	int i;
	switch(opt&0x0007) //display lenght
	{
		case 0x0000:
			printf("lenght: %d ",rhs->lenght);
			break;	
		case 0x0001:
			printf("{%d} :",rhs->lenght);
			break;
		case 0x0002:
			printf("lenght: %d\n",rhs->lenght);
			break;	
		case 0x0003:
			printf("{%d} :\n",rhs->lenght);
			break;
		default:
			break;
	}
	switch(opt&0x0038) //display Id
	{
		case 0x0008:
			printf(" ");
			for(i=0;i < rhs->lenght;i++)
			{
				printf("%d ",rhs->id[i]);
			}
			printf("\n");
			break;
		case 0x0010:
			for(i=0;i < rhs->lenght;i++)
			{
				printf(" %d\n",rhs->id[i]);
			}
			break;
		case 0x0018:
			printf(" ");
			for(i=0;i < rhs->lenght;i++)
			{
				printf("%d |",rhs->id[i]);
			}
			printf("\n");
			break;	
		default:
			break;
	}
	switch(opt&0x01c0)
	{
		case 0x0040:
			printf(" ");
			for(i=0;i < rhs->lenght;i++)
			{
				printf("%d ",rhs->data[i]);
			}
			printf("\n");
			break;
		case 0x0080:
			for(i=0;i < rhs->lenght;i++)
			{
				printf("%d\n",rhs->data[i]);
			}
			break;
		case 0x00c0:
			printf(" ");
			for(i=0;i < rhs->lenght;i++)
			{
				printf("%d |",rhs->data[i]);
			}
			printf("\n");
			break;
		case 0x0100://when a type is temp
			printf(" ");
			for(i=0;i < rhs->lenght;i++)
			{
				printf("%c ",rhs->data[i]);
			}
			printf("\n");
			break;	
		case 0x0140://when a type is temp
			for(i=0;i < rhs->lenght;i++)
			{
				printf("%c\n",rhs->data[i]);
			}
			break;	
		default:
			break;
	}
	
}
int countSameElesSprVect_temp(sprVect_temp* rhs,sprVect_temp*lhs,int set)
{
	if(check_sprVect_tempObj(rhs) ==0 || check_sprVect_tempObj(lhs) ==0 )
	{
		return 0;
	}
	else
	{
		//do nothing
	}
	int sum =0;
	int index1=0,index2=0;
	int fact1,fact2;
	if(set ==0)
	{
		while(index1 < rhs->lenght && index2 <lhs->lenght)
		{
			fact1 = (rhs->data[index1] == lhs->data[index2]);
			fact2 = (rhs->id[index1] == lhs->id[index2]);
			if(fact1 ==1 && fact2 ==1)
			{	
				sum++;
				index1++;
				index2++;
			}
			else if(fact2 == 1)
			{
				index1++;	
				index2++;	
			}
			else if(rhs->id[index1] >lhs->id[index2])
			{
				index2++;
			}
			else
			{
				index1++;
			}
		}
	}
	else if(set ==1)
	{
		while(index1 < rhs->lenght && index2 <lhs->lenght)
		{
			fact1 = (rhs->data[index1] == -(lhs->data[index2]));
			fact2 = (rhs->id[index1] == lhs->id[index2]);
			if(fact1 ==1 && fact2 ==1)
			{	
				sum++;
				index1++;
				index2++;
			}
			else if(fact2 == 1)
			{
				index1++;	
				index2++;	
			}
			else if(rhs->id[index1] >lhs->id[index2])
			{
				index2++;
			}
			else
			{
				index1++;
			}
		}
	}
	else
	{
		//do nothing
	}
	return sum;
}
int countSameElesSprVect_vector_temp(sprVect_temp* rhs,vector_temp* lhs,int set)
{
	if(check_sprVect_tempObj(rhs) ==0 ||
	   supervise_vector_temp(lhs)!=0)
	{
		return 0;
	}
	else
	{
		//do nothing
	}
	int sum =0;
	int index1=0,index2=0;
	int fact1,fact2;
	if(set==0)
	{
		while(index1 < rhs->lenght && index2 <lhs->lenght)
		{
			fact1 = (rhs->data[index1] == lhs->data[index2]);
			fact2 = (rhs->id[index1] == index2);
			if(fact1 ==1 && fact2 ==1)
			{	
				sum++;
				index1++;
				index2++;
			}
			else if(fact2 == 1)
			{
				index1++;	
				index2++;	
			}
			else if(rhs->id[index1] >index2)
			{
				index2++;
			}
			else
			{
				index1++;
			}
		}
	}
	else if(set ==1)
	{
		while(index1 < rhs->lenght && index2 <lhs->lenght)
		{
			fact1 = (rhs->data[index1] == lhs->data[index2]);
			fact2 = (rhs->id[index1] == index2);
			if(fact1 ==1 && fact2 ==1)
			{	
				sum++;
				index1++;
				index2++;
			}
			else if(fact2 == 1)
			{
				index1++;	
				index2++;	
			}
			else if(rhs->id[index1] >index2)
			{
				index2++;
			}
			else
			{
				index1++;
			}
		}
	}
	return sum;
}
