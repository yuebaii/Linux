#ifndef __SEM_H
#define __SEM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semid;

union semun
{
	int val;
};

void sem_get(); //创建或者获取信号量
void sem_p();  //P操作
void sem_v();  //V操作
void sem_del(); //删除



#endif
