#include<stdio.h>
#include<string.h>

int main()
{
	pid_t pid = fork();
	if(pid == 0)
	{
		printf("child pid == %d", getpid());
		execl("./tests.sh", "test.sh", "aaa", "bbb", "ccc", (char*)0);
		exit(0);
	}
	else
	{
		printf("parent pid == %d", getpid());
		wait(NULL);
	}
	printf("main over!");
}
