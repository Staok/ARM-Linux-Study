#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <time.h>
#include "shm.h"
#include <errno.h>
#include <error.h>
#define FIFO_PATH "/tmp/test_fifo"
#define SHM_SIZE 100
#define SHM_KEY  10222226L
#define SEM_KEY  10222226L
#define SEM_SIZE  1
#define SEM_INDEX 0 
#define SEM_INIT_VALUE 1
#include <string.h>
#include <string>
using namespace std;
using namespace htx_ipc;
int fifo_write(CFifo &fifo)
{
    char *p = (char*)malloc(1024 * 1024);
    char sendbuf[1024] = {0};
    time_t t = time(NULL);
    struct tm* ptm = localtime(&t);
    snprintf(sendbuf,sizeof(sendbuf),"now is %4d-%02d-%02d %02d:%02d:%02d",ptm->tm_year + 1900,\
            ptm->tm_mon + 1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
    unsigned len = strlen(sendbuf);
    unsigned flow = 1002;
    memcpy(p,sendbuf,len);
    int ret = fifo.enqueue(p,len,flow);
    if (ret < 0)
    {
        printf("send data to fifo error\n");
        free(p);
        return -1;
    }
    free(p);
    printf("send data to fifo succ\n");
    return 0;
}
int fifo_read(CFifo &fifo)
{
   char * p = (char*)malloc(1024 * 1024);
   unsigned buf_size = 1024 * 1024;
   char recvbuf[1024] = {0};
   unsigned len,flow;
   int ret = fifo.dequeue(p,buf_size,len,flow);
   if (ret < 0)
   {
       printf("get data from fifo error\n");
       free(p);
       return -1;
   }
   strncpy(recvbuf,p,len);
   printf("get data %s\n",recvbuf);
   free(p);
   return 0;
}
void test_fifo()
{
    CShm testshm;

    int ret = testshm.init(SHM_KEY,SHM_SIZE);
    if (ret < 0)
    {
        printf("init shm error %d\n",ret);
        exit(1);
    }
    CSem testsem;
    ret = testsem.sem_init(SEM_KEY,SEM_SIZE,SEM_INDEX,SEM_INIT_VALUE,&testshm);
    if (ret < 0)
    {
        printf("init sem fail\n");
        testshm.detach();
        return;
    }
    //char strfifopath[1024] = {0};
    //strcpy(strfifopath,FIFO_PATH);
    //fifopath.assign(strfifopath,strlen(strfifopath));
    string fifopath;
    fifopath.assign(FIFO_PATH,strlen(FIFO_PATH));
    CFifo testfifo(testsem);
    ret = testfifo.init(fifopath,3,0);
    int fifo_fd = testfifo.fd();
    if (ret < 0)
    {
        printf("init fifo error errno= %d\n",errno);
        return ;
    }
    while(1)
    {
        fifo_write(testfifo);
        fifo_read(testfifo);
        sleep(1);
        printf("fifo again\n");
    }
    testshm.detach();
    close(fifo_fd);
    printf("bye bye\n");
}
int main(int argc,char *argv[])
{
    test_fifo();
   // test_shm();
    return 0;
}
