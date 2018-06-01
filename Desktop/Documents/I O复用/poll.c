#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>

#define MAX 128

void Init(struct pollfd *fds, int len)
{
	int i = 0;
	for(; i < len; ++i)
	{
		fds[i].fd = -1;
		fds[i].events = 0;
	}
}

void AddFd(struct pollfd *fds, int len, int fd)
{
	int i = 0;
	for(; i < len; ++i)
	{
		if(fds[i].fd == -1)
		{
			fds[i].fd = fd;
			fds[i].events = POLLIN;
			break;
		}
	}
}

void main()
{
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(listenfd != -1);

	struct sockaddr_in ser, cli;
	memset(&ser, 0, sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(6000);
	ser.sin_addr.s_addr = inet_addr("192.168.1.120");

	int res = bind(listenfd, (struct sockaddr*)&ser, sizeof(ser));
	assert(res != -1);

	listen(listenfd, 5);

	struct pollfd fds[MAX];
	Init(fds, MAX);
	AddFd(fds, MAX, listenfd);

	while(1)
	{
		int n = poll(fds, MAX, -1);
		assert(n != -1);
		if(n == 0)
		{
			printf("time out\n");
			continue;
		}
		int i = 0;
		for(; i < MAX; ++i)
		{
			if(fds[i].fd == -1)
			{
				continue;
			}
			if(fds[i].revents & POLLIN)
			{
				int fd = fds[i].fd;
				if(fd == listenfd)
				{
					int len = sizeof(cli);
					int c = accept(fd, (struct sockaddr *)&cli, &len);
					assert(c != -1);

					printf("one client link\n");

					AddFd(fds, MAX, c);
				}
				else
				{
					char  buff[128] = {0};
					int n = recv(fd, buff, 127, 0);
					if(n <= 0)
					{
						printf("client unlink\n");
						close(fd);
						fds[i].fd = -1;
						fds[i].events = 0;
						continue;
					}

					printf("%d :  %s\n", fd, buff);
					send(fd, "OK", 2, 0);
				}
			}
		}
	}
}
