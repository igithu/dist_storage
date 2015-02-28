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

namespace name_server {

class KetamaDistAlg : public DistributeAlg {
    public:
        // use ketema hash to build virtual nodes number (bucket number)
        virtual bool BuildDistTable(BUCKET_NODE_MAP& bi_map); 

        // use ketema hash to get real node host 
        virtual bool GetDistNode(const BUCKET_NODE_MAP& bi_map, 
                                 const std::string& key, 
                                 std::string& host); 
};

}  // end of namespace name_server

}  // end of namespace dist_storage
















#endif  //__KETAMADIST_ALG_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
