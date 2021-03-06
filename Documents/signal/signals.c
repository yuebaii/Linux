#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <signal.h>

void sig_fun(int sign)
{
	printf("sig_fun start  %d\n", sign);
	int i = 0;
	for(; i < 10; ++i)
	{
		//sleep(1);
		printf("sig_fun running\n");
	}
	printf("sig_fun end\n");
	signal(sign, SIG_DFL);
}

void main()
{
	signal(SIGINT, sig_fun);
	signal(SIGTERM, sig_fun);

	while(1)
	{
		sleep(2);
		printf("main running\n");
	}
}
