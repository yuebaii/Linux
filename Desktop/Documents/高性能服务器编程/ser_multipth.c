#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>

struct sockaddr_in ser, cli;
void *fun(void *arg)
{
	int c = (int)arg;
	while(1)
	{
		char buff[128] = {0};
		int n = recv(c, buff, 127, 0);
		if(n <= 0)
		{
			break;
		}
		printf("addr::%s  port::%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
		printf("%s \n", buff);
		send(c, "OK", 2, 0);
	}
	printf("%d unlink!\n", c);
	close(c);
	pthread_exit("read!\n");
}
int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&ser, 0, sizeof(ser));
	ser.sin_addr.s_addr = inet_addr("192.168.52.130");
	ser.sin_port = htons(6500);
	ser.sin_family = AF_INET;

	int res = bind(sockfd, (struct sockaddr *)&ser, sizeof(ser));
	assert(res != -1);
	 
	listen(sockfd, 5);
	
	while(1)
	{
		int len = sizeof(cli);
		int a = accept(sockfd, (struct sockaddr *)&cli, &len);//返回一个文件描述符
		if(a < 0)
		{
			printf("Error\n");
			break;
		}

		pthread_t pth;
		pthread_create(&pth, NULL, fun, (void *)a);
	        pthread_join(&pth, NULL);
	}
}
