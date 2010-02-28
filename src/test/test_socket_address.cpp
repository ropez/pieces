#include "support.h"
#include <Pieces/SocketAddress>
#include <Pieces/BufferStream>

using pcs::InetAddress;
using pcs::SocketAddress;

class TestSocketAddress : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestSocketAddress);
    CPPUNIT_TEST(testDefault);
    CPPUNIT_TEST(testCreate);
    CPPUNIT_TEST(testIsNull);
    CPPUNIT_TEST(testModify);
    CPPUNIT_TEST(testCopy);
    CPPUNIT_TEST(testCompare);
    CPPUNIT_TEST(testDataStream);
    CPPUNIT_TEST_SUITE_END();

public:
    void testDefault() {
        SocketAddress sa;
        CPPUNIT_ASSERT(sa.getInetAddress().isNull());
        CPPUNIT_ASSERT_EQUAL(pcs::port_t(0), sa.getPort());
    }

    void testCreate() {
        SocketAddress sa(std::string("1.2.3.4"), 80);
        CPPUNIT_ASSERT_EQUAL(InetAddress("1.2.3.4"), sa.getInetAddress());
        CPPUNIT_ASSERT_EQUAL(pcs::port_t(80), sa.getPort());
    }

    void testIsNull() {
        SocketAddress sa;
        CPPUNIT_ASSERT(sa.isNull());
        sa.setInetAddress(InetAddress());
        CPPUNIT_ASSERT(sa.isNull());
        sa.setInetAddress(std::string("1.2.3.4"));
        CPPUNIT_ASSERT(!sa.isNull());
        sa.setInetAddress(InetAddress());
        CPPUNIT_ASSERT(sa.isNull());
        sa.setPort(80);
        CPPUNIT_ASSERT(!sa.isNull());
    }

    void testModify() {
        SocketAddress sa(std::string("1.2.3.4"), 80);
        sa.setInetAddress(std::string("4.3.2.1"));
        CPPUNIT_ASSERT_EQUAL(InetAddress("4.3.2.1"), sa.getInetAddress());
        CPPUNIT_ASSERT_EQUAL(pcs::port_t(80), sa.getPort());
        sa.setPort(8080);
        CPPUNIT_ASSERT_EQUAL(InetAddress("4.3.2.1"), sa.getInetAddress());
        CPPUNIT_ASSERT_EQUAL(pcs::port_t(8080), sa.getPort());
    }

    void testCopy() {
        SocketAddress sa1(std::string("1.2.3.4"), 80);
        SocketAddress sa2 = sa1;
        CPPUNIT_ASSERT_EQUAL(InetAddress("1.2.3.4"), sa2.getInetAddress());
        CPPUNIT_ASSERT_EQUAL(pcs::port_t(80), sa2.getPort());
        sa1.setPort(8080);
        sa2 = sa1;
        CPPUNIT_ASSERT_EQUAL(InetAddress("1.2.3.4"), sa2.getInetAddress());
        CPPUNIT_ASSERT_EQUAL(pcs::port_t(8080), sa2.getPort());
        sa2 = sa2;
        CPPUNIT_ASSERT_EQUAL(InetAddress("1.2.3.4"), sa2.getInetAddress());
        CPPUNIT_ASSERT_EQUAL(pcs::port_t(8080), sa2.getPort());
    }

    void testCompare() {
        SocketAddress sa(std::string("1.2.3.4"), 80);
        CPPUNIT_ASSERT(sa != SocketAddress());
        CPPUNIT_ASSERT(sa == SocketAddress(std::string("1.2.3.4"), 80));
        CPPUNIT_ASSERT(sa != SocketAddress(std::string("4.3.2.1"), 80));
        CPPUNIT_ASSERT(sa != SocketAddress(std::string("1.2.3.4"), 8080));
        CPPUNIT_ASSERT(sa != SocketAddress(std::string("4.3.2.1"), 8080));
        sa.setInetAddress(std::string("4.3.2.1"));
        CPPUNIT_ASSERT(sa != SocketAddress());
        CPPUNIT_ASSERT(sa != SocketAddress(std::string("1.2.3.4"), 80));
        CPPUNIT_ASSERT(sa == SocketAddress(std::string("4.3.2.1"), 80));
        CPPUNIT_ASSERT(sa != SocketAddress(std::string("1.2.3.4"), 8080));
        CPPUNIT_ASSERT(sa != SocketAddress(std::string("4.3.2.1"), 8080));
        sa.setPort(8080);
        CPPUNIT_ASSERT(sa != SocketAddress());
        CPPUNIT_ASSERT(sa != SocketAddress(std::string("1.2.3.4"), 80));
        CPPUNIT_ASSERT(sa != SocketAddress(std::string("4.3.2.1"), 80));
        CPPUNIT_ASSERT(sa != SocketAddress(std::string("1.2.3.4"), 8080));
        CPPUNIT_ASSERT(sa == SocketAddress(std::string("4.3.2.1"), 8080));
        sa.setInetAddress(InetAddress());
        sa.setPort(0);
        CPPUNIT_ASSERT(sa == SocketAddress());
    }

    void testDataStream() {
        pcs::BufferStream ds;
        ds << SocketAddress(std::string("1.2.3.4"), 80);
        ds << SocketAddress(std::string("4.3.2.1"), 8080);
        SocketAddress sa;
        ds >> sa;
        CPPUNIT_ASSERT_EQUAL(InetAddress("1.2.3.4"), sa.getInetAddress());
        CPPUNIT_ASSERT_EQUAL(pcs::port_t(80), sa.getPort());
        ds >> sa;
        CPPUNIT_ASSERT_EQUAL(InetAddress("4.3.2.1"), sa.getInetAddress());
        CPPUNIT_ASSERT_EQUAL(pcs::port_t(8080), sa.getPort());
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestSocketAddress);
