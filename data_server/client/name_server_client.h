/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file name_server_client.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/25 10:12:19
 * @brief 
 *  
 **/




#ifndef  __NAME_SERVER_CLIENT_H_
#define  __NAME_SERVER_CLIENT_H_


#include "proto/name_serv.pb.h"
#include "rpc/rpc_channel.h"

namespace dist_storage {

namespace data_server {

class NameServerClient {
    public:
        NameServerClient();

        ~NameServerClient();

        bool SendHeartBeat();

    private:
        bool ClientInit();

    private:
        Channel* rpc_channel_ptr_;
  
        NameService::Stub* serveice_stub_ptr_;

};

}  // end of namespace data_server

}  // end of namespace dist_storage













#endif  //__NAME_SERVER_CLIENT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
