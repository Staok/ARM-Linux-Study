/*
 * =====================================================================================
 *
 *       Filename:  fork.c
 *
 *    Description:  wait 函数的简单实例
 *
 *        Version:  1.0
 *        Created:  05/29/2012 08:24:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t 	pid;
	char 	*message;
	int	n;
	int	exit_code;

	printf("Fork program starting\n");
	
	pid = fork();

	switch(pid) {
		case -1:
			perror("Fork failed");
			exit(EXIT_FAILURE);
		case 0:
			message = "This is the child";
			n = 5;
			exit_code = 37;
			break;
		default:
			message = "This is the parent";
			n = 3;
			exit_code = 0;
			break;
	}

	for (; n > 0; n--) {
		puts(message);
		sleep(1);
	}
	
	if (pid != 0) {
		int stat_val;
		pid_t child_pid;

		child_pid = wait(&stat_val);

		printf("Child has finished: PID = %d\n", child_pid);
		if (WIFEXITED(stat_val)) {	// 若子进程正常结束，该宏返回非0值，反之返回0
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
		} else {
			printf("Child terminated abnormally\n");
		}
	}

	return EXIT_SUCCESS;
}


