/*
 * =====================================================================================
 *
 *       Filename:  thread2.c
 *
 *    Description:  一个简单的多线程程序
 *
 *
 *        Version:  1.0
 *        Created:  06/03/2012 12:00:31 AM
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

int run_now = 1;
void *thread_function();

int main(int argc, char *argv[])
{
	int res;
	pthread_t a_thread;

	res = pthread_create(&a_thread, NULL, thread_function, NULL);
	
	int print_count1 = 0;

	while (print_count1++ < 20) {
		if (run_now == 1) {
			printf("1");
			run_now = 2;
		} else {
			sleep(1);
		}
	}
	if (res != 0) {
		perror("Thread creation failed!");
		exit(EXIT_FAILURE);
	}
	printf("Waiting for thread to finish...\n");
	res = pthread_join(a_thread, NULL);
	if (res != 0) {
		perror("Thread join failed!");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined\n");

	return EXIT_SUCCESS;
}

void *thread_function()
{
	int print_count2 = 0;

	while (print_count2++ < 20) {
		if (run_now == 2) {
			printf("2");
			run_now = 1;
		} else {
			sleep(1);
		}
	}
	pthread_exit(0);
}
