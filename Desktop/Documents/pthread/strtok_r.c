#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include<pthread.h>

void *pthread_fun(void *arg)
{
	char buff[128]="a,b,c,d,e,f,g";
	char *q=NULL;
	//char *p=strtok(buff,",");
	char *p = strtok_r(buff, ",", &q);
	while(p!=NULL)
	{
		printf("fun::%s\n",p);
		sleep(1);
		p=strtok(NULL,",");
	}

}

void main()
{
	pthread_t id;
	int res=pthread_create(&id,NULL,pthread_fun,NULL);
	assert(res==0);

	char buff[128]="1,2,3,4,5,6,7";
	char *q=NULL;
	//char *p=strtok(buff,","); //线程不安全
	char *p = strtok_r(buff, ",", &q);//此函数为strtok的线程安全版本
	while(p!=NULL)
	{
		printf("main::%s\n",p);
		sleep(1);
		p=strtok(NULL,",");
	}
	pthread_join(&id,NULL);
}
