#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<signal.h>

int main()
{
	printf("....\n");
	sleep(2);
	pid_t pid = fork();
	if(pid == 0)
	{
		execl("./main", "./main", (char*)0);
	}
	else
	{
		printf("father start\n");
		sleep(3);
		printf("father over\n");
	}
}
