/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file heartbeat_thread.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/25 18:49:35
 * @brief 
 *  
 **/




#ifndef  __HEARTBEAT_THREAD_H_
#define  __HEARTBEAT_THREAD_H_

#include "thread.h"
#include "name_server_client.h"

namespace dist_storage {

namespace data_server {

class HeartBeatThread : public  PUBLIC_UTIL::Thread {
    public:
        // ctor
        HeartBeatThread();

        // dtor
        ~HeartBeatThread();

        virtual void Run();

    private:
        NameServerClient ns_client_;

};

}  // end of namespace data_server

}  // end of namespace dist_storage





#endif  //__HEARTBEAT_THREAD_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
