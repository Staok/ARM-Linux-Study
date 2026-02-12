#ifndef _SHM_H_
#define _SHM_H_ 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/times.h>
#include <errno.h>
#include <error.h>
#include <assert.h>
#include "shm.h"
#define C_HEAD_SIZE 8
using namespace std;
namespace htx_ipc
{
    class CSem
    {
        public:
            CSem(){}
            ~CSem(){}
            int  sem_open(key_t key,unsigned ui_size);
            int  sem_create_only(key_t key,unsigned ui_size);
            int  sem_init(int semkey,unsigned semsize,unsigned index,unsigned init_value,CShm* pshm);
            int  set_value(unsigned init_value);
            int  get_value();
            int  sem_post();
            int  sem_wait();
            int  sem_trywait();
            int  sem_timewait(unsigned& sec,unsigned& nanosec);
            int  sem_destroy();
            int  get_semid()
            {
                return sem_id;
            }
            int get_semkey()
            {
                return sem_key;
            }
            int get_semsize()
            {
                return sem_size;
            }
            int get_semindex()
            {
                return sem_index;
            }
            int enqueue(const void *data,unsigned data_len ,unsigned flow);
            int dequeue(void* buf,unsigned buf_size,unsigned& data_len,unsigned& flow);
        protected:
            int      sem_id;
            unsigned sem_key;
            unsigned sem_size;
            unsigned sem_index;
            CShm*    sem_pshm;
    };
}
#endif
