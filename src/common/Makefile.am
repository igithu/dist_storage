top_dir = ${top_srcdir}/..
common_rootdir = ${top_srcdir}/src/common
third_dir = ${top_dir}/third-64

AM_CPPFLAGS = -I${third_dir}/glog/include/ \
			  -I${third_dir}/crypto/include/

AM_LDFLAGS = -lz -lrt -rdynamic

LDADD = ${third_dir}/glog/lib/libglog.a \
		${third_dir}/crypto/lib/*.a

AM_CXXFLAGS = -Werror

include_HEADERS = ${common_rootdir}/ds_log.h \
				  ${common_rootdir}/crytocpp.h \
				  ${common_rootdir}/tools.h \
				  ${common_rootdir}/dist_hash.h


COMMON_SRC = ${common_rootdir}/ds_log.h \
			 ${common_rootdir}/ds_log.cpp \
			 ${common_rootdir}/crytocpp.h \
			 ${common_rootdir}/crytocpp.cpp \
			 ${common_rootdir}/tools.h \
			 ${common_rootdir}/tools.cpp \
			 ${common_rootdir}/dist_hash.h \
			 ${common_rootdir}/dist_hash.cpp

noinst_LIBRARIES = libcommon.a

libcommon_a_SOURCES = ${COMMON_SRC}

