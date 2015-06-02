#!/bin/sh
#!/bin/bash

#build the all including name server, data server and dist_storage
#must have the bootstrap.sh file or be failed for sure
#must install automake

BUILD_ROOT=$PWD

CONF_PATH=$BUILD_ROOT/share/conf
SCRIPT_PATH=$BUILD_ROOT/scripts

SRC_ROOT=$BUILD_ROOT/src
NS_BIN_FILE=$SRC_ROOT/name_server/name_server
DS_BIN_FILE=$SRC_ROOT/data_server/data_server
CL_BIN_FILE=$SRC_ROOT/dist_client/dist_client

PRO_PATH=$BUILD_ROOT/dist_storage
DS_PATH=$PRO_PATH/data_server
NS_PATH=$PRO_PATH/name_server
CL_PATH=$PRO_PATH/dist_client

# bin file path
DS_BIN_PATH=$DS_PATH/bin
NS_BIN_PATH=$NS_PATH/bin
CL_BIN_PATH=$CL_PATH/bin

# config file path
DS_CONF_PATH=$DS_PATH/conf
NS_CONF_PATH=$NS_PATH/conf
CL_CONF_PATH=$CL_PATH/conf


function start_build()
{
    BIN_FILE=$1
    CONF_FILE=$2
    START_FILE=$3
    DI_BIN_PATH=$4
    DI_CONF_PATH=$5

    if [ ! -f $BIN_FILE ]
    then
        echo "1.The $BIN_FILE bin file is not exist!"
        return -1
    fi

    if [ ! -f $CONF_FILE ]
    then
        echo "2.The $CONF_FILE config file is not exist!"
        return -1
    fi

    if [ ! -f $START_FILE ]
    then
        echo "3.The $START_FILE  file is not exist!"
        return -1
    fi

    if [ ! -d $DI_BIN_PATH ]
    then
        mkdir -p $DI_BIN_PATH
    fi

    if [ ! -d $DI_CONF_PATH ]
    then
        mkdir -p $DI_CONF_PATH
    fi

    cp $BIN_FILE $START_FILE $DI_BIN_PATH/ &&
    cp $CONF_FILE $DI_CONF_PATH

    if [ $? -ne 0 ]
    then
        echo "Copy file failed when build $BIN_FILE "
        return -1
    fi

    return 0
}


# check the bootstrap exist.
if [ ! -f $BUILD_ROOT/bootstrap.sh ]
then
    echo "The bootstrap.sh does not exist!"
    exit -1
fi

if [ -d $PRO_PATH ] 
then
    rm -rf $PRO_PATH
fi
make distclean && ./bootstrap.sh clean
./bootstrap.sh

# check the configure file 
if [ ! -f $BUILD_ROOT/configure ]
then
    echo "The configure does not exist!"
    exit -1
fi

# make the project
./configure --disable-dependency-tracking
if [ $? -ne 0 ]
then
    echo "The configure the project failed!"
    exit -1
fi

if [ "$1" != "all" ]
then
    exit 0
fi

make
if [ $? -ne 0 ]
then
    echo "Error: make the project failed!"
    exit -1
fi



#start collect project file

start_build $NS_BIN_FILE $CONF_PATH/name_server.ini \
$SCRIPT_PATH/name_server.sh $NS_BIN_PATH $NS_CONF_PATH

start_build $DS_BIN_FILE $CONF_PATH/data_server.ini \
$SCRIPT_PATH/data_server.sh $DS_BIN_PATH $DS_CONF_PATH

start_build $CL_BIN_FILE $CONF_PATH/dist_client.ini \
$SCRIPT_PATH/dist_client.sh $CL_BIN_PATH $CL_CONF_PATH


if [ $? -ne 0 ]
then
    echo "build the clint bin failed"
    exit -1
fi

echo ""
echo "*******************************************************"
echo "build the dist storage project successfully!!"
echo "*******************************************************"
echo ""

make distclean && ./bootstrap.sh clean


