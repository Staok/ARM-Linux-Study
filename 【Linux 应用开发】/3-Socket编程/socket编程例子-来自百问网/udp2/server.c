#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>


/* socket
 * bind
 * sendto/recvfrom
 */

#define SERVER_PORT 8888

int main(int argc, char **argv)
{
	int iSocketServer;
	int iSocketClient;
	struct sockaddr_in tSocketServerAddr;
	struct sockaddr_in tSocketClientAddr;
	int iRet;
	int iAddrLen;

	int iRecvLen;
	unsigned char ucRecvBuf[1000];

	int iClientNum = -1;
	
	iSocketServer = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == iSocketServer)
	{
		printf("socket error!\n");
		return -1;
	}

	tSocketServerAddr.sin_family      = AF_INET;
	tSocketServerAddr.sin_port        = htons(SERVER_PORT);  /* host to net, short */
 	tSocketServerAddr.sin_addr.s_addr = INADDR_ANY;
	memset(tSocketServerAddr.sin_zero, 0, 8);
	
	iRet = bind(iSocketServer, (const struct sockaddr *)&tSocketServerAddr, sizeof(struct sockaddr));
	if (-1 == iRet)
	{
		printf("bind error!\n");
		return -1;
	}


	while (1)
	{
		iAddrLen = sizeof(struct sockaddr);
		iRecvLen = recvfrom(iSocketServer, ucRecvBuf, 999, 0, (struct sockaddr *)&tSocketClientAddr, &iAddrLen);
		if (iRecvLen > 0)
		{
			ucRecvBuf[iRecvLen] = '\0';
			printf("Get Msg From %s : %s\n", inet_ntoa(tSocketClientAddr.sin_addr), ucRecvBuf);
		}
	}
	
	close(iSocketServer);
	return 0;
}


