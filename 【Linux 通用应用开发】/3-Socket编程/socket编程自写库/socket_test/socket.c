#include "socket.h"


#define CLIENT_DEFAULT_AIM_ADDR_STR   "127.0.0.1"

#ifdef WIN_OR_LINUX


/* 记录 server 和 client 的 socket 句柄 的 全局变量 */
SOCKET socket_server_g = 0;
SOCKET socket_client_g[TEST_SERVER_LISTEN_CNT_MAX] = { 0 };

SOCKET win_socket_TCP_server_init(unsigned char autoaddr, 
    const char* ip_str, const unsigned short port, 
    const unsigned short listen_cnt_max)
{
    SOCKET socket_server = 0;
	struct sockaddr_in saddr = { 0 };

    WSADATA wd = { 0 };
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0)
        {
            perror("server startup error");
            exit(-1);
        }

    if( (socket_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        {
            perror("server socket error");
            exit(-1);
        }

    socket_server_g = socket_server;
    
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    if(!autoaddr)
    {
        // if(inet_pton(AF_INET,ip_str,&(saddr.sin_addr)) < 0) 这里是 linux 下的
        // {
        //     perror("server inet_pton error");
        //     exit(-1);
        // }
        saddr.sin_addr.S_un.S_addr = inet_addr(ip_str); // inet_addr() 只支持 ipv4 地址
    }else
    {
        saddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // 用这个 就是 系统自动指定 addr
    }
 
    if (bind(socket_server, (struct sockaddr*)&saddr, sizeof(struct sockaddr)) == SOCKET_ERROR)
        {
            perror("server bind error\n");
            exit(-1);
        }
 
	if (listen(socket_server, listen_cnt_max) == SOCKET_ERROR)
        {
            perror("server listen error\n");
            exit(-1);
        }
 
	// printf("server ip:%d.%d.%d.%d port:%d listening...\n",
    //     saddr.sin_addr.S_un.S_un_b.s_b1,
    //     saddr.sin_addr.S_un.S_un_b.s_b2,
    //     saddr.sin_addr.S_un.S_un_b.s_b3,
    //     saddr.sin_addr.S_un.S_un_b.s_b4,
    //     port);

    printf("server ip:%s port:%d listening...\n",
            inet_ntoa(saddr.sin_addr),   // inet_ntoa() 只支持 ipv4 地址
            ntohs(saddr.sin_port));
 
    return socket_server;
}

/* tcp server 接受连接和接收数据 并原样回传 的处理函数，目前只能接受一个连接 */
    /* 日后加上 epoll 就更加完善 支持多连接了 */
void win_socket_TCP_server_loop_handle(SOCKET socket_server)
{
    SOCKET socket_client = 0;
    struct sockaddr_in caddr = { 0 };
    int csize = sizeof(caddr);
    char buf[32] = { 0 };
    unsigned int recv_num = 0;

	while(1)
	{
		socket_client = accept(socket_server, (struct sockaddr*)&caddr, &csize);
            if (socket_client == INVALID_SOCKET)
            {
                perror("server accept error\n");
                exit(-1);
            }

        socket_client_g[0] = socket_client;
 
		printf("socket_client = %#X\n", socket_client);

        // char client_ip_addr_str[20] = {'\0'};
        // if(inet_ntop(AF_INET, &(caddr.sin_addr), client_ip_addr_str, sizeof(client_ip_addr_str)) < 0) 这里是 linux 下的
        // {
        //     perror("server inet_ntop error");
        //     exit(-1);
        // }
        printf("client ip:%s port:%d\n",
            inet_ntoa(caddr.sin_addr),
            ntohs(caddr.sin_port));
 
		do
		{
            memset(buf,'\0',sizeof(buf));

			recv_num = recv(socket_client, buf, sizeof(buf), 0);
			if (recv_num > 0)
			{
				
                printf("Receive data: %s\n", buf);
                send(socket_client, buf, strlen(buf) + 1, 0);
				
                if (strcmp("quit", buf) == 0)
				{
                    printf("quiting...\n");
                    closesocket(socket_client);
					goto quit_server_test;

				}else if(strcmp("diss", buf) == 0)
                {
                    printf("disconnect...wait for next\n");
                    break;
                }
			}
 
		} while (recv_num > 0);
 
		closesocket(socket_client);
	}

quit_server_test:
 
	closesocket(socket_server);
 
	WSACleanup();
    
    printf("quited\n");
	return ;
}


SOCKET win_socket_TCP_client_init(unsigned char defaultaddr, 
    const char* ip_str, const unsigned short port)
{
    SOCKET sock = 0;
	struct sockaddr_in addr = { 0 };

    WSADATA wd = { 0 };
    if(WSAStartup(MAKEWORD(2, 2), &wd) != 0)
        {
            perror("client startup error");
            exit(-1);
        }

    if( (sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        {
            perror("client socket error");
            exit(-1);
        }

    /* client 要接连的 server 的 ip 和 port */
    addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

    if(!defaultaddr)
    {
        // if(inet_pton(AF_INET,ip_str,&(saddr.sin_addr)) < 0) 这里是 linux 下的
        // {
        //     perror("client inet_pton error");
        //     exit(-1);
        // }

        addr.sin_addr.S_un.S_addr = inet_addr(ip_str);   // inet_addr() 只支持 ipv4 地址
    }else
    {
        addr.sin_addr.S_un.S_addr = inet_addr(CLIENT_DEFAULT_AIM_ADDR_STR);
    }

    /* 这里可以省去 bind() 步骤 */

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
        {
            perror("connect error");
            exit(-1);
        }

    printf("connect succeed\n");
    printf("connect to server ip:%s port:%d\n",
            inet_ntoa(addr.sin_addr),   // inet_ntoa() 只支持 ipv4 地址
            ntohs(addr.sin_port));

    return sock;
}

/* 简单 client 发送 和 接受处理函数 */
void win_socket_TCP_client_loop_handle(SOCKET socket_client)
{
    char input[32] = { '\0' };
	char recv_buf[128] = { '\0' };
	int recv_n = 0;

    while (1)
	{
		printf("Input a str to send: ");
 
		scanf("%s", input);
 
		send(socket_client, input, strlen(input) + 1, 0);
 
		recv_n = recv(socket_client, recv_buf, sizeof(recv_buf), 0);
 
		if (recv_n > 0)
		{
			printf("Receive data: %s\n", recv_buf);
		}
		else
		{
			break;
		}
	}
 
	closesocket(socket_client);
 
	WSACleanup();
 
	return ;
}

#else

/* 记录 server 和 client 的 socket 句柄 的 全局变量 */
int socket_server_g;
int socket_client_g[TEST_SERVER_LISTEN_CNT_MAX];

int linux_socket_TCP_server_init(unsigned char autoaddr, 
    const char* ip_str, const unsigned short port, 
    const unsigned short listen_cnt_max)
{
    int socket_server = 0;
	struct sockaddr_in saddr = { 0 };

    if( (socket_server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            perror("server socket error");
            exit(-1);
        }

    socket_server_g = socket_server;
    
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    if(!autoaddr)
    {
        if(inet_pton(AF_INET,ip_str,&(saddr.sin_addr)) < 0)    // inet_pton() 支持 ipv4 或 ipv6 地址
        {
            perror("server inet_pton error");
            exit(-1);
        }
    }else
    {
        saddr.sin_addr.s_addr = htonl(INADDR_ANY); // 用这个 就是 系统自动指定 addr
    }
 
    if (bind(socket_server, (struct sockaddr*)&saddr, sizeof(struct sockaddr)) < 0)
        {
            perror("server bind error\n");
            exit(-1);
        }
 
	if (listen(socket_server, listen_cnt_max) < 0)
        {
            perror("server listen error\n");
            exit(-1);
        }

    // inet_ntop() 支持 ipv4 或 ipv6 地址
    char server_ip_addr_str[20] = {'\0'};
    if(inet_ntop(AF_INET, &(saddr.sin_addr), server_ip_addr_str, sizeof(server_ip_addr_str)) < 0)
        {
            perror("server inet_ntop 1 error");
            exit(-1);
        }
    
    printf("server ip:%s port:%d listening...\n",
            server_ip_addr_str,
            ntohs(saddr.sin_port));
 
    return socket_server;
}

/* tcp server 接受连接和接收数据 并原样回传 的处理函数，目前只能接受一个连接 */
    /* 日后加上 epoll 就更加完善 支持多连接了 */
void linux_socket_TCP_server_loop_handle(int socket_server)
{
    int socket_client = 0;
    struct sockaddr_in caddr = { 0 };
    int csize = sizeof(caddr);
    char buf[32] = { 0 };
    unsigned int recv_num = 0;

	while(1)
	{
		socket_client = accept(socket_server, (struct sockaddr*)&caddr, &csize);
            if (socket_client < 0)
            {
                perror("server accept error\n");
                exit(-1);
            }

        socket_client_g[0] = socket_client;
 
		printf("socket_client = %#X\n", socket_client);

        // inet_ntop() 支持 ipv4 或 ipv6 地址
        char client_ip_addr_str[20] = {'\0'};
        if(inet_ntop(AF_INET, &(caddr.sin_addr), client_ip_addr_str, sizeof(client_ip_addr_str)) < 0)
            {
                perror("server inet_ntop 2 error");
                exit(-1);
            }
        
        printf("client ip:%s port:%d\n",
            client_ip_addr_str,
            ntohs(caddr.sin_port));
 
		do
		{
            memset(buf,'\0',sizeof(buf));

			recv_num = recv(socket_client, buf, sizeof(buf), 0);
			if (recv_num > 0)
			{
                printf("Receive data: %s\n", buf);
                if(send(socket_client, buf, strlen(buf) + 1, 0) < 0)
                    {
                        perror("server send error");
                        goto quit_server_test;
                    }
				
                if (strcmp("quit", buf) == 0)
				{
                    printf("quiting...\n");
                    close(socket_client);
					goto quit_server_test;

				}else if(strcmp("diss", buf) == 0)
                {
                    printf("disconnect...wait for next\n");
                    break;
                }
			}
 
		} while (recv_num > 0);
 
		close(socket_client);
	}

quit_server_test:

	close(socket_server);
    
    printf("quited\n");

	return ;
}

int linux_socket_TCP_client_init(unsigned char defaultaddr, 
    const char* ip_str, const unsigned short port)
{
    int sock = 0;
	struct sockaddr_in addr = { 0 };

    if( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            perror("client socket error");
            exit(-1);
        }

    /* client 要接连的 server 的 ip 和 port */
    addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
    if(!defaultaddr)
    {
        if(inet_pton(AF_INET, ip_str, &(addr.sin_addr)) < 0)
        {
            perror("client inet_pton 1 error");
            exit(-1);
        }
    }else
    {
        if(inet_pton(AF_INET, CLIENT_DEFAULT_AIM_ADDR_STR, &(addr.sin_addr)) < 0)
        {
            perror("client inet_pton 2 error");
            exit(-1);
        }
    }

    /* 这里可以省去 bind() 步骤 */

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
        {
            perror("connect error");
            exit(-1);
        }
    
    // inet_ntop() 支持 ipv4 或 ipv6 地址
    char server_ip_addr_str[20] = {'\0'};
    if(inet_ntop(AF_INET, &(addr.sin_addr), server_ip_addr_str, sizeof(server_ip_addr_str)) < 0)
        {
            perror("client inet_ntop error");
            exit(-1);
        }

    printf("connect succeed\n");
    printf("connect to server ip:%s port:%d\n",
            server_ip_addr_str,
            ntohs(addr.sin_port));

    return sock;
}

void linux_socket_TCP_client_loop_handle(int socket_client)
{
    char input[32] = { '\0' };
	char recv_buf[128] = { '\0' };
	int recv_n = 0;

    while (1)
	{
        memset(input,'\0',sizeof(input));
        memset(recv_buf,'\0',sizeof(recv_buf));

		printf("Input a str to send: ");
 
		scanf("%s", input);
 
		if( send(socket_client, input, strlen(input) + 1, 0) < 0)
            {
                perror("client send error");
                break;
            }
 
		recv_n = recv(socket_client, recv_buf, sizeof(recv_buf), 0);
 
		if (recv_n > 0)
		{
			printf("Receive data: %s\n", recv_buf);
		}
		else
		{
            perror("client recv error");
			break;
		}
	}

	close(socket_client);
    
    printf("quited\n");
 
	return ;
}

#endif