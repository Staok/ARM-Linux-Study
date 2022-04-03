#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>

static char g_buf[1000];
static pthread_mutex_t g_tMutex  = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  g_tConVar = PTHREAD_COND_INITIALIZER;

static void *my_thread_func (void *data)
{
	while (1)
	{
		//sleep(1);
		/* 等待通知 */
		//while (g_hasData == 0);
		pthread_mutex_lock(&g_tMutex);
		pthread_cond_wait(&g_tConVar, &g_tMutex);	

		/* 打印 */
		printf("recv: %s\n", g_buf);
		pthread_mutex_unlock(&g_tMutex);
	}

	return NULL;
}


int main(int argc, char **argv)
{
	pthread_t tid;
	int ret;
	char buf[1000];
	
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
		fgets(buf, 1000, stdin);
		pthread_mutex_lock(&g_tMutex);
		memcpy(g_buf, buf, 1000);
		pthread_cond_signal(&g_tConVar); /* 通知接收线程 */
		pthread_mutex_unlock(&g_tMutex);
	}
	return 0;
}

