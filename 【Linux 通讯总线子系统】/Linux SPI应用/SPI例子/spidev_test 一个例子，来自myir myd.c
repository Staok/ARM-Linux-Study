/*
 * SPI testing utility (using spidev driver)
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static void pabort(const char *s)
{
	perror(s);
	abort();
}

static const char *device = "/dev/spidev32766.0";
static uint32_t mode;
static uint8_t bits = 8;
static uint32_t speed = 500000;
static uint16_t delay;
static int verbose;

uint8_t default_tx[] = {

	0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
};

uint8_t default_rx[ARRAY_SIZE(default_tx)] = {0, };
char *input_tx;

static void hex_dump(const void *src, size_t length, size_t line_size, char *prefix)
{
	int i = 0;
	const unsigned char *address = src;
	const unsigned char *line = address;
	unsigned char c;

	printf("%s | ", prefix);
	while (length-- > 0) {
		printf("%02X ", *address++);
		if (!(++i % line_size) || (length == 0 && i % line_size)) {
			if (length == 0) {
				while (i++ % line_size)
					printf("__ ");
			}
			printf(" | ");  /* right close */
			while (line < address) {
				c = *line++;
				printf("%c", (c < 33 || c == 255) ? 0x2E : c);
			}
			printf("\n");
			if (length > 0)
				printf("%s | ", prefix);
		}
	}
}

/*
 *  Unescape - process hexadecimal escape character
 *      converts shell input "\x23" -> 0x23
 */
static int unescape(char *_dst, char *_src, size_t len)
{
	int ret = 0;
	char *src = _src;
	char *dst = _dst;
	unsigned int ch;

	while (*src) {
		if (*src == '\\' && *(src+1) == 'x') {
			sscanf(src + 2, "%2x", &ch);
			src += 4;
			*dst++ = (unsigned char)ch;
		} else {
			*dst++ = *src++;
		}
		ret++;
	}
	return ret;
}

static void transfer(int fd, uint8_t const *tx, uint8_t const *rx, size_t len)
{
	int ret;

	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = len,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	if (mode & SPI_TX_QUAD)
		tr.tx_nbits = 4;
	else if (mode & SPI_TX_DUAL)
		tr.tx_nbits = 2;
	if (mode & SPI_RX_QUAD)
		tr.rx_nbits = 4;
	else if (mode & SPI_RX_DUAL)
		tr.rx_nbits = 2;
	if (!(mode & SPI_LOOP)) {
		if (mode & (SPI_TX_QUAD | SPI_TX_DUAL))
			tr.rx_buf = 0;
		else if (mode & (SPI_RX_QUAD | SPI_RX_DUAL))
			tr.tx_buf = 0;
	}

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
		pabort("can't send spi message");

//	if (verbose)
//		hex_dump(tx, len, 32, "TX");
	hex_dump(rx, len, 32, "RX");
}

static void print_usage(const char *prog)
{
	printf("Usage: %s [-DsbdlHOLC3]\n", prog);
	puts("  -D --device   device to use (default /dev/spidev1.1)\n"
	     "  -s --speed    max speed (Hz)\n"
	     "  -d --delay    delay (usec)\n"
	     "  -b --bpw      bits per word \n"
	     "  -l --loop     loopback\n"
	     "  -H --cpha     clock phase\n"
	     "  -O --cpol     clock polarity\n"
	     "  -L --lsb      least significant bit first\n"
	     "  -C --cs-high  chip select active high\n"
	     "  -3 --3wire    SI/SO signals shared\n"
	     "  -v --verbose  Verbose (show tx buffer)\n"
	     "  -p            Send data (e.g. \"1234\\xde\\xad\")\n"
	     "  -N --no-cs    no chip select\n"
	     "  -R --ready    slave pulls low to pause\n"
	     "  -2 --dual     dual transfer\n"
	     "  -4 --quad     quad transfer\n");
	exit(1);
}

static void parse_opts(int argc, char *argv[])
{
	while (1) {
		static const struct option lopts[] = {
			{ "device",  1, 0, 'D' },
			{ "speed",   1, 0, 's' },
			{ "delay",   1, 0, 'd' },
			{ "bpw",     1, 0, 'b' },
			{ "loop",    0, 0, 'l' },
			{ "cpha",    0, 0, 'H' },
			{ "cpol",    0, 0, 'O' },
			{ "lsb",     0, 0, 'L' },
			{ "cs-high", 0, 0, 'C' },
			{ "3wire",   0, 0, '3' },
			{ "no-cs",   0, 0, 'N' },
			{ "ready",   0, 0, 'R' },
			{ "dual",    0, 0, '2' },
			{ "verbose", 0, 0, 'v' },
			{ "quad",    0, 0, '4' },
			{ NULL, 0, 0, 0 },
		};
		int c;

		c = getopt_long(argc, argv, "D:s:d:b:lHOLC3NR24p:v", lopts, NULL);

		if (c == -1)
			break;

		switch (c) {
		case 'D':
			device = optarg;
			break;
		case 's':
			speed = atoi(optarg);
			break;
		case 'd':
			delay = atoi(optarg);
			break;
		case 'b':
			bits = atoi(optarg);
			break;
		case 'l':
			mode |= SPI_LOOP;
			break;
		case 'H':
			mode |= SPI_CPHA;
			break;
		case 'O':
			mode |= SPI_CPOL;
			break;
		case 'L':
			mode |= SPI_LSB_FIRST;
			break;
		case 'C':
			mode |= SPI_CS_HIGH;
			break;
		case '3':
			mode |= SPI_3WIRE;
			break;
		case 'N':
			mode |= SPI_NO_CS;
			break;
		case 'v':
			verbose = 1;
			break;
		case 'R':
			mode |= SPI_READY;
			break;
		case 'p':
			input_tx = optarg;
			break;
		case '2':
			mode |= SPI_TX_DUAL;
			break;
		case '4':
			mode |= SPI_TX_QUAD;
			break;
		default:
			print_usage(argv[0]);
			break;
		}
	}
	if (mode & SPI_LOOP) {
		if (mode & SPI_TX_DUAL)
			mode |= SPI_RX_DUAL;
		if (mode & SPI_TX_QUAD)
			mode |= SPI_RX_QUAD;
	}
}

#define READ_ACCESS     0x00
#define WRITE_ACCESS    0x80
#define SPI_SPEED       800000
#define SPI_DEV_PATH    "/dev/spidev0.0"

int write_test(int fd){

    int spi_device;
    uint8_t out_buf[100];
	uint8_t r_buf[100];
    uint8_t command_size;
    struct spi_ioc_transfer k;
    int a,i;
//	uint8_t *data;

	out_buf[0]=0x02;
	out_buf[1]=0x0;
	out_buf[2]=0x0;
	out_buf[3]=0x01;
	out_buf[4]=0x02;
	out_buf[5]=0x03;
	out_buf[6]=0x04;
	out_buf[7]=0x05;
	out_buf[8]=0x06;

	for(i=0;i<68;i++){
     out_buf[i]=i;
	}

    /* I/O transaction */
    memset(&k, 0, sizeof(k)); /* clear k */
    k.tx_buf = (unsigned long) out_buf;
	k.rx_buf = (unsigned long) r_buf;
    k.len = 66;
    k.speed_hz = SPI_SPEED;
    k.cs_change = 0;
    k.bits_per_word = 8;
	k.delay_usecs=0;
    a = ioctl(fd, SPI_IOC_MESSAGE(1), &k);
//	printf("printf = a= %d \n ",a);
//    /* determine return code */
//    if (a != (int)k.len) {
//        printf("ERROR: SPI WRITE FAILURE\n");
//        return -1;
//    } else {
//        printf("Note: SPI write success\n");
//		 *data = r_buf[3-1];
//		printf("--- %s \n",r_buf[0]);
//		printf("--- %s \n",r_buf[1]);
//		printf("--- %s \n",r_buf[2]);
//		printf("--- %s \n",r_buf[3]);
//        return 1;
//    }

//		hex_dump(r_buf, k.len, 32, "RX");
	   for(i=0;i< k.len ;i++){
			printf("r_buf[%d] = %d  \n ",i,r_buf[i]);
	   }
//	
}

int write_test_2(int fd){

    int spi_device;
    uint8_t out_buf[100];
	uint8_t r_buf[100];
    uint8_t command_size;
    struct spi_ioc_transfer k;
    int a,i;
//	uint8_t *data;

	out_buf[0]=0x03;
	out_buf[1]=0x0;
	out_buf[2]=0x0;

    /* I/O transaction */
    memset(&k, 0, sizeof(k)); /* clear k */
    k.tx_buf = (unsigned long) out_buf;
	k.rx_buf = (unsigned long) r_buf;
    k.len = 3;
    k.speed_hz = SPI_SPEED;
    k.cs_change = 0;
    k.bits_per_word = 8;
	k.delay_usecs=0;
    a = ioctl(fd, SPI_IOC_MESSAGE(1), &k);
	printf("printf = a= %d \n ",a);
//    /* determine return code */
//    if (a != (int)k.len) {
//        printf("ERROR: SPI WRITE FAILURE\n");
//        return -1;
//    } else {
//        printf("Note: SPI write success\n");
//		 *data = r_buf[3-1];
//		printf("--- %s \n",r_buf[0]);
//		printf("--- %s \n",r_buf[1]);
//		printf("--- %s \n",r_buf[2]);
//		printf("--- %s \n",r_buf[3]);
//        return 1;
//    }

//		hex_dump(r_buf, k.len, 32, "RX");
	   for(i=0;i< k.len ;i++){
			printf("r_buf[%d] = %d  \n ",i,r_buf[i]);
	   }
	
}

//int test_m914(int fd,u16 address)
//{
//  uint8  buff_send[3];


//  buff_send[01]     = 1;
//  buff_send[01]     =  (u8)((address & 0xFF00) >> 8);;
//  buff_send[01]     =  (u8)(address & 0x00FF);

//   
//}

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd;
	uint8_t *tx;
	uint8_t *rx;
	int size;

	parse_opts(argc, argv);

//     printf("delay = %d ",delay);


	fd = open(device, O_RDWR);
	if (fd < 0)
		pabort("can't open device");

	/*
	 * spi mode
	 */
	ret = ioctl(fd, SPI_IOC_WR_MODE32, &mode);
	if (ret == -1)
		pabort("can't set spi mode");

	ret = ioctl(fd, SPI_IOC_RD_MODE32, &mode);
	if (ret == -1)
		pabort("can't get spi mode");

	/*
	 * bits per word
	 */
	ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't set bits per word");

	ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
		pabort("can't get bits per word");

	/*
	 * max speed hz
	 */
	ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't set max speed hz");

	ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
		pabort("can't get max speed hz");

	printf("spi mode: 0x%x\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

	if (input_tx) {
		size = strlen(input_tx+1);
		tx = malloc(size);
		rx = malloc(size);
		size = unescape((char *)tx, input_tx, size);
		while(1){
			transfer(fd, tx, rx, size);
			usleep(10000);
			break;
			printf("0000\n");
//			sleep(1);
		}
		
		free(rx);
		free(tx);
	} else {

	    while(1){
 //   		transfer(fd, default_tx, default_rx, sizeof(default_tx));
//			write_test(fd);
//			sleep(1);
			write_test(fd);
//			write_test_2(fd);
			printf("1111\n");
			usleep(100000);
			//break;
//			sleep(1);
		}

	}

	close(fd);

	return ret;
}
