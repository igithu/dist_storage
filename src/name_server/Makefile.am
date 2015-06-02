AUTOMAKE_OPTIONS = foreign subdir-objects

top_dir = ${top_srcdir}/..
nameserver_rootdir = ${top_srcdir}/src/name_server
third_dir = ${top_dir}/third-32
pub_dir = ${top_dir}/pub_util

AM_CPPFLAGS = -I${top_srcdir}/src \
			  -I${third_dir}/protobuf/include/ \
			  -I${third_dir}/glog/include/ \
			  -I${third_dir}/boost/include/ \
			  -I${third_dir}/libev/include/ \
			  -I${third_dir}/crypto/include/ \
			  -I${third_dir}/iniparser/include/ \
			  -I${pub_dir}

AM_LDFLAGS = -lz -lrt

LDADD = $(top_builddir)/src/rpc/librpc.a \
		$(top_builddir)/src/config/libconfig.a \
		$(top_builddir)/src/common/libcommon.a \
		$(top_builddir)/src/proto/libproto.a \
		${third_dir}/protobuf/lib/*.a \
		${third_dir}/glog/lib/*.a \
		${third_dir}/boost/lib/*.a \
		${third_dir}/libev/lib/*.a \
		${third_dir}/crypto/lib/*.a \
		${third_dir}/iniparser/lib/*.a


NAMESERVER_SRC = ${nameserver_rootdir}/name_server.cc \
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

name_server_SOURCES = ${NAMESERVER_SRC}

SUBDIRS = test
