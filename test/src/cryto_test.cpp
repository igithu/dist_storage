/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file cryto_test.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/09 13:36:45
 * @brief 
 *  
 **/

#include <stdio.h>

#include <string>

#include "../../util/crytocpp.h"
#include "../../util/dist_hash.h"

using namespace dist_storage;

int main() {

    //unsigned char md5_str[] = "HelloWWW";
    
    int n = 40;

    for (int i = 0; i < n / 4; ++i) {
        std::string m_str = "HelloWWW";
        unsigned char md5_str[15];
        unsigned char digest[16];
        sprintf((char*)md5_str, "%s%c", m_str.c_str(), static_cast<char>(i));
        MD5(md5_str, digest);
        for (int j = 0; j < 4; ++j) {
            long m = KetamaHash(digest, j);
            printf("Test mhash is %ld\n", m);
        }
    }

    printf("\n");
    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
