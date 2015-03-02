
dataserver_rootdir = ${top_srcdir}/src/data_server
top_dir=../../..
third_dir=../../../third-64
pub_dir=${top_dir}/pub_util

#INCLUDES=-I${top_srcdir}/src -I${third_dir}/protobuf/include/ -I${third_dir}/iniparser/include/

AM_CPPFLAGS=-I${top_srcdir}/src \
			-I${third_dir}/protobuf/include/ \
            -I${third_dir}/glog/include/ \
			-I${third_dir}/boost/include/ \
			-I${third_dir}/libev/include/ \
			-I${third_dir}/crypto/include/ \
			-I${third_dir}/iniparser/include/ \
			-I${third_dir}/leveldb/include/ \
			-I${pub_dir}


AM_LDFLAGS=-rdynamic -lpthread -lz -lm -lrt -lssl -lcrypto -ldl -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H


LDADD=$(top_builddir)/src/rpc/librpc.a \
	  $(top_builddir)/src/config/libconfig.a \
	  $(top_builddir)/src/common/libcommon.a \
	  $(top_builddir)/src/proto/libproto.a \
      ${third_dir}/glog/lib/*.a \
	  ${third_dir}/protobuf/lib/*.a \
	  ${third_dir}/boost/lib/*.a \
	  ${third_dir}/libev/lib/*.a \
	  ${third_dir}/crypto/lib/*.a \
	  ${third_dir}/iniparser/lib/*.a \
	  ${third_dir}/leveldb/lib/*.a

dataserver_LDADD=${LDADD}


DATASERVER_SRC=${dataserver_rootdir}/data_service.h \
			   ${dataserver_rootdir}/data_service.cpp \
			   ${dataserver_rootdir}/name_server_client.h \
			   ${dataserver_rootdir}/name_server_client.cpp \
			   ${dataserver_rootdir}/heartbeat_thread.h \
			   ${dataserver_rootdir}/heartbeat_thread.cpp \
			   ${dataserver_rootdir}/level_db.h \
			   ${dataserver_rootdir}/level_db.cpp \
			   ${dataserver_rootdir}/common_db.h


libnameserver_a_LIBFLAGS=$(AM_LDFLAGS)

noinst_LIBRARIES=libdata_server.a

libdata_server_a_SOURCES=${DATASERVER_SRC} ${dataserver_rootdir}/data_server.cc

bin_PROGRAMS = data_server

data_server_SOURCES=${DATASERVER_SRC} ${dataserver_rootdir}/data_server.cc

