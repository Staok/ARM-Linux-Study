/*
 * =====================================================================================
 *
 *       Filename:  fwrite.c
 *
 *    Description:  fwrite的实例
 *
 *        Version:  1.0
 *        Created:  2012年05月20日 22时07分01秒
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

#define LENGTH 20

int main(int argc, char *argv[])
{
	FILE *ptr;
	int  i, numread, numwritten;
	char data[LENGTH];

	if ((ptr = fopen("test.txt", "w+")) != NULL) {
		for (i = 0; i < LENGTH; i++) {
			data[i] = 'a' + i;
		}
		numwritten = fwrite(data, sizeof(char), LENGTH, ptr);
		printf("Write %d words.\n", numwritten);
		fclose(ptr);
	} else {
		printf("Open file failed!\n");
	}

	if ((ptr = fopen("test.txt", "r+")) != NULL) {
		numread = fread(data, sizeof(char), LENGTH, ptr);
		printf("%s\n", data);
		printf("Read %d words.\n", numread);
		fclose(ptr);
	} else {
		printf("Read file failed!\n");
	}

	return EXIT_SUCCESS;
}


