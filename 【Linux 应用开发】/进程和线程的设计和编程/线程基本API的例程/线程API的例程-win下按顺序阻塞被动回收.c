#define _GNU_SOURCE 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/* 例子说明：
创建 系统级 线程 1，无传入和传出参数，死循环，特定条件时退出，使用 pthread_join 回收
创建 用户级 线程 2、3、4 三个线程，线程号使用数组，传入和传出参数，使用 pthread_tryjoin_np 回收
*/

/* 用于设置线程属性，主要包括scope属性(用于区分用户态或者内核态)、detach属性、堆栈地址、堆栈大小、优先级 */
pthread_attr_t attr_1,attr_2_3_4[3];
/* 指向线程标识符的指针，区分线程，即可称为 线程号，仅在本进程中有效。本质是 unsigned long int */
pthread_t id_1, id_2_3_4[3]; 

/* 线程 1，无传入和传出参数，执行完后退出，使用 pthread_join 回收 */
void *thread_1(void *in_arg)
{
    int i = 0;
    printf("thread_1 ID = %lu\n", (unsigned long)pthread_self());
    for(;;)
    {
        printf("thread_1 print times = %d\n", ++i);
        if(i >= 3)
            pthread_exit(NULL);
            /* 用 pthread_exit() 来调用线程的返回值，用来退出线程，但是退出线程所占用的资源不会随着线程的终止而得到释放 */
        sleep(1); /* sleep() 单位秒，程序挂起 1 秒 */
    }
}

/* 线程 2 3 4 */
void *thread_2_3_4(void *in_arg)
{
    /* 必须要 static 修饰，否则 pthread_join/pthread_tryjoin_np 无法获取到正确值 */
    static char* exit_arg;
    
    /* exit_arg 是 本函数的一个局部变量，多个线程 2、3、4 都会修改它，因此最后返回的时候不知道是谁最后一次修改的 */
    /* 因此要格外注意 */
    exit_arg = (char*)in_arg;
    
    pthread_t self_id = pthread_self();
    if(self_id == id_2_3_4[0])
    {
        printf("thread_2 ID = %lu\n", (unsigned long)self_id);
        sprintf((char*)in_arg,"id_2 gagaga");
    }else if(self_id == id_2_3_4[1])
    {
        printf("thread_3 ID = %lu\n", (unsigned long)self_id);
        sprintf((char*)in_arg,"id_3 lalala");
    }else if(self_id == id_2_3_4[2])
    {
        printf("thread_4 ID = %lu\n", (unsigned long)self_id);
        sprintf((char*)in_arg,"id_4 hahaha");
    }else
    {
        pthread_exit(NULL);
    }

    pthread_exit((void*)in_arg);
}

int main(void)
{
    int ret = -1, i = 0;
    char *str_gru[3];
    void *exit_arg = NULL;
    
    pthread_attr_init(&attr_1);
    pthread_attr_setscope(&attr_1, PTHREAD_SCOPE_SYSTEM); /* 系统级线程 */
    
    for(i = 0;i < 3;i++)
    {
        pthread_attr_init(&attr_2_3_4[i]);
        pthread_attr_setscope(&attr_2_3_4[i], PTHREAD_SCOPE_PROCESS); /* 用户级线程 */
    }
    
    /* 创建线程 1 */
    ret = pthread_create(&id_1, NULL, thread_1, NULL);
    if(ret != 0)
    {
        /* perror 把一个描述性错误消息输出到标准错误 stderr, 调用"某些"函数出错时，该函数已经重新设置了errno 的值。perror 函数只是将你输入的一些信息和 errno 所对应的错误一起输出 */
        perror("pthread1, pthread_create: ");
        return -1;
    }
    
    /* 创建线程 2、3、4 */
	for(i = 0;i < 3;i++)
    {
        str_gru[i] = (char*)malloc(sizeof(char) * 42 + i);
	    ret = pthread_create(&id_2_3_4[i], NULL, thread_2_3_4, (void *)str_gru[i]);
	    if(ret != 0)
        {
		    perror("pthread 2 3 4, pthread_create: ");
		    return -1;
		}
	}
    
    /* 等待所有线程结束，先等 线程 2、3、4 按顺序要求的 退出，再等 线程 1 退出 */
    for(i = 0;i < 3;i++)
    {
        pthread_join(id_2_3_4[i], &exit_arg);
        printf("pthread : %d exit with str: %s\n", id_2_3_4[i], (char*)exit_arg);
        free(str_gru[i]);
	}
    pthread_join(id_1, NULL);
    printf("pthread : 1 exit\n");
    
    getchar();
    return 0;
}