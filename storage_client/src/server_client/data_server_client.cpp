/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file data_server_client.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/22 15:13:31
 * @brief 
 *  
 **/

#include "data_server_client.h"

#include "log/ds_log.h"
#include "config/config_manager.h"

namespace dist_storage { 

namespace storage_client {

DataServerClient::DataServerClient(const char* ds_host, const char* ds_port) :
   rpc_channel_ptr_(NULL), service_stub_ptr_(NULL) {
       ClientInit(ds_host, ds_port);
}

DataServerClient::~DataServerClient() {
    if (NULL != service_stub_ptr_) {
        delete service_stub_ptr_;
    }
    if (NULL != rpc_channel_ptr_) {
        delete rpc_channel_ptr_;
    }
}

bool DataServerClient::ClientInit(const char* ds_host, const char* ds_port) {

    rpc_channel_ptr_ = new Channel(ds_host, ds_port);
    service_stub_ptr_ = new NameService::Stub(rpc_channel_ptr_);

    return true;
}

bool DataServerClient::Put(const char* key, const char* value) {
    return true;
}

bool DataServerClient::Get(const char* key, string& value) {
    return true;
}

bool DataServerClient::Delete(const char* key) {
    return true;
}


}  // end of namespace storage_client

}  // end of namespace dist_storage 





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
