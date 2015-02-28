/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file client.cc
 * @author aishuyu(asy5178@163.com)
 * @date 2014/12/11 14:29:55
 * @brief 
 *  
 **/

#include <iostream>

#include "engine_client.h"

using namespace std;
using namespace db_engine;

int main() {
    EngineClient client;

    printf("start put\n");
    client.Put("test", "Testvalue");

    string value;
    printf("start get\n");
    //client.Delete("test");
    client.Get("test", value);

    cout << "value is: " << value << endl;
    return 0;
}














/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
