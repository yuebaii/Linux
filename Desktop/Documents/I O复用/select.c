#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);

	struct sockaddr_in ser, cli;
	memset(&ser, 0, sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(6500);
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = bind(sockfd, (struct sockaddr*)&ser, sizeof(ser));
	assert(res != -1);

	listen(sockfd, 5);

	fd_set read;

	int nfds = 0;
	int fds[128];
	//memset(fds, -1, 128);
	int i = 0;
	for(; i < 128; i++)
	{
		fds[i] = -1;
	}
	fds[0] = sockfd;

	while(1)
	{
		int i = 0;
		FD_ZERO(&read);
		for(; i < 128; ++i)
		{
			if(fds[i] != -1)
			{
			if(fds[i] > nfds);
			{
				nfds = fds[i];
			}
			FD_SET(fds[i], &read);
			}
		}
		
		int n = select(nfds+1, &read, NULL, NULL, NULL);
		if(n < 0)
		{
			printf("error\n");
			exit(0);
		}
		if(n == 0) //  超时
		{
			printf("time out\n");
			continue;
		}
		i = 0;
		
		for(; i < 128; ++i)
		{
			if(fds[i] == -1)
				continue;

			if(FD_ISSET(fds[i], &read))
			{
				if(fds[i] == sockfd)
				{
					int len = sizeof(cli);
					int c = accept(sockfd, (struct sockaddr*)&cli, &len);
					int i = 0;
					for(; i < 128; ++i)
					{
						if(fds[i] == -1)
						{
							fds[i] = c;
							if(nfds-1 < c)							                   
							{
								nfds = c+1;
							}
								break;
						}
					}
				}
				else
				{
					char buff[128] = {0};
					int n = recv(fds[i], buff, 128, 0);
					if(n <= 0)
					{
						close(fds[i]);
						fds[i] = -1;
						continue;
					}

					printf("%s\n", buff);
					send(fds[i], "ok", 2, 0);
				}
			}
		}

	}
}
