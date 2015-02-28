
dataserver_rootdir = ${top_srcdir}/src/data_server
third_dir=../../../third-64

AM_CPPFLAGS=-I${top_srcdir}/src \
            -I${third_dir}/protobuf/include/ \
            -I${third_dir}/glog/include/ \
			-I${third_dir}/boost/include/ \
			-I${third_dir}/libev/include/ \
			-I${third_dir}/crypto/include/

AM_LDFLAGS=-lz -lrt

LDADD=${third_dir}/protobuf/lib/*.a \
      ${third_dir}/glog/lib/*.a \
	  ${third_dir}/boost/lib/*.a \
	  ${third_dir}/libev/lib/*.a \
	  ${third_dir}/crypto/lib/*.a \
	  $(top_builddir)/src/common/libcommon.a \
	  $(top_builddir)/src/config/libconfig.a \
	  $(top_builddir)/src/rpc/librpc.a


DATASERVER_SRC=${dataserver_rootdir}/data_server.cc \
			   ${dataserver_rootdir}/data_service.h \
			   ${dataserver_rootdir}/data_service.cpp \
			   ${dataserver_rootdir}/name_server_client.h \
			   ${dataserver_rootdir}/name_server_client.cpp \
			   ${dataserver_rootdir}/heartbeat_thread.h \
			   ${dataserver_rootdir}/heartbeat_thread.cpp \
			   ${dataserver_rootdir}/common_db.h \
			   ${dataserver_rootdir}/level_db.h \
			   ${dataserver_rootdir}/level_db.cpp

#noinst_LIBRARIES=data_server.a

bin_PROGRAMS = data_server

data_server_SOURCES=${DATASERVER_SRC}

