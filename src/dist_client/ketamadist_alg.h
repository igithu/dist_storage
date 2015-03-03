/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file ketamadist_alg.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/12 15:53:28
 * @brief 
 *  
 **/




#ifndef  __KETAMADIST_ALG_H_
#define  __KETAMADIST_ALG_H_



#include "distribute_alg.h"


namespace dist_storage {

namespace dist_client {

class KetamaDistAlg : public DistributeAlg {
    public:
        // use ketema hash to get hash_key
        virtual bool GetNodeHashKey(const BUCKET_NODE_MAP& bi_hash_map, 
                                    const char* key, 
                                    uint64_t& hash_key); 
};

}  // end of namespace dist_client

}  // end of namespace dist_storage
















#endif  //__KETAMADIST_ALG_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
