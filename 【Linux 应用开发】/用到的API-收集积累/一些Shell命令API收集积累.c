


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


