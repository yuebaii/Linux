#include "queue.h"
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

#define THREAD_NUMBER 4//�������߳�����������4�ˣ�������4

void *thread_push(void *arg);
void *thread_pop(void *arg);

/*
��ʼ���ն���

Ϊ��ģ���̶߳���Դ����ռ
����4���߳� ÿ���߳�push 20��Ԫ�� 0~19
�ȴ�4���߳̽���
��ӡ����Ԫ�� ��֤push
�����ĸ��߳� ÿ���̶߳��Զ��н��� pop����
*/
int main()
{
	LinkQueue que;
	init_Queue(&que);

	int i;
	/*
	�����ĸ����߳� ÿ���̶߳�ִ�� thread_push(&que)
	*/
	pthread_t threadArr[THREAD_NUMBER];
	for (i = 0; i < THREAD_NUMBER; ++i)
	{
		pthread_create(&threadArr[i], NULL, thread_push, (void *)&que);
	}

	/*
	�ȴ��ĸ��̶߳�ִ����
	Ҫ��Ȼ���߳�һ���Ӿ������� ����ͽ�����
	���о��� Ϊ��show���� ������֤Ԫ���ǲ��Ƕ�push��ȥ��
	*/
	for (i = 0; i < THREAD_NUMBER; ++i)
	{
		pthread_join(threadArr[i], NULL);
	}

	show(&que);

	/*
	�����ĸ����߳� ÿ���̶߳�ִ�� thread_pop(&que)
	*/
	for (i = 0; i < THREAD_NUMBER; ++i)
	{
		pthread_create(&threadArr[i], NULL, thread_pop, (void *)&que);
	}

	for (i = 0; i < THREAD_NUMBER; ++i)
	{
		pthread_join(threadArr[i], NULL);
	}

	exit(EXIT_SUCCESS);
}

void *thread_push(void *arg)
{
	printf("start push\n");
	LinkQueue * quePtr = (LinkQueue *)arg;
	int i;
	for (i = 0; i < 20; ++i)
	{
		cas_push(quePtr, i);
	}
	printf("finish push\n");
	pthread_exit(NULL);
}

void *thread_pop(void *arg)
{
	printf("start pop\n");
	LinkQueue * quePtr = (LinkQueue *)arg;
	int tmp;
	int res;
	while (1)
	{
		res = cas_pop(quePtr, &tmp);
		if (!res)
		{
			break;
		}
		printf("%d ", tmp);
        //sleep(1);
	}
	printf("finish pop\n");
	pthread_exit(NULL);
}
