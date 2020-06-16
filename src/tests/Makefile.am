bin_PROGRAMS = test

test_SOURCES = \
	../utils.cpp \
	../analyze.cpp \
	../pageanalyze.cpp \
	../converter.cpp \
	../generator.cpp \
	../genericexception.cpp \
	main.cpp

noinst_HEADERS = \
	littletest.h

test_CXXFLAGS = -I.. -I. -I../..

test_LDADD = \
	../semantic/libsemantic.a \
	../parser/libparser.a \
	../epub/libepub.a \
	../zip/libzip.a \
	../html/libhtml.a \
	../xml/libxml.a \
	../glyphs/libglyphs.a \
	../graphics/libgraphics.a \
	../nodes/libnodes.a
