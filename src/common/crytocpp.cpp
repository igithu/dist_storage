/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file crytocpp.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/10 17:32:16
 * @brief 
 *  
 **/


#include "crytocpp.h"

#include <stdio.h>

#include <cryptopp/hex.h>
#include <cryptopp/files.h>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#pragma comment (lib,"cryptlib.lib")


namespace dist_storage {

using namespace CryptoPP;

bool MD5(unsigned char* md5_str, unsigned char digest[16]) {
    //int32_t len = strlen(static_cast<const char*>(md5_str));
    int32_t len = strlen((const char*)(md5_str));
    if (0 >= len) {
        return false;
    }
    Weak::MD5 md5;
    md5.Update(md5_str, len);
    md5.Final(digest);
    return true;
}



}  // end of namespace dist_storage











/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
