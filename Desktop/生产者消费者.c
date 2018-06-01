/*======================================================================
        	Copyright (C) 2007-2017 图论科技有限公司    
        	All rights reserved  
        	禁止侵权，违者必究

        	filename : main_thread.c 

        	description : 
        	主线程作为生产者，从键盘获取数据写入共享缓冲区，子线程作
			为消费者，从共享缓冲区读数据，并打印。

        	created by 苏锋 QQ: 414715129
            2017/11/16 17:41:28
            
        	图论科技网站主页：http://www.tulun1024.com 
            图论科技微信公众号：tulun2007
			
======================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

sem_t read_sem;//控制消费者是否可以打印，初始值为0，代表数据没有被产生之前，消费者不能使用数据。由生产者产生完数据进行v操作。
sem_t write_sem;//控制生产者是否可以进行新数据的加入，初值为1，代表生产者可以先产生数据，由消费者进行v操作。

void* work_thread(void * arg)
{
    char * s = (char*)arg;

    while( 1 )
    {
        sem_wait(&read_sem);//对读的信号量进行p操作
        if ( strncmp(s,"end",3) == 0 )
        {
            break;
        }

        printf("read:%s\n",s);
        sem_post(&write_sem);//对写的信号量进行v操作
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t id;
    char shared_buff[128] = {0};

    sem_init(&read_sem,0,0);//信号量初始化
    sem_init(&write_sem,0,1);

    int res = pthread_create(&id,NULL,work_thread,(void*)shared_buff);
    assert( res == 0 );
    
    while( 1 )
    {
        char tmp_buff[128] = {0};

        printf("input data:\n");
        fgets(tmp_buff,128,stdin);

        sem_wait(&write_sem);//对控制写的信号量进行p操作
        strcpy(shared_buff,tmp_buff);
        sem_post(&read_sem);//对读的信号量进行v操作

        if ( strncmp(tmp_buff,"end",3) == 0 )
        {
            break;
        }

    }

    pthread_join(id,NULL);
    sem_destroy(&read_sem);//销毁信号量
    sem_destroy(&write_sem);
    exit(0);
}
