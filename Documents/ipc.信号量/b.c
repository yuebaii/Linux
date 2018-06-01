#include<stdio.h>
#include"sem.h"

int main()
{
	sem_get();
	sem_p();
	int n = 2;
	int i = 2;
	int t  = 1;

	for(i = 2; i <= 100; i++)
	{
		int flag = 1;
		for(n = 2; n < i; n++)
		{
			if(i%n == 0)
		   {
			   flag = 0;
				break;
			}
		
		}
		if(flag)
		{
			printf("%d  ", i);
		}
	}
	sem_del();
}
