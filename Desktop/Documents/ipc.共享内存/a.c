#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<ctype.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include"mem.h"

int main()
{
	struct membuff *shared_buff;
	char buff[128];
	int shmid = shmget((key_t)1234, 128, IPC_CREAT | 0664);
	if(shmid == -1)
	{
		printf("shmget error!\n");
		exit(0);
	}
	 
	void *memaddr = shmat(shmid, (void*)0, 0);
	printf("shmat attched at %X\n", memaddr);

	shared_buff = (struct membuff *)memaddr;
	while(1)
	{
		fgets(buff, 128, stdin); 
		buff[strlen(buff)-1] = 0;
		strncpy(shared_buff->data, buff, 128);
		shared_buff->flag = 1;
		if(strncmp(buff, "end", 3) == 0)
		{
			break;
		}
		memset(buff, 0, 128);
	}
	shmdt(memaddr);
	shmctl(shmid, IPC_RMID, 0);
}
