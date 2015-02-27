/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file client_thread.h
 * @author aishuyu(com@baidu.com)
 * @date 2015/02/26 14:28:29
 * @brief 
 *  
 **/




#ifndef  __CLIENT_THREAD_H_
#define  __CLIENT_THREAD_H_


#include "thread.h"
#include "server_client/name_server_client.h"

namespace dist_storage {

namespace storage_client {

class DistStorageClientThread : public PUBLIC_UTIL::Thread {
    public:
        // ctor
        DistStorageClientThread();

        // dtor
        ~DistStorageClientThread();

        virtual void Run();

    private:
        NameServerClient ns_client_;
};


}  // end of namespace storage

}  // end of namespace dist_storage













#endif  //__CLIENT_THREAD_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
