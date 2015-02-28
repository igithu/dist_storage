/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file engine_client.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/10 17:06:05
 * @brief 
 *  
 **/




#ifndef  __ENGINE_CLIENT_H_
#define  __ENGINE_CLIENT_H_

#include "../proto/db_engine.pb.h"
#include "../rpc/rpc_channel.h"

namespace db_engine {

using namespace google::protobuf;

class EngineClient {
    public:
        EngineClient();

        ~EngineClient();


        bool Put(const char* key, const char* value);

        bool Get(const char* key, std::string& value);

        bool Delete(const char* key);

    public:
        bool ClientInit();

    private:
        Channel* rpc_channel_ptr_;

        EngineService::Stub* serveice_stub_ptr_;

        //ConfigManager& config_manager_;

};

}  // end of namespace db_engine








#endif  //__ENGINE_CLIENT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
