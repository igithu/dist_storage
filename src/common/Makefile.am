
common_rootdir = ${top_srcdir}/src/common
third_dir=../../../third-64

AM_CPPFLAGS=-I${third_dir}/glog/include/ \
			-I${third_dir}/crypto/include/

AM_LDFLAGS=-lz -lrt

LDADD=${third_dir}/glog/lib/*.a \
	  ${third_dir}/crypto/lib/*.a


COMMON_SRC= ${common_rootdir}/ds_log.h \
			${common_rootdir}/ds_log.cpp \
			${common_rootdir}/crytocpp.h \
			${common_rootdir}/crytocpp.cpp \
			${common_rootdir}/dist_hash.h \
			${common_rootdir}/dist_hash.cpp

noinst_LIBRARIES=libcommon.a

libcommon_a_SOURCES=${COMMON_SRC}

include_HEADERS=${common_rootdir}/ds_log.h \
				${common_rootdir}/util/crytocpp.h \
				${common_rootdir}/util/dist_hash.h
