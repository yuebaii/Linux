#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	printf("mykill pid == %d\n", getpid());
	if(argc < 2)
	{
		printf("please input pid\n");
		exit(0);
	}

	//argv[1] = "1234";
	int pid = 0;
        int signum = 0;
	sscanf(argv[1], "%d", &pid);
 	sscanf(argv[2], "%s", &signum);//9
	printf("pid == %d\n", pid);

	//if(kill(pid, SIGCHLD) == -1)
	if(kill(pid, signum) == -1)
	{
		perror(NULL);
		exit(0);
	}
}
