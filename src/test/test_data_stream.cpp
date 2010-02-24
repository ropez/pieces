#include "support.h"
#include <Pieces/DataBuffer>
#include <Pieces/DataStream>
#include <Pieces/BufferStream>
#include <Pieces/Exception>
#include <Pieces/AutoPointer>

using pcs::ByteArray;
using pcs::DataBuffer;
using pcs::DataStream;
using pcs::BufferStream;
using pcs::StreamTarget;

class TestDataStreamTarget : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDataStreamTarget);
    CPPUNIT_TEST(testNullTarget);
    CPPUNIT_TEST(testCreateTarget);
    CPPUNIT_TEST(testRemoveTarget);
    CPPUNIT_TEST(testSetTarget);
    CPPUNIT_TEST_SUITE_END();

    class MockStreamTarget : public StreamTarget
    {
        ByteArray data;
    public:
        ByteArray read(size_t maxSize) {
            return data.left(maxSize);
        }

        void write(const ByteArray& data) {
            this->data = data;
        }

        void flush() {}
    };

    pcs::AutoPointer<StreamTarget> t;

public:
    void setUp() {
        t = new MockStreamTarget();
    }

    void tearDown() {
        t = 0;
    }

    void testNullTarget() {
        DataStream ds;
        CPPUNIT_ASSERT(ds.target() == 0);
        int i = 42;
        CPPUNIT_ASSERT_THROW(ds << i, pcs::Exception);
        CPPUNIT_ASSERT_THROW(ds >> i, pcs::Exception);
        CPPUNIT_ASSERT_EQUAL(42, i);
    }

    void testCreateTarget() {
        DataStream ds(t.get());
        CPPUNIT_ASSERT(ds.target() != 0);
        int i = 42;
        CPPUNIT_ASSERT_NO_THROW(ds << i);
        CPPUNIT_ASSERT_NO_THROW(ds >> i);
        CPPUNIT_ASSERT_EQUAL(42, i);
    }

    void testRemoveTarget() {
        DataStream ds(t.get());
        CPPUNIT_ASSERT_NO_THROW(ds << 42);
        ds.setTarget(0);
        int i = 42;
        CPPUNIT_ASSERT_THROW(ds << i, pcs::Exception);
        CPPUNIT_ASSERT_THROW(ds >> i, pcs::Exception);
        CPPUNIT_ASSERT_EQUAL(42, i);
    }

    void testSetTarget() {
        DataStream ds;
        CPPUNIT_ASSERT(ds.target() == 0);
        int i = 42;
        CPPUNIT_ASSERT_THROW(ds << i, pcs::Exception);
        CPPUNIT_ASSERT_THROW(ds >> i, pcs::Exception);
        CPPUNIT_ASSERT_EQUAL(42, i);
        ds.setTarget(t.get());
        CPPUNIT_ASSERT(ds.target() != 0);
        CPPUNIT_ASSERT_NO_THROW(ds << i);
        CPPUNIT_ASSERT_NO_THROW(ds >> i);
        CPPUNIT_ASSERT_EQUAL(42, i);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestDataStreamTarget);

class TestDataStreamWriteBytes : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDataStreamWriteBytes);
    CPPUNIT_TEST(testWriteBytes);
    CPPUNIT_TEST_SUITE_END();

    class MockStreamTarget : public StreamTarget
    {
    public:
        ByteArray read(size_t) {
            throw;
        }

        void write(const ByteArray& data) {
            CPPUNIT_ASSERT_EQUAL(ByteArray("foobar", 6), data);
        }

        void flush() {}
    };

    pcs::AutoPointer<StreamTarget> t;

public:
    void setUp() {
        t = new MockStreamTarget;
    }

    void tearDown() {
        t = 0;
    }

    void testWriteBytes() {
        DataStream ds(t.get());
        ds.writeBytes(ByteArray("foobar", 6));
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestDataStreamWriteBytes);

class TestDataStreamReadBytes : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDataStreamReadBytes);
    CPPUNIT_TEST(testReadBytes);
    CPPUNIT_TEST_SUITE_END();

    class MockStreamTarget : public StreamTarget
    {
    public:
        ByteArray read(size_t maxSize) {
            return ByteArray("foobar", maxSize > 6 ? 6 : maxSize);
        }

        void write(const ByteArray& data) {
            throw;
        }

        void flush() {}
    };

    pcs::AutoPointer<StreamTarget> t;

public:
    void setUp() {
        t = new MockStreamTarget;
    }

    void tearDown() {
        t = 0;
    }

    void testReadBytes() {
        DataStream ds(t.get());
        CPPUNIT_ASSERT_EQUAL(ByteArray(), ds.readBytes(0));
        CPPUNIT_ASSERT_EQUAL(ByteArray("foo", 3), ds.readBytes(3));
        CPPUNIT_ASSERT_EQUAL(ByteArray("foobar", 6), ds.readBytes(6));
        CPPUNIT_ASSERT_EQUAL(ByteArray("foobarfoo", 9), ds.readBytes(9));
        CPPUNIT_ASSERT_EQUAL(ByteArray("foobarfoobar", 12), ds.readBytes(12));
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestDataStreamReadBytes);
