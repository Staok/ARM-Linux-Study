/*
 * =====================================================================================
 *
 *       Filename:  createthread.c
 *
 *    Description:  多线程简单实例
 *
 *        Version:  1.0
 *        Created:  06/01/2012 06:15:23 PM
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
#include <pthread.h>

int * thread(void * arg)
{
	pthread_t newthid;

	newthid = pthread_self();
	printf("This is a new thread, thread ID = %u\n", newthid);

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t thid;
	
	printf("Main thread, ID is %u\n", pthread_self());

	if (pthread_create(&thid, NULL, (void *)thread, NULL) != 0) {
		printf("Thread creation failed!\n");
		exit(EXIT_FAILURE);
	}

	sleep(1);

	return EXIT_SUCCESS;
}

