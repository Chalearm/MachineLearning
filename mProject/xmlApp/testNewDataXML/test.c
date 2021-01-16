/*****************************************************************************/
/*	Name          : chalearm saelim                                          */
/*	E-mail        : chalearm33@hotmail.com, chalearm90@gmail.com             */
/*	Date-create   : 6 Sep 2014 15:09 UTC+7 Thailand                          */
/*	Purpose       : to test XMLUi library                                    */
/*                                                                           */
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "simStringList.h"
#include "simReadXML.h"
#include "simWriteXML.h"
#include "XmlUi.h"
#define PATH_DEFAULT "./taskForm.xml"
#define DEF_WORK 1

int main(int argc,char** argv)
{
    int res = DEF_WORK;
    XMLUi xmluiObj;
    initialXMLUi(&xmluiObj);
    res = loadSourceToXMLUi(&xmluiObj,PATH_DEFAULT);
    if(res==1)
    {
        printXMLUi(&xmluiObj);
    }
    else
    {
        printf("failed\n");
    }
    destructXMLUi(&xmluiObj);
    return res;
}
