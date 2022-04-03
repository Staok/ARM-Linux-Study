#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

/* set_opt(fd,115200,8,'N',1) */
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	
	if ( tcgetattr( fd,&oldtio) != 0) { 
		perror("SetupSerial 1");
		return -1;
	}
	
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag |= CLOCAL | CREAD; 
	newtio.c_cflag &= ~CSIZE; 

	newtio.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
	newtio.c_oflag  &= ~OPOST;   /*Output*/

	switch( nBits )
	{
	case 7:
		newtio.c_cflag |= CS7;
	break;
	case 8:
		newtio.c_cflag |= CS8;
	break;
	}

	switch( nEvent )
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
	break;
	case 'E': 
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
	break;
	case 'N': 
		newtio.c_cflag &= ~PARENB;
	break;
	}

	switch( nSpeed )
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
	break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
	break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
	break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
	break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
	break;
	}
	
	if( nStop == 1 )
		newtio.c_cflag &= ~CSTOPB;
	else if ( nStop == 2 )
		newtio.c_cflag |= CSTOPB;
	
	newtio.c_cc[VMIN]  = 1;  /* 读数据时的最小字节数: 没读到这些数据我就不返回! */
	newtio.c_cc[VTIME] = 0; /* 等待第1个数据的时间: 
	                         * 比如VMIN设为10表示至少读到10个数据才返回,
	                         * 但是没有数据总不能一直等吧? 可以设置VTIME(单位是10秒)
	                         * 假设VTIME=1，表示: 
	                         *    10秒内一个数据都没有的话就返回
	                         *    如果10秒内至少读到了1个字节，那就继续等待，完全读到VMIN个数据再返回
	                         */

	tcflush(fd,TCIFLUSH);
	
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
	//printf("set done!\n");
	return 0;
}

int open_port(char *com)
{
	int fd;
	//fd = open(com, O_RDWR|O_NOCTTY|O_NDELAY);
	fd = open(com, O_RDWR|O_NOCTTY);
    if (-1 == fd){
		return(-1);
    }
	
	  if(fcntl(fd, F_SETFL, 0)<0) /* 设置串口为阻塞状态*/
	  {
			printf("fcntl failed!\n");
			return -1;
	  }
  
	  return fd;
}


/*
 * ./serial_send_recv <dev>
 */
int main(int argc, char **argv)
{
	int fd;
	int iRet;
	char c;

	/* 1. open */

	/* 2. setup 
	 * 115200,8N1
	 * RAW mode
	 * return data immediately
	 */

	/* 3. write and read */
	
	if (argc != 2)
	{
		printf("Usage: \n");
		printf("%s </dev/ttySAC1 or other>\n", argv[0]);
		return -1;
	}

	fd = open_port(argv[1]);
	if (fd < 0)
	{
		printf("open %s err!\n", argv[1]);
		return -1;
	}

	iRet = set_opt(fd, 115200, 8, 'N', 1);
	if (iRet)
	{
		printf("set port err!\n");
		return -1;
	}

	printf("Enter a char: ");
	while (1)
	{
		scanf("%c", &c);
		iRet = write(fd, &c, 1);
		iRet = read(fd, &c, 1);
		if (iRet == 1)
			printf("get: %02x %c\n", c, c);
		else
			printf("can not get data\n");
	}

	return 0;
}

