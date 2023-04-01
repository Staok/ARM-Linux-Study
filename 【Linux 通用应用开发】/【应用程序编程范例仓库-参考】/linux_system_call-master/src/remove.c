/*
 * =====================================================================================
 *
 *       Filename:  remove.c
 *
 *    Description:  文件删除实例
 *
 *        Version:  1.0
 *        Created:  2012年05月20日 22时24分49秒
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

int main(int argc, char *argv[])
{
	int  flag;
	char s[] = "test.txt";

	flag = remove(s);
	if (0 == flag) {
		printf("Delete file successfully!\n");
	} else {
		printf("Delete file failed!\n");
	}
		
	return EXIT_SUCCESS;
}


