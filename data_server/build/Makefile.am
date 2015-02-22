
#SUBDIRS=src
#DIST_SUBDIRS=src

root_dir=${top_srcdir}/..
toproot_dir=${root_dir}/..
common_dir=${toproot_dir}/common
third_dir=${toproot_dir}/../third-64
pub_dir=${toproot_dir}/../pub_util
UTIL_LIB=${pub_dir}/tools/tools.h  ${pub_dir}/tools/tools.cpp

INCLUDES=-I${root_dir} -I${toproot_dir} -I${common_dir}

COMMON_SRC=${common_dir}/config/config_manager.h \
		   ${common_dir}/config/config_manager.cpp \
		   ${common_dir}/rpc/socket_util.h \
		   ${common_dir}/rpc/socket_util.cpp \
		   ${common_dir}/rpc/rpc_util.h \
		   ${common_dir}/rpc/rpc_util.cpp \
		   ${common_dir}/rpc/rpc_msg.pb.h \
		   ${common_dir}/rpc/rpc_msg.pb.cc \
		   ${common_dir}/proto/data_serv.pb.h \
		   ${common_dir}/proto/data_serv.pb.cc \
		   ${common_dir}/include/inter_include.h \
		   ${common_dir}/include/ext_include.h \
		   ${common_dir}/log/ds_log.h \
		   ${common_dir}/log/ds_log.cpp 

COMMON_CF =-I${third_dir}/protobuf/include/ \
		   -I${third_dir}/glog/include/ \
		   -I${third_dir}/boost/include/ \
		   -I${third_dir}/iniparser/include/ \
		   -I${third_dir}/libev/include/ \
		   -I${pub_dir}/tools/include/

COMMON_LD = -lpthread -lz -ldl -lrt \
		   ${third_dir}/protobuf/lib/*.a \
		   ${third_dir}/glog/lib/*.a \
		   ${third_dir}/iniparser/lib/*.a \
		   ${third_dir}/libev/lib/*.a \
		   ${third_dir}/boost/lib/*.a

bin_PROGRAMS = data_server

data_server_SOURCES = \
		      ${root_dir}/server/data_server.cc \
		      ${root_dir}/server/data_service.h \
		      ${root_dir}/server/data_service.cpp \
			  ${root_dir}/storage/common_db.h \
			  ${root_dir}/storage/level_db.h \
			  ${root_dir}/storage/level_db.cpp \
			  ${common_dir}/rpc/libev_connector.h \
			  ${common_dir}/rpc/libev_connector.cpp \
			  ${common_dir}/rpc/rpc_server.h \
			  ${common_dir}/rpc/rpc_server.cpp \
			  ${common_dir}/rpc/io_thread.h \
			  ${common_dir}/rpc/io_thread.cpp \
			  ${common_dir}/rpc/thread_pool.h \
			  ${common_dir}/rpc/thread_pool.cpp \
			  $(COMMON_SRC) \
			  $(UTIL_LIB)
data_server_CPPFLAGS = $(COMMON_CF) \
						 -I${third_dir}/leveldb/include/ \
  						 -I${pub_dir}/thread/include/
data_server_LDFLAGS =-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
data_server_LDADD = $(COMMON_LD)  ${third_dir}/leveldb/lib/*.a 
