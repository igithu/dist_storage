/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file ketamadist_alg.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/02/12 16:01:16
 * @brief 
 *  
 **/


#include "ketamadist_alg.h"

#include "common/tools.h"
#include "common/ds_log.h"
#include "config/config_manager.h"
#include "common/crytocpp.h"
#include "common/dist_hash.h"

namespace dist_storage {    

namespace name_server {

using std::vector;
using std::string;
using namespace PUBLIC_UTIL;

bool KetamaDistAlg::BuildDistTable(BUCKET_NODE_MAP& bi_map) {

    int32_t buckt_num = 100;
    int32_t group_num = buckt_num / 4;
    
    const char* server_list_str = DS_SYS_CONF.IniGetString("service:data_server_list");
    vector<string> data_node_list;
    Split(server_list_str, ",", data_node_list);
    for (vector<string>::iterator ser_iter = data_node_list.begin();
         ser_iter != data_node_list.end();
         ++ser_iter) {
        const string& server_str = *ser_iter;
        for (int32_t i = 0; i < group_num; ++i) {
            unsigned char md5_str[server_str.size() + 2];
            sprintf((char*)md5_str, "%s%c", server_str.c_str(), static_cast<char>(i));
            unsigned char digest[16];
            MD5(md5_str, digest);
            for (int j = 0; j < 4; ++j) {
                Long m = KetamaHash(digest, j);
                BI_PTR bi_ptr(new BucketInfo());
                bi_ptr->number = m;
                bi_ptr->bnode_list_ptr->push_back(server_str);
                if (bi_map.find(m) != bi_map.end()) {
                    bi_map[m] = bi_ptr;
                } else {
                    bi_map.insert(std::make_pair(m, bi_ptr));
                }
            }
        }
    }

    return true;
}

bool KetamaDistAlg::GetDistNode(const BUCKET_NODE_MAP& bi_map,
                                const string& key, 
                                string& host) {
    if (bi_map.size() == 0) {
        return false;
    }
    unsigned char md5_str[key.size()];
    sprintf((char*)md5_str, "%s", key.c_str());

    unsigned char digest[16];
    MD5(md5_str, digest);
    Long m = KetamaHash(digest, 0);

    BUCKET_NODE_MAP::const_iterator bi_itr = bi_map.find(m);
    if (bi_itr != bi_map.end()) {
        const BN_LIST& bi_list = *(bi_itr->second->bnode_list_ptr);
        if (bi_list.size() == 0) {
            return false;
        }
        host = bi_list[0];
    } else {
        do {
            bi_itr = bi_map.lower_bound(m);
            if (bi_itr != bi_map.end()) {
                const BN_LIST& bi_list = *(bi_itr->second->bnode_list_ptr);
                if (bi_list.size() == 0) {
                    return false;
                }
                host = bi_list[0];
                break;
            }
            m = 0;
        } while(true);
    }
    return true;
}

}  // end of namespace name_server

}  // end of namespace dist_storage











/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
