/*
 * =====================================================================================
 *
 *       Filename:  popen1.c
 *
 *    Description:  管道的简单示例
 *
 *        Version:  1.0
 *        Created:  08/29/2012 06:43:26 PM
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
	FILE *read_fp;
	char buffer[BUFSIZ + 1];
	int chars_read;

	memset(buffer, '\0', sizeof(buffer));
	read_fp = popen("uname -a", "r");
	if (read_fp != NULL) {
		chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
		if (chars_read > 0) {
			printf("Output was:\n%s\n", buffer);
		}
		pclose(read_fp);
		exit(EXIT_SUCCESS);
	}

	exit(EXIT_FAILURE);
}

