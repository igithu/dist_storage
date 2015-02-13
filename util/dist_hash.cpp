/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file dist_hash.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/11 13:36:15
 * @brief 
 *  
 **/


#include "dist_hash.h"


namespace dist_storage {

Long KetamaHash(unsigned char digest[], Long locate) {
    unsigned int hash_val = (digest[3 + locate * 4] << 24) | 
                   (digest[2 + locate * 4] << 16) | 
                   (digest[1 + locate * 4] << 8) | 
                   (digest[3 + locate * 4]);

    return hash_val & 0xffffffffL;
}


}  // end of namespace













/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
