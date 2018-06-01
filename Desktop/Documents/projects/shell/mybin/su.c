#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <pwd.h>
#include <shadow.h>
#include <termios.h>

int main(int argc, char *argv[])
{
	char *user = "root";

	if(argv[1] != NULL)
	{
		user = argv[1];
	}

	//input  password
	printf("Passwd: ");
	fflush(stdout);
	char passwd[128] = {0};
	struct termios old, new;
	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~ECHO;
	new.c_lflag &= ~ICANON;  
	tcsetattr(0, TCSANOW, &new);  
	//fgets(passwd, 128, stdin);
	char c = 0;
	int num = 0;
	while((c = getchar())!= '\n')
	{
		if(c == 127)
		{
			if(num > 0)
			{
				passwd[--num] = 0;
				printf("\033[1D");//光标向左移动一列
				printf("\033[K");//光标后面的剩余一行覆盖
			}
			continue;
		}
		printf("*");
		fflush(stdout);
		passwd[num++] = c;
	}
	tcsetattr(0, TCSANOW, &old);
	//passwd[strlen(passwd) - 1] = 0;

	printf("\n");

	struct spwd *sp = getspnam(user);
	assert(sp != NULL);

	//printf("%s\n", sp->sp_pwdp);

	char salt[128] = {0};
	int i = 0, count = 0;
	for(; sp->sp_pwdp[i] != 0; ++i)
	{
		salt[i] = sp->sp_pwdp[i];
		if(salt[i] == '$')
		{
			count++;
			if(count == 3)
			{
				break;
			}
		}
	}

	char *p =(char*) crypt(passwd, salt);//jiamisuanfa
	assert(p != NULL);

	//printf("%s\n", p);

	if(strcmp(p, sp->sp_pwdp) != 0)
	{
		printf("passwd error\n");
		exit(0);
	}
	
	pid_t pid = fork();
	assert(pid != -1);

	if(pid == 0)
	{
		struct passwd *pw = getpwnam(user);
		assert(pw != NULL);
		setuid(pw->pw_uid);
		setenv("HOME", pw->pw_dir, 1);
		execl(pw->pw_shell, pw->pw_shell, (char*)0);
		printf("error\n");
		exit(0);
	}
	else
	{
		wait(NULL);
	}
}