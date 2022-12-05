#ifndef _SERIAL_H
#define _SERIAL_H

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);
int open_port(char *com);

/* 编程例子 在 serial.c 最后 */

#endif


