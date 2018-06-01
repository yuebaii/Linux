#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"mem.h"

int main()
{
	struct membuff *shared_buff;
	int shmid = shmget((key_t)1234, 128, 0664);
	if(shmid == -1)
	{
		printf("shmet error!");
	}
	void *memaddr = shmat(shmid, (void *)0, SHM_RDONLY);
	shared_buff = (struct membuff *)memaddr;
	int num = 0;
	while(1)
	{
		if(strncmp((shared_buff->data), "end", 3) == 0)
		{
			break;
		}
		if(shared_buff->flag == 1)
		{
			int i = 0;
			int count = 0;
			for(i = 0; i < sizeof(shared_buff->data); i++)
			{
				if(isalpha(shared_buff->data[i]) && (!isalpha(shared_buff->data[i+1])))
				
				{
					count++;
				}
				num += count;
			}
		}
	}
	
	printf("%d",num);
	shmdt(memaddr);
}
