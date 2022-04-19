# 驱动例子中的API总结说明

多处网搜和引用，侵删。

## 驱动程序内的

### 主次设备号相关

在内核中，用dev_t类型(其实就是一个32位的无符号整数)的变量来保存设备的**主次设备号**，其中高12位表示**主设备号**，低20位表示**次设备号**。

设备获得主次设备号有两种方式：一种是手动给定一个32位数，并将它与设备联系起来(即用某个函数注册)；另一种是调用系统函数给设备动态分配一个主次设备号。

与主次设备号相关的3个宏：

```c
#define MAJOR(dev)    ((dev)>>8)
#define MINOR(dev)    ((dev) & 0xff)
#define MKDEV(ma,mi)  ((ma)<<8 | (mi))
```

- MAJOR(dev_t dev)：根据设备号dev获得主设备号。
- MINOR(dev_t dev)：根据设备号dev获得次设备号。
- MKDEV(int major, int minor)：根据主设备号major和次设备号minor构建设备号。

### register_chrdev / unregister_chrdev

int register_chrdev(unsigned int major,const char*name,struct file_operations *fops);

其中参数major如果等于0，则表示采用系统动态分配的主设备号；不为0，则表示静态注册，范围为 1~255。

 name 是注册驱动的名子(出现在 /proc/devices)，fops 是 file_operations 结构。

### 字符设备创建

参考 [字符设备驱动编写流程以及大概框架_辣眼睛的Developer的博客-CSDN博客](https://blog.csdn.net/softwoker/article/details/45113221)。

这里面讲另外两种创建字符设备方式：cdev 方式 和混杂方式。详情看上面这个链接。

register_chrdev_region：对于 手动/静态 给定一个主次设备号（不推荐），使用以下函数：`int register_chrdev_region(dev_t first, unsigned int count, char *name);`。其中first是我们手动给定的设备号，count是所请求的连续设备号的个数，而name是和该设备号范围关联的设备名称，它将出现在/proc/devices和sysfs中。比如，若first为0x3FFFF0，count为0x5，那么该函数就会为5个设备注册设备号，分别是0x3FFFF0、 0x3FFFF1、 0x3FFFF2、 0x3FFFF3、 0x3FFFF4。用这种方法注册设备号有一个缺点，那就是若该驱动module被其他人广泛使用，那么无法保证注册的设备号是其他人的Linux系统中未分配使用的设备号。

alloc_chrdev_region：对于动态分配设备号，使用以下函数：`int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);`。该函数需要传递给它指定的第一个次设备号firstminor(一般为0)和要分配的设备数count，以及设备名，调用该函数后自动分配得到的设备号保存在dev中。**次设备号可以指定，主设备号不能指定只能内核动态分配。**动态分配设备号可以避免手动指定设备号时带来的缺点，但是它却也有自己的缺点，那就是无法预知在/dev下创建设备节点是什么名字，因为动态分配设备号不能保证在每次加载驱动module时始终一致，这个缺点可以避免，因为在加载驱动module后，我们可以读取/proc/devices文件以获得Linux内核分配给该设备的主设备号。

```c
struct cdev {
	struct kobject kobj;
	struct module *owner;
	const struct file_operations *ops; // 文件操作函数
	struct list_head list;
	dev_t dev;   //设备号（包括主次设备号）
	unsigned int count;   //设备个数
};
```

100ask 的例子，01b_hello_drv 里面的：

```c
static struct cdev hello_cdev;
static struct file_operations hello_drv = {...};
...
rc = alloc_chrdev_region(&devid, 0, 1, "hello"); // 直接动态分配 dev_t 类型的设备号，其中包含了主、次涉设备号
cdev_init(&hello_cdev, &hello_drv); // cdev->ops = fops，将 &hello_drv 赋值给 &hello_cdev->ops
cdev_add(&hello_cdev, devid, 1); // 将设备号添加进cdev里的dev设备号成员，并向内核注册cdev

然后就是创建设备类 class_create 和创建设备 device_create
```

更多例程：[字符设备驱动框架3：深入探讨—完整的驱动代码工程_欧阳海宾的博客-CSDN博客](https://blog.csdn.net/oyhb_1992/article/details/77596411)，看看理解就好，这个例子并不通用。

### class_create / class_destroy

### device_create / device_destroy

### module_init / module_exit

修饰本模块的 加载 和 卸载 时候 调用的函数。

### 总线平台驱动相关

参考 [Linux Platform驱动模型(一) _设备信息_Neilo_chen的博客-CSDN博客](https://blog.csdn.net/cjianeng/article/details/122776618)，[关于platform_device一些讲解_Leo丶Fun的博客-CSDN博客_platform_device](https://blog.csdn.net/weixin_38233274/article/details/109093673)。

结构体成员只取一部分进行展示。

#### platform_device 详细

```c
//include/linux/platform_device.h
 22 struct platform_device {                                    
 23         const char      *name;
 24         int             id;
 25         bool            id_auto;
 26         struct device   dev;
 27         u32             num_resources;
 28         struct resource *resource;
 29 
 30         const struct platform_device_id *id_entry;
 31 
 32         /* MFD cell pointer */
 33         struct mfd_cell *mfd_cell;
 34 
 35         /* arch specific additions */
 36         struct pdev_archdata    archdata;
 37 };

--23-->name就是设备的名字，注意， 模块名(lsmod)!=设备名(/proc/devices)!=设备文件名(/dev)，这个名字就是驱动方法和设备信息匹配的桥梁
--24-->表示这个platform_device对象表征了几个设备，当多个设备有共用资源的时候(MFD)，里面填充相应的设备数量，如果只是一个，填-1
--26-->父类对象(include/linux/device.h +722)，我们通常关心里面的platform_data和release,前者是用来存储私有设备信息的，后者是供当这个设备的最后引用被删除时被内核回调，注意和rmmod没关系。
--27-->资源的数量，即resource数组中元素的个数，我们用ARRAY_SIZE()宏来确定数组的大小(include/linux/kernel.h +54 #define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) )
--28-->资源指针，如果是多个资源就是struct resource[]数组名，

struct device {
    void   *driver_data;   /* data private to the driver */
    void   *platform_data; /* Platform specific data, device core doesn't touch it */
    struct device_node	*of_node; /* associated device tree node */ /* 支持设备树的 device 用于匹配 支持设备树的 driver */
    void	(*release)(struct device *dev);
    ...
};
struct device_node {
    const char *name;
    const char *type;
    phandle phandle;
    const char *full_name;
    struct property *properties; /* 含有 compatible 属性，用于匹配 支持设备树的 driver */
};

struct resource {  
    resource_size_t start;      //资源的起始值  
    resource_size_t end;        //资源的结束值  
    const char *name;  
    unsigned long flags;        //资源的类型，如 IORESOURCE_IO,IORESOURCE_MEM,IORESOURCE_IRQ,IORESOURCE_DMA  
    struct resource *parent, *sibling, *child;  
}; 

start表示资源开始的位置，如果是IO地址资源，就是起始物理地址，如果是中断资源，就是中断号;
end表示资源结束的位置，如果是IO地址地址，就是映射的最后一个物理地址，如果是中断资源，就不用填;
name就是这个资源的名字。
flags表示资源类型，提取函数在寻找资源的时候会对比自己传入的参数和这个成员，理论上只要和可以随便写，但是合格的工程师应该使用内核提供的宏，这些宏也在"ioport.h"中进行了定义，比如IORESOURCE_MEM表示这个资源是地址资源，IORESOURCE_IRQ表示这个资源是中断资源

//include/linux/ioport.h
#define IORESOURCE_BITS         0x000000ff      /* Bus-specific bits */
#define IORESOURCE_TYPE_BITS    0x00001f00      /* Resource type */
#define IORESOURCE_IO           0x00000100      /* PCI/ISA I/O ports */
#define IORESOURCE_MEM          0x00000200
#define IORESOURCE_REG          0x00000300      /* Register offsets */
#define IORESOURCE_IRQ          0x00000400          
#define IORESOURCE_DMA          0x00000800
#define IORESOURCE_BUS          0x00001000
...
#define DEFINE_RES_IO(_start, _size)   
#define DEFINE_RES_MEM(_start, _size)   
#define DEFINE_RES_IRQ(_irq)  
#define DEFINE_RES_DMA(_dma)   

下面是一个资源数组的实例，多个资源的时候就写成数组
struct resource res[] = {
	[0] = {
		.start	= 0x10000000,
		.end	= 0x20000000-1,
		.flags	= IORESOURCE_MEM
	},
	[1] = DEFINE_RES_MEM(0x20000000, 1024),
	[2] = {
		.start	= 10,   //中断号
		.flags	= IORESOURCE_IRQ|IRQF_TRIGGER_RISING //include/linux/interrupt.h
	},
	[3] = DEFINE_RES_IRQ(11),	
};

————————————另一个例子———————————————
static struct resource pxa27x_ohci_resources[] = {
 [0] = {
  .start  = 0x4C000000,
  .end    = 0x4C00ff6f,
  .flags  = IORESOURCE_MEM,
 },
 [1] = {
  .start  = IRQ_USBH1,
  .end    = IRQ_USBH1,
  .flags  = IORESOURCE_IRQ,
 },
};
static struct platform_device ohci_device = {
 .name  = "pxa27x-ohci",
 .id  = -1,
 .dev  = {
  .dma_mask = &pxa27x_dmamask,
  .coherent_dma_mask = 0xffffffff,
 },
 .num_resources  = ARRAY_SIZE(pxa27x_ohci_resources),  // 这里填入 struct resource 结构体数组的 结构体个数
 .resource       = pxa27x_ohci_resources,
};

———————————100ask例子———————————————————
static struct resource resources[] = {
    {
        .start = GROUP_PIN(3,1),
        .flags = IORESOURCE_IRQ,
        .name = "100ask_led_pin",
    },
    {
        .start = GROUP_PIN(5,8),
        .flags = IORESOURCE_IRQ,
        .name = "100ask_led_pin",
    },
};
static struct platform_device board_A_led_dev = {
    .name = "100ask_led",
    .num_resources = ARRAY_SIZE(resources),
    .resource = resources,
    .dev = {
        .release = led_dev_release,
    },
};
```

```c
/**
 *注册：把指定设备添加到内核中平台总线的设备列表，等待匹配,匹配成功则回调驱动中probe；
 */
int platform_device_register(struct platform_device *);

/**
 *注销：把指定设备从设备列表中删除，如果驱动已匹配则回调驱动方法和设备信息中的release；
 */
void platform_device_unregister(struct platform_device *);

通常，我们会将platform_device_register写在模块加载的函数中，将platform_device_unregister写在模块卸载函数中。
```

#### platform_driver 详细

```c
struct platform_driver {
	int (*probe)(struct platform_device *); /* driver 与 device 匹配成功之后调用该函数，一般进行获取资源和创建设备 */
	int (*remove)(struct platform_device *);
	void (*shutdown)(struct platform_device *);
	int (*suspend)(struct platform_device *, pm_message_t state);
	int (*resume)(struct platform_device *);
	struct device_driver driver;
	const struct platform_device_id *id_table;
};

struct platform_device_id {
	char name[PLATFORM_NAME_SIZE];
	kernel_ulong_t driver_data
			__attribute__((aligned(sizeof(kernel_ulong_t))));
};

struct device_driver {
	const char		*name; /* drvier 名字，用于 device 匹配 */
	struct bus_type		*bus;
 
	struct module		*owner;
	const char		*mod_name;	/* used for built-in modules */
 
	bool suppress_bind_attrs;	/* disables bind/unbind via sysfs */
 
	const struct of_device_id	*of_match_table; /* 用于支持设备树的 driver 匹配支持设设备树的 device */
	const struct acpi_device_id	*acpi_match_table;
 
	int (*probe) (struct device *dev);
	int (*remove) (struct device *dev);
	void (*shutdown) (struct device *dev);
	int (*suspend) (struct device *dev, pm_message_t state);
	int (*resume) (struct device *dev);
	const struct attribute_group **groups;
 
	const struct dev_pm_ops *pm;
 
	struct driver_private *p;
};

struct of_device_id
{
    undefined
    char name[32];
    char type[32];
    char compatible[128]; // 用于 device 和 driver 的 match
    const void *data;
};

———————100ask例子———————————
static struct platform_driver chip_demo_gpio_driver = {
    .probe      = chip_demo_gpio_probe, /* 创建设备 device_create，记录资源 */
    .remove     = chip_demo_gpio_remove, /* 删除设备 device_destroy */
    .driver     = {
        .name   = "100ask_led",
    },
};
```



#### platform_get_xxx 获取资源

可参考 [linux （platform_driver）平台设备驱动常用API函数 (icode9.com)](https://www.icode9.com/content-3-637874.html)。

```c
struct resource *platform_get_resource(struct platform_device *dev, unsigned int type, unsigned int num);

功能：通过探测函数中有设备指针获得设备结构中的指定类型的资源结构地址。 这个函数是在驱动层的探测函数使用
参数： 
    dev ： 设备指针 ，实际就是探测函数参数
	type： 资源类型
	num：同类资源进行重新编号后的下标编号，和设备层中的资源数组不相同。（要注意这一点）
返回值：设备层资源结构数组中对应的资源结构首地址。 NULL:失败

unsigned int type决定资源的类型，unsigned int num决定type类型的第几份资源（从0开始）。即使同类型资源在资源数组中不是连续排放也可以定位得到该资源。
比如第一份IORESOURCE_IRQ类型资源在resource[2]，而第二份在resource[5]，那platform_get_resource(pdev,IORESOURCE_IRQ,0);可以定位第一份IORESOURCE_IRQ资源；platform_get_resource(pdev,IORESOURCE_IRQ,1);可以定位第二份IORESOURCE_IRQ资源。
```

```c
int platform_get_irq(struct platform_device *dev, unsigned int num);

功能： 通过设备指针获得设备结构中的指定编号的中断资源起始编号
参数：
	dev ：设备指针 ，实际就是探测函数参数
	num：同类资源进行重新编号后的下标编号，和设备层中的资源数组不相同。（要注意这一点）
返回值： >0 ：中断资源中的起始编号； -ENXIO：失败
```

```c
struct resource *platform_get_resource_byname(struct platform_device *dev,unsigned int type, const char *name);

功能：通过设备指针获得设备结构中的指定名字指定类型的资源结构内存地址
参数：
	dev ：设备指针 ，实际就是探测函数参数
	name：资源名
返回值：设备层资源结构数组中对应的资源结构首地址。 NULL:失败
```

```c
int platform_get_irq_byname(struct platform_device *dev, const char *name);

功能：通过设备指针获得设备结构中的指定名字的中断资源起始编号
参数：
	dev ：设备指针 ，实际就是探测函数参数
	name：中断资源名
返回值： >0 ：中断资源中的起始编号； -ENXIO：失败
```

## 其它用到的 API

### copy_from_user / copy_to_user

内核空间的数据与 应用/用户进程 的数据相互之间的拷贝。

### ioremap / iounmap 

用来将物理地址映射到一个虚拟地址，内核进程通过该虚拟地址访问到实际物理地址，安全。

把物理地址phys_addr开始的一段空间(大小为size)，映射为虚拟地址；返回值是该段虚拟地址的首地址。

`virt_addr = ioremap(phys_addr, size);`

实际上，它是按页(4096字节)进行映射的，是整页整页地映射的。

假设phys_addr = 0x10002，size=4，ioremap的内部实现是：

a. phys_addr按页取整，得到地址0x10000

b. size按页取整，得到4096

c. 把起始地址0x10000，大小为4096的这一块物理地址空间，映射到虚拟地址空间，

  假设得到的虚拟空间起始地址为0xf0010000

d. 那么phys_addr = 0x10002对应的virt_addr = 0xf0010002

### EXPORT_SYMBOL

a.c编译为a.ko，里面定义了func_a；如果它想让b.ko使用该函数，那么a.c里需要导出此函数。即 如果 a.c, b.c 分别编译出两个 .ko，即 a.ko 和 b.ko，则需使用这个来导出。并且，使用时要先加载a.ko。如果先加载b.ko，会有类似如下“Unknown symbol”的提示。

如果 a.c, b.c 编译在一起，编译出一个 .ko，则无需使用这个来导出。

### file_inode / iminor

参考 [字符设备驱动框架2：设备文件(设备节点)如何和驱动建立联系-Linux字符设备中的两个重要结构体(file、inode)_欧阳海宾的博客-CSDN博客](https://blog.csdn.net/oyhb_1992/article/details/77110676) 就比较清楚了。

> 一般而言在驱动程序的设计中，会关系 struct file 和 struct inode 这两个结构体。
>
> 用户空间使用open()系统调用函数打开一个字符设备时（ int fd = open("dev/demo", O_RDWR) ）大致有以下过程：
>
> 1. 在虚拟文件系统VFS中的查找对应与字符设备对应 struct inode节点
> 2. 遍历字符设备列表（chardevs数组），根据inod节点中的 cdev_t设备号找到cdev对象
> 3. 创建struct file对象（系统采用一个数组来管理一个进程中的多个被打开的设备，每个文件秒速符作为数组下标标识了一个设备对象）
> 4. 初始化struct file对象，将 struct file对象中的 file_operations成员指向 struct cdev对象中的 file_operations成员（file->fops =  cdev->fops）
> 5. 回调file->fops->open函数
>
> **inode 结构体**
>
> ​     VFS inode 包含文件访问权限、属主、组、大小、生成时间、访问时间、最后修改时间等信息。它是Linux 管理文件系统的最基本单位，也是文件系统连接任何子目录、文件的桥梁。
>
> ​    内核使用inode结构体在内核内部表示一个文件。因此，它与表示一个已经打开的文件描述符的结构体(即file 文件结构)是不同的，我们可以使用多个file 文件结构表示同一个文件的多个文件描述符，但此时，所有的这些file文件结构全部都必须只能指向一个inode结构体。
>
>    inode结构体包含了一大堆文件相关的信息，但是就针对驱动代码来说，我们只要关心其中的两个域即可：
>
> 1. dev_t i_rdev;   表示设备文件的结点，这个域实际上包含了设备号。
> 2. struct cdev *i_cdev;　　struct cdev是内核的一个内部结构，它是用来表示字符设备的，当inode结点指向一个字符设备文件时，此域为一个指向inode结构的指针。
>
> **file 文件结构体**
>
> ​    在设备驱动中，这也是个非常重要的数据结构，必须要注意一点，这里的file与用户空间程序中的FILE指针是不同的，用户空间FILE是定义在C库中，从来不会出现在内核中。而struct file，却是内核当中的数据结构，因此，它也不会出现在用户层程序中。
>
> ​    file结构体指示一个已经打开的文件（设备对应于设备文件），其实系统中的每个打开的文件在内核空间都有一个相应的struct file结构体，它由内核在打开文件时创建，并传递给在文件上进行操作的任何函数，直至文件被关闭。如果文件被关闭，内核就会释放相应的数据结构。
>
>    在内核源码中，struct file要么表示为file，或者为filp(意指“file pointer”), 注意区分一点，file指的是struct file本身，而filp是指向这个结构体的指针。

- 在 xxx_write() 和 xxx_read() 函数里面，实际控制一个设备类下面的哪一个设备，根据子设备号，获取通过 file_inode() 根据 file 得到文件的 inode，再用 iminor() 根据 inode 得到子/次设备号。

  ```c
  /* 提取主设备号 */
  static inline unsigned imajor(const struct inode *inode)
  {
  　　return MAJOR(inode->i_rdev);
  }
  /* 提取次设备号 */
  static inline unsigned iminor(const struct inode *inode)
  {
  　　return MINOR(inode->i_rdev);
  }
  ```

  

- 在 xxx_open() 和 xxx_close() 里面 可以根据 int minor = iminor(node); 直接获得次设备号（来或者这一个外设的哪一个具体资源）。

### kmalloc / kfree

驱动中申请内存。释放用 kfree。使用详见 [ linux中kmalloc函数详解_fulinux的博客-CSDN博客_kmalloc linux](https://fulinux.blog.csdn.net/article/details/8635234)。

# 申请内存资源函数

参考 [linux （platform_driver）平台设备驱动常用API函数 (icode9.com)](https://www.icode9.com/content-3-637874.html)。

申请内存资源函数

- request_region
- request_mem_region
-  devm_request_region
- devm_request_mem_region

释放内存资源

- release_region
- release_ mem_region
- devm_release_region
- devm_release_mem_region

## request_region

> 原型：
> \#define request_region(start,n,name) __request_region(&ioport_resource, (start), (n), (name), 0)
> 功能：向内核申请一段 IO 端口（**IORESOURCE_IO** 类型的）**（不常用）**
> 参数：
> start：起始地址
> n： 连续大小
> name：使用者名字，用于内核登记。
> 返回值：
> 非 NULL：申请成功的资源结构内存地址 struct resource *
> NULL： 所申请的 IO 端口资源已经被别人占用了，申请失败。

## request_mem_region

> 原型：
> \#define **request_mem_region**(start,n,name) __request_region(&iomem_resource, (start), (n), (name), 0)
> 功能：向内核申请一段 IO 内存（**IORESOURCE_MEM**类型的）
> 参数：
> start：起始地址
> n：连续大小
> name：使用者名字，用于内核登记。
> 返回值：
> 非 NULL：申请成功的资源结构内存地址 struct resource *
> NULL： 所申请的 IO 内存资源已经被别人占用了，申请失败。
> 这个宏在实际编程中使用非常多。

##  devm_request_region

> 原型：
> \#define devm_request_region(dev,start,n,name) \
> __devm_request_region(dev, &ioport_resource, (start), (n), (name))
> 功能：向内核申请一段 IO 端口（**IORESOURCE_IO** 类型的） ,功能上和 request_region 相同
> 参数：
> dev：设备指针， struct device *
> start：起始地址
> n：连续大小
> name：使用者名字，用于内核登记。
> 返回值：
> 非 NULL：申请成功的资源结构内存地址 struct resource *
> NULL： 所申请的 IO 端口资源已经被别人占用了，申请失败。

##  devm_request_mem_region

> 原型：
> #define devm_request_mem_region(dev,start,n,name) \
> __devm_request_region(dev, &iomem_resource, (start), (n), (name))
> 功能：向内核申请一段 IO 内存（IORESOURCE_MEM 类型的）（**常用来申请IO寄存器**）
> 参数：
> dev：设备指针， struct device *
> start：起始地址
> n：连续大小
> name：使用者名字，用于内核登记。
> 返回值：
> 非 NULL：申请成功的资源结构内存地址 struct resource *
> NULL： 所申请的 IO 内存资源已经被别人占用了，申请失败。
> 这个宏在实际编程中使用非常多。

# 释放内存资源

## release_region

> 原型：
> \#define release_region(start,n) __release_region(&ioport_resource, (start), (n))
> 功能：释放一段使用 request_region 申请的 Io 端口空间。
> 参数：
>
> start：起始地址
> n：连续大小

## release_ mem_region

> \#define release_mem_region(start,n) __release_region(&iomem_resource, (start), (n))
> 功能：释放一段使用 request_mem_region 申请的 Io 内存空间。
> 参数：
> start：起始地址
> n：连续大小

## devm_release_region

> __devm_release_region(dev, &ioport_resource, (start), (n))
> 这个宏和前面 release_region 相同，只是多了一个 dev 设备指针参数，类型为 struct device *

## devm_release_mem_region

> \#define devm_release_mem_region(dev, start, n) \
> __devm_release_region(dev, &iomem_resource, (start), (n))
> 这个宏和前面 release_mem_region 相同，只是多了一个 dev 设备指针参数，类型为 struct device *