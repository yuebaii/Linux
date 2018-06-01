#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define MAX 128

void main()
{
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(listenfd != -1);

	struct sockaddr_in ser, cli;
	memset(&ser, 0, sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(6000);
	ser.sin_addr.s_addr = inet_addr("192.168.52.130");

	int res = bind(listenfd, (struct sockaddr*)&ser, sizeof(ser));
	assert(res != -1);

	listen(listenfd, 5);

	int epfd = epoll_create(5);
	assert(epfd != -1);

	struct epoll_event revents[MAX];//存放就绪文件描述符的数组
	
	struct epoll_event event;//指定事件
	event.events = EPOLLIN;// | EPOLLET;  //事件类型
	event.data.fd = listenfd;  //事件所从属的文件描述符

	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &event);

	while(1)
	{
		int n = epoll_wait(epfd, revents, MAX, -1);
		assert(n != -1);
		if(n == 0)
		{
			printf("time out\n");
			continue;
		}
 
		int i = 0;
		for(; i < n; ++i)
		{
			if(revents[i].events & EPOLLIN)
			{
				int fd = revents[i].data.fd;
				int len = sizeof(cli);
				if(fd == listenfd)
				{
					int c = accept(listenfd, (struct sockaddr*)&cli, &len);
					assert(c != -1);
					event.data.fd = c;
					epoll_ctl(epfd, EPOLL_CTL_ADD, c, &event);
				}
				else
				{
					char buff[10] = {0};
					int n = recv(fd, buff, 1, 0);
					if(n <= 0)
					{
						close(fd);
						revents[i].data.fd = -1;
						continue;
					}
					printf("%s \n", buff);
				}
			}
		}
	}
}
