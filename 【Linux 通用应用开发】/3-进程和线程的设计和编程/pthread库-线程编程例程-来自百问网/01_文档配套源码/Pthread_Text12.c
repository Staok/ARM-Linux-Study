#define _GNU_SOURCE 
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>

sem_t sem1,sem2,sem3;//申请的三个信号量变量

void *fun1(void *arg)
{
	sem_wait(&sem1);//因sem1本身有资源，所以不被阻塞 获取后sem1-1 下次会会阻塞
	printf("%s:Pthread Come!\n",__FUNCTION__);
	sem_post(&sem2);// 使得sem2获取到资源
	pthread_exit(NULL);
}

void *fun2(void *arg)
{
	sem_wait(&sem2);//因sem2在初始化时无资源会被阻塞，直至14行代码执行 不被阻塞 sem2-1 下次会阻塞
	printf("%s:Pthread Come!\n",__FUNCTION__);
	sem_post(&sem3);// 使得sem3获取到资源
	pthread_exit(NULL);
}

void *fun3(void *arg)
{
	sem_wait(&sem3);//因sem3在初始化时无资源会被阻塞，直至22行代码执行 不被阻塞 sem3-1 下次会阻塞
	printf("%s:Pthread Come!\n",__FUNCTION__);
	sem_post(&sem1);// 使得sem1获取到资源
	pthread_exit(NULL);
}

int main()
{
	int ret;
	pthread_t tid1,tid2,tid3;
	ret = sem_init(&sem1,0,1);  //初始化信号量1 并且赋予其资源
	if(ret < 0){
		perror("sem_init");
		return -1;
	}
	ret = sem_init(&sem2,0,0); //初始化信号量2 让其阻塞
	if(ret < 0){
		perror("sem_init");
		return -1;
	}
	ret = sem_init(&sem3,0,0); //初始化信号3 让其阻塞
	if(ret < 0){
		perror("sem_init");
		return -1;
	}
	ret = pthread_create(&tid1,NULL,fun1,NULL);//创建线程1
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	ret = pthread_create(&tid2,NULL,fun2,NULL);//创建线程2
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	ret = pthread_create(&tid3,NULL,fun3,NULL);//创建线程3
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	/*回收线程资源*/
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);

	/*销毁信号量*/
	sem_destroy(&sem1);
	sem_destroy(&sem2);
	sem_destroy(&sem3);

	return 0;
}
