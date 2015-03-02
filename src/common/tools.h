/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file tools.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/29 14:01:54
 * @brief 
 *  
 **/




#ifndef  __SPLIT_H_
#define  __SPLIT_H_

#include <vector>
#include <string>

namespace dist_storage {

bool Split(std::string& splited_str, 
           const std::string& split_ch, 
           std::vector<std::string>& split_vec);

bool Split(const char* splited_chs, 
           const std::string& split_ch, 
           std::vector<std::string>& split_vec);

bool CreateDir(const char* path);

}  // end of namespace dist_storage








#endif  //__SPLIT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
