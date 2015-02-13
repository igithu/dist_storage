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

#include "distribute_alg.h"

namespace dist_storage {

namespace name_server {

class DistributionManager {
    public:
        // ctor
        DistributionManager();

        // dtor
        ~DistributionManager();

        bool InitDistTable();

        bool BuildDistTable();
        
    private:
        // bucket <---> node mapping
        BI_HASH_MAP bucket_node_map_;

        // hash alg
        DistributeAlg* distribute_alg_ptr_;

};


} // end of namespace name_server

}  // end of namespace dist_storage













#endif  //__DISTRIBUTION_MANAGER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
