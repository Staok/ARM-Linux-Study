#ifndef _SOCKET_DEBUG_H
#define _SOCKET_DEBUG_H

/* 参考：
    WIN
    https://blog.csdn.net/qq_52484093/article/details/122535244
    https://blog.csdn.net/baidu_16370559/article/details/104646624
    https://blog.csdn.net/weixin_39990029/article/details/116734100

    LINUX
    https://www.cnblogs.com/jiangzhaowei/p/8261174.html
    https://www.cnblogs.com/duzouzhe/archive/2009/06/19/1506699.html
    https://blog.csdn.net/weixin_36828200/article/details/123754901
    100ask
    MYD
    BiscuitOS
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* 选择 win 端 编译 还是 linux 端编译，不注释为 win 编译，反之相反 */
// #define WIN_OR_LINUX

/* 关于连接：
    只要在一个局域网内（都接到一个 wifi 源 或者 通过网线交换机 接到一起），
    确保 server 程序启动时候 win 端的 防火墙 都是允许通过的，
    确认好 两端的 ip 地址，pc 端通过 ipconfig 查看（网线或者 wifi 的），linux 为 ifconfig，手机端的 网络调试助手 会显示本地的 ip
        确保 这些 ip 地址 除了最后一个数 都一样，且 子网掩码通常设置 255.255.255.0，网关 是 ip 地址 最后一个数为 1 其余均相同，
        就说明 这些 端 在一个局域网里面，就可以互通
*/

#define TEST_SERVER_PORT              8888
#define TEST_SERVER_ADDR_STR          "192.168.43.229"
    /* server 端的 ip 只可以为 0.0.0.0（INADDR_ANY） 和 127.0.0.1 
        和 192.168.43.229（pc wifi 连手机热点后 pc 的 ip） */
#define TEST_SERVER_LISTEN_CNT_MAX 5

#define TEST_CLIENT_AIM_PORT          8888
#define TEST_CLIENT_AIM_SOC_ADDR_STR      "169.254.54.99"
#define TEST_CLIENT_AIM_WIN_ADDR_STR      "169.254.54.36"
#define TEST_CLIENT_AIM_KPAX_ADDR_STR     "192.168.43.1"


#ifdef WIN_OR_LINUX

#include <winsock2.h>
// #include <winsock.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

/* mingw 即 win 平台 gcc 编译要引用库 -lwsock32 */

/* 记录 server 和 client 的 socket 句柄 的 全局变量 */
extern SOCKET socket_server_g;
extern SOCKET socket_client_g[TEST_SERVER_LISTEN_CNT_MAX];

SOCKET win_socket_TCP_server_init(unsigned char autoaddr, 
    const char* ip_str, const unsigned short port, 
    const unsigned short listen_cnt_max);
void win_socket_TCP_server_loop_handle(SOCKET socket_server);

SOCKET win_socket_TCP_client_init(unsigned char defaultaddr, 
    const char* ip_str, const unsigned short port);
void win_socket_TCP_client_loop_handle(SOCKET socket_client);


#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // htons() etc
#include <arpa/inet.h>  // inet_pton() etc
#include <netdb.h>      // getaddrinfo() etc

/* 记录 server 和 client 的 socket 句柄 的 全局变量 */
extern int socket_server_g;
extern int socket_client_g[TEST_SERVER_LISTEN_CNT_MAX];

int linux_socket_TCP_server_init(unsigned char autoaddr, 
    const char* ip_str, const unsigned short port, 
    const unsigned short listen_cnt_max);
void linux_socket_TCP_server_loop_handle(int socket_server);

int linux_socket_TCP_client_init(unsigned char defaultaddr, 
    const char* ip_str, const unsigned short port);
void linux_socket_TCP_client_loop_handle(int client_server);

#endif

/* socket API 错误返回

    socket()，accept() 错误返回 INVALID_SOCKET (不可默认为 -1)
    bind()，listen() 错误返回 SOCKET_ERROR (不可默认为 -1)
    connect()，send()，recv() 错误返回 SOCKET_ERROR (不可默认为 -1)

    socket、accept 错误返回 INVALID_SOCKET
    bind、listen、connect、send、setsockopt 等 错误返回 SOCKET_ERROR

*/

/* 列一些用到的结构体 和 转换用 API

—————————————————————— sockaddr_in 结构体 ——————————————————————
struct sockaddr_in
{
     short sin_family;          // 地址族 AF_INET（IPv4）
     u_short sin_port;          // 16位端口号，需使用网络字节顺序（大端），需要 htons(PORT) 转换
     struct in_addr sin_addr;   // 4 个 8 位 数 的 IP 地址 需使用网络字节顺序，详细见下边
        // 对服务器而言 对于 IPv4 来说，通配地址可以由 htonl(INADDR_ANY) 来指定，其值一般为 0。它告知内核去选择 IP 地址
     char sin_sero[8];          // 保留不用
};

其中 in_addr 结构体 在 win 下：
struct in_addr
{
    union
    {
        struct{ u_char s_b1,s_b2,s_b3,s_b4}S_un_b;
        struct{ u_short s_w1,s_w2}S_un_w;
        U_long S_addr;
    }S_un;
};

其中 in_addr 结构体 在 linux 下：
typedef uint32_t in_addr_t;
struct in_addr
  {
    in_addr_t s_addr;
  };


—————————————————————— sockaddr 结构体，socket API 用，
                但是内容结构与 sockaddr_in 一致，实际用 (struct sockaddr*)&sockaddr_in_data 来替代 ——————————————————————
struct sockaddr
{
    u_short sa_family;    // 协议地址族
    char sa_data[14];     // 协议地址
};

—————————————————————— 本机数据 大小端模式 与 网络传输需要的 大端 互转 ——————————————————————
网络字节顺序
合成和逆合成 网络传输数据包 时候用

htons 即 host to net short，l 即 long，以此类推

u_short htons(u_short hostshrot);   // 用于16位
    hostshrot :一个待转换的主机字节顺序的无符号的短整形数据。
    返回值为一个网络字节顺序的无符号的短整形数据。

u_long htonl(u_long hostlong);      // 32位
    hostlong :一个待转换的主机字节顺序的无符号的长整形数据。
    返回值为一个网络字节顺序的无符号的长整形数据。

u_shor ntohs(u_short netshort);    // 用于16位
    netshort ：一个待转换的网络字节数顺序的无符号短整形数据。
    返回值为一个主机字节顺序的无符号的短整形数据。

u_long ntohl(u_long netlong);      // 32位
    netlong ：一个待转换的网络字节顺序的无符号的长整形数据。
    返回值为一个主机字节顺序的无符号的长整形数据。


win 下 地址转换函数，即 IP 地址（IPv4） 字符串（exp "192.128.54.99"） 与 socket API 需要的 二进制串 in_addr 互转

char *inet_ntoa(struct in_addr in);
    in_addr 结构体 转 ip 字符串。inet_ntoa()的功能是将网络地址转换成“.”点隔的字符串格式。

unsigned long inet_addr(const char FAR *cp );
    ip 字符串 转 in_addr 结构体。inet_addr()的功能是将一个点分十进制的IP转换成一个长整数型数（u_long类型）


linux 下 地址转换函数，即 IP 地址（IPv4 或 IPv6） 字符串（exp "192.128.54.99"） 与 socket API 需要的 二进制串 in_addr 互转

ip 字符串 转 in_addr 结构体
int inet_pton(int af, const char * src, void* dst)
    af :使用的地址族，即 IPv4 为 AF_INET, IPv6 为 AF_INET6。
    src ：指向要转换的字符串形式的地址。
    dst ：指向用于保存转换后的结构变 IPv4 为 in_addr ，IPv6 为 in6_addr。
    例子：
    in_addr a;
    if(inet_pton(AF_INET,"192.168.1.1",&a) == 1)
    {
        cout << ntohl(a.S_un.S_addr) << endl;
    }

in_addr 结构体 转 ip 字符串
const char*inet_ntop(int af , const char* src, char *dst, socklen_t cnt);
    af :使用地址族：IPv4 ：AE_INET ，IPv6：AE_INET6。
    src ：指向转换的整形表示地址。
    dst ：指向保存转换结果的存储区。
    cnt ：dst所指向的缓存区的大小。
    例子：
    in_addr a;
    char b[20];
    a.S_un.S_addr = htonl(0XC0a801010);
    if(inet_ntop(AF_INET, &a, b, sizeof(b)) != NULL)
    {
        cout << b << endl;
    }

*/



#endif