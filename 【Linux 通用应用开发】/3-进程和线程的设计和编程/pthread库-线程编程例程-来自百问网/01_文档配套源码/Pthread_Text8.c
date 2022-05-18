#define _GNU_SOURCE 
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void *fun1(void *arg)
{
	printf("Pthread:1 come!\n");
	while(1){
		sleep(1);
	}
}

void *fun2(void *arg)
{
	printf("Pthread:2 come!\n");
	pthread_cancel((pthread_t )(long)arg);
	pthread_exit(NULL);
}

int main()
{
	int ret,i,flag = 0;
	void *Tmp = NULL;
	pthread_t tid[2];
	ret = pthread_create(&tid[0],NULL,fun1,NULL);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	sleep(1);
	ret = pthread_create(&tid[1],NULL,fun2,(void *)tid[0]);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	while(1){
		for(i = 0;i <2;i++){
			if(pthread_tryjoin_np(tid[i],NULL) == 0){
				printf("Pthread : %d exit !\n",i+1);
				flag++;	
			}
		}
		if(flag >= 2) break;
	}
	return 0;
}
