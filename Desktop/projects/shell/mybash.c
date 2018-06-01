#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/utsname.h>

#define LENTH 20
char *cmdArr[LENTH]={NULL};
int count = 0;

char OLDPWD[128] = {0};

//提示符输出函数
void out_flag()
{
	char path[128] = {0};
	if(NULL == getcwd(path, 128))
	{
		printf("getcwd error\n");
		return;
	}

	char dir[128] = {0};
	char *p = strtok(path, "/");
	while(p != NULL)
	{
		strcpy(dir, p);
		p = strtok(NULL, "/");
	}

	if(strlen(dir) == 0)
	{
		strcpy(dir, "/");
	}
	
	struct passwd *pw = getpwuid(getuid());
	if(pw == NULL)
	{
		printf("error\n");
		return;
	}
	if(strcmp(pw->pw_dir, getcwd(path, 128)) == 0)
	{
		memset(dir, 0, 128);
		strcpy(dir, "~");
	}

	struct utsname host;
	uname(&host);

	char *hname = strtok(host.nodename, ".");
	if(hname == NULL)
	{
		printf("error\n");
		return;
	}

	char flag = '$';

	if(pw->pw_uid == 0)
	{
		flag = '#';
	}

	printf("[%s@%s %s]%c ", pw->pw_name, hname, dir, flag);
	fflush(stdout);
}

//命令切割函数
void cut_cmd(char *cmd)
{
	count = 0;
	memset(cmdArr, 0, LENTH * sizeof(cmdArr[0]));
	char *p = strtok(cmd, " ");
	while(p != NULL)
	{
    	cmdArr[count++] = p;
		p = strtok(NULL, " ");
	}
}

//cd命令实现
void my_cd()
{
	/*
	 * cd 绝对路径    相对路径    chdir(路径);
	 * cd ~    cd                直接进入当前用户的家目录
	 * cd -            切换到上一次所在的目录
	*/

	char nowpwd[128] = {0};
	getcwd(nowpwd, 128);

	if(cmdArr[1] == NULL || strncmp(cmdArr[1], "~", 1) == 0)
	{
		struct passwd *pw = getpwuid(getuid());
		if(chdir(pw->pw_dir) == -1)
		{
			perror(pw->pw_dir);
			return;
		}
	}
	else if(strncmp(cmdArr[1], "-", 1) == 0)
	{
		if(strlen(OLDPWD) == 0)
		{
			printf("OLDPWD not set\n");
			return;
		}
		printf("%s\n", OLDPWD);
		if(chdir(OLDPWD) == -1)
		{
			perror(OLDPWD);
			return;
		}
	}
	else
	{
		if(chdir(cmdArr[1]) == -1)
		{
			perror(cmdArr[1]);
			return;
		}
	}

	strcpy(OLDPWD, nowpwd);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, SIG_IGN);
	while(1)
	{
		out_flag();
		char cmd[128] = {0};
		fgets(cmd, 128, stdin);
		cmd[strlen(cmd) - 1] = 0;

		if(strlen(cmd) == 0)
		{
			continue;
		}

		cut_cmd(cmd);

		if(cmdArr[0] == NULL)
		{
			continue;
		}
		
		if(strncmp(cmdArr[0], "cd", 2) == 0)
		{
			my_cd();
			continue;
		}
		if(strncmp(cmdArr[0], "exit", 4) == 0)
		{
			exit(0);
		}

/*----------------------------------------------------------------*/		
		pid_t pid = fork();
		assert(pid != -1);

		if(pid == 0)
		{
			//exec  调用命令所对应的可执行文件
			char path[128] = "/home/yuebai/Documents/projects/shell/mybin/";

			if(strstr(cmdArr[0], "/") != NULL)
			{
				memset(path, 0, 128);
			}
			strcat(path, cmdArr[0]);
			execv(path, cmdArr);

			printf("mybash: %s :: command not found\n", cmdArr[0]);
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
}
