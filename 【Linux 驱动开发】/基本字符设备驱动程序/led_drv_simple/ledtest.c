#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


// ledtest /dev/myled on
// ledtest /dev/myled off

int main(int argc, char **argv)
{
	int fd;
	char status = 0;
	
	if (argc != 3)
	{
		printf("Usage: %s <dev> <on|off>\n", argv[0]);
		printf("  eg: %s /dev/myled on\n", argv[0]);
		printf("  eg: %s /dev/myled off\n", argv[0]);
		return -1;
	}
	// open
	fd = open(argv[1], O_RDWR);
	if (fd < 0)
	{
		printf("can not open %s\n", argv[0]);
		return -1;
	}

	// write
	if (strcmp(argv[2], "on") == 0)
	{
		status = 1;
	}

	write(fd, &status, 1);
	return 0;	
}

