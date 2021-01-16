#include "tempElement.h"
#include <stdio.h>
void assignElement(element *a,element *b)
{
	if(a == NULL || b == NULL || a==b)
	{
		return;
	}
	else
	{	
		*a = *b;
	}
		
}
int compareEqual(element *a,element *b)
{
	if(a == NULL || b == NULL)
	{
		return 0;
	}
	else if(a == b || *a == *b)
	{
		return 1;
	}
	else if(*a > *b)
	{
		return 2;
	}
	else if(*a < *b)
	{
		return 4;
	}
	else if(*a >= *b)
	{
		return 3;
	}
	else if(*a <= *b)
	{
		return 5;
	}
	else
	{
		return 6;
	}
}
