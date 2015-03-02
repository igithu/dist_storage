/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file ketamadist_alg.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/12 16:01:16
 * @brief 
 *  
 **/


#include "ketamadist_alg.h"

#include "common/tools.h"
#include "common/crytocpp.h"
#include "common/dist_hash.h"

namespace dist_storage {    

namespace storage_client {

using std::vector;
using std::string;


bool KetamaDistAlg::GetNodeHashKey(const BUCKET_NODE_MAP& bi_hash_map,
                                   const char* key, 
                                   uint64_t& hash_key) {
    if (bi_hash_map.size() == 0) {
        return false;
    }
    unsigned char md5_str[strlen(key)];
    sprintf((char*)md5_str, "%s", key);

    unsigned char digest[16];
    MD5(md5_str, digest);
    Long m = KetamaHash(digest, 0);

    BUCKET_NODE_MAP::const_iterator bi_itr = bi_hash_map.find(m);
    if (bi_itr != bi_hash_map.end()) {
        const NODE_LIST& bi_list = *(bi_itr->second);
        if (bi_list.size() == 0) {
            return false;
        }
        hash_key = m;
    } else {
        do {
            bi_itr = bi_hash_map.lower_bound(m);
            if (bi_itr != bi_hash_map.end()) {
                if (!bi_itr->second || bi_itr->second->size() == 0) {
                    return false;
                }
                hash_key = bi_itr->first;
                break;
            }
            m = 0;
        } while(true);
    }
    return true;
}

}  // end of namespace storage_client

}  // end of namespace dist_storage











/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
