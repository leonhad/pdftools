#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

class ComplexNumberTest: public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( ComplexNumberTest );

	CPPUNIT_TEST(testEquality);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp() {

	}

	void tearDown() {
	}

	void testEquality() {
		CPPUNIT_ASSERT(1 == 1);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ComplexNumberTest);

int main(int argc, char **argv) {
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry =
			CppUnit::TestFactoryRegistry::getRegistry();

	runner.addTest(registry.makeTest());

	runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
	                                                       std::cerr ) );

	runner.run();
	bool wasSuccessful = runner.run("", false);
	return !wasSuccessful;
}
