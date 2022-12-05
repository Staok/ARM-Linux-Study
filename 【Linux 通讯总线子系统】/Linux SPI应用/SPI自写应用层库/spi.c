

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <stdint.h>

#include <sys/ioctl.h>
#include <poll.h>
#include <signal.h>
#include <termios.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "spi.h"
#include "debug_print.h"


/* ———————————————————————————————— spidev 设置的相关参数 ———————————————————————————————— */
const char *spi_dev_name = "/dev/spidev1.0"; /* ecspi2 spi 外设的第 0 个设备（第 0 个 cs 线） */
static uint8_t spi_mode = SPI_MODE_0; /* mode 默认是 0，即 SPI_MODE_0 */
    /* mode 可选：
        SPI_MODE_0          (0|0)         即 CPOL = 0，CPHA = 0
        SPI_MODE_1          (0|SPI_CPHA)  即 CPOL = 0，CPHA = 1 以下同理
        SPI_MODE_2          (SPI_CPOL|0)
        SPI_MODE_3          (SPI_CPOL|SPI_CPHA)
        
        SPI_CPHA 和 SPI_CPOL 可以不用，只用 SPI_MODE_0~3 即可 选好模式
        SPI_CPHA            clock phase     采样时刻，在时钟第一个跳变沿还是第二个
        SPI_CPOL            clock polarity  时钟空闲时电平

        这些可以用 | 多选。有的可能不支持，驱动会打印不支持个别 mode
        SPI_LOOP            loopback                        回环模式
        SPI_LSB_FIRST       least significant bit first     设置为 LSB，不设置则默认是 MSB
        SPI_CS_HIGH         chip select active high         设置为 CS 高有效，不设置默认是 CS 低有效
        SPI_3WIRE           SI/SO signals shared            输入输出信号使用同一根信号线
        SPI_NO_CS
        SPI_READY
     */
static uint8_t spi_bits = 8;          /* 一个传输 word 的 bit 数，写 0 时默认为 8 */ /* 就用 8 不要改了 */
static uint32_t spi_speed = 5000;  /*  spi clk 频率 */ // 设备树中规定 最高频 20MHz，这里定 15MHz
static uint16_t spi_delay = 10;      /* delay (usec 微秒)，两个 spi_ioc_transfer 之间的延时 */

unsigned char* spi_rx_buf = NULL; /* 在 spi_dev_init() 中 使用 malloc 为其申请 SPI_BUF_SIZE 字节空间，spi_tx_buf 同，并要在 spi_dev_uninit() 中 free 释放掉 */
unsigned char* spi_tx_buf = NULL;

int spi_dev_fd = 0;

/* ———————————————————————————————— spi 测试 相关 ———————————————————————————————— */
/* 往 spi_s_tx_buf 装填 一个 16bits 数据 */
#define load_spi_m_tx_buf_16b(x)    \
    do{                             \
        spi_tx_buf[0] = ((unsigned short)(x)) >> 8;     \
        spi_tx_buf[1] = ((unsigned short)(x)) & 0xff;   \
    }while(0);

/* 往 spi_s_tx_buf 装填 一个 32bits 数据 */
#define load_spi_m_tx_buf_32b(x)    \
    do{                             \
        *((unsigned int*)&spi_tx_buf[0]) = (unsigned int)(x); \
    }while(0);

#define CMD_IOC_SETIO_GPIO5_08      _IOW(CMD_IOC_MAGIC, 4, unsigned int)

    /* ecspi2 外设 master 发送时候 的 cs 脚不能用（传输周期内不变化），在设备树中更换 cs-gpio 也没有用
        暂不知原因，因此用 一个 io 模拟 cs */
#define spi_send_16b(x) \
    err = ioctl(dev_fd, CMD_IOC_SETIO_GPIO5_08, 0); P_ERR_RAW(err < 0); \
    load_spi_m_tx_buf_16b(x); spi_test_ioctl_msg_send(1, 2);               \
    err = ioctl(dev_fd, CMD_IOC_SETIO_GPIO5_08, 1); P_ERR_RAW(err < 0);

/* spi 测试 */
void spi_test(void)
{
    int err = 0;
    spi_dev_init();
    sleep(1);

    /* 测试 spi_test_ioctl_msg_send/recs API */

    /* 读 sopc 端 的测试数据 测试 */
    char* dev_name = "/dev/mic_arr_1";
    int dev_fd;
    dev_fd = open(dev_name, O_RDWR | O_NONBLOCK);
        P_ERR_RAW(dev_fd < 0);
    err = ioctl(dev_fd, CMD_IOC_SETIO_GPIO5_08, 1); /* 先给 cs 设置高 */
        P_ERR_RAW(err < 0);
    sleep(1);

    /* 接收一次 4byte 数据，soc 运行到这里之前，sopc 那边应该确保已经运行到 spi 待发送的函数处 */
    err = ioctl(dev_fd, CMD_IOC_SETIO_GPIO5_08, 0); P_ERR_RAW(err < 0);
    // while(err < 0)
    // {
        err = spi_test_ioctl_msg_recv(1, 4);
    // }
    err = ioctl(dev_fd, CMD_IOC_SETIO_GPIO5_08, 1); P_ERR_RAW(err < 0);
    
    printf("spi rx data: %#x\n",(unsigned int)spi_rx_buf[0]);

    sleep(1);

    close(dev_fd);

    /* 读 icm-20608-g 的 WHO AM I 寄存器，应该返回 0xaf */
    // spi_tx_buf[0] = 0x75 | 0x80;
        /* 读 0x75 寄存器，读时候把 最高位 置1，写时置0 */
    // spi_test_ioctl_msg_send(1, 1);
    // spi_test_ioctl_msg_recv(1, 1);
    
    // printf("spi_rx_buf:");
    // for(i = 0;i < 5;i++)
    //     printf("%#x ",spi_rx_buf[i]);
    // printf("\n");

    /* 给 max7219 发显示数据 */
    // spi_tx_buf[0] = 0x0c;spi_tx_buf[1] = 0x01;
    // spi_tx_buf[2] = 0x0f;spi_tx_buf[3] = 0x00;
    // spi_tx_buf[4] = 0x09;spi_tx_buf[5] = 0xff;
    // spi_tx_buf[6] = 0x0b;spi_tx_buf[7] = 0x07;
    // spi_tx_buf[8] = 0x0a;spi_tx_buf[9] = 0x01;

    // spi_tx_buf[10] = 0x01;spi_tx_buf[11] = 0x04;
    // spi_tx_buf[12] = 0x02;spi_tx_buf[13] = 0x08;
    // spi_tx_buf[14] = 0x03;spi_tx_buf[15] = 0x00;
    // spi_tx_buf[16] = 0x04;spi_tx_buf[17] = 0x0b;

    // spi_tx_buf[18] = 0x05;spi_tx_buf[19] = 0x0f;
    // spi_tx_buf[20] = 0x06;spi_tx_buf[21] = 0x0a;
    // spi_tx_buf[22] = 0x07;spi_tx_buf[23] = 0x0e;
    // spi_tx_buf[24] = 0x08;spi_tx_buf[25] = 0x02;

    // spi_test_ioctl_msg_send(13, 2);


    /* 测试 cs 用 一个 io 模拟 的方法 */

    // dev_fd = open(dev_name, O_RDWR | O_NONBLOCK);
    //     P_ERR_RAW(dev_fd < 0);

    // err = ioctl(dev_fd, CMD_IOC_SETIO_GPIO5_08, 1); /* 先给 cs 设置高 */
    //     P_ERR_RAW(err < 0);
    // sleep(1);

    // spi_send_16b(0x0c01);
    // spi_send_16b(0x0f00);
    // spi_send_16b(0x09ff);
    // spi_send_16b(0x0b07);
    // spi_send_16b(0x0a01);

    // spi_send_16b(0x0104);
    // spi_send_16b(0x0208);
    // spi_send_16b(0x0300);
    // spi_send_16b(0x040b);

    // spi_send_16b(0x050f);
    // spi_send_16b(0x060a);
    // spi_send_16b(0x070e);
    // spi_send_16b(0x0802);

    sleep(1);

    spi_dev_uninit();
}


/* ———————————————————————————————— spi 应用层 封装 API ———————————————————————————————— */

void spi_dev_init(void)
{
    int err = -1;
    spi_rx_buf = (unsigned char*)malloc(SPI_BUF_SIZE);
    spi_tx_buf = (unsigned char*)malloc(SPI_BUF_SIZE);

    memset(spi_rx_buf, 0, SPI_BUF_SIZE);
    memset(spi_tx_buf, 0, SPI_BUF_SIZE);
    
    spi_dev_fd = open(spi_dev_name, O_RDWR);
        P_ERR_RAW(spi_dev_fd < 0);
    
    err = ioctl(spi_dev_fd, SPI_IOC_WR_MODE32, &spi_mode);
        P_ERR_RAW(err < 0);
        err = ioctl(spi_dev_fd, SPI_IOC_RD_MODE32, &spi_mode);
            P_ERR_RAW(err < 0);
        P_DEBUG_ARG("spi_mode read:%d",spi_mode);
    
    err = ioctl(spi_dev_fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bits);
        P_ERR_RAW(err < 0);
        err = ioctl(spi_dev_fd, SPI_IOC_RD_BITS_PER_WORD, &spi_bits);
            P_ERR_RAW(err < 0);
        P_DEBUG_ARG("spi_bits read:%d",spi_bits);
    
    err = ioctl(spi_dev_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);
        P_ERR_RAW(err < 0);
        err = ioctl(spi_dev_fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);
            P_ERR_RAW(err < 0);
        P_DEBUG_ARG("spi_speed read:%d",spi_speed);
    
}

/* spi 收发 可以用 read/write，也可以用 ioctl，
    这三个，每调用一次就是一个 cs 传输周期，一个传输周期 长度都是 len 字节
    
    spi 用 read/write 半双工进行收发的例子
        用 read/write 每次读或者写的大小不能大于 4096Byte
        err = write(spi_dev_fd, spi_tx_buf, len);
            P_ERR_ARG("write spi, err:%d", err);
        
        err = read(spi_dev_fd, spi_rx_buf, len);
            P_ERR_ARG("read spi, err:%d", err);

    对于 ioctl，是用 struct spi_ioc_transfer，
        只读 则保持 rx_buf 成员 为 NULL，只写 同理，
        如果 tx_buf 和 rx_buf 成员都不为 NULL，则是全双工的读写传输  
*/

/* spi 发送，发送 spi_tx_buf 的数据，适合用于 大数据量 传输，每次调用都要好几毫秒，因此不必要频繁调用
    tr_cnt 为 几个 传输周期，
    tr_byte 为 一次 传输周期（cs 的周期） 的 字节数
    
    比如：tr_cnt = 10，tr_byte = 4，即 err = spi_test_ioctl_msg_send(10, 4);
        就是 每次 传输周期 传输 4字节（32bits数据），传输 10次，
        spi_tx_buf 必须这样填充：
            spi_tx_buf[0:3] 填充第一次传输的四个字节
            spi_tx_buf[4:7] 填充第二次传输的四个字节，以此类推

        如果 4 字节是一个 32bit 变量/数字，可以这样写：但要注意不同机器的大小端的区别
            for(i = 0; i < tr_cnt - 1;i++)
                *((unsigned int*)&spi_tx_buf[i * 4]) = (unsigned int)(0x0a0b0c00 + i); 
*/
int spi_test_ioctl_msg_send(unsigned int tr_cnt, unsigned int tr_byte)
{
    int status = -1;

    if(tr_byte * tr_cnt > SPI_BUF_SIZE)
    {
        return -1;
    }

    struct spi_ioc_transfer * tr = (struct spi_ioc_transfer *)malloc(sizeof(struct spi_ioc_transfer) * tr_cnt);
        P_ERR_RAW(NULL == tr);
    
    for(unsigned int i = 0;i < tr_cnt;i++)
    {
        memset(&tr[i], 0, sizeof(tr[0]));

        /* 在声明xfer后,必须初始化为0，
            因为驱动层会判断 tx_buf 和 rx_buf 不为空来进行读写操作!
            否则很容易误判断!*/
        tr[i].tx_buf = (unsigned long)(spi_tx_buf + (i * tr_byte));
        tr[i].rx_buf = (unsigned long)0;
        tr[i].len = tr_byte;                // 一次传输周期 几个 word，因为这里设置 一个 word 为 8bit，因此这里是几个 byte
        tr[i].delay_usecs = spi_delay;
        tr[i].speed_hz = spi_speed;
        tr[i].bits_per_word = spi_bits;     // 这里设置 一个 word 为 8bit
        tr[i].cs_change = 0;            /* 置1 会引起 CS 线在 
                                    spi_message 序列中 transfers 间变反向变化 */
    }

    /* SPI_IOC_MESSAGE(n) 的 n 表示 struct spi_ioc_transfer 有几个，有几个 就是几次 cs 传输周期 */
    status = ioctl(spi_dev_fd, SPI_IOC_MESSAGE(tr_cnt), tr); 
        P_ERR_RAW(status < 0);
    
    P_DEBUG_ARG("spi send done, ioctl status:%d",status);

    free(tr);

    return status;
}

/* spi 接收，与 发送 的 同理 */
int spi_test_ioctl_msg_recv(unsigned int tr_cnt, unsigned int tr_byte)
{
    int status = -1;

    if(tr_byte * tr_cnt > SPI_BUF_SIZE)
    {
        return -1;
    }

    struct spi_ioc_transfer tr_send_zero;
    struct spi_ioc_transfer * tr = (struct spi_ioc_transfer *)malloc(sizeof(struct spi_ioc_transfer) * tr_cnt);
        P_ERR_RAW(NULL == tr);

    memset(tr_send_zero, 0, sizeof(tr_send_zero);

    tr_send_zero[0].tx_buf = (unsigned long)"0x00"; /* 先发 1byte 的 0x00 */
    tr_send_zero[0].rx_buf = (unsigned long)0;
    tr_send_zero[0].len = 1;
    tr_send_zero[0].delay_usecs = spi_delay;
    tr_send_zero[0].speed_hz = spi_speed;
    tr_send_zero[0].bits_per_word = spi_bits;
    tr_send_zero[0].cs_change = 0;

    for(unsigned int i = 0;i < tr_cnt;i++)
    {
        memset(&tr[i], 0, sizeof(tr[0]));

        tr[i].tx_buf = (unsigned long)0;
        tr[i].rx_buf = (unsigned long)(spi_rx_buf + (i * tr_byte)); /* 再读 len byte */
        tr[i].len = tr_byte;
        tr[i].delay_usecs = spi_delay;
        tr[i].speed_hz = spi_speed;
        tr[i].bits_per_word = spi_bits;
        tr[i].cs_change = 0;
    }
    
    /* SPI_IOC_MESSAGE(n) 表示 struct spi_ioc_transfer 有几个，有几个 就是几次 cs 传输周期 */
    status = ioctl(spi_dev_fd, SPI_IOC_MESSAGE(1), tr_send_zero);
        P_ERR_RAW(status < 0);
    
    status = ioctl(spi_dev_fd, SPI_IOC_MESSAGE(tr_cnt), tr);
        P_ERR_RAW(status < 0);
    
    P_DEBUG_ARG("spi recv done, ioctl status:%d",status);

    free(tr);

    return status;
}



void spi_dev_uninit(void)
{
    close(spi_dev_fd);

    free(spi_tx_buf);
    free(spi_rx_buf);
}


