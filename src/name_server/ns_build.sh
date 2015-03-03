#!/bin/sh
#!/bin/bash

#build the data_server
#must have generated Makefile  or be failed for sure

BUILD_ROOT=$PWD
TOP_ROOT=../..
START_FILE=$TOP_ROOT/scripts/name_server.sh
SERVER_PATH=$BUILD_ROOT/nserver
SERVER_BIN_PATH=$SERVER_PATH/bin
SERVER_CONF_PATH=$SERVER_PATH/conf
CONF_PATH=$TOP_ROOT/share/conf
CONF_FILE=$CONF_PATH/name_server.ini 


if [ ! -f $BUILD_ROOT/Makefile ]
then
    echo "Please run the build.sh in top root path FIRST!"
    exit -1
fi

make clean

# make the project
make
if [ $? -ne 0 ]
then
    echo "make the project failed!"
    exit -1
fi


# start to collect the project file 
# make sure the config file exist
if [ ! -f $CONF_FILE ]
then
    echo "the config file $CONF_FILE does not exist"
    exit -1
fi

if [ ! -f $START_FILE ]
then
    echo "the $START_FILE file does not exist"
    exit -1
fi

if [ -d $SERVER_PATH ]
then
    rm -rf  $SERVER_PATH
fi 


# make sure the path SERVER_BIN_PATH exist
if [ ! -d $SERVER_BIN_PATH ]
then
    mkdir -p $SERVER_BIN_PATH
fi 

if [ ! -d $SERVER_CONF_PATH ]
then
    mkdir -p $SERVER_CONF_PATH
fi 

mv name_server $SERVER_BIN_PATH && \
cp $CONF_FILE $SERVER_CONF_PATH/ && \
cp $START_FILE $SERVER_BIN_PATH/

if [ $? -ne 0 ]
then
    echo "build the name server bin failed"
    exit -1
fi

echo "build the name server successfully!!"

make clean


