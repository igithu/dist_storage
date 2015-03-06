/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file data_server.cc
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/10 16:43:11
 * @brief 
 *  
 **/

#include <signal.h>
#include <stdio.h>
#include <fcntl.h>

#include "data_service.h"
#include "heartbeat_thread.h"
#include "rpc/rpc_server.h"
#include "config/config_manager.h"
#include "common/ds_log.h"
#include "common/tools.h"

using namespace dist_storage;
using namespace dist_storage::data_server;
using namespace PUBLIC_UTIL;

inline void InitSignal() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    if (-1 == sigaction(SIGPIPE, &sa, NULL)) {
        exit(1);
    }
}

inline void Daemonize() {
    if (0 != fork()) {
        exit(0);
    }
    if (-1 == setsid()) {
        fprintf(stderr, "set sid error!\n");
        exit(-1);
    }
    umask(0);
    int fd = open("/dev/null", O_RDWR, 0);
    if (-1 != fd) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) {
            close(fd);
        }
    }  
}

int main(int argc, char* argv[]) {
    InitSignal();


    if (true) {
         Daemonize();
    }
    if (!DS_SYS_CONF.ConfigInit("../conf/data_server.ini")) {
        DS_LOG(ERROR, "init the data server config failed!");
        return 0;
    }

    const char* log_dir = DS_SYS_CONF.IniGetString("log:path");

    if (!CreateDir(log_dir)) {
        DS_LOG(ERROR, "create log dir: %s faied!", log_dir);
        return 0;
    }
    if (false == DSLogInit(
                argc, argv, DS_SYS_CONF.IniGetString("log:level"), log_dir)) {
        return 0;
    }

    const char* addr = DS_SYS_CONF.IniGetLocalIPAddr();
    const char* port = DS_SYS_CONF.IniGetString("data_service:port");
    int32_t thread_num = DS_SYS_CONF.IniGetInt("data_service:threadpool_num");

    DS_LOG(INFO, "get the rpc sever....");
    RpcServer& rpc_server = RpcServer::GetInstance();
    DataServiceImpl service;
    rpc_server.RegisteService(&service);
    DS_LOG(INFO, "Start the rpc sevice....");
    rpc_server.Start(thread_num, addr, port);

    DS_LOG(INFO, "Init heart beat thread");
    HeartBeatThread hb_thread;
    DS_LOG(INFO, "Start heart beat thread");
    hb_thread.Start();

    hb_thread.Wait();
    rpc_server.Wait();
    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
