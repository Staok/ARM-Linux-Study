#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void *fun1(void *arg)
{
	static int tmp = 0;//必须要static修饰，否则pthread_join无法获取到正确值
	//int tmp = 0;
	tmp = *(int *)arg;
	tmp+=100;
	printf("%s:Addr = %p tmp = %d\n",__FUNCTION__,&tmp,tmp);
	pthread_exit((void *)&tmp);
}


int main()
{

	pthread_t tid1;
	int a = 50;
	void *Tmp = NULL;
	int ret = pthread_create(&tid1,NULL,fun1,(void *)&a);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	pthread_join(tid1,&Tmp);
	printf("%s:Addr = %p Val = %d\n",__FUNCTION__,Tmp,*(int *)Tmp);
	return 0;
}
