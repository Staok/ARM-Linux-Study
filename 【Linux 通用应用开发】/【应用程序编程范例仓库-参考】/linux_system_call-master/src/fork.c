/*
 * =====================================================================================
 *
 *       Filename:  fork.c
 *
 *    Description:  fork 函数的简单实例
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
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	pid_t 	pid;
	char 	*message;
	int	n;

	printf("Fork program starting\n");
	
	pid = fork();

	switch(pid) {
		case -1:
			perror("Fork failed");
			exit(EXIT_FAILURE);
		case 0:
			message = "This is the child";
			n = 5;
			break;
		default:
			message = "This is the parent";
			n = 6;
			break;
	}

	for (; n > 0; n--) {
		puts(message);
		sleep(1);
	}

	return EXIT_SUCCESS;
}


