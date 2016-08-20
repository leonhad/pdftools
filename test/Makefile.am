SUBDIRS = zip

TESTS = testsuit
check_PROGRAMS = $(TESTS)

testsuit_CXXFLAGS = $(CPPUNIT_CFLAGS) -I../src

testsuit_LDFLAGS = $(CPPUNIT_LIBS) -ldl \
	../src/semantic/libsemantic.a \
	../src/parser/libparser.a \
	../src/epub/libepub.a \
	../src/zip/libzip.a \
	../src/html/libhtml.a \
	../src/xml/libxml.a \
	../src/glyphs/libglyphs.a \
	../src/graphics/libgraphics.a \
	../src/nodes/libnodes.a \
	zip/libziptest.a


testsuit_SOURCES = \
	main.cpp \
	../src/utils.cpp \
	../src/analyze.cpp \
	../src/pageanalyze.cpp \
	../src/converter.cpp \
	../src/generator.cpp \
	../src/genericexception.cpp

bin_PROGRAMS = testsuit

MOSTLYCLEANFILES = \
	*.gcda *.gcno *.gcov
