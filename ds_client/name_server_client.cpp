/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file name_server_client.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/22 22:09:13
 * @brief 
 *  
 **/


#include "name_server_client.h"

namespace dist_storage { 

namespace ds_client {

using std::map;

NameServerClient::NameServerClient() {
}

NameServerClient::~NameServerClient() {
}

bool NameServerClient::ClientInit() {
    return true;
}

bool NameServerClient::GetBuketList(map<int64_t, NODE_LIST_PTR>& bucket_node_map) {
    return true;
}

}  // end of namespace ds_client

}  // end of namespace dist_storage 























/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
