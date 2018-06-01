#include "sem.h"

void sem_get()
{
	semid = semget((key_t)1234, 1, 0664);
	if(semid == -1) // 获取失败, 内核中并没有这个信号量集
	{
		semid = semget((key_t)1234, 1, 0664 | IPC_CREAT);
		assert(semid != -1);

		//本次获取是创建信号量集，所以必须初始化

		union semun v;
		v.val = 0;
		if(-1 == semctl(semid, 0, SETVAL, v))
		{
			perror("error");
			exit(0);
		}
	}
}
void sem_p()
{
	struct sembuf buff;
	buff.sem_num = 0;
	buff.sem_op = -1;
	buff.sem_flg = SEM_UNDO;

	if(-1 == semop(semid, &buff, 1))
	{
		perror("p error");
		exit(0);
	}
}
void sem_v()
{
	struct sembuf buff;
	buff.sem_num = 0;
	buff.sem_op = 1;
	buff.sem_flg = SEM_UNDO;

	if(-1 == semop(semid, &buff, 1))
	{
		perror("p error");
		exit(0);
	}
}
void sem_del()
{
	if(-1 == semctl(semid, 0, IPC_RMID))
	{
		perror("del error");
		exit(0);
	}
}
