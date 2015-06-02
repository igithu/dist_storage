/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file testsocket_client.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/03/05 18:34:08
 * @brief 
 *  
 **/

#include <stdio.h>
#include <unistd.h>

#include "rpc/socket_util.h"

using namespace std;
using namespace dist_storage;


int main() {
    int connect_fd = TcpConnect("127.0.0.1", "9910");

    if (connect_fd < 0) {
        printf("test client connect server failed!");
        return 0;
    }

    string send_str = "123456789|123456789";
    if (SendMsg(connect_fd, send_str) < 0) {
        printf("send msg error!\n");
    }

    string ss;
    if (RecvMsg(connect_fd, ss) < 0) {
        printf("erroe recv!");
    }
    printf("ss %s\n", ss.c_str());

    close(connect_fd);


    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
