#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <Pieces/DataBuffer>
#include <Pieces/ByteArray>
#include <Pieces/IOException>

using pcs::ByteArray;
using pcs::DataBuffer;

class TestDataBuffer : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDataBuffer);
    CPPUNIT_TEST(testEmpty);
    CPPUNIT_TEST(testSingleWriteMultiRead);
    CPPUNIT_TEST(testMultiWriteSingleRead);
    CPPUNIT_TEST(testReadMoreThanAvailable);
    CPPUNIT_TEST_SUITE_END();

public:
    void testEmpty() {
        DataBuffer db;
        CPPUNIT_ASSERT_EQUAL(ByteArray(), db.data());
        CPPUNIT_ASSERT_THROW(db.read(3), pcs::Exception);
    }

    void testSingleWriteMultiRead() {
        DataBuffer db;
        CPPUNIT_ASSERT_NO_THROW(db.write(ByteArray("foobar", 6)));
        CPPUNIT_ASSERT_EQUAL(ByteArray("foo", 3), db.read(3));
        CPPUNIT_ASSERT_EQUAL(ByteArray("bar", 3), db.read(3));
        CPPUNIT_ASSERT_EQUAL(ByteArray("foobar", 6), db.data());
        CPPUNIT_ASSERT_THROW(db.read(3), pcs::Exception);
    }

    void testMultiWriteSingleRead() {
        DataBuffer db;
        CPPUNIT_ASSERT_NO_THROW(db.write(ByteArray("foo", 3)));
        CPPUNIT_ASSERT_NO_THROW(db.write(ByteArray("bar", 3)));
        CPPUNIT_ASSERT_EQUAL(ByteArray("foobar", 6), db.read(6));
        CPPUNIT_ASSERT_EQUAL(ByteArray("foobar", 6), db.data());
        CPPUNIT_ASSERT_THROW(db.read(3), pcs::Exception);
    }

    void testReadMoreThanAvailable() {
        const ByteArray ba("foo", 3);
        DataBuffer db;
        CPPUNIT_ASSERT_NO_THROW(db.write(ba));
        CPPUNIT_ASSERT_EQUAL(ba, db.read(6));
        CPPUNIT_ASSERT_THROW(db.read(3), pcs::Exception);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestDataBuffer);
