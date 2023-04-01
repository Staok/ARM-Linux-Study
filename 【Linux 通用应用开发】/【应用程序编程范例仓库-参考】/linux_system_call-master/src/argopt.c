/*
 * =====================================================================================
 *
 *       Filename:  argopt.c
 *
 *    Description:  getopt 函数的使用
 *
 *        Version:  1.0
 *        Created:  05/27/2012 09:21:38 AM
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

int main(int argc, char *argv[])
{
	int opt;

	while ((opt = getopt(argc, argv, ":if:lr")) != -1) {
		switch (opt) {
			case 'i':
			case 'l':
			case 'r':
				printf("Option: %c\n", opt);
				break;
			case 'f':
				printf("Filename: %s\n", optarg);
				break;
			case ':':
				printf ("Option needs a value\n");
				break;
			case '?':
				printf ("Unknow option: %c\n", optopt);
				break;
		}
	}

	for (; optind < argc; optind++) {
		printf ("Argument: %s\n", argv[optind]);
	}

	return EXIT_SUCCESS;
}

