
storageclient_rootdir = ${top_srcdir}/src/storage_client
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


SC_SRC=${storageclient_rootdir}/test_client.cc \
			   ${storageclient_rootdir}/client_driver.h \
			   ${storageclient_rootdir}/client_driver.cpp \
			   ${storageclient_rootdir}/client_thread.h \
			   ${storageclient_rootdir}/client_thread.cpp \
			   ${storageclient_rootdir}/name_server_client.h \
			   ${storageclient_rootdir}/name_server_client.cpp \
			   ${storageclient_rootdir}/data_server_client.h \
			   ${storageclient_rootdir}/data_server_client.cpp 

#noinst_LIBRARIES=storage_client.a

bin_PROGRAMS = storage_client

storage_client_SOURCES=${SC_SRC}

