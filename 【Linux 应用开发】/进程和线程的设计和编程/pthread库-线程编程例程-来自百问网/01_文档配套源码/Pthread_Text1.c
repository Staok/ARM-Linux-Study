#include <pthread.h>
#include <stdio.h>

int main()
{
	pthread_t tid = pthread_self();
	printf("tid = %lu\n",(unsigned long)tid);
	return 0;
}
