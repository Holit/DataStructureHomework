#include <stdio.h>

#ifndef _main_
#define _main_ main
#else
#define _main_ default_main
#endif // !_main_

int _main_(int argc, char* argv)
{
	printf("Hello World!");
	return 0;
}