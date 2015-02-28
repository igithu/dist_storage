
nameserver_rootdir = ${top_srcdir}/src/nameserver
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


NAMESERVER_SRC=${nameserver_rootdir}/name_server.cc \
			   ${nameserver_rootdir}/name_service.h \
			   ${nameserver_rootdir}/name_service.cpp \
			   ${nameserver_rootdir}/node_manager.h \
			   ${nameserver_rootdir}/node_manager.cpp \
			   ${nameserver_rootdir}/node_status_updater.h \
			   ${nameserver_rootdir}/node_status_updater.cpp \
			   ${nameserver_rootdir}/distribution_manager.h \
			   ${nameserver_rootdir}/distribution_manager.cpp \
			   ${nameserver_rootdir}/distribute_alg.h \
			   ${nameserver_rootdir}/ketamadist_alg.h \
			   ${nameserver_rootdir}/ketamadist_alg.cpp

#noinst_LIBRARIES=name_server.a

bin_PROGRAMS = name_server

name_server_SOURCES=${NAMESERVER_SRC}

