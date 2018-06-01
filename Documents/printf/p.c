#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	printf("0\n");
    printf("1");
	printf("Hello world!");
	printf("2");
//	fflush(stdout);
	_exit(0);
}
