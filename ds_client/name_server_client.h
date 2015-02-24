/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file name_server_client.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/22 22:00:23
 * @brief 
 *  
 **/




#ifndef  __NAME_SERVER_CLIENT_H_
#define  __NAME_SERVER_CLIENT_H_


#include <string>
#include <map>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "rpc/rpc_channel.h"
#include "proto/name_serv.pb.h"

namespace dist_storage {

namespace ds_client {

typedef std::vector<std::string> NODE_LIST;
typedef boost::shared_ptr<NODE_LIST> NODE_LIST_PTR;

class NameServerClient {
    public:
        NameServerClient();

        ~NameServerClient();

        // get info from name server
        bool GetBuketList(std::map<int64_t, NODE_LIST_PTR>& bucket_node_map);

    private:
        // get init paramters
        bool ClientInit();
        
    private:
         Channel* rpc_channel_ptr_;

         DataService::Stub* serveice_stub_ptr_;

};

}  // end of namespace ds_client

}  // end of namespace dist_storage

















#endif  //__NAME_SERVER_CLIENT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
