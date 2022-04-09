#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void *fun(void *arg)
{
	printf("pthread_New = %lu\n",(unsigned long)pthread_self());
}

int main()
{

	pthread_t tid1;
	int ret = pthread_create(&tid1,NULL,fun,NULL);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}

	/*tid_main 为通过pthread_self获取的线程ID，tid_new通过执行pthread_create成功后tid指向的空间*/
	printf("tid_main = %lu tid_new = %lu \n",(unsigned long)pthread_self(),(unsigned long)tid1);
	
	/*因线程执行顺序随机，不加sleep可能导致猪线程先执行，导致进程结束，无法执行到子线程*/
	sleep(1);

	return 0;
}
