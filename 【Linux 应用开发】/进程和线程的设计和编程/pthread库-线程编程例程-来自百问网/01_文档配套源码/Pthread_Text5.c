#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

struct Stu{
	int Id;
	char Name[32];
	float Mark;
};

void *fun1(void *arg)
{
	struct Stu *tmp = (struct Stu *)arg;
	printf("%s:Id = %d Name = %s Mark = %.2f\n",__FUNCTION__,tmp->Id,tmp->Name,tmp->Mark);
	
}

int main()
{

	pthread_t tid1,tid2;
	struct Stu stu;
	stu.Id = 10000;
	strcpy(stu.Name,"ZhangSan");
	stu.Mark = 94.6;

	int ret = pthread_create(&tid1,NULL,fun1,(void *)&stu);
	if(ret != 0){
		perror("pthread_create");
		return -1;
	}
	printf("%s:Id = %d Name = %s Mark = %.2f\n",__FUNCTION__,stu.Id,stu.Name,stu.Mark);
	sleep(1);
	return 0;
}
