/*
 * =====================================================================================
 *
 *       Filename:  write.c
 *
 *    Description:  文件读写测试
 *
 *        Version:  1.0
 *        Created:  2012年05月20日 21时40分34秒
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int  fd, size;
	char s[] = "This is a linux programe!\n", buffer[50];

	fd = open("temp.txt", O_RDWR | O_CREAT | O_EXCL, S_IRWXU);
	write(fd, s, sizeof(s));
	close(fd);

	fd = open("temp.txt", O_RDONLY);
	size = read(fd, buffer, sizeof(buffer));
	close(fd);
	printf("%s", buffer);

	return EXIT_SUCCESS;
}
