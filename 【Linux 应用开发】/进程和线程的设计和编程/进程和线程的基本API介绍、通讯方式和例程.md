# 进程 和 线程 的基本 API 介绍、通讯方式 和 例程

大量参考 100ask、网络文章等资料（参考源均以给出，侵删），这里参考网络文章和官方文档并做多处横向对比，形成系统性 一文全解，给出保姆级别的参考，则避免 同质化。

## 查看进程/线程/系统运行状况等的命令

- [主线剧情02-ARM-Linux基础学习记录_Real-Staok的博客-CSDN博客](https://blog.csdn.net/Staokgo/article/details/123693110) 里面的 `Linux Shell` 一节 的 **任务后台执行 / 任务&进程查看** 部分。
- [关于Linux下进程的详解【进程查看与管理】 - AshJo - 博客园 (cnblogs.com)](https://www.cnblogs.com/ashjo009/p/11912563.html)。
- [linux top命令查看内存及多核CPU的使用讲述 - tamatama - 博客园 (cnblogs.com)](https://www.cnblogs.com/tamatama/p/13044402.html)。
- [Linux vmstat命令实战详解_浮生忆梦的博客-CSDN博客_vmstat](https://blog.csdn.net/m0_38110132/article/details/84190319)。
- etc.

## 前置了解和其他

这里仅仅是将我随机看到的放在这里，网搜会有更多/更好的文章，多看看。这里也是本文的参考源之一。

- [进程 & 线程相关知识 - blcblc - 博客园 (cnblogs.com)](https://www.cnblogs.com/charlesblc/p/6135666.html)，基本概念 和其 异同 的介绍。
- [ linux基础——linux进程与线程的区别与联系_yexz的博客-CSDN博客](https://blog.csdn.net/a987073381/article/details/52054875)。
- [操作系统基础知识复习总结_loserChen.的博客-CSDN博客_操作系统基础知识](https://blog.csdn.net/qq_35564813/article/details/80651259)、[操作系统基础_wang德华的博客-CSDN博客](https://blog.csdn.net/weixin_43823756/article/details/108260982)、[操作系统基础知识整理_零分分分分的博客-CSDN博客_操作系统基础知识](https://blog.csdn.net/qq_33399567/article/details/106022913)、[操作系统基础知识总结整理_EasyChill的博客-CSDN博客_操作系统基础知识总结](https://blog.csdn.net/Song_JiangTao/article/details/79670805)。

## 一些进程/线程调试经验

设计模式 / 分配策略 相关：

- 进程和线程的分配策略（里面的 “启发任务分配的规则” 和 “进程 和 线程 设计经验参考” 一节） 那篇文章（包括本篇 都传到 linux study git 仓库）。
- [从内核角度分析：当linux多线程遭遇Linux多进程 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/366187163)。
- 一些 线程池 编写经验 [linux基础——经典线程同步问题解析及编程实现_yexz的博客-CSDN博客](https://blog.csdn.net/a987073381/article/details/52081857)。
- 设计模式 [POSIX多线程程序设计（第4章：使用线程的几种方式）_瓦釜苑-CSDN博客_posix多线程程序设计](https://blog.csdn.net/lincoln_2012/article/details/47979675)。
- etc.

调试相关：

- [Linux进程崩溃原调试_guotianqing的博客-CSDN博客](https://blog.csdn.net/guotianqing/article/details/108409878)。
- etc.

## Linux 进程

参考：TODO 看这里的，总结到下面

- [如何在Linux下的进行多进程编程（初步） - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/90476128)。
- [Linux 进程详解 - 程序员大本营 (pianshen.com)](https://www.pianshen.com/article/3385597611/)。
- [Linux进程基础教程详解_Linux_脚本之家 (jb51.net)](https://www.jb51.net/article/111091.htm)。
- [Linux进程解析_deep_explore的博客-CSDN博客](https://blog.csdn.net/deep_explore/article/details/6301044)。
- [Linux应用程序中出现两次fork的解释_leng_que的博客-CSDN博客_两次fork](https://blog.csdn.net/leng_que/article/details/44084237)。
- [【Linux】如何创建daemon进程&fork一次和fork两次有什么区别_pointer_y的博客-CSDN博客](https://blog.csdn.net/pointer_y/article/details/58147568)。

### 各个 API 原型介绍



### 使用这些 API 的例程



### 进程间通讯（IPC）

参考 / 引用：

- [linux基础——linux进程间通信（IPC）机制总结_千里之行，始于足下-CSDN博客](https://blog.csdn.net/a987073381/article/details/52006729)。TODO 待总结和验证，写出自己的验证程序。
- [Linux IPC总结（全）_xuexingyang的博客-CSDN博客_linuxipc](https://blog.csdn.net/dxdxsmy/article/details/6653189)。TODO 待总结和验证，写出自己的验证程序。
- TODO 有待下载 [Linux进程间通信-详解(经典)_linux进程间通信,linux进程间通信-硬件开发文档类资源-CSDN文库](https://download.csdn.net/download/jmq_0000/3554996)。

UNIX 进程间通信方式:：包括管道(PIPE)，有名管道(FIFO)，和信号(Signal)；System V 进程通信方式：包括信号量(Semaphore)，消息队列(Message Queue)，和共享内存(Shared Memory)。这两种都是早期 UNIX 的 IPC，还有 套接字 和 内存映射，这基本的 八种方式，Linux 则都继承了下来。

总结起来：管道、命名管道、信号、信号量、消息队列、共享内存、内存映射 和 套接字。

#### 管道（Pipe）

管道是一种半双工的通信方式，是内核的一段缓冲区，数据只能单向流动，一端写和一端读，而且只能在具有亲缘关系(父子进程)的进程间使用。另外管道传送的是无格式的字节流，并且管道缓冲区的大小是有限的（管道缓冲区存在于内存中，在管道创建时，为缓冲区分配一个页面大小）。

半双工（双向通讯，同一时刻只能有一方发和一方收）；用于父子、兄弟之间。

#### 命名管道（FIFO）

也有叫有名管道。有名管道也是半双工的通信方式，但是它允许无亲缘关系进程间的通信。

#### 信号（Signal）

信号是一种比较复杂的通信方式，用于通知接收进程某个事件已经发生。

信号是异步的，一个进程不必通过任何操作来等待信号的到达，事实上，进程也不知道信号到底什么时候到达。信号是进程间通信机制中唯一的异步通信机制，可以看作是异步通知。

信号可以直接进行用户空间进程和内核进程（比如驱动程序）之间的交互，内核进程可以利用它来通知用户空间进程发生了哪些事件。还可以作为进程间通信或修改行为的一种方式，明确地由一个进程发送给另一个进程。一个信号的产生叫生成，接收到一个信号叫捕获。

#### 信号量（Semaphore）

信号量是一个计数器，可以用来控制多个进程对共享资源的访问。它常作为一种锁机制，防止某进程正在访问共享资源时，其他进程也访问该资源。因此，主要作为进程间以及同一进程内不同线程之间的同步手段。

常用来处理临界资源的访问同步问题。临界资源：为某一时刻只能由一个进程或线程操作的资源。

#### 消息列队（Message Queue）

消息队列是由消息的链表，存放在内核中并由消息队列标识符标识。消息队列克服了信号传递信息少、管道只能承载无格式字节流以及缓冲区大小受限等缺点。消息链表存于内核，每个消息队列由消息队列标识符标识；与管道不同的是，消息队列存放在内核中，只有在内核重启时才能删除一个消息队列；消息队列的大小受限制。

消息队列 具有特定的格式以及特定的优先级。有写权限的进程可以向消息队列中添加新消息；有读权限的进程则可以从消息队列中读走消息。

#### 共享内存（Shared Memory）

可以说是最有用的进程间通信方式，也是最快的 IPC 形式。

共享内存就是映射一段能被其他进程所访问的内存，这段共享内存由一个进程创建，但多个进程都可以访问。共享内存是最快的 IPC 方式，它是针对其他进程间通信方式运行效率低而专门设计的。它往往与其他通信机制，如信号量，配合使用，来实现进程间的同步和通信。

两个进程通过页表将虚拟地址映射到物理地址时，在物理地址中有一块共同的内存区，即共享内存，这块内存可以被两个进程同时看到。这样当一个进程进行写操作，另一个进程读操作就可以实现进程间通信。但是，我们要确保一个进程在写的时候不能被读，因此我们使用信号量来实现同步与互斥。

Proc A 进程给内存中写数据，Proc B 进程从内存中读取数据，在此期间一共发生了两次复制：Proc A 到共享内存 和 共享内存到 Proc B，因为直接在内存上操作，所以共享内存的速度也就提高了。

#### 内存映射（Memory Map）



#### 套接字（Socket）

创建 Socket 的时候 作用域 选择 系统内使用（而 选择 以太网 就是不同机器间的 TCP/UDP/IP 通讯了）。

## Linux 线程

详细学习的地方，可以当字典备查：

- [Multi-Threaded Programming With POSIX Threads (kent.edu)](http://www.cs.kent.edu/~ruttan/sysprog/lectures/multi-thread/multi-thread.html)。
- 书《POSIX多线程程序设计》。
- 书《Unix_Linux_Windows_OpenMP多线程编程》中的《第三章 Unix/Linux 多线程编程》。

多线程指的是在单个 程序/进程 中可以同时运行多个不同的线程，执行不同的任务：

> - 更高的运行效率，并行执行；
> - 多线程是模块化的编程模型；
> - 与进程相比，线程的创建和切换开销更小；
> - 通信方便；
> - 能简化程序的结构，便于理解和维护；更高的资源利用率。

多线程的应用场景：

> 1. 程序中出现需要等待的操作，比如网络操作、文件IO等，可以利用多线程充分使用处理器资源，而不会阻塞程序中其他任务的执行。
> 2. 程序中出现可分解的大任务，比如耗时较长的计算任务，可以利用多线程来共同完成任务，缩短运算时间。
> 3. 程序中出现需要后台运行的任务，比如一些监测任务、定时任务，可以利用多线程来完成。

线程安全与线程同步：

> **线程安全**：多线程访问时，采用了加锁机制，当一个线程访问该类的某个数据时，进行保护，其他线程不能进行访问直到该线程读取完，其他线程才可使用。不会出现数据不一致或者数据污染。
>
> **线程不安全**：不提供数据访问保护，有可能出现多个线程先后更改数据造成所得到的数据是脏数据。如果多个线程同时读写共享变量，会出现数据不一致的问题。
>
> **线程安全问题都是由全局变量及静态变量引起的**。
>
> 若每个线程中对全局变量、静态变量只有读操作，而无写操作，一般来说，这个全局变量是线程安全的；若有多个线程同时执行写操作，一般都需要考虑线程同步，否则的话就可能影响线程安全。
>
> **线程同步**：即当有一个线程在对内存进行操作时，其他线程都不可以对这个内存地址进行操作，直到该线程完成操作， 其他线程才能对该内存地址进行操作，
>
> **线程异步**：访问资源时在空闲等待时同时访问其他资源，实现多线程机制。
>
> 同步：A线程要请求某个资源，但是此资源正在被B线程使用中，因为同步机制存在，A线程请求不到，怎么办，A线程只能等待下去
>
> 异步：A线程要请求某个资源，但是此资源正在被B线程使用中，因为没有同步机制存在，A线程仍然请求的到，A线程无需等待
>
> **线程同步的优势**：
>
> 好处：解决了线程的安全问题。
>
> 弊端：每次都有判断锁，降低了效率。
>
> 但是在安全与效率之间，首先考虑的是安全。

Linux 系统下的用 C 开发多线程使用叫 pthread 的线程库；内核级线程 和 用户级线程 是在创建线程时通过传入 API 的不同参数进行 区分/设置 的。

因为 pthread 并非 Linux 系统的默认库，而是 POSIX 标准的线程库。在 Linux 中将其作为一个库来使用，因此编译选项需要加上 -lpthread（或-pthread）以显式链接该库。例子：`gcc xxx.c -lpthread -o xxx.bin`。

### 各个 API 原型介绍

- pthread_self()——获取线程 ID。

  ```c
  /* pthread_self()——函数获取线程 ID
  	#include <pthread.h>
  	pthread_t pthread_self(void);
  	成功：返回线程号
  */
  #include <pthread.h>
  #include <stdio.h>
  int main()
  {
  	pthread_t tid = pthread_self();
  	printf("tid = %lu\n",(unsigned long)tid);
  	return 0;
  }
  ```

- pthread_create()——线程创建。

  ```c
  /* pthread_create()——线程创建
      #include <pthread.h>
      int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
      该函数第一个参数为pthread_t指针，用来保存新建线程的线程号。
      第二个参数表示了线程的属性，可传入NULL表示默认属性。
      第三个参数是一个函数指针，就是线程执行的函数。这个函数返回值为void*，形参为void*。
      第四个参数则表示为向线程处理函数传入的参数，若不传入，可用NULL填充。
      返回 0 表示成功，负值表示失败。
  */
  #include <pthread.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <errno.h>
  void *fun(void *arg) {    printf("pthread_New = %lu\n",(unsigned long)pthread_self());    }
  int main()
  {
      pthread_t tid1;
      int ret = pthread_create(&tid1,NULL,fun,NULL);
      ... 简化，错误处理略
      
      /* tid_main 为通过pthread_self获取的线程ID，tid_new通过执行pthread_create成功后tid指向的空间 */
     	/* 即 tid1 与 pthread_New 打印结果应为一致 */
      printf("tid_main = %lu tid_new = %lu \n",(unsigned long)pthread_self(),(unsigned long)tid1);
      /* 因线程执行顺序随机，不加sleep可能导致主线程先执行，导致进程结束，无法执行到子线程 */
      /* 也就是说，主线程 执行到这里 如果不加 sleep 则 后面直接 return 结束了，那么 线程 fun 还没执行 本进程就结束了 */
      sleep(1);    return 0;
  }
  /*
  通过pthread_create确实可以创建出来线程，主线程中执行pthread_create后的tid指向了线程号空间，与子线程通过函数pthread_self打印出来的线程号一致。
  特别说明的是，当主线程伴随进程结束时，所创建出来的线程也会立即结束，不会继续执行。并且创建出来的线程的执行顺序是随机竞争的，并不能保证哪一个线程会先运行。可以将上述代码中sleep函数进行注释，观察实验现象。
  */
  ```

  创建 进程时候 传入参数：

  ```c
  #include <pthread.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <errno.h>
  void *fun1(void *arg){    printf("%s:arg = %d Addr = %p\n",__FUNCTION__,*(int *)arg,arg);    }
  void *fun2(void *arg){    printf("%s:arg = %d Addr = %p\n",__FUNCTION__,(int)(long)arg,arg);    }
  int main()
  {
      pthread_t tid1,tid2;    int a = 50;
      int ret = pthread_create(&tid1,NULL,fun1,(void *)&a); /* 传入地址 */
      ... 简化，错误处理略
      ret = pthread_create(&tid2,NULL,fun2,(void *)(long)a); /* 传入值 */
      ... 简化
      sleep(1);    printf("%s:a = %d Add = %p \n",__FUNCTION__,a,&a);    return 0;
  }
  ```

- pthread_exit / pthread_cancel 和 pthread_join / pthread_tryjoin_np——线程的退出。

  线程的退出情况有三种：

  - 第一种是进程结束，进程中所有的线程也会随之结束。
  - 第二种是通过函数 pthread_exit() 来主动的退出所在的线程。
  - 第三种被其他线程调用 pthread_cancel() 来被动退出。

  关于线程退出后的资源回收：

  一个进程中的多个线程是共享数据段的。如果一个线程是 joinable 或者叫 非分离状态的，在线程退出之后，退出线程所占用的资源并不会随着线程的终止而得到释放，要用 pthread_join/pthread_tryjoin_np 函数来同步并释放资源，即 当线程结束后，主线程要通过函数 pthread_join/pthread_tryjoin_np 来回收线程的资源，并且获得线程结束后需要返回的数据。如果一个线程是 unjoinable 或者叫 分离状态的，则 在线程退出之后 其自己会主动回收资源，主线程里便不用再调用 pthread_join/pthread_tryjoin_np 来回收线程的资源，当然此时 线程退出的时候也就不能传出参数。joinable 和 unjoinable 可以设置，后面 线程属性 部分会说到。

  关于主线程 / 进程的退出：

  - 在主线程中，在 main 函数中 return 了或是调用了 exit() 函数，则主线程退出，且整个进程也会终止，此时进程中的所有线程也将终止，因此要避免 main 函数过早结束。
  - 在任何一个线程中调用 exit() 函数都会导致进程结束，进程一旦结束，那么进程中的所有线程都将结束。

  以下 是对 pthread_exit / pthread_cancel 和 pthread_join / pthread_tryjoin_np 线程的退出 相关 API 的说明。

  ```c
  /*
  线程主动退出 pthread_exit
      #include <pthread.h>
      void pthread_exit(void *retval);
      pthread_exit函数为线程退出函数，在退出时候可以传递一个void*类型的数据带给主线程，若选择不传出数据，可将参数填充为NULL。
      pthread_exit函数唯一的参数value_ptr是函数的返回值，只要pthread_join中的第二个参数value_ptr不是NULL，这个值将被传递给value_ptr
  
  线程被动退出 pthread_cancel，其他线程使用该函数让另一个线程退出 
      #include <pthread.h>
      int pthread_cancel(pthread_t thread);
      成功：返回0
      该函数传入一个tid号，会强制退出该tid所指向的线程，若成功执行会返回0。
  
  线程资源回收（阻塞在执行到 pthread_join 的地方，然后等待 thread 线程的退出）
      #include <pthread.h>
      int pthread_join(pthread_t thread, void **retval);
      该函数为线程回收函数，默认状态为阻塞状态，直到成功回收线程后才返回。第一个参数为要回收线程的tid号，第二个参数为线程回收后接受线程传出的数据，     或者该线程被取消而返回PTHREAD_CANCELED。
  	
  线程资源回收（非阻塞，需要循环查询）
      #define _GNU_SOURCE            
      #include <pthread.h>
      int pthread_tryjoin_np(pthread_t thread, void **retval);
      该函数为非阻塞模式回收函数，通过返回值判断是否回收掉线程，成功回收则返回0，其余参数与pthread_join一致。
  
  阻塞方式 pthread_join 和 非阻塞方式 pthread_tryjoin_np 使用上的区别：
      通过函数 pthread_join 阻塞方式回收线程，几乎规定了线程回收的顺序，若最先回收的线程未退出，则一直会被阻塞，导致后续先退出的线程无法及时的回收。
      通过函数 pthread_tryjoin_np 使用非阻塞回收线程，可以根据退出先后顺序自由的进行资源的回收。
  */
  ```

- 线程属性相关：

  参考 [pthread_attr_init线程属性_高司机的博客-CSDN博客_pthread_attr_destroy](https://blog.csdn.net/pbymw8iwm/article/details/6721038)，线程属性详解 [线程属性pthread_attr_t简介_Robin Hu的专栏-CSDN博客](https://blog.csdn.net/hudashi/article/details/7709413)。

  ```c
  /* 定义 pthread_attr_t 线程属性变量，用于设置线程属性，主要包括 scope 属性(用于区分用户态或者内核态)、detach（分离/joinable）属性、堆栈地址、堆栈大小、优先级 */
  pthread_attr_t attr_1,attr_2_3_4[3];
  
  /* 首先调用 pthread_attr_init 来对 线程属性变量 进行默认的初始化，然后才可以调用 pthread_attr_xxx 类函数来改变其值 */
  pthread_attr_init(&attr_1);
  
  /* 比如 （这里举一个例子，有很多设置属性的 API）
  	pthread_attr_setdetachstate(&attr_1,PTHREAD_CREATE_DETACHED); 来设置 该线程的 可分离属性（pthread_detach 函数也是设置某一个 线程的 这个属性）
  	在默认情况下线程是 joinable 或者叫非分离状态的，这种情况下，主线程等待子线程退出后，只有当 pthread_join() 函数返回时，创建的线程才算终止，才能释放自己占用的系统资源。如果设置线程 为 unjoinable 或者叫 分离状态，即 子线程退出后 其主动的回收资源，主线程这里不必再调用 pthread_join 等待 子线程退出了。
  	可以使用 pthread_attr_setdetachstate 函数把线程属性 detachstate 设置为下面的两个合法值之一：设置为 PTHREAD_CREATE_DETACHED 以分离状态启动线程（unjoinable）；或者设置为 PTHREAD_CREATE_JOINABLE 正常启动线程（joinable，即默认的）。
  可以使用 pthread_attr_getdetachstate 函数获取当前的 datachstate 线程属性。
  	另外，一般 不 建 议 去主动更改线程的优先级。
  	上面的 线程属性相关 的参考 链接中 对更多属性设置API进行了介绍，包括 继承性、调度策略（两种可选+其它方式）、调度参数
  */
  
  /* 这里是通过设置线程属性 设置为 系统级线程，还是用户级线程 */
  pthread_attr_setscope(&attr_1, PTHREAD_SCOPE_SYSTEM);         /* 系统级线程，适合计算密集 */
  pthread_attr_setscope(&attr_2_3_4[0], PTHREAD_SCOPE_PROCESS); /* 用户级线程，适合IO密集 */
  
  /* 然后用这个属性去创建线程 */
   pthread_create(&tid, &attr_1, fn, arg);
  
  /* 可以将属性都设为 NULL 值，来重新 init 然后设置 */
  pthread_attr_destroy(&attr_1);
  ```

  线程的竞争：参考 [Linux线程的实现 & LinuxThread vs. NPTL & 用户级内核级线程 & 线程与信号处理 - blcblc - 博客园 (cnblogs.com)](https://www.cnblogs.com/charlesblc/p/6242518.html)。

  系统级线程会与其它 进程 共同竞争时间片，用户及线程仅与所在进程内的其它用户及线程竞争调度。

  Linux 2.6 以后的 pthread 使用 NPTL（更好支持 POSIX） 实现，都是系统级别的1:1线程（一个线程相当于一个进程，1:n就相当于一个进程里面n各线程相互竞争）模型，都是系统级线程。而 pthread_create() 里调用 clone() 时设置了CLONE_VM，所以在内核看来就产生了两个拥有相同内存空间的进程。所以用户态创建一个新线程，内核态就对应生成一个新进程。
  
- etc.

### 使用这些 API 的例程

```c
/* 文件名 “线程API的例程-Linux下，被动回收.c” */

#define _GNU_SOURCE 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/* 例子说明：
创建 系统级 线程 1，无传入和传出参数，死循环，特定条件时退出，使用 pthread_join 回收
创建 用户级 线程 2、3、4 三个线程，线程号使用数组，传入和传出参数，使用 pthread_tryjoin_np 回收

在 linux 环境 的 gnu 编译器 下 执行编译：gcc temp.c -lpthread -o temp.bin
*/

/* 用于设置线程属性，主要包括 scope 属性(用于区分用户态或者内核态)、detach（分离/joinable）属性、堆栈地址、堆栈大小、优先级 */
pthread_attr_t attr_1, attr_2_3_4[3];
/* 指向线程标识符的指针，区分线程，即可称为 线程号，仅在本进程中有效。本质是 unsigned long int */
pthread_t id_1, id_2_3_4[3];

/* 线程 1，无传入和传出参数，执行完后退出，使用 pthread_join 回收 */
void *thread_1(void *in_arg)
{
    int i = 0;
    printf("thread_1 ID = %lu\n", (unsigned long)pthread_self());
    for(;;)
    {
        printf("thread_1 print times = %d\n", ++i);
        if(i >= 3)
            pthread_exit(NULL);
            /* 用 pthread_exit() 来调用线程的返回值，用来退出线程，但是退出线程所占用的资源不会随着线程的终止而得到释放 */
        sleep(1); /* sleep() 单位秒，程序挂起 1 秒 */
    }
}

/* 线程 2 3 4 */
void *thread_2_3_4(void *in_arg)
{
    /* 必须要 static 修饰，否则 pthread_join/pthread_tryjoin_np 无法获取到正确值 */
    static char* exit_arg;
    
    /* exit_arg 是 本函数的一个局部变量，多个线程 2、3、4 都会修改它，因此最后返回的时候不知道是谁最后一次修改的 */
    /* 因此要格外注意 */
    exit_arg = (char*)in_arg;
    
    pthread_t self_id = pthread_self();
    if(self_id == id_2_3_4[0])
    {
        printf("thread_2 ID = %lu\n", (unsigned long)self_id);
        sprintf((char*)in_arg,"id_2 gagaga");
    }else if(self_id == id_2_3_4[1])
    {
        printf("thread_3 ID = %lu\n", (unsigned long)self_id);
        sprintf((char*)in_arg,"id_3 lalala");
    }else if(self_id == id_2_3_4[2])
    {
        printf("thread_4 ID = %lu\n", (unsigned long)self_id);
        sprintf((char*)in_arg,"id_4 hahaha");
    }else
    {
        pthread_exit(NULL);
    }

    pthread_exit((void*)in_arg);
}

int main(void)
{
    int ret = -1, i = 0, return_thread_num = 0;
    char *str_gru[3];
    void *exit_arg = NULL;

    pthread_attr_init(&attr_1);
    pthread_attr_setscope(&attr_1, PTHREAD_SCOPE_SYSTEM); /* 系统级线程 */
    
    for(i = 0;i < 3;i++)
    {
        pthread_attr_init(&attr_2_3_4[i]);
        pthread_attr_setscope(&attr_2_3_4[i], PTHREAD_SCOPE_PROCESS); /* 用户级线程 */
    }

    /* 创建线程 1 */
    ret = pthread_create(&id_1, &attr_1, thread_1, NULL);
    if(ret != 0)
    {
        /* perror 把一个描述性错误消息输出到标准错误 stderr, 调用"某些"函数出错时，该函数已经重新设置了errno 的值。perror 函数只是将你输入的一些信息和 errno 所对应的错误一起输出 */
        perror("pthread1, pthread_create: ");
        return -1;
    }
    
    /* 创建线程 2、3、4 */
	for(i = 0;i < 3;i++)
    {
        str_gru[i] = (char*)malloc(sizeof(char) * 42 + i);
	    ret = pthread_create(&id_2_3_4[i], &attr_2_3_4[i], thread_2_3_4, (void *)str_gru[i]);
	    if(ret != 0)
        {
		    perror("pthread 2 3 4, pthread_create: ");
		    return -1;
		}
	}
    
    /* 等待所有线程结束，先等 线程 2、3、4 相继的、无顺序要求的 退出，再等 线程 1 退出 */
    for(;;)
    {
		for(i = 0;i < 3;i++)
        {
            /* pthread_tryjoin_np 的 np 为不可移植，是gnu定的非POSIX标准的API，仅linux里面的编译器能用 */
            if(pthread_tryjoin_np(id_2_3_4[i], &exit_arg) == 0)
            {
                printf("pthread : %lu exit with str: %s\n", (unsigned long)id_2_3_4[i], (char*)exit_arg);
                free(str_gru[i]);
                return_thread_num++;
            }
        }
        if(return_thread_num >= 3) break;
	}
    pthread_join(id_1, NULL);

    return 0;
}
```

### 线程间通讯 / 线程同步方式

参考 / 引用：

- 100ask。
- [linux基础——linux线程间通信及同步机制总结_yexz的博客-CSDN博客_linux 线程间通信](https://blog.csdn.net/a987073381/article/details/52029070)。
- [pthread的互斥量和自旋锁_zhaopengnju的博客-CSDN博客_pthread 自旋锁](https://blog.csdn.net/zhaopengnju/article/details/52068108)、[pthread_spin自旋锁_gdut17的博客-CSDN博客_pthread 自旋锁](https://blog.csdn.net/beyond706/article/details/103745414)。
- [pthread-win32 semaphore信号量总结 - ayanmw - 博客园 (cnblogs.com)](https://www.cnblogs.com/ayanmw/archive/2012/12/10/2811830.html)。

由于线程间共享进程变量资源，线程间的通信目的主要是用于线程同步（即约束多个线程的执行的顺序规则（信号量）或互斥规则（互斥锁）），所以线程没有像进程通信中的用于数据交换的通信机制。

互斥锁、条件变量和信号量的区别：

- 互斥锁：互斥，一个线程占用了某个资源，那么其它的线程就无法访问，直到这个线程解锁，其它线程才可以访问。
- 信号量：同步，一个线程完成了某一个动作就通过信号量告诉别的线程，别的线程再进行某些动作。而且信号量有一个更加强大的功能，信号量可以用作为资源计数器，把信号量的值初始化为某个资源当前可用的数量，使用一个之后递减，归还一个之后递增。
- 条件变量：同步，一个线程完成了某一个动作就通过条件变量发送信号告诉别的线程，别的线程再进行某些动作。条件变量必须和互斥锁配合使用。

锁机制适用于类似原子操作的情况，加锁后 快速的处理某一个临界区的资源，然后立马解锁，不适合长时间的加锁（更不好的情况就是在加锁后的临界区里被执行了中断，在中断里面又要阻塞的进行加锁，那么这时就发生死锁了，卡住了）；而信号/信号量（和 条件变量）适合 长时间的 等待 信号/条件的发生，而且 在等待/阻塞 期间调用者是休眠的。

为了减少错误 和 复杂性，设计程序前应尽量考虑 不要在 中断中 使用 锁、信号 等之类的东西，中断程序里面设计的要 简洁、优雅。

#### 锁机制

##### 互斥锁（Mutex）

互斥锁 / 互斥量 用来防止多个线程 同时/并发的 访问某个临界资源。

互斥量本质上说是一把锁，在访问共享资源前对互斥量进行加锁，在访问完成后释放互斥量。对互斥量进行加锁以后，其他识图再次对互斥量加锁的线程都会被阻塞直到当前线程释放该互斥锁。对于互斥锁，如果资源已经被占用，资源申请者只能进入睡眠状态。

如果释放互斥量时有一个以上的线程阻塞，那么所有该锁上的阻塞线程都会变成可运行状态，第一个变成运行状态的线程可以对互斥量加锁，其他线程就会看到互斥量依然是锁着，只能再次阻塞等待它重新变成可用，这样，一次只有一个线程可以向前执行。

即 多个线程都要访问某个临界资源，比如某个全局变量时，需要互斥地访问：我访问时，你不能访问。

头文件：`#include <pthread.h>`。

常用 API：

```c
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr); // 初始化量
/* 该函数初始化一个互斥量，第一个参数是改互斥量指针，第二个参数为控制互斥量的属性，一般为 NULL。当函数成功后会返回 0，代表初始化互斥量成功。
    当然初始化互斥量也可以调用宏来快速初始化，代码如下：
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITALIZER;
*/

int pthread_mutex_lock(pthread_mutex_t *mutex);                                       // 加锁（阻塞）
int pthread_mutex_unlock(pthread_mutex_t *mutex);                                     // 解锁（非阻塞）
/* lock 函数与 unlock 函数分别为加锁解锁函数，只需要传入已经初始化好的 pthread_mutex_t 互斥量指针。成功后会返回 0。
    当某一个线程获得了执行权后，执行 lock 函数，一旦加锁成功后，其余线程遇到 lock 函数时候会发生阻塞，直至获取资源的线程执行 unlock 函数后。unlock 函数会唤醒其他正在等待互斥量的线程。
    特别注意的是，当获取 lock 之后，必须在逻辑处理结束后执行 unlock，否则会发生死锁现象！导致其余线程一直处于阻塞状态，无法执行下去。在使用互斥量的时候，尤其要注意使用 pthread_cancel 函数，防止发生死锁现象！
*/

int pthread_mutex_trylock(pthread_mutex_t *mutex);                                   // 互斥量加锁（非阻塞）
/* 该函数同样也是一个线程加锁函数，但该函数是非阻塞模式通过返回值来判断是否加锁成功，用法与上述阻塞加锁函数一致。 */

int pthread_mutex_destroy(pthread_mutex_t *mutex);                                    // 销毁互斥量
/* 该函数是用于销毁互斥量的，传入互斥量的指针，就可以完成互斥量的销毁，成功返回0。 */
```

例程：参考 `pthread库-线程编程例程-来自百问网\01_文档配套源码\Pthread_Text10.c`。

互斥锁的属性：

```c
/* 与 线程属性类似的，先 声明变量，再用 pthread_mutexattr_init 初始化，
	再用 pthread_mutexattr_getxxx/pthread_mutexattr_setxxx 来 获取 / 设置 属性的某个选项，
	然后在 调用 互斥锁初始化 pthread_mutex_init 的时候 填入 该属性
	最后可以销毁 */
int pthread_mutexattr_init(pthread_mutexattr_t* attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t* attr);

int pthread_mutexattr_getshared(const pthread_mutexattr_t* attr, int* pshared);
int pthread_mutexattr_setshared(pthread_mutexattr_t* attr, int* pshared);
	pshared 的可以传入的参数：
        PTHREAD_PROCESS_SHARED：互斥锁可以被跨进程共享
        PTHREAD_PROCESS_PRIVATE：只能被初始化线程所属的进程中的线程共享
int pthread_mutexattr_gettype(const pthread_mutexattr_t* attr, int* type);
int pthread_mutexattr_settype(pthread_mutexattr_t* attr, int type);
	type 的可以传入的参数：
        PTHREAD_MUTEX_NOMAL：公平锁，对一个已经加锁的普通锁再次加锁，将引发死锁;对一个已经被其他线程加锁的普通锁解锁，或者对一个已经解锁的普通锁再次解锁，将导致不可预期的后果。
        PTHREAD_MUTEX_ERRORCHECK：检错锁，对一个已经加锁的检错锁再次加锁，则加锁操作返回EDEADLOCK。对一个已经被其他线程加锁的检错锁解锁，或者对一个已经解锁的检错锁再次解锁，则解锁操作返回EPERM。
        PTHREAD_MUTEX_RECURSIVE：嵌套锁，错误使用返回EPERM
        PTHREAD_MUTEX_DEFAULT：跟nomal差不多。
```

##### 读写锁（rwlock）

　读写锁与互斥量类似，不过读写锁拥有更高的并行性。互斥量要么是锁住状态，要么是不加锁状态，而且一次只有一个线程可以对其加锁。读写锁有 3 种状态：**读模式下加锁状态，写模式下加锁状态，不加锁状态**。

一次只有一个线程可以占有写模式的读写锁，但是多个线程可以同时占有读模式的读写锁。当读写锁是写加锁状态时，在这个锁被解锁之前，所有试图对这个锁加锁的线程都会被阻塞。当读写锁在读加锁状态时，所有试图以读模式对它进行加锁的线程都可以得到访问权，但是任何希望以写模式对此锁进行加锁的线程都会阻塞，直到所有的线程释放它们的读锁为止。

头文件：`#include <pthread.h>`。

常用 API：

```c
int pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *rwlockattr); // 初始化读写锁

int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);                                       // 读模式锁定读写锁
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);                                       // 写模式锁定读写锁
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);                                       // 解锁读写锁

int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);                                      // 销毁读写锁
```

##### 自旋锁（spin）

如果 互斥锁 被占用（被锁住），另一个线程进入时，互斥锁会引起线程切换（不死等，而是 yield 一次去运行其它线程）。适合锁的内容比较多的。

对于自旋锁，如果锁被占用（被锁住），来了的线程会一直等待直到获取这把锁相当于 `while(1);`（死等，跑满一个时间片时间）。适合锁的内容比较少的
当线程切换的代价远远比等待的代价大的时候，使用自旋锁。（如果对于 RTOS 有了解的，就会明白 yeild、跑满一个时间片时间 等的概念，可以玩一玩 单片机上的 FreeRTOS、RTT 就了解了）。

自旋锁与互斥量类似，但它不是通过休眠使进程阻塞，而是在获取锁之前一直处于忙等（自旋）阻塞状态。自旋锁可以用于以下情况：锁被持有的时间短，而且线程并不希望在重新调度上花费太多的成本。

如果一个可执行线程试图获得一个被争用(已经被持有的)自旋锁，那么该线程就会一直进行忙等待，自旋，也就是空转，等待锁重新可用（等待被解锁）。一个被争用的自旋锁使得请求它的线程在等待锁重新可用时自旋，特别的浪费CPU时间，所以自旋锁不应该被长时间的持有。实际上，这就是自旋锁的设计初衷，在短时间内进行轻量级加锁。自旋锁 也不能用在 中断程序里面，自旋锁保持期间是抢占失效的（内核不允许被抢占）。

头文件：`#include <pthread.h>`。

常用 API：

```c
int pthread_spin_init(pthread_spinlock_t *lock, int pshared);
/* 自旋锁 初始化函数，里面没有 属性变量，pshared 可以选择的参数：
	PTHREAD_PROCESS_PRIVATE 只在本进程内 使用该锁
	PTHREAD_PROCESS_SHARED 该锁可能位于共享内存对象中，在多个进程之间共享
	如果想要使用自旋锁同步多进程，那么设置 pshared 为 PTHREAD_PROCESS_SHARED，然后在进程共享内存中分配 pthread_spinlock_t 对象即可（pthread_mutex_t 亦如此）。
*/

int pthread_spin_destroy(pthread_spinlock_t *lock);

// 自旋锁操作
int pthread_spin_lock(pthread_spinlock_t *lock);
int pthread_spin_trylock(pthread_spinlock_t *lock);
int pthread_spin_unlock(pthread_spinlock_t *lock);
```

#### 信号量机制（Semaphore）

信号量 是一个大于等于 0 的量，为 0 时候线程阻塞。通过 sem_pos 函数（非阻塞） 给信号量增加 1，sem_wait 函数（阻塞） 当 信号量大于 0 时候对其 减少 1，等于 0 时阻塞。

可以用来做通知用，也可以用来计数：

- 信号量 可以控制多个 本来先后执行是随机无序的线程 的 执行顺序可控 和 可预测。例如 线程 A 在等待某件事，线程 B 完成了这件事后就可以给线程 A 发信号。
- 当需要一个计数器来限制可以使用某共享资源的线程数目时，可以使用“信号量”对象。信号量 保存了对当前访问某一个指定资源的线程的计数值，该计数值是当前还可以使用该资源的线程数目。如果这个计数达到了零，则所有对这个 信号量 所控制的资源的访问尝试都被放入到一个队列中等待，直到超时或计数值不为零为止。

头文件：`#include <semaphore.h>`。

常用 API：

```c
int sem_init(sem_t *sem, int pshared, unsigned int value);    // 初始化一个信号量 
/* 该函数可以初始化一个信号量，第一个参数传入sem_t类型指针。
    第二个参数传入 0 代表线程控制（多线程内使用），否则为进程控制（多进程使用）。
    第三个参数表示信号量的初始值，0代表阻塞，1以及更大的数字代表初始值（不阻塞）。
    待初始化结束信号量后，若执行成功会返回0。 */
int sem_destroy(sem_t * sem);                                 // 销毁信号量

int sem_wait(sem_t * sem);                                    // 信号量减少 1（阻塞），P 操作
int sem_post(sem_t * sem);                                    // 信号量增加 1（非阻塞），V 操作
int sem_trywait(sem_t *sem);                                  // 信号量减少 1（非阻塞），成功返回 0 
/* sem_wait 函数作用为检测指定信号量是否有资源可用，若无资源可用会阻塞等待，若有资源可用会自动的执行 sem - 1 的操作。
   sem_post 函数会释放指定信号量的资源，执行 sem + 1 操作。
   即信号量的 申请 与 释放 */

int sem_timedwait (sem_t * sem,const struct timespec * abstime); // 在 sem_wait 的 等待/阻塞 期间内最多 等待 abstime 秒的时间 就返回
int sem_post_multiple (sem_t * sem,int count);                // 一次 信号量增加 count（非阻塞）

int sem_getvalue(sem_t * sem, int * sval);                    // 获取当前信号量的值
```

例程：参考 `pthread库-线程编程例程-来自百问网\01_文档配套源码\Pthread_Text12.c`、`pthread库-线程编程例程-来自百问网\02_视频配套源码\pthread3.c 和 pthread4.c`。

#### 条件变量机制

条件变量时一种同步机制，用来通知其他线程条件满足了，即 一个线程被挂起，直到某件事件发生。一般是用来通知对方共享数据的状态信息，因此条件变量时结合互斥量来使用的。

条件变量 是在多线程程序中用来实现 “等待--->唤醒” 逻辑常用的方法。

头文件：`#include <pthread.h>`。

常用 API：

```c
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);  // 初始化条件变量
/* 若 不需要设置属性则 cond_attr 填为N ULL */
/* 另一种以默认方式初始化 pthread_cond_t cond = PTHREAD_COND_INITIALIZER; */
int pthread_cond_destroy(pthread_cond_t *cond);                               // 销毁条件变量

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);          // 无条件等待条件变量变为真
int pthread_cond_timewait(pthread_cond_t *cond, pthread_mutex_t *mutex, const struct timespec *tsptr);  // 在给定时间内，等待条件变量变为真

int pthread_cond_signal(pthread_cond_t *cond); // 通知条件变量 条件满足啦，pthread_cond_signal 函数只会唤醒一个等待 cond 条件变量的线程

使用：
...
pthread_mutex_lock(&mutex); /* 可以加锁的时候 加锁 然后往后运行，否则阻塞 */
pthread_cond_wait(&cond, &mutex); /* 如果条件不满足则，会 先解锁 mutex，然后 阻塞/休眠 在这里等待条件满足；条件满足后被唤醒，先加锁 mutex 然后取消阻塞 往后执行*/
.../* 在这里 操作临界资源 */
pthread_mutex_unlock(&mutex);
...
```

例程：参考 `pthread库-线程编程例程-来自百问网\02_视频配套源码\pthread5.c`。

#### 信号（Signal）

在 一个进程的 多个线程 之间处理 信号（signal），与 进程中的信号处理不一样，需要多学、多用一下。

例如，当你发送一个SIGSTP信号给进程，这个进程的所有线程都会停止。因为所有线程内用同样的内存空间，所以对一个signal的handler都是一样的，但不同的线程有不同的管理结构所以不同的线程可以有不同的mask（引自 [Linux线程的实现 & LinuxThread vs. NPTL & 用户级内核级线程 & 线程与信号处理 - blcblc - 博客园 (cnblogs.com)](https://www.cnblogs.com/charlesblc/p/6242518.html)）。

参考：

- [linux 多线程信号处理总结 - CobbLiu - 博客园 (cnblogs.com)](https://www.cnblogs.com/cobbliu/p/5592659.html)。
- [pthread信号_track sun的博客-CSDN博客](https://blog.csdn.net/weixin_30540691/article/details/97729902)。
- 经验性总结 [linux多线程信号总结-businiaowyf-ChinaUnix博客](http://blog.chinaunix.net/uid-12274566-id-3050955.html)。





