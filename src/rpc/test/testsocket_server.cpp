/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file testsocket_server.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/03/05 18:35:20
 * @brief 
 *  
 **/

#include <errno.h>

#include "rpc/socket_util.h"


using namespace std;
using namespace dist_storage;

int main() {
    printf("Start\n");

    const char* addr = "127.0.0.1";
    const char* port = "9910";
    int32_t listenfd = TcpListen(addr, port, AF_UNSPEC,  false);

    if (listenfd < 0) {
        printf("Listen failed!\n");
        printf("errno is %s\n", strerror(errno));
        return 0;
    }

    fd_set fds;
    struct timeval tv;
    int32_t max_sock;


    printf("errno is %s , listenfd %d\n", strerror(errno), listenfd);
    while (true) {
        FD_ZERO(&fds);
        FD_SET(listenfd, &fds)

        struct sockaddr_in client_addr;
        socklen_t len = sizeof(struct sockaddr_in);
        int32_t cfd = Accept(listenfd, client_addr, len);
        if (cfd < 0) {
            printf("Accept error, errno is %s\n", strerror(errno));
            return 0;
        }

        string recv_msg_str;
        if (RecvMsg(cfd, recv_msg_str) < 0) {
            printf("recv msg failed!\n");
        }
        printf("recv_msg_str is %s.\n", recv_msg_str.c_str());
        string send_str = recv_msg_str;
        if (SendMsg(cfd, send_str) < 0) {
            printf("send msg failed!\n");
        }
        close(cfd);
    }
    close(listenfd);

    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
