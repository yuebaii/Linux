#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<assert.h>
#include<semaphore.h>

char buff[128]={0};
sem_t sem;//共享信号量

void *pthread_fun(void *arg)
{
	int num=0;
	while(1)
	{
		sem_wait(&sem);//p
		if(strncmp(buff,"end",3)==0)
		{
			break;
		}
 		printf("buff lenth:%d\n",strlen(buff)-1);
		sem_post(&sem);
	}
}

void main()
{
	pthread_t id;
	int res=pthread_create(&id,NULL,pthread_fun,NULL);
	assert(res==0);
	
	sem_init(&sem,0,1);

	while(1)
	{
		sem_wait(&sem);
		printf("please input:");
		fflush(stdout);
		
		fgets(buff,128,stdin);
		sem_post(&sem);//v
		buff[strlen(buff)-1]==0;
		if(strncmp(buff,"end",3)==0)
		{
			break;
		}
		
	}
	pthread_join(&id,NULL);
}
