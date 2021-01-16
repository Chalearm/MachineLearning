#include "listMatChar.h"
#include "simMatChar.h"
typedef unsigned int uint;


void constructListVchar(list_v_char* alist)
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
}//end constructListVchar

void addNodeVchar(list_v_char* alist,vector_char* dat)
{
    if(alist->numOfNode == 0)
    { 
        alist->firstNode			= (node_v_char*)malloc(sizeof(node_v_char));
        alist->lastNode				= alist->firstNode;
        alist->firstNode->next 		= NULL;
        alist->firstNode->back 		= NULL;
        alist->firstNode->element 	= new_vector_char(0);
        copy_v_char(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if(alist->numOfNode >0)
    {
        alist->lastNode->next		= (node_v_char*)malloc(sizeof(node_v_char));
        alist->lastNode->next->back	= alist->lastNode;
        alist->lastNode				= alist->lastNode->next;
        alist->lastNode->next		= NULL;
        alist->lastNode->element 	= new_vector_char(0);
        copy_v_char(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
    else
    {
        /* do nothing */
    }
} // end addNodeVchar
void addNodeUniqueVchar(list_v_char* alist,vector_char* dat)
{
    if(searchListVchar(alist,dat) == -1)
    {
        addNodeVchar(alist,dat);
    } /* end if 1 */
    else
    {
        /* do nothing */
    }
} // end addNodeUniqueVchar
/*
void insertNodeVchar(list_v_char* alist,vector_char* dat,int pos);


void insertFrontNodeVchar(list_v_char* alist,vector_char* dat,int pos);

*/
void deleteNodeVcharByOreder(list_v_char* alist,int ord)
{
    node_v_char *p          = alist->firstNode;
    node_v_char *p2         = NULL;
    int	index               = 0;
    int numberOfNode        = alist->numOfNode;
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
            delete_vector_char(&p->element);
            free(p);
            alist->numOfNode--;
        } //end if(p == alist->firstNode)
        else if(p == alist->lastNode)
        {
            alist->lastNode 	  = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_vector_char(&p->element);
            free(p);
            alist->numOfNode--;
        } //  end else if(p == alist->lastNode)
        else
        {
            p2                      = p->next;
            p2->back                = p->back;
            p2                      = p->back;
            p2->next                = p->next;
            delete_vector_char(&p->element);
            free(p);
            alist->numOfNode--;
        } // end else
    } /* end  if(index != numberOfNode && numberOfNode >0) */
    else
    {
        /* do nothing */
    }
}// end deleteNodeVcharByOreder

void deleteNodeVcharByElement(list_v_char* alist,vector_char* dat)
{
    int order = searchListVchar(alist,dat);
    deleteNodeVcharByOreder(alist,order);
} // end deleteNodeVcharByElement

int searchListVchar(list_v_char* alist,vector_char* dat)
{// -1 not fount , 0,1,.., n fount at an index
    uint        index = 0;
    uint       num   = alist->numOfNode;
    node_v_char *p    = alist->firstNode;
    for(index=0;index < num;index++)
    {
        if(compareEqual_v_char(&p->element,dat) == 1)
        {
            return index;
        }
        else
        {
            /* do nothing */
        }
        p = p->next;
    }
    return -1;
}// end searcbListVchar

vector_char getValueVchar(list_v_char* alist,int index)
{

    int index1      = 0;
    int numOfNode   = alist->numOfNode;
    vector_char dummy = new_vector_char(0);
    node_v_char *p  = alist->firstNode;
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
        else
        {
            /* do nothing */
        }
        p = p->next;
    }
    copy_v_char(&dummy,&p->element);
    return dummy;
}// end getValueVchar

void printListVchar(list_v_char* alist,int opt)
{
    node_v_char *p = alist->firstNode;
    while(p !=NULL)
    {
            print_vector_char(&p->element,opt);
            p = p->next;
    } // end    while(p !=NULL)
}//end printListVdouble
/*
void replaceElementVcharByOrder(list_v_char* alist,vector_char* rep,int num);


void replaceElementVcharByElement(list_v_char* alist,vector_char* rep);



*/
matrix_char     listVchar2Matrix(list_v_char* alist)
{

    int index       = 0;
    int index2      = 0;
    matrix_char dummy = new_matrix_char(0,0);
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
    node_v_char	*p  = alist->firstNode;
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
    dummy           = new_matrix_char(numOfRow,numOfCol);
    p               = alist->firstNode;

    for(index =0; index<numOfRow;index++)
    {
        
        for(index2 =0;index2<numOfCol ;index2++)
        {
            dummy.data[index][index2] = p->element.data[index2];
        }
        p = p->next;
    } // end loop for
    return dummy;
} /* end listVint2Matrix   */


void destructorListVchar(list_v_char* alist)
{
    makeEmptyVchar(alist);
} // end destructorListVchar

void makeEmptyVchar(list_v_char* alist)
{
    alist->currentNode = alist->firstNode;
    node_v_char *p          = NULL;
    while(alist->numOfNode--)
    {
        p                   = alist->currentNode;
        alist->currentNode  = alist->currentNode->next;
        delete_vector_char(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} // end makeEmptyVchar

void constructListMchar(list_m_char* alist)
{
    if(alist == NULL)
    {
        return;
    }
    else
    {
        //do nothing
    }
    alist->numOfNode        = 0;
    alist->firstNode    = NULL;
    alist->lastNode     = NULL;
    alist->currentNode  = NULL;
}//end constructListMchar
void addNodeMchar(list_m_char* alist,matrix_char* dat)
{
    if(alist->numOfNode == 0)
    { 
        alist->firstNode            = (node_m_char*)malloc(sizeof(node_m_char));
        alist->lastNode             = alist->firstNode;
        alist->firstNode->next      = NULL;
        alist->firstNode->back      = NULL;
        alist->firstNode->element   = new_matrix_char(0,0);
        copy_m_char(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if(alist->numOfNode >0)
    {
        alist->lastNode->next       = (node_m_char*)malloc(sizeof(node_m_char));
        alist->lastNode->next->back = alist->lastNode;
        alist->lastNode             = alist->lastNode->next;
        alist->lastNode->next       = NULL;
        alist->lastNode->element    = new_matrix_char(0,0);
        copy_m_char(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
    else
    {
        /* do nothing */
    }
} // end addNodeMchar

void addNodeUniqueMchar(list_m_char* alist,matrix_char* dat){
    if(searchListMchar(alist,dat) == -1)
    {
        addNodeMchar(alist,dat);
    } /* end if 1  */
    else
    {
        /* do nothing */
    }
} // end addNodeUniqueMchar

/*
void insertNodeMchar(list_m_char* alist,matrix_char* dat,int pos);


void insertFrontNodeMchar(list_m_char* alist,matrix_char* dat,int pos);


*/
int searchListMchar(list_m_char* alist,matrix_char* dat)
{// -1 not fount , 0,1,.., n fount at an index
    uint        index = 0;
    uint       num   = alist->numOfNode;
    node_m_char *p    = alist->firstNode;
    for(index=0;index < num;index++)
    {
        if(compareEqual_m_char(&p->element,dat) == 1)
        {
            return index;
        }
        else
        {
            /*do nothing */
        }
        p = p->next;
    }
    return -1;
}// end searchListMchar


void deleteNodeMcharByOreder(list_m_char* alist,int ord)
{
    node_m_char *p          = alist->firstNode;
    node_m_char *p2         = NULL;
    int	index               = 0;
    int numberOfNode        = alist->numOfNode;
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
            delete_matrix_char(&p->element);
            alist->numOfNode--;
            free(p);
        } //end if(p == alist->firstNode)
        else if(p == alist->lastNode)
        {
            alist->lastNode 	  = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_matrix_char(&p->element);
            alist->numOfNode--;
            free(p);
        } //  end else if(p == alist->lastNode)
        else
        {
            p2 					  = p->next;
            p2->back			  = p->back;
            p2					  = p->back;
            p2->next			  = p->next;
            delete_matrix_char(&p->element);
            alist->numOfNode--;
            free(p);
        } // end else
    } // end  if(index != numberOfNode && numberOfNode >0)
}// end deleteNodeMcharByOreder


void deleteNodeMcharByElement(list_m_char* alist,matrix_char* dat)
{
    int order = searchListMchar(alist,dat);
    deleteNodeMcharByOreder(alist,order);
} // end deleteNodeMcharByElement

matrix_char         getValueMchar(list_m_char* alist,int index)
{

    int index1      = 0;
    int numOfNode   = alist->numOfNode;
    matrix_char dummy = new_matrix_char(0,0);
    node_m_char	*p  = alist->firstNode;
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
        else
        {
            /*do nothing */
        }
        p = p->next;
    }
    copy_m_char(&dummy,&p->element);
    return dummy;
}// end getMalueMchar
/*
void replaceElementMcharByOrder(list_m_char* alist,matrix_char* rep,int num);


void replaceElementMcharByElement(list_m_char* alist,matrix_char* rep);

*/
void destructorListMchar(list_m_char* alist)
{
    makeEmptyMchar(alist);
} // end destructorListMchar

void makeEmptyMchar(list_m_char* alist)
{
    alist->currentNode = alist->firstNode;
    node_m_char *p	   = NULL;
    while(alist->numOfNode--)
    {
        p                  = alist->currentNode;
        alist->currentNode = alist->currentNode->next;
        delete_matrix_char(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} // end makeEmptyMchar

void printListMchar(list_m_char* alist,int opt)
{
    node_m_char *p = alist->firstNode;
    while(p !=NULL)
    {
            print_matrix_char(&p->element,opt);
            p = p->next;
    } // end 	while(p !=NULL)
}//end printListMchar
void addNodeElement(list_v_char* alist,element* dat,int size)
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
        alist->firstNode			= (node_v_char*)malloc(sizeof(node_v_char));
        alist->lastNode				= alist->firstNode;
        alist->firstNode->next 		= NULL;
        alist->firstNode->back 		= NULL;
        alist->firstNode->element 	= new_vector_char(size);
        //copy_v_char(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if(alist->numOfNode >0)
    {
        alist->lastNode->next		= (node_v_char*)malloc(sizeof(node_v_char));
        alist->lastNode->next->back	= alist->lastNode;
        alist->lastNode				= alist->lastNode->next;
        alist->lastNode->next		= NULL;
        alist->lastNode->element 	= new_vector_char(size);
        //copy_v_char(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
    for(i =0 ;i < size;i++)
    {
        alist->lastNode->element.data[i] = dat[i];
    }
}
vector_char getLastValueVchar(list_v_char* alist)
{
    vector_char dummy = new_vector_char(0);
    if(alist !=NULL)
    {
        node_v_char	*p  = alist->lastNode;
        copy_v_char(&dummy,&p->element);
    }
    else
    {
        //do nothing
    }
    return dummy;
}
void deleteLastNodeVchar(list_v_char* alist)
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
    node_v_char *p	      = alist->lastNode;
    alist->lastNode	      = alist->lastNode->back;
    if(alist->lastNode !=NULL)
    {
        alist->lastNode->next = NULL;
    }
    else
    {
        alist->firstNode = NULL;
    }
    delete_vector_char(&p->element);
    free(p);
    alist->numOfNode--;
}
