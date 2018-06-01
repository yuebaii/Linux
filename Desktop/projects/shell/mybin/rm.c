#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>

void deletedir(char *dir)
{
   		 DIR *dp;
		 struct dirent *entry;
		 struct stat statbuf;

		 dp = opendir(dir);

		 chdir(dir);
		 while((entry = readdir(dp)) != NULL)
		 {
			 lstat(entry->d_name, &statbuf);
			 if(S_ISDIR(statbuf.st_mode))
			 {
				 deletedir(entry->d_name);
				 rmdir(entry->d_name);
			 }
			 else
			 {
				 unlink(entry->d_name);
			 }

		 }
		 chdir("..");
		 closedir(dp);
}
int main(int argc, char *argv[])
{
	if(argc < 3)
	{
     int flag = unlink(argv[1]);
     if(flag != 0)
    {
	 	 printf("No such file or directory");
    }
	}
	else
	{	
		deletedir(argv[2]);
	}
}



