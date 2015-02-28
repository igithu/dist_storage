/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file node_status_updater.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/01/16 17:00:25
 * @brief 
 *  
 **/




#ifndef  __NODE_STATUS_UPDATER_H_
#define  __NODE_STATUS_UPDATER_H_

#include "thread.h"

namespace dist_storage {

namespace name_server {

class NodeStatusUpdater : public PUBLIC_UTIL::Thread {
    public:
        // ctor
        NodeStatusUpdater();

        // dtor
        ~NodeStatusUpdater();

        virtual void Run();
};


}  // end of namespace name_server


}  // end of namespace dist_storage














#endif  //__NODE_STATUS_UPDATER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
