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

#include "common/ds_log.h"

namespace dist_storage {

namespace dist_client {

using namespace PUBLIC_UTIL;

PUBLIC_UTIL::Mutex DistStorageClientDriver::instance_mutex_;
DSCDSmartPtr DistStorageClientDriver::client_driver_ptr_(NULL);

DistStorageClientDriver::DistStorageClientDriver() :
   client_thread_ptr_(NULL),
   distribute_alg_ptr_ (NULL),
   bn_map_ptr_(new BUCKET_NODE_MAP()),
   ds_client_map_ptr_(new DSCLINT_MAP()){
}

DistStorageClientDriver::~DistStorageClientDriver() {
    Stop();
    if (NULL != client_thread_ptr_) {
        delete client_thread_ptr_;
    }
    if (NULL != distribute_alg_ptr_) {
        delete distribute_alg_ptr_;
    }
    bn_map_ptr_.reset();
    ds_client_map_ptr_.reset();
}


DistStorageClientDriver& DistStorageClientDriver::GetInstance() {
    if (NULL == client_driver_ptr_.get()) {
        MutexLockGuard lock(instance_mutex_);
        client_driver_ptr_.reset(new DistStorageClientDriver());
        return *client_driver_ptr_;
    }
    return *client_driver_ptr_;
}

bool DistStorageClientDriver::Start() {
    // first get info from name server
    DS_LOG(INFO, "Start first update bucket node info!");
    if (!UpdateBucketNodeMap()) {
        DS_LOG(ERROR, "First update bucket map error! Start failed");
        return false;
    }
    DS_LOG(INFO, "Start build ds client map!");
    if (!BuildDSClientMap()) {
        DS_LOG(ERROR, "First build ds client map error! Start failed");
        return false;
    }

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

bool DistStorageClientDriver::GetNodeClient(const char* key, DSC_PTR& dsc_ptr) {

    // 1. get alg obj
    // 2. use the alg get hash_key
    // 3. use hash_key get node list
    // 4. find first alive node host in the node list
    //    if not find, failed return false

    // Note: if GetNodeHost run slowly, should add cache that map the key to host here!!

    if (NULL == distribute_alg_ptr_) {
        DS_LOG(ERROR, "The distribute_alg_ptr_ is NULL! the driver may be unstarted!");
        return false;
    }

    uint64_t hash_key;
    if (!distribute_alg_ptr_->GetNodeHashKey(*bn_map_ptr_, key, hash_key)) {
        DS_LOG(ERROR, "Call GetDistNode failed!");
        return false;
    }

    // get alive node map info
    DSCLINT_MAP_PTR ds_client_map_ptr; 
    {
        ReadLockGuard rguard(ds_client_rwlock_);
        ds_client_map_ptr = ds_client_map_ptr_;
    }
    if (NULL == ds_client_map_ptr || ds_client_map_ptr->empty()) {
        DS_LOG(ERROR, "Alive node map is empty!please check!");
        return false;
    }

    const NODE_LIST& node_list = *((*bn_map_ptr_)[hash_key]);
    dsc_ptr.reset();
    for (NODE_LIST::const_iterator nl_iter = node_list.begin();
         nl_iter != node_list.end();
         ++nl_iter) {
        const string& cur_host = *nl_iter; 
        DSCLINT_MAP::iterator dsc_iter = ds_client_map_ptr->find(cur_host);
        if (ds_client_map_ptr->find(cur_host) != ds_client_map_ptr->end()) {
            dsc_ptr = dsc_iter->second;
            break;
        } 
    }

    if (NULL == dsc_ptr) {
        DS_LOG(ERROR, "Cann't find alive host!");
        return false;
    }

    return true;
}

bool DistStorageClientDriver::Set(const char* key, const char* value) {
    DSC_PTR dsc_ptr;
    if (!GetNodeClient(key, dsc_ptr)) {
        DS_LOG(ERROR, "Set the key %s failed!", key);
        return false;
    }
    if (!dsc_ptr->Put(key, value)) {
        DS_LOG(ERROR, "Set the key %s failed! whern call data server client.", key);
        return false;
    }
    return true;
}

bool DistStorageClientDriver::Get(const char* key, string& value) {
    DSC_PTR dsc_ptr;
    if (!GetNodeClient(key, dsc_ptr)) {
        DS_LOG(ERROR, "Get the value of key %s failed!", key);
        return false;
    }
    if (!dsc_ptr->Get(key, value)) {
        DS_LOG(ERROR, "Get value of the key %s failed! whern call data server client.", key);
        return false;
    }
    return true;
}

bool DistStorageClientDriver::Delete(const char* key) {
    DSC_PTR dsc_ptr;
    if (!GetNodeClient(key, dsc_ptr)) {
        DS_LOG(ERROR, "Delete the key %s failed!", key);
        return false;
    }
    if (!dsc_ptr->Delete(key)) {
        DS_LOG(ERROR, "Delete the key %s failed! whern call data server client.", key);
        return false;
    }
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

bool DistStorageClientDriver::UpdateBucketNodeMap() {
    BN_MAP_PTR bn_map_ptr(new BUCKET_NODE_MAP());
    DS_LOG(INFO, "Rpc call GetBucketInfo!");
    ns_client_.GetBucketInfo(*bn_map_ptr);
    if (NULL == bn_map_ptr) {
        DS_LOG(ERROR, "bn_map_ptr is NULL! update bn_map failed!");
        return false;
    }
    WriteLockGuard wguard(bn_map_rwlock_);
    // refresh the ptr
    bn_map_ptr_.swap(bn_map_ptr);
    DS_LOG(INFO, "New bn_map_ptr_ size is %d", bn_map_ptr_->size());

    return true;
}

bool DistStorageClientDriver::BuildDSClientMap() {

    string ds_port;
    vector<string> node_list;

    if (!ns_client_.GetNodeInfo(node_list, ds_port)) {
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


}  // end of namespace dist_client

}  // end of namespace dist_storage







/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
