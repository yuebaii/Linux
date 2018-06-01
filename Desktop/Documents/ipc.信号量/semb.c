#include"sem.h"

void main()
{
	sem_get();
	sem_P();

	int i;
	for(i=2;i<100;i++)
	{
		int j=2;
		for(;j<i/2;j++)
		{
			if(i%j==0)
			{
				break;
			}
		}
		while(j<i/2)
		{
			printf("%d   ",i);
		}
	}
	sem_del();
}
