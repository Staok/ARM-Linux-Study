/*
 * =====================================================================================
 *
 *       Filename:  thread3.c
 *
 *    Description:  信号量同步的多线程程序
 *
 *        Version:  1.0
 *        Created:  06/03/2012 02:22:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_function(void *arg);
sem_t bin_sem;

#define WORK_SIZE 1024
char work_area[WORK_SIZE];

int main(int argc, char *argv[])
{
	int		res;
	pthread_t	a_thread;
	void 		*thread_result;

	res = sem_init(&bin_sem, 0, 0);
	if (res != 0) {
		perror("Semaphore initialization failed!");
		exit(EXIT_FAILURE);
	}
	res = pthread_create(&a_thread, NULL, thread_function, NULL);
	if (res != 0) {
		perror("Thread creation failed!");
		exit(EXIT_FAILURE);
	}

	printf("\nInput some text. Enter 'end' to finish\n");
	while (strncmp("end", work_area, 3) != 0) {
		fgets(work_area, WORK_SIZE, stdin);
		sem_post(&bin_sem);
	}

	printf("Waiting for thread to finish...\n");
	res = pthread_join(a_thread, &thread_result);
	if (res != 0) {
		perror("Thread join failed!");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined\n");
	sem_destroy(&bin_sem);

	return EXIT_SUCCESS;
}

void *thread_function(void *arg)
{
	sem_wait(&bin_sem);
	while (strncmp("end", work_area, 3) != 0) {
		printf("You input %d characters\n", strlen(work_area) -1);
		sem_wait(&bin_sem);
	}

	pthread_exit(NULL);
}

