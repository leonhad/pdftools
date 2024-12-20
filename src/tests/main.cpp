#include "littletest.h"

#include "../parser/pageparser.h"
#include "../nodes/nodes.h"
#include <fstream>

using namespace std;
using namespace parser;
using namespace node;

LT_BEGIN_SUITE(ParserSuite)
void set_up()
{
    //
}

void tear_down()
{
    //
}
LT_END_SUITE(ParserSuite)

LT_BEGIN_TEST(ParserSuite, Stream1)

ifstream filestream("stream1.txt", ios::binary);
PageParser parser(&filestream);
const auto root = parser.Parse();
LT_ASSERT(root);
filestream.close();
LT_END_TEST(Stream1)

LT_BEGIN_AUTO_TEST_ENV()
    AUTORUN_TESTS()
LT_END_AUTO_TEST_ENV()
