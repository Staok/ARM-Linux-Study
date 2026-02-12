#include "shm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <fcntl.h>
//send data to queue
//using namespace htx_ipc;
namespace htx_ipc
{
int CShm::shm_create_only(key_t key,unsigned ui_size)
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
}
int CShm::shm_open(key_t key,unsigned size)
{
    int shmid = shmget(key,size,0777);
    if (shmid < 0)
    {
        return -1;
    }
    shm_id   = shmid;
    shm_key  = key;
    shm_size = size;
    m_block = NULL;
    return 0;
}
int CShm::init(key_t shmkey,unsigned shmsize)
{   
    assert(shmsize > C_HEAD_SIZE);
    int ret =  shm_create_only(shmkey,shmsize);
    if (ret  == -1) 
    {  
        return -1; 
    }   
    else if(ret == -2) 
    {   
        ret = shm_open(shmkey,shmsize);
        if (ret == 0)
        {
            if (m_block == NULL)
            {
                attatch();
            }
        }
        return ret;
    }   
    else 
    {  
        shmkey = shm_key;
        shmsize = shm_size;
        attatch();
        return 0;
    }   
}   
void CShm::detach()
{
    if (m_block !=NULL)
    {
        shmdt(m_block);
        //shmctl(shm_id,IPC_RMID,NULL);
    }
}
void CShm::attatch()
{
    m_block = NULL;
    char *p  = NULL;
    p = (char*)shmat(shm_id,NULL,0);
    m_head = (unsigned*)p;
    m_tail = m_head + 1;
    m_block = (char*)(m_tail + 1);
    m_block_size = shm_size - C_HEAD_SIZE;
}
//send data to queue
int CShm::enqueue(const void* data,unsigned data_len,unsigned flow)
{
    unsigned head = *m_head;
    unsigned tail = *m_tail;
    unsigned free_len = head > tail ? head - tail : head + m_block_size - tail;
    unsigned tail_len = m_block_size - tail;

    char sHead[C_HEAD_SIZE] = {0};
    unsigned total_len = data_len + C_HEAD_SIZE;
    if (free_len <= total_len)
    {
        return -1;
    }
    memcpy(sHead,&total_len,sizeof(unsigned));
    memcpy(sHead + sizeof(unsigned),&flow,sizeof(unsigned));

    if (tail_len >= total_len)
    {
        memcpy(m_block + tail, sHead,C_HEAD_SIZE);
        memcpy(m_block + tail + C_HEAD_SIZE,data,data_len);
        *m_tail += data_len + C_HEAD_SIZE;
    }
    else if (tail_len >= C_HEAD_SIZE && tail_len < C_HEAD_SIZE + data_len)
    {
        memcpy(m_block + tail,sHead,C_HEAD_SIZE);
        unsigned first_len = tail_len - C_HEAD_SIZE;
        memcpy(m_block + tail + C_HEAD_SIZE,data,first_len);

        unsigned second_len = data_len - first_len;
        memcpy(m_block,((char*)data) + first_len,second_len);

        *m_tail += data_len + C_HEAD_SIZE;
        *m_tail -= m_block_size;
    }
    else 
    {
        memcpy(m_block + tail, sHead,tail_len);
        unsigned second_len = C_HEAD_SIZE - tail_len;
        memcpy(m_block,sHead + tail_len,second_len);

        memcpy(m_block + second_len,data,data_len);
        *m_tail = second_len + data_len;
    }
    return 0;
}
//get data from queue
int CShm::dequeue(void* buf,unsigned buf_size,unsigned& data_len,unsigned& flow)
{
    unsigned head = *m_head;
    unsigned tail = *m_tail;
    if (head == tail)
    {
        data_len = 0;
        return 0;
    }
    unsigned used_len = tail > head ? tail - head : tail + m_block_size - head;
    char sHead[C_HEAD_SIZE];

    if (head + C_HEAD_SIZE > m_block_size)
    {
        unsigned first_size = m_block_size - head;
        unsigned second_size = C_HEAD_SIZE - first_size;
        memcpy(sHead,m_block + head,first_size);
        memcpy(sHead + first_size,m_block,second_size);
        head = second_size;
    }
    else 
    {
        memcpy(sHead,m_block + head ,C_HEAD_SIZE);
        head += C_HEAD_SIZE;
    }

    unsigned total_len = *(unsigned*)(sHead);
    flow = *(unsigned*)(sHead + sizeof(unsigned));
    assert(total_len <= used_len);

    data_len = total_len - C_HEAD_SIZE;
    if (data_len > buf_size)
    {
        return -1;
    }

    if (head + data_len  > m_block_size)
    {
        unsigned first_size = m_block_size - head;
        unsigned second_size = data_len - first_size;
        memcpy(buf,m_block + head,first_size);
        memcpy(((char*)buf) + first_size,m_block,second_size);
        *m_head = second_size;
    }
    else 
    {
        memcpy(buf,m_block + head,data_len);
        *m_head = head + data_len;
    }
    return 0;
}
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
    int ret = sem_wait();
    if (ret < 0)
    {
        printf("sem wait error\n");
        return -1;
    }
    ret = sem_pshm->enqueue(data,data_len,flow);
    if (ret < 0)
    {
        printf("sem enqueue error\n");
        sem_post();
        return -1;
    }
    sem_post();
    return 0;
}
//get data from queue
int CSem::dequeue(void* buf,unsigned buf_size,unsigned& data_len,unsigned& flow)
{
    int ret = sem_wait();
    if (ret < 0)
    {
        printf("sem wait error\n");
        return -1;
    }
    ret = sem_pshm->dequeue(buf,buf_size,data_len,flow);
    if (ret < 0)
    {
        printf("sem dequeue error\n");
        sem_post();
        return -1;
    }
    sem_post();
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
    return -1;
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
    return 1;
}
int CSem::sem_destroy()
{
    int ret = semctl(sem_id,0,IPC_RMID);
    return ret < 0 ? ret: 0;
}
int CFifo::init(const std::string& fifo_path,unsigned wait_sec,unsigned wait_usec)
{
    m_uiwait_sec   = wait_sec;
    m_uiwait_usec  = wait_usec;

    int mode = 0666 | O_NONBLOCK | O_NDELAY;

    errno = 0;
    if ((mkfifo(fifo_path.c_str(),mode)) < 0)
    {
        if (errno != EEXIST)
        {
            return -1;
        }
    }
    if (m_ifd != -1)
    {
        close(m_ifd);
        m_ifd = -1;
    }
    if ((m_ifd = open(fifo_path.c_str(),O_RDWR)) < 0)
    {
        return -1;
    }
    if (m_ifd > 1024)
    {
        close(m_ifd);
        return -1;
    }

    m_strfifo_path = fifo_path;
    int flag = fcntl(m_ifd,F_GETFL,0);

    if (flag == -1)
    {
        return errno ? -errno : flag;
    }
    if (flag & O_NONBLOCK)
    {
        return 0;
    }
    int ret = fcntl(m_ifd,F_SETFL,flag | O_NONBLOCK | O_NDELAY);
    return (ret < 0) ? (errno ? -errno :ret) : 0;
    return 0;
}
int CFifo::enqueue(const void *data,unsigned data_len,unsigned flow)
{
    int ret = m_sem.enqueue(data,data_len,flow);
    if (ret)
    {
        return ret;
    }

    errno = 0;
    ret = write(m_ifd,"\0",1);
    if (ret < 0 && errno != EAGAIN)
    {
        return -1;
    }
    return 0;
}
int CFifo::dequeue(void *buf,unsigned buf_size,unsigned& data_len,unsigned& flow)
{
    int ret = m_sem.dequeue(buf,buf_size,data_len,flow);
    if (ret || data_len)
    {
        return ret;
    }
    ret = select_fifo();
    if (ret == 0)
    {
        data_len = 0;
        return ret;
    }
    else if (ret < 0)
    {
        return -1;
    }
    static const unsigned buf_len = 1 <<10;
    char buffer[buf_len];
    ret = read(m_ifd,buffer,buf_len);
    if (ret < 0 && errno != EAGAIN)
    {
        return -1;
    }
    return m_sem.dequeue(buf,buf_size,data_len,flow);
}
int CFifo::select_fifo()
{
    errno = 0;
    fd_set readfd;
    FD_ZERO(&readfd);
    FD_SET(m_ifd,&readfd);
    struct timeval tv;
    tv.tv_sec  = m_uiwait_sec;
    tv.tv_usec = m_uiwait_usec;

    int ret = select(m_ifd + 1,&readfd,NULL,NULL,&tv);
    if (ret > 0)
    {
        if (FD_ISSET(m_ifd,&readfd))
        {
            return ret;
        }
        else 
        {
            return -1;
        }
    }
    else if (ret == 0)
    {
        return 0;
    }
    else 
    {
        if (errno != EINTR)
        {
            close(m_ifd);
        }
        return -1;
    }
}
}
