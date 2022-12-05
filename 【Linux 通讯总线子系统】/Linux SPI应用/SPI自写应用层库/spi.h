#ifndef _SPI_DEBUG_H
#define _SPI_DEBUG_H

extern const char *spi_dev_name;

#define SPI_BUF_SIZE 50
extern unsigned char* spi_rx_buf; /* 在 spi_dev_init() 中 使用 malloc 为其申请 SPI_BUF_SIZE 字节空间，spi_tx_buf 同，并要在 spi_dev_uninit() 中 free 释放掉 */
extern unsigned char* spi_tx_buf;

/* spi 测试 */
void spi_test(void);

/* 初始化 spi 设备。为 spi_buf 申请空间，打开 spidev 设备文件，并 ioctl() 配置 */
void spi_dev_init(void); 

/* spi 发送，发送 spi_tx_buf 的数据，适合用于 大数据量 传输，每次调用都要好几毫秒，因此不必要频繁调用
    tr_cnt 为 几个 传输周期，
    tr_byte 为 一次 传输周期（cs 的周期） 的 字节数 */
int spi_test_ioctl_msg_send(unsigned int tr_cnt, unsigned int tr_byte);

/* spi 接收，与 发送 的 同理 */
int spi_test_ioctl_msg_recv(unsigned int tr_cnt, unsigned int tr_byte);

/* 反初始化 spi 设备。关闭设备并释放 spi_buf 空间 */
void spi_dev_uninit(void);

#endif



