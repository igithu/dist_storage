/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file name_service.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/01/16 16:49:33
 * @brief 
 *  
 **/

#include "name_service.h"

#include "node_manager.h"
#include "distribution_manager.h"
#include "rpc/rpc_server.h"
#include "common/ds_log.h"
#include "config/config_manager.h"

namespace dist_storage {

namespace name_server {


NameServiceImpl::NameServiceImpl() {

}

NameServiceImpl::~NameServiceImpl() {
}

void NameServiceImpl::HeartBeat(RpcController* controller,
                                const HBRequest* hb_request,
                                HBResponse* hb_reponse,
                                Closure* done) {

    NI_PTR hb_ni_ptr(new NodeInfo());

    hb_ni_ptr->updated_time = hb_request->updated_time();
    hb_ni_ptr->disk_space = hb_request->disk_space();
    hb_ni_ptr->visit_flow = hb_request->visit_flow();

    if ((NodeAction)UnReg == hb_request->action()) {
        hb_ni_ptr->updated_time = -1;
    }

    GlobalNM.UpdateNodeInfo(hb_request->host(), hb_ni_ptr);
    //GlobalNM.UpdateNodeList();
}

void NameServiceImpl::GetBucketInfo(RpcController* controller,
                                    const CNSRequest* request,
                                    CNSResponse* response,
                                    Closure* done) {
    GlobalDM.GetBucketInfo(*response->mutable_bucket_list());
}

void NameServiceImpl::GetNodeInfo(RpcController* controller,
                                  const CNSRequest* request,
                                  CNSResponse* response,
                                  Closure* done) {
    GlobalNM.GetAliveNodes(*response->mutable_node_list());
    const char* ds_port = DS_SYS_CONF.IniGetString("data_service:port");
    response->set_ds_port(ds_port);
}

void NameServiceThread::Run() {
    RpcServer& rpc_server = RpcServer::GetInstance();
    NameServiceImpl name_service;
    rpc_server.RegisteService(&name_service);

    int32_t thread_num = DS_SYS_CONF.IniGetInt("name_service:thread_num");
    const char* port = DS_SYS_CONF.IniGetString("name_service:port");
    const char* addr = DS_SYS_CONF.IniGetLocalIPAddr();

    rpc_server.Start(thread_num, addr, port);
    rpc_server.Wait();
}

}  // end of namespace name_server

}  // end of namespace dist_storage








/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
