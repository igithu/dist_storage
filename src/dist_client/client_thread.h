/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file client_thread.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/26 14:28:29
 * @brief 
 *  
 **/




#ifndef  __CLIENT_THREAD_H_
#define  __CLIENT_THREAD_H_


#include "thread.h"

namespace dist_storage {

namespace dist_client {

class DistStorageClientThread : public PUBLIC_UTIL::Thread {
    public:
        // ctor
        DistStorageClientThread();

        // dtor
        ~DistStorageClientThread();

        virtual void Run();
};


}  // end of namespace storage

}  // end of namespace dist_storage













#endif  //__CLIENT_THREAD_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
