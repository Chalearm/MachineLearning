#include <stdio.h>
#include "simMatChar.h"
#include "simMatInt.h"
#include "listMatChar.h"
#define FILENAME1 "inputdigi.txt"

void getInput(matrix_char* m1,const char* filename);
int getInputparam(char* d);
int getOuputparam(char* d);
int compareDigibin(char *a,char *b,int lenght);  // >= 0 is position diff 1 bit ,-1  diff more than 1
int compareWithDonCare(char *a,char *b,int lenght); 
matrix_char int2binMatrixchar(vector_int *a,int col);
vector_int countnumber1(matrix_char* m1,int whichrow);
void solveDigital(matrix_char* m1,list_m_char* result1);
void assignSOP(matrix_char *m1,matrix_char* a,int whichrow);
void mergeGroup(matrix_char* a);
void sortSOP(matrix_char *a,char ch,char opt);// 1 LSB, 0 MSB
void essPI(matrix_char *a,matrix_char *b,list_m_char *c); // ESS PI --> Essentail Prime Implicant
int findNumOfx(matrix_char *a,int row,char ch);
int finenumbit(int num);
//int compare2Boolean();
//int setDonCare(vector_char*a,vectpr_char *b);
int main(int argc,char** argv)
{
	int numinp = 3;
	int numout = 4;
	list_m_char result;
	constructListMchar(&result);
	matrix_char alloutput = new_matrix_char(0,0);
	vector_char b = new_vector_char(0);
	getInput(&alloutput,FILENAME1);
	solveDigital(&alloutput,&result);
	// printListMchar(&result,3);
	
	destructorListMchar(&result);
	delete_vector_char(&b);
	delete_matrix_char(&alloutput);
	
	return 0;
}

void getInput(matrix_char* m1,const char* filename)
{
	FILE* fp         = fopen(filename,"r");
	SetValue set1    = {0,0,0.0};
	int index,index2;
	char *buffer     = NULL;
	int numOfSetout  = 0;
	int numoutput    = 0;
	vector_char text = new_vector_char(100);
	initial_vector_char(&text,set1);
	buffer = text.data;
	if(fp != NULL)
	{
		// find number i/o 
		fgets(buffer,99,fp);
		numOfSetout  = getInputparam(buffer);
		fgets(buffer,99,fp);		
		numoutput    = getOuputparam(buffer);
	
		*m1	         = new_matrix_char(numOfSetout,numoutput);
		for(index = 0;index < numOfSetout;index++)
		{
			fgets(buffer,99,fp);	
			for(index2 = 0;index2 < numoutput;index2++)
			{
				m1->data[index][index2] = buffer[index2] -48;
			}
		}
		fclose(fp);
	}
	
	
    delete_vector_char(&text);
}
int getInputparam(char* d)
{
	if(d != NULL)
	{
		if(d[1] <48)
		return (d[0]-48);
		else
		return (d[1]-48) + 10*(d[0]-48);
	}
return 0;
}
int getOuputparam(char* d)
{
	if(d != NULL)
	{
		if(d[1] <48)
		return (d[0]-48);
		else
		return (d[1]-48) + 10*(d[0]-48);
	}
return 0;
}
matrix_char int2binMatrixchar(vector_int *a,int col)
{
	matrix_char text = new_matrix_char(a->lenght,col);
    SetValue set1    = {0,0,0};
	initial_matrix_char(&text,set1);	
	int index1=0,index2 =0;
	int numofNum	= a->lenght;
	for(index1 = 0;index1 < numofNum;index1++)
	{
		for(index2=0;a->data[index1] !=0;a->data[index1]=a->data[index1]>>1,index2++)
		{
			text.data[index1][col-1-index2] = a->data[index1]%2;
		}
	}
	return text;
}
void solveDigital(matrix_char* m1,list_m_char* result1)
{
	if(m1 == NULL || result1 == NULL)
	{
		return;
	}
	else
	{
		// do nothing
	}
	if(m1->row == 0 || m1->col == 0)
	{
		return;
	}
	else
	{
		// do nothing
	}
	int numloop 	 = m1->row;
	int index1  	 = 0;
	int index2       = 0;
	SetValue set1    = {0,0,0.0};
	int complete1	 = 0;
	matrix_char  dat = new_matrix_char(0,0);
	matrix_char	oldDat	= new_matrix_char(0,0);
        matrix_char	sop	= new_matrix_char(0,0);
	for(index1 =0 ;index1 < numloop;index1++) //loop n output
	{

		assignSOP(m1,&dat,index1);
		print_matrix_char(&dat,3);
		complete1 = compareEqual_m_char(&oldDat,&dat);
		copy_m_char(&sop,&dat);

		for(;complete1!=1;)
		{
printf("core 0 \n");
			copy_m_char(&oldDat,&dat);
printf("core 1\n");
			mergeGroup(&dat);
printf("core 2\n");
			complete1 = compareEqual_m_char(&oldDat,&dat);;
printf("core 3 \n");
			copy_m_char(&oldDat,&dat);
printf("core 4 \n");
			
		}

		sortSOP(&dat,5,0);
		essPI(&dat,&sop,result1);
		print_matrix_char(&dat,3);
		addNodeMchar(result1,&dat);

	 	delete_matrix_char(&dat);
	}
	delete_matrix_char(&oldDat);
	delete_matrix_char(&dat);
	delete_matrix_char(&sop);
}
int compareDigibin(char *a,char *b,int lenght)
{
	int index = 0;
	int diff  = -1;
	if(a == NULL || b == NULL) return -1;
	for(index = 0;index<lenght;index++)
	{
		if(a[index] != b[index])
		{
			if(diff != -1)
			{
				return -1;
			}
			diff = index;
			
			
		}
	}
	return diff;
}
vector_int countnumber1(matrix_char* m1,int whichrow)
{
	int index2,index,numelem    = m1->col;
	int sum 	         = 0;
	vector_int  setTrue  = new_vector_int(0);
	if(m1==NULL) return setTrue;
	for(index =0 ;index<numelem;index++)
	{
		sum += (int)(m1->data[whichrow][index] ==1);
	}
	setTrue        = new_vector_int(sum);	
	index2 		   = 0;
	for(index =0 ;index<numelem;index++)
	{
		if(m1->data[whichrow][index] ==1)
		{
			setTrue.data[index2++] = index;
		}
	}
	return setTrue;
}
void assignSOP(matrix_char *m1,matrix_char* a,int whichrow)
{   
	if(m1 == NULL || a==NULL) return;
	int index			 = 0; 
	int num1   		     = 0;
	int index2 			 = 0;
	vector_int setOfTrue = new_vector_int(0) ;
	setOfTrue  = countnumber1(m1,whichrow);	
    *a = int2binMatrixchar(&setOfTrue,finenumbit(m1->col)+1);
	delete_vector_int(&setOfTrue);
}
int finenumbit(int num)
{
	if(num ==0)
	{	
		return -1;
	}
	return finenumbit(num/2)+1;
}
void mergeGroup(matrix_char* a)
{
	int index = 0;
	int index2= 0;
	int pos	  = -1;
	int num   = a->row;
	int checkMatch = 0;
	list_v_char listTemp;
	constructListVchar(&listTemp);
	vector_char vchar1 = new_vector_char(0);
	sortSOP(a,1,1);
//printf("num : %d -------\n",num);
	for(index = 0;index < num;index++)
	{
		checkMatch = 0;
		 
		for(index2 =index+1;index2 <num;index2++)
		{
 
			pos = compareDigibin(&a->data[index][1],&a->data[index2][1],a->col-1);
			if(pos != -1)
			{
/*
vchar1 = rowMatrix2Vectorchar(a,index);
printf("===========================\n");
print_vector_char(&vchar1,10);
delete_vector_char(&vchar1);
printf("   ");
*/
			    //a->data[index2][0] = 5; //set read, and match
				vchar1 = rowMatrix2Vectorchar(a,index2);
//print_vector_char(&vchar1,10);
				pos++;
				vchar1.data[pos] = 5;
				 vchar1.data[0]   = 0;
 /*
printf(" -----> ");
print_vector_char(&vchar1,10);
printf("\n");	
*/
			 	addNodeUniqueVchar(&listTemp,&vchar1);
				delete_vector_char(&vchar1);
				checkMatch = 1;
			}
			 
		}
 
		if(checkMatch == 0 )
		{
	        vchar1 = rowMatrix2Vectorchar(a,index);
		    vchar1.data[0]   = 0;
			addNodeUniqueVchar(&listTemp,&vchar1);
			delete_vector_char(&vchar1);
		}
	}
	if(listTemp.numOfNode !=0)
	{
	 delete_matrix_char(a);
	 *a = listVchar2Matrix(&listTemp);
	}
	else
	{
		//do nothing
	}
	destructorListVchar(&listTemp);
}

void sortSOP(matrix_char *a,char ch,char opt) // opt =1 LSB, opt=0 MSB
{
	if(a ==NULL)
	{
		return;
	}
	else
	{
		//do nothing
	}
	int index =0;
	int index2 =0;
	int num  = a->row;
	if(opt == 1)
	{
		for(index =0 ;index <num;index++)
		{
			for(index2 =index+1;index2 <num;index2++)
			{
				if(findNumOfx(a,index,ch) > findNumOfx(a,index2,ch))
				{
					swapRowMchar(a,index,index2);
				}// end if(findNumOfx(a,index,ch) > findNumOfx(a,index2,ch))
				else
				{
					//do nothing
				}// end else
			} // end for(index2 =index+1;index2 <num;index2++)
		}// end for(index =0 ;index <num;index++)
	}//end if(opt == 1)
	else if(opt == 0)
	{
		for(index =0 ;index <num;index++)
		{
			for(index2 =index+1;index2 <num;index2++)
			{
				if(findNumOfx(a,index,ch) < findNumOfx(a,index2,ch))
				{
					swapRowMchar(a,index,index2);
				} // end if(findNumOfx(a,index,ch) < findNumOfx(a,index2,ch))
			}//end for(index2 =index+1;index2 <num;index2++)
		}// end for(index =0 ;index <num;index++)
	}//end 	else if(opt == 0)
}
int findNumOfx(matrix_char *a,int row,char ch)
{
	if(a == NULL)
	{
		return -1;
	}
	else
	{
		//do nothing
	}
	int index =0;
	int sum =0;
	for(index= 0;index <a->col;index++)
	{
		if(a->data[row][index] == ch)
		{
			sum++;
		}
	}
	return sum ;
}
int compareWithDonCare(char *a,char *b,int lenght)
{
	char c[lenght];
	if(a == NULL || b ==NULL || lenght <= 0 )
	{
		return ;
	}
	else
	{
		// do nothing
	}
	int index = 0;
	for(index =0 ;index <lenght;index++)
	{
		c[index] = a[index];
		if(a[index] == 5)
		{
			c[index] = b[index];
		}
	}
	for(index =0 ;index <lenght;index++)
	{
		 
		if(c[index] != b[index])
		{
			return 0;
		}
	}
	return 1;
}
void essPI(matrix_char *a,matrix_char *b,list_m_char *c)// ESS PI --> Essentail Prime Implicant
{ //a set of PI //b set of SOP
	if(a == NULL || b==NULL || c==NULL)
	{
		return;
	}//end if(a == NULL || b==NULL || c==NULL)
	else
	{
		//do nothing
	}//end else 	if(a == NULL || b==NULL || c==NULL)
	SetValue set = {0,0,0};
	matrix_char essPITable = new_matrix_char(a->row,b->row);
	vector_char vChar = new_vector_char(0);
    vector_char vPI = new_vector_char(0);
    int index = 0,index2 =0,numRow = essPITable.row,numCol = essPITable.col ;
	initial_matrix_char(&essPITable,set);
	
	for(index =0 ;index <numRow;index++)
	{
		vPI   = rowMatrix2Vectorchar(a,index);
		
		for(index2 =0 ;index2<numCol;index2++)
		{
		 	vChar = rowMatrix2Vectorchar(b,index2);
			if(compareWithDonCare(vPI.data,vChar.data,vPI.lenght) == 1)
			{
				essPITable.data[index][index2] = 5;
			}//end if(compareWithDonCare(vPI.data,vChar.data,vPI.lenght) == 1)
			else
			{
			}// end if(compareWithDonCare(vPI.data,vChar.data,vPI.lenght) == 1)
			
			 delete_vector_char(&vChar);
		} // end loop col SOP
		
	delete_vector_char(&vPI);
	}//end  loop PI
	print_matrix_char(&essPITable,3);
	delete_matrix_char(&essPITable);
} //end essPI(matrix_char *a,matrix_char *b,list_v_char *c); 
