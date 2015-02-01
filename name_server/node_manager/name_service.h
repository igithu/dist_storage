/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file name_service.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/01/16 14:40:58
 * @brief 
 *  
 **/




#ifndef  __NAME_SERVICE_H_
#define  __NAME_SERVICE_H_

#include "thread.h"
#include "../../proto/name_serv.pb.h"

namespace dist_storage {

namespace name_server {

using namespace google::protobuf;

class NameServiceImpl : public NameSevice {
    public:
        // ctor
        NameServiceImpl();

        // dtor
        ~NameServiceImpl();

        virtual void HeartBeat(RpcController* controller,
                               const HBRequest* hb_request,
                               HBResponse* hb_reponse,
                               Closure* done);

    private:
};

class NameServiceThread : public PUBLIC_UTIL::Thread {
    public:
        // ctor
        NameServiceThread() {}

        // dtor
        ~NameServiceThread() {}

        virtual void Run();

};


}  // end of namespace name_server

}  // end of namespace dist_storage














#endif  //__NAME_SERVICE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
