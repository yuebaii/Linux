#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

void main()
{
	printf("exec start\n");

	sleep(2);

	printf("exec front pid == %d\n", getpid());

	execl("./mykill", "./mykill", "1234", (char *)0);

	printf("exec finish\n");

	sleep(2);

	printf("exec end\n");
}
