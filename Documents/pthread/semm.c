#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<assert.h>
#include<semaphore.h>

char buff[128]={0};
sem_t sem1;//共享信号量
sem_t sem2;

void *pthread_fun(void *arg)
{
	int num=0;
	while(1)
	{
		sem_wait(&sem2);//p
		if(strncmp(buff,"end",3)==0)
		{
			break;
		}
 		printf("buff lenth:%d\n",strlen(buff)-1);
		sem_post(&sem1);
	}
}

void main()
{
	pthread_t id;
	int res=pthread_create(&id,NULL,pthread_fun,NULL);
	assert(res==0);
	
	sem_init(&sem1,0,1);
	sem_init(&sem2,0,0);

	while(1)
	{
		sem_wait(&sem1);
		printf("please input:");
		fflush(stdout);
		
		fgets(buff,128,stdin);
		sem_post(&sem2);//v
		buff[strlen(buff)-1]==0;
		if(strncmp(buff,"end",3)==0)
		{
			break;
		}
		
	}
	pthread_join(&id,NULL);
}
