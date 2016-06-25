#include <iostream>

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

class ComplexNumberTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ComplexNumberTest);
    CPPUNIT_TEST(testEquality);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp()
    {

    }

    void tearDown()
    {
    }

protected:
    void testEquality()
    {
        CPPUNIT_ASSERT(1 == 1);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ComplexNumberTest);

int main(int argc, char **argv)
{
    // Create the event manager and test controller
    CPPUNIT_NS::TestResult controller;

    // Add a listener that collects test result
    CPPUNIT_NS::TestResultCollector result;
    controller.addListener(&result);

    // Add a listener that print dots as test run.
    CPPUNIT_NS::BriefTestProgressListener progress;
    controller.addListener(&progress);

    // Add the top suite to the test runner
    CPPUNIT_NS::TestRunner runner;
    runner.addTest( CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    runner.run(controller);

    std::ofstream xmlout("cppunit.xml");
    CPPUNIT_NS::XmlOutputter xmlOutputter(&result, xmlout);
    xmlOutputter.write();

    return result.wasSuccessful() ? 0 : 1;
}
