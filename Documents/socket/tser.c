#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);

	struct sockaddr_in ser, cli;
	ser.sin_family = AF_INET; // 地址簇、
	ser.sin_port = htons(6000);
	ser.sin_addr.s_addr =inet_addr("192.168.1.120");

	int res = bind(sockfd, (struct sockaddr*)&ser, sizeof(ser));
	assert(res != -1);

	listen(sockfd, 5);
	printf("listen over\n");

	while(1)
	{
		int len = sizeof(cli);
		int c = accept(sockfd, (struct sockaddr*)&cli, &len);
		assert(c != -1);

		char buff[128] = {0};
		recv(c, buff, 127, 0);
		printf("recv:: %s\n", buff);
		send(c, "I Know", strlen("I Know"), 0);

		close(c);
	}

	close(sockfd);
}
