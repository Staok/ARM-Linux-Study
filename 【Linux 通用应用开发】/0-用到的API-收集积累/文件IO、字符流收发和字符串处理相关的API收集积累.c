/* 一些 文件 IO、字符流收发 和 字符串处理 相关的 API 的收集积累和整理 */
/* 文档构建始于 2020/8/27 */

/*
    有待收集的
        https://blog.csdn.net/qq_45396672/category_11169831.html
*/



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
			e. O_TRUNC 表示如果这个文件中本来是有内容的，则原来的内容会被丢弃；
			f. O_CREAT 表示当前打开文件不存在，我们创建它并打开它；若与 O_EXCL 结合使用，当没有文件时创建文件，有这个文件时会报错提醒我们；
		③ Mode 表示创建文件的权限，只有在 flags 中使用了 O_CREAT 时才有效，否则忽略；有多种权限，用时现查。
            mode_t 可参考 https://blog.csdn.net/sjc214/article/details/47905619
		④ 返回值：打开成功返回文件描述符，失败将返回 -1 或其它，有多种错误类型，用时现查。
	头文件：
		#include <sys/types.h>
		#include <sys/stat.h>
		#include <fcntl.h>
		#include <unistd.h>
    重要说明：Linux 下 fopen 与 open 的区别
        参考 
            https://blog.csdn.net/u012803067/article/details/59053962
            https://www.cnblogs.com/hnrainll/archive/2011/09/16/2178706.html
		一般用 fopen 打开普通文件，用 open 打开设备文件，fopen 是标准 c 里的，而 open 是 linux 的系统调用。
        fopen 与 open：前者有缓冲，后者无缓冲；前者与 fread, fwrite 等配合使用， 后者与 read, write 等配合使用。
        fopen 是在 open 的基础上扩充而来的，根据要打开的文件类型（实际存在的文件 还是 驱动文件等虚拟文件）来选择。
        
        ### fopen参数说明
        | 参数 | 说明                                                         |
        |  --  | ------------------------------------------------------------ |
        |  r   | 以只读方式打开文件，该文件必须存在。                         |
        |  r+  | 以可读写方式打开文件，该文件必须存在。                       |
        | rb+  | 读写打开一个二进制文件，允许读写数据，文件必须存在。         |
        |  w   | 打开只写文件，若文件存在则文件长度清为0，即该文件内容会消失。若文件不存在则建立该文件。 |
        |  w+  | 打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。 |
        |  a   | 以追加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。（EOF符保留） |
        |  a+  | 以追加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。 （原来的EOF符不保留） |
        |  wb  | 只写打开或新建一个二进制文件；只允许写数据。                 |
        | wb+  | 读写打开或建立一个二进制文件，允许读和写。                   |
        | ab+  | 读写打开一个二进制文件，允许读或在文件末追加数据。           |
        |  wx  | 创建文本文件,只允许写入数据.[C11]                            |
        | wbx  | 创建一个二进制文件,只允许写入数据.[C11]                      |
        | w+x  | 创建一个文本文件,允许读写.[C11]                              |
        | wb+x | 创建一个二进制文件,允许读写.[C11]                            |
        | w+bx | 和"wb+x"相同[C11]                                            |

        > 以x结尾的模式为独占模式,文件已存在或者无法创建(一般是路径不正确)都会导致fopen失败.文件以操作系统支持的独占模式打开.[C11]


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

函数原型：  
    int fstat(int fd, struct stat *buf);
    函数说明：
        获取文件 状态/属性 信息，通过 struct stat *buf 返回，执行成功返回 0，失败返回 -1。
        struct stat buf 里有很多信息，比如 buf.st_size 是文件大小。
    头文件：
        #include <sys/stat.h>
		#include <unistd.h>

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
	void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
	函数说明：
		① addr 表示指定映射的內存起始地址，通常设为 NULL 表示让系统自动选定地址，在成功映射后返回该地址；
		② length 表示将文件 fd 中多大的内容映射到内存中；
		③ prot 表示映射区域的保护方式，可以为以下 4 种方式的组合
			a. PROT_EXEC 映射区域 *addr 可被执行
			b. PROT_READ 映射区域可被读出
			c. PROT_WRITE 映射区域可被写入
			d. PROT_NONE 映射区域不能存取
		④ Flags 表示影响映射区域的不同特性，常用的有以下两种
			a. MAP_SHARED 表示对映射区域 *addr 写入的数据会复制回文件 fd 内，原来的文件 fd 会改变；
                而且允许其他映射该文件的进程共享。
			b. MAP_PRIVATE 表示对映射区域的操作会产生一个映射文件的复制，对此区域的任何修改都不会写回原来的文件内容中。
		⑤ fd 为被映射的文件。
        ⑥ offset 文件映射的偏移量，通常为 0。
        返回值：若成功映射，将返回指向映射的区域的指针，失败将返回-1。
        例子：
            static unsigned char *fb_base = (unsigned char *)mmap(NULL , screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
            ...
            munmap(fb_base , screen_size);
    头文件：
		#include <sys/mman.h>
        #include <unistd.h>
    
    用完后，取消 内存重映射 int munmap(void *start, size_t length); start 是内存起始地址，length 是大小
    
    使用 mmap 来对一个文件（实体文件或块设备驱动文件）重映射到一块内存（虚拟内存），
    从而让访问该文件内容时候就像读写内存一样（指针移动和读写），
    常用在文件内容的搬运、屏幕的 Framebuffer（将屏幕驱动文件重映射到一块内存，然后读写内存就是读写屏幕）。
    
    内存映射，就是将内核空间的一段内存区域映射到用户空间，映射成功后，
    用户对这段内存区域的修改可以直接反映到内核空间，
    相反，内核空间对这段区域的修改也直接反映用户空间。
    那么对于内核空间和用户空间两者之间需要大量数据传输等操作的时候效率是非常高的。

    详解mmap原理：https://zhuanlan.zhihu.com/p/465336136


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
	int getchar(); 相当于 getc(stdin);
	
	char* fgets(char* s,int n,FILE* stream);
	char* gets(char* s);
    
    int fputs(const char *s, FILE *stream);
    
    int fputc(int char, FILE *stream);



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


