引自 [embedded-notes/linux.md at master · xiaowenxia/embedded-notes (github.com)](https://github.com/xiaowenxia/embedded-notes/blob/master/linux.md)。

### linux常用的系统调用函数

* [进程控制函数](#进程控制函数)
* [文件操作函数](#文件操作函数)
* [文件系统操作函数](#文件系统操作函数)
* [系统控制函数](#系统控制函数)
* [内存管理函数](#内存管理函数)
* [网络管理函数](#网络管理函数)
* [socket函数](#socket函数)
* [用户管理函数](#用户管理函数)
* [进程间通信函数](#进程间通信函数)
* [信号相关函数](#信号相关函数)
* [消息相关函数](#消息相关函数)
* [管道相关函数](#管道相关函数)
* [信号量相关函数](#信号量相关函数)
* [共享内存相关函数](#共享内存相关函数)

#### 进程控制函数

<table>
   <tr style="color:red">
      <td>fork</td>
      <td>创建一个新进程</td>
   </tr>
   <tr style="color:red">
      <td>clone</td>
      <td>按指定条件创建子进程</td>
   </tr>
   <tr style="color:red">
      <td>execve</td>
      <td>运行可执行文件</td>
   </tr>
   <tr style="color:red">
      <td>exit</td>
      <td>中止进程</td>
   </tr>
   <tr>
      <td>_exit</td>
      <td>立即中止当前进程</td>
   </tr>
   <tr>
      <td>getdtablesize</td>
      <td>进程所能打开的最大文件数</td>
   </tr>
   <tr>
      <td>getpgid</td>
      <td>获取指定进程组标识号</td>
   </tr>
   <tr>
      <td>setpgid</td>
      <td>设置指定进程组标志号</td>
   </tr>
   <tr>
      <td>getpgrp</td>
      <td>获取当前进程组标识号</td>
   </tr>
   <tr>
      <td>setpgrp</td>
      <td>设置当前进程组标志号</td>
    </tr>
      <tr style="color:red">
          <td>getpid</td>
          <td>获取进程标识号</td>
    </tr>
      <tr>
          <td>getppid</td>
          <td>获取父进程标识号</td>
    </tr>
      <tr style="color:red">
          <td>getpriority</td>
          <td>获取调度优先级</td>
    </tr>
      <tr style="color:red">
          <td>setpriority</td>
          <td>设置调度优先级</td>
    </tr>
      <tr>
          <td>modify_ldt</td>
          <td>读写进程的本地描述表</td>
    </tr>
      <tr>
          <td>nanosleep</td>
          <td>使进程睡眠指定的时间</td>
    </tr>
      <tr>
          <td>nice</td>
          <td>改变分时进程的优先级</td>
    </tr>
      <tr style="color:red">
          <td>pause</td>
          <td>挂起进程，等待信号</td>
    </tr>
      <tr>
          <td>personality</td>
          <td>设置进程运行域</td>
    </tr>
      <tr style="color:red">
          <td>prctl</td>
          <td>对进程进行特定操作</td>
    </tr>
      <tr>
          <td>ptrace</td>
          <td>进程跟踪</td>
    </tr>
      <tr>
          <td>sched_get_priority_max</td>
          <td>取得静态优先级的上限</td>
    </tr>
      <tr>
          <td>sched_get_priority_min</td>
          <td>取得静态优先级的下限</td>
    </tr>
      <tr>
          <td>sched_getparam</td>
          <td>取得进程的调度参数</td>
    </tr>
      <tr>
          <td>sched_getscheduler</td>
          <td>取得指定进程的调度策略</td>
    </tr>
      <tr>
          <td>sched_rr_get_interval</td>
          <td>取得按RR算法调度的实时进程的时间片长度</td>
    </tr>
      <tr>
          <td>sched_setparam</td>
          <td>设置进程的调度参数</td>
    </tr>
      <tr>
          <td>sched_setscheduler</td>
          <td>设置指定进程的调度策略和参数</td>
    </tr>
      <tr>
          <td>sched_yield</td>
          <td>进程主动让出处理器,并将自己等候调度队列队尾</td>
    </tr>
      <tr>
          <td>vfork</td>
          <td>创建一个子进程，以供执行新程序，常与execve等同时使用</td>
    </tr>
      <tr style="color:red">
          <td>wait</td>
          <td>等待子进程终止</td>
    </tr>
      <tr>
          <td>wait3</td>
          <td>参见wait</td>
    </tr>
      <tr>
          <td>waitpid</td>
          <td>等待指定子进程终止</td>
    </tr>
      <tr>
          <td>wait4</td>
          <td>参见waitpid</td>
    </tr>
      <tr>
          <td>capget</td>
          <td>获取进程权限</td>
    </tr>
      <tr>
          <td>capset</td>
          <td>设置进程权限</td>
    </tr>
      <tr>
          <td>getsid</td>
          <td>获取会晤标识号</td>
    </tr>
      <tr>
          <td>setsid</td>
          <td>设置会晤标识号</td>
      </tr>
</table>


#### 文件操作函数

<table>
  <tr style="color:red">
      <td>fcntl</td>
      <td>文件控制</td>
  </tr>
  <tr style="color:red">
      <td>open</td>
      <td>打开文件</td>
  </tr>
  <tr style="color:red">
      <td>creat</td>
      <td>创建新文件</td>
  </tr>
  <tr style="color:red">
      <td>close</td>
      <td>关闭文件描述字</td>
  </tr>
  <tr style="color:red">
      <td>read</td>
      <td>读文件</td>
  </tr>
  <tr style="color:red">
      <td>write</td>
      <td>写文件</td>
  </tr>
  <tr>
      <td>readv</td>
      <td>从文件读入数据到缓冲数组中</td>
  </tr>
  <tr>
      <td>writev</td>
      <td>将缓冲数组里的数据写入文件</td>
  </tr>
  <tr>
      <td>pread</td>
      <td>对文件随机读</td>
  </tr>
  <tr>
      <td>pwrite</td>
      <td>对文件随机写</td>
  </tr>
  <tr style="color:red">
      <td>lseek</td>
      <td>移动文件指针</td>
  </tr>
  <tr>
      <td>_llseek</td>
      <td>在64位地址空间里移动文件指针</td>
  </tr>
  <tr>
      <td>dup</td>
      <td>复制已打开的文件描述字</td>
  </tr>
  <tr>
      <td>dup2</td>
      <td>按指定条件复制文件描述字</td>
  </tr>
  <tr style="color:red">
      <td>flock</td>
      <td>文件加/解锁</td>
  </tr>
  <tr style="color:red">
      <td>poll</td>
      <td>I/O多路转换</td>
  </tr>
  <tr>
      <td>truncate</td>
      <td>截断文件</td>
  </tr>
  <tr>
      <td>ftruncate</td>
      <td>参见truncate</td>
  </tr>
  <tr>
      <td>umask</td>
      <td>设置文件权限掩码</td>
  </tr>
  <tr style="color:red">
      <td>fsync</td>
      <td>把文件在内存中的部分写回磁盘</td>
  </tr>
</table>


#### 文件系统操作函数

<table>
  <tr style="color:red">
      <td>access</td>
      <td>确定文件的可存取性</td>
  </tr>
  <tr style="color:red">
      <td>chdir</td>
      <td>改变当前工作目录</td>
  </tr>
  <tr>
      <td>fchdir</td>
      <td>参见chdir</td>
  </tr>
  <tr style="color:red">
      <td>chmod</td>
      <td>改变文件方式</td>
  </tr>
  <tr>
      <td>fchmod</td>
      <td>参见chmod</td>
  </tr>
  <tr>
      <td>chown</td>
      <td>改变文件的属主或用户组</td>
  </tr>
  <tr>
      <td>fchown</td>
      <td>参见chown</td>
  </tr>
  <tr>
      <td>lchown</td>
      <td>参见chown</td>
  </tr>
  <tr style="color:red">
      <td>chroot</td>
      <td>改变根目录</td>
  </tr>
  <tr style="color:red">
      <td>stat</td>
      <td>取文件状态信息</td>
  </tr>
  <tr>
      <td>lstat</td>
      <td>参见stat</td>
  </tr>
  <tr>
      <td>fstat</td>
      <td>参见stat</td>
  </tr>
  <tr style="color:red">
      <td>statfs</td>
      <td>取文件系统信息</td>
  </tr>
  <tr>
      <td>fstatfs</td>
      <td>参见statfs</td>
  </tr>
  <tr style="color:red">
      <td>readdir</td>
      <td>读取目录项</td>
  </tr>
  <tr>
      <td>getdents</td>
      <td>读取目录项</td>
  </tr>
  <tr style="color:red">
      <td>mkdir</td>
      <td>创建目录</td>
  </tr>
  <tr style="color:red">
      <td>mknod</td>
      <td>创建索引节点</td>
  </tr>
  <tr style="color:red">
      <td>rmdir</td>
      <td>删除目录</td>
  </tr>
  <tr style="color:red">
      <td>rename</td>
      <td>文件改名</td>
  </tr>
  <tr style="color:red">
      <td>link</td>
      <td>创建链接</td>
  </tr>
  <tr style="color:red">
      <td>symlink</td>
      <td>创建符号链接</td>
  </tr>
  <tr style="color:red">
      <td>unlink</td>
      <td>删除链接</td>
  </tr>
  <tr>
      <td>readlink</td>
      <td>读符号链接的值</td>
  </tr>
  <tr>
      <td>mount</td>
      <td>安装文件系统</td>
  </tr>
  <tr>
      <td>umount</td>
      <td>卸下文件系统</td>
  </tr>
  <tr style="color:red">
      <td>ustat</td>
      <td>取文件系统信息</td>
  </tr>
  <tr>
      <td>utime</td>
      <td>改变文件的访问修改时间</td>
  </tr>
  <tr>
      <td>utimes</td>
      <td>参见utime</td>
  </tr>
  <tr>
      <td>quotactl</td>
      <td>控制磁盘配额</td>
  </tr>
</table>


#### 系统控制函数

<table>
  <tr style="color:red">
      <td>ioctl</td>
      <td>I/O总控制函数</td>
  </tr>
  <tr>
      <td>_sysctl</td>
      <td>读/写系统参数</td>
  </tr>
  <tr>
      <td>acct</td>
      <td>启用或禁止进程记账</td>
  </tr>
  <tr>
      <td>getrlimit</td>
      <td>获取系统资源上限</td>
  </tr>
  <tr>
      <td>setrlimit</td>
      <td>设置系统资源上限</td>
  </tr>
  <tr>
      <td>getrusage</td>
      <td>获取系统资源使用情况</td>
  </tr>
  <tr>
      <td>uselib</td>
      <td>选择要使用的二进制函数库</td>
  </tr>
  <tr>
      <td>ioperm</td>
      <td>设置端口I/O权限</td>
  </tr>
  <tr>
      <td>iopl</td>
      <td>改变进程I/O权限级别</td>
  </tr>
  <tr>
      <td>outb</td>
      <td>低级端口操作</td>
  </tr>
  <tr style="color:red">
      <td>reboot</td>
      <td>重新启动</td>
  </tr>
  <tr>
      <td>swapon</td>
      <td>打开交换文件和设备</td>
  </tr>
  <tr>
      <td>swapoff</td>
      <td>关闭交换文件和设备</td>
  </tr>
  <tr>
      <td>bdflush</td>
      <td>控制bdflush守护进程</td>
  </tr>
  <tr>
      <td>sysfs</td>
      <td>取核心支持的文件系统类型</td>
  </tr>
  <tr>
      <td>sysinfo</td>
      <td>取得系统信息</td>
  </tr>
  <tr>
      <td>adjtimex</td>
      <td>调整系统时钟</td>
  </tr>
  <tr>
      <td>alarm</td>
      <td>设置进程的闹钟</td>
  </tr>
  <tr>
      <td>getitimer</td>
      <td>获取计时器值</td>
  </tr>
  <tr>
      <td>setitimer</td>
      <td>设置计时器值</td>
  </tr>
  <tr>
      <td>gettimeofday</td>
      <td>取时间和时区</td>
  </tr>
  <tr>
      <td>settimeofday</td>
      <td>设置时间和时区</td>
  </tr>
  <tr style="color:red">
      <td>stime</td>
      <td>设置系统日期和时间</td>
  </tr>
  <tr style="color:red">
      <td>time</td>
      <td>取得系统时间</td>
  </tr>
  <tr>
      <td>times</td>
      <td>取进程运行时间</td>
  </tr>
  <tr style="color:red">
      <td>uname</td>
      <td>获取当前UNIX系统的名称、版本和主机等信息</td>
  </tr>
  <tr>
      <td>vhangup</td>
      <td>挂起当前终端</td>
  </tr>
  <tr>
      <td>nfsservctl</td>
      <td>对NFS守护进程进行控制</td>
  </tr>
  <tr>
      <td>vm86</td>
      <td>进入模拟8086模式</td>
  </tr>
  <tr>
      <td>create_module</td>
      <td>创建可装载的模块项</td>
  </tr>
  <tr>
      <td>delete_module</td>
      <td>删除可装载的模块项</td>
  </tr>
  <tr>
      <td>init_module</td>
      <td>初始化模块</td>
  </tr>
  <tr>
      <td>query_module</td>
      <td>查询模块信息</td>
  </tr>
  <tr>
      <td>*get_kernel_syms</td>
      <td>取得核心符号,已被query_module代替</td>
  </tr>
</table>


#### 内存管理函数

<table>
  <tr>
      <td>brk</td>
      <td>改变数据段空间的分配</td>
  </tr>
  <tr>
      <td>sbrk</td>
      <td>参见brk</td>
  </tr>
  <tr>
      <td>mlock</td>
      <td>内存页面加锁</td>
  </tr>
  <tr>
      <td>munlock</td>
      <td>内存页面解锁</td>
  </tr>
  <tr>
      <td>mlockall</td>
      <td>调用进程所有内存页面加锁</td>
  </tr>
    <tr>
      <td>munlockall</td>
      <td>调用进程所有内存页面解锁</td>
  </tr>
  <tr>
      <td>mmap</td>
      <td>映射虚拟内存页</td>
  </tr>
  <tr>
      <td>munmap</td>
      <td>去除内存页映射</td>
  </tr>
  <tr>
      <td>mremap</td>
      <td>重新映射虚拟内存地址</td>
  </tr>
  <tr>
      <td>msync</td>
      <td>将映射内存中的数据写回磁盘</td>
  </tr>
  <tr>
      <td>mprotect</td>
      <td>设置内存映像保护</td>
  </tr>
  <tr>
      <td>getpagesize</td>
      <td>获取页面大小</td>
  </tr>
  <tr style="color:red">
      <td>sync</td>
      <td>将内存缓冲区数据写回硬盘</td>
  </tr>
  <tr>
      <td>cacheflush</td>
      <td>dddd将指定缓冲区中的内容写回磁盘dd</td>
  </tr>
</table>


#### 网络管理函数

<table>
  <tr style="color:red">
      <td>getdomainname</td>
      <td>取域名</td>
  </tr>
  <tr style="color:red">
      <td>setdomainname</td>
      <td>设置域名</td>
  </tr>
  <tr>
      <td>gethostid</td>
      <td>获取主机标识号</td>
  </tr>
  <tr>
      <td>sethostid</td>
      <td>设置主机标识号</td>
  </tr>
  <tr style="color:red">
      <td>gethostname</td>
      <td>获取本主机名称</td>
  </tr>
  <tr style="color:red">
      <td>sethostname</td>
      <td>设置主机名称</td>
  </tr>
</table>


#### socket函数

<table>
  <tr>
      <td>socketcall</td>
      <td>socket系统调用</td>
  </tr>
  <tr style="color:red">
      <td>socket</td>
      <td>建立socket</td>
  </tr>
  <tr style="color:red">
      <td>bind</td>
      <td>绑定socket到端口</td>
  </tr>
  <tr style="color:red">
      <td>connect</td>
      <td>连接远程主机</td>
  </tr>
  <tr style="color:red">
      <td>accept</td>
      <td>响应socket连接请求</td>
  </tr style="color:red">
    <tr>
      <td>send</td>
      <td>通过socket发送信息</td>
  </tr>
  <tr style="color:red">
      <td>sendto</td>
      <td>发送UDP信息</td>
  </tr>
  <tr>
      <td>sendmsg</td>
      <td>参见send</td>
  </tr>
  <tr style="color:red">
      <td>recv</td>
      <td>通过socket接收信息</td>
  </tr>
    <tr style="color:red">
      <td>recvfrom</td>
      <td>接收UDP信息</td>
  </tr>
  <tr>
      <td>recvmsg</td>
      <td>参见recv</td>
  </tr>
  <tr style="color:red">
      <td>listen</td>
      <td>监听socket端口</td>
  </tr>
  <tr style="color:red">
      <td>select</td>
      <td>对多路同步I/O进行轮询</td>
  </tr>
  <tr style="color:red">
      <td>close</td>
      <td>关闭socket上的连接</td>
  </tr>
  <tr>
      <td>getsockname</td>
      <td>取得本地socket名字</td>
  </tr>
  <tr>
      <td>getpeername</td>
      <td>获取通信对方的socket名字</td>
  </tr>
  <tr style="color:red">
      <td>getsockopt</td>
      <td>取端口设置</td>
  </tr>
  <tr style="color:red">
      <td>setsockopt</td>
      <td>设置端口参数</td>
  </tr>
  <tr>
      <td>sendfile</td>
      <td>在文件或端口间传输数据</td>
  </tr>
  <tr>
      <td>socketpair</td>
      <td>创建一对已联接的无名socket</td>
  </tr>
</table>


#### 用户管理函数

<table>
  <tr>
      <td>getuid</td>
      <td>获取用户标识号</td>
  </tr>
  <tr>
      <td>setuid</td>
      <td>设置用户标志号</td>
  </tr>
  <tr>
      <td>getgid</td>
      <td>获取组标识号</td>
  </tr>
  <tr>
      <td>setgid</td>
      <td>设置组标志号</td>
  </tr>
  <tr>
      <td>getegid</td>
      <td>获取有效组标识号</td>
  </tr>
  <tr>
      <td>setegid</td>
      <td>设置有效组标识号</td>
  </tr>
  <tr>
      <td>geteuid</td>
      <td>获取有效用户标识号</td>
  </tr>
  <tr>
      <td>seteuid</td>
      <td>设置有效用户标识号</td>
  </tr>
  <tr>
      <td>setregid</td>
      <td>分别设置真实和有效的的组标识号</td>
  </tr>
  <tr>
      <td>setreuid</td>
      <td>分别设置真实和有效的用户标识号</td>
  </tr>
  <tr>
      <td>getresgid</td>
      <td>分别获取真实的,有效的和保存过的组标识号</td>
  </tr>
  <tr>
      <td>setresgid</td>
      <td>分别设置真实的,有效的和保存过的组标识号</td>
  </tr>
  <tr>
      <td>getresuid</td>
      <td>分别获取真实的,有效的和保存过的用户标识号</td>
  </tr>
  <tr>
      <td>setresuid</td>
      <td>分别设置真实的,有效的和保存过的用户标识号</td>
  </tr>
  <tr>
      <td>setfsgid</td>
      <td>设置文件系统检查时使用的组标识号</td>
  </tr>
  <tr>
      <td>setfsuid</td>
      <td>设置文件系统检查时使用的用户标识号</td>
  </tr>
  <tr>
      <td>getgroups</td>
      <td>获取后补组标志清单</td>
  </tr>
  <tr>
      <td>setgroups</td>
      <td>设置后补组标志清单</td>
  </tr>
</table>


#### 进程间通信函数

<table>
  <tr style="color:red">
      <td>ipc</td>
      <td>进程间通信总控制调用</td>
  </tr>
</table>


##### 信号相关函数

<table>
  <tr>
      <td>sigaction</td>
      <td>设置对指定信号的处理方法</td>
  </tr>
  <tr>
      <td>sigprocmask</td>
      <td>根据参数对信号集中的信号执行阻塞/解除阻塞等操作</td>
  </tr>
  <tr>
      <td>sigpending</td>
      <td>为指定的被阻塞信号设置队列</td>
  </tr>
  <tr>
      <td>sigsuspend</td>
      <td>挂起进程等待特定信号</td>
  </tr>
  <tr style="color:red">
      <td>signal</td>
      <td>参见signal</td>
  </tr>
  <tr style="color:red">
      <td>kill</td>
      <td>向进程或进程组发信号</td>
  </tr>
  <tr>
      <td>*sigblock</td>
      <td>向被阻塞信号掩码中添加信号,已被sigprocmask代替</td>
  </tr>
  <tr>
      <td>*siggetmask</td>
      <td>取得现有阻塞信号掩码,已被sigprocmask代替</td>
  </tr>
  <tr>
      <td>*sigsetmask</td>
      <td>用给定信号掩码替换现有阻塞信号掩码,已被sigprocmask代替</td>
  </tr>
  <tr>
      <td>*sigmask</td>
      <td>将给定的信号转化为掩码,已被sigprocmask代替</td>
  </tr>
  <tr>
      <td>*sigpause</td>
      <td>作用同sigsuspend,已被sigsuspend代替</td>
  </tr>
  <tr>
      <td>sigvec</td>
      <td>为兼容BSD而设的信号处理函数,作用类似sigaction</td>
  </tr>
  <tr>
      <td>ssetmask</td>
      <td>ANSI C的信号处理函数,作用类似sigaction</td>
  </tr>
</table>


##### 管道相关函数

<table style="color:red">
  <tr>
      <td>pipe</td>
      <td>创建管道</td>
  </tr>
</table>
补充：还有命名管道



##### 信号量相关函数

<table style="color:red">
  <tr>
      <td>semctl</td>
      <td>信号量控制</td>
  </tr>
  <tr>
      <td>semget</td>
      <td>获取一组信号量</td>
  </tr>
  <tr>
      <td>semop</td>
      <td>信号量操作</td>
  </tr>
</table>


##### 消息相关函数

<table style="color:red">
  <tr>
      <td>msgctl</td>
      <td>消息控制操作</td>
  </tr>
  <tr>
      <td>msgget</td>
      <td>获取消息队列</td>
  </tr>
  <tr>
      <td>msgsnd</td>
      <td>发消息</td>
  </tr>
  <tr>
      <td>msgrcv</td>
      <td>取消息</td>
  </tr>
</table>

即 “消息队列”。



##### 共享内存相关函数

<table style="color:red">
  <tr>
      <td>shmctl</td>
      <td>控制共享内存</td>
  </tr>
  <tr>
      <td>shmget</td>
      <td>获取共享内存</td>
  </tr>
  <tr>
      <td>shmat</td>
      <td>连接共享内存</td>
  </tr>
  <tr>
      <td>shmdt</td>
      <td>拆卸共享内存</td>
  </tr>
</table>


### 