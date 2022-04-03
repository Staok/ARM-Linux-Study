#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

static char g_buf[1000];
static sem_t g_sem;
static void *my_thread_func (void *data)
{
	while (1)
	{
		//sleep(1);
		/* 等待通知 */
		//while (g_hasData == 0);
		sem_wait(&g_sem);

		/* 打印 */
		printf("recv: %s\n", g_buf);
	}

	return NULL;
}


int main(int argc, char **argv)
{
	pthread_t tid;
	int ret;

	sem_init(&g_sem, 0, 0);
	
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
		fgets(g_buf, 1000, stdin);

		/* 通知接收线程 */
		sem_post(&g_sem);
	}
	return 0;
}

