#include<stdio.h>
#include<string.h>
#include"sem.h"

int main()
{
	sem_get();
	char buff[128];
	while(1)
	{
		fgets(buff, 128, stdin);
		buff[strlen(buff)-1] = 0;

		if(strncmp(buff, "OK", 2) == 0)
		{
			sem_v();
		}
		if(strncmp(buff, "end", 3) == 0)
		{
			break;
		}
	}
	sem_del();
}
