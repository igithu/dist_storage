
#SUBDIRS=src
#DIST_SUBDIRS=src

UTIL_LIB=../../../util/tools/tools.h ../../../util/tools/tools.cpp

COMM_LIB=../../config/config_manager.h \
		 ../../config/config_manager.cpp \
		 ../../rpc/connection_manager.h \
		 ../../rpc/connection_manager.cpp \
		 ../../rpc/rpc_util.h \
		 ../../rpc/rpc_util.cpp \
		 ../../rpc/rpc_msg.pb.h \
		 ../../rpc/rpc_msg.pb.cc \
		 ../../proto/data_serv.pb.h \
		 ../../proto/data_serv.pb.cc \
		 ../../include/inter_include.h \
		 ../../include/ext_include.h \
		 ../../log/ds_log.h \
		 ../../log/ds_log.cpp 

COMMON_CF = -I../../../third-64/protobuf/include/ \
		   -I../../../third-64/glog/include/ \
		   -I../../../third-64/boost/include/ \
		   -I../../../third-64/iniparser/include/ \
		   -I../../../util/tools/include/

COMMON_LD = -lpthread -lz -ldl -lrt \
		   ../../../third-64/protobuf/lib/*.a \
		   ../../../third-64/glog/lib/*.a \
		   ../../../third-64/iniparser/lib/*.a \
		   ../../../third-64/boost/lib/*.a

bin_PROGRAMS = data_server

data_server_SOURCES = \
		      ../server/data_server.cc \
		      ../server/data_service.h \
		      ../server/data_service.cpp \
			  ../storage/common_db.h \
			  ../storage/level_db.h \
			  ../storage/level_db.cpp \
			  ../../rpc/rpc_server.h \
			  ../../rpc/rpc_server.cpp \
			  ../../rpc/io_thread.h \
			  ../../rpc/io_thread.cpp \
			  ../../rpc/thread_pool.h \
			  ../../rpc/thread_pool.cpp \
			  $(COMM_LIB) \
			  $(UTIL_LIB)
data_server_CPPFLAGS = $(COMMON_CF) \
						 -I../../../third-64/leveldb/include/ \
  						 -I../../../util/thread/include/
data_server_LDFLAGS =-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
data_server_LDADD = $(COMMON_LD)  ../../../third-64/leveldb/lib/*.a 
