/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file client.cc
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/22 22:31:33
 * @brief 
 *  
 **/

#include <string>

#include "config/config_manager.h"
#include "common/ds_log.h"
#include "common/tools.h"

#include "client_thread.h"
#include "client_driver.h"

using namespace dist_storage;
using namespace dist_client;

int main(int argc, char* argv[]) {
    if (!DS_SYS_CONF.ConfigInit("../conf/dist_client.ini")) {
        DS_LOG(ERROR, "init the dist client config failed!");
        return 0;
    }

    //const char* log_dir = DS_SYS_CONF.IniGetString("log:path");
    //if (!CreateDir(log_dir)) {
    //    DS_LOG(ERROR, "create log dir: %s faied!", log_dir);
    //    return 0;
    //}
    //if (false == DSLogInit(
    //            argc, argv, DS_SYS_CONF.IniGetString("log:level"), log_dir)) {
    //    return 0;
    //}

    DS_LOG(INFO, "start GlobalDSClient!");
    GlobalDSClient.Start();

    DS_LOG(INFO, "GlobalDSClient has started!");
    
    if (!GlobalDSClient.Set("Test", "Testvalue")) {
        printf("set key failed");
    }

    sleep(1);

    std::string test_value; 
    if (!GlobalDSClient.Get("Test", test_value)) {
        printf("get key failed.\n");
    }

    printf("get the value is %s.\n", test_value.c_str());

    GlobalDSClient.Stop();
    GlobalDSClient.Wait();


    return 0;
}
















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
