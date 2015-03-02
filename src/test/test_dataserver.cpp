/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_data_server.cpp
 * @author aishuyu(com@baidu.com)
 * @date 2015/03/02 13:46:17
 * @brief 
 *  
 **/



#include "config/config_manager.h"


//#include "proto/name_serv.pb.h"
#include "rpc/rpc_server.h"
#include "common/ds_log.h"

using namespace dist_storage;
//using namespace data_server;


int main() {

    DS_SYS_CONF.ConfigInit("../conf/data_serv.ini");

    DS_LOG(ERROR, "init the data server config failed!");

    RpcServer& rpc_server = RpcServer::GetInstance();

    return 0;
}















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
