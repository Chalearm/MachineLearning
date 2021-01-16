#include <stdio.h>
#include "foo.h"

int main()
{
	puts("This is a shared library test...");
	foo();
	return 0;
}
