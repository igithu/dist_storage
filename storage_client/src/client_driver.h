/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file client_driver.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/26 14:27:13
 * @brief 
 *  
 **/




#ifndef  __CLIENT_DRIVER_H_
#define  __CLIENT_DRIVER_H_

#include "client_thread.h" 

#include <string>

#include <boost/unordered_map.hpp>

#include "disallow_copy_and_assign.h"
#include "server_client/name_server_client.h"
#include "server_client/data_server_client.h"


namespace dist_storage {

namespace storage_client {

typedef boost::shared_ptr<DataServerClient> DSC_PTR;
typedef boost::unordered_map<string, DSC_PTR> DSCLINT_MAP;
typedef boost::shared_ptr<DSCLINT_MAP> DSCLINT_MAP_PTR;

class DistStorageClientDriver;
typedef std::auto_ptr<DistStorageClientDriver> DSCDSmartPtr;

class DistStorageClientDriver {
    public:
        ~DistStorageClientDriver();

        static DistStorageClientDriver& GetInstance();

        bool Start();

        bool Wait();

        bool Stop();

        // set, get and delete will call ketamahash
        bool Set(const char* key, const char* value);

        bool Get(const char* key, std::string& value);

        bool Delete(const char* key);

        // update current map info
        bool UpdateBucketNodeMap(name_server::BUCKET_NODE_MAP& bn_map_ptr);

        bool BuildDSClientMap();

    private:
        // ctor
        DistStorageClientDriver();

        bool GetNodeHost(std::string& node_host);

        DISALLOW_COPY_AND_ASSIGN(DistStorageClientDriver);

    private:
        // threads
        DistStorageClientThread* client_thread_ptr_;

        // map data
        name_server::BUCKET_NODE_MAP_PTR bn_map_ptr_;
        DSCLINT_MAP_PTR ds_client_map_ptr_;

        // rw lock
        PUBLIC_UTIL::RWLock bn_map_rwlock_;
        PUBLIC_UTIL::RWLock ds_client_rwlock_;

        // for name_server rpc call
        NameService ns_client_;

        name_server::DistributeAlg* distribute_alg_ptr_;

        // for instance
        static DSCDSmartPtr client_driver_ptr_;
        static PUBLIC_UTIL::Mutex instance_mutex_;

        
};


}  // end of namespace storage_client

}  // end of namespace dist_storage





#endif  //__CLIENT_DRIVER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
