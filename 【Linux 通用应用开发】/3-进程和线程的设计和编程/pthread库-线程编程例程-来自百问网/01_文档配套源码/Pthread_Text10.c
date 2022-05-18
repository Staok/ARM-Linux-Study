#define _GNU_SOURCE 
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutex;

int Num = 0;

void *fun1(void *arg)
{
	pthread_mutex_lock(&mutex);
	while(Num < 3){
		Num++;
		printf("%s:Num = %d\n",__FUNCTION__,Num);
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

void *fun2(void *arg)
{
	pthread_mutex_lock(&mutex);
	while(Num > -3){
		Num--;
		printf("%s:Num = %d\n",__FUNCTION__,Num);
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main()
{
	int ret;
	pthread_t tid1,tid2;
	ret = pthread_mutex_init(&mutex,NULL);
	if(ret != 0){
		perror("pthread_mutex_init");
		return -1;
	}
	ret = pthread_create(&tid1,NULL,fun1,NULL);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	ret = pthread_create(&tid2,NULL,fun2,NULL);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}
