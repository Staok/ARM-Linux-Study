	@ 本程序仅仅是一个示例
	@ 不同ARM内核的中断向量表不同，具体看手册
	@ 现在的微处理器寄存器结构非常复杂，不建议硬刚芯片手册手写配置代码，直接参考厂家和网络高手的例子特别省事
	@ 一些基础的、不变的、规律性的则必须要会
	
	@ 中断的保存、恢复现场，以及分辨中断号和调用相应中断函数，Cortex M3/M4 是硬件完成的， Cortex A7 是软件实现的
	
	.text					@ 代码段(.text)，表示代码段
							@ 其他段介绍：
							@ 只读数据段(.rodata)：存放有初始值并且const修饰的全局类变量（全局变量或static修饰的局部变量）
							@ 数据段(.data)：存放有初始值的全局类变量
							@ 注释段(.comment)：存放注释，注释段里面的机器码是用来表示文字的
							@ 零初始化段(.bss)：存放没有初始值或初始值为0的全局类变量
							@ 注：bss段和注释段不保存在bin/elf文件中，
							@ 所以如果bss段的数据没有清0的话，没有初始值的变量在初始化时会是随机的，但个人觉得清不清0不是特别重要。
	
	.global start			@ .global 表示 start 是一个全局符号
	
start:						@ 程序入口
	@异常向量表
	b	reset				@ 0x00 reset
	ldr pc,=_undef			@ 0x04 undef 未定义指令异常
	ldr pc,=_swi_handler	@ 0x08 swi 软中断入口 （如果用 mov 指令有32M地址大小限制）
	ldr pc,=_pre_fetch		@ 0x0c prefetch abort
	ldr pc,=_data_abort		@ 0x10 data abort
	nop						@ 0x14 reserved
	ldr pc,=_irq			@ 0x18 irq
	ldr pc,=_fiq			@ 0x1c fiq
	
_undef:			.word		_undef
_swi_handler:	.word		_swi_handler
_pre_fetch:		.word		_pre_fetch
_data_abort:	.word		_data_abort
_irq:			.word		_irq
_fiq:			.word		_fiq


_swi_handler:
	stmfd sp!,{r0-r12,lr}	@ 把 r0-r12 和 lr 寄存器内容进栈，即保护现场
	sub r0,lr,#4			@ 软中断号被保存到 lr 寄存器的上一个指令地址，将其临时保存到 r0
	ldr r0,[r0]				@ 取 r0 保存的地址所指向的值
	bic r0,#0xff000000		@ 根据手册，软中断号被保存在低 24 位，则把高八位内容清 0
	bl swi_user_handle		@ 跳转到 swi_user_handle 软中断用户处理程序，并把下一指令的地址保存到 lr 中
	ldmfd sp!,{r0-r12,pc}^	@ 从栈恢复 r0-r12 寄存器内容，并把原来的 lr 内容 恢复到 pc 中，
							@ 并从 spsr（cpsr的影子寄存器）恢复到 cpsr，即恢复现场
swi_user_handle:
	@... 软中断的用户应用程序，可以调用 c 函数
	
	cmp r0,#2				@ 判断软中断号是否为2，是则执行后面尾缀带eq的指令
	moveq r7,#2
	
	cmp r0,#5				@ 判断软中断号是否为5，是则执行后面尾缀带eq的指令
	moveq r7,#5
	
	cmp r0,#7				@ 判断软中断号是否为7，是则执行后面尾缀带eq的指令
	moveq r7,#7
	
	ldr pc,lr				@ 跳回
	
_irq:
	sub lr,lr,#4
	stmfd sp!,{r0-r12,lr}
	bl irq_user_handle
	ldmfd sp!,{r0-r12,pc}^
	
irq_user_handle:
	@... 外中断的用户应用程序，可以调用 c 函数
	@并在用户程序中，从中断控制器的寄存器中读出当前的中断号，做相应的相应，然后清中断标志位
	@现在的微处理器寄存器结构非常复杂，不建议硬刚芯片手册手写配置代码，直接参考厂家和网络高手的例子特别省事
	
	ldr pc,lr

reset:
	ldr sp,=stack_base		@ 分配栈地址到 sp 寄存器
	msr cpsr,#0x10			@ 切换到 user 模式
	
	@... 用户应用程序，可以调用 c 函数
	
	swi 2					@ 触发软中断，自动跳转到软中断程序入口
							@ 并自动把返回地址（下一个指令的地址）保存到 LR 寄存器
							@ 并自动切换到 SVC（超级用户） 模式
	nop
	nop
	
	
	swi 5
	nop
	nop
	
	
	swi 7
	nop
	nop
	
	/*
		@ 这一段是调用 c 程序里面的 void print_test_string(unsigned int cpsr, char *str) 函数
		@ 给它传入的两个实参为 r0 和 r1
		@ 这时 ARM-THUMB procedure call standard（ARM-Thumb过程调用标准）所规定的
		mrs r0, cpsr
		ldr r1, =test_string
		bl print_test_string
	*/
	
	b reset					@ 返回 reset 地址，大循环

/*
		test_string:
			.string "test_string"	
*/
	
	@ 定义栈空间和地址，buf 为栈的开头地址，stack_base 为栈的尾地址，中间有 32 个 word 空间
	@ 我们使用进出栈的指令是 stmfd 和 ldmfd
	@ 这两个指令，为从 stack_base 开始向上递进存，向下递进取的顺序，与这里定义的顺序一致
	
	/*
		ldr sp,=0x80200000
		stmfd sp!, {r0-r2} @ 入栈
		ldmfd sp!, {r0-r2} @ 出栈
		
		结果：
				0x00000000
				...
				0x801FFFF4	-> 	R0
								R1
				0x80200000	-> 	R2	sp指针的移动方向：存向上，取向下
		
		也可以用下面指令，效果一样
		push {r0-r2} @ 入栈
		pop {r0-r2}  @ 出栈

	*/
	
	/*
		栈的存取方式
		栈的存取方式，为后进先出（LIFO），是由于进出栈指令的作用方式决定的，数据在栈指针处入栈时，
		如 stmfd sp!,{r0-r12,lr}，根据这个指令的含义，栈指针sp会根据数据存放的方向自增或自减，出栈的时候过程相反，
		在外界看来，这种方式就是只能在头部进出数据的线性表，从算法上来说是一种特殊的线性表，这种
		方式是由汇编指令和硬件的易实现性所决定的。
		
		堆是一块空闲空间，使用 malloc 函数来管理它，malloc 函数可以自己写
		
		"stack_base:" 这种带冒号的标签表示地址位置，通过其得到指令/数据地址
	*/
	.data					
buf:
	.space 32
stack_base:
	
	
	
	.end
