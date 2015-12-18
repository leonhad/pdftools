TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lz -liconv

SOURCES += main.cpp \
    analyze.cpp \
    cmapparser.cpp \
    converter.cpp \
    generator.cpp \
    genericparser.cpp \
    pageanalyze.cpp \
    pageparser.cpp \
    parser.cpp \
    scanner.cpp \
    token.cpp \
    utils.cpp \
    epub/epub.cpp \
    glyphs/breakglyph.cpp \
    glyphs/fontglyph.cpp \
    glyphs/fontsizeglyph.cpp \
    glyphs/glyph.cpp \
    glyphs/paragraphglyph.cpp \
    glyphs/textglyph.cpp \
    graphics/graphicstate.cpp \
    graphics/state.cpp \
    html/html.cpp \
    nodes/arraynode.cpp \
    nodes/bdcnode.cpp \
    nodes/booleannode.cpp \
    nodes/breaknode.cpp \
    nodes/charnode.cpp \
    nodes/cmapnode.cpp \
    nodes/codespacenode.cpp \
    nodes/fontnode.cpp \
    nodes/mapnode.cpp \
    nodes/namenode.cpp \
    nodes/numbernode.cpp \
    nodes/objnode.cpp \
    nodes/refnode.cpp \
    nodes/rootnode.cpp \
    nodes/statenode.cpp \
    nodes/stringnode.cpp \
    nodes/textmatrixnode.cpp \
    nodes/textnode.cpp \
    nodes/treenode.cpp \
    nodes/xrefnode.cpp \
    semantic/context.cpp \
    semantic/document.cpp \
    semantic/font.cpp \
    semantic/outline.cpp \
    semantic/page.cpp \
    semantic/pagelabel.cpp \
    xml/xml.cpp \
    zip/zipfile.cpp

HEADERS += \
    analyze.h \
    cmapparser.h \
    converter.h \
    generator.h \
    genericparser.h \
    pageanalyze.h \
    pageparser.h \
    parser.h \
    scanner.h \
    token.h \
    utils.h \
    epub/epub.h \
    glyphs/breakglyph.h \
    glyphs/fontglyph.h \
    glyphs/fontsizeglyph.h \
    glyphs/glyph.h \
    glyphs/glyphs.h \
    glyphs/paragraphglyph.h \
    glyphs/textglyph.h \
    graphics/graphicstate.h \
    graphics/state.h \
    html/html.h \
    nodes/arraynode.h \
    nodes/bdcnode.h \
    nodes/booleannode.h \
    nodes/breaknode.h \
    nodes/charnode.h \
    nodes/cmapnode.h \
    nodes/codespacenode.h \
    nodes/fontnode.h \
    nodes/mapnode.h \
    nodes/namenode.h \
    nodes/nodes.h \
    nodes/numbernode.h \
    nodes/objnode.h \
    nodes/refnode.h \
    nodes/rootnode.h \
    nodes/statenode.h \
    nodes/stringnode.h \
    nodes/textmatrixnode.h \
    nodes/textnode.h \
    nodes/treenode.h \
    nodes/xrefnode.h \
    semantic/context.h \
    semantic/document.h \
    semantic/font.h \
    semantic/outline.h \
    semantic/page.h \
    semantic/pagelabel.h \
    xml/xml.h \
    zip/zipfile.h
