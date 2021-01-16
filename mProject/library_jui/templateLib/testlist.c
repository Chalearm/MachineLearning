#include "listTemp.h"
#include <stdio.h>
int main(int argc,char** argv)
{
	int a =1,b=2,c=3,d=4,e=5;
	int index =30;
	int index1,index2;
	int value1,value2;
tempList list1;
constructorTempList(&list1);	
	addDataPt(&list1,&a);
	for(index =30;index <35;index++)
	{
		addData(&list1,index);
	}
	enQueueTempList(&list1,39);
	enQueueTempList(&list1,e);
	enQueueTempListPt(&list1,&b);
	pushTempListPt(&list1,&c);	
	index1 = searchTempListPt(&list1,&a);
	index2 = searchTempList(&list1,33);
	value1 = getDataTempList(&list1,3);
	value2 = getLastDataTempList(&list1);
	printTempList(&list1,1);
	printf("Search 1 and 33 : %d %d\n",index1,index2);
	printf("the number of Node:%d\n",countTempList(&list1));	
	printf("getValue index3 and last : %d %d\n",value1,value2);
	value2 = popTempList(&list1);
	printf("%d is poped, after pop:   ",value2);
	printTempList(&list1,1);
	value1 = deQueueTempList(&list1);
	printf("%d is dequeue, after that:",value1);
	printTempList(&list1,1);
	printf("the number of Node:%d\n",countTempList(&list1));	
	
	deleteIndexElementTempList(&list1,2);

	deleteElementTempList(&list1,31);	
	deleteElementTempListPt(&list1,&c);	
	printf("delete index:2,data:31,%d\n",c);
	printTempList(&list1,-1);
	printf("the number of Node:%d\n",countTempList(&list1));	
	swapElementTempList(&list1,2,4);	
	printf("Swap index2,4 :\n");
	printTempList(&list1,-1);
	printf("Swap index0,5 :\n");
	swapElementTempListPt(&list1,0,5);	
	printTempList(&list1,-1);
destructorTempList(&list1);
	printf("clear all the number of Node:%d\n",countTempList(&list1));	
return 0;
}
