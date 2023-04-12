# 主线剧情09-Linux性能优化相关总结

收集整理 与 实践记录。

------

## 调试工具

工欲善其事必先利其器。

- top 命令。
- 内存扫描。
- [perf: Linux 性能测试调试工具](http://www.biscuitos.cn/blog/TOOLS-perf/)。
- [blktrace: Block IO 性能测试调试工具](http://www.biscuitos.cn/blog/TOOLS-blktrace/)。



## 优秀参考

对于深刻理解 Linux 系统有益良多。

！！！尽快看，说不定哪天下面的链接就挂掉了  (＃°Д°)  (°ー°〃) ┌(。Д。)┐

### 内核理解

- [万字讲解你写的代码是如何跑起来的？ - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/607142856)。

### 系统带宽

- [Linux性能优化的全景指南-面包板社区 (eet-china.com)](https://www.eet-china.com/mp/a178989.html)。

  内容很多，有 性能指标、性能观测工具、任务调度开销、CPU优化、内存等待比较丰富。

- [Linux 管道到底能有多快？ - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/588956958)。

  > 本文作者通过一个示例程序，演示了通过Linux管道读写数据的性能优化过程，使吞吐量从最初的 3.5GiB/s，提高到最终的 65GiB/s。即便只是一个小例子，可它涉及的知识点却不少，包括零拷贝操作、环形缓冲区、分页与虚拟内存、同步开销等，尤其对Linux内核中的拼接、分页、虚拟内存地址映射等概念从源码级进行了分析。文章从概念到代码由浅入深、层层递进，虽然是围绕管道读写性能优化展开，但相信高性能应用程序或Linux内核的相关开发人员都会从中受益匪浅。

### 高效I/O

- [Linux探秘之 I/O 效率 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/486955226)。
- [聊聊 Linux IO | 浅墨的部落格 (0xffffff.org)](https://www.0xffffff.org/2017/05/01/41-linux-io/)。
- `.\【Linux 通用应用开发】\Linux高并发编程、epoll\` 目录下的 epoll 的内容。
- 

### 内存管理

- [聊聊内存管理 | 浅墨的部落格 (0xffffff.org)](https://www.0xffffff.org/2014/10/31/32-memory-management/)。[聊聊 Linux 的内存统计 | 浅墨的部落格 (0xffffff.org)](https://www.0xffffff.org/2019/07/17/42-linux-memory-monitor/)。
- `.\【Linux 通用应用开发】\3-内存管理\` 目录下的内容。
- [kvm 优化特性：ksm技术，大页内存等 - 码农岛 (manongdao.com)](https://www.manongdao.com/article-2264777.html)。

### 多线程

- 进程线程 基本使用总结 [（真正全）Linux进程和线程的基本编程、通讯和例程【杂记】 - 欢迎来到 Staok - 瞰百易 (gitee.io)](https://staok.gitee.io/24linux进程和线程的基本编程-通讯和例程/)。
- [《Linux 多线程服务端编程》总结备忘 | 浅墨的部落格 (0xffffff.org)](https://www.0xffffff.org/2014/01/09/27-linux-mutil-threads-programming/)。

### 多核利用

- [linux下把进程/线程绑定到特定cpu核上运行_guotianqing的博客-CSDN博客_linux多核cpu调度](https://blog.csdn.net/guotianqing/article/details/80958281)。
- 获取CPU可用核数并绑定某核运行 [linux_system_call/get_cpu_core_num.c at master · hurley25/linux_system_call (github.com)](https://github.com/hurley25/linux_system_call/blob/master/src/get_cpu_core_num.c)。
- [linux下充分利用多核cpu-低头、真掩饰-ChinaUnix博客](http://blog.chinaunix.net/uid-24652842-id-233561.html)。

### 实时化改造



#### 加快中断响应速度



## 实践记录