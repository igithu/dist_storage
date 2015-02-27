/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file client_thread.cpp
 * @author aishuyu(com@baidu.com)
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
    while (true) {
        BN_MAP_PTR bn_map_ptr(new BN_MAP());
        ns_client_.GetBuketList(*bn_map_ptr);
        dsc_driver.UpdateBucketNodeMap(bn_map_ptr);
        sleep(60 * 30);
    }
} 


}  // end of namespace storage_client

}  // end of namespace dist_storage





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
