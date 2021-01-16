#include <iostream>
#include <stdlib.h>  /* srand, rand */
#include <time.h>     /* time */
#include "datgen.h"
using namespace std;
int main()
{  
    /* initialize random seed: */
    srand (time(NULL));
    datGen ok("datGsetting.xml");
    ok.startGenDat();
   // ok.printGenAttrb();
   // cout<<"Ok jui "<<randomizedFn(100.51,-4.41);
return 0;
}