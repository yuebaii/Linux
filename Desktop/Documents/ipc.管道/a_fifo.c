#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
int main()
{
	int fd = open("FIFO",O_WRONLY);
	if(fd == -1)
	{
		exit(0);
	}
	
	char buf[128] = {0};
	while(1)
	{
	fgets(buf, 128, stdin);
	buf[strlen(buf)-1] = 0;
	write(fd, buf, strlen(buf));
	if(strncmp(buf, "end", 3) == 0)
	{
		break;
	}
	memset(buf, 0, 128);
	}
	printf("write successed!");
	close(fd);
}
