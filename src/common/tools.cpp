/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file tools.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/29 14:11:09
 * @brief 
 *  
 **/


#include "tools.h"

#include <stdlib.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/detail/classification.hpp>

namespace dist_storage {

using std::string;
using std::vector;

bool Split(string& splited_str, const string& split_ch, vector<string>& split_vec) {
    // split the splited_str by split_ch and insert these string into split_vec
    vector<string> split_tmp_vec;
    split_vec.clear();
    boost::split(split_tmp_vec, splited_str, boost::is_any_of(split_ch));
    for (vector<string>::iterator cur_iter = split_tmp_vec.begin();
         cur_iter != split_tmp_vec.end();
         ++cur_iter) {
        string& cur_str = *cur_iter;
        if (" " == cur_str || "" == cur_str) {
            continue;
        }
        cur_str.erase(remove(cur_str.begin(), cur_str.end(), ' '), cur_str.end());
        split_vec.push_back(cur_str);
    }
    return true;
}


bool Split(const char* splited_chs, const string& split_ch, vector<string>& split_vec) {
    string splited_str = splited_chs;
    return Split(splited_str, split_ch, split_vec);
}


bool CreateDir(const char* path) {
    char cmd[256];
    sprintf(cmd, "mkdir -p %s", path);
    if (system(cmd) == -1) {
        return false;
    }
    return true;
}

}  // end of namespace dist_storage











/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
