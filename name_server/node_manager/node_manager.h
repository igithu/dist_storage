/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file node_manager.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/01/15 17:21:28
 * @brief 
 *  
 **/




#ifndef  __NODE_MANAGER_H_
#define  __NODE_MANAGER_H_

//#include <memory>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <google/protobuf/repeated_field.h>

#include "atomic.h"
#include "pthread_mutex.h"
#include "pthread_rwlock.h"
#include "disallow_copy_and_assign.h"
#include "node_status_updater.h"
#include "server/name_service.h"

namespace dist_storage {

namespace name_server {

#define GlobalNM NodeManager::GetInstance()

enum Status {
    Reg,
    UnReg,
    Alive, 
    Pending,
    Dead 
};

typedef struct NodeInfo_t {
    // current node latest update time
    time_t updated_time;
    // node available space
    int64_t disk_space;
    // current flow
    int64_t visit_flow; 
} NodeInfo;

typedef struct NodeStatus_t {
    // current node
    Status status;
} NodeStatus;

typedef boost::shared_ptr<NodeInfo> NI_PTR;
typedef boost::shared_ptr<NodeStatus> NS_PTR;
typedef struct NodeStatusInfo_t {
    // ctor
    NodeStatusInfo_t() : 
        node_info_ptr(new NodeInfo_t()), node_status_ptr(new NodeStatus_t()) {
    }

    // dtor
    ~NodeStatusInfo_t() {
        node_info_ptr.reset();
        node_status_ptr.reset();
    }

    std::string host;
    // mutex for node_info_ptr
    PUBLIC_UTIL::Mutex info_mutex;
    // node info ptr
    NI_PTR node_info_ptr;
    // rwlock
    PUBLIC_UTIL::RWLock status_rwlock;
    // node status ptr
    NS_PTR node_status_ptr;
    // for other ext info
} NodeStatusInfo;

class NodeManager;

typedef boost::unordered_map<std::string, NodeStatusInfo> NS_HASH_MAP;
typedef boost::shared_ptr<NS_HASH_MAP> NS_HASH_MAP_PTR;
typedef boost::unordered_set<std::string> NODE_LIST; 
typedef boost::shared_ptr<boost::unordered_set<std::string> > NODE_LIST_PTR; 
typedef std::auto_ptr<NodeManager> NMSmartPtr;

class NodeManager {
    public:
        ~NodeManager();

        static NodeManager& GetInstance();

        bool InitNM();

        // start all threads
        bool Start();

        // block on all threads
        bool Wait();
        
        // api to node_info_map_
        bool UpdateNodeInfo(const string& server_str, NI_PTR& hb_ni_ptr);

        // api to node_info_map_
        bool UpdateNodeStatus();

        // relocate alive or unavailable node
        bool UpdateNodeList();

        // get the all alive nodes
        bool GetAliveNodes(::google::protobuf::RepeatedPtrField<std::string>& node_list);

    private:
        NodeManager();

        DISALLOW_COPY_AND_ASSIGN(NodeManager);

    private:
        // the nodes info come from conf file
        NS_HASH_MAP node_info_map_;

        // alive node list
        NODE_LIST_PTR alive_nlist_ptr_;

        // unavailable node list
        NODE_LIST_PTR unavail_nlist_ptr_;

        // for node_info_map_
        PUBLIC_UTIL::ATOMIC_BOOL is_status_updated_;       

        // rw lock for alive_nlist_ptr_ 
        PUBLIC_UTIL::RWLock alive_rwlock_;  

        // rw lock for unavail_nlist_ptr_
        PUBLIC_UTIL::RWLock unavail_rwlock_;  

        // for static
        static NMSmartPtr node_manager_ptr_;

        static PUBLIC_UTIL::Mutex instance_mutex_;
    private:
        // threads
        NameServiceThread* nse_thread_ptr_;

        NodeStatusUpdater* nsu_thread_ptr_;

};



}  // end of namespace name_server

}  // end of namespace dist_storage














#endif  //__NODE_MANAGER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
