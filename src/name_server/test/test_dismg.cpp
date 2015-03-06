/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_dismg.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/03/05 10:18:42
 * @brief 
 *  
 **/

#include <google/protobuf/message.h>

#include "rpc/rpc_msg.pb.h"
#include "config/config_manager.h"
#include "name_server/distribution_manager.h"
#include "common/ds_log.h"
#include "common/tools.h"
#include "proto/name_serv.pb.h"

using namespace dist_storage;
using namespace name_server;
using namespace google::protobuf;

int main(int argc, char* argv[]) {
    if (!DS_SYS_CONF.ConfigInit("../../../share/conf/name_server.ini")) {
        DS_LOG(ERROR, "test_dismg init the data server config failed!");
        return 0;
    }

    const char* log_dir = DS_SYS_CONF.IniGetString("log:path");
    if (!CreateDir(log_dir)) {
        DS_LOG(ERROR, "test_dismg create log dir: %s faied!", log_dir);
        return 0;
    }
    if (false == DSLogInit(
                argc, argv, DS_SYS_CONF.IniGetString("log:level"), log_dir)) {
        return 0;
    }

    CNSResponse cns_resp;
     GlobalDM;
     sleep(5);
    GlobalDM.GetBucketInfo(*cns_resp.mutable_bucket_list());

    std::string cns_info;
    
    Message* send_msg = &cns_resp;
    send_msg->SerializeToString(&cns_info);

    RpcMessage send_rpc_msg;
    send_rpc_msg.set_head_code(200);
    send_rpc_msg.set_body_msg(cns_info);

    std::string send_str;
    send_rpc_msg.SerializeToString(&send_str);

    std::string& recv_str = send_str;
    RpcMessage recv_rpc_msg;
    if (!recv_rpc_msg.ParseFromString(recv_str)) {
        printf("recv_rpc_msg parse error\n");
    } else {
        printf("Text : %s\n", recv_rpc_msg.DebugString().c_str());
    }


    //CNSResponse new_resp;
    //new_resp.ParseFromString(cns_info);

    //printf("Text : %s\n", new_resp.DebugString().c_str());
    //printf("cns_info size id %d\n", cns_info.size());


}






















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
