#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
//int fdd[2];
int main()
{
    	int fdd[2];
	pipe(fdd);
	pid_t fd = fork();

	if(fd == 0)
	{
		sleep(1);
		close(fdd[1]);
		char buf[128] = {0};

		while(1)
		{
		int length = 0;
		read(fdd[0], buf, 127);
		if(strncmp(buf, "end", 3) == 0)
		{
			break;
		}

		length += (strlen(buf)-1);
		memset(buf, 0, 127);
		printf("%d\n", length);
		}
		close(fdd[0]);
	}
	else
	{
		close(fdd[0]);
		char buf[128] = {0};
		while(1)
		{
		printf("input:");		
		fgets(buf, 127, stdin);
		
		write(fdd[1], buf, strlen(buf)); 
		if(strncmp(buf, "end", 3) == 0)
		{
        	break;
		}
		sleep(1.8);
		memset(buf, 0, 128*sizeof(buf[0]));
		}
		close(fdd[1]);
		
	}

}
