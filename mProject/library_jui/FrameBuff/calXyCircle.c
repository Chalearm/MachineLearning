#include <stdio.h>
#include <math.h>

int main(int argc,char **argv)
{
    int tTa1,tTa2;
    int r =0;
    double pi = acos(-1);
    if(argc ==4)
    {
        
        sscanf(argv[1],"%d",&tTa1);
        sscanf(argv[2],"%d",&tTa2);
        sscanf(argv[3],"%d",&r); 
        
        printf("(x1,y1) : (%f,%f)\n",r*sin(pi*tTa1/180),r*cos(pi*tTa1/180));
        printf("(x2,y2) : (%f,%f)\n",r*sin(pi*tTa2/180),r*cos(pi*tTa2/180)); 
        printf("Vector : (%f,%f)\n",r*(sin(pi*tTa2/180)-sin(pi*tTa1/180)),r*(cos(pi*tTa2/180)-cos(pi*tTa1/180)));
    }
    else
    {
        /* do nothing */
    }
    return 0;
}