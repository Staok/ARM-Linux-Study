#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


static void *my_thread_func (void *data)
{
	while (1)
	{
		sleep(1);
	}
}


int main(int argc, char **argv)
{
	pthread_t tid;
	int ret;
	
	/* 1. 创建"接收线程" */
	ret = pthread_create(&tid, NULL, my_thread_func, NULL);
	if (ret)
	{
		printf("pthread_create err!\n");
		return -1;
	}


	/* 2. 主线程读取标准输入, 发给"接收线程" */
	while (1)
	{
		sleep(1);
	}
	return 0;
}

