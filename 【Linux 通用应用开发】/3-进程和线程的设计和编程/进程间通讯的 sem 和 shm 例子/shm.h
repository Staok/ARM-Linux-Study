#ifndef _SHM_H_
#define _SHM_H_ 1
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <time.h>
#include <sys/times.h>
#include <errno.h>
#include <error.h>
#include <assert.h>
#include <fcntl.h>
#define C_HEAD_SIZE 8
#include <string>
using namespace std;
namespace htx_ipc
{
    class CShm
    {
        public:
            typedef struct tagMQStat
            {
                unsigned _used_len;
                unsigned _free_len;
                unsigned _total_len;
                unsigned _shm_key;
                unsigned _shm_id;
                unsigned _shm_size;
            }TMQStat;
        public:
            CShm(){}
            ~CShm(){}
            int shm_open(key_t key,unsigned ui_size);
            int shm_create_only(key_t key,unsigned ui_size);
            /* 
             {
                 int shmid = shmget(key,ui_size ,0777 | IPC_CREAT | IPC_EXCL);
                 if (shmid < 0)
                 {
                     if (errno == EEXIST)
                     {
                         return -2;
                     }
                     else 
                     {
                         return -1;
                     }
                 }
                 else 
                 {
                     shm_id = shmid;
                     shm_size = ui_size;
                     m_block_size = shm_size - C_HEAD_SIZE;
                     return 0;
                 }
            }*/
            int init(int shmkey,unsigned shmsize);
            void detach();
            void attatch();
            void get_stat(TMQStat &mq_stat)
            {
                unsigned head = *m_head;
                unsigned tail = *m_tail;

                mq_stat._used_len = (tail >= head) ? tail - head : tail + m_block_size - head;
                mq_stat._free_len = head > tail ? head - tail : head  + m_block_size - tail;
                mq_stat._total_len = m_block_size;
                mq_stat._shm_id    = shm_id;
                mq_stat._shm_id    = shm_key;
                mq_stat._shm_size  = shm_size;
            }
            int get_shmid()
            {
                return shm_id;
            }
            int get_shmkey()
            {
                return shm_key;
            }
            int get_shmsize()
            {
                return shm_size;
            }
            int enqueue(const void *data,unsigned data_len ,unsigned flow);
            int dequeue(void* buf,unsigned buf_size,unsigned& data_len,unsigned& flow);
        protected:
            int shm_id;
            unsigned shm_key;
            unsigned shm_size;
            unsigned* m_head;
            unsigned* m_tail;
            char* m_block;
            unsigned m_block_size;
            //static const unsigned C_HEAD_SIZE = 8;
    };
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
    class CFifo
    {
        public:
            CFifo(CSem& sem):m_sem(sem) ,m_ifd(-1){}
            ~CFifo(){}
            int init(const string& fifo_path,unsigned wait_sec,unsigned wait_usec);
            int enqueue(const void *data,unsigned data_len,unsigned flow);
            int dequeue(void *buf,unsigned buf_size,unsigned& data_len,unsigned& flow);
            int fd(){return m_ifd;}
            std::string fifo_path(){return m_strfifo_path;}
            unsigned wait_sec(){return m_uiwait_sec;}
            unsigned wait_usec(){return m_uiwait_usec;}
            CSem& get_sem(){return m_sem;}
        private:
            int select_fifo();
            CSem& m_sem;
            int m_ifd;
            unsigned m_uiwait_sec;
            unsigned m_uiwait_usec;
            std::string m_strfifo_path; 
    };
}
#endif



























