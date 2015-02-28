/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file data_server_client.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/21 22:19:08
 * @brief 
 *  
 **/




#ifndef  __DATA_SERVER_CLIENT_H_
#define  __DATA_SERVER_CLIENT_H_

#include <string>

#include "rpc/rpc_channel.h"
#include "proto/data_serv.pb.h"

namespace dist_storage {

namespace storage_client {

class DataServerClient {
    public:
        DataServerClient();

        ~DataServerClient();

        // api to exchange data
        bool Put(const char* key, const char* value);

        bool Get(const char* key, std::string& value);

        bool Delete(const char* key);

    private:
        // get init paramters
        bool ClientInit();
        
    private:
         Channel* rpc_channel_ptr_;

         DataService::Stub* service_stub_ptr_;

};

}  // end of namespace storage_client

}  // end of namespace dist_storage















#endif  //__DATA_SERVER_CLIENT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
