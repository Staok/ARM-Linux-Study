#include <linux/module.h>

#include <linux/fs.h>
#include <linux/io.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include <asm/io.h>

#include "button_drv.h"


struct stm32mp157_gpio {
  volatile unsigned int MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  volatile unsigned int OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  volatile unsigned int OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  volatile unsigned int PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  volatile unsigned int IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  volatile unsigned int ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  volatile unsigned int BSRR;     /*!< GPIO port bit set/reset,               Address offset: 0x18      */
  volatile unsigned int LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  volatile unsigned int AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} ;


/* RCC_PLL4CR */
static volatile unsigned int *RCC_PLL4CR; 

/* RCC_MP_AHB4ENSETR */
static volatile unsigned int *RCC_MP_AHB4ENSETR; 

static struct stm32mp157_gpio *gpiog; /* KEY1: PG3, KEY2: PG2 */

static void board_stm32mp157_button_init (int which) /* 初始化button, which-哪个button */      
{
    if (!RCC_PLL4CR)
    {
        RCC_PLL4CR = ioremap(0x50000000 + 0x894, 4);
        RCC_MP_AHB4ENSETR = ioremap(0x50000000 + 0xA28, 4);

        gpiog = ioremap(0x50008000, sizeof(struct stm32mp157_gpio));
    }

    if (which == 0)
    {
        /* 1. enable PLL4 
         * CG15, b[31:30] = 0b11
         */
		*RCC_PLL4CR |= (1<<0);
		while((*RCC_PLL4CR & (1<<1)) == 0);

		/* 2. enable GPIOG */
		*RCC_MP_AHB4ENSETR |= (1<<6);
		
		/* 3. 设置PG3为GPIO模式, 输入模式 
		 */
		gpiog->MODER &= ~(3<<6);
        
    }
    else if(which == 1)
    {
        /* 1. enable PLL4 
         * CG15, b[31:30] = 0b11
         */
		*RCC_PLL4CR |= (1<<0);
		while((*RCC_PLL4CR & (1<<1)) == 0);

		/* 2. enable GPIOG */
		*RCC_MP_AHB4ENSETR |= (1<<6);
		
		/* 3. 设置PG2为GPIO模式, 输入模式 
		 */
		gpiog->MODER &= ~(3<<4);
    }
    
}

static int board_stm32mp157_button_read (int which) /* 读button, which-哪个 */
{
    //printk("%s %s line %d, button %d, 0x%x\n", __FILE__, __FUNCTION__, __LINE__, which, *GPIO1_DATAIN);
    if (which == 0)
        return (gpiog->IDR & (1<<3)) ? 1 : 0;
    else
        return (gpiog->IDR & (1<<2)) ? 1 : 0;
}
    
static struct button_operations my_buttons_ops = {
    .count = 2,
    .init = board_stm32mp157_button_init,
    .read = board_stm32mp157_button_read,
};

int board_stm32mp157_button_drv_init(void)
{
    register_button_operations(&my_buttons_ops);
    return 0;
}

void board_stm32mp157_button_drv_exit(void)
{
    unregister_button_operations();
}

module_init(board_stm32mp157_button_drv_init);
module_exit(board_stm32mp157_button_drv_exit);

MODULE_LICENSE("GPL");

