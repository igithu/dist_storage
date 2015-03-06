/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_nm.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/03/05 14:09:45
 * @brief 
 *  
 **/

#include <google/protobuf/repeated_field.h>

#include "config/config_manager.h"
#include "name_server/node_manager.h"
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

    GlobalNM.Start();
    ::google::protobuf::RepeatedPtrField<std::string> node_list;

    GlobalNM.GetAliveNodes(node_list);

    printf("Test node_list size is %d , the no. is %s.\n", node_list.size(), node_list.Get(0).c_str());


    GlobalNM.Stop();


    return 0;
}




















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
