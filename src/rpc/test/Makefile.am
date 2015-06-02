AUTOMAKE_OPTIONS = foreign subdir-objects

rpc_rootdir=${top_srcdir}/src/rpc
test_rootdir=${rpc_rootdir}/test
top_dir=../../../..
third_dir=../../../../third-32
pub_dir=${top_dir}/pub_util

AM_CPPFLAGS=-I${top_srcdir}/src \
            -I${third_dir}/protobuf/include/ \
            -I${third_dir}/glog/include/ \
			-I${third_dir}/boost/include/ \
			-I${third_dir}/libev/include/ \
			-I${third_dir}/crypto/include/ \
			-I${third_dir}/iniparser/include/ \
			-I${pub_dir}

AM_LDFLAGS=-lz -lrt

LDADD=${third_dir}/protobuf/lib/*.a \
      ${third_dir}/glog/lib/*.a \
	  ${third_dir}/boost/lib/*.a \
	  ${third_dir}/libev/lib/*.a \
	  ${third_dir}/crypto/lib/*.a \
	   ${third_dir}/iniparser/lib/*.a 

bin_PROGRAMS = testsocket_client testsocket_server

TSC_SRC=${test_rootdir}/testsocket_client.cpp \
		${rpc_rootdir}/socket_util.h \
		${rpc_rootdir}/socket_util.cpp

testsocket_client_SOURCES=${TSC_SRC}


TSS_SRC=${test_rootdir}/test_server.cpp \
		${rpc_rootdir}/socket_util.h \
		${rpc_rootdir}/socket_util.cpp

testsocket_server_SOURCES=${TSS_SRC}


