#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>

struct msgbuff
{
	long type;
	char data[128];
};

int main()
{
	int msgid = msgget((key_t)1234, 0664);
	assert(msgid != -1);

	struct msgbuff buff;
	memset(&buff, 0, sizeof(buff));
	msgrcv(msgid, &buff, 127, 1000, 0);
	printf("%s\n", buff.data);
	msgctl(msgid,IPC_RMID,0);
}
