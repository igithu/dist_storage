
#SUBDIRS=src
#DIST_SUBDIRS=src

root_dir=${top_srcdir}/../src
toproot_dir=${top_srcdir}/../..
common_dir=../../common
third_dir=../../../third-64
pub_dir=../../../pub_util
UTIL_LIB=${pub_dir}/tools.h ${pub_dir}/tools.cpp

INCLUDES=-I${root_dir} -I${toproot_dir} -I${common_dir} 

COMMON_SRC=${common_dir}/config/config_manager.h \
		   ${common_dir}/config/config_manager.cpp \
		   ${common_dir}/rpc/rpc_channel.h \
		   ${common_dir}/rpc/rpc_channel.cpp \
		   ${common_dir}/rpc/socket_util.h \
		   ${common_dir}/rpc/socket_util.cpp \
		   ${common_dir}/rpc/rpc_util.h \
		   ${common_dir}/rpc/rpc_util.cpp \
		   ${common_dir}/rpc/rpc_msg.pb.h \
		   ${common_dir}/rpc/rpc_msg.pb.cc \
		   ${common_dir}/proto/name_serv.pb.h \
		   ${common_dir}/proto/name_serv.pb.cc \
		   ${common_dir}/proto/data_serv.pb.h \
		   ${common_dir}/proto/data_serv.pb.cc \
		   ${common_dir}/util/dist_hash.h \
		   ${common_dir}/util/dist_hash.cpp \
		   ${common_dir}/util/crytocpp.h \
		   ${common_dir}/util/crytocpp.cpp \
		   ${common_dir}/log/ds_log.h \
		   ${common_dir}/log/ds_log.cpp 

COMMON_CF =-I${third_dir}/protobuf/include/ \
		   -I${third_dir}/glog/include/ \
		   -I${third_dir}/boost/include/ \
		   -I${third_dir}/iniparser/include/ \
		   -I${third_dir}/crypto/include/ \
		   -I${pub_dir}/

COMMON_LD = -lpthread -lz -ldl -lrt \
		   ${third_dir}/protobuf/lib/*.a \
		   ${third_dir}/glog/lib/*.a \
		   ${third_dir}/iniparser/lib/*.a \
		   ${third_dir}/crypto/lib/*.a \
		   ${third_dir}/boost/lib/*.a

bin_PROGRAMS = name_server

name_server_SOURCES = \
		      ${root_dir}/test_client.cc \
		      ${root_dir}/client_driver.h \
		      ${root_dir}/client_driver.cpp \
		      ${root_dir}/client_thread.h \
		      ${root_dir}/client_thread.cpp \
		      ${root_dir}/server_client/name_server_client.h \
		      ${root_dir}/server_client/name_server_client.cpp \
			  ${root_dir}/server_client/data_server_client.h \
			  ${root_dir}/server_client/data_server_client.cpp \
			  ${root_dir}/dist_alg/distribute_alg.h \
			  ${root_dir}/dist_alg/ketamadist_alg.h \
			  ${root_dir}/dist_alg/ketamadist_alg.cpp \
			  ${COMMON_SRC} \
			  ${UTIL_LIB}
name_server_CPPFLAGS = ${COMMON_CF}
name_server_LDFLAGS =-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
name_server_LDADD = $(COMMON_LD) 
