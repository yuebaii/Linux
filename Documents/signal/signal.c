#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <signal.h>

void fun(int);
int count = 0;

void main()
{
	signal(SIGINT, fun);

	while(1)
	{
		sleep(2);
		printf("main running\n");
	}
}

void fun(int sign)
{
	printf("hello world\n");
	signal(SIGINT, SIG_DFL);
}
