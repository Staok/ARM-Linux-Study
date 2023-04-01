/*
 * =====================================================================================
 *
 *       Filename:  find_file.c
 *
 *    Description:  在目录中查找指定类型的文件
 *
 *        Version:  1.0
 *        Created:  2013年07月18日 16时14分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <linux/errno.h>

#include "find_file.h"

// 待寻找类型的文件数量
int file_count;

int main(int argc, char *argv[])
{
	// 这里简单处理参数，高级的处理自己百度 getopt 系列函数用法
	if (argc != 4 || strcmp(argv[2], "-t") != 0) {
		print_useage(argv[0]);
	} else {
		find_directory(argv[1], process_file, argv[3]);
		printf("Find Total : %d\n", file_count);
	}

	return EXIT_SUCCESS;
}

// 对文件的处理函数
void process_file(char *filename, char *type)
{
	char *pname = filename;
	int name_length = strlen(filename);
	char curr_dir[PATH_MAX];

	// 指针移动到文件名尾部
	while (*pname != '\0') {
		pname++;
	}

	// 文件名移动到文件名中最后一个 . 处
	while (*pname != '.' && name_length--) {
		pname--;
	}
	
	if (strcmp(type, pname+1) == 0) {
		if (getcwd(curr_dir, PATH_MAX) == NULL) {
			perror("getcwd Error");
			return;
		}
		file_count++;
		printf("%s%s\n", curr_dir, filename);
	}
}

// 递归遍历一个目录
void find_directory(char *dir_name, void (*process_file)(char *, char *), char *type)
{
	DIR *dir;
	struct dirent *entry;
	struct stat statbuf;

	if ((dir = opendir(dir_name)) == NULL) {
		perror("Open Directory Error");
		return;
	}

	// 改变当前工作目录
	chdir(dir_name);
	while ((entry = readdir(dir)) != NULL) {
		if (lstat(entry->d_name, &statbuf) == -1) {
			perror(entry->d_name);
			return;
		}
		// 如果目标是一个目录
		if (S_ISDIR(statbuf.st_mode)) {
			// 注意忽略掉特殊目录 . 和 ..
			if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) {
				continue;
			}
			// 对子目录递归查找
			find_directory(entry->d_name, process_file, type);
		} else { // 如果是文件
			process_file(entry->d_name, type);
		}
	}

	// 返回上一层目录
	chdir("..");

	// 释放资源
	closedir(dir);
}

// 打印使用方法
void print_useage(char *filename)
{
	printf("Useage：\n");
	printf("\t%s path -t types\n", filename);
}
