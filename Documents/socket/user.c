#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	assert(sockfd != -1);

	struct sockaddr_in ser, cli;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(6000);
	ser.sin_addr.s_addr = inet_addr("127.0.0.1");

	int res = bind(sockfd, (struct sockaddr *)&ser, sizeof(ser));
	assert(res != -1);

	while(1)
	{
	char buff[128] = {0};
	int len = sizeof(cli);
	recvfrom(sockfd, buff, 5, 0, (struct sockaddr *)&cli, &len);
	printf("%s \n", buff);
	sendto(sockfd, "I know!", strlen("I know!"), 0, (struct sockaddr*)&cli, len);
	}
	close(sockfd);
}

