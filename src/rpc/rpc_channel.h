/***************************************************************************
 * 
 * Copyright (c) 2014 Aishuyu. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file rpc_channel.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/11/23 16:37:20
 * @brief 
 *  
 **/




#ifndef  __RPC_CHANNEL_H_
#define  __RPC_CHANNEL_H_


#include <google/protobuf/service.h>
#include <google/protobuf/message.h>

namespace dist_storage {

using namespace google::protobuf;

class Channel : public RpcChannel {
    public:
        Channel(const char* addr, const char* port, bool allow_overlong = false);

        virtual ~Channel();

        bool ResetHost(const char* addr);

        bool ResetPort(const char* port);

        virtual void CallMethod(const MethodDescriptor* method,
                                RpcController* controll,
                                const Message* request,
                                Message* response,
                                Closure* done);

        void Close();

    private:
        //FormatSendMsg();

        //FormatRecvMsg();
    
    private:
        char* addr_;

        char* port_;

        int32_t connect_fd_;

        bool allow_overlong_;

};

}  // end of namespace dist_storage



#endif  //__RPC_CHANNEL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
