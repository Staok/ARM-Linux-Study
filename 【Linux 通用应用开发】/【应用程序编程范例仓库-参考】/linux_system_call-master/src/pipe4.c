/*
 * =====================================================================================
 *
 *       Filename:  pipe4.c
 *
 *    Description:  管道操作
 *
 *        Version:  1.0
 *        Created:  08/29/2012 09:38:08 PM
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

int main(int argc, char *argv[])
{
	int data_processed;
	char buffer[BUFSIZ + 1];
	int file_descriptor;

	memset(buffer, '\0', sizeof(buffer));

	sscanf(argv[1], "%d", &file_descriptor);
	data_processed = read(file_descriptor, buffer, BUFSIZ);

	printf("%d -read %d bytes: %s\n", getpid(), data_processed, buffer);

	return EXIT_SUCCESS;
}


