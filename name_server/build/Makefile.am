
#SUBDIRS=src
#DIST_SUBDIRS=src

root_dir=${top_srcdir}/..
toproot_dir=${root_dir}/../
common_dir=../../common
third_dir=../../../third-64
pub_dir=../../../pub_util
UTIL_LIB=${pub_dir}/tools/tools.h ${pub_dir}/tools/tools.cpp

INCLUDES=-I${root_dir} -I${toproot_dir} -I${common_dir} 

COMM_LIB=${common_dir}/config/config_manager.h \
		 ${common_dir}/config/config_manager.cpp \
		 ${common_dir}/rpc/socket_util.h \
		 ${common_dir}/rpc/socket_util.cpp \
		 ${common_dir}/rpc/rpc_util.h \
		 ${common_dir}/rpc/rpc_util.cpp \
		 ${common_dir}/rpc/rpc_msg.pb.h \
		 ${common_dir}/rpc/rpc_msg.pb.cc \
		 ${common_dir}/proto/name_serv.pb.h \
		 ${common_dir}/proto/name_serv.pb.cc \
		 ${common_dir}/include/inter_include.h \
		 ${common_dir}/include/ext_include.h \
		 ${common_dir}/util/dist_hash.h \
		 ${common_dir}/util/dist_hash.cpp \
		 ${common_dir}/util/crytocpp.h \
		 ${common_dir}/util/crytocpp.cpp \
		 ${common_dir}/log/ds_log.h \
		 ${common_dir}/log/ds_log.cpp 

COMMON_SRC =-I${third_dir}/protobuf/include/ \
		   -I${third_dir}/glog/include/ \
		   -I${third_dir}/boost/include/ \
		   -I${third_dir}/iniparser/include/ \
		   -I${third_dir}/libev/include/ \
		   -I${third_dir}/crypto/include/ \
		   -I${pub_dir}/thread/include/ \
		   -I${pub_dir}/tools/

COMMON_LD = -lpthread -lz -ldl -lrt \
		   ${third_dir}/protobuf/lib/*.a \
		   ${third_dir}/glog/lib/*.a \
		   ${third_dir}/iniparser/lib/*.a \
		   ${third_dir}/libev/lib/*.a \
		   ${third_dir}/crypto/lib/*.a \
		   ${third_dir}/boost/lib/*.a

bin_PROGRAMS = name_server

name_server_SOURCES = \
		      ${root_dir}/server/name_server.cc \
		      ${root_dir}/server/name_service.h \
		      ${root_dir}/server/name_service.cpp \
		      ${root_dir}/node_manager/node_manager.h \
		      ${root_dir}/node_manager/node_manager.cpp \
		      ${root_dir}/node_manager/node_status_updater.h \
		      ${root_dir}/node_manager/node_status_updater.cpp \
			  ${root_dir}/dist_manager/distribution_manager.h \
			  ${root_dir}/dist_manager/distribution_manager.cpp \
			  ${root_dir}/dist_manager/distribute_alg.h \
			  ${root_dir}/dist_manager/ketamadist_alg.h \
			  ${root_dir}/dist_manager/ketamadist_alg.cpp \
			  ${common_dir}/rpc/rpc_server.h \
			  ${common_dir}/rpc/rpc_server.cpp \
			  ${common_dir}/rpc/io_thread.h \
			  ${common_dir}/rpc/io_thread.cpp \
			  ${common_dir}/rpc/libev_connector.h \
			  ${common_dir}/rpc/libev_connector.cpp \
			  ${common_dir}/rpc/thread_pool.h \
			  ${common_dir}/rpc/thread_pool.cpp \
			  ${COMM_LIB} \
			  ${UTIL_LIB}
name_server_CPPFLAGS = ${COMMON_SRC} \
  						 -I${pub_dir}/thread/include/
name_server_LDFLAGS =-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
name_server_LDADD = $(COMMON_LD) 
