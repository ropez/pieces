#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <Pieces/SharedData>
#include <Pieces/AutoPointer>
#include <Pieces/ReferencePointer>
#include <Pieces/SharedDataPointer>
#include <Pieces/global>

using pcs::AutoPointer;
using pcs::ReferencePointer;
using pcs::SharedDataPointer;

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

class MockData : public MockObject
{
public:
    MockData() : MockObject() {}
    MockData(const MockData& other) : MockObject() {}

    void foo() {}
};
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
        p = new MockObject;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        p = 0;
        CPPUNIT_ASSERT_EQUAL(0, MockObject::count);
    }

    void testOwnerChange() {
        AutoPointer<MockObject> p(new MockObject);
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        AutoPointer<MockObject> q(new MockObject);
        CPPUNIT_ASSERT_EQUAL(2, MockObject::count);
        MockObject* pp = p.get();
        q = p;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT_EQUAL(pp, q.get());
        CPPUNIT_ASSERT(p.isNull());
        p = q;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT_EQUAL(pp, p.get());
        CPPUNIT_ASSERT(q.isNull());
    }

    void testSelfAssignment() {
        AutoPointer<MockObject> p(new MockObject);
        MockObject* pp = p.get();
        p = p;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT_EQUAL(pp, p.get());
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestAutoPointer);

class TestReferencePointer : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestReferencePointer);
    CPPUNIT_TEST(testNullPointer);
    CPPUNIT_TEST(testScopeCleanUp);
    CPPUNIT_TEST(testManualCleanUp);
    CPPUNIT_TEST(testMultipleReferences);
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
        ReferencePointer<MockObject> p;
        CPPUNIT_ASSERT(p.isNull());
        CPPUNIT_ASSERT(!p.isValid());
        CPPUNIT_ASSERT(!p);
        CPPUNIT_ASSERT(p.get() == 0);
    }

    void testScopeCleanUp() {
        ReferencePointer<MockObject> p(new MockObject);
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
    }

    void testManualCleanUp() {
        ReferencePointer<MockObject> p;
        CPPUNIT_ASSERT_EQUAL(0, MockObject::count);
        p = new MockObject;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        p = new MockObject;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        p = 0;
        CPPUNIT_ASSERT_EQUAL(0, MockObject::count);
    }

    void testMultipleReferences() {
        ReferencePointer<MockObject> p(new MockObject);
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        ReferencePointer<MockObject> q(new MockObject);
        CPPUNIT_ASSERT_EQUAL(2, MockObject::count);
        MockObject* pp = p.get();
        q = p;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT_EQUAL(pp, q.get());
        CPPUNIT_ASSERT_EQUAL(pp, p.get());
        CPPUNIT_ASSERT(p->shared());
        p = q;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT_EQUAL(pp, q.get());
        CPPUNIT_ASSERT_EQUAL(pp, p.get());
        CPPUNIT_ASSERT(p->shared());
    }

    void testSelfAssignment() {
        ReferencePointer<MockObject> p(new MockObject);
        MockObject* pp = p.get();
        p = p;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT_EQUAL(pp, p.get());
        CPPUNIT_ASSERT(!p->shared());
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestReferencePointer);

class TestSharedDataPointer : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestSharedDataPointer);
    CPPUNIT_TEST(testNullPointer);
    CPPUNIT_TEST(testScopeCleanUp);
    CPPUNIT_TEST(testManualCleanUp);
    CPPUNIT_TEST(testMultipleReferences);
    CPPUNIT_TEST(testAutomaticDetach);
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
        SharedDataPointer<MockData> p;
        CPPUNIT_ASSERT(p.const_data() == 0);
    }

    void testScopeCleanUp() {
        SharedDataPointer<MockData> p(new MockData);
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
    }

    void testManualCleanUp() {
        SharedDataPointer<MockData> p;
        CPPUNIT_ASSERT_EQUAL(0, MockObject::count);
        p = new MockData;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        p = new MockData;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        p = 0;
        CPPUNIT_ASSERT_EQUAL(0, MockObject::count);
    }

    void testMultipleReferences() {
        SharedDataPointer<MockData> p(new MockData);
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        SharedDataPointer<MockData> q(new MockData);
        CPPUNIT_ASSERT_EQUAL(2, MockObject::count);
        const MockData* pp = p.const_data();
        q = p;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT_EQUAL(pp, q.const_data());
        CPPUNIT_ASSERT_EQUAL(pp, p.const_data());
        CPPUNIT_ASSERT_EQUAL(q.const_data(), p.const_data());
        CPPUNIT_ASSERT(p.const_data()->shared());
        p = q;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT_EQUAL(pp, q.const_data());
        CPPUNIT_ASSERT_EQUAL(pp, p.const_data());
        CPPUNIT_ASSERT_EQUAL(q.const_data(), p.const_data());
    }

    void testAutomaticDetach() {
        SharedDataPointer<MockData> p(new MockData);
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        SharedDataPointer<MockData> q(new MockData);
        CPPUNIT_ASSERT_EQUAL(2, MockObject::count);
        q = p;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT_EQUAL(q.const_data(), p.const_data());
        CPPUNIT_ASSERT(p.const_data()->shared());

        p->foo(); // access data directly, causing detach

        CPPUNIT_ASSERT_EQUAL(2, MockObject::count);
        CPPUNIT_ASSERT(q.const_data() != p.const_data());
        CPPUNIT_ASSERT(!p.const_data()->shared());
        CPPUNIT_ASSERT(!q.const_data()->shared());
    }

    void testSelfAssignment() {
        SharedDataPointer<MockData> p(new MockData);
        p = p;
        CPPUNIT_ASSERT_EQUAL(1, MockObject::count);
        CPPUNIT_ASSERT(p.const_data() != 0);
        CPPUNIT_ASSERT(!p.const_data()->shared());
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestSharedDataPointer);

