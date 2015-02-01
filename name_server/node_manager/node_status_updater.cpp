/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file node_status_updater.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/01/18 15:38:27
 * @brief 
 *  
 **/

#include "node_status_updater.h"

#include "node_manager.h"
#include "../../include/inter_include.h"

namespace dist_storage {

namespace name_server {

NodeStatusUpdater::NodeStatusUpdater() {
}

NodeStatusUpdater::~NodeStatusUpdater() {
}

void NodeStatusUpdater::Run() {
    int64_t updated_interval = 
        DS_SYS_CONF.IniGetInt("name_service:status_update_interval");

    while (true) {
        if (!GlobalNM.UpdateNodeList()) {
            DS_LOG(WARNING, "NodeStatusUpdater call update node list failed!");
        }

        sleep(updated_interval);
    }

}


}  // end of namespace name_server

}  // end of namespace dist_storage





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
