#include <stdio.h>

#define SETTINGFILE "setting.xml"
#include "replacingApp.h"

int main(int argc,char** argv)
{
    repApp theRep;
    constructorRepApp(&theRep);
    getInputRepApp(&theRep,SETTINGFILE);
    initialRepApp(&theRep);
    startProcessRepApp(&theRep);
    printRepApp(&theRep);
    destructorRepApp(&theRep);
    printf("Hello World \n");
    return 0;
}

