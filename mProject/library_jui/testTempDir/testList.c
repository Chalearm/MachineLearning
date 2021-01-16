#include <stdio.h>
#include "simMatChar.h"
#include "listMatChar.h"
 
char main(char argc,char** argv)
{
	 srand((unsigned char)time(NULL));
	 list_v_char listChar;
	int aa,bb,cc;
	SetValue set1 ={3,30,0.0};
	SetValue set2 ={2,11.0,7};
	vector_char v1= new_vector_char(5);
	vector_char v2= new_vector_char(5);
	vector_char v3= new_vector_char(5);
	matrix_char m1= new_matrix_char(0,0);
	vector_char v4= new_vector_char(0);
	vector_char v5= new_vector_char(0);
	vector_char v6= new_vector_char(0);
	initial_vector_char(&v1,set1);
	initial_vector_char(&v2,set2);
	
	dotmultiply_v_char(&v1,&v2,&v3);
 	constructListVchar(&listChar);
	addNodeVchar(&listChar,&v1);
	addNodeVchar(&listChar,&v3);
			minus_v_char(&v2,&v2,&v3);	
	addNodeVchar(&listChar,&v3);
	addNodeVchar(&listChar,&v2);
	plus_v_char(&v2,&v2,&v3);	
	addNodeVchar(&listChar,&v3);

	aa = searchListVchar(&listChar,&v2);
	printf("position of v2 : %d\n",aa);
	bb = searchListVchar(&listChar,&v3);
	printf("position of v3 : %d\n",bb);	
	cc = searchListVchar(&listChar,&v1);
	printf("position of v1 : %d\n",cc);	
printf("++++++++++++++++++++++++++++++++++\n");
	 printListVchar(&listChar,5);
printf("++++++++++++++++++++++++++++++++++\n");
	 v4 = getValueVchar(&listChar,3);
	 v5 = getValueVchar(&listChar,2);
	 v6 = getValueVchar(&listChar,1);
	 printf("get index 3 to v4 : ");
	 print_vector_char(&v4,5);
	 printf("get index 2 to v5 : ");
	 print_vector_char(&v5,5);
	 printf("get index 1 to v6 : ");
	 print_vector_char(&v6,5);
	 m1 = listVchar2Matrix(&listChar);
	 
	 	 print_matrix_char(&m1,3);
	destructorListVchar(&listChar);
printf("--------------------------\n");
	 printListVchar(&listChar,5);
	delete_vector_char(&v1);
	delete_vector_char(&v2);
	delete_vector_char(&v3);
	delete_vector_char(&v4);
	delete_vector_char(&v5);
	delete_vector_char(&v6);
	delete_matrix_char(&m1);
	return 0;
}
