/*
 * =====================================================================================
 *
 *       Filename:  simple_read.c
 *
 *    Description:  read 调用的实例
 *
 *        Version:  1.0
 *        Created:  05/25/2012 01:27:57 PM
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
	char   buffer[128];
	size_t nread;

	nread = read(0, buffer, 128);
	if (nread == -1) {
		write(2, "A read error has occurred\n", 26);
	}

	if ((write(1, buffer, nread)) != nread) {
		write(2, "A write error has occurred\n", 27);
	}

	return EXIT_SUCCESS;
}


