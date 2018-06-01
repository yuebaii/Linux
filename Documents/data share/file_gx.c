#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
	int fd = open(argv[1],O_RDONLY);
	assert(fd != -1);
	pid_t res = fork();
	assert(res != -1);
	if(res == 0)
	{
		char buff[128];
		read(fd,buff,1);
		printf("child::%c\n",buff[0]);
	}
	else
	{
		sleep(1);
		char buffer[128];
		read(fd,buffer,1);
		printf("parent::%c\n",buffer[0]);
	}

	close(fd);
}

