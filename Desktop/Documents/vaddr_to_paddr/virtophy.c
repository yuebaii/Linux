#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <fcntl.h>

int g = 10;

int add(int x, int y)
{
    return x + y;
}

unsigned long vir_to_phyadd(unsigned long vaddr )
{
    int pagesize = getpagesize();
    int index = vaddr / pagesize;
    int offset = vaddr % pagesize;

    int file_offset = index * 8;

    int fd = open("/proc/self/pagemap",O_RDONLY);
    if ( fd == -1 )
    {
        return 0;
    }

    lseek(fd,file_offset,SEEK_SET);
    uint64_t val = 0;

    read(fd,&val,sizeof(uint64_t));

    if ( val & ((uint64_t)1<<63) )
    {
        val &= (((uint64_t)1<<55 ) - 1 );

        unsigned long phyaddr = val * pagesize  + offset;
        return phyaddr; 
    }

    return 0;
}

int main()
{
    char *s = (char*)malloc(128);
    assert( s != NULL );

    pid_t pid = fork();
    if ( pid == 0 )
    {
        strcpy(s,"child");
    }
    else
    {
        strcpy(s,"parent");
	//	sleep(2);
    }
    int b = vir_to_phyadd((unsigned long)s);
    printf("pid=%d,vir=%x\n",getpid(),s);
    printf("pid=%d,phy:%x\n",getpid(),b);
	
	while(1)
	{
	}
    exit(0);
}
