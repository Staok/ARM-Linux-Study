/*
 * =====================================================================================
 *
 *       Filename:  thread4.c
 *
 *    Description:  关于线程互斥量的示例，需要注意的是本示例采用的轮询的方式并不是最好的
 *    		    方式，本示例在此仅作为功能示例，实际工程中应该尽量采用信号量避免轮询
 *
 *        Version:  1.0
 *        Created:  08/29/2012 09:42:09 AM
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
pthread_mutex_t work_mutex;

#define WORK_SIZE 1024
char work_area[WORK_SIZE];
int time_to_exit = 0;

int main(int argc, char *argv[])
{
	int res;
	pthread_t a_thread;
	void *thread_result;
	
	res = pthread_mutex_init(&work_mutex, NULL);
	if (res != 0) {
		perror("Mutex initialization failed!");
		exit(EXIT_FAILURE);
	}
	res = pthread_create(&a_thread, NULL, thread_function, NULL);
	if (res != 0) {
		perror("Thread creation failed!");
		exit(EXIT_FAILURE);
	}
	pthread_mutex_lock(&work_mutex);
	
	printf("Input some text. Enter the 'End' to finish\n");

	while (!time_to_exit) {
		fgets(work_area, WORK_SIZE, stdin);
		pthread_mutex_unlock(&work_mutex);
		while (1) {
			pthread_mutex_lock(&work_mutex);
			if (work_area[0] != '\0') {
				pthread_mutex_unlock(&work_mutex);
				sleep(1);
			} else {
				break;
			}
		}
	}

	pthread_mutex_unlock(&work_mutex);
	printf("\nWaiting for thread to finish...\n");
	res = pthread_join(a_thread, &thread_result);
	if (res != 0) {
		perror("Thread join failed!");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined!\n");
	pthread_mutex_destroy(&work_mutex);

	return EXIT_SUCCESS;
}

void *thread_function(void *arg)
{
	sleep(1);
	pthread_mutex_lock(&work_mutex);
	while (strncmp("end", work_area, 3) != 0) {
		printf("You input %d characters.\n", strlen(work_area) - 1);
		work_area[0] = '\0';
		pthread_mutex_unlock(&work_mutex);
		sleep(1);
		pthread_mutex_lock(&work_mutex);
		while (work_area[0] == '\0') {
			pthread_mutex_unlock(&work_mutex);
			sleep(1);
			pthread_mutex_lock(&work_mutex);
		}
	}
	time_to_exit = 1;
	work_area[0] = '\0';
	pthread_mutex_unlock(&work_mutex);
	pthread_exit(0);
}

