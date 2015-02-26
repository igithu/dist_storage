/***************************************************************************
 * 
 * Copyright (c) 2015 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file config_manager.h
 * @author aishuyu(asy5178@163.com)
 * @date 2015/01/02 15:58:14
 * @brief 
 *  
 **/




#ifndef  __CONFIG_MANAGER_H_
#define  __CONFIG_MANAGER_H_

#include <string>
#include <memory>

#include "atomic.h"
#include "iniparser.h"
#include "disallow_copy_and_assign.h"
#include "pthread_mutex.h"

#define NOT_EXIST_INT -1
#define INI_ERROR_INT -2
#define INI_NULL_INT -3

#define NOT_EXIST_DOU -1.0
#define INI_ERROR_DOU -2.0
#define INI_NULL_DOU -3.0

#define NOT_EXIST_STR "ne"
#define INI_ERROR_STR "error"
#define INI_NULL_STR "null"


#define DS_SYS_CONF dist_storage::ConfigManager::GetInstance()
#define MAX_HOST_LEN 128;

namespace dist_storage {

class ConfigManager;
typedef std::auto_ptr<ConfigManager> CMSmartPtr;

class ConfigManager {
    public:
        ~ConfigManager();

        bool ConfigInit(const char* conf_file);

        static ConfigManager& GetInstance();

        int32_t GetSecKeysNum(const std::string& sec_key);

        int32_t IniGetInt(const std::string& sec_key);

        double IniGetDouble(const std::string& sec_key);

        const char *IniGetString(const std::string& sec_key);

        bool IniGetBool(const std::string& sec_key);

        const char *IniGetLocalIPAddr();

        const char *IniGetLocalHostName();


    private:
        ConfigManager();

        DISALLOW_COPY_AND_ASSIGN(ConfigManager);

    private:
        static CMSmartPtr config_manager_ptr_;

        static PUBLIC_UTIL::ATOMIC_BOOL is_init_;

        static PUBLIC_UTIL::Mutex instance_mutex_;

        dictionary* dict_ini_;

        char localhost_name_[MAX_HOST_LEN];

        char localip_addr_[MAX_HOST_LEN];

        //ConfigManager instance_ptr_;
};


}  // end of namespace dist_storage



#endif  //__CONFIG_MANAGER_H_


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
