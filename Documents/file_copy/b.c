#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{	if(argc < 3)
	{
		printf("Error!");
		exit(0);
	}
	int fda=open(argv[1],O_RDONLY);
		if(fda == -1) 
		{
			printf("OPen failed!");
		}
	int fdb=open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0664);
		if(fdb == -1)
		{
			printf("open failed!");
		}
	while(1)
	{
		char buff[1024];
		int n = read(fda,buff,1024);
		if(n <= 0)
		{
			break;
		}
		write(fdb,buff,strlen(buff));
	}
		close(fda);
		close(fdb);
	
}
