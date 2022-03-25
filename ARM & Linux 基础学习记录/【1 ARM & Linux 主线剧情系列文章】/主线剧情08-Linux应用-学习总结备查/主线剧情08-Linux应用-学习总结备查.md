# Linux 应用 - 学习总结备查

记 Linux 应用 相关的基本概念和流程，便于 备查 / 复习。*p.s Linux 系统性的入门与学习推荐去看 [【主线剧情 0.0】Linux 学习资源大综合 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/486903467)（[CSDN 链接](https://blog.csdn.net/Staokgo/article/details/123717871#t7)） 里面的 `!学习来源!` 一节！*。

------

# 地基

**① Linux 开发 基本工具的使用**

代码编辑：Vim、gedit（ubuntu 下）。编译工具：gcc，make，cmake（生成 makefile），gdb。项目管理：git。文本编辑：Windows 端的如 source insight、notepad、VsCode 等；Linux 端的如 gedit（Ubuntu 端）、VsCode 等。 

引 [主线剧情02-ARM-Linux基础学习记录_Real-Staok的博客-CSDN博客](https://blog.csdn.net/Staokgo/article/details/123693110#t7) 里面的 `Linux 下的开发` 一节的内容。

**② 编译 / 交叉编译 工具的获取**

引 [主线剧情02-ARM-Linux基础学习记录_Real-Staok的博客-CSDN博客](https://blog.csdn.net/Staokgo/article/details/123693110#t14) 里面的 `获取交叉编译工具链` 一节的内容。其中 举出三个方法：用开发板厂家提供的 SDK 里的工具链、ARM 官网下载 合适的工具链、使用 Linaro GCC 编译器。

另外，在构建 rootfs 时候使用 buildroot 或 yocto 时候可以构建 交叉编译器。

**③ Linux 系统调用（各层调用关系）**

- [Linux系统相关的基础问题（空间、内存、库、链接、环境变量）_~青萍之末~的博客-CSDN博客](https://blog.csdn.net/daaikuaichuan/article/details/82729483)。
- [Linux系统调用_~青萍之末~的博客-CSDN博客_linux系统调用](https://blog.csdn.net/daaikuaichuan/article/details/82902407)。[【第4篇】嵌入式Linux应用开发基础知识_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1kk4y117Tu?p=13)，其中 `4-2_ 文件IO _系统接口` 这一个节讲解 系统调用怎么进入内核。
- [Linux内核的五大模块_~青萍之末~的博客-CSDN博客_linux内核模块](https://blog.csdn.net/daaikuaichuan/article/details/82957655)，进程调度，进程间通信模块（包括管道、命名管道、消息队列、信号量和共享内存等），内存管理模块，文件系统模块，网络接口模块。
- etc.

**④ Linux 一般开发流程**

引 [主线剧情02-ARM-Linux基础学习记录_Real-Staok的博客-CSDN博客](https://blog.csdn.net/Staokgo/article/details/123693110#t2) 里面的 `Linux 一般开发步骤` 一节的内容：

> Bootloader、Linux 内核、根文件系统、APP 等等软件，需要在 Ubuntu 中编译；但是阅读、修改这些源码时，在 Windows 下会比较方便。
>
> 所以工作日常开发流程如下：
>
> PC 端，使用 source insight 编、改源码 —>传—> Ubuntu 端，对修改好的源码进行编译、制作 —>下载—> 嵌入式板端，在 Linux 板子上运行、测试。
>
> 分步来说就是：
>
> 在 Windows 上阅读、研究、修改，修改后，上传（推荐 FileZilla）到 Ubuntu ；
>
> 在 Ubuntu 上编译、制作（推荐使用 MobaXterm 通过 SSH 远程登陆 Ubuntu）；
>
> 把制作好的可执行程序下载到开发板上运行、测试。
>
> u-boot、Linux内核，在 Windows 和 Ubuntu 各存一份。根文件系统使用 buildroot （或 Busybox 或 Yocto）制作，它无需放在 Windows 上。

**⑤ 主机端 与 嵌入式 Linux 板端 相互传文件**

引 [主线剧情02-ARM-Linux基础学习记录_Real-Staok的博客-CSDN博客]([(40条消息) 主线剧情02-ARM-Linux基础学习记录_Real-Staok的博客-CSDN博客](https://blog.csdn.net/Staokgo/article/details/123693110)) 里面的 `PC 与 嵌入式板 传输文件的方式汇总` 一节的内容。这一块内容会只在 [Github](https://github.com/Staok/ARM-Linux-Study)/[Gitee](https://gitee.com/staok/ARM-Linux-Study) 仓库内更新：

- 网络传输：ETH/WiFi。通过 SSH、NFS、TFTP 等。
- USB 传输：~~U 盘拷贝~~，芯片 官方配套的 USB 传输 / 烧写 工具。
- 串口传输：rz / sz 命令。

**⑥ 期待美好发生**

这儿的能力是靠 多做项目、多积累经验，量变出质变。

# 开发

## 参考源

### 通过手册的 API 详细描述参考

引 [【规范】万字集大成的C编写规范_Real-Staok的博客-CSDN博客](https://blog.csdn.net/Staokgo/article/details/122451567#t20) 中的 `7 C 标准库的使用` 一节内容，即 各种C标准库详解和用例，其中包括了 C/C++ 的常用标准库 的 API 使用的详细描述，还包括 Linux_C（[glibc_man_cn](https://gitee.com/zhaixuebuluo/glibc_man_cn)）、POSIX-C 等的 API 的完整描述文档（包括中文），便于速查，其 仓库在 [额外文档/各种C标准库详解和用例 · 瞰百/coding-style-and-more - 码云 - 开源中国 (gitee.com)](https://gitee.com/staok/coding-style-and-more/tree/main/额外文档/各种C标准库详解和用例)（[Gituhb 仓库地址](https://github.com/Staok/coding-style-and-more/tree/main/%E9%A2%9D%E5%A4%96%E6%96%87%E6%A1%A3/%E5%90%84%E7%A7%8DC%E6%A0%87%E5%87%86%E5%BA%93%E8%AF%A6%E8%A7%A3%E5%92%8C%E7%94%A8%E4%BE%8B)）。

其中包括文件如：C语言标准函数库速查.pdf、C语言函数大全语法着色版.pdf、Linux函数大全.chm、POSIX-C函数速查.chm 等等。

### 通过命令行寻找 命令、API  描述参考

help、man 和 info 命令。

- help 只能用于查看某个命令的用法。

- man 命令既可以查看命令的用法，还可以查看函数的详细介绍等等。（引自 `百问网`）

  比如想查看 open() 函数的用法时，可以直接执行 `man open` ，发现这不是想要内容时再执行 `man  2  open`。

  在 man 命令中可以及时按“h”查看帮助信息了解快捷键。常用的快捷键是：

  - `f` 往前翻一页。
  - `b` 往后翻一页。
  - `/<patten>` 往前搜 `patten` 字符。
  - `?<patten>` 往后搜。

- info 命令会显示最全面的信息，一般 `man` 命令就够了，故 `info` 命令介绍 暂时略。

### Linux 应用开发 / 学习 / 备查 参考源

- [【主线剧情 0.0】Linux 学习资源大综合 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/486903467)（[CSDN 链接](https://blog.csdn.net/Staokgo/article/details/123717871#t7)） 里面的 `!学习来源!` 一节！
- [主线剧情0.0-Linux学习资源大综合_Real-Staok的博客-CSDN博客](https://blog.csdn.net/Staokgo/article/details/123717871#t12) 里面的 `Linux 应用编程内容补充` 一节。

## 系统调用

参考：

- [Linux 下系统调用的三种方法_海风林影的博客-CSDN博客](https://blog.csdn.net/hazir/article/details/11894427)。
- [ linux系统调用(持续更新....)_tiramisu_L的博客-CSDN博客](https://blog.csdn.net/tiramisu_L/article/details/106393065)。

通过 glibc 提供的库函数、使用 syscall 直接调用、通过 int 指令陷入；popen()函数、fgets()函数、system()函数、strstr()函数。

## 标准 API 富集

这里就是日常用到的 API 的积累和整理，最详细、全面的 API 参考 见 上面 `通过手册的 API 详细描述参考` 一节。

日常用到的 标准 API 富集 单独放在了文件夹 `用到的API-收集积累` 里面。



