#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#define SERVPORT 3333 /*port */
#define BACKLOG 10 /* max client */

int main()
{
	int sockfd,client_fd; 
	struct sockaddr_in my_addr; /* loacl */
	struct sockaddr_in remote_addr; 
	int sin_size;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket fail！"); exit(1);
	}
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(SERVPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero),8); 

	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind error！");
		exit(1);
	}
	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen error！");
		exit(1);
	}
	while(1) {
		sin_size = sizeof(struct sockaddr_in);
		if ((client_fd = accept(sockfd, (struct sockaddr *)&remote_addr, &sin_size)) == -1) {
			perror("accept error");
			continue;
		}
		printf("REC FROM： %s\n",inet_ntoa(remote_addr.sin_addr));

		if (fork() == 0) {
			if (send(client_fd, "Make Your idea Real! \n", 26, 0) == -1)
				perror("send error！");
			close(client_fd);
			exit(0);
		}else
            close(client_fd);
	}
}
