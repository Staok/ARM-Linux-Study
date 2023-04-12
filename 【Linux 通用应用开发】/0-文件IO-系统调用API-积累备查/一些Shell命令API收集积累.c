
注意，应用程序中可以使用 int system(const char * string); 函数实现 命令行操作，
	对于常见的如 运行其它程序、文件/目录操作 等等，相比于下面的 一个一个具体的 API 来说很方便。
	
	比较复杂的例子：
	
	执行一个应用程序并传参数：
		int a = 3;
		char str1[50];
		sprintf(str1, "omxplayer -o hdmi /home/pi/%04d.mp4 --loop", a);
		system(str1);
	
	执行 sh 脚本：
		system("bash playVideo.sh");
	
	传参数：
		int a = 3;
		char str1[50];
		sprintf(str1, "bash playVideo.sh %d", a);
		system(str1);

********************** 一些 Shell命令 API ***********************************
函数原型：
int rename(const char *oldpath, const char *newpath); 
    改变文件的名字或路径
	头文件：
		#include <stdio.h>

函数原型：
	int chmod( const char *filename, int pmode );
	int fchmod(int fd, mode_t mode);
	int chown(const char * path, uid_t owner, gid_t group);
	头文件：
		#include<sys/stat.h>
		#include <unistd.h>
		
函数原型：
	int unlink(const char* path);
	int link(const char* path1,const char* path2);
	int symlink(const char* path1,const char* path2);
	头文件：
		#include <unistd.h>
		
函数原型：
	int mkdir(const char* path,mode_t mode);
	int rmdir(const char* path);
	头文件：
		#include <sys/types.h>
		#include <sys/stat.h>
		#include <unistd.h>

函数原型：
	int chdir(const char* path);
	char* getcwd(char* buf,size_t size);
	头文件：
		#include <unistd.h>


