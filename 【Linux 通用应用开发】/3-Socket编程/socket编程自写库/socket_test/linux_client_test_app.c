#include <stdio.h>
#include <stdlib.h>

#include "socket.h"

/* 编译命令：
    (交叉编译器名) linux_client_test_app.c .//socket.c -I .// -o linux_client_test_app.exe
    
    对于 i.mx8mm 就是
    $CC linux_client_test_app.c ./socket.c -I ./ -o linux_client_test_app.app
*/
int main(void)
{
    linux_socket_TCP_client_loop_handle(linux_socket_TCP_client_init(
        0,
        TEST_CLIENT_AIM_WIN_ADDR_STR,
        TEST_CLIENT_AIM_PORT
    ));
    
    return 0;
}