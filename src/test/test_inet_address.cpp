#include "support.h"
#include <Pieces/InetAddress>
#include <Pieces/Exception>

using pcs::InetAddress;

class TestInetAddress : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestInetAddress);
    CPPUNIT_TEST(testDefault);
    CPPUNIT_TEST(testParseAddress);
    CPPUNIT_TEST(testParseError);
    CPPUNIT_TEST(testFromBinary);
    CPPUNIT_TEST_SUITE_END();

    unsigned int ip4(unsigned int b1, unsigned int b2, unsigned int b3, unsigned int b4) {
        return b1 << 0 | b2 << 8 | b3 << 16 | b4 << 24;
    }

public:
    void testDefault() {
        InetAddress addr;
        CPPUNIT_ASSERT(addr.isNull());
        CPPUNIT_ASSERT_EQUAL(std::string("0.0.0.0"), addr.toString());
        CPPUNIT_ASSERT_EQUAL(ip4(0, 0, 0, 0), addr.toInt32());
    }

    void testParseAddress() {
        InetAddress addr1("1.2.3.4");
        CPPUNIT_ASSERT(!addr1.isNull());
        CPPUNIT_ASSERT_EQUAL(std::string("1.2.3.4"), addr1.toString());
        CPPUNIT_ASSERT_EQUAL(ip4(1, 2, 3, 4), addr1.toInt32());
        InetAddress addr2("1.0.0.127");
        CPPUNIT_ASSERT(!addr2.isNull());
        CPPUNIT_ASSERT_EQUAL(std::string("1.0.0.127"), addr2.toString());
        CPPUNIT_ASSERT_EQUAL(ip4(1, 0, 0, 127), addr2.toInt32());
        InetAddress addr3("255.255.255.255");
        CPPUNIT_ASSERT(!addr3.isNull());
        CPPUNIT_ASSERT_EQUAL(std::string("255.255.255.255"), addr3.toString());
        CPPUNIT_ASSERT_EQUAL(ip4(255, 255, 255, 255), addr3.toInt32());
    }

    void testParseError() {
        CPPUNIT_ASSERT_THROW(InetAddress(""), pcs::Exception);
        CPPUNIT_ASSERT_THROW(InetAddress("foobar"), pcs::Exception);
        CPPUNIT_ASSERT_THROW(InetAddress("1.2.3.4.5"), pcs::Exception);
        CPPUNIT_ASSERT_THROW(InetAddress("300.100.100.100"), pcs::Exception);
    }

    void testFromBinary() {
        InetAddress addr1(ip4(1, 2, 3, 4));
        CPPUNIT_ASSERT_EQUAL(std::string("1.2.3.4"), addr1.toString());
        InetAddress addr2(ip4(1, 0, 0, 127));
        CPPUNIT_ASSERT_EQUAL(std::string("1.0.0.127"), addr2.toString());
        InetAddress addr3(ip4(255, 255, 255, 255));
        CPPUNIT_ASSERT_EQUAL(std::string("255.255.255.255"), addr3.toString());
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestInetAddress);
