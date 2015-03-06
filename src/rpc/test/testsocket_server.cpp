/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file testsocket_server.cpp
 * @author aishuyu(com@baidu.com)
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

    printf("errno is %s , listenfd %d\n", strerror(errno), listenfd);
    while (true) {
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
        close(cfd);
    }
    close(listenfd);

    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
