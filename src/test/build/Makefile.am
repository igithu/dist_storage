
#SUBDIRS=src
#DIST_SUBDIRS=src


COMMON_CF = -I../../../third-64/crypto/include/

COMMON_LD = -lpthread -lz -ldl -lrt \
		    ../../../third-64/crypto/lib/*.a

bin_PROGRAMS = cryto_test
cryto_test_SOURCES = ../src/cryto_test.cpp \
			  ../../util/dist_hash.h \
			  ../../util/dist_hash.cpp \
			  ../../util/crytocpp.h \
			  ../../util/crytocpp.cpp

cryto_test_CPPFLAGS = $(COMMON_CF)
cryto_test_LDFLAGS = -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -fpermissive 
cryto_test_LDADD = $(COMMON_LD)


