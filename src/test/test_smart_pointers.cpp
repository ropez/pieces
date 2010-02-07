#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <Pieces/SharedData>
#include <Pieces/AutoPointer>
#include <Pieces/global>

using pcs::AutoPointer;

namespace {
class MockObject : public pcs::SharedData
{
public:
    static int count;

    MockObject() {
        count++;
    }

    ~MockObject() {
        count--;
    }

private:
    DISABLE_COPY(MockObject);
};
int MockObject::count = 0;
}

class TestSharedData : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestSharedData);
    CPPUNIT_TEST(testReferenceCount);
    CPPUNIT_TEST_SUITE_END();

public:
    void testReferenceCount() {
        MockObject o;
        o.ref();
        CPPUNIT_ASSERT(!o.shared());
        o.ref();
        CPPUNIT_ASSERT(o.shared());
        o.ref();
        CPPUNIT_ASSERT(o.shared());

        bool v;
        v = o.deref();
        CPPUNIT_ASSERT(o.shared());
        CPPUNIT_ASSERT(v);
        v = o.deref();
        CPPUNIT_ASSERT(!o.shared());
        CPPUNIT_ASSERT(v);
        v = o.deref();
        CPPUNIT_ASSERT(!o.shared());
        CPPUNIT_ASSERT(!v);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestSharedData);

class TestAutoPointer : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestAutoPointer);
    CPPUNIT_TEST(testNullPointer);
    CPPUNIT_TEST(testScopeCleanUp);
    CPPUNIT_TEST(testManualCleanUp);
    CPPUNIT_TEST(testOwnerChange);
    CPPUNIT_TEST(testSelfAssignment);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp() {
        MockObject::count = 0;
    }

    void tearDown() {
        CPPUNIT_ASSERT_EQUAL(0, MockObject::count);
    }

    void testNullPointer() {
        AutoPointer<MockObject> p;
        CPPUNIT_ASSERT(p.isNull());
        CPPUNIT_ASSERT(!p.isValid());
        CPPUNIT_ASSERT(!p);
        CPPUNIT_ASSERT(p.get() == 0);
    }

    void testScopeCleanUp() {
        AutoPointer<MockObject> p(new MockObject);
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
    }

    void testManualCleanUp() {
        AutoPointer<MockObject> p;
        CPPUNIT_ASSERT_EQUAL(0, MockObject::count);
        p = new MockObject;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        p = 0;
        CPPUNIT_ASSERT_EQUAL(0, MockObject::count);
    }

    void testOwnerChange() {
        AutoPointer<MockObject> p(new MockObject);
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        AutoPointer<MockObject> q = p;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT(q.isValid());
        CPPUNIT_ASSERT(p.isNull());
        p = q;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT(p.isValid());
        CPPUNIT_ASSERT(q.isNull());
    }

    void testSelfAssignment() {
        AutoPointer<MockObject> p(new MockObject);
        p = p;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT(p.isValid());
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestAutoPointer);
