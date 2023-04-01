/*
 * =====================================================================================
 *
 *       Filename:  myshell.c
 *
 *    Description:  shell 的一个很简单的实现
 *
 *        Version:  1.0
 *        Created:  05/30/2012 09:43:52 AM
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
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define NORMAL		0	// 一般的命令
#define OUT_REDIRECT	1	// 输出重定向v
#define IN_REDIRECT	2	// 输入重定向
#define HAVE_PIPE	3	// 命令中有管道

void print_prompt();								// 打印提示符
void get_input(char *);							// 得到输入的命令
void explain_input(char *buf, int *argcount, char arglist[100][256]);		// 对输入命令进行解析
void do_cmd(int argcount, char arglist[100][256]);				// 执行命令
int  find_command(char *);							// 查找命令中的可执行程序

int main(int argc, char *argv[])
{
	int  i;
	int  argcount = 0;
	char arglist[100][256];
	char **arg = NULL;
	char *buf = NULL;

	buf = (char *)malloc(256);
	if (buf == NULL) {
		perror("malloc failed!\n");
		exit(EXIT_FAILURE);
	}

	while (1) {
		// 将buf指向的空间清0
		memset(buf, 0, 256);
		print_prompt();
		get_input(buf);
		
		// 如果输入 exit 或者 logout 则退出本程序
		if (strcmp(buf, "exit\n") == 0 || strcmp(buf, "logout\n") == 0) {
			break;
		}
		for (i = 0; i < 100; i++) {
			arglist[i][0] = '\0';
		}
		argcount = 0;
		explain_input(buf, &argcount, arglist);
		do_cmd(argcount, arglist);
	}

	if (buf != NULL) {
		free(buf);
		buf = NULL;
	}

	return EXIT_SUCCESS;
}

void print_prompt()
{
	printf("myshell$$ ");
}

// 获取用户输入
void get_input(char *buf)
{
	int len = 0;
	int ch;

	while (ch = getchar(), len < 256 && ch != '\n') {
		buf[len++] = ch;
	}

	if (len == 256) { 	// 输入的命令过长则退出
		printf("Command is too long!\n");
		exit(EXIT_FAILURE);
	}
	
	buf[len++] = '\n';
	buf[len] = '\0';
}

// 解析 buf 中的命令，将结果存入 arglist 中，命令以回车符 \n 结尾
void explain_input(char *buf, int *argcount, char arglist[100][256])
{
	char	*p = buf;
	char	*q = buf;
	int number = 0;

	while (1) {
		if (p[0] == '\n') {
			break;
		}
		if (p[0] == ' ') {
			p++;
		} else {
			q = p;
			number = 0;
			while ((q[0] != ' ') && (q[0] != '\n')) {
				number++;
				q++;
			}
			strncpy(arglist[*argcount], p, number + 1);
			arglist[*argcount][number] = '\0';
			*argcount = *argcount + 1;
			p = q;
		}
	}
}

void do_cmd(int argcount, char arglist[100][256])
{
	int	flag = 0;
	int	how  = 0;		// 用于标示命令中是否有　＞　＜　｜
	int 	background = 0;		// 用于标示命令中是否有后台运行指示符　＆
	int	status;
	int	i;
	int	fd;
	char	*arg[argcount + 1];
	char	*argnext[argcount + 1];
	char	*file;
	pid_t	pid;
	
	// 取出命令字符串
	for (i = 0; i < argcount; i++) {
		arg[i] = (char *)arglist[i];
	}
	arg[argcount] = NULL;

	// 查看命令行是否有后台运行符＆
	for (i = 0; i < argcount; i++) {
		if (strncmp(arg[i], "&", 1) == 0) {
			if (i == argcount - 1) {
				background = 1;
				arg[argcount - 1] = NULL;
				break;
			} else {
				printf("Wrong command!\n");
				return;
			}
		}
	}
	for (i = 0; arg[i] != NULL; i++) {
		if (strcmp(arg[i], ">") == 0) {
			flag++;
			how = OUT_REDIRECT;
			if (arg[i+1] == NULL) {
				flag++;
			}
		}
		if (strcmp(arg[i], "<") == 0) {
			flag++;
			how = IN_REDIRECT;
			if (i == 0)
			{
				flag++;
			}
		}
		if (strcmp(arg[i], "|") == 0) {
			flag++;
			how = HAVE_PIPE;
			if (arg[i+1] == NULL) {
				flag++;
			}
			if (i == 0) {
				flag++;
			}
		}
	}

	// flag 大于 1 则说明程序中含有多个 < > | 命令，本程序不支持该种用法
	if (flag > 1) {
		printf("Worng command!\n");
		return;
	}

	// 命令只含有一个 > 输出重定向符号
	if (how == OUT_REDIRECT) {
		for (i = 0; arg[i] != NULL; i++) {
			if (strcmp(arg[i], ">") == 0) {
				file = arg[i+1];
				arg[i] = NULL;
			}
		}
	}

	// 命令只含有一个 < 输入重定向符号
	if (how == OUT_REDIRECT) {
		for (i = 0; arg[i] != NULL; i++)
		{
			if (strcmp(arg[i], "<") == 0)
			{
				file = arg[i+1];
				arg[i] = NULL;
			}
		}
	}
	// 命令只含有一个 | 管道符号
	if (how == OUT_REDIRECT) {
		for (i = 0; arg[i] != NULL; i++) {
			if (strcmp(arg[i], "|") == 0) {
				arg[i] = NULL;
				int j;
				// 把管道符号后面的可执行命令部分存入 argnext 中
				for (j = i + 1; arg[j] != NULL; i++) {
					argnext[j-i-1] = arg[j];
				}
				argnext[j-i-1] = arg[j];
				break;
			}
		}
	}

	if ((pid = fork()) < 0) {
		printf("Fork error!\n");
		return;
	}

	switch (how) {
		// 输入的命令不含 < > |
		case NORMAL:
			if (pid == 0) {
				if (!(find_command(arg[0]))) {
					printf("%s : command not found!\n", arg[0]);
					exit(EXIT_SUCCESS);
				}
				execvp(arg[0], arg);
				exit(EXIT_SUCCESS);
			}
			break;
		// 含有输出重定向符
		case OUT_REDIRECT:
			if (pid == 0) {
				if (!(find_command(arg[0]))) {
					printf("%s : command not found!\n", arg[0]);
					exit(EXIT_SUCCESS);
				}
				fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
				dup2(fd, 1);
				execvp(arg[0], arg);
				exit(EXIT_SUCCESS);
			}

			break;
		// 含有输入重定向符
		case IN_REDIRECT:
			if (pid == 0) {
				if (!(find_command(arg[0]))) {
					printf("%s : command not found!\n", arg[0]);
					exit(EXIT_SUCCESS);
				}
				fd = open(file, O_RDONLY);
				execvp(arg[0], arg);
				exit(EXIT_SUCCESS);
			}
			break;
		// 命令中有管道
		case HAVE_PIPE:
			if(pid == 0) {
				int pid2;
				int status2;
				int fd2;

				if ((pid2 = fork()) < 0) {
					printf("fork2 error.\n");
					return;
				} else if (pid2 == 0) {
					if (!(find_command(arg[0]))) {
						printf("%s : command not found!\n", arg[0]);
						exit(EXIT_SUCCESS);
					}
					fd2 = open("/tmp/youdonotknowfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
					dup2(fd2, 1);
					execvp(arg[0], arg);
					exit(EXIT_SUCCESS);
				}
				if (waitpid(pid2, &status2, 0) == -1) {
					printf("Wait for child process error.\n");
				}
				if (!(find_command(argnext[0]))) {
					printf("%s : command not found!\n", arg[0]);
					exit(EXIT_SUCCESS);
				}
				fd2 = open("/tmp/youdonotknowfile", O_RDONLY);
				dup2(fd2, 0);
				execvp(argnext[0], argnext);

				if (remove("/tmp/youdonotknowfile")) {
					printf("Remove file error.\n");
				}
				exit(EXIT_SUCCESS);
			}
			break;
		default:
			break;

	}

	// 若命令中有 & ，则父进程直接返回
	if (background == 1) {
		printf("[process id %d]\n", pid);
		return;
	}

	// 父进程等待子进程结束
	if (waitpid(pid, &status, 0) == -1) {
		printf("wait for chile process error.\n");
	}

}

// 查找进程中的可执行程序
int find_command(char * command)
{
	DIR		* dp;
	struct dirent	* dirp;
	char		* path[] = { "./", "/bin", "/usr/bin", NULL };

	// 使得当前目录下程序可以执行
	if (strncmp(command, "./", 2) == 0) {
		command += 2;
	}

	// 分别在当前目录，以及 /bin ，/usr/bin 查找程序
	int i = 0;

	while (path[i] != NULL) {
		if ((dp = opendir(path[i])) == NULL) {
			printf("Cannot open /bin \n");
		}
		while ((dirp = readdir(dp)) != NULL) {
			if (strcmp(dirp->d_name, command) == 0) {
				closedir(dp);
				return 1;
			}
		}
		closedir(dp);
		i++;
	}

	return 0;
}
