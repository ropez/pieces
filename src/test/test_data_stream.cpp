#include "support.h"
#include <Pieces/DataBuffer>
#include <Pieces/DataStream>
#include <Pieces/BufferStream>
#include <Pieces/Exception>
#include <Pieces/AutoPointer>
#include <Pieces/ValueList>
#include <Pieces/PropertyList>

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

class TestDataStreamManipulator : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDataStreamManipulator);
    CPPUNIT_TEST(testManipulator);
    CPPUNIT_TEST_SUITE_END();

    static int count;
    static DataStream& foo(DataStream& ds) {
        count++;
    }

public:
    void setUp() {
        count = 0;
    }

    void testManipulator() {
        DataStream ds;
        CPPUNIT_ASSERT_EQUAL(0, count);
        ds << foo;
        CPPUNIT_ASSERT_EQUAL(1, count);
        ds << foo << foo;
        CPPUNIT_ASSERT_EQUAL(3, count);
        ds >> foo;
        CPPUNIT_ASSERT_EQUAL(4, count);
        ds << foo >> foo;
        CPPUNIT_ASSERT_EQUAL(6, count);
    }
};
int TestDataStreamManipulator::count;
CPPUNIT_TEST_SUITE_REGISTRATION(TestDataStreamManipulator);

class TestDataStreamFlush : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDataStreamFlush);
    CPPUNIT_TEST(testNullTarget);
    CPPUNIT_TEST(testFlushTarget);
    CPPUNIT_TEST(testUsingManipulator);
    CPPUNIT_TEST_SUITE_END();

    class MockStreamTarget : public StreamTarget
    {
    public:
        class flushed {};

        ByteArray read(size_t) {
            throw;
        }

        void write(const ByteArray& data) {
            throw;
        }

        void flush() {
            throw flushed();
        }
    };

    pcs::AutoPointer<MockStreamTarget> t;

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
        CPPUNIT_ASSERT_THROW(ds.flush(), pcs::Exception);
    }

    void testFlushTarget() {
        DataStream ds(t.get());
        CPPUNIT_ASSERT_THROW(ds.flush(), MockStreamTarget::flushed);
    }

    void testUsingManipulator() {
        DataStream ds(t.get());
        CPPUNIT_ASSERT_THROW(ds << pcs::flush, MockStreamTarget::flushed);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestDataStreamFlush);

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

class TestDataStreamOnBuffer : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestDataStreamOnBuffer);
    CPPUNIT_TEST(testBool);
    CPPUNIT_TEST(testChar);
    CPPUNIT_TEST(testShort);
    CPPUNIT_TEST(testInt);
    CPPUNIT_TEST(testLong);
    CPPUNIT_TEST(testFloat);
    CPPUNIT_TEST(testDouble);
    CPPUNIT_TEST(testByteArray);
    CPPUNIT_TEST(testValueList);
    CPPUNIT_TEST(testPropertyList);
    CPPUNIT_TEST(testStdString);
    CPPUNIT_TEST(testCStringToStdString);
    CPPUNIT_TEST(testRandomTypes);
    CPPUNIT_TEST_SUITE_END();

    pcs::AutoPointer<DataBuffer> t;

    template<typename T>
    void write(DataStream& ds, const T& value) {
        ds << value;
    }

    template<typename T>
    void read(DataStream &ds, const T& expected) {
        T value;
        ds >> value;
        CPPUNIT_ASSERT_EQUAL(expected, value);
    }

    template<typename T, typename U, typename V>
    void test1(const T& v1, const U& v2, const V& v3) {
        DataStream ds(t.get());
        write(ds, v1);
        read(ds, v1);
        write(ds, v2);
        read(ds, v2);
        write(ds, v3);
        read(ds, v3);
    }


    template<typename T, typename U, typename V>
    void test2(const T& v1, const U& v2, const V& v3) {
        {
            DataStream ds(t.get());
            write(ds, v1);
            write(ds, v2);
            write(ds, v3);
        }
        {
            DataStream ds(t.get());
            read(ds, v1);
            read(ds, v2);
            read(ds, v3);
        }
    }

    template<typename T, typename U, typename V>
    void test(const T& v1, const U& v2, const V& v3) {
        test1(v1, v2, v3);
        test2(v1, v2, v3);
    }

public:
    void setUp() {
        t = new DataBuffer();
    }

    void tearDown() {
        // All bytes must be read
        CPPUNIT_ASSERT_THROW(t->read(1), pcs::Exception);
        t = 0;
    }

    void testBool() {
        test(true, false, true);
    }

    void testChar() {
        unsigned char uc = '\n';
        test('a', uc, '\0');
    }

    void testShort() {
        short v1 = 42, v2 = 0;
        unsigned short v3 = 0xffffu;
        test(v1, v2, v3);
    }

    void testInt() {
        test(42, 0xffffffffu, 0);
    }

    void testLong() {
        test(42l, ~0ul, 0l);
    }

    void testFloat() {
        test(3.14f, 3.14159f, 1e-8f);
    }

    void testDouble() {
        test(3.14, 3.14159, 1e-8);
    }

    void testByteArray() {
        ByteArray v1;
        ByteArray v2("foo", 3);
        ByteArray v3("foo\0bar\0", 8);
        test(v1, v2, v3);
    }

    void testValueList() {
        pcs::ValueList v1, v2, v3;
        v2.add(42).add(3.14).add(ByteArray("foo", 3));
        v3.add(v2);
        test(v1, v2, v3);
    }

    void testPropertyList() {
        pcs::PropertyList v1, v2, v3;
        v2.set(100, 42).set(200, 3.14).set(300, ByteArray("foo", 3));
        v3.set(1000, v2);
        test(v1, v2, v3);
    }

    void testStdString() {
        std::string v1 = "foo";
        std::string v2 = "";
        std::string v3 = "\tfoo\n\tbar\n";
        test(v1, v2, v3);
    }

    void testCStringToStdString() {
        DataStream ds(t.get());
        write(ds, "foo");
        write(ds, "");
        write(ds, "\tfoo\tbar\n");
        read(ds, std::string("foo"));
        read(ds, std::string(""));
        read(ds, std::string("\tfoo\tbar\n"));
    }

    void testRandomTypes() {
        test(42, ByteArray(), '\0');
        test(3.14, std::string("foo"), 0xffffffff);
        test(ByteArray("\n\0\n\0\n\0", 6), -1l, 'a');
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestDataStreamOnBuffer);
