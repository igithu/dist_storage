/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file config_manager.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2015/01/05 18:21:14
 * @brief 
 *  
 **/

#include "../include/inter_include.h"


namespace dist_storage {

using std::string;
using namespace PUBLIC_UTIL;

PUBLIC_UTIL::Mutex ConfigManager::instance_mutex_;
PUBLIC_UTIL::ATOMIC_BOOL ConfigManager::is_init_(false);
CMSmartPtr ConfigManager::config_manager_ptr_(NULL);

ConfigManager::ConfigManager() : dict_ini_(NULL) {
    DS_LOG(INFO, "ConfigManager init.");
}

ConfigManager::~ConfigManager() {
    if (NULL != dict_ini_) {
        iniparser_freedict(dict_ini_);
    }
}

ConfigManager& ConfigManager::GetInstance() {
    if (NULL == config_manager_ptr_.get()) {
        MutexLockGuard lock(instance_mutex_);
        config_manager_ptr_.reset(new ConfigManager());
        return *config_manager_ptr_;
    }
    return *config_manager_ptr_;;
}

bool ConfigManager::ConfigInit(const char* conf_file) {
    dict_ini_ = iniparser_load(conf_file);
    // dict_ini_ = iniparser_load("../conf/data_serv.ini");
    if (NULL == dict_ini_) {
        DS_LOG(ERROR, "iniparser_load failed!")
        return false;
    }
    is_init_ = true;
    return true;
}

int32_t ConfigManager::GetSecKeysNum(const std::string& sec_key) {
    return iniparser_getsecnkeys(dict_ini_, const_cast<char*>(sec_key.c_str()));
}

int32_t ConfigManager::IniGetInt(const string& sec_key) {
    if (NULL == dict_ini_) {
        DS_LOG(ERROR, "dict_ini_ null ptr !");
        return INI_NULL_INT; 
    }
    int32_t ret = iniparser_getint(dict_ini_, sec_key.c_str(), NOT_EXIST_INT);

    if (NOT_EXIST_INT == ret) {
        DS_LOG(WARNING, "get the int sec_key : %s failed!" , sec_key.c_str());
    }
    return ret;
}

double ConfigManager::IniGetDouble(const string& sec_key) {
    double ret = iniparser_getdouble(dict_ini_, sec_key.c_str(), NOT_EXIST_DOU);

    if (NOT_EXIST_DOU == ret) {
        DS_LOG(WARNING, "get the double sec_key : %s failed!" , sec_key.c_str());
    }
    return ret;
}

const char *ConfigManager::IniGetString(const string& sec_key) {
    char *ret = iniparser_getstring(dict_ini_, sec_key.c_str(), NOT_EXIST_STR);

    if (NOT_EXIST_STR == ret) {
        DS_LOG(WARNING, "get the string sec_key : %s failed!" , sec_key.c_str());
    }
    return ret;
}

bool ConfigManager::IniGetBool(const string& sec_key) {
    int32_t ret = iniparser_getboolean(dict_ini_, sec_key.c_str(), NOT_EXIST_INT);

    if (NOT_EXIST_INT == ret) {
        DS_LOG(WARNING, "get the bool sec_key : %s failed!" , sec_key.c_str());
    }
    return ret;
}


}  // end of namespace dist_storage







/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
