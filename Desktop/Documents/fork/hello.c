#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>

int main()
{
	int i = 0;
	for(;i < 2; i++)
	{
		if(fork())
		//	printf("A");
		    printf("A\n");
		else
		//	printf("B");
		    printf("B\n");
	}
}

