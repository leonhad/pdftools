SUBDIRS = nodes parser glyphs semantic zip xml html epub graphics

bin_PROGRAMS = pdftools
pdftools_SOURCES = main.cpp \
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

pdftools_CXXFLAGS = 

pdftools_LDADD = \
	semantic/libsemantic.a \
	parser/libparser.a \
	epub/libepub.a \
	zip/libzip.a \
	html/libhtml.a \
	xml/libxml.a \
	glyphs/libglyphs.a \
	graphics/libgraphics.a \
	nodes/libnodes.a \
	$(XML_LIBS) -liconv

if HELP2MAN
pdftools.1: pdftools$(EXEEXT) pdftools.h2m
	@echo generating help file $@...
	@$(HELP2MAN) --output=$@ -N -i pdftools.h2m ./pdftools$(EXEEXT)
endif

