/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file engine_service.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/10 15:51:48
 * @brief 
 *  
 **/

#include "data_service.h"

#include <stdio.h>
#include <string>

#include "../storage/level_db.h"
#include "../../include/inter_include.h"

namespace dist_storage {

namespace data_server {

using std::string;

DataServiceImpl::DataServiceImpl():
   common_ds_ptr_(NULL) {
       EngineServiceInit();
}

DataServiceImpl::~DataServiceImpl() {
    if (NULL != common_ds_ptr_) {
        delete common_ds_ptr_;
    }
}

bool DataServiceImpl::EngineServiceInit() {
    const char* db_path = DS_SYS_CONF.IniGetString(
            "db_storage:storage_path");
    common_ds_ptr_ = new LeveDB(db_path);
    return true;
}

void DataServiceImpl::Put(RpcController* controller,
                            const DSRequest* request,
                            DSResponse* response,
                            Closure* done) {
    const string& key = request->ds_key();
    const string& value = request->ds_value();
    if ("" == key || "" == value) {
        return;
    }
    if (NULL == common_ds_ptr_ || !common_ds_ptr_->Put(key.c_str(), value.c_str())) {
        DS_LOG(ERROR, "EngineService put the key : %s, value: %s failed!",
               key.c_str(), value.c_str());
        response->set_code(ERR);
    }
    //response->set_db_res("null");
}

void DataServiceImpl::Get(RpcController* controller,
                            const DSRequest* request,
                            DSResponse* response,
                            Closure* done) {
    const string& key = request->ds_key();
    if ("" == key) {
        return;
    }
    string value;
    if (!common_ds_ptr_->Get(key.c_str(), value)) {
        DS_LOG(ERROR, "EngineService get the key : %s failed!", key.c_str());
        response->set_code(ERR);
    }

    if ("" == value) {
        response->set_code(NOFOUND);
        return;
    }
    response->set_ds_res(value);
}

void DataServiceImpl::Delete(RpcController* controller,
                               const DSRequest* request,
                               DSResponse* response,
                               Closure* done) {
    const string& key = request->ds_key();
    if ("" == key) {
        return;
    }
    if (!common_ds_ptr_->Delete(key.c_str())) {
        DS_LOG(ERROR, "EngineService del the key : %s failed!", key.c_str());
        response->set_code(ERR);
    }
}

}  // end of namespace data_server

}  // end of namespace dist_storage





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
