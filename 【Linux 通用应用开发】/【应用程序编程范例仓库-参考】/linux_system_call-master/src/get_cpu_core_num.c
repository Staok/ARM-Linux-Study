/*
 * =====================================================================================
 *
 *       Filename:  get_cpu_core_num.c
 *
 *    Description:  获取CPU可用核数并绑定某核运行
 *
 *        Version:  1.0
 *        Created:  2013年08月09日 13时01分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#define _GNU_SOURCE 

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <sys/sysinfo.h>

int main(int argc, char *argv[])
{
	int cpu_core_num = get_nprocs();

	printf("CPU has %d core\n", cpu_core_num);
	
	cpu_set_t mask;
	cpu_set_t get;

	int myid, i;
	for (myid = 0; myid < cpu_core_num; myid++) {
		CPU_ZERO(&mask);
		CPU_SET(myid, &mask);
		if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
			printf("warning: could not set CPU affinity, continuing\n");
		}

		CPU_ZERO(&get);
		if (sched_getaffinity(0, sizeof(get), &get) == -1) {
			printf("warning: cound not get cpu affinity\n");
		}
		for (i = 0; i < cpu_core_num; i++) {
			if (CPU_ISSET(i, &get)) {
				printf("this process %d is running processor : %d\n",getpid(), i);
			}
		}
	}

	return EXIT_SUCCESS;
}

