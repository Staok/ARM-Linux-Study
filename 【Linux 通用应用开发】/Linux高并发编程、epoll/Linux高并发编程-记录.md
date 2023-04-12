# Linux高并发编程-记录

Linux高并发编程，学习记录，备查。

------



下面是 积攒的学习网址，用时学习整理在这里，配上文字说明和例子





[IO 多路复用: Poll/Epoll/Select 机制 (biscuitos.cn)](http://www.biscuitos.cn/blog/IO-SYNC/)



[Linux 并发编程小结_codetracer的博客-CSDN博客](https://blog.csdn.net/joker0910/article/details/7731107)



[linux下的并发编程详解_Leon_George的博客-CSDN博客](https://blog.csdn.net/liangzc1124/article/details/105340274)



[linux之linux 并发编程（1） - Sunny_Boy_H - 博客园 (cnblogs.com)](https://www.cnblogs.com/heych/p/12582840.html)

[linux之linux 并发编程（2） - Sunny_Boy_H - 博客园 (cnblogs.com)](https://www.cnblogs.com/heych/p/12582868.html)

[linux之linux并发编程（3） - Sunny_Boy_H - 博客园 (cnblogs.com)](https://www.cnblogs.com/heych/p/12582890.html)



[linux多线程并发编程的一些本质问题 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/345757649)





https://www.zhihu.com/question/32163005/answer/1802684879


主要使用 Epoll 来做多输入/输出流的高并发的处理


Linux 高性能服务 epoll 的本质
https://mp.weixin.qq.com/s/a3qjnucpBHfIoRKlSOrQ2w


Epoll详细介绍 和使用说明
！！！ https://blog.csdn.net/hbsyaaa/article/details/127599657
https://blog.csdn.net/armlinuxww/article/details/92803381
https://blog.csdn.net/mengzuchao/article/details/81294554
http://blog.chinaunix.net/uid/28541347/sid-193117-list-1.html


https://blog.csdn.net/a987073381/article/details/51913607


或者还可以使用 Libev 库（非Linux自带）
libev是一个开源的事件驱动库，基于epoll，kqueue等OS提供的基础设施。其以高效出名，它可以将IO事件，定时器，和信号统一起来，统一放在事件处理这一套框架下处理。基于Reactor模式，效率较高，并且代码精简（4.15版本8000多行），是学习事件驱动编程的很好的资源。

下载链接：http://software.schmorp.de/pkg/libev.html
详细介绍
https://blog.csdn.net/janeqi1987/article/details/74279973


https://zhuanlan.zhihu.com/p/461398753


这是一个展示epoll水平触发(level trigger)和边缘触发(edge trigger)，分别在read和write两种情况下有什么表现的实验，目的是彻底搞清楚epoll的水平触发和边缘触发原理。
https://github.com/Manistein/test_epoll_lt_and_et



——————————

学好epoll 之后 要写一个 socket 多对多的 程序，在现有 socket 自写库基础上，另开一个 新写，一个server可以自动处理接收多个client 并且 处理 收发，高效的。

使用 epoll 对 自写的socket库 改进 做个 更通用的 网络编程。

这个 epoll 版本的 网络编程测试库，放到 `\【Linux 通用应用开发】\3-Socket编程\socket编程自写库\` 里面，并且这里 epoll 文章要引用 到那个路径。
