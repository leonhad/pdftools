check_LTLIBRARIES = libgtest.la
libgtest_la_SOURCES = ../googletest/googletest/src/gtest-all.cc
libgtest_la_CPPFLAGS = -I$(top_srcdir)/googletest/googletest/include -I$(top_srcdir)/googletest/googletest
libgtest_la_LDFLAGS = -pthread

# TESTS = gtest

check_PROGRAMS = gtest

gtest_SOURCES = gtest.cpp \
    ../src/utils.cpp \
    ../src/genericexception.cpp

gtest_LDADD = libgtest.la

gtest_LDFLAGS = -pthread \
    ../src/zip/libzip.a

gtest_CPPFLAGS = -I.. -I../src -I../src/zip \
    -I$(top_srcdir)/googletest/googletest/include -I$(top_srcdir)/googletest/googletest -pthread

