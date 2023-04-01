/*
 * =====================================================================================
 *
 *       Filename:  setjmp.c
 *
 *    Description:  setjmp 版 Hello World
 *
 *        Version:  1.0
 *        Created:  05/27/2012 03:46:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

jmp_buf go;

void jmp(void)
{
	longjmp(go, 1);
}

int main(int argc, char *argv[])
{
	if (setjmp(go)) {
		printf("World\n");
	}
	else {
		printf ("Hello ");
		jmp();
	}
	
	return EXIT_SUCCESS;
}


