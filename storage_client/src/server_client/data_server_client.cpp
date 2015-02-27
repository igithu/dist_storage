/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file data_server_client.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/22 15:13:31
 * @brief 
 *  
 **/

#include "data_server_client.h"

namespace dist_storage { 

namespace storage_client {

DataServerClient::DataServerClient() {
}

DataServerClient::~DataServerClient() {
}

bool DataServerClient::ClientInit() {
    return true;
}

bool DataServerClient::Put(const char* key, const char* value) {
    return true;
}

bool DataServerClient::Get(const char* key, string& value) {
    return true;
}

bool DataServerClient:L::Delete(const char* key) {
    return true;
}


}  // end of namespace storage_client

}  // end of namespace dist_storage 





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
