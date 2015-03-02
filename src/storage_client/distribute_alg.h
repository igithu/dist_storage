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
#include "common/dist_hash.h"

namespace dist_storage {

namespace storage_client {

typedef std::vector<std::string> NODE_LIST;
typedef boost::shared_ptr<NODE_LIST> NODE_LIST_PTR;
typedef std::map<uint64_t, NODE_LIST_PTR> BUCKET_NODE_MAP;
typedef boost::shared_ptr<BUCKET_NODE_MAP> BN_MAP_PTR; 

class DistributeAlg {
    public:
        virtual bool GetNodeHashKey(const BUCKET_NODE_MAP& bi_hash_map,
                                    const char* key,
                                    uint64_t& hash_key) = 0;
};

}  // end of namespace storage_client

}  // end of namespace dist_storage





#endif  //__DISTRIBUTE_ALG_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
