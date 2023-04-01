/*
 * =====================================================================================
 *
 *       Filename:  daemon.c
 *
 *    Description:  守护进程的建立
 *
 *        Version:  1.0
 *        Created:  05/30/2012 08:05:28 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <time.h>
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>

int init_daemon(void)
{
	int pid;
	int i;

	// 忽略终端 I/O 信号，STOP 信号
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);	// SIGTTOU，SIGTTIN 信号表示终端需要从终端读取
	signal(SIGTSTP, SIG_IGN);	// 终端挂起信号，通常因按下 Ctrl + Z 产生
	signal(SIGHUP,  SIG_IGN);	// 由一个处于非链接状态的终端发送给控制进程，
					// 或者由控制进程在自身结束时发送给每个前台进程
	pid = fork();
	if (pid > 0) {
		exit(EXIT_SUCCESS);	// 结束父进程，使得子进程成为后台进程
	} else {
		if (pid < 0) {
			return EXIT_FAILURE;
		}
	}
	
	// 建立一个新的进程组，在这个新的进程组中，子进程成为这个进程组的首进程，以使该进程脱离所有终端
	setsid();
	
	// 再次建立一个子进程，退出父进程，保证该进程不是进程组长，同时让该进程无法打开一个新的终端
	pid = fork();
	if(pid > 0) {
		exit(EXIT_SUCCESS);
	} else {
		if (pid < 0) {
			return EXIT_FAILURE;
		}
	}

	// 关闭所有从父进程继承的不再需要的文件描述符
	for (i = 0; i < NOFILE; close(i++))	// NOFILE 定义在 sys/param.h ，其值为256
		;
		
	// 改变工作目录，使得进程不与任何文件系统联系
	chdir("/");

	// 将文件屏蔽字设置为0
	umask(0);

	// 忽略 SIGCHLD 信号
	signal(SIGCHLD, SIG_IGN);	// SIGCHLD 信号在子进程暂停或退出时产生

	return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	time_t now;

	init_daemon();
	syslog(LOG_USER | LOG_INFO, "测试守护进程！\n");

	while (1) {
		sleep(8);
		time(&now);
		syslog(LOG_USER | LOG_INFO, "系统时间：\t%s\t\t\n", ctime(&now));
	}

	return EXIT_SUCCESS;
}

