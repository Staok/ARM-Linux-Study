#include <stdio.h>
#include <stdlib.h>

#include "socket.h"

/* 编译命令：
    gcc win_client_test_app.c .//socket.c -I .// -lwsock32 -o win_client_test_app.exe
*/
int main(void)
{
    win_socket_TCP_client_loop_handle(win_socket_TCP_client_init(
        0,
        TEST_CLIENT_AIM_WIN_ADDR_STR,
        TEST_CLIENT_AIM_PORT
    ));
    return 0;
}