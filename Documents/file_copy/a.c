#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<fcntl.h>
#include<string.h>
int main()
{
	int fd = open("a1.txt",O_WRONLY | O_CREAT,0664);
	assert(fd != -1);

	while(1)
	{
		printf("input:");
		fflush(stdout);
		char buff[128] = {0};
	    int n = read(0,buff,127);
		if(strncmp(buff,"end",3) == 0)
		{
		    break;
		}
		int i = 0;
		for(;i < n; i++)
		{
			if(buff[i] >= 'A' && buff[i] <= 'Z')
			{
				buff[i] += 32;
			}
			else if(buff[i] >= 'a' && buff[i] <= 'z')
			{
				buff[i] -= 32;
			}
			else 
			{
				continue;
			}
		}

	write(fd,buff,n);
	}
	close(fd);
}
