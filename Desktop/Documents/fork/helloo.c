#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>

int main()
{
	if(fork() || fork())
		printf("A\n");
	else 
		printf("B\n");
}
