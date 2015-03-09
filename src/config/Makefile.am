top_dir = ${top_srcdir}/..
config_rootdir = ${top_srcdir}/src/config
third_dir = ${top_dir}/third-64
pub_dir = ${top_dir}/pub_util

AM_CPPFLAGS = -I${top_srcdir}/src \
			  -I${third_dir}/boost/include/ \
			  -I${third_dir}/glog/include/ \
			  -I${third_dir}/iniparser/include/ \
			  -I${pub_dir}

AM_LDFLAGS = -lz -lrt -rdynamic

LDADD = ${third_dir}/boost/lib/*.a \
		${third_dir}/glog/lib/*.a \
		${third_dir}/iniparser/lib/*.a \
		$(top_builddir)/src/common/libcommon.a


CONFIG_SRC = ${config_rootdir}/config_manager.h \
			 ${config_rootdir}/config_manager.cpp

noinst_LIBRARIES = libconfig.a

libconfig_a_SOURCES = ${CONFIG_SRC}

