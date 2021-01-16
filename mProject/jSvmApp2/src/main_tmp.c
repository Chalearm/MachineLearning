/********************************************************************/
/*
      FILE        :   main.c
      Name        :   Chalearm Saelim
      Date        :   15 October 2017
      Email       :   chalearm33@hotmail.com, chalearm90@gmail.com
      Purpose     :   to implement and make some experiment about the (sequential minimal optimization) SMO 


      Description :  This code is for making some experiment in Feature space, input space and abut SVM
      
                     "Fast Training of Support Vector Machines using Sequential Minimal Optimization"
                     John C. Platt, 2000 Aug
      Dependency  :   We use the included library as below 
                        #include "simMatDouble.h"
                        #include "listPvoid.h"
                        #include "setRealV.h"
      How to compile: N/A
      How to run    : N/A
      
      revision-history
      version   date          author     Description
      1.        15-10-2017    csaelim    First draft (based on tKSetting)
*/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "setRealV.h"


#include "basicVarArea.h"
#include "simStringList.h"
#include "convertStr2Digi.h"
#include "simMatChar.h"
#include "listChar.h"


#include "learningMgr.h" 

#define SETTING_CONF "setting.xml"


int main(int argc,char **argv)
{  
    struct learningMgr learnMgr;
    constructorLearningMgr(&learnMgr,SETTING_CONF);
    /*
    while(upStepKFnHdl(&kHdl) == 1)
    {
    }
    printf("End Kf loop \n");

    while(downStepKFnHdl(&kHdl) == 1)
    {
    }
    printf("End Kf loop 22 \n");
    */  
    printf(" Hello hopless \n");
    destructorLearningMgr(&learnMgr);
    return 0;
}

