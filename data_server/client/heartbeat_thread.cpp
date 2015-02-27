/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file heartbeat_thread.cpp
 * @author aishuyu(com@baidu.com)
 * @date 2015/02/25 19:54:51
 * @brief 
 *  
 **/


#include "heartbeat_thread.h"

#include "config/config_manager.h"

namespace dist_storage {

namespace data_server {

HeartBeatThread::HeartBeatThread() {
}

HeartBeatThread::~HeartBeatThread() {
}

void HeartBeatThread::Run() {
    int64_t hb_interval = DS_SYS_CONF.IniGetInt(
            "data_service:heartbeat_interval");

    if (hb_interval <= 0) {
        hb_interval = 60;
    }

    while (true) {
        ns_client_.SendHeartBeat();
        sleep(hb_interval);
    }
}

}  // end of namespace data_server

}  // end of namespace dist_storage





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
