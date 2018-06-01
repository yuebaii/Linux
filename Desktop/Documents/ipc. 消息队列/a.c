#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>

struct msgbuff
{
	long type;
	char data[128];
};

int main(int argc, char *argv[])
{
    int msgid =	msgget((key_t)1234, IPC_CREAT | 0664);
	assert(msgget != -1);

	struct msgbuff buff;
	if(strncmp(argv[1], "1000", 4) == 0)
	{
		buff.type = 1000;
		strcpy(buff.data, argv[2]);
		msgsnd(msgid, &buff, strlen(buff.data), 0);
	}
	if(strncmp(argv[1], "2000", 4) == 0)
	{
		buff.type = 2000;
		strcpy(buff.data, argv[2]);
		msgsnd(msgid, &buff, strlen(buff.data), 0);
	}
}
