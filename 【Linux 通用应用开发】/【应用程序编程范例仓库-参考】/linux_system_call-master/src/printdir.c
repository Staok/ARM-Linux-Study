/*
 * =====================================================================================
 *
 *       Filename:  printdir.c
 *
 *    Description:  打印用户目录程序
 *
 *        Version:  1.0
 *        Created:  05/25/2012 05:39:21 PM
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
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir, int depth)
{
	DIR 	      *dp;
	struct dirent *entry;
	struct stat    statbuf;

	if ((dp = opendir(dir)) == NULL) { 		// 打开目录并建立目录流
		fprintf(stderr, "Cannot open directory: %s\n", dir);
		exit(EXIT_FAILURE);
	}
	chdir(dir);		// 修改当前工作目录
	while ((entry = readdir(dp)) != NULL)	{  	// 读取目录，再次调用时读取下一个目录项
		lstat(entry->d_name, &statbuf);	// 返回通过文件名查询到的信息
		if (S_ISDIR(statbuf.st_mode))	{  	// 测试是否是目录
			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0 ) {
				continue;
			}
			printf("%*s%s/\n", depth, "", entry->d_name);
			printdir(entry->d_name, depth + 4);		// 如果是目录则递归调用自身
		} else {
			printf("%*s%s\n", depth, "", entry->d_name);
		}
	}
	chdir("..");		// 将工作目录更改到当前目录的上一个目录
	closedir(dp);		// 关闭打开的目录		
}

int main(int argc, char *argv[])
{
	char *topdir = ".";

	if (argc >= 2) {
		topdir = argv[1];
	}

	printf("Directory scan of %s:\n", topdir);
	printdir(topdir, 0);
	printf("done.\n");
	
	return EXIT_SUCCESS;
}

