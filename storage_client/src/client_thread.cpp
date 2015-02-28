/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file client_thread.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/26 14:28:36
 * @brief 
 *  
 **/


#include "client_thread.h"

#include "client_driver.h"
#include "config/config_manager.h"

namespace dist_storage {
    
namespace storage_client {

DistStorageClientThread::DistStorageClientThread() {
}

DistStorageClientThread::~DistStorageClientThread() {
}

void DistStorageClientThread::Run() {

    DistStorageClientDriver& dsc_driver = 
        DistStorageClientDriver::GetInstance();
    time_t bucket_interval = DS_SYS_CONF.IniGetInt("storage_client:bucket_update_interval");
    if (bucket_interval <= 0) {
        bucket_interval = 60 * 30;
    }
    time_t node_interval = DS_SYS_CONF.IniGetInt("storage_client:node_update_interval");
    if (node_interval <= 0) {
        node_interval = 60;
    }

    time_t bucket_latest_time = time(NULL);
    time_t node_latest_time = time(NULL);

    // Note: alarm and setitimer is only support single timer, so cannot directly use 
    //       alarm or setitimer, for now use the simple solution
    while (true) {
        sleep(5);
        time_t cur_time = time(NULL); 
        if (bucket_latest_time + bucket_interval < cur_time) {
            dsc_driver.UpdateBucketNodeMap();
        }
        if (node_latest_time + node_interval < cur_time) {
            dsc_driver.BuildDSClientMap();
        }
    }
} 


}  // end of namespace storage_client

}  // end of namespace dist_storage





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
