#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

/*
��ͨ��
��ʽ����
*/
typedef struct QNode
{
	int data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct LinkQueue
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;


void init_Queue(LinkQueue *q);//��ʼ������
void push_Queue(LinkQueue *q, int e);//��β���
int pop_Queue(LinkQueue *q, int *e);//��ͷ����
int is_Empty(LinkQueue *q);
void show(LinkQueue *q);


#endif /* QUEUE_H_ */
