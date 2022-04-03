#define _GNU_SOURCE 
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void *fun1(void *arg)
{
	printf("%s:Pthread Come!\n",__FUNCTION__);
	pthread_exit(NULL);
}

void *fun2(void *arg)
{
	printf("%s:Pthread Come!\n",__FUNCTION__);
	pthread_exit(NULL);
}

void *fun3(void *arg)
{
	printf("%s:Pthread Come!\n",__FUNCTION__);
	pthread_exit(NULL);
}

int main()
{
	int ret;
	pthread_t tid1,tid2,tid3;
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
	ret = pthread_create(&tid3,NULL,fun3,NULL);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	return 0;
}
