
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>


/* ./01_get_input_info /dev/input/event0 */
int main(int argc, char **argv)
{
	int fd;
	int err;
	int len;
	int ret;
	int i;
	unsigned char byte;
	int bit;
	struct input_id id;
	unsigned int evbit[2];
	struct input_event event;
	int nfds;
	struct timeval tv;
	fd_set readfds;
	
	char *ev_names[] = {
		"EV_SYN ",
		"EV_KEY ",
		"EV_REL ",
		"EV_ABS ",
		"EV_MSC ",
		"EV_SW	",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"NULL ",
		"EV_LED ",
		"EV_SND ",
		"NULL ",
		"EV_REP ",
		"EV_FF	",
		"EV_PWR ",
		};
	
	if (argc != 2)
	{
		printf("Usage: %s <dev>\n", argv[0]);
		return -1;
	}

	fd = open(argv[1], O_RDWR | O_NONBLOCK);
	if (fd < 0)
	{
		printf("open %s err\n", argv[1]);
		return -1;
	}

	err = ioctl(fd, EVIOCGID, &id);
	if (err == 0)
	{
		printf("bustype = 0x%x\n", id.bustype );
		printf("vendor	= 0x%x\n", id.vendor  );
		printf("product = 0x%x\n", id.product );
		printf("version = 0x%x\n", id.version );
	}

	len = ioctl(fd, EVIOCGBIT(0, sizeof(evbit)), &evbit);
	if (len > 0 && len <= sizeof(evbit))
	{
		printf("support ev type: ");
		for (i = 0; i < len; i++)
		{
			byte = ((unsigned char *)evbit)[i];
			for (bit = 0; bit < 8; bit++)
			{
				if (byte & (1<<bit)) {
					printf("%s ", ev_names[i*8 + bit]);
				}
			}
		}
		printf("\n");
	}

	while (1)
	{
		/* 设置超时时间 */
		tv.tv_sec  = 5;
		tv.tv_usec = 0;
		
		/* 想监测哪些文件? */
		FD_ZERO(&readfds);    /* 先全部清零 */	
		FD_SET(fd, &readfds); /* 想监测fd */
		
		/* 函数原型为:
			int select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout);
         * 我们为了"read"而监测, 所以只需要提供readfds
		 */
		nfds = fd + 1; /* nfds 是最大的文件句柄+1, 注意: 不是文件个数, 这与poll不一样 */ 
		ret = select(nfds, &readfds, NULL, NULL, &tv);
		if (ret > 0)  /* 有文件可以提供数据了 */
		{
			/* 再次确认fd有数据 */
			if (FD_ISSET(fd, &readfds))
			{
				while (read(fd, &event, sizeof(event)) == sizeof(event))
				{
					printf("get event: type = 0x%x, code = 0x%x, value = 0x%x\n", event.type, event.code, event.value);
				}
			}
		}
		else if (ret == 0)  /* 超时 */
		{
			printf("time out\n");
		}
		else   /* -1: error */
		{
			printf("select err\n");
		}
	}

	return 0;
}

