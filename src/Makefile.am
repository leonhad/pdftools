SUBDIRS = nodes parser glyphs semantic zip xml html epub graphics tests

bin_PROGRAMS = pdftools

pdftools_SOURCES = \
	main.cpp \
	utils.cpp \
	analyze.cpp \
	pageanalyze.cpp \
	converter.cpp \
	generator.cpp \
	genericexception.cpp

dist_man_MANS = pdftools.1

noinst_HEADERS = \
	utils.h \
	analyze.h \
	pageanalyze.h \
	converter.h \
	generator.h \
	genericexception.h

pdftools_CXXFLAGS = -I.. -I.

pdftools_LDADD = \
	semantic/libsemantic.a \
	parser/libparser.a \
	epub/libepub.a \
	zip/libzip.a \
	html/libhtml.a \
	xml/libxml.a \
	glyphs/libglyphs.a \
	graphics/libgraphics.a \
	nodes/libnodes.a

MOSTLYCLEANFILES = \
	pdftools.1
