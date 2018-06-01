#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>

//mkdir abc
int main(int argc, char *argv[])
{
    //int fd = open(argv[1], O_WRONLY | O_CREAT, 0664);
	//assert(fd != -1);
	mkdir(argv[1], 0664);
}
