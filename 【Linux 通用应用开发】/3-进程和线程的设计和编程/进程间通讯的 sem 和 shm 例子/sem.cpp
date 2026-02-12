#include "sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
namespace htx_ipc
{
int CSem::sem_init(key_t semkey,unsigned semsize,unsigned index,unsigned init_value,CShm *pshm)
{
    int ret = sem_create_only(semkey,semsize);
    if (ret < 0)
    {
        return -1;
    }
    sem_index = index;
    sem_key   = semkey;
    sem_size  = semsize;
    sem_pshm  = pshm;
    unsigned short* init_array = new unsigned short[semsize];
    unsigned int i;
    for(i = 0; i < semsize;++i)
    {
        init_array[i] = init_value;
    }
    ret = semctl(sem_id,0,SETALL,init_array);
    delete [] init_array;
    if (ret )
    {
        return -1;
    }
    return 0;
}   
//send data to queue
int CSem::enqueue(const void* data,unsigned data_len,unsigned flow)
{
    return 0;
}
//get data from queue
int CSem::dequeue(void* buf,unsigned buf_size,unsigned& data_len,unsigned& flow)
{
    return 0;
}
int CSem::sem_open(key_t semkey,unsigned semsize)
{
    int semid = semget(semkey,semsize,0666);
    if (semid < 0)
    {
        return -1;
    }
    sem_id = semid;
    return 0;
}
int CSem::sem_create_only(key_t semkey,unsigned semsize)
{
   int semid = semget(semkey,semsize,0666 | IPC_CREAT | IPC_EXCL);
   if ( semid < 0)
   {
       if (errno == EEXIST)
       {
           int ret = sem_open(semkey,semsize);
           if (ret < 0)
           {
               return -1;
           }
           return 0;
       }
       return -1;
   }
   else 
   {
      sem_id  = semid;
      return 0;
   }
}
int CSem::set_value(unsigned init_value)
{
    int ret = semctl(sem_id,sem_index,SETVAL,init_value);
    return ret;
}
int CSem::get_value()
{
    int ret = semctl(sem_id,sem_index,GETVAL);
    return ret;
}
int CSem::sem_post()
{
    struct sembuf _buf;
    _buf.sem_num = sem_index;
    _buf.sem_op = 1;
    _buf.sem_flg = SEM_UNDO;
    int ret = semop(sem_id,&_buf,1);
    if (ret < 0)
    {
        return -1;
    }
    return 0;
}
int CSem::sem_wait()
{
    struct sembuf _buf;
    _buf.sem_num = sem_index;
    _buf.sem_op = -1;
    _buf.sem_flg = SEM_UNDO;
    int i,loop_limit = 5;
    for (i = 0;i < loop_limit;++i)
    {
        errno = 0;
        int ret = semop(sem_id,&_buf,1);
        if (ret < 0)
        {
            if ( errno != EINTR)
            {
                return -1;
            
            }
        }
        else 
        {
            return 0;
        }
    }
}
/* 
 * 0 trywait succ
 * -1 errno 
 *  1 no sem set 
 * */
int CSem::sem_trywait()
{
    errno = 0;
    struct sembuf _buf;
    _buf.sem_num = sem_index;
    _buf.sem_op = -1;
    _buf.sem_flg = SEM_UNDO | IPC_NOWAIT;
    int ret = semop(sem_id,&_buf,1);
    if (ret < 0)
    {
        if (errno != EAGAIN)
        {
            return -1;
        }
        else 
        {
            return 1;
        }
    }
    else 
    {
        return 0;
    }
}
/* 
 * 0 timewait succ
 * 1 time out 
 * -1 timewait error
 * */
int CSem::sem_timewait(unsigned& sec,unsigned& nanosec)
{
    struct timespec ts;
    ts.tv_sec = sec;
    ts.tv_nsec = nanosec;

    struct sembuf _buf;
    _buf.sem_num = sem_index;
    _buf.sem_op = -1;
    _buf.sem_flg = SEM_UNDO | IPC_NOWAIT;
    
    int i,loop_limit = 5;
    for (i = 0; i< loop_limit;++i)
    {
        errno = 0;
        int ret = semtimedop(sem_id,&_buf,1,&ts);
        if (ret < 0)
        {
            if (errno == EAGAIN)
            {
                return 1;
            }
            else if (errno == EINTR)
            {
                continue;
            }
            else 
            {
                return -1;
            }
        }
        else 
        {
            return 0;
        }
    }
}
int CSem::sem_destroy()
{
    int ret = semctl(sem_id,0,IPC_RMID);
    return ret < 0 ? ret: 0;
}
}
