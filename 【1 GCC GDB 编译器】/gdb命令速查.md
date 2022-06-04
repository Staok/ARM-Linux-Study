# GDB 命令速查



- [100-gdb-tips/index.md at master · hellogcc/100-gdb-tips (github.com)](https://github.com/hellogcc/100-gdb-tips/blob/master/src/index.md)。
- [GDB在线手册](https://sourceware.org/gdb/onlinedocs/gdb)。
- [GDB命令卡片](https://github.com/hellogcc/100-gdb-tips/blob/master/refcard.pdf)。
- [GDB dashboard](https://github.com/cyrus-and/gdb-dashboard)。
- [Gdbinit for OS X, iOS and others - x86, x86_64 and ARM](https://github.com/gdbinit/Gdbinit)。
- [dotgdb：关于底层调试和反向工程的gdb脚本集](https://github.com/dholm/dotgdb)。

------

以下引自 [100-gdb-tips/index.md at master · hellogcc/100-gdb-tips (github.com)](https://github.com/hellogcc/100-gdb-tips/blob/master/src/index.md)。

## 信息显示

- [显示gdb版本信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/show-version.md)
- [显示gdb版权相关信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/show-copying-warranty.md)
- [启动时不显示提示信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/start-gdb-silently.md)
- [退出时不显示提示信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/quit-gdb-silently.md)
- [输出信息多时不会暂停输出](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-pagination-off.md)

## 函数

- [列出函数的名字](https://github.com/hellogcc/100-gdb-tips/blob/master/src/info-function.md)
- [是否进入带调试信息的函数](https://github.com/hellogcc/100-gdb-tips/blob/master/src/step-and-next-function.md)
- [进入不带调试信息的函数](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-step-mode-on.md)
- [退出正在调试的函数](https://github.com/hellogcc/100-gdb-tips/blob/master/src/finish-and-return.md)
- [直接执行函数](https://github.com/hellogcc/100-gdb-tips/blob/master/src/call-func.md)
- [打印函数堆栈帧信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/info-frame.md)
- [打印尾调用堆栈帧信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-debug-entry-values.md)
- [选择函数堆栈帧](https://github.com/hellogcc/100-gdb-tips/blob/master/src/select-frame.md)
- [向上或向下切换函数堆栈帧](https://github.com/hellogcc/100-gdb-tips/blob/master/src/up-down-select-frame.md)

## 断点

- [在匿名空间设置断点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/break-anonymous-namespace.md)
- [在程序地址上打断点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/break-on-address.md)
- [在程序入口处打断点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/break-on-entry.md)
- [在文件行号上打断点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/break-on-linenum.md)
- [保存已经设置的断点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/save-breakpoints.md)
- [设置临时断点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-tbreak.md)
- [设置条件断点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-condition-break.md)
- [忽略断点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/ignore-break.md)

## 观察点

- [设置观察点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-watchpoint.md)
- [设置观察点只针对特定线程生效](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-watchpoint-on-specified-thread.md)
- [设置读观察点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-read-watchpoint.md)
- [设置读写观察点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-read-write-watchpoint.md)

## Catchpoint

- [让catchpoint只触发一次](https://github.com/hellogcc/100-gdb-tips/blob/master/src/tcatch.md)
- [为fork调用设置catchpoint](https://github.com/hellogcc/100-gdb-tips/blob/master/src/catch-fork.md)
- [为vfork调用设置catchpoint](https://github.com/hellogcc/100-gdb-tips/blob/master/src/catch-vfork.md)
- [为exec调用设置catchpoint](https://github.com/hellogcc/100-gdb-tips/blob/master/src/catch-exec.md)
- [为系统调用设置catchpoint](https://github.com/hellogcc/100-gdb-tips/blob/master/src/catch-syscall.md)
- [通过为ptrace调用设置catchpoint破解anti-debugging的程序](https://github.com/hellogcc/100-gdb-tips/blob/master/src/catch-ptrace.md)

## 打印

- [打印ASCII和宽字符字符串](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-ascii-and-wide-string.md)
- [打印STL容器中的内容](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-STL-container.md)
- [打印大数组中的内容](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-large-array.md)
- [打印数组中任意连续元素值](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-consecutive-array-elements.md)
- [打印数组的索引下标](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-array-indexes.md)
- [格式化打印数组](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-formatted-array.md)
- [打印函数局部变量的值](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-local-variables.md)
- [打印进程内存信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-process-memory.md)
- [打印静态变量的值](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-static-variables.md)
- [打印变量的类型和所在文件](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-variable-info.md)
- [打印内存的值](https://github.com/hellogcc/100-gdb-tips/blob/master/src/examine-memory.md)
- [打印源代码行](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-source-lines.md)
- [每行打印一个结构体成员](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-print-pretty-on.md)
- [按照派生类型打印对象](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-derived-type.md)
- [指定程序的输入输出设备](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-io-tty.md)
- [使用“$\_”和“$\__”变量](https://github.com/hellogcc/100-gdb-tips/blob/master/src/use-$_-$__-variables.md)
- [打印程序动态分配内存的信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-malloc-memory.md)
- [打印调用栈帧中变量的值](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-frame-variables.md)

## 多进程/线程

- [调试已经运行的进程](https://github.com/hellogcc/100-gdb-tips/blob/master/src/attach-process.md)
- [调试子进程](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-follow-fork-mode-child.md)
- [同时调试父进程和子进程](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-detach-on-fork.md)
- [查看线程信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-threads.md)
- [打印所有线程的堆栈信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-all-threads-bt.md)
- [在Solaris上使用maintenance命令查看线程信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/maint-info-sol-threads.md)
- [不显示线程启动和退出信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/show-print-thread-events.md)
- [只允许一个线程运行](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-scheduler-locking-on.md)
- [使用“$_thread”变量](https://github.com/hellogcc/100-gdb-tips/blob/master/src/use-$_thread-variable.md)
- [一个gdb会话中同时调试多个程序](https://github.com/hellogcc/100-gdb-tips/blob/master/src/add-copy-inferiors.md)
- [打印程序进程空间信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/maint-info-program-space.md)
- [使用“$_exitcode”变量](https://github.com/hellogcc/100-gdb-tips/blob/master/src/use-$_exitcode.md)

## core dump文件

- [为调试进程产生core dump文件](https://github.com/hellogcc/100-gdb-tips/blob/master/src/generate-core-dump-file.md)
- [加载可执行程序和core dump文件](https://github.com/hellogcc/100-gdb-tips/blob/master/src/load-executable-and-coredump-file.md)

## 汇编

- [设置汇编指令格式](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-disassembly-flavor.md)
- [在函数的第一条汇编指令打断点](https://github.com/hellogcc/100-gdb-tips/blob/master/src/break-on-first-assembly-code.md)
- [自动反汇编后面要执行的代码](https://github.com/hellogcc/100-gdb-tips/blob/master/src/disassemble-next-line.md)
- [将源程序和汇编指令映射起来](https://github.com/hellogcc/100-gdb-tips/blob/master/src/map-source-code-and-assembly.md)
- [显示将要执行的汇编指令](https://github.com/hellogcc/100-gdb-tips/blob/master/src/display-instruction-pc.md)
- [打印寄存器的值](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-registers.md)
- [显示程序原始机器码](https://github.com/hellogcc/100-gdb-tips/blob/master/src/disassemble-raw-machine-code.md)

## 改变程序的执行

- [改变字符串的值](https://github.com/hellogcc/100-gdb-tips/blob/master/src/change-string.md)
- [设置变量的值](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-var.md)
- [修改PC寄存器的值](https://github.com/hellogcc/100-gdb-tips/blob/master/src/modify-pc-register.md)
- [跳转到指定位置执行](https://github.com/hellogcc/100-gdb-tips/blob/master/src/jump.md)
- [使用断点命令改变程序的执行](https://github.com/hellogcc/100-gdb-tips/blob/master/src/breakpoint-command.md)
- [修改被调试程序的二进制文件](https://github.com/hellogcc/100-gdb-tips/blob/master/src/patch-program.md)

## 信号

- [查看信号处理信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/info-signals.md)
- [信号发生时是否暂停程序](https://github.com/hellogcc/100-gdb-tips/blob/master/src/stop-signal.md)
- [信号发生时是否打印信号信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/print-signal.md)
- [信号发生时是否把信号丢给程序处理](https://github.com/hellogcc/100-gdb-tips/blob/master/src/pass-signal.md)
- [给程序发送信号](https://github.com/hellogcc/100-gdb-tips/blob/master/src/send-signal.md)
- [使用“$_siginfo”变量](https://github.com/hellogcc/100-gdb-tips/blob/master/src/use-$_siginfo-variable.md)

## 共享库

- [显示共享链接库信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/info_sharedlibrary.md)

## 脚本

- [配置gdb init文件](https://github.com/hellogcc/100-gdb-tips/blob/master/src/config-gdbinit.md)
- [按何种方式解析脚本文件](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-script-extension.md)
- [保存历史命令](https://github.com/hellogcc/100-gdb-tips/blob/master/src/save-history-commands.md)

## 源文件

- [设置源文件查找路径](https://github.com/hellogcc/100-gdb-tips/blob/master/src/directory.md)
- [替换查找源文件的目录](https://github.com/hellogcc/100-gdb-tips/blob/master/src/substitute-path.md)

## 图形化界面

- [进入和退出图形化调试界面](https://github.com/hellogcc/100-gdb-tips/blob/master/src/tui-mode.md)
- [显示汇编代码窗口](https://github.com/hellogcc/100-gdb-tips/blob/master/src/layout-asm.md)
- [显示寄存器窗口](https://github.com/hellogcc/100-gdb-tips/blob/master/src/layout-regs.md)
- [调整窗口大小](https://github.com/hellogcc/100-gdb-tips/blob/master/src/winheight.md)

## 其它

- [命令行选项的格式](https://github.com/hellogcc/100-gdb-tips/blob/master/src/option-format.md)
- [支持预处理器宏信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/preprocessor-macro.md)
- [保留未使用的类型](https://github.com/hellogcc/100-gdb-tips/blob/master/src/keep-unused-types.md)
- [使用命令的缩写形式](https://github.com/hellogcc/100-gdb-tips/blob/master/src/use-short-command.md)
- [在gdb中执行shell命令和make](https://github.com/hellogcc/100-gdb-tips/blob/master/src/run-shell-command.md)
- [在gdb中执行cd和pwd命令](https://github.com/hellogcc/100-gdb-tips/blob/master/src/run-cd-pwd.md)
- [设置命令提示符](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-prompt.md)
- [设置被调试程序的参数](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-program-args.md)
- [设置被调试程序的环境变量](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-program-env.md)
- [得到命令的帮助信息](https://github.com/hellogcc/100-gdb-tips/blob/master/src/help.md)
- [记录执行gdb的过程](https://github.com/hellogcc/100-gdb-tips/blob/master/src/set-logging.md)