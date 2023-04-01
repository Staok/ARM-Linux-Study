/*
 * =====================================================================================
 *
 *       Filename:  lock.c
 *
 *    Description:  创建锁文件
 *
 *        Version:  1.0
 *        Created:  05/27/2012 04:28:59 PM
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
#include <fcntl.h>
#include <errno.h>

const char * lock_file = "/tmp/LCK.test";

int main(int argc, char *argv[])
{
	int file_desc;
	int tries = 10;

	while (tries--) {
		file_desc = open(lock_file, O_RDWR | O_CREAT | O_EXCL, 0444);
		if (file_desc == -1) {
			printf ("%d - Lock already present\n", getpid());
			sleep(3);
		} else {
			printf ("%d - I have exclusive access\n", getpid());
			sleep(1);
			(void)close(file_desc);
			(void)unlink(lock_file);
			sleep(2);
		}
	}

	return EXIT_SUCCESS;
}


