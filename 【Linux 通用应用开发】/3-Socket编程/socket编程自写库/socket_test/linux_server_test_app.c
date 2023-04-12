#include <stdio.h>
#include <stdlib.h>

#include "socket.h"

/* 编译命令：
    (交叉编译器名) linux_server_test_app.c .//socket.c -I .// -o linux_server_test_app.exe
    
    对于 i.mx8mm 就是
    $CC linux_server_test_app.c ./socket.c -I ./ -o linux_server_test_app.app
*/
int main(void)
{
    linux_socket_TCP_server_loop_handle(linux_socket_TCP_server_init(
        1,
        TEST_SERVER_ADDR_STR,
        TEST_SERVER_PORT,
        1
    ));

    return 0;
}