/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file distribution_manager.cpp
 * @author aishuyu(asy5178@163.com)
 *
 * @date 2015/02/04 10:36:34
 *
 * @brief 
 *  
 **/

#include "distribution_manager.h"
#include "pthread_rwlock.h"
#include "ketamadist_alg.h" 

namespace dist_storage {

namespace name_server {

using namespace PUBLIC_UTIL;

PUBLIC_UTIL::Mutex DistributionManager::instance_mutex_;
DMSmartPtr DistributionManager::dist_manager_ptr_(NULL);

DistributionManager::DistributionManager() :
   distribute_alg_ptr_(NULL) {
}

DistributionManager::~DistributionManager() {
    if (NULL != distribute_alg_ptr_) {
        delete distribute_alg_ptr_;
    }
}

DistributionManager& DistributionManager::GetInstance() {
    if (NULL == dist_manager_ptr_.get()) {
        MutexLockGuard lock(instance_mutex_);
        dist_manager_ptr_.reset(new DistributionManager());
        return *dist_manager_ptr_;
    }   
    return *dist_manager_ptr_;
}

bool DistributionManager::InitDistTable() {
    if (NULL == distribute_alg_ptr_) {
        return false;
    }
    // for now only ketama hash alg
    distribute_alg_ptr_ = new KetamaDistAlg();

    // start to build dist mapping table
    distribute_alg_ptr_->BuildDistTable(bucket_node_map_);
    return true;
}

bool DistributionManager::BuildDistTable() {
    return true;
}

bool DistributionManager::GetBucketList(
        ::google::protobuf::RepeatedPtrField<Bucket>& bucket_list) {
    for (BUCKET_NODE_MAP::iterator bn_iter = bucket_node_map_.end();
         bn_iter != bucket_node_map_.end();
         ++bn_iter) {
        Bucket* bucket_ptr = bucket_list.Add();
        bucket_ptr->set_number(bn_iter->first);
        BI_PTR bi_ptr = bn_iter->second;
        BN_LIST_PTR bnode_list_ptr;
        {
            ReadLockGuard rguard(bi_ptr->rwlock);
            bnode_list_ptr = bi_ptr->bnode_list_ptr;
        }

        if (NULL == bnode_list_ptr) {
            continue;
        }
        BN_LIST& bn_list = *bnode_list_ptr;
        for (BN_LIST::iterator bnl_iter = bn_list.begin();
             bnl_iter != bn_list.end();
             ++bnl_iter) {
            bucket_ptr->add_node_list(*bnl_iter);
        }

    }
    return true;
}

}  // end of namespace name_server

}  // end of namespace dist_storage








/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
