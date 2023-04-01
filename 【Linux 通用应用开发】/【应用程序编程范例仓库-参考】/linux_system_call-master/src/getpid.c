/*
 * =====================================================================================
 *
 *       Filename:  getpid.c
 *
 *    Description:  getpid函数测试
 *
 *        Version:  1.0
 *        Created:  2012年05月21日 15时34分09秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf("Current Process ID: %d\n", getpid());
	printf("Parent Process ID: %d\n", getppid());

	return EXIT_SUCCESS;
}


