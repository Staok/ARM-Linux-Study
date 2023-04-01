/*
 * =====================================================================================
 *
 *       Filename:  alarm.c
 *
 *    Description:  模拟闹钟
 *
 *
 *        Version:  1.0
 *        Created:  05/29/2012 09:37:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int alarm_fired = 0;

void ding(int sig)
{
	alarm_fired = 1;
}

int main(int argc, char *argv[])
{
	pid_t pid;

	printf("Alarm application starting\n");

	pid = fork();

	switch(pid) {
		case -1:
			perror("Fork failed!\n");
		case 0:
			sleep(5);
			kill(getppid(), SIGALRM);
			exit(EXIT_SUCCESS);
	}

	printf("Waiting for alarm to go off\n");

	(void) signal(SIGALRM, ding);

	pause();

	if (alarm_fired) {
		printf("Ding!\n");
	}
	printf("Done.\n");

	return EXIT_SUCCESS;
}

