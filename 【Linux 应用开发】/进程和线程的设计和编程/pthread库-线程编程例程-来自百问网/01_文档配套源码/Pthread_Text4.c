#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void *fun1(void *arg)
{
	while(1){
	
		printf("%s:arg = %d Addr = %p\n",__FUNCTION__,*(int *)arg,arg);
		sleep(1);
	}
}

void *fun2(void *arg)
{
	while(1){
	
		printf("%s:arg = %d Addr = %p\n",__FUNCTION__,(int)(long)arg,arg);
		sleep(1);
	}
}

int main()
{

	pthread_t tid1,tid2;
	int a = 50;
	int ret = pthread_create(&tid1,NULL,fun1,(void *)&a);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	sleep(1);
	ret = pthread_create(&tid2,NULL,fun2,(void *)(long)a);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	while(1){
		a++;
		sleep(1);
		printf("%s:a = %d Add = %p \n",__FUNCTION__,a,&a);
	}
	return 0;
}
