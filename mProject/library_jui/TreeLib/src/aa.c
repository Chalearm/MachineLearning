#include <stdio.h>

void printPointer(const void* p)
{
    void **o = (void**)p;

    printf("-... %p \n",*o);
    
    
    
    printf("... %p \n",p);
}
int main(int argc,char** argv)
{
    void* a =NULL;
    int b = 20;
    a = &b;
    printPointer(&a);
    printPointer(a);
    printPointer(&b);
    printf("%d %d\n",sizeof(long),sizeof(long long int));
    return 0;
}