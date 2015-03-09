top_dir = ${top_srcdir}/..
pb_rootdir = ${top_srcdir}/src/proto
third_dir = ${top_dir}/third-64

AM_CPPFLAGS = -I${third_dir}/protobuf/include/

AM_LDFLAGS = -lz -lrt

LDADD = ${third_dir}/protobuf/lib/*.a

include_HEADERS = ${pb_rootdir}/name_serv.pb.h \
				  ${pb_rootdir}/data_serv.pb.h

PB_SRC = ${include_HEADERS} \
		 ${pb_rootdir}/name_serv.pb.cc \
		 ${pb_rootdir}/data_serv.pb.cc


noinst_LIBRARIES = libproto.a

libproto_a_SOURCES = ${PB_SRC}

