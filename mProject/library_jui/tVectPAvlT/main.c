/********************************************************************/
/*
      FILE        :  main.c
      Name     :   Chalearm Saelim
      Date       :   14 Nov 2015
      Purpose :   To test AVL Tree with Vector pointer Key : 
                         Adding, Removing, Reblance and destruct tree

      Description :      In this file is make up of following list below :
                                1. data structure to handle array of vector integer
                                2. methods for pluging to AVL tree
                                3  statements about adding Vector integer  pointer key to the tree
                                4. statements about removing Vector integer  pointer key from the node
*/
/*******************************************************************/
#include <stdio.h>
#include <time.h>
#include "iVtHandle.h" 

int main(int argc,char** argv)
{
    srand(time(NULL));
    iVtH ivtH;
    constructIVTH(&ivtH,12,2);
    setMaxMinValueIVTH(&ivtH,100,0); /* max and min */
    setAllVectValueIVTH(&ivtH);
    AddAllValue2TIVTH(&ivtH);
   //viewIVTH(&ivtH);
    destructIVTH(&ivtH);
    
    
    constructIVTH(&ivtH,16,3);
    setMaxMinValueIVTH(&ivtH,100,0); /* max and min */
    setAllVectValueIVTH(&ivtH);
    AddAllValue2TIVTH(&ivtH);
    //viewIVTH(&ivtH);
    menuDisplayOfVH();
    mainDisplayLoopVHSetting(&ivtH);
    destructIVTH(&ivtH); 
    return 0;
}

