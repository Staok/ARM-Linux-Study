# 驱动程序常用内核态API积累



------

## 内存申请

一文说明清楚：[Linux内核空间内存申请函数kmalloc、kzalloc、vmalloc的区别【转】_danxibaoxxx的博客-CSDN博客](https://blog.csdn.net/danxibaoxxx/article/details/99357541)。

更多 API [Linux内核API 内存管理|极客笔记 (deepinout.com)](https://deepinout.com/linux-kernel-api/linux-kernel-api-memory-management/linux-kernel-api-memory-management.html)。

### kmalloc()

```c
#include <linux/slab.h>

void *kmalloc(size_t size, gfp_t flags);
void kfree(const void *objp);
```

> kmalloc() 申请的内存位于物理内存映射区域，而且在物理上也是连续的，它们与真实的物理地址只有一个固定的偏移，因为存在较简单的转换关系，所以对申请的内存大小有限制，**不能超过128KB**。 
> 　　 
> 较常用的 flags（分配内存的方法）：
>
> - **GFP_ATOMIC** —— 分配内存的过程是一个原子过程，分配内存的过程不会被（高优先级进程或中断）打断；
> - **GFP_KERNEL** —— 正常分配内存；
> - **GFP_DMA** —— 给 DMA 控制器分配内存，需要使用该标志（DMA要求分配虚拟地址和物理地址连续）。
> - 更多 标志位 的列举 [linux中kmalloc函数详解_fulinux的博客-CSDN博客_kmalloc函数](https://fulinux.blog.csdn.net/article/details/8635234)。

下文引自 [ linux 字符驱动 申请内存最大,Linux驱动技术(一) _内存申请_一只小短腿的博客-CSDN博客](https://blog.csdn.net/weixin_33375514/article/details/116727531)。

> GFP_KERNEL是最常用的flag，注意，使用这个flag来申请内存时，如果暂时不能满足，**会引起进程阻塞**，So，一定不要在中断处理函数、tasklet和内核定时器等非进程上下文中使用GFP_KERNEL！

### kzalloc()

```c
#include <linux/slab.h>

/**
 * kzalloc - allocate memory. The memory is set to zero.
 * @size: how many bytes of memory are required.
 * @flags: the type of memory to allocate (see kmalloc).
 */
 static inline void *kzalloc(size_t size, gfp_t flags)
{
    return kmalloc(size, flags | __GFP_ZERO);
}

void kfree(const void *objp);
```

> kzalloc() 函数与 kmalloc() 非常相似，参数及返回值是一样的，可以说是前者是后者的一个变种，因为 kzalloc() 实际上只是额外附加了 **__GFP_ZERO** 标志。所以它除了申请内核内存外，还会**对申请到的内存内容清零**。
>
> kzalloc() 对应的内存释放函数也是 kfree()。

### vmalloc()

```c
#include <linux/vmalloc.h>
#include <linux/init.h>
#include <linux/module.h>

void *vmalloc(unsigned long size);
void vfree(const void *addr);
```

> vmalloc() 函数则会在虚拟内存空间给出一块连续的内存区，但这片连续的虚拟内存在物理内存中并不一定连续。由于 vmalloc() 没有保证申请到的是连续的物理内存（**所以不能用来做DMA之类的操作**），**对申请的内存大小没有限制**，如果需要申请较大的内存空间就需要用此函数了。
>
> 注意：vmalloc() 和 vfree() 可以睡眠，因此不能从中断上下文调用。 
>
> vmalloc() 还会调用使用GFP_KERN的kmalloc，一定不要在中断处理函数、tasklet和内核定时器等非进程上下文中使用 vmalloc！

### 总结

> kmalloc()、kzalloc()、vmalloc() 的共同特点是：
>
> 1. 用于申请内核空间的内存；
> 2. 内存以字节为单位进行分配；
> 3. 所分配的内存虚拟地址上连续；
>
> kmalloc()、kzalloc()、vmalloc() 的区别是：
>
> 1. kzalloc 是强制清零的 kmalloc 操作；（以下描述不区分 kmalloc 和 kzalloc）
> 2. kmalloc 分配的内存大小有限制（128KB），而 vmalloc 没有限制；
> 3. kmalloc 可以保证分配的内存物理地址是连续的，但是 vmalloc 不能保证；
> 4. kmalloc 分配内存的过程可以是原子过程（使用 GFP_ATOMIC），而 vmalloc 分配内存时则可能产生阻塞；
> 5. kmalloc 分配内存的开销小，因此 kmalloc 比 vmalloc 要快；
>
> 一般情况下，内存只有在要被 DMA 访问的时候才需要物理上连续，但为了性能上的考虑，内核中一般使用 kmalloc()，而只有在需要获得大块内存时才使用 vmalloc()。例如，当模块被动态加载到内核当中时，就把模块装载到由 vmalloc() 分配的内存上。

## likely 与 unlikely

引自 [linux内核中likely与unlikely_夜风~的博客-CSDN博客_linux unlikely](https://blog.csdn.net/u014470361/article/details/81193023)。

> 简单从表面上看 `if( likely(value) ){ }` 和 `if(unlikely(value)){ }else{ }`。
> 也就是likely和unlikely是一样的，但是实际上执行是不同的，加likely的意思是value的值为真的可能性更大一些，那么执行if的机会大，而unlikely表示value的值为假的可能性大一些，执行else机会大一些。
>
> 加上这种修饰，编译成二进制代码时likely使得if后面的执行语句紧跟着前面的程序，unlikely使得else后面的语句紧跟着前面的程序，这样就会被**cache预读取**，增加程序的**执行速度**。
>
> 用来引导gcc进行条件分支预测。在一条指令执行时，由于流水线的作用，CPU可以同时完成下一条指令的取指，这样可以提高CPU的利用率。在执行条件分支指令时，CPU也会预取下一条执行，但是如果条件分支的结果为跳转到了其他指令，那CPU预取的下一条指令就没用了，这样就降低了流水线的效率。
>
> 简单理解：
>
> - likely(x) 代表 x 是 逻辑真 的可能性比较大。
> - unlikely(x) 代表 x 是 逻辑假 的可能性比较大。

## 内核中错误处理

参考：

- [linux中ERR_PTR、PTR_ERR、IS_ERR和IS_ERR_OR_NULL_夜风~的博客-CSDN博客_linux ptr](https://blog.csdn.net/u014470361/article/details/81175817)。
- [ Linux内核使用ERR_PTR和PTR_ERR等函数来实现指针函数返回错误码_tanglinux的博客-CSDN博客](https://tanglinux.blog.csdn.net/article/details/78065586)。
- [Linux 内核IS_ERR函数 - 简书 (jianshu.com)](https://www.jianshu.com/p/7bc78698ed09)。
- [【Linux内核】Linux的errno和ERR_PTR、PTR_ERR简介_gccwdn的博客-CSDN博客](https://blog.csdn.net/u014001096/article/details/124896853)。

> linux内核中判断返回指针是否错误的内联函数主要有：**ERR_PTR、PTR_ERR、IS_ERR 和 IS_ERR_OR_NULL**等。
>
> 在写设备驱动程序的过程中，涉及到的任何一个指针，必然有三种情况：
>
> 1. **有效指针**；
> 2. **NULL，空指针**；
> 3. **错误指针，或者说无效指针**。
>    

## 内核中对字符串的操作

具体 API 用法看 [linux内核驱动中对字符串的操作【转】 - 走看看 (zoukankan.com)](http://t.zoukankan.com/sky-heaven-p-4826009.html)。

> ```c
> #include <linux/string.h>
> 
> int strnicmp(const char *s1, const char *s2, size_t len)  
> int strcasecmp(const char *s1, const char *s2)  
> int strncasecmp(const char *s1, const char *s2, size_t n)  
> char *strcpy(char *dest, const char *src)  
> char *strncpy(char *dest, const char *src, size_t count)  
> size_t strlcpy(char *dest, const char *src, size_t size)  
> char *strcat(char *dest, const char *src)  
> char *strncat(char *dest, const char *src, size_t count)  
> size_t strlcat(char *dest, const char *src, size_t count)  
> int strcmp(const char *cs, const char *ct)  
> int strncmp(const char *cs, const char *ct, size_t count)  
> char *strchr(const char *s, int c)  
> char *strrchr(const char *s, int c)  
> char *strnchr(const char *s, size_t count, int c)  
> char *skip_spaces(const char *str)  
> char *strim(char *s)  
> size_t strlen(const char *s)  
> size_t strnlen(const char *s, size_t count)  
> char *strpbrk(const char *cs, const char *ct)  
> char *strsep(char **s, const char *ct)  
> bool sysfs_streq(const char *s1, const char *s2)  
> void *memset(void *s, int c, size_t count)  
> void *memcpy(void *dest, const void *src, size_t count)  
> void *memmove(void *dest, const void *src, size_t count)  
> int memcmp(const void *cs, const void *ct, size_t count)  
> void *memscan(void *addr, int c, size_t size)  
> char *strstr(const char *s1, const char *s2)  
> char *strnstr(const char *s1, const char *s2, size_t len)  
> void *memchr(const void *s, int c, size_t n)  
> ```
>

## Linux 内核常见宏的作用

[Linux内核常见宏的作用_-CSDN博客](https://blog.csdn.net/thisway_diy/article/details/84621827)。
