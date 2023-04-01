/*
 * =====================================================================================
 *
 *       Filename:  simple_write.c
 *
 *    Description:  write 对标准输出和标准错误的操作
 *
 *        Version:  1.0
 *        Created:  05/25/2012 01:17:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if ((write(1, "Here is some data\n", 18)) != 18) {
		write(2, "A write error has occurred on file descriptor 1\n", 48);
	}

	return EXIT_SUCCESS;
}


