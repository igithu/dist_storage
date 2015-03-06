/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_distalg.cpp
 * @author aishuyu(com@baidu.com)
 * @date 2015/03/04 16:27:40
 * @brief 
 *  
 **/

#include "config/config_manager.h"
#include "name_server/ketamadist_alg.h"
#include "common/ds_log.h"
#include "common/tools.h"

using namespace dist_storage;
using namespace name_server;

int main(int argc, char* argv[]) {
    if (!DS_SYS_CONF.ConfigInit("../../../share/conf/name_server.ini")) {
        DS_LOG(ERROR, "name server init the data server config failed!");
        return 0;
    }

    const char* log_dir = DS_SYS_CONF.IniGetString("log:path");

    if (!CreateDir(log_dir)) {
        DS_LOG(ERROR, "name server create log dir: %s faied!", log_dir);
        return 0;
    }
    if (false == DSLogInit(
                argc, argv, DS_SYS_CONF.IniGetString("log:level"), log_dir)) {
        return 0;
    }
    BUCKET_NODE_MAP bucket_node_map;
    KetamaDistAlg k_alg;
    k_alg.BuildDistTable(bucket_node_map);

    for (BUCKET_NODE_MAP::iterator iter = bucket_node_map.begin();
         iter != bucket_node_map.end();
         ++iter) {
        printf("Test number is %ld.\n", iter->first);
        BN_LIST& b_list = *(iter->second->bnode_list_ptr);
        for (BN_LIST::iterator l_iter = b_list.begin();
             l_iter != b_list.end();
             ++l_iter) {
            printf("The host is %s.\n",(*l_iter).c_str());
        }
    }


    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
