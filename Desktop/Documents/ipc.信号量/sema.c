#include"sem.h"

void main()
{
	sem_get();

	while(1)
	{
		printf("please input:");
		fflush(stdout);
		char buff[128]={0};
		fgets(buff,128,stdin);
		buff[strlen(buff)-1]=0;
		if(strncmp(buff,"ok",2)==0)
		{
			sem_V();
		}
		if(strncmp(buff,"end",3)==0)
		{
			break;
		}

	}
	sem_del();
}
