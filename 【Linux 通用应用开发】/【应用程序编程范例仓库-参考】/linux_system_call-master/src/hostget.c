/*
 * =====================================================================================
 *
 *       Filename:  hostget.c
 *
 *    Description:  gethostname 函数和 uname 函数的实例
 *
 *        Version:  1.0
 *        Created:  05/27/2012 12:54:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[])
{
	char computer[NAME_MAX];
	struct utsname uts;

	if (gethostname(computer, NAME_MAX-1) != 0 || uname(&uts) < 0) {
		fprintf(stderr, "Could not get host information\n");
		exit(EXIT_FAILURE);
	}

	printf ("Computer host name is %s\n", computer);
	printf ("System is %s on %s hardware\n", uts.sysname, uts.machine);
	printf ("Nodenname is %s\n", uts.nodename);
	printf ("Version is %s, %s\n", uts.release, uts.version);

	return EXIT_SUCCESS;
}


