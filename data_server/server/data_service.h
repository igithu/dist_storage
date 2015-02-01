/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file data_service.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/10 15:45:48
 * @brief 
 *  
 **/




#ifndef  __ENGINE_SERVICE_H_
#define  __ENGINE_SERVICE_H_


#include "../../proto/data_serv.pb.h"
#include "../storage/common_db.h"

namespace dist_storage {

namespace data_server {

using namespace google::protobuf;

class DataServiceImpl : public DataService {
    public:

        DataServiceImpl();

        ~DataServiceImpl();

        virtual void Put(RpcController* controller,
                         const DSRequest* request,
                         DSResponse* response,
                         Closure* done);

        virtual void Get(RpcController* controller,
                         const DSRequest* request,
                         DSResponse* response,
                         Closure* done);

        virtual void Delete(RpcController* controller,
                            const DSRequest* request,
                            DSResponse* response,
                            Closure* done);
    private:
        bool EngineServiceInit();

    private:
        CommonDS* common_ds_ptr_;
};


}  // end of namespace data_server

}  // end of namespace dist_storage













#endif  //__ENGINE_SERVICE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
