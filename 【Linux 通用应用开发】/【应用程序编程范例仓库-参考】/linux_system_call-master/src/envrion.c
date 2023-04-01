/*
 * =====================================================================================
 *
 *       Filename:  envrion.c
 *
 *    Description:  getenv 函数和 putenv 函数的使用
 *
 *        Version:  1.0
 *        Created:  05/27/2012 09:44:52 AM
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
	char *var, *value;

	if (argc == 1 || argc > 3) {
		fprintf(stderr, "Usage: environ var [value]\n");
		exit(EXIT_FAILURE);
	}

	var = argv[1];
	value = getenv(var);
	if (value) {
		printf("Vairable %s has value %s\n", var, value);	
	} else {
		printf ("vairable %s has no value\n", var);
	}

	if (argc == 3) {
		char *string;
		value = argv[2];
		string = malloc(strlen(var) + strlen(value) + 2);
		if (!string) {	
			fprintf (stderr, "Out of memory\n");
			exit(EXIT_FAILURE);
		}
		strcpy(string, var);
		strcat(string, "=");
		strcat(string, value);
		printf("Calling putenv with: %s\n", string);
		if (putenv(string) != 0) {
			fprintf(stderr, "Putenv failed\n");
			free(string);
			exit(EXIT_FAILURE);
		}
		value = getenv(var);
		if (value) {
			printf("New value of %s is %s\n", var, value);
		} else {
			printf("New value of %s is null?\n", var);
		}
		free(string);
	}

	return EXIT_SUCCESS;
}


