/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file truncate_hash.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/11 13:20:36
 * @brief 
 *  
 **/




#ifndef  __TRUNCATE_HASH_H_
#define  __TRUNCATE_HASH_H_

#include <stdio.h>

namespace dist_storage {

typedef unsigned long Long;

Long KetamaHash(unsigned char digest[], Long locate);


}  // end of namespace dist_strorage








#endif  //__TRUNCATE_HASH_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
