/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file node_manager.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/01/15 17:24:07
 * @brief 
 *  
 **/

#include "node_manager.h"

#include <time.h>

#include "tools.h"
#include "../../include/inter_include.h"
#include "../../proto/name_serv.pb.h"

namespace dist_storage {

namespace name_server {

using namespace PUBLIC_UTIL;
using std::string;

PUBLIC_UTIL::Mutex NodeManager::instance_mutex_;
NSSmartPtr NodeManager::node_manager_ptr_(NULL);

NodeManager::NodeManager() :
   nse_thread_ptr_(NULL),
   nsu_thread_ptr_(NULL) {
}

NodeManager::~NodeManager() {
   if (NULL != nse_thread_ptr_) {
       delete nse_thread_ptr_;
   }

    if (NULL != nsu_thread_ptr_) {
        delete nsu_thread_ptr_;
    }

}

NodeManager& NodeManager::GetInstance() {
    if (NULL == node_manager_ptr_.get()) {
        MutexLockGuard lock(instance_mutex_);
        node_manager_ptr_.reset(new NodeManager());
        return *node_manager_ptr_;
    }   
    return *node_manager_ptr_;
}

bool NodeManager::InitNM() {
    const char* server_list_str = DS_SYS_CONF.IniGetString("server:data_server");
    vector<string> data_node_list;
    Split(server_list_str, ",", data_node_list);

    for (vector<string>::iterator ser_iter = data_node_list.begin();
         ser_iter != data_node_list.end();
         ++ser_iter) {

        const string& server_str = *ser_iter;
        NS_HASH_MAP::iterator nsi_iter = node_info_map_.find(*ser_iter);
        // init node status info
        if (nsi_iter == node_info_map_.end()) {
            NI_PTR cur_ni_ptr(new NodeInfo()); 
            cur_ni_ptr->updated_time = 0;
            cur_ni_ptr->avail_space = 0;
            cur_ni_ptr->visit_flow = 0;

            NS_PTR cur_nsi_ptr(new NodeStatus()); 
            cur_nsi_ptr->status = UnReg;

            NodeStatusInfo nsi;
            nsi.node_info_ptr.swap(cur_ni_ptr);
            nsi.node_status_ptr.swap(cur_nsi_ptr);

            node_info_map_.insert(std::make_pair(server_str, nsi));
        } 
    }
    is_status_updated_ = true;

    return true;
}

bool NodeManager::Start() {

    nse_thread_ptr_ = new NameServiceThread();
    nsu_thread_ptr_ = new NodeStatusUpdater();
    
    nse_thread_ptr_->Start();
    nsu_thread_ptr_->Start();

    return true;
}

bool NodeManager::Wait() {

    if (NULL != nse_thread_ptr_) {
        nse_thread_ptr_->Wait();
    }

    if (NULL != nsu_thread_ptr_) {
        nsu_thread_ptr_->Wait();
    }
}

bool NodeManager::UpdateNodeInfo(const string& server_str, NI_PTR& hb_ni_ptr) {
    if (NULL == hb_ni_ptr) {
        DS_LOG(ERROR, "update node info error!hb_ni_ptr is NULL!");
        return false;
    }

    NS_HASH_MAP::iterator nsi_iter = node_info_map_.find(server_str);
    if (nsi_iter == node_info_map_.end()) {
        DS_LOG(WARNING, "the host %s is not set in name_server config file! update exit now!",
                server_str.c_str());
        return false;
    }

    NodeStatusInfo& nsi = nsi_iter->second;
    if (NULL == nsi.node_info_ptr) {
        DS_LOG(ERROR, "node_status_info update failed! info ptr is NULL!");
        return false;
    }

    PUBLIC_UTIL::Mutex& info_mutex = nsi.info_mutex;
    {
        MutexLockGuard guard(info_mutex);
        nsi.node_info_ptr.swap(hb_ni_ptr);
    }
    return true;
}

bool NodeManager::UpdateNodeStatus() {

    int64_t now_time = time(NULL);

    int64_t pend_time = DS_SYS_CONF.IniGetInt("name_service:pending_timeout");
    int64_t dead_time = DS_SYS_CONF.IniGetInt("name_service:dead_timeout");

    if (dead_time - pend_time < 30) {
        //DS_LOG(WARNING, "invalid pending_timeout and dead_timeout set! 
        //        dead_timeout must be more than pend_time 30s!
        //        now set pending_timeout 60s, set dead_timeout 120s");
        pend_time = 60;
        dead_time = 120;
    }
    
    for (NS_HASH_MAP::iterator nsi_iter = node_info_map_.begin();
         nsi_iter != node_info_map_.end();
         ++nsi_iter) {
        NodeStatusInfo& nsi = nsi_iter->second;
        NI_PTR& ni_ptr = nsi.node_info_ptr; 
        NS_PTR& ns_ptr = nsi.node_status_ptr;
        if (NULL == ni_ptr || NULL == ns_ptr) {
            DS_LOG(ERROR, "invalid node status info!");
            continue;
        }

        Status cur_status = Alive;
        {
            MutexLockGuard guard(nsi.info_mutex);
            if (ni_ptr->updated_time > 0) {
                int64_t interval = now_time - ni_ptr->updated_time;
                if (interval > dead_time) {
                    cur_status = Dead;
                } else if (interval > pend_time) {
                    cur_status = Pending;
                }
            } else {
                cur_status = UnReg;
            }
        }

        {
            ReadLockGuard rguard(nsi.status_rwlock);
            if (cur_status == ns_ptr->status) {
                continue;
            }
        }

        {
            WriteLockGuard wguard(nsi.status_rwlock);
            ns_ptr->status = cur_status;
        }
    }
    return true;
}

bool NodeManager::UpdateNodeList() {
    NODE_LIST_PTR alive_list_ptr(new NODE_LIST());
    NODE_LIST_PTR unavailable_list_ptr(new NODE_LIST());

    for (NS_HASH_MAP::iterator nsi_iter = node_info_map_.begin();
         nsi_iter != node_info_map_.end();
         ++nsi_iter) {
        NodeStatusInfo& nsi = nsi_iter->second;
        {
            ReadLockGuard rguard(nsi.status_rwlock);
            if (nsi.node_status_ptr->status == Alive ) {
                alive_list_ptr->insert(nsi.host);
            } else {
                unavailable_list_ptr->insert(nsi.host);
            }
        }
    }

    {
        WriteLockGuard wguard(alive_rwlock_);
        alive_list_ptr.swap(alive_nlist_ptr_);
    }

    {
        WriteLockGuard wguard(unavail_rwlock_);
        unavailable_list_ptr.swap(unavail_nlist_ptr_);
    }

    return true;
}

bool NodeManager::GetAliveNodes(vector<string> node_list) {
    NODE_LIST_PTR nl_ptr;
    {
        WriteLockGuard wguard();
        nl_ptr = alive_nlist_ptr_;
    }

    if (NULL == nl_ptr) {
        DS_LOG(ERROR, "get alive node list failed! the alive ptr is NULL!");
        return false;
    }

    for (NODE_LIST::iterator niter = nl_ptr->begin(); niter != nl_ptr->end(); ++niter) {
        node_list.push_back(*niter);
    }
    return true;
}

}  // end of namespace namespace

}  // end of namespace dist_storage





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
