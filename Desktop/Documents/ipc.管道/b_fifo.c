#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
int num = 0;
int main()
{
	int fd = open("FIFO",O_RDONLY);
	if(fd == -1)
	{
		exit(0);
	}

	char buf[128];
	int n = 0;
    while(1){
	printf("start read\n");
	read(fd, buf, 128);
	if(strncmp(buf, "end", 3) == 0)
	{
		break;
	}

	int i = 0; 
	//int word = 0;  
	int count = 1;
	for(i = 0; i < strlen(buf); i++)
	{
	/*	if(isalpha(buf[i]) && (!isalpha(buf[i+1])))
		{
			count++;
		}
	}*/
	
		if((isalpha(buf[i])) && (buf[i+1]==' '))
		{
            count++;
        }
	/*	if(buf[i]  == ' ')
		{
			word = 0;
		}
	    if(word == 0)
		{
			word = 1;
			count++;
		}*/
	}
		num = count+num;
    	memset(buf, 0, 128*sizeof(buf[0]));
}
	printf("%d\n", num);
	close(fd);
}
