#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
	   rmdir(argv[1]);
   }
   else
   {
	   unlink(argv[2]);
   }
}
