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
	/*
	 * socket   connect  recv/send  close
	 */

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);

	struct sockaddr_in  ser, cli;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(6000);
	ser.sin_addr.s_addr = inet_addr("192.168.1.120");

	int res = connect(sockfd, (struct sockaddr*)&ser, sizeof(ser));
	assert(res != -1);

	send(sockfd, "hello world", strlen("hello world"), 0);
	char buff[128] = {0};
	recv(sockfd, buff, 127, 0);

	printf("recv:: %s\n", buff);

	close(sockfd);
}
