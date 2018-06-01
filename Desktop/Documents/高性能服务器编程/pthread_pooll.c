#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>

#define  MAX  10
int fds[MAX];
//因为在主线程与不同的函数线程之间，有可能函数线程取文件描述符，还没执行完get_fds（）。此时主线程add_fds()添加文件描述符到等待队列中，可能存在不连续添加到队列中的情况，所以获取文件描述符与添加文件描述符操作应该加锁控制。。
sem_t sem;
pthread_mutex_t mutex;

void Init_fds()
{
	int i = 0;
	for(; i < MAX; ++i)
	{
		fds[i] = -1;
	}
}

int Add_fds(int c)
{
	pthread_mutex_lock(&mutex);

	int i = 0;
	for(; i < MAX; ++i)
	{
		if(fds[i] == -1)
		{
			fds[i] = c;
			pthread_mutex_unlock(&mutex);
			return 1;
		}
	}

	if(i == MAX)
	{
		pthread_mutex_unlock(&mutex);
		return 0;
	}
}

void Del_fds(int i)
{
	for(; i < MAX - 1; ++i)
	{
		fds[i] = fds[i + 1];

		if(fds[i+1] == -1)
		{
			break;
		}
	}
	fds[MAX - 1] = -1;
}

int Get_fds()
{
	pthread_mutex_lock(&mutex);

	int i = 0, c = -1;
	for(; i < MAX; ++i)
	{
		if(fds[i] != -1)
		{
			c = fds[i];
			Del_fds(i);
			break;
		}
	}

	pthread_mutex_unlock(&mutex);
	return c;
}

void *pthread_fun(void *arg)
{
	while(1)  //工作线程必须死循环，不能处理一个客户端以后就结束
	{
		sem_wait(&sem);
		int c = Get_fds();
		if(c == -1)
		{
			continue;
		}
		while(1)
		{
			char buff[128] = {0};
			int n = recv(c, buff, 127, 0);
			if(n <= 0)
			{
				close(c);
				break;
			}

			printf("cli: %d ; buff: %s\n", c, buff);
			send(c, "OK", 2, 0);
		}
	}
}

int main(int argc, char *argv[])
{
	Init_fds();
	sem_init(&sem, 0, 0);
	pthread_mutex_init(&mutex, NULL);
	int i = 0;
	for(; i < 3; ++i)
	{
		pthread_t id;
		int res = pthread_create(&id, NULL, pthread_fun, NULL);
		assert(res == 0);
	}

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);

	struct sockaddr_in ser, cli;
	memset(&ser, 0, sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(6000);
	ser.sin_addr.s_addr = inet_addr("192.168.1.120");

	int res = bind(sockfd, (struct sockaddr *)&ser, sizeof(ser));
	assert(res != -1);

	listen(sockfd, 5);

	while(1)
	{
		socklen_t len = sizeof(cli);
		int c = accept(sockfd, (struct sockaddr*)&cli, &len);
		if(c < 0)
		{
			printf("error\n");
			continue;
		}

		if(!Add_fds(c))
		{
			send(c, "please wait...", strlen("please wait..."), 0);
			close(c);
			continue;
		}
		sem_post(&sem); // 对信号量执行V操作
	}
	
	return 0;
}
