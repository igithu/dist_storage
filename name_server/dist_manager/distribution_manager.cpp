/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file distribution_manager.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/04 10:36:34
 * @brief 
 *  
 **/

#include "distribution_manager.h"

#include "ketamadist_alg.h" 

namespace dist_storage {

namespace name_server {

DistributionManager::DistributionManager() :
   distribute_alg_ptr_(NULL) {
}

DistributionManager::~DistributionManager() {
    if (NULL != distribute_alg_ptr_) {
        delete distribute_alg_ptr_;
    }
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

}  // end of namespace name_server

}  // end of namespace dist_storage








/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
