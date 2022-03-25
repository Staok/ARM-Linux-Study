/* 一些 文件 IO、字符流收发 和 字符串处理 相关的 API 的收集积累和整理 */

/*
    有待收集的
        https://blog.csdn.net/qq_45396672/category_11169831.html
*/

/*

    注：最详细、全面的 函数参考 见：【算法-软件组件资料】\各种C标准库详解和用例 里面的！！！
    help 只能用于查看某个命令的用法，man 命令既可以查看命令的用法，还可以查看函数的详细介绍等等，
        比如想查看open函数的用法时，可以直接执行“man open”，发现这不是想要内容时再执行“man  2  open”
        在man命令中可以及时按“h”查看帮助信息了解快捷键。常用的快捷键是：
            f  往前翻一页
            b  往后翻一页
            /patten 往前搜
            ?patten 往后搜


*/


/*

********************** 常用 文件 IO API ***********************************
函数原型：
	int open(const char *pathname, int flags);
	int open(const char *pathname, int flags, mode_t mode);
	int close(int fd);
	函数说明：
		① pathname 表示打开文件的路径；
		② Flags 表示打开文件的方式，常用的有以下 6 种，
			a. O_RDWR 表示可读可写方式打开;
			b. O_RDONLY 表示只读方式打开;
			c. O_WRONLY 表示只写方式打开;
			d. O_APPEND 表示如果这个文件中本来是有内容的，则新写入的内容会接续到原来内容的后面;
			e. O_TRUNC 表示如果这个文件中本来是有内容的，则原来的内容会被丢弃，截断；
			f. O_CREAT 表示当前打开文件不存在，我们创建它并打开它，通常与 O_EXCL 结合使用，当没有文件时创建文件，有这个文件时会报错提醒我们；
		③ Mode 表示创建文件的权限，只有在 flags 中使用了 O_CREAT 时才有效，否则忽略。
		④ 返回值：打开成功返回文件描述符，失败将返回-1。
	头文件：
		#include <sys/types.h>
		#include <sys/stat.h>
		#include <fcntl.h>
		#include <unistd.h>
		
函数原型：
	ssize_t read(int fd, void *buf, size_t count);
	ssize_t write(int fd, const void *buf, size_t count);
	函数说明：
		read 函数会尝试从文件描述符 fd 中读取 count 个字节到缓冲区 buf 中
			返回值：成功时返回读到的字节数，0表示读到文件末尾了。如果返回字节数小于指定的字节数，不一定出错，有可能文件就剩这么多数据了。出错时返回 -1，并设置 errno 为合适值
		write 函数会尝试从缓冲区 buf 中读取 count 个字节，写到文件描述符 fd 中
			返回值：成功时返回写入的字节数。如果返回字节数小于指定的字节数，不一定出错，有可能是磁盘满了。出错时返回 -1，并设置 errno 为合适值
	头文件：
		#include <unistd.h>

函数原型：
	off_t lseek(int fd, off_t offset, int whence);
	函数说明：
		有的设备支持随机读写文件，例如磁盘，而有的则只支持顺序读写，例如管道、套接字和 FIFO。
		支持随机读写的设备，可以通过 lseek 函数移动读写位置。之后的读写操作，将会从这个新位置开始。
		参数：
			offset：目标位置，其偏移的参照点，由第三个参数 whence 决定
			whence：有效值是 SEEK_SET、SEEK_CUR、SEEK_END，含义如下：
                SEEK_SET 设置新的读写位置为从文件开头算起，偏移 offset 字节；
                SEEK_CUR 设置新的读写位置为从当前所在的位置算起，偏移 offset 字节，正值表示往文件尾部偏移，负值表示往文件头部偏移；
                SEEK_END 设置新的读写位置为从文件结尾算起，偏移 offset 字节，正值表示往文件尾部偏移，负值表示往文件头部偏移。
		返回值：
			操作成功则返回新的读写位置，否则返回 -1。按顺序读写的文件不支持 lseek 操作，对这类文件调用 lseek()，将返回-1，且 errno=ESPIPE。
	头文件：
		#include <unistd.h>

函数原型：TODO   
    fstat(fd_old, &stat)	

函数原型：
	int ioctl(int fd, unsigned long request, ...);
	函数说明：
		① fd 表示文件描述符；
		② request 表示与驱动程序交互的命令，用不同的命令控制驱动程序输出我们需要的数据；
		③ … 表示可变参数 arg，根据 request 命令，设备驱动程序返回输出的数据。
		④ 返回值：打开成功返回文件描述符，失败将返回-1。
	头文件：
		#include <sys/ioctl.h>

函数原型：		
	void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
	函数说明：
		① addr 表示指定映射的內存起始地址，通常设为 NULL 表示让系统自动选定地址，并在成功映射后返回该地址；
		② length 表示将文件中多大的内容映射到内存中；
		③ prot 表示映射区域的保护方式，可以为以下 4 种方式的组合
			a. PROT_EXEC 映射区域可被执行
			b. PROT_READ 映射区域可被读出
			c. PROT_WRITE 映射区域可被写入
			d. PROT_NONE 映射区域不能存取
		④ Flags 表示影响映射区域的不同特性，常用的有以下两种
			a. MAP_SHARED 表示对映射区域写入的数据会复制回文件内，原来的文件会改变。
			b. MAP_PRIVATE 表示对映射区域的操作会产生一个映射文件的复制，对此区域的任何修改都不会写回原来的文件内容中。
		⑤ 返回值：若成功映射，将返回指向映射的区域的指针，失败将返回-1。
        TODO：fd 和 offset 参数，这个函数还需要说明具体是干啥的
    头文件：
		#include <sys/mman.h>



********************** 常用 字符流收发 API ***********************************
函数原型：
	int printf(const char *format, ...);
	int fprintf(FILE *stream. const char *format, ...);
	int sprintf(char *str, const char *format, ...);
	
	int scanf(const char* format,...);
	int fscanf(FILE* stream,const char* format,...);
	int sscanf(char* s,const char* format,...);
	
	int fflush(FILE *stream);
	int fseek(FILE *stream, long offset, int fromwhere);
	
	int fgetc(FILE* stream);
	int getc(FILE* stream);
	int getchar();
	
	char* fgets(char* s,int n,FILE* stream);
	char* gets(char* s);



********************** 常用 字符串处理 API ***********************************
共同头文件：
		#include <string.h>

函数原型：
	字符串拷贝
	char *strcpy(char *dest, const char *src);
	char *strncpy(char *dest, const char *src, size_t n);
	
	字符串连接
	char *strcat(char *dest, const char *src);
	char *strncat(char *dest, const char *src, size_t n);
	
	字符串比较
	int strcmp(const char *s1,const char *s2);
	int strncmp(const char *s1,const char *s2,size_t n);
	
	字符串分割
	char *strtok(char *str, const char *delim);
	用法介绍：参数str指向欲分割的字符串，参数delim则为分割字符串，当strtok()在参数str的字符串中发现参数delim的分割字符时则会将该字符该为\0字符。
	第一次调用时，strtok()必须给予参数str字符串，往后的调用将参数str设置成NULL，每次调用成功返回下一个分割后的字符串指针。
	返回值：返回下一个分割后的字符串指针，如果已无从分割则返回NULL。
	例子：
	char s[] = "ab-cd : ef;gh:i-ijkl;mnop;qrs-tu;vwx-y;z";
    char *delim = "-;;";
    char *p;
    printf("%s", strtok(s,delim));
    while((p = strtok(NULL, delim)))
        printf("%s", p);



*/





