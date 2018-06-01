#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int a = 15;
	int *p = (int*)malloc(4);
	*p = 10;
    	pid_t f = fork();
	assert(f != -1);

	if(f == 0)
	{
		a = 19;
		*p = 15;
		printf("child = %d,%d\n",a,*p);
	}
	else
	{
		sleep(2);
		printf("father = %d,%d\n",a,*p);
	}
}
