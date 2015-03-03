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

#include "name_server_client.h"
#include "data_server_client.h"
#include "pthread_mutex.h"
#include "pthread_rwlock.h"
#include "disallow_copy_and_assign.h"


namespace dist_storage {

namespace dist_client {

#define GlobalDSClient DistStorageClientDriver::GetInstance()

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
        bool UpdateBucketNodeMap();

        bool BuildDSClientMap();

    private:
        // ctor
        DistStorageClientDriver();

        bool GetNodeClient(const char* key, DSC_PTR& dsc_ptr);

        DISALLOW_COPY_AND_ASSIGN(DistStorageClientDriver);

    private:
        // threads
        DistStorageClientThread* client_thread_ptr_;

        // dist hash alg
        DistributeAlg* distribute_alg_ptr_;

        // map data
        BN_MAP_PTR bn_map_ptr_;
        DSCLINT_MAP_PTR ds_client_map_ptr_;

        // rw lock
        PUBLIC_UTIL::RWLock bn_map_rwlock_;
        PUBLIC_UTIL::RWLock ds_client_rwlock_;

        // for name_server rpc call
        NameServerClient ns_client_;

        // for instance
        static DSCDSmartPtr client_driver_ptr_;
        static PUBLIC_UTIL::Mutex instance_mutex_;

        
};


}  // end of namespace dist_client

}  // end of namespace dist_storage





#endif  //__CLIENT_DRIVER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
