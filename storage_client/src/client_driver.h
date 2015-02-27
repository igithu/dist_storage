/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file client_driver.h
 * @author aishuyu(com@baidu.com)
 * @date 2015/02/26 14:27:13
 * @brief 
 *  
 **/




#ifndef  __CLIENT_DRIVER_H_
#define  __CLIENT_DRIVER_H_

#include "client_thread.h" 

#include <string>

#include "disallow_copy_and_assign.h"
#include "server_client/name_server_client.h"
#include "server_client/data_server_client.h"


namespace dist_storage {

namespace storage_client {

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

    private:
        DistStorageClientDriver();

        bool GetNodeHost();

        DISALLOW_COPY_AND_ASSIGN(DistStorageClientDriver);

    private:
        DistStorageClientThread* client_thread_ptr_;

        name_server::BUCKET_NODE_MAP bn_map_ptr_;

        PUBLIC_UTIL::RWLock bn_map_rwlock_;

        DataServerClient ds_client_;

        // for instance
        static DSCDSmartPtr client_driver_ptr_;

        static PUBLIC_UTIL::Mutex instance_mutex_;

        
};


}  // end of namespace storage_client

}  // end of namespace dist_storage





#endif  //__CLIENT_DRIVER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
