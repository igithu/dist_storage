/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file distribution_manager.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/03 18:50:52
 * @brief 
 *  
 **/




#ifndef  __DISTRIBUTION_MANAGER_H_
#define  __DISTRIBUTION_MANAGER_H_


#include <string>
#include <vector>

#include "pthread_rwlock.h"

namespace dist_storage {

namespace name_server {

typedef std::vector<string> BN_LIST;
typedef boost::shared_ptr<BN_LIST> BN_LIST_PTR; 

// virtual node in fact
typedef struct BucketInfo_t {
    BucketInfo() : bnode_list_ptr(new BN_LIST()) {
        bnode_list_ptr
    }

    ~BucketInfo() {
        bnode_list_ptr.reset();
    }

    int32_t  number;
    // node list
    BN_LIST_PTR bnode_list_ptr;

    PUBLIC_UTIL::RWLock rwlock;
} BucketInfo;

typedef boost::unordered_map<int32_t, BucketInfo> BI_HASH_MAP;

class DistributionManager {
    public:
        // ctor
        DistributionManager();

        // dtor
        ~DistributionManager();

        bool InitDistTable();

        bool BuildDistTable();

    private:
        // control the bucket num: pow(2, bucket_pow_)
        int32_t bucket_pow_;

        // bucket <---> node mapping
        BI_HASH_MAP bucket_node_map_;

};


} // end of namespace name_server

}  // end of namespace dist_storage













#endif  //__DISTRIBUTION_MANAGER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
