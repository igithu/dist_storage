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

namespace storage_client {

// because the bn_map_ptr_ is write and read by different threads
typedef boost::shared_ptr<BN_MAP> BN_MAP_PTR; 

class DistributeAlg {
    public:
        virtual bool GetDistNode(const BUCKET_NODE_MAP& bi_hash_map,
                                 const std::string& key,
                                 std::string& host) = 0;
};

}  // end of namespace storage_client

}  // end of namespace dist_storage





#endif  //__DISTRIBUTE_ALG_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
