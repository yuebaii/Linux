#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

void main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);

	struct sockaddr_in ser, cli;
	memset(&ser, 0, sizeof(ser));
	ser.sin_family = AF_INET;
	ser.sin_port = htons(6500);
	ser.sin_addr.s_addr = inet_addr("192.168.1.120");

	int res = connect(sockfd, (struct sockaddr*)&ser, sizeof(ser));
	assert(res != -1);

	while(1)
	{
		printf("please input: ");
		fflush(stdout);
		char buff[128] = {0};
		fgets(buff, 128, stdin);
		if(strncmp(buff, "end", 3) == 0)
		{
			close(sockfd);
			break;
		}

		send(sockfd, buff, strlen(buff) - 1, 0);
		memset(buff, 0, 128);
		recv(sockfd, buff, 127, 0);
		printf("%s\n", buff);
	}
}
