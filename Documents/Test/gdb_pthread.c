#include<stdio.h>
#include<pthread.h>
//using namespace std;

void *test(void *arg)
{
//	int num = (int)arg;
	int num = 0;
	printf("child pthread==%d\n",num);

	pthread_exit("finished!\n");
}

int main()
{
	pthread_t pth;
	void *status;
	int num = 0;
	pthread_create(&pth, NULL, test, NULL);

	num = 10;
	printf("main pthread==%d\n", num);
	pthread_join(pth, &status);
	printf("%s", (char*)status);
}
