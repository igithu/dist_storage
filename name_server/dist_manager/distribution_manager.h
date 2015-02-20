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
#include "disallow_copy_and_assign.h"
#include "../../proto/name_serv.pb.h"

namespace dist_storage {

namespace name_server {

class DistributionManager;
typedef std::auto_ptr<DistributionManager> DMSmartPtr;

#define GlobalDM DistributionManager::GetInstance()

class DistributionManager {
    public:
        friend class NameServiceImpl;

    public:
        static DistributionManager& GetInstance();

        // dtor
        ~DistributionManager();

        bool InitDistTable();

        bool BuildDistTable();

        bool GetBucketList(::google::protobuf::RepeatedPtrField<Bucket>& bucket_list);


    private:
        // ctor
        DistributionManager();

        DISALLOW_COPY_AND_ASSIGN(DistributionManager);

    private:
        // bucket <---> node mapping
        BUCKET_NODE_MAP bucket_node_map_;

        // hash alg
        DistributeAlg* distribute_alg_ptr_;

        // for static
        static DMSmartPtr dist_manager_ptr_;

        static PUBLIC_UTIL::Mutex instance_mutex_;



};


} // end of namespace name_server

}  // end of namespace dist_storage













#endif  //__DISTRIBUTION_MANAGER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
