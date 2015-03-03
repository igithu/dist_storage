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



#include "client_thread.h"
#include "client_driver.h"

using namespace dist_storage;
using namespace dist_client;

int main() {

    GlobalDSClient.Start();
    
    if (!GlobalDSClient.Set("Test", "Testvalue")) {
        printf("set key failed");
    }
    
    GlobalDSClient.Wait();

    GlobalDSClient.Stop();

    return 0;
}
















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
