/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file client_driver.cpp
 * @author aishuyu(asy5178@163.com)
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
   bn_map_ptr_(new BN_MAP()),
   ds_client_map_ptr_(new DSCLINT_MAP()){
}

DistStorageClientDriver::~DistStorageClientDriver() {
    Stop();
    if (NULL != client_thread_ptr_) {
        delete client_thread_ptr_
    }
    bn_map_ptr_.reset();
    ds_client_map_ptr_.reset();
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

    // for now only ketetma hash alg 
    distribute_alg_ptr_ = new KetamaDistAlg();

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

bool DistStorageClientDriver::GetNodeHost(const char* key, string& node_host) {

    // 1. get alg obj
    // 2. use the alg get host
    // 3. check the host is alive
    // 4. if alive return the host, 
    //    if not alive, find new host from bucket_node_map
    // 5. if find alive node return the host 
    //    if not find, failed return false

    return true;
}

bool DistStorageClientDriver::Set(const char* key, const char* value) {
    return true;
}

bool DistStorageClientDriver::Get(const char* key, string& value) {
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

bool DistStorageClientDriver::BuildDSClientMap() {

    string ds_port;
    vector<string> node_list;

    if (!ns_client_.GetNodeInfo(node_host, ds_port)) {
        DS_LOG(ERROR, "Get node info failed!");
        return false;
    }
    
    // build new data server map
    DSCLINT_MAP_PTR new_client_map_ptr(new DSCLINT_MAP());
    for (vector<string>::iterator nl_iter = node_list.begin();
         nl_iter != node_list.end();
         ++nl_iter) {
        const string& cur_host = *nl_iter;
        DSC_PTR new_dsc_ptr(
                new DataServerClient(cur_host.c_str(), ds_port.c_str()));
        new_client_map_ptr->insert(std::make_pair(cur_host, new_dsc_ptr));
    }

    // update ds_client_map_ptr_
    {
        WriteLockGuard wguard(ds_client_rwlock_);
        ds_client_map_ptr_.swap(new_client_map_ptr);
    }  

    return true;
}


}  // end of namespace storage_client

}  // end of namespace dist_storage







/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
