#ifndef ZIPFILETEST_H
#define ZIPFILETEST_H

#include <cppunit/extensions/HelperMacros.h>

class ZipTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ZipTest);
    CPPUNIT_TEST(testInstance);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testInstance();
};

#endif
