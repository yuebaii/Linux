#include "queue.h"

/*
��ʼ��
Ϊ���й���һ��ͷ���
��front��rear��ָ�����ͷ���
*/
void init_Queue(LinkQueue *q)
{
	q->front = q->rear = (QNode *)malloc(sizeof(QNode));
	q->front->next = NULL;
}

/*
��ͨ����Ӳ���
*/
void push_Queue(LinkQueue *q, int e)
{
	QueuePtr newNode = (QueuePtr)malloc(sizeof(QNode));
	newNode->data = e;
	newNode->next = NULL;
	q->rear->next = newNode;
	q->rear = newNode;
}

/*
cas����Ӳ���
����ͨ����Ӳ���һ��
�½��ڵ��
Ҫ���½ڵ���ڶ�βʱ��Ҫ����cas����
��Ϊ�ٷ��ĵ���The definition given in the Intel documentation allows only for the use of the types int, long, long long as well as their unsigned counterparts
ֻ���� int, long, long long
����Ҫ��ָ������ QueuePtr ��� long
��long����һ��ԭ����ǣ�����32λ��64λ�Ĳ��� long��32λ��4�ֽ� 64λ��8�ֽ�
*/
void cas_push(LinkQueue *q, int e)
{
	QueuePtr newNode = (QueuePtr)malloc(sizeof(QNode));
	newNode->data = e;
	newNode->next = NULL;

	QueuePtr tmp;
	do
	{
		tmp = q->rear;
	}while (!__sync_bool_compare_and_swap((long *)(&(tmp->next)), NULL, (long)newNode));

	q->rear = newNode;
}

/*
��ǰ���п��� q->front == q->rear
���������ӻ����ӳ��ӵĲ��� �����������һ��Ԫ��ʱ, q->rear��Ҫָ�� q->front
�Ұ���һ��ʡ�� ��ʱû�з�����ʲô������
�����Ҹĳ��� q->front->next == NULL
*/
int is_Empty(LinkQueue *q)
{
	if (q->front->next == NULL)
	{
		return(1);
	}
	return(0);
}

/*
��ͨ�ĳ��Ӳ���
����ӿ� ����0 Ҳ����false
e��Ϊ����Ԫ�صĻ���
*/
int pop_Queue(LinkQueue *q, int *e)
{
	if (is_Empty(q))
	{
		return(0);
	}
	QueuePtr tmp;
	tmp = q->front->next;
	q->front->next = tmp->next;

	*e = tmp->data;
	free(tmp);
	return(1);
}

/*
cas�ĳ��Ӳ���
ÿһ�ζ�Ҫ�ж���������ǲ��ǿ�
Ȼ��ִ��cas�ĳ��Ӳ�����
��1��tmp = q->rear �ѾɵĶ�ͷ������
��2��ִ��ԭ�Ӳ������� �ɵĶ�ͷ �Ƿ���� ���ڵĶ�ͷ tmp == *(&(q->front)) ������ִ�� *(&(q->front)) = tmp->next ����true 
	���򣬼�ִ����һ��ԭ�Ӳ�����ʱ�򣬱���߳��޸��˶��У����¶�βָ��ı��ˣ�����false ,while(!false)�ص���һ������ִ��
*/
int cas_pop(LinkQueue *q, int *e)
{
	QueuePtr tmp;
	do {
		if (is_Empty(q))
		{
			return(0);
		}
        //printf("cas_pop...\n");
		tmp = q->front->next;
	} while (!__sync_bool_compare_and_swap((long *)(&(q->front->next)), (long)tmp, (long)tmp->next));

	*e = tmp->data;
	free(tmp);
	return(1);
}

/*
�������� ��ӡ�����Ԫ�� Ϊ����֤���������Ԫ��
*/
void show(LinkQueue *q)
{
	printf("void show(LinkQueue *q)\n");
	QueuePtr tmp = q->front->next;
	while (tmp)
	{
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}
