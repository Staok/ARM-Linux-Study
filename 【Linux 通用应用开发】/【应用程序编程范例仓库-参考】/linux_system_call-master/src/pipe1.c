/*
 * =====================================================================================
 *
 *       Filename:  pipe1.c
 *
 *    Description:  pipe 调用的演示1
 *
 *        Version:  1.0
 *        Created:  08/29/2012 09:18:33 PM
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
	int 	data_processed;
	int 	file_pipes[2];
	char 	buffer[BUFSIZ + 1];
	const char some_data[] = "123";
	
	memset(buffer, '\0', sizeof(buffer));

	if (pipe(file_pipes) == 0) {
		data_processed = write(file_pipes[1], some_data, strlen(some_data));
		printf("Write %d bytes\n", data_processed);
		data_processed = read(file_pipes[0], buffer, BUFSIZ);
		printf("Read %d bytes: %s\n", data_processed, buffer);
		
		exit(EXIT_SUCCESS);
	}

	exit(EXIT_FAILURE);
}

