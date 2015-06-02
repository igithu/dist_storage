AUTOMAKE_OPTIONS = foreign subdir-objects

nameserver_rootdir=${top_srcdir}/src/name_server
test_rootdir=${nameserver_rootdir}/test
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

LDADD=$(top_builddir)/src/config/libconfig.a \
	  $(top_builddir)/src/common/libcommon.a \
	  $(top_builddir)/src/proto/libproto.a \
	  $(top_builddir)/src/rpc/librpc.a \
      ${third_dir}/protobuf/lib/*.a \
      ${third_dir}/glog/lib/*.a \
	  ${third_dir}/boost/lib/*.a \
	  ${third_dir}/libev/lib/*.a \
	  ${third_dir}/crypto/lib/*.a \
	   ${third_dir}/iniparser/lib/*.a 

bin_PROGRAMS = test_dismg

#TESTDALG_SRC=${test_rootdir}/test_distalg.cpp \
#			 ${nameserver_rootdir}/distribute_alg.h \
#			 ${nameserver_rootdir}/ketamadist_alg.h \
#			 ${nameserver_rootdir}/ketamadist_alg.cpp

#noinst_LIBRARIES=name_server.a


#test_distalg_SOURCES=${TESTDALG_SRC}


TESTDIMG_SRC=${test_rootdir}/test_dismg.cpp \
			 ${nameserver_rootdir}/distribute_alg.h \
			 ${nameserver_rootdir}/ketamadist_alg.h \
			 ${nameserver_rootdir}/ketamadist_alg.cpp \
			 ${nameserver_rootdir}/distribution_manager.h \
			 ${nameserver_rootdir}/distribution_manager.cpp

test_dismg_SOURCES=${TESTDIMG_SRC}

#TESTNM_SRC=${test_rootdir}/test_nm.cpp \
#			 ${nameserver_rootdir}/node_manager.h \
#			 ${nameserver_rootdir}/node_manager.cpp \
#			 ${nameserver_rootdir}/node_status_updater.h \
#			 ${nameserver_rootdir}/node_status_updater.cpp
#
#test_nm_SOURCES=${TESTNM_SRC}

