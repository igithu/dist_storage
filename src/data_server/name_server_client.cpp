/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file name_server_client.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/25 10:50:04
 * @brief 
 *  
 **/


#include "name_server_client.h"

#include <time.h>
#include <sys/statfs.h>

#include "common/ds_log.h"
#include "config/config_manager.h"

namespace dist_storage {

namespace data_server {

using namespace google::protobuf;

NameServerClient::NameServerClient():
   rpc_channel_ptr_(NULL), serveice_stub_ptr_(NULL) {
       ClientInit();
}

NameServerClient::~NameServerClient() {
    if (NULL != serveice_stub_ptr_) {
        delete serveice_stub_ptr_;
    }

    if (NULL != rpc_channel_ptr_) {
        delete rpc_channel_ptr_;
    }
}

bool NameServerClient::ClientInit() {
    const char* ns_host = DS_SYS_CONF.IniGetString("name_service:host");
    const char* ns_port = DS_SYS_CONF.IniGetString("name_service:port");

    DS_LOG(INFO, "Init client set, the host is %s, the port is %s.", ns_host, ns_port);


    rpc_channel_ptr_ = new Channel(ns_host, ns_port);
    serveice_stub_ptr_ = new NameService::Stub(rpc_channel_ptr_);

    return true;
}

bool NameServerClient::SendHeartBeat() {

    if (NULL == serveice_stub_ptr_) {
        DS_LOG(ERROR, "The serveice_stub_ptr_ is NULL!");
        return false;
    }
    const char* st_path = DS_SYS_CONF.IniGetString("data_service:storage_path");
    struct statfs disk_info;
    if (statfs(st_path, &disk_info) == -1) {
        DS_LOG(ERROR, "Get statfs info failed!");
        return false;
    }

    int64_t disk_space = disk_info.f_blocks * disk_info.f_bsize;
    // in KB
    disk_space >>= 10;

    HBRequest hb_request;

    const char* ip_addr = DS_SYS_CONF.IniGetLocalIPAddr();
    hb_request.set_host(ip_addr);
    hb_request.set_action(Beat);
    hb_request.set_updated_time(time(NULL));
    hb_request.set_disk_space(disk_space);

    HBResponse hb_reponse;

    serveice_stub_ptr_->HeartBeat(
            NULL, &hb_request, &hb_reponse, NULL);

    return true;
}




}  // end of namespace data_server 

}  // end of namespace dist_storage




















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
