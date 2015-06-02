AUTOMAKE_OPTIONS = foreign subdir-objects

top_dir=${top_srcdir}/..
test_rootdir=${top_srcdir}/src/test
third_dir=${top_dir}/third-32
pub_dir=${top_dir}/pub_util
config_dir=${top_srcdir}/src/config

INCLUDES = -I${top_srcdir}/src \
           -I${third_dir}/protobuf/include/ \
           -I${third_dir}/glog/include/ \
		   -I${third_dir}/boost/include/ \
		   -I${third_dir}/libev/include/ \
		   -I${third_dir}/crypto/include/ \
		   -I${third_dir}/iniparser/include/ \
		   -I${third_dir}/leveldb/include/ \
		   -I${pub_dir}

AM_LDFLAGS = -lz -lrt -rdynamic -static

#LDADD=${third_dir}/protobuf/lib/*.a \
#      ${third_dir}/glog/lib/*.a \
#	  ${third_dir}/boost/lib/*.a \
#	  ${third_dir}/libev/lib/*.a \
#	  ${third_dir}/crypto/lib/*.a \
#	  ${third_dir}/iniparser/lib/*.a \
#	  ${third_dir}/leveldb/lib/*.a \
#      $(top_builddir)/src/common/libcommon.a \
#	  $(top_builddir)/src/config/libconfig.a \
#	  $(top_builddir)/src/proto/libproto.a \
#	  $(top_builddir)/src/rpc/librpc.a

LDADD = ${third_dir}/glog/lib/*.a \
	    ${third_dir}/iniparser/lib/*.a \
	    $(top_builddir)/src/rpc/librpc.a  \
	    ${third_dir}/protobuf/lib/*.a \
	    ${third_dir}/libev/lib/*.a


libtest_a_LIBFLAGS=$(AM_LDFLAGS)

noinst_LIBRARIES = libtest.a

libtest_a_SOURCES= ${test_rootdir}/test_dataserver.cpp

bin_PROGRAMS = test

test_SOURCES = ${config_dir}/config_manager.h ${config_dir}/config_manager.cpp ${test_rootdir}/test_dataserver.cpp


