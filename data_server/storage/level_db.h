/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file level_db.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/08 13:44:26
 * @brief 
 *  
 **/




#ifndef  __LEVEL_DB_H_
#define  __LEVEL_DB_H_

#include <leveldb/db.h>

#include "common_db.h"

namespace dist_storage {

namespace data_server {

class LeveDB : public CommonDS {

    public:

        LeveDB(const char* db_path = "/tmp/testdb");

        ~LeveDB();

        virtual bool Put(const char* key, const char* value);

        virtual bool Get(const char* key, std::string& value);

        virtual bool Delete(const char* key);

    private:
         bool LeveDBInit(const char* db_path);

    private:
        leveldb::Options options_;

        leveldb::WriteOptions w_options_;

        leveldb::DB* db_ptr_;

};

}  // end of namespace data_server

}  // end of namespace dist_storage



#endif  //__LEVEL_DB_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
