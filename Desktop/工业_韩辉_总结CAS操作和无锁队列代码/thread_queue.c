#include "queue.h"
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <assert.h>

#define THREAD_NUMBER 4//�������߳�����������4�ˣ�������4

sem_t queue_sem;//ͬ����

void *thread_push(void *arg);
void *thread_pop(void *arg);

int main()
{
	LinkQueue que;
	init_Queue(&que);

	/*��ʼ���������ź��� ��ʼֵΪ1 ����ÿһ��ֻ��1���߳̿��Է��� 
	��������Ӧ���û����� �Ƚ������龰 ���ǲ�̫�� �������ź���
	*/
	int res = sem_init(&queue_sem, 0, 1);
	assert(res != -1);

	int i;
	pthread_t threadArr[THREAD_NUMBER];
	for (i = 0; i < THREAD_NUMBER; ++i)
	{
		pthread_create(&threadArr[i], NULL, thread_push, (void *)&que);
	}

	for (i = 0; i < THREAD_NUMBER; ++i)
	{
		pthread_join(threadArr[i], NULL);
	}

	show(&que);

	for (i = 0; i < THREAD_NUMBER; ++i)
	{
		pthread_create(&threadArr[i], NULL, thread_pop, (void *)&que);
	}

	for (i = 0; i < THREAD_NUMBER; ++i)
	{
		pthread_join(threadArr[i], NULL);
	}

	sem_destroy(&queue_sem);

	exit(EXIT_SUCCESS);
}

void *thread_push(void *arg)
{
	printf("start push\n");
	LinkQueue * quePtr = (LinkQueue *)arg;
	int i;
	for (i = 0; i < 20; ++i)
	{
		sem_wait(&queue_sem);
		push_Queue(quePtr, i);
		sem_post(&queue_sem);
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
		sem_wait(&queue_sem);
		res = pop_Queue(quePtr, &tmp);
		sem_post(&queue_sem);
		if (!res)
		{
			break;
		}
		printf("%d ", tmp);
	}
	printf("finish pop\n");
	pthread_exit(NULL);
}
