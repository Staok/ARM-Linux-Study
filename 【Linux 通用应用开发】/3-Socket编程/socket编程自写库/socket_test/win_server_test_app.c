#include <stdio.h>
#include <stdlib.h>

#include "socket.h"

/* 编译命令：
    gcc win_server_test_app.c .//socket.c -I .// -lwsock32 -o win_server_test_app.exe
*/
int main(void)
{
    win_socket_TCP_server_loop_handle(win_socket_TCP_server_init(
        1,
        TEST_SERVER_ADDR_STR,
        TEST_SERVER_PORT,
        1
    ));

    return 0;
}