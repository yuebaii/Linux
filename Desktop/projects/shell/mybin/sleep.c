#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	unsigned int time =(unsigned int)argv[1] -'0';
	printf("start.");
	sleep(time);
	printf("end!");
	return 0;
}
