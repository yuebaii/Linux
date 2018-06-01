#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_DGRAM,0);
	assert(sockfd != -1);

	struct sockaddr_in cli, ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(6000);
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");

	sendto(sockfd, "Hello World", strlen("Hello World"), 0, (struct sockaddr *)&ser, sizeof(ser));
	char buff[128] = {0};
	recvfrom(sockfd, buff, 127, 0, NULL, NULL);
	printf("%s \n", buff);
	close(sockfd);
}

