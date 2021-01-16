#ifndef SVMERRHANDLER_H_
#define SVMERRHANDLER_H_
#include "taskMgr.h"
#include "svmApp.h"
#include "simReadXML.h"
#include "simStringList.h"
#include "listChar.h"
#include "convertStr2Digi.h"
#include "eleXMLNodeList.h"
struct errReport
{
   simStrList    msgList;
   charList      statusList;
   char          canWork;
};
typedef struct errReport errReport;
int  initialErrReport(errReport* errP);
void destructorErrReport(errReport* errP);
void addListErrReportVChar(errReport *errP,vector_char *vch,char status);
void addListErrReport(errReport *errP,simString *str,char status);
int  getNumListErrReport(errReport *errP);
int  moveSimStrListAndCharListToErrReport(errReport *errP,simStrList *pathList,charList *statusList);
/*-------- application of errReport */;
int openFileBysimString(FILE **fp,const char *mode,simString *str);
int openFileByVectorChar(FILE **fp,const char *mode,vector_char *vch);
int checkConfigPaths(svmApp *app,errReport *errP);
int checkAllTaskPath(svmApp *app,errReport *errP);
    int getListPathInTaskMgr(errReport *errP,simStrList *listPath,charList *listUse,svmApp *app);

int checkAllInputPath(svmApp *app,errReport *errP);
    int getAndCheckTrainingList(svmApp *app,simString *ds_mgr,simStrList *pathList,charList *statusList);
    int getAndCheckTestingList(svmApp *app,simString *ds_mgr,simStrList *pathList,charList *statusList);
void reportConfigPathError(errReport *errP,treeXML *root);
    int  readTagErrPathFile(treeXML *root);
    vector_char  readPathFromTagErrPathFile(treeXML *root);
const char* errorNumberToMsg(int a);
#endif
