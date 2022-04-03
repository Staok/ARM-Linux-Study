/* 在 vscode 上面编程，插件补全，在 win 或者 ubuntu 都可以 */

/* 都采用 doxgenxy 注释格式  */

/* 开头文件信息注释，包括作者、日期、版本 */


/* include 系统头文件  用户头文件 */



/* 预编译选择：degub或者relece
根据这个来选择  是否打印调试信息等等

 */


/* main */
int main(int argc, char* argv[])
{
    int cmd;
    
    /* 第一步：首先处理输入命令 */
    if(process_start_cmd(argc,argv,*cmd))
    {
        
        return (int)wrong;
    }
    
    /* 第二步：瞬时应用实现 */
    switch(cmd)
    {
        case 开灯:
            
            return (int)OK;
            break;
        case 关灯灯:
            
            return (int)OK;
            break;
        case 发射火箭:
            
            return (int)OK;
            break;
        
        default:break;
    }
    
    /* 第三步：循环应用实现 */
    for(;;)
    {
        /* 多进程/多线程创建 */
        /* 不用多个函数循环执行，用进程/线程做，这是操作系统，不是裸机 */
    }
    
    return (int)OK;
}


/* 首先处理输入命令，包含完善的不合规输入检测和提示信息 */
unsigned char process_start_cmd(int argc, char* argv[],int *cmd)
{
    return OK //制定返回类型枚举
}