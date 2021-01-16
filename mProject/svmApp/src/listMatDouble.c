#include "listMatDouble.h"
#include "simMatDouble.h"
typedef unsigned int uint;


void constructListVdouble(list_v_double* alist)
{
    if(alist == NULL)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    alist->numOfNode	= 0;
    alist->firstNode 	= NULL;
    alist->lastNode 	= NULL;
    alist->currentNode 	= NULL;
}/*end constructListVdouble*/

void addNodeVdouble(list_v_double* alist,vector_double* dat)
{
    if(alist->numOfNode == 0)
    { 
        alist->firstNode            = (node_v_double*)malloc(sizeof(node_v_double));
        alist->lastNode             = alist->firstNode;
        alist->firstNode->next      = NULL;
        alist->firstNode->back      = NULL;
        alist->firstNode->element   = new_vector_double(0);
        copy_v_double(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if(alist->numOfNode >0)
    {
        alist->lastNode->next		= (node_v_double*)malloc(sizeof(node_v_double));
        alist->lastNode->next->back	= alist->lastNode;
        alist->lastNode				= alist->lastNode->next;
        alist->lastNode->next		= NULL;
        alist->lastNode->element 	= new_vector_double(0);
        copy_v_double(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
    else
    {
        /* do nothing */
    }
} /* end addNodeVdouble*/
void addNodeUniqueVdouble(list_v_double* alist,vector_double* dat)
{
    if(searchListVdouble(alist,dat) == -1)
    {
        addNodeVdouble(alist,dat);
    } /* end if 1 */
    else
    {
        /* do nothing */
    }
} /* end addNodeUniqueVdouble*/
/*
void insertNodeVdouble(list_v_double* alist,vector_double* dat,int pos);


void insertFrontNodeVdouble(list_v_double* alist,vector_double* dat,int pos);

*/
void deleteNodeVdoubleByOreder(list_v_double* alist,int ord)
{
    node_v_double *p          = alist->firstNode;
    node_v_double *p2         = NULL;
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
            delete_vector_double(&p->element);
            free(p);
            alist->numOfNode--;
        } /*end if(p == alist->firstNode)*/
        else if(p == alist->lastNode)
        {
            alist->lastNode 	  = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_vector_double(&p->element);
            free(p);
            alist->numOfNode--;
        } /*  end else if(p == alist->lastNode)*/
        else
        {
            p2                      = p->next;
            p2->back                = p->back;
            p2                      = p->back;
            p2->next                = p->next;
            delete_vector_double(&p->element);
            free(p);
            alist->numOfNode--;
        } /* end else*/
    } /* end  if(index != numberOfNode && numberOfNode >0) */
    else
    {
        /* do nothing */
    }
}/*end deleteNodeVdoubleByOreder*/

void deleteNodeVdoubleByElement(list_v_double* alist,vector_double* dat)
{
    int order = searchListVdouble(alist,dat);
    deleteNodeVdoubleByOreder(alist,order);
} /* end deleteNodeVdoubleByElement*/

int searchListVdouble(list_v_double* alist,vector_double* dat)
{/* -1 not fount , 0,1,.., n fount at an index*/
    int        index = 0;
    uint       num   = alist->numOfNode;
    node_v_double *p    = alist->firstNode;
    for(index=0;index < num;index++)
    {
        if(compareEqual_v_double(&p->element,dat) == 1)
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
}/* end searcbListVdouble*/

vector_double getValueVdouble(list_v_double* alist,int index)
{

    int index1      = 0;
    int numOfNode   = alist->numOfNode;
    vector_double dummy = new_vector_double(0);
    node_v_double *p  = alist->firstNode;
    if(index >= numOfNode)
    {
        return dummy;
    }
    else
    {
        /* do nothing */
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
    copy_v_double(&dummy,&p->element);
    return dummy;
}/* end getValueVdouble*/

void printListVdouble(list_v_double* alist,int opt)
{
    node_v_double *p = alist->firstNode;
    while(p !=NULL)
    {
            print_vector_double(&p->element,opt);
            p = p->next;
    } /* end    while(p !=NULL) */
}/*end printListVdouble*/
/*
void replaceElementVdoubleByOrder(list_v_double* alist,vector_double* rep,int num);


void replaceElementVdoubleByElement(list_v_double* alist,vector_double* rep);



*/
matrix_double     listVdouble2Matrix(list_v_double* alist)
{

    int index       = 0;
    int index2      = 0;
    matrix_double dummy = new_matrix_double(0,0);
    if(alist == NULL)
    {
        return dummy;
    }
    else
    {
        /* do nothing */
    }
    if(alist->numOfNode == 0)
    {
        return dummy;
    }
    else
    {
        /* do nothing */
    }
    node_v_double   *p  = alist->firstNode;
    int numOfCol    = (alist->firstNode)->element.lenght;
    int numOfRow    = alist->numOfNode;
    /*check the number of cols of all Nodes that must be equal*/
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
    } /*  end loop for */
    dummy           = new_matrix_double(numOfRow,numOfCol);
    p               = alist->firstNode;

    for(index =0; index<numOfRow;index++)
    {
        
        for(index2 =0;index2<numOfCol ;index2++)
        {
            dummy.data[index][index2] = p->element.data[index2];
        }
        p = p->next;
    } /* end loop for */
    return dummy;
} /* end listVint2Matrix   */


void destructorListVdouble(list_v_double* alist)
{
    makeEmptyVdouble(alist);
} /* end destructorListVdouble */

void makeEmptyVdouble(list_v_double* alist)
{
    alist->currentNode = alist->firstNode;
    node_v_double *p          = NULL;
    while(alist->numOfNode--)
    {
        p                   = alist->currentNode;
        alist->currentNode  = alist->currentNode->next;
        delete_vector_double(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} /* end makeEmptyVdouble */

void constructListMdouble(list_m_double* alist)
{
    if(alist == NULL)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    alist->numOfNode        = 0;
    alist->firstNode    = NULL;
    alist->lastNode     = NULL;
    alist->currentNode  = NULL;
}/*end constructListMdouble */
void addNodeMdouble(list_m_double* alist,matrix_double* dat)
{
    if(alist->numOfNode == 0)
    { 
        alist->firstNode            = (node_m_double*)malloc(sizeof(node_m_double));
        alist->lastNode             = alist->firstNode;
        alist->firstNode->next      = NULL;
        alist->firstNode->back      = NULL;
        alist->firstNode->element   = new_matrix_double(0,0);
        copy_m_double(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if(alist->numOfNode >0)
    {
        alist->lastNode->next       = (node_m_double*)malloc(sizeof(node_m_double));
        alist->lastNode->next->back = alist->lastNode;
        alist->lastNode             = alist->lastNode->next;
        alist->lastNode->next       = NULL;
        alist->lastNode->element    = new_matrix_double(0,0);
        copy_m_double(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
    else
    {
        /* do nothing */
    }
} /* end addNodeMdouble */

void addNodeUniqueMdouble(list_m_double* alist,matrix_double* dat){
    if(searchListMdouble(alist,dat) == -1)
    {
        addNodeMdouble(alist,dat);
    } /* end if 1  */
    else
    {
        /* do nothing */
    }
} /* end addNodeUniqueMdouble */

/*
void insertNodeMdouble(list_m_double* alist,matrix_double* dat,int pos);


void insertFrontNodeMdouble(list_m_double* alist,matrix_double* dat,int pos);


*/
int searchListMdouble(list_m_double* alist,matrix_double* dat)
{/* -1 not fount , 0,1,.., n fount at an index */
    int        index = 0;
    uint       num   = alist->numOfNode;
    node_m_double *p    = alist->firstNode;
    for(index=0;index < num;index++)
    {
        if(compareEqual_m_double(&p->element,dat) == 1)
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
}/* end searchListMdouble */


void deleteNodeMdoubleByOreder(list_m_double* alist,int ord)
{
    node_m_double *p          = alist->firstNode;
    node_m_double *p2         = NULL;
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
            delete_matrix_double(&p->element);
            alist->numOfNode--;
            free(p);
        } /* end if(p == alist->firstNode) */
        else if(p == alist->lastNode)
        {
            alist->lastNode 	  = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_matrix_double(&p->element);
            alist->numOfNode--;
            free(p);
        } /*  end else if(p == alist->lastNode) */
        else
        {
            p2 					  = p->next;
            p2->back			  = p->back;
            p2					  = p->back;
            p2->next			  = p->next;
            delete_matrix_double(&p->element);
            alist->numOfNode--;
            free(p);
        } /* end else*/
    } /* end  if(index != numberOfNode && numberOfNode >0) */
}/* end deleteNodeMdoubleByOreder*/


void deleteNodeMdoubleByElement(list_m_double* alist,matrix_double* dat)
{
    int order = searchListMdouble(alist,dat);
    deleteNodeMdoubleByOreder(alist,order);
} /* end deleteNodeMdoubleByElement */

matrix_double         getValueMdouble(list_m_double* alist,int index)
{

    int index1      = 0;
    int numOfNode   = alist->numOfNode;
    matrix_double dummy = new_matrix_double(0,0);
    node_m_double	*p  = alist->firstNode;
    if(index >= numOfNode)
    {
        return dummy;
    }
    else
    {
        /* do nothing */
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
    copy_m_double(&dummy,&p->element);
    return dummy;
}/* end getMalueMdouble */
/*
void replaceElementMdoubleByOrder(list_m_double* alist,matrix_double* rep,int num);


void replaceElementMdoubleByElement(list_m_double* alist,matrix_double* rep);

*/
void destructorListMdouble(list_m_double* alist)
{
    makeEmptyMdouble(alist);
} /*  end destructorListMdouble */

void makeEmptyMdouble(list_m_double* alist)
{
    alist->currentNode = alist->firstNode;
    node_m_double *p	   = NULL;
    while(alist->numOfNode--)
    {
        p                  = alist->currentNode;
        alist->currentNode = alist->currentNode->next;
        delete_matrix_double(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} /* end makeEmptyMdouble */

void printListMdouble(list_m_double* alist,int opt)
{
    node_m_double *p = alist->firstNode;
    while(p !=NULL)
    {
            print_matrix_double(&p->element,opt);
            p = p->next;
    } /* end 	while(p !=NULL) */
}/*end printListMdouble*/
void addNodeDouble(list_v_double* alist,double* dat,int size)
{
    if(alist == NULL || dat ==NULL || size <= 0)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    int i=0;
    if(alist->numOfNode == 0)
    { 
        alist->firstNode			= (node_v_double*)malloc(sizeof(node_v_double));
        alist->lastNode				= alist->firstNode;
        alist->firstNode->next 		= NULL;
        alist->firstNode->back 		= NULL;
        alist->firstNode->element 	= new_vector_double(size);
        /* copy_v_double(&(alist->firstNode->element),dat); */
        alist->numOfNode++;
    }
    else if(alist->numOfNode >0)
    {
        alist->lastNode->next		= (node_v_double*)malloc(sizeof(node_v_double));
        alist->lastNode->next->back	= alist->lastNode;
        alist->lastNode				= alist->lastNode->next;
        alist->lastNode->next		= NULL;
        alist->lastNode->element 	= new_vector_double(size);
        /* copy_v_double(&(alist->lastNode->element),dat); */
        alist->numOfNode++;
    }
    for(i =0 ;i < size;i++)
    {
        alist->lastNode->element.data[i] = dat[i];
    }
}
vector_double getLastValueVdouble(list_v_double* alist)
{
    vector_double dummy = new_vector_double(0);
    if(alist !=NULL)
    {
        node_v_double	*p  = alist->lastNode;
        copy_v_double(&dummy,&p->element);
    }
    else
    {
        /* do nothing */
    }
    return dummy;
}
void deleteLastNodeVdouble(list_v_double* alist)
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
        /* do nothing */
    }
    node_v_double *p	      = alist->lastNode;
    alist->lastNode	      = alist->lastNode->back;
    if(alist->lastNode !=NULL)
    {
        alist->lastNode->next = NULL;
    }
    else
    {
        alist->firstNode = NULL;
    }
    delete_vector_double(&p->element);
    free(p);
    alist->numOfNode--;
}
