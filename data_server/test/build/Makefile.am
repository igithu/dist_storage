
#SUBDIRS=src
#DIST_SUBDIRS=src

UTIL_LIB=../../util/tools/tools.h ../../util/tools/tools.cpp

COMM_LIB=../config/config_manager.h \
		 ../config/config_manager.cpp \
		 ../rpc/connection_manager.h \
		 ../rpc/connection_manager.cpp \
		 ../rpc/rpc_util.h \
		 ../rpc/rpc_util.cpp \
		 ../rpc/rpc_msg.pb.h \
		 ../rpc/rpc_msg.pb.cc \
		 ../proto/db_engine.pb.h \
		 ../proto/db_engine.pb.cc \
		 ../include/inter_include.h \
		 ../include/ext_include.h \
		 ../log/db_log.h \
		 ../log/db_log.cpp 

COMMON_CF = -I../../third-64/protobuf/include/ \
		   -I../../third-64/glog/include/ \
		   -I../../third-64/boost/include/ \
		   -I../../third-64/iniparser/include/ \
		   -I../../util/tools/include/

COMMON_LD = -lpthread -lz -ldl -lrt \
		   ../../third-64/protobuf/lib/*.a \
		   ../../third-64/glog/lib/*.a \
		   ../../third-64/iniparser/lib/*.a \
		   ../../third-64/boost/lib/*.a

bin_PROGRAMS = shell_client engine_client engine_server

shell_client_SOURCES = \
		      ../client/shell_client_driver.cc \
		      ../client/shell_client.h \
		      ../client/shell_client.cpp \
		      ../client/engine_client.h \
		      ../client/engine_client.cpp \
			  ../rpc/rpc_channel.h \
			  ../rpc/rpc_channel.cpp \
			  $(COMM_LIB) \
			  $(UTIL_LIB)

#INCLUDES = -I../third-64/libevent/include/
#CXXFLAGS = -std=c++11 -Wall -g -fPIC
shell_client_CPPFLAGS = $(COMMON_CF) -I../../util/thread/include/
shell_client_LDFLAGS = -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
shell_client_LDADD = $(COMMON_LD)


engine_client_SOURCES = \
		      ../client/client.cc \
		      ../client/engine_client.h \
		      ../client/engine_client.cpp \
			  ../rpc/rpc_channel.h \
			  ../rpc/rpc_channel.cpp \
			  $(COMM_LIB)
engine_client_CPPFLAGS = $(COMMON_CF) 
engine_client_LDFLAGS = -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
engine_client_LDADD = $(COMMON_LD)




engine_server_SOURCES = \
		      ../server/engine_server.cc \
		      ../server/engine_service.h \
		      ../server/engine_service.cpp \
			  ../engine_db/common_db.h \
			  ../engine_db/level_db.h \
			  ../engine_db/level_db.cpp \
			  ../rpc/rpc_server.h \
			  ../rpc/rpc_server.cpp \
			  ../rpc/io_thread.h \
			  ../rpc/io_thread.cpp \
			  ../rpc/thread_pool.h \
			  ../rpc/thread_pool.cpp \
			  $(COMM_LIB) \
			  $(UTIL_LIB)
engine_server_CPPFLAGS = $(COMMON_CF) \
						 -I../../third-64/leveldb/include/ \
  						 -I../../util/thread/include/
engine_server_LDFLAGS =-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
engine_server_LDADD = $(COMMON_LD)  ../../third-64/leveldb/lib/*.a 
