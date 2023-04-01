/*
 * =====================================================================================
 *
 *       Filename:  argopt.c
 *
 *    Description:  getopt_long 函数的使用
 *
 *        Version:  1.0
 *        Created:  05/27/2012 09:38:31 AM
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

#define _GNU_SOURCE
#include <getopt.h>

int main(int argc, char *argv[])
{
	int opt;
	struct option longopts[] = {
		{ "initialize", 0, NULL, 'i' },
		{ "file", 1, NULL, 'f' },
		{ "list", 0, NULL, 'l' },
		{ "restart", 0, NULL, 'r' },
		{ 0, 0, 0, 0 }
	};

	while ((opt = getopt_long(argc, argv, ":if:lr", longopts, NULL)) != -1) {
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

