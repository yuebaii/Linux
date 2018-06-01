#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msgbuff
{
	long type;
	char data[128];
};

void main()
{
	int msgid=msgget((key_t)1234,IPC_CREAT|0664);
	assert(msgid!=-1);

	struct msgbuff buff;
	memset(&buff,0,sizeof(buff));
	msgrcv(msgid,&buff,127,2000,0);
	printf("%s\n",buff.data);
}
