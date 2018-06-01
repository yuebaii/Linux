#include<iostream>
#include<unistd.h>
using namespace std;

int main()
{
	pid_t pid = 0;
	int num = 0;
	if(fork())
	{
		num = 1;
		cout<<"parent=="<<num<<endl;
	}
	else
	{
		num = 100;
		cout<<"children=="<<num<<endl;
	}
}
