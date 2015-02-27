/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file client_driver.cpp
 * @author aishuyu(com@baidu.com)
 * @date 2015/02/26 14:27:19
 * @brief 
 *  
 **/

#include "client_driver.h"

#include "log/ds_log.h"

namespace dist_storage {

namespace storage_client {

using namespace name_server;

DistStorageClientDriver::DistStorageClientDriver() :
   client_thread_ptr_(NULL),
   bn_map_ptr_(new BN_MAP()) {
}

DistStorageClientDriver::~DistStorageClientDriver() {
    Stop();
    if (NULL != client_thread_ptr_) {
        delete client_thread_ptr_
    }
    bn_map_ptr_.reset();
}

DistStorageClientDriver& DistStorageClientDriver::GetInstance() {
    if (NULL == client_driver_ptr_) {
        MutexLockGuard lock(instance_mutex_);
        client_thread_ptr_.reset(new DistStorageClientDriver());
        return *client_thread_ptr_;
    }
    return *client_thread_ptr_;
}

bool DistStorageClientDriver::Start() {

    client_thread_ptr_ = new DistStorageClientThread();

    client_thread_ptr_->Start();

    return true;
}

bool DistStorageClientDriver::Wait() {
    if (NULL != client_thread_ptr_) {
        client_thread_ptr_->Wait();
    } else {
        return false;
    }
    return true;
}

bool DistStorageClientDriver::GetNodeHost(const char* key) {

    return true;
}

bool DistStorageClientDriver::Set(const char* key, const char* value) {
    return true;
}

bool DistStorageClientDriver::Get(const char* key, std::string& value) {
    return true;
}

bool DistStorageClientDriver::Delete(const char* key) {
    return true;
}

bool DistStorageClientDriver::Stop() {
    if (NULL != client_thread_ptr_) {
        client_thread_ptr_->Stop();
    } else {
        return false;
    }
    return true;
}

bool DistStorageClientDriver::UpdateBucketNodeMap(BUCKET_NODE_MAP& bn_map_ptr) {
    if (NULL == bn_map_ptr) {
        DS_LOG(ERROR, "bn_map_ptr is NULL! update bn_map failed!");
        return false;
    }
    WriteLockGuard wguard(bn_map_rwlock_);
    // refresh the ptr
    bn_map_ptr_.swap(bn_map_ptr);

    return true;
}


}  // end of namespace storage_client

}  // end of namespace dist_storage











/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
