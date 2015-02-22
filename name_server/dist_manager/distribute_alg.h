/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file distribute_alg.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/12 14:56:05
 * @brief 
 *  
 **/




#ifndef  __DISTRIBUTE_ALG_H_
#define  __DISTRIBUTE_ALG_H_

#include <string>
#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>

#include "pthread_rwlock.h"
#include "util/dist_hash.h"

namespace dist_storage {

namespace name_server {

typedef std::vector<std::string> BN_LIST;
typedef boost::shared_ptr<BN_LIST> BN_LIST_PTR; 

// virtual node in fact
typedef struct BucketInfo_t {
    BucketInfo_t() : bnode_list_ptr(new BN_LIST()) {
    }

    ~BucketInfo_t() {
        bnode_list_ptr.reset();
    }

    Long  number;
    // node list
    BN_LIST_PTR bnode_list_ptr;

    PUBLIC_UTIL::RWLock rwlock;
} BucketInfo;

typedef boost::shared_ptr<BucketInfo> BI_PTR;
typedef std::map<Long, BI_PTR> BUCKET_NODE_MAP;

class DistributeAlg {
    public:
        virtual bool BuildDistTable(BUCKET_NODE_MAP& bi_hash_map) = 0;

        virtual bool GetDistNode(const BUCKET_NODE_MAP& bi_hash_map,
                                 const std::string& key,
                                 std::string& host) = 0;
};

}  // end of namespace name_server

}  // end of namespace dist_storage





#endif  //__DISTRIBUTE_ALG_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
