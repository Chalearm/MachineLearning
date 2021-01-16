#include "listMatTemp.h"
#include "simMatTemp.h"
#include "debug.h"
typedef unsigned int uint;


void constructListVtemp(list_v_temp* alist)
{
	if(alist == NULL)
	{
		return;
	}
	else
	{
		//do nothing
	}
	alist->numOfNode	= 0;
 	alist->firstNode 	= NULL;
	alist->lastNode 	= NULL;
	alist->currentNode 	= NULL;
}//end constructListVtemp

void addNodeVtemp(list_v_temp* alist,vector_temp* dat){
	if(alist->numOfNode == 0)
	{ 
		alist->firstNode			= (node_v_temp*)malloc(sizeof(node_v_temp));
		printOpt(__LINE__-1,"addNodeVtemp",__FILE__,(void*) alist->firstNode,0);
		alist->lastNode				= alist->firstNode;
		alist->firstNode->next 		= NULL;
		alist->firstNode->back 		= NULL;
		alist->firstNode->element 	= new_vector_temp(0);
		copy_v_temp(&(alist->firstNode->element),dat);
		alist->numOfNode++;
	}
	else if(alist->numOfNode >0)
	{
		alist->lastNode->next		= (node_v_temp*)malloc(sizeof(node_v_temp));
		printOpt(__LINE__-1,"addNodeVtemp",__FILE__,(void*) alist->lastNode->next,0);
		alist->lastNode->next->back	= alist->lastNode;
		alist->lastNode				= alist->lastNode->next;
		alist->lastNode->next		= NULL;
		alist->lastNode->element 	= new_vector_temp(0);
		copy_v_temp(&(alist->lastNode->element),dat);
	    alist->numOfNode++;
	}
} // end addNodeVtemp
void addNodeUniqueVtemp(list_v_temp* alist,vector_temp* dat)
{
	if(searchListVtemp(alist,dat) == -1)
	{
		addNodeVtemp(alist,dat);
	} // end if 1
} // end addNodeUniqueVtemp
/*
void insertNodeVtemp(list_v_temp* alist,vector_temp* dat,int pos);


void insertFrontNodeVtemp(list_v_temp* alist,vector_temp* dat,int pos);

*/
void deleteNodeVtempByOreder(list_v_temp* alist,int ord){
	node_v_temp *p	   	   = alist->firstNode;
    node_v_temp *p2	   	   = NULL;
	int	index 			   = 0;
	int numberOfNode	   = alist->numOfNode;
	for(index =0;index< numberOfNode ;index++)
	{
		if(ord == index)
		{
			break;
		}
		else
		{
			p = p->next;
		}

	}
	if(index != numberOfNode && numberOfNode >0)
	{
		if(p == alist->firstNode)
		{
			alist->firstNode       = alist->firstNode->next;
			alist->firstNode->back = NULL;
			delete_vector_temp(&p->element);
			printOpt(__LINE__+1,"deleteNodeVtempByOreder",__FILE__,(void*) p,1);
			free(p);
			alist->numOfNode--;
		} //end if(p == alist->firstNode)
		else if(p == alist->lastNode)
		{
			alist->lastNode 	  = alist->lastNode->back;
			alist->lastNode->next = NULL;
			delete_vector_temp(&p->element);
		printOpt(__LINE__+1,"deleteNodeVtempByOreder",__FILE__,(void*) p,1);
			free(p);
			alist->numOfNode--;
		} //  end else if(p == alist->lastNode)
		else
		{
			p2 					  = p->next;
			p2->back			  = p->back;
			p2					  = p->back;
			p2->next			  = p->next;
			delete_vector_temp(&p->element);
			printOpt(__LINE__+1,"deleteNodeVtempByOreder",__FILE__,(void*) p,1);
			free(p);
			alist->numOfNode--;
		} // end else
	} // end  if(index != numberOfNode && numberOfNode >0)
}// end deleteNodeVtempByOreder

void deleteNodeVtempByElement(list_v_temp* alist,vector_temp* dat)
{
	int order = searchListVtemp(alist,dat);
	deleteNodeVtempByOreder(alist,order);
} // end deleteNodeVtempByElement

int searchListVtemp(list_v_temp* alist,vector_temp* dat)
{// -1 not fount , 0,1,.., n fount at an index
	int        index = 0;
	uint       num   = alist->numOfNode;
	node_v_temp *p    = alist->firstNode;
	for(index=0;index < num;index++)
	{
		if(compareEqual_v_temp(&p->element,dat) == 1)
		{
			return index;
		}
		p = p->next;
	}
	return -1;
}// end searcbListVtemp

vector_temp getValueVtemp(list_v_temp* alist,int index)
{

	int index1		= 0;
	int numOfNode	= alist->numOfNode;
	vector_temp dummy = new_vector_temp(0);
	node_v_temp	*p  = alist->firstNode;
	if(index >= numOfNode)
    	{
		return dummy;
	}
	else
	{
		//do nothing
	}
	for(index1 =0 ;index1 < numOfNode;index1++)
	{
		if(index1 == index)
		{
			break;
		}
		p = p->next;
	}
	copy_v_temp(&dummy,&p->element);
	return dummy;
}// end getValueVtemp

void printListVtemp(list_v_temp* alist,int opt)
{
	node_v_temp *p = alist->firstNode;
	while(p !=NULL)
	{
			print_vector_temp(&p->element,opt);
			p = p->next;
	} // end 	while(p !=NULL)
}//end printListVdouble
/*
void replaceElementVtempByOrder(list_v_temp* alist,vector_temp* rep,int num);


void replaceElementVtempByElement(list_v_temp* alist,vector_temp* rep);



*/
matrix_temp 	listVtemp2Matrix(list_v_temp* alist)
{

	int index 	    = 0;
	int index2      = 0;
	matrix_temp dummy = new_matrix_temp(0,0);
	if(alist == NULL)
	{
		return dummy;
	}
	else
	{
		//do nothing
	}
	if(alist->numOfNode == 0)
	{
		return dummy;
	}
	else
	{
		// do nothing
	}
	node_v_temp	*p  = alist->firstNode;
	int numOfCol    = (alist->firstNode)->element.lenght;
	int numOfRow    = alist->numOfNode;
	//check the number of cols of all Nodes that must be equal
	for(index =0 ;index<numOfRow;index++)
	{
		if(p->element.lenght != numOfCol)
		{
			return dummy;
		}
		else
		{
			p = p->next;
		}
	} // end loop for
	dummy		   = new_matrix_temp(numOfRow,numOfCol);
	p			   = alist->firstNode;
	
	for(index =0; index<numOfRow;index++)
	{
		
		for(index2 =0;index2<numOfCol ;index2++)
		{
			dummy.data[index][index2] = p->element.data[index2];
		}
		p = p->next;
	} // end loop for
	return dummy;
} // end listVint2Matrix


void destructorListVtemp(list_v_temp* alist)
{
	makeEmptyVtemp(alist);
} // end destructorListVtemp

void makeEmptyVtemp(list_v_temp* alist){
	alist->currentNode = alist->firstNode;
	node_v_temp *p	   = NULL;
	while(alist->numOfNode--)
	{
		p 				   = alist->currentNode;
		alist->currentNode = alist->currentNode->next;
		delete_vector_temp(&p->element);
				printOpt(__LINE__-1,"makeEmptyVtemp",__FILE__,(void*) p,1);
		free(p);
	}
	alist->firstNode   = NULL;
	alist->lastNode    = NULL;
	alist->currentNode = NULL;
} // end makeEmptyVtemp

void constructListMtemp(list_m_temp* alist)
{
	if(alist == NULL)
	{
		return;
	}
	else
	{
		//do nothing
	}
	alist->numOfNode		= 0;
 	alist->firstNode 	= NULL;
	alist->lastNode 	= NULL;
	alist->currentNode 	= NULL;
}//end constructListMtemp
void addNodeMtemp(list_m_temp* alist,matrix_temp* dat)
{
	if(alist->numOfNode == 0)
	{ 
		alist->firstNode			= (node_m_temp*)malloc(sizeof(node_m_temp));
		printOpt(__LINE__-1,"addNodeMtemp",__FILE__,(void*) alist->firstNode,0);
		alist->lastNode				= alist->firstNode;
		alist->firstNode->next 		= NULL;
		alist->firstNode->back 		= NULL;
		alist->firstNode->element 	= new_matrix_temp(0,0);
		copy_m_temp(&(alist->firstNode->element),dat);
		alist->numOfNode++;
	}
	else if(alist->numOfNode >0)
	{
		alist->lastNode->next		= (node_m_temp*)malloc(sizeof(node_m_temp));
		printOpt(__LINE__-1,"addNodeMtemp",__FILE__,(void*) alist->lastNode->next,0);
		alist->lastNode->next->back	= alist->lastNode;
		alist->lastNode				= alist->lastNode->next;
		alist->lastNode->next		= NULL;
		alist->lastNode->element 	= new_matrix_temp(0,0);
		copy_m_temp(&(alist->lastNode->element),dat);
	    alist->numOfNode++;
	}
} // end addNodeMtemp

void addNodeUniqueMtemp(list_m_temp* alist,matrix_temp* dat){
	if(searchListMtemp(alist,dat) == -1)
	{
		addNodeMtemp(alist,dat);
	} // end if 1
} // end addNodeUniqueMtemp

/*
void insertNodeMtemp(list_m_temp* alist,matrix_temp* dat,int pos);


void insertFrontNodeMtemp(list_m_temp* alist,matrix_temp* dat,int pos);


*/
int searchListMtemp(list_m_temp* alist,matrix_temp* dat)
{// -1 not fount , 0,1,.., n fount at an index
	int        index = 0;
	uint       num   = alist->numOfNode;
	node_m_temp *p    = alist->firstNode;
	for(index=0;index < num;index++)
	{
		if(compareEqual_m_temp(&p->element,dat) == 1)
		{
			return index;
		}
		p = p->next;
	}
	return -1;
}// end searchListMtemp


void deleteNodeMtempByOreder(list_m_temp* alist,int ord)
{
	node_m_temp *p	   	   = alist->firstNode;
    node_m_temp *p2	   	   = NULL;
	int	index 			   = 0;
	int numberOfNode	   = alist->numOfNode;
	for(index =0;index< numberOfNode ;index++)
	{
		if(ord == index)
		{
			break;
		}
		else
		{
			p = p->next;
		}

	}
	if(index != numberOfNode && numberOfNode >0)
	{
		if(p == alist->firstNode)
		{
			alist->firstNode       = alist->firstNode->next;
			alist->firstNode->back = NULL;
			delete_matrix_temp(&p->element);
			alist->numOfNode--;
			printOpt(__LINE__+1,"deleteNodeMtempByOreder",__FILE__,(void*) p,1);
			free(p);
		} //end if(p == alist->firstNode)
		else if(p == alist->lastNode)
		{
			alist->lastNode 	  = alist->lastNode->back;
			alist->lastNode->next = NULL;
			delete_matrix_temp(&p->element);
			alist->numOfNode--;
			printOpt(__LINE__+1,"deleteNodeMtempByOreder",__FILE__,(void*) p,1);
			free(p);
		} //  end else if(p == alist->lastNode)
		else
		{
			p2 					  = p->next;
			p2->back			  = p->back;
			p2					  = p->back;
			p2->next			  = p->next;
			delete_matrix_temp(&p->element);
			alist->numOfNode--;
            printOpt(__LINE__+1,"deleteNodeMtempByOreder",__FILE__,(void*) p,1);
			free(p);
		} // end else
	} // end  if(index != numberOfNode && numberOfNode >0)
}// end deleteNodeMtempByOreder


void deleteNodeMtempByElement(list_m_temp* alist,matrix_temp* dat){
	int order = searchListMtemp(alist,dat);
	deleteNodeMtempByOreder(alist,order);
} // end deleteNodeMtempByElement

matrix_temp 		getValueMtemp(list_m_temp* alist,int index){

	int index1		= 0;
	int numOfNode	= alist->numOfNode;
	matrix_temp dummy = new_matrix_temp(0,0);
	node_m_temp	*p  = alist->firstNode;
	if(index >= numOfNode)
    {
		return dummy;
	}
	else
	{
		//do nothing
	}
	for(index1 =0 ;index1 < numOfNode;index1++)
	{
		if(index1 == index)
		{
			break;
		}
		p = p->next;
	}
	copy_m_temp(&dummy,&p->element);
	return dummy;
}// end getMalueMtemp
/*
void replaceElementMtempByOrder(list_m_temp* alist,matrix_temp* rep,int num);


void replaceElementMtempByElement(list_m_temp* alist,matrix_temp* rep);

*/
void destructorListMtemp(list_m_temp* alist)
{
	makeEmptyMtemp(alist);
} // end destructorListMtemp

void makeEmptyMtemp(list_m_temp* alist)
{
	alist->currentNode = alist->firstNode;
	node_m_temp *p	   = NULL;
	while(alist->numOfNode--)
	{
		p 				   = alist->currentNode;
		alist->currentNode = alist->currentNode->next;
		delete_matrix_temp(&p->element);
	printOpt(__LINE__+1,"makeEmptyMtemp",__FILE__,(void*) p,1);
		free(p);
	}
	alist->firstNode   = NULL;
	alist->lastNode    = NULL;
	alist->currentNode = NULL;
} // end makeEmptyMtemp

void printListMtemp(list_m_temp* alist,int opt){
	node_m_temp *p = alist->firstNode;
	while(p !=NULL)
	{
			print_matrix_temp(&p->element,opt);
			p = p->next;
	} // end 	while(p !=NULL)
}//end printListMtemp
void addNodeElement(list_v_temp* alist,element* dat,int size)
{
	if(alist == NULL || dat ==NULL || size <= 0)
	{
		return;
	}
	else
	{
		//do nothing
	}
	int i=0;
	if(alist->numOfNode == 0)
	{ 
		alist->firstNode			= (node_v_temp*)malloc(sizeof(node_v_temp));
				printOpt(__LINE__-1,"addNodeElement",__FILE__,(void*) alist->firstNode,0);
		alist->lastNode				= alist->firstNode;
		alist->firstNode->next 		= NULL;
		alist->firstNode->back 		= NULL;
		alist->firstNode->element 	= new_vector_temp(size);
		//copy_v_temp(&(alist->firstNode->element),dat);
		alist->numOfNode++;
	}
	else if(alist->numOfNode >0)
	{
		alist->lastNode->next		= (node_v_temp*)malloc(sizeof(node_v_temp));
		printOpt(__LINE__-1,"addNodeElement",__FILE__,(void*) alist->lastNode->next,0);
		alist->lastNode->next->back	= alist->lastNode;
		alist->lastNode				= alist->lastNode->next;
		alist->lastNode->next		= NULL;
		alist->lastNode->element 	= new_vector_temp(size);
		//copy_v_temp(&(alist->lastNode->element),dat);
	    alist->numOfNode++;
	}
	for(i =0 ;i < size;i++)
	{
		alist->lastNode->element.data[i] = dat[i];
	}
}
vector_temp getLastValueVtemp(list_v_temp* alist)
{
	vector_temp dummy = new_vector_temp(0);
	if(alist !=NULL)
	{
		node_v_temp	*p  = alist->lastNode;
		copy_v_temp(&dummy,&p->element);
	}
	else
	{
		//do nothing
	}
	return dummy;
}
void deleteLastNodeVtemp(list_v_temp* alist)
{
	if(alist == NULL)
	{
		return;
	}
	else if(alist->firstNode == NULL)
	{
		return;
	}
	else
	{
		//do nothing
	}
	node_v_temp *p	      = alist->lastNode;
	alist->lastNode	      = alist->lastNode->back;
	if(alist->lastNode !=NULL)
	{
		alist->lastNode->next = NULL;
	}
	else
	{
		alist->firstNode = NULL;
	}
	delete_vector_temp(&p->element);
	printOpt(__LINE__+1,"deleteLastNodeVtemp",__FILE__,(void*) p,1);
	free(p);
	alist->numOfNode--;
}
