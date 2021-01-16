#include <stdio.h>
#include "listMatrix.h"
#include "SimpleMatrix.h"
void constructListVint(list_v_int* alist)
{
    if (alist == NULL)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    alist->numOfNode    = 0;
    alist->firstNode    = NULL;
    alist->lastNode     = NULL;
    alist->currentNode  = NULL;
} /* end constructListVint */
void constructListVchar(list_v_char* alist)
{
    if (alist == NULL)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    alist->numOfNode    = 0;
    alist->firstNode    = NULL;
    alist->lastNode     = NULL;
    alist->currentNode  = NULL;
}/* end constructListVchar */
void constructListVfloat(list_v_float* alist)
{
    if (alist == NULL)
    {
        return;
    }
    else
    {
        //do nothing
    }
    alist->numOfNode    = 0;
    alist->firstNode    = NULL;
    alist->lastNode     = NULL;
    alist->currentNode  = NULL;
}//end constructListVfloat
void constructListVdouble(list_v_double* alist)
{
    if (alist == NULL)
    {
        return;
    }
    else
    {
        //do nothing
    }
    alist->numOfNode        = 0;
    alist->firstNode     = NULL;
    alist->lastNode     = NULL;
    alist->currentNode     = NULL;
}//end constructListVdouble

void constructListMint(list_m_int* alist)
{
    if (alist == NULL)
    {
        return;
    }
    else
    {
        //do nothing
    }
    alist->numOfNode        = 0;
    alist->firstNode     = NULL;
    alist->lastNode     = NULL;
    alist->currentNode     = NULL;
}//end constructListMint
void constructListMchar(list_m_char* alist)
{
    if (alist == NULL)
    {
        return;
    }
    else
    {
        //do nothing
    }
    alist->numOfNode        = 0;
     alist->firstNode     = NULL;
    alist->lastNode     = NULL;
    alist->currentNode     = NULL;
}//end constructListMchar
void constructListMfloat(list_m_float* alist)
{
    if (alist == NULL)
    {
        return;
    }
    else
    {
        //do nothing
    }
    alist->numOfNode        = 0;
     alist->firstNode     = NULL;
    alist->lastNode     = NULL;
    alist->currentNode     = NULL;
}//end constructListMfloat
void constructListMdouble(list_m_double* alist)
{
    if (alist == NULL)
    {
        return;
    }
    else
    {
        //do nothing
    }
    alist->numOfNode        = 0;
     alist->firstNode     = NULL;
    alist->lastNode     = NULL;
    alist->currentNode     = NULL;
}//end constructListMdouble

void addNodeVint(list_v_int* alist,vector_int* dat)
{
    if (alist->numOfNode == 0)
    { 
        alist->firstNode            = (node_v_int*)malloc(sizeof(node_v_int));
        alist->lastNode                = alist->firstNode;
        alist->firstNode->next         = NULL;
        alist->firstNode->back         = NULL;
        alist->firstNode->element     = new_vector_int(0);
        copy_v_int(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if (alist->numOfNode >0)
    {
        alist->lastNode->next        = (node_v_int*)malloc(sizeof(node_v_int));
        alist->lastNode->next->back    = alist->lastNode;
        alist->lastNode                = alist->lastNode->next;
        alist->lastNode->next        = NULL;
        alist->lastNode->element     = new_vector_int(0);
        copy_v_int(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
} // end addNodeVint

void addNodeVchar(list_v_char* alist,vector_char* dat)
{
    if (alist->numOfNode == 0)
    { 
        alist->firstNode            = (node_v_char*)malloc(sizeof(node_v_char));
        alist->lastNode                = alist->firstNode;
        alist->firstNode->next         = NULL;
        alist->firstNode->back         = NULL;
        alist->firstNode->element     = new_vector_char(0);
        copy_v_char(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if (alist->numOfNode >0)
    {
        alist->lastNode->next        = (node_v_char*)malloc(sizeof(node_v_char));
        alist->lastNode->next->back    = alist->lastNode;
        alist->lastNode                = alist->lastNode->next;
        alist->lastNode->next        = NULL;
        alist->lastNode->element     = new_vector_char(0);
        copy_v_char(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
} // end addNodeVchar
void addNodeVfloat(list_v_float* alist,vector_float* dat)
{
    if (alist->numOfNode == 0)
    { 
        alist->firstNode            = (node_v_float*)malloc(sizeof(node_v_float));
        alist->lastNode                = alist->firstNode;
        alist->firstNode->next         = NULL;
        alist->firstNode->back         = NULL;
        alist->firstNode->element     = new_vector_float(0);
        copy_v_float(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if (alist->numOfNode >0)
    {
        alist->lastNode->next        = (node_v_float*)malloc(sizeof(node_v_float));
        alist->lastNode->next->back = alist->lastNode;
        alist->lastNode                = alist->lastNode->next;
        alist->lastNode->next        = NULL;
        alist->lastNode->element     = new_vector_float(0);
        copy_v_float(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
} // end addNodeVfloat
void addNodeVdouble(list_v_double* alist,vector_double* dat)
{
    if (alist->numOfNode == 0)
    { 
        alist->firstNode            = (node_v_double*)malloc(sizeof(node_v_double));
        alist->lastNode                = alist->firstNode;
        alist->firstNode->next         = NULL;
        alist->firstNode->back         = NULL;
        alist->firstNode->element     = new_vector_double(0);
        copy_v_double(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if (alist->numOfNode >0)
    {
        alist->lastNode->next        = (node_v_double*)malloc(sizeof(node_v_double));
        alist->lastNode->next->back    = alist->lastNode;
        alist->lastNode                = alist->lastNode->next;
        alist->lastNode->next        = NULL;
        alist->lastNode->element     = new_vector_double(0);
        copy_v_double(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
} // end addNodeVdouble

void addNodeMint(list_m_int* alist,matrix_int* dat)
{
    if (alist->numOfNode == 0)
    { 
        alist->firstNode            = (node_m_int*)malloc(sizeof(node_m_int));
        alist->lastNode                = alist->firstNode;
        alist->firstNode->next         = NULL;
        alist->firstNode->back         = NULL;
        alist->firstNode->element     = new_matrix_int(0,0);
        copy_m_int(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if (alist->numOfNode >0)
    {
        alist->lastNode->next        = (node_m_int*)malloc(sizeof(node_m_int));
        alist->lastNode->next->back    = alist->lastNode;
        alist->lastNode                = alist->lastNode->next;
        alist->lastNode->next        = NULL;
        alist->lastNode->element     = new_matrix_int(0,0);
        copy_m_int(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
} // end addNodeMint
void addNodeMchar(list_m_char* alist,matrix_char* dat)
{
    if (alist->numOfNode == 0)
    { 
        alist->firstNode            = (node_m_char*)malloc(sizeof(node_m_char));
        alist->lastNode                = alist->firstNode;
        alist->firstNode->next         = NULL;
        alist->firstNode->back         = NULL;
        alist->firstNode->element     = new_matrix_char(0,0);
        copy_m_char(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if (alist->numOfNode >0)
    {
        alist->lastNode->next        = (node_m_char*)malloc(sizeof(node_m_char));
        alist->lastNode->next->back    = alist->lastNode;
        alist->lastNode                = alist->lastNode->next;
        alist->lastNode->next        = NULL;
        alist->lastNode->element     = new_matrix_char(0,0);
        copy_m_char(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
} // end addNodeMchar
void addNodeMfloat(list_m_float* alist,matrix_float* dat)
{
    if (alist->numOfNode == 0)
    { 
        alist->firstNode            = (node_m_float*)malloc(sizeof(node_m_float));
        alist->lastNode                = alist->firstNode;
        alist->firstNode->next         = NULL;
        alist->firstNode->back         = NULL;
        alist->firstNode->element     = new_matrix_float(0,0);
        copy_m_float(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if (alist->numOfNode >0)
    {
        alist->lastNode->next        = (node_m_float*)malloc(sizeof(node_m_float));
        alist->lastNode->next->back = alist->lastNode;
        alist->lastNode                = alist->lastNode->next;
        alist->lastNode->next        = NULL;
        alist->lastNode->element     = new_matrix_float(0,0);
        copy_m_float(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
} // end addNodeMfloat
void addNodeMdouble(list_m_double* alist,matrix_double* dat)
{
    if (alist->numOfNode == 0)
    { 
        alist->firstNode            = (node_m_double*)malloc(sizeof(node_m_double));
        alist->lastNode                = alist->firstNode;
        alist->firstNode->next         = NULL;
        alist->firstNode->back         = NULL;
        alist->firstNode->element     = new_matrix_double(0,0);
        copy_m_double(&(alist->firstNode->element),dat);
        alist->numOfNode++;
    }
    else if (alist->numOfNode >0)
    {
        alist->lastNode->next        = (node_m_double*)malloc(sizeof(node_m_double));
        alist->lastNode->next->back    = alist->lastNode;
        alist->lastNode                = alist->lastNode->next;
        alist->lastNode->next        = NULL;
        alist->lastNode->element     = new_matrix_double(0,0);
        copy_m_double(&(alist->lastNode->element),dat);
        alist->numOfNode++;
    }
} // end addNodeMdouble
int searchListVint(list_v_int* alist,vector_int* dat)
{
    /* -1 not fount , 0,1,.., n fount at an index */
    int        index = 0;
    uint       num   = alist->numOfNode;
    node_v_int *p    = alist->firstNode;
    for (index = 0;index < num;index++)
    {
        if (compareEqual_v_int(&p->element,dat) == 1)
        {
            return index;
        }
        p = p->next;
    }
    return -1;
}    /* end searcbListVint    */
int searchListVchar(list_v_char* alist,vector_char* dat)
{
    /* -1 not fount , 0,1,.., n fount at an index    */
    int index = 0;
    unsigned int    num   = alist->numOfNode;
    node_v_char *p   = alist->firstNode;
    for (index = 0;index < num;index++)
    {
        if (compareEqual_v_char(&p->element,dat) == 1)
        {
            return index;
        }
        else
        {
            p = p->next;
        }
    }
    return -1;
}    /* end searcbListVchar   */
int searchListVfloat(list_v_float* alist,vector_float* dat)
{
    /*   -1 not fount , 0,1,.., n fount at an index    */
    int        index = 0;
    uint       num   = alist->numOfNode;
    node_v_float *p  = alist->firstNode;
    for (index = 0;index < num;index++)
    {
        if (compareEqual_v_float(&p->element,dat) == 1)
        {
            return index;
        }
        else
        {
            p = p->next;
        }
    }
    return -1;
}   /* end searcbListVfloat    */
int searchListVdouble(list_v_double* alist,vector_double* dat)
{
    /* -1 not fount , 0,1,.., n fount at an index */
    int        index = 0;
    unsigned int       num   = alist->numOfNode;
    node_v_double *p = alist->firstNode;
    for (index = 0;index < num;index++)
    {
        if (compareEqual_v_double(&p->element,dat) == 1)
        {
            return index;
        }
        p = p->next;
    }
    return -1;
}   /* end searcbListVdouble */

int searchListMint(list_m_int* alist,matrix_int* dat)
{// -1 not fount , 0,1,.., n fount at an index
    int        index = 0;
    uint       num   = alist->numOfNode;
    node_m_int *p    = alist->firstNode;
    for (index = 0;index < num;index++)
    {
        if (compareEqual_m_int(&p->element,dat) == 1)
        {
            return index;
        }
        p = p->next;
    }
    return -1;
}// end searchListMint
int searchListMchar(list_m_char* alist,matrix_char* dat)
{// -1 not fount , 0,1,.., n fount at an index
    int        index = 0;
    uint       num   = alist->numOfNode;
    node_m_char *p    = alist->firstNode;
    for (index = 0;index < num;index++)
    {
        if (compareEqual_m_char(&p->element,dat) == 1)
        {
            return index;
        }
        p = p->next;
    }
    return -1;
}// end searchListMchar
int searchListMfloat(list_m_float* alist,matrix_float* dat)
{
    /* -1 not fount , 0,1,.., n fount at an index    */
    int        index = 0;
    uint       num   = alist->numOfNode;
    node_m_float *p    = alist->firstNode;
    for (index = 0;index < num;index++)
    {
        if (compareEqual_m_float(&p->element,dat) == 1)
        {
            return index;
        }
        p = p->next;
    }
    return -1;
}// end searchListMfloat
int searchListMdouble(list_m_double* alist,matrix_double* dat)
{// -1 not fount , 0,1,.., n fount at an index
    int        index = 0;
    uint       num   = alist->numOfNode;
    node_m_double *p    = alist->firstNode;
    for (index = 0;index < num;index++)
    {
        if (compareEqual_m_double(&p->element,dat) == 1)
        {
            return index;
        } /* end if 1  */
        else
        {
            p = p->next;
        }       
    }
    return -1;
}    
 
void addNodeUniqueVint(list_v_int* alist,vector_int* dat)
{
    if (searchListVint(alist,dat) == -1)
    {
        addNodeVint(alist,dat);
    } /*   end if 1    */
    else
    {
        /* do nohting */
    }
} /* end addNodeUniqueVint    */
void addNodeUniqueVchar(list_v_char* alist,vector_char* dat)
{
    if (searchListVchar(alist,dat) == -1)
    {
        addNodeVchar(alist,dat);
    } /*   end if 1    */
    else
    {
        /* do nohting */
    }
} /* end addNodeUniqueVchar    */
void addNodeUniqueVfloat(list_v_float* alist,vector_float* dat)
{
    if (searchListVfloat(alist,dat) == -1)
    {
        addNodeVfloat(alist,dat);
    } /*   end if 1    */
    else
    {
        /* do nohting */
    }
} /* end addNodeUniqueVfloat    */
void addNodeUniqueVdouble(list_v_double* alist,vector_double* dat)
{
    if (searchListVdouble(alist,dat) == -1)
    {
        addNodeVdouble(alist,dat);
    } /*   end if 1    */
    else
    {
        /* do nohting */
    }
} /* end addNodeUniqueVdouble    */

void addNodeUniqueMint(list_m_int* alist,matrix_int* dat)
{
    if (searchListMint(alist,dat) == -1)
    {
        addNodeMint(alist,dat);
    } /*   end if 1    */
    else
    {
        /* do nohting */
    }
} /* end addNodeUniqueMint    */
void addNodeUniqueMchar(list_m_char* alist,matrix_char* dat)
{
    if (searchListMchar(alist,dat) == -1)
    {
        addNodeMchar(alist,dat);
    } /*   end if 1    */
    else
    {
        /* do nohting */
    }
} /* end addNodeUniqueMchar    */
void addNodeUniqueMfloat(list_m_float* alist,matrix_float* dat)
{
    if (searchListMfloat(alist,dat) == -1)
    {
        addNodeMfloat(alist,dat);
    } /*   end if 1    */
    else
    {
        /* do nohting */
    }
} /* end addNodeUniqueMfloat    */
void addNodeUniqueMdouble(list_m_double* alist,matrix_double* dat)
{
    if (searchListMdouble(alist,dat) == -1)
    {
        addNodeMdouble(alist,dat);
    } /*   end if 1    */
    else
    {
        /* do nohting */
    }
} /* end addNodeUniqueMdouble    */

void makeEmptyVint(list_v_int* alist)
{
    alist->currentNode = alist->firstNode;
    node_v_int *p       = NULL;
    while(alist->numOfNode--)
    {
        p    = alist->currentNode;
        alist->currentNode = alist->currentNode->next;
        delete_vector_int(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} // end makeEmptyVint

void makeEmptyVchar(list_v_char* alist)
{
    alist->currentNode = alist->firstNode;
    node_v_char *p       = NULL;
    while(alist->numOfNode--)
    {
        p                    = alist->currentNode;
        alist->currentNode = alist->currentNode->next;
        delete_vector_char(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} // end makeEmptyVchar

void makeEmptyVfloat(list_v_float* alist)
{
    alist->currentNode = alist->firstNode;
    node_v_float *p       = NULL;
    while(alist->numOfNode--)
    {
        p                    = alist->currentNode;
        alist->currentNode = alist->currentNode->next;
        delete_vector_float(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} // end makeEmptyVfloat
void makeEmptyVdouble(list_v_double* alist)
{
    alist->currentNode = alist->firstNode;
    node_v_double *p       = NULL;
    while(alist->numOfNode--)
    {
        p                    = alist->currentNode;
        alist->currentNode = alist->currentNode->next;
        delete_vector_double(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} // end makeEmptyVdouble

void makeEmptyMint(list_m_int* alist)
{
    alist->currentNode = alist->firstNode;
    node_m_int *p       = NULL;
    while(alist->numOfNode--)
    {
        p                    = alist->currentNode;
        alist->currentNode = alist->currentNode->next;
        delete_matrix_int(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} // end makeEmptyMint

void makeEmptyMchar(list_m_char* alist)
{
    alist->currentNode = alist->firstNode;
    node_m_char *p       = NULL;
    while(alist->numOfNode--)
    {
        p                    = alist->currentNode;
        alist->currentNode = alist->currentNode->next;
        delete_matrix_char(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} // end makeEmptyMchar

void makeEmptyMfloat(list_m_float* alist)
{
    alist->currentNode = alist->firstNode;
    node_m_float *p       = NULL;
    while(alist->numOfNode--)
    {
        p                    = alist->currentNode;
        alist->currentNode = alist->currentNode->next;
        delete_matrix_float(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} // end makeEmptyMfloat
void makeEmptyMdouble(list_m_double* alist)
{
    alist->currentNode = alist->firstNode;
    node_m_double *p       = NULL;
    while(alist->numOfNode--)
    {
        p                    = alist->currentNode;
        alist->currentNode = alist->currentNode->next;
        delete_matrix_double(&p->element);
        free(p);
    }
    alist->firstNode   = NULL;
    alist->lastNode    = NULL;
    alist->currentNode = NULL;
} // end makeEmptyMdouble

void destructorListVint(list_v_int* alist)
{
    makeEmptyVint(alist);
} // end destructorListVint
void destructorListVchar(list_v_char* alist)
{
    makeEmptyVchar(alist);
} // end destructorListVchar
void destructorListVfloat(list_v_float* alist)
{
    makeEmptyVfloat(alist);
} // end destructorListVfloat
void destructorListVdouble(list_v_double* alist)
{
    makeEmptyVdouble(alist);
} // end destructorListVdouble

void destructorListMint(list_m_int* alist)
{
    makeEmptyMint(alist);
} // end destructorListMint
void destructorListMchar(list_m_char* alist)
{
    makeEmptyMchar(alist);
} // end destructorListMchar
void destructorListMfloat(list_m_float* alist)
{
    makeEmptyMfloat(alist);
} // end destructorListMfloat
void destructorListMdouble(list_m_double* alist)
{
    makeEmptyMdouble(alist);
} // end destructorListMdouble

void deleteNodeVintByOreder(list_v_int* alist,int ord)
{
    node_v_int *p              = alist->firstNode;
    node_v_int *p2              = NULL;
    int    index                = 0;
    int numberOfNode       = alist->numOfNode;
    for (index =0;index< numberOfNode ;index++)
    {
        if (ord == index)
        {
            break;
        }
        else
        {
            p = p->next;
        }

    }
    if (index != numberOfNode && numberOfNode >0)
    {
        if (p == alist->firstNode)
        {
            alist->firstNode       = alist->firstNode->next;
            alist->firstNode->back = NULL;
            delete_vector_int(&p->element);
            free(p);
        } //end if (p == alist->firstNode)
        else if (p == alist->lastNode)
        {
            alist->lastNode       = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_vector_int(&p->element);
            free(p);
        } //  end else if (p == alist->lastNode)
        else
        {
            p2                       = p->next;
            p2->back              = p->back;
            p2                      = p->back;
            p2->next              = p->next;
            delete_vector_int(&p->element);
            free(p);
        } // end else
    } // end  if (index != numberOfNode && numberOfNode >0)
}// end deleteNodeVintByOreder

void deleteNodeVcharByOreder(list_v_char* alist,int ord)
{
    node_v_char *p           = alist->firstNode;
    node_v_char *p2           = NULL;
    int    index                = 0;
    int numberOfNode       = alist->numOfNode;
    for (index =0;index< numberOfNode ;index++)
    {
        if (ord == index)
        {
            break;
        }
        else
        {
            p = p->next;
        }

    }
    if (index != numberOfNode && numberOfNode >0)
    {
        if (p == alist->firstNode)
        {
            alist->firstNode       = alist->firstNode->next;
            alist->firstNode->back = NULL;
            delete_vector_char(&p->element);
            free(p);
        } //end if (p == alist->firstNode)
        else if (p == alist->lastNode)
        {
            alist->lastNode       = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_vector_char(&p->element);
            free(p);
        } //  end else if (p == alist->lastNode)
        else
        {
            p2                       = p->next;
            p2->back              = p->back;
            p2                      = p->back;
            p2->next              = p->next;
            delete_vector_char(&p->element);
            free(p);
        } // end else
    } // end  if (index != numberOfNode && numberOfNode >0)
}// end deleteNodeVcharByOreder
void deleteNodeVfloatByOreder(list_v_float* alist,int ord)
{
    node_v_float *p           = alist->firstNode;
    node_v_float *p2       = NULL;
    int    index                = 0;
    int numberOfNode       = alist->numOfNode;
    for (index =0;index< numberOfNode ;index++)
    {
        if (ord == index)
        {
            break;
        }
        else
        {
            p = p->next;
        }

    }
    if (index != numberOfNode && numberOfNode >0)
    {
        if (p == alist->firstNode)
        {
            alist->firstNode       = alist->firstNode->next;
            alist->firstNode->back = NULL;
            delete_vector_float(&p->element);
            free(p);
        } //end if (p == alist->firstNode)
        else if (p == alist->lastNode)
        {
            alist->lastNode       = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_vector_float(&p->element);
            free(p);
        } //  end else if (p == alist->lastNode)
        else
        {
            p2                       = p->next;
            p2->back              = p->back;
            p2                      = p->back;
            p2->next              = p->next;
            delete_vector_float(&p->element);
            free(p);
        } // end else
    } // end  if (index != numberOfNode && numberOfNode >0)
}// end deleteNodeVfloatByOreder
void deleteNodeVdoubleByOreder(list_v_double* alist,int ord)
{
    node_v_double *p       = alist->firstNode;
    node_v_double *p2       = NULL;
    int    index                = 0;
    int numberOfNode       = alist->numOfNode;
    for (index =0;index< numberOfNode ;index++)
    {
        if (ord == index)
        {
            break;
        }
        else
        {
            p = p->next;
        }

    }
    if (index != numberOfNode && numberOfNode >0)
    {
        if (p == alist->firstNode)
        {
            alist->firstNode       = alist->firstNode->next;
            alist->firstNode->back = NULL;
            delete_vector_double(&p->element);
            free(p);
        } //end if (p == alist->firstNode)
        else if (p == alist->lastNode)
        {
            alist->lastNode       = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_vector_double(&p->element);
            free(p);
        } //  end else if (p == alist->lastNode)
        else
        {
            p2                       = p->next;
            p2->back              = p->back;
            p2                      = p->back;
            p2->next              = p->next;
            delete_vector_double(&p->element);
            free(p);
        } // end else
    } // end  if (index != numberOfNode && numberOfNode >0)
}// end deleteNodeVdoubleByOreder

void deleteNodeMintByOreder(list_m_int* alist,int ord)
{
    node_m_int *p              = alist->firstNode;
    node_m_int *p2              = NULL;
    int    index                = 0;
    int numberOfNode       = alist->numOfNode;
    for (index =0;index< numberOfNode ;index++)
    {
        if (ord == index)
        {
            break;
        }
        else
        {
            p = p->next;
        }

    }
    if (index != numberOfNode && numberOfNode >0)
    {
        if (p == alist->firstNode)
        {
            alist->firstNode       = alist->firstNode->next;
            alist->firstNode->back = NULL;
            delete_matrix_int(&p->element);
            free(p);
        } //end if (p == alist->firstNode)
        else if (p == alist->lastNode)
        {
            alist->lastNode       = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_matrix_int(&p->element);
            free(p);
        } //  end else if (p == alist->lastNode)
        else
        {
            p2                       = p->next;
            p2->back              = p->back;
            p2                      = p->back;
            p2->next              = p->next;
            delete_matrix_int(&p->element);
            free(p);
        } // end else
    } // end  if (index != numberOfNode && numberOfNode >0)
}// end deleteNodeMintByOreder

void deleteNodeMcharByOreder(list_m_char* alist,int ord)
{
    node_m_char *p           = alist->firstNode;
    node_m_char *p2           = NULL;
    int    index                = 0;
    int numberOfNode       = alist->numOfNode;
    for (index =0;index< numberOfNode ;index++)
    {
        if (ord == index)
        {
            break;
        }
        else
        {
            p = p->next;
        }
    }
    if (index != numberOfNode && numberOfNode >0)
    {
        if (p == alist->firstNode)
        {
            alist->firstNode       = alist->firstNode->next;
            alist->firstNode->back = NULL;
            delete_matrix_char(&p->element);
            free(p);
        } //end if (p == alist->firstNode)
        else if (p == alist->lastNode)
        {
            alist->lastNode       = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_matrix_char(&p->element);
            free(p);
        } //  end else if (p == alist->lastNode)
        else
        {
            p2                       = p->next;
            p2->back              = p->back;
            p2                      = p->back;
            p2->next              = p->next;
            delete_matrix_char(&p->element);
            free(p);
        } // end else
    } // end  if (index != numberOfNode && numberOfNode >0)
}// end deleteNodeMcharByOreder
void deleteNodeMfloatByOreder(list_m_float* alist,int ord)
{
    node_m_float *p           = alist->firstNode;
    node_m_float *p2       = NULL;
    int    index                = 0;
    int numberOfNode       = alist->numOfNode;
    for (index =0;index< numberOfNode ;index++)
    {
        if (ord == index)
        {
            break;
        }
        else
        {
            p = p->next;
        }

    }
    if (index != numberOfNode && numberOfNode >0)
    {
        if (p == alist->firstNode)
        {
            alist->firstNode       = alist->firstNode->next;
            alist->firstNode->back = NULL;
            delete_matrix_float(&p->element);
            free(p);
        } //end if (p == alist->firstNode)
        else if (p == alist->lastNode)
        {
            alist->lastNode       = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_matrix_float(&p->element);
            free(p);
        } //  end else if (p == alist->lastNode)
        else
        {
            p2                       = p->next;
            p2->back              = p->back;
            p2                      = p->back;
            p2->next              = p->next;
            delete_matrix_float(&p->element);
            free(p);
        } // end else
    } // end  if (index != numberOfNode && numberOfNode >0)
}// end deleteNodeMfloatByOreder
void deleteNodeMdoubleByOreder(list_m_double* alist,int ord)
{
    node_m_double *p       = alist->firstNode;
    node_m_double *p2       = NULL;
    int    index                = 0;
    int numberOfNode       = alist->numOfNode;
    for (index =0;index< numberOfNode ;index++)
    {
        if (ord == index)
        {
            break;
        }
        else
        {
            p = p->next;
        }

    }
    if (index != numberOfNode && numberOfNode >0)
    {
        if (p == alist->firstNode)
        {
            alist->firstNode       = alist->firstNode->next;
            alist->firstNode->back = NULL;
            delete_matrix_double(&p->element);
            free(p);
        } //end if (p == alist->firstNode)
        else if (p == alist->lastNode)
        {
            alist->lastNode       = alist->lastNode->back;
            alist->lastNode->next = NULL;
            delete_matrix_double(&p->element);
            free(p);
        } //  end else if (p == alist->lastNode)
        else
        {
            p2                       = p->next;
            p2->back              = p->back;
            p2                      = p->back;
            p2->next              = p->next;
            delete_matrix_double(&p->element);
            free(p);
        } // end else
    } // end  if (index != numberOfNode && numberOfNode >0)
}// end deleteNodeMdoubleByOreder
void deleteNodeVintByElement(list_v_int* alist,vector_int* dat)
{
    int order = searchListVint(alist,dat);
    deleteNodeVintByOreder(alist,order);
} // end deleteNodeVintByElement
void deleteNodeVcharByElement(list_v_char* alist,vector_char* dat)
{
    int order = searchListVchar(alist,dat);
    deleteNodeVcharByOreder(alist,order);
} // end deleteNodeVcharByElement
void deleteNodeVfloatByElement(list_v_float* alist,vector_float* dat)
{
    int order = searchListVfloat(alist,dat);
    deleteNodeVfloatByOreder(alist,order);
} // end deleteNodeVfloatByElement
void deleteNodeVdoubleByElement(list_v_double* alist,vector_double* dat)
{
    int order = searchListVdouble(alist,dat);
    deleteNodeVdoubleByOreder(alist,order);
} // end deleteNodeVdoubleByElement
void deleteNodeMintByElement(list_m_int* alist,matrix_int* dat)
{
    int order = searchListMint(alist,dat);
    deleteNodeMintByOreder(alist,order);
} // end deleteNodeMintByElement
void deleteNodeMcharByElement(list_m_char* alist,matrix_char* dat)
{
    int order = searchListMchar(alist,dat);
    deleteNodeMcharByOreder(alist,order);
} // end deleteNodeMcharByElement
void deleteNodeMfloatByElement(list_m_float* alist,matrix_float* dat)
{
    int order = searchListMfloat(alist,dat);
    deleteNodeMfloatByOreder(alist,order);
} // end deleteNodeMfloatByElement
void deleteNodeMdoubleByElement(list_m_double* alist,matrix_double* dat)
{
    int order = searchListMdouble(alist,dat);
    deleteNodeMdoubleByOreder(alist,order);
} // end deleteNodeMdoubleByElement
vector_int getValueVint(list_v_int* alist,int index)
{

    int index1        = 0;
    int numOfNode    = alist->numOfNode;
    vector_int temp = new_vector_int(0);
    node_v_int    *p  = alist->firstNode;
    if (index >= numOfNode)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    for (index1 =0 ;index1 < numOfNode;index1++)
    {
        if (index1 == index)
        {
            break;
        }
        p = p->next;
    }
    copy_v_int(&temp,&p->element);
    return temp;
}// end getValueVint

vector_char getValueVchar(list_v_char* alist,int index)
{

    int index1        = 0;
    int numOfNode    = alist->numOfNode;
    vector_char temp = new_vector_char(0);
    node_v_char    *p  = alist->firstNode;
    if (index >= numOfNode)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    for (index1 =0 ;index1 < numOfNode;index1++)
    {
        if (index1 == index)
        {
            break;
        }
        p = p->next;
    }
    copy_v_char(&temp,&p->element);
    return temp;
}// end getValueVchar

vector_float getValueVfloat(list_v_float* alist,int index)
{

    int index1        = 0;
    int numOfNode    = alist->numOfNode;
    vector_float temp = new_vector_float(0);
    node_v_float    *p  = alist->firstNode;
    if (index >= numOfNode)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    for (index1 =0 ;index1 < numOfNode;index1++)
    {
        if (index1 == index)
        {
            break;
        }
        p = p->next;
    }
    copy_v_float(&temp,&p->element);
    return temp;
}// end getValueVfloat

vector_double getValueVdouble(list_v_double* alist,int index)
{

    int index1        = 0;
    int numOfNode    = alist->numOfNode;
    vector_double temp = new_vector_double(0);
    node_v_double    *p  = alist->firstNode;
    if (index >= numOfNode)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    for (index1 =0 ;index1 < numOfNode;index1++)
    {
        if (index1 == index)
        {
            break;
        }
        p = p->next;
    }
    copy_v_double(&temp,&p->element);
    return temp;
}// end getValueVdouble
matrix_int getValueMint(list_m_int* alist,int index)
{

    int index1        = 0;
    int numOfNode    = alist->numOfNode;
    matrix_int temp = new_matrix_int(0,0);
    node_m_int    *p  = alist->firstNode;
    if (index >= numOfNode)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    for (index1 =0 ;index1 < numOfNode;index1++)
    {
        if (index1 == index)
        {
            break;
        }
        p = p->next;
    }
    copy_m_int(&temp,&p->element);
    return temp;
}// end getMalueMint

matrix_char getValueMchar(list_m_char* alist,int index)
{

    int index1        = 0;
    int numOfNode    = alist->numOfNode;
    matrix_char temp = new_matrix_char(0,0);
    node_m_char    *p  = alist->firstNode;
    if (index >= numOfNode)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    for (index1 =0 ;index1 < numOfNode;index1++)
    {
        if (index1 == index)
        {
            break;
        }
        p = p->next;
    }
    copy_m_char(&temp,&p->element);
    return temp;
}// end getMalueMchar

matrix_float getValueMfloat(list_m_float* alist,int index)
{

    int index1        = 0;
    int numOfNode    = alist->numOfNode;
    matrix_float temp = new_matrix_float(0,0);
    node_m_float    *p  = alist->firstNode;
    if (index >= numOfNode)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    for (index1 =0 ;index1 < numOfNode;index1++)
    {
        if (index1 == index)
        {
            break;
        }
        p = p->next;
    }
    copy_m_float(&temp,&p->element);
    return temp;
}// end getMalueMfloat

matrix_double getValueMdouble(list_m_double* alist,int index)
{

    int index1        = 0;
    int numOfNode    = alist->numOfNode;
    matrix_double temp = new_matrix_double(0,0);
    node_m_double    *p  = alist->firstNode;
    if (index >= numOfNode)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    for (index1 =0 ;index1 < numOfNode;index1++)
    {
        if (index1 == index)
        {
            break;
        }
        p = p->next;
    }
    copy_m_double(&temp,&p->element);
    return temp;
}// end getMalueMdouble
matrix_int         listVint2Matrix(list_v_int* alist)
{

    int index         = 0;
    int index2      = 0;
    matrix_int temp = new_matrix_int(0,0);
    if (alist == NULL)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    if (alist->numOfNode == 0)
    {
        return temp;
    }
    else
    {
        // do nothing
    }
    node_v_int    *p  = alist->firstNode;
    int numOfCol    = (alist->firstNode)->element.lenght;
    int numOfRow    = alist->numOfNode;
    //check the number of cols of all Nodes that must be equal
    for (index =0 ;index<numOfRow;index++)
    {
        if (p->element.lenght != numOfCol)
        {
            return temp;
        }
        else
        {
            p = p->next;
        }
    } // end loop for
    temp           = new_matrix_int(numOfRow,numOfCol);
    p               = alist->firstNode;
    
    for (index =0; index<numOfRow;index++)
    {
        
        for (index2 =0;index2<numOfCol ;index2++)
        {
            temp.data[index][index2] = p->element.data[index2];
        }
        p = p->next;
    } // end loop for
    return temp;
} // end listVint2Matrix
matrix_char         listVchar2Matrix(list_v_char* alist)
{

    int index         = 0;
    int index2      = 0;
    matrix_char temp = new_matrix_char(0,0);
    if (alist == NULL)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    if (alist->numOfNode == 0)
    {
        return temp;
    }
    else
    {
        // do nothing
    }
    node_v_char    *p  = alist->firstNode;
    int numOfCol    = (alist->firstNode)->element.lenght;
    int numOfRow    = alist->numOfNode;
    //check the number of cols of all Nodes that must be equal
    for (index =0 ;index<numOfRow;index++)
    {
        if (p->element.lenght != numOfCol)
        {
            return temp;
        }
        else
        {
            p = p->next;
        }
    } // end loop for
    temp           = new_matrix_char(numOfRow,numOfCol);
    p               = alist->firstNode;
    
    for (index =0; index<numOfRow;index++)
    {
        
        for (index2 =0;index2<numOfCol ;index2++)
        {
            temp.data[index][index2] = p->element.data[index2];
        }
        p = p->next;
    } // end loop for
    return temp;
} // end listVchar2Matrix
matrix_float         listVfloat2Matrix(list_v_float* alist)
{

    int index         = 0;
    int index2      = 0;
    matrix_float temp = new_matrix_float(0,0);
    if (alist == NULL)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    if (alist->numOfNode == 0)
    {
        return temp;
    }
    else
    {
        // do nothing
    }
    node_v_float    *p  = alist->firstNode;
    int numOfCol    = (alist->firstNode)->element.lenght;
    int numOfRow    = alist->numOfNode;
    //check the number of cols of all Nodes that must be equal
    for (index =0 ;index<numOfRow;index++)
    {
        if (p->element.lenght != numOfCol)
        {
            return temp;
        }
        else
        {
            p = p->next;
        }
    } // end loop for
    temp           = new_matrix_float(numOfRow,numOfCol);
    p               = alist->firstNode;
    
    for (index =0; index<numOfRow;index++)
    {
        
        for (index2 =0;index2<numOfCol ;index2++)
        {
            temp.data[index][index2] = p->element.data[index2];
        }
        p = p->next;
    } // end loop for
    return temp;
} // end listVfloat2Matrix
matrix_double         listVdouble2Matrix(list_v_double* alist)
{

    int index         = 0;
    int index2      = 0;
    matrix_double temp = new_matrix_double(0,0);
    if (alist == NULL)
    {
        return temp;
    }
    else
    {
        //do nothing
    }
    if (alist->numOfNode == 0)
    {
        return temp;
    }
    else
    {
        // do nothing
    }
    node_v_double    *p  = alist->firstNode;
    int numOfCol    = (alist->firstNode)->element.lenght;
    int numOfRow    = alist->numOfNode;
    //check the number of cols of all Nodes that must be equal
    for (index =0 ;index<numOfRow;index++)
    {
        if (p->element.lenght != numOfCol)
        {
            return temp;
        }
        else
        {
            p = p->next;
        }
    } // end loop for
    temp           = new_matrix_double(numOfRow,numOfCol);
    p               = alist->firstNode;
    
    for (index =0; index<numOfRow;index++)
    {
        
        for (index2 =0;index2<numOfCol ;index2++)
        {
            temp.data[index][index2] = p->element.data[index2];
        }
        p = p->next;
    } // end loop for
    return temp;
} // end listVdouble2Matrix

void printListVint(list_v_int* alist,int opt)
{
    node_v_int *p = alist->firstNode;
    while(p !=NULL)
    {
            print_vector_int(&p->element,opt);
            p = p->next;
    } // end     while(p !=NULL)
}//end printListVint
void printListVchar(list_v_char* alist,int opt)
{
    node_v_char *p = alist->firstNode;
    while(p != NULL )
    {
            
            print_vector_char(&(p->element),opt);
            p = p->next;
    } // end     while(p !=NULL)
}//end printListVchar
void printListVfloat(list_v_float* alist,int opt)
{
    node_v_float *p = alist->firstNode;
    while(p !=NULL)
    {
            print_vector_float(&p->element,opt);
            p = p->next;
    } // end     while(p !=NULL)
}//end printListVfloat
void printListVdouble(list_v_double* alist,int opt)
{
    node_v_double *p = alist->firstNode;
    while(p !=NULL)
    {
            print_vector_double(&p->element,opt);
            p = p->next;
    } // end     while(p !=NULL)
}//end printListVdouble
 
 void printListMint(list_m_int* alist,int opt)
{
    node_m_int *p = alist->firstNode;
    while(p !=NULL)
    {
            print_matrix_int(&p->element,opt);
            p = p->next;
    } // end     while(p !=NULL)
}//end printListMint
void printListMchar(list_m_char* alist,int opt)
{
    node_m_char *p = alist->firstNode;
    while(p !=NULL)
    {
            print_matrix_char(&p->element,opt);
            p = p->next;
    } // end     while(p !=NULL)
}//end printListMchar
void printListMfloat(list_m_float* alist,int opt)
{
    node_m_float *p = alist->firstNode;
    while(p !=NULL)
    {
            print_matrix_float(&p->element,opt);
            p = p->next;
    } // end     while(p !=NULL)
}//end printListMfloat
void printListMdouble(list_m_double* alist,int opt)
{
    node_m_double *p = alist->firstNode;
    while(p !=NULL)
    {
            print_matrix_double(&p->element,opt);
            p = p->next;
    } // end     while(p !=NULL)
}//end printListMdouble
 