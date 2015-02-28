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
    service_stub_ptr_ = new DataService::Stub(rpc_channel_ptr_);

    return true;
}

bool DataServerClient::Put(const char* key, const char* value) {
    DSRequest ds_request;
    ds_request.set_ds_key(key);
    ds_request.set_ds_value(value);

    DSResponse ds_response;
    service_stub_ptr_->Put(NULL, &ds_request, &ds_response, NULL);
    if (DS_ERR == ds_response.code()) {
        DS_LOG(ERROR, "Put data failed!rpc server error");
        return false;
    }

    return true;
}

bool DataServerClient::Get(const char* key, string& value) {
    DSRequest ds_request;
    ds_request.set_ds_key(key);

    DSResponse ds_response;
    service_stub_ptr_->Get(NULL, &ds_request, &ds_response, NULL);
    if (DS_ERR == ds_response.code()) {
        DS_LOG(ERROR, "Get data failed!rpc server error");
        return false;
    }
    value = ds_response.ds_res();
    return true;
}

bool DataServerClient::Delete(const char* key) {
    DSRequest ds_request;
    ds_request.set_ds_key(key);

    DSResponse ds_response;
    service_stub_ptr_->Delete(NULL, &ds_request, &ds_response, NULL);
    if (DS_ERR == ds_response.code()) {
        DS_LOG(ERROR, "Delete data failed!rpc server error");
        return false;
    }
    return true;
}


}  // end of namespace storage_client

}  // end of namespace dist_storage 
















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
