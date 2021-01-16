#ifndef MAINAPP_H_
#define MAINAPP_H_
#include <time.h> /* srand, rand */
#define MAINCONFIGFILE "configFile/main.xml"
#include "simReadXML.h"
#include "simMatChar.h"
#include "svmApp.h"
#include "inputDataMgr.h"
#include "taskMgr.h"
#include "convertStr2Digi.h"
#include "svmErrHandler.h"
/* main function */
int configurationFile(svmApp *root);
    int  readTagErrPathFile(treeXML *root);
    vector_char  readPathFromTagErrPathFile(treeXML *root);
    void readAllPathConfig(svmApp *rootMSVM,treeXML *root);
    void readMainConfig(treeXML *root);
     
void displayMenu(int i);
int  doProgram(svmApp *app,int i);
    void doTask(svmApp *app);
        void runAllTask(svmApp *app);
    void displayMenuDoLearningTask();
void doATask(svmApp *root,int opt);
void runMainApp();

#endif
