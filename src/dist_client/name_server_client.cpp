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

#include "common/ds_log.h"
#include "config/config_manager.h"

namespace dist_storage { 

namespace dist_client {

using namespace google::protobuf;
using std::string;

NameServerClient::NameServerClient():
   rpc_channel_ptr_(NULL), service_stub_ptr_(NULL) {
}

NameServerClient::~NameServerClient() {
    if (NULL != service_stub_ptr_) {
        delete service_stub_ptr_;
    }
    if (NULL != rpc_channel_ptr_) {
        delete rpc_channel_ptr_;
    }
}

bool NameServerClient::ClientInit() {
    const char* ns_host = DS_SYS_CONF.IniGetString("name_server:host");
    const char* ns_port = DS_SYS_CONF.IniGetString("name_server:port");

    rpc_channel_ptr_ = new Channel(ns_host, ns_port);
    service_stub_ptr_ = new NameService::Stub(rpc_channel_ptr_);
    return true;
}

bool NameServerClient::GetBucketInfo(BUCKET_NODE_MAP& bucket_node_map) {

    CNSRequest cns_request;
    CNSResponse cns_response;

    // rpc call
    service_stub_ptr_->GetBucketInfo(NULL, &cns_request, &cns_response, NULL);
    if (NS_ERR == cns_response.ret_code()) {
        DS_LOG(ERROR, "Get bucket list failed!");
        return false;
    }

    typedef RepeatedPtrField<Bucket> BUCKET_LIST_TYPE;
    typedef RepeatedPtrField<string> NODE_LIST_TYPE;
    const BUCKET_LIST_TYPE&  bucket_list = cns_response.bucket_list();
    // read bucket -> node info from cns_response
    for (BUCKET_LIST_TYPE::const_iterator bl_iter = bucket_list.begin();
         bl_iter !=  bucket_list.end();
         ++bl_iter) {

        uint64_t bucket_num = bl_iter->number();
        NODE_LIST_PTR nl_ptr(new NODE_LIST());
        const NODE_LIST_TYPE& node_list = bl_iter->node_list();
        for (NODE_LIST_TYPE::const_iterator nl_iter = node_list.begin();
             nl_iter != node_list.end();
             ++nl_iter) {
            nl_ptr->push_back(*nl_iter);
        }
        if (bucket_node_map.find(bucket_num) != bucket_node_map.end()) {
            bucket_node_map[bucket_num] = nl_ptr;
        } else {
            bucket_node_map.insert(std::make_pair(bucket_num, nl_ptr));
        } 
    }

    if (bucket_node_map.size() == 0) {
        DS_LOG(WARNING, "Get the bucket info id empty!");
        return false;
    }

    return true;
}

bool NameServerClient::GetNodeInfo(vector<string>& node_list, string& ds_port) {

    CNSRequest cns_request;
    CNSResponse cns_response;

    service_stub_ptr_->GetNodeInfo(NULL, &cns_request, &cns_response, NULL);
    if (NS_ERR == cns_response.ret_code()) {
        DS_LOG(ERROR, "Get node info failed!");
        return false;
    }

    typedef RepeatedPtrField<string> NODE_LIST_TYPE;
    const NODE_LIST_TYPE& alive_node_list = cns_response.node_list();
    for (NODE_LIST_TYPE::const_iterator nl_iter = alive_node_list.begin();
         nl_iter != alive_node_list.end();
         ++nl_iter) {
        node_list.push_back(*nl_iter);
    }
    ds_port = cns_response.ds_port();

    if (node_list.size() == 0) {
        DS_LOG(WARNING, "Get the node info id empty!");
        return false;
    }
    
    return true;
} 

}  // end of namespace dist_client

}  // end of namespace dist_storage 





/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
