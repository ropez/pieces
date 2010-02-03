#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <Pieces/Message>

using pcs::Message;

class TestMessageType : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestMessageType);
    CPPUNIT_TEST(testDefaultMessageType);
    CPPUNIT_TEST(testCreateMessageType);
    CPPUNIT_TEST(testModifyMessageType);
    CPPUNIT_TEST(testCopyMessageType);
    CPPUNIT_TEST(testAssignMessageType);
    CPPUNIT_TEST_SUITE_END();

    enum {
        TYPE_FOO = 1000,
        TYPE_BAR = 2000,
    };

public:
    void testDefaultMessageType() {
        Message msg;
        CPPUNIT_ASSERT(msg.getMessageType() == pcs::NO_MESSAGE_TYPE);
    }

    void testCreateMessageType() {
        Message msg(TYPE_FOO);
        CPPUNIT_ASSERT(msg.getMessageType() == TYPE_FOO);
    }

    void testModifyMessageType() {
        Message msg;

        msg.setMessageType(TYPE_FOO);
        CPPUNIT_ASSERT(msg.getMessageType() == TYPE_FOO);

        msg.setMessageType(TYPE_BAR);
        CPPUNIT_ASSERT(msg.getMessageType() == TYPE_BAR);
    }

    void testCopyMessageType() {
        Message msg;
        Message foo(TYPE_FOO);
        Message bar(TYPE_BAR);

        Message msgX(msg);
        Message fooX(foo);
        Message barX(bar);
        CPPUNIT_ASSERT(msgX.getMessageType() == pcs::NO_MESSAGE_TYPE);
        CPPUNIT_ASSERT(fooX.getMessageType() == TYPE_FOO);
        CPPUNIT_ASSERT(barX.getMessageType() == TYPE_BAR);
    }

    void testAssignMessageType() {
        Message foo(TYPE_FOO);
        Message bar(TYPE_BAR);
        Message msg;
        CPPUNIT_ASSERT(msg.getMessageType() == pcs::NO_MESSAGE_TYPE);

        msg = foo;
        CPPUNIT_ASSERT(msg.getMessageType() == TYPE_FOO);

        msg = bar;
        CPPUNIT_ASSERT(msg.getMessageType() == TYPE_BAR);

        msg = foo = bar = Message();
        CPPUNIT_ASSERT(msg.getMessageType() == pcs::NO_MESSAGE_TYPE);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestMessageType);

class TestMessageFlags : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestMessageFlags);
    CPPUNIT_TEST(testDefaultMessageFlags);
    CPPUNIT_TEST(testCreateMessageFlags);
    CPPUNIT_TEST(testModifyMessageFlags);
    CPPUNIT_TEST(testCopyMessageFlags);
    CPPUNIT_TEST(testAssignMessageFlags);
    CPPUNIT_TEST_SUITE_END();

    enum {
        FL_FOO = 0x0100,
        FL_BAR = 0x0200,
    };

    bool hasFlag(Message msg, pcs::flags_t fl) {
        return !!(msg.getFlags() & fl);
    }

    bool hasNotFlag(Message msg, pcs::flags_t fl) {
        return !hasFlag(msg, fl);
    }

public:
    void testDefaultMessageFlags() {
        Message msg;
        CPPUNIT_ASSERT(hasNotFlag(msg, FL_FOO));
        CPPUNIT_ASSERT(hasNotFlag(msg, FL_BAR));
    }

    void testCreateMessageFlags() {
        Message foo(pcs::NO_MESSAGE_TYPE, FL_FOO);
        Message bar(pcs::NO_MESSAGE_TYPE, FL_BAR);
        Message foobar(pcs::NO_MESSAGE_TYPE, FL_FOO | FL_BAR);

        CPPUNIT_ASSERT(hasFlag(foo, FL_FOO));
        CPPUNIT_ASSERT(hasNotFlag(foo, FL_BAR));
        CPPUNIT_ASSERT(hasNotFlag(bar, FL_FOO));
        CPPUNIT_ASSERT(hasFlag(bar, FL_BAR));
        CPPUNIT_ASSERT(hasFlag(foobar, FL_FOO));
        CPPUNIT_ASSERT(hasFlag(foobar, FL_BAR));
    }

    void testModifyMessageFlags() {
        Message foobar;
        CPPUNIT_ASSERT(hasNotFlag(foobar, FL_FOO));
        CPPUNIT_ASSERT(hasNotFlag(foobar, FL_BAR));

        foobar.setFlags(FL_FOO);
        CPPUNIT_ASSERT(hasFlag(foobar, FL_FOO));
        CPPUNIT_ASSERT(hasNotFlag(foobar, FL_BAR));

        foobar.setFlags(FL_BAR);
        CPPUNIT_ASSERT(hasNotFlag(foobar, FL_FOO));
        CPPUNIT_ASSERT(hasFlag(foobar, FL_BAR));


        foobar.setFlags(FL_FOO | FL_BAR);
        CPPUNIT_ASSERT(hasFlag(foobar, FL_FOO));
        CPPUNIT_ASSERT(hasFlag(foobar, FL_BAR));
    }

    void testCopyMessageFlags() {
        Message msg(pcs::NO_MESSAGE_TYPE);
        Message foo(pcs::NO_MESSAGE_TYPE, FL_FOO);
        Message bar(pcs::NO_MESSAGE_TYPE, FL_BAR);

        Message msgX(msg);
        Message fooX(foo);
        Message barX(bar);
        CPPUNIT_ASSERT(hasNotFlag(msgX, FL_FOO));
        CPPUNIT_ASSERT(hasNotFlag(msgX, FL_BAR));
        CPPUNIT_ASSERT(hasFlag(fooX, FL_FOO));
        CPPUNIT_ASSERT(hasNotFlag(fooX, FL_BAR));
        CPPUNIT_ASSERT(hasNotFlag(barX, FL_FOO));
        CPPUNIT_ASSERT(hasFlag(barX, FL_BAR));
    }

    void testAssignMessageFlags() {
        Message msg(pcs::NO_MESSAGE_TYPE);
        Message foo(pcs::NO_MESSAGE_TYPE, FL_FOO);
        Message bar(pcs::NO_MESSAGE_TYPE, FL_BAR);

        CPPUNIT_ASSERT(hasNotFlag(msg, FL_FOO));
        CPPUNIT_ASSERT(hasNotFlag(msg, FL_BAR));

        msg = foo;
        CPPUNIT_ASSERT(hasFlag(msg, FL_FOO));
        CPPUNIT_ASSERT(hasNotFlag(msg, FL_BAR));

        msg = bar;
        CPPUNIT_ASSERT(hasNotFlag(msg, FL_FOO));
        CPPUNIT_ASSERT(hasFlag(msg, FL_BAR));

        msg = foo = bar = Message();
        CPPUNIT_ASSERT(hasNotFlag(msg, FL_FOO));
        CPPUNIT_ASSERT(hasNotFlag(msg, FL_BAR));
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestMessageFlags);
