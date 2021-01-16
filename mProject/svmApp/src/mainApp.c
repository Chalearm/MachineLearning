#include "mainApp.h"

/*----------------------- MACRO DEFINE ------------------*/
#define STR_PRINT                                   "print"
#define STR_UI_MODE                                 "UI_MODE"
#define STR_CURRENT_ABSOLUTE_PATH                   "CURRENT_ABSOLUTE_PATH"
#define STR_INPUT_CONFIGURATION                     "INPUT_CONFIGURATION"
#define STR_TASK_CONFIGURATION                      "TASK_CONFIGURATION"
/*----------------------- END MACRO DEFINE ------------------*/
int configurationFile(svmApp *root)
{
    /*setting Obj */
    treeXML   tXML;
    errReport errP;
    char uiShow = 0;
    int isOpenFile = 1;
    int isOkToWork = 1;
    initialErrReport(&errP);
    initial_treeXML(&tXML);
    /* Read Main.xml */
    isOpenFile = setReadFile(&tXML,MAINCONFIGFILE);
    /* Can Read ? */
    if(isOpenFile == 0)
    {
        printf("Cannot Open configuration file\n");
        destructorTreeXML(&tXML);
        return -1; /* not work -1 is error*/
    }
    else
    {
        /* start Process here !! */
        /* Keep file name Configuration */
        createTreeXML(&tXML);
        readAllPathConfig(root,&tXML);
        uiShow = isUiModeSvmApp(root);
    }
    if(validVariableSvmApp(root) == 0)
    {
        uiShow = -1;
    }
    else
    {
        /* check all sub link of input and Task path */
        isOkToWork = checkConfigPaths(root,&errP);
        reportConfigPathError(&errP,&tXML);
    }
    destructorTreeXML(&tXML);
    /* error report to console (prinft) and pathError.txt */
    if(isOkToWork == 0)
    {
        uiShow = -1;
    }
    else
    {
        /*do nothing */
    }
    destructorErrReport(&errP);
    return uiShow; /* can read ? */
}

void runAllTask(svmApp *app)
{
    int res = 0;
    if(app != NULL)
    {
        res = runAllTasksOfSvm(app);
    }
    else
    {
        /* do nothing*/
    }
    if(res ==1)
    {
        printf("Train Complete\n");
    }
    else
    {
        /* do nohting */
    }
}
void readAllPathConfig(svmApp *rootMSVM,treeXML *root)
{
    elementXML  *rootXML          = NULL;
    vector_char inputPathV        = new_vector_char(0);
    vector_char taskPathV         = new_vector_char(0);
    vector_char currentAbPathV    = new_vector_char(0);
    int print1 = 0;
    int print2 = 0;
    int print3 = 0;
    int print4 = 0;
    int uiMode  = 0;
    if(rootMSVM == NULL || root == NULL)
    {
        return;
    }
    else if(root->root == NULL)
    {
        return;
    }
    else
    {
        /* do nothing */
    }
    rootXML     = getRootElementXML(root);
    getValueOfFirstChildEle2Var(rootXML,STR_UI_MODE,"0",(void*)&uiMode,0x010); /* 0x010 = int type */
    getAttrbValueOfFirstChildEle2Var(rootXML,STR_UI_MODE,STR_PRINT,"0",(void*)&print1,0x10);
    inputPathV  = getValueFirstChildXML(rootXML,STR_INPUT_CONFIGURATION,"");
    getAttrbValueOfFirstChildEle2Var(rootXML,STR_INPUT_CONFIGURATION,STR_PRINT,"0",(void*)&print2,0x10);
    taskPathV   = getValueFirstChildXML(rootXML,STR_TASK_CONFIGURATION,"");
    getAttrbValueOfFirstChildEle2Var(rootXML,STR_TASK_CONFIGURATION,STR_PRINT,"0",(void*)&print3,0x10);
    currentAbPathV = getValueFirstChildXML(rootXML,STR_CURRENT_ABSOLUTE_PATH,"");
    getAttrbValueOfFirstChildEle2Var(rootXML,STR_CURRENT_ABSOLUTE_PATH,STR_PRINT,"0",(void*)&print4,0x10);
    addAbsolutePathSvmApp(rootMSVM,&currentAbPathV);
    addInputPathSvmApp(rootMSVM,&inputPathV);
    addTaskPathSvmApp(rootMSVM,&taskPathV);
    printf("-%d\n",uiMode);
    setUiMode(rootMSVM,uiMode);
    uiMode = (print1 ==1)||(print2==1)||(print3==1)||(print4==1);
    if(uiMode == 1)
    {
        printf("------print debug First configuration --------\n");
    }
    else
    {
        /* do nothing */
    }
    if(print1 == 1)
    {
        printf("UiMode : %d \n",rootMSVM->uiMode);
    }
    else 
    {
        /* do nothing */
    }
    if(print2 == 1)
    {
        printSimString(&(rootMSVM->inputMgrPath));
    }
    else 
    {
       /* do nothing */
    }
    if(print3 == 1)
    {
        printSimString(&(rootMSVM->taskMgrPath));
    }
    else 
    {
       /* do nothing */
    }
    if(print4 == 1)
    {
        printSimString(&(rootMSVM->abPath));
    }
    else 
    {
       /* do nothing */
    }
    if(uiMode == 1)
    {
        printf("-----------------------------------------------\n");
    }
    else
    {
        /* do nothing */
    }
    delete_vector_char(&inputPathV);
    delete_vector_char(&taskPathV);
    delete_vector_char(&currentAbPathV);
}
void displayMenuDoLearningTask()
{
    printf("-------------Do Learning Task ----------------\n");
    printf("Please Select Menu ... \n");
    printf("1. Run Learning Case \n");
    printf("2. Update Learninig Case \n");
    printf("3. Back To Main Menu\n");
}
void displayMenu(int i)
{
  if(i == 1)
  {
    printf("--------------- Multi Svms Application -------------- \n");
    printf("Please Select Menu ... \n");
    printf("1. Learning Multi SVM \n");
    printf("2. Try to classify or Predict \n");
    printf("3. End Program \n");
  }
  else if(i == -1)
  {
    printf("Program Failed to work.\n");
  }
  else
  {
     /* do nothing */
  }

}

/* for no ui mode*/
void doATask(svmApp *root,int opt)
{
   if(opt ==0)/* do task */
   {
       printf("ui Mode\n");
   }
   else
   {
      /* do nothing */
   }
}
int doProgram(svmApp *app,int i)
{
    int key = 0;
    int ret = 0;
    /*if 0(no uimode) or -1(error),it will exit program */
    if(i ==0 || i ==-1 || app == NULL) 
    {
        /* auto select case 3 : End Application */
        ret = 1;
    }
    else
    {   
        /* Select by an user */
        /* temporaly : 08July 2017*/
        if(app->bbbb ==0)
        {app->bbbb =1;
        key = 1;
        }else key =3;
        /*
        // real command is below
        scanf("%d",&key);
        */
        switch(key)
        {
            case 1: /* learnig multi svms */
                ret = 0;
                printf("Learning Multi SVMs \n");
                doTask(app);
            break;
            case 2: /* try to classify and predict */
                ret = 0;
                printf("Try to Classify and Predict\n");
            break;
            case 3: 
                /* End Application */ 
                ret = 1;
                printf("Bye \n");
            break;
            default:
                ret =1;
                printf("Bye \n");
            break;
        }
    }
    return ret;
}
void doTask(svmApp *app)
{
    int choose = 0;
    while(app != NULL && choose != -1)
    {
        /* Select by an user */
        displayMenuDoLearningTask();
        /* temporary 08July2017*/
        if(app->cccc == 0)
        {app->cccc=1;
        choose=1;
        }
        else
        {
        choose = 3;
        }
        /* real command is below*/
        /*
        scanf("%d",&choose);
        */
        switch(choose)
        {
            case 1: /* learnig multi svms */
                runAllTasksOfSvm(app);
            break;
            case 2: /* try to classify and predict */
                printf("Update Learning Case\n");
            break;
            case 3: 
                /* End Application */ 
                choose =-1;
                printf("Bye \n");
            break;
            default:
                choose=-1;
                printf("Bye \n");
            break;
        }
    }
}

void runMainApp()
{
    int ret = 0;
    int key = 0;
    /* initialize random seed: */
    srand (time(NULL));
    /* new gobal variable */
    svmApp root;
    initialSvmApp(&root);
    /*--------------------*/
    ret = configurationFile(&root);
    doATask(&root,ret);
    do
    {
         displayMenu(ret);
         key =  doProgram(&root,ret);
    }while(key == 0);
    destructSvmApp(&root);
}
