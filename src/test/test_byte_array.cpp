#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <Pieces/ByteArray>
#include <cstring>
#include <iomanip>

using pcs::ByteArray;

namespace CppUnit {
template<>
struct assertion_traits<ByteArray>
{
    static bool equal(const ByteArray& x, const ByteArray& y)
    {
        if (x.size() != y.size())
            return false;
        if (std::memcmp(x.constData(), y.constData(), x.size()))
            return false;
        else
            return true;
    }

    static std::string toString(const ByteArray& x)
    {
        std::stringstream hex, asc;
        hex << std::setfill('0');
        for (int i = 0; i < x.size(); i++) {
            hex << std::setw(2) << std::hex << int(x[i]) << ' ';
            if (std::isalnum(x[i]))
                asc << x[i];
            else
                asc << '.';
        }
        std::stringstream ss;
        ss << hex.str() << "|" << asc.str() << "|";
        return ss.str();
    }
};
}


class TestByteArray : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestByteArray);
    CPPUNIT_TEST(testEmpty);
    CPPUNIT_TEST(testByteArray);
    CPPUNIT_TEST(testNullBytes);
    CPPUNIT_TEST(testRandomAccess);
    CPPUNIT_TEST(testImplicitSharing);
    CPPUNIT_TEST_SUITE_END();

public:
    void testEmpty() {
        ByteArray ba;
        CPPUNIT_ASSERT(ba.isEmpty());
        CPPUNIT_ASSERT_EQUAL(0ul, ba.size());
        CPPUNIT_ASSERT_EQUAL(0ul, ba.allocated());

        CPPUNIT_ASSERT_NO_THROW(ba.clear());
        CPPUNIT_ASSERT(ba.isEmpty());

        ByteArray b2(0);
        CPPUNIT_ASSERT(b2.isEmpty());
        CPPUNIT_ASSERT_EQUAL(ba, b2);

        ByteArray b3("", 0);
        CPPUNIT_ASSERT(b3.isEmpty());
        CPPUNIT_ASSERT_EQUAL(ba, b3);
    }

    void testByteArray() {
        ByteArray ba("hello", 5ul);
        CPPUNIT_ASSERT(!ba.isEmpty());
        CPPUNIT_ASSERT_EQUAL(5ul, ba.size());
        CPPUNIT_ASSERT(std::memcmp("hello", ba.constData(), ba.size()) == 0);

        ba.clear();
        CPPUNIT_ASSERT(ba.isEmpty());
        CPPUNIT_ASSERT_EQUAL(0ul, ba.size());
    }

    void testRandomAccess() {
        const ByteArray ba("foo", 3);

        CPPUNIT_ASSERT(ba[0] == 'f');
        CPPUNIT_ASSERT(ba[1] == 'o');
        CPPUNIT_ASSERT(ba[2] == 'o');

        ByteArray b2(ba);
        ByteArray b3(ba);

        CPPUNIT_ASSERT_EQUAL(ba, b2);
        CPPUNIT_ASSERT_EQUAL(ba, b3);

        b2[0] = 'l';
        b2[2] = 'l';
        CPPUNIT_ASSERT_EQUAL(ByteArray("lol", 3), b2);
        CPPUNIT_ASSERT_EQUAL(ba, b3);

        b3.clear();
        CPPUNIT_ASSERT_EQUAL(ByteArray("foo", 3), ba);
    }

    void testNullBytes() {
        ByteArray ba("foobar", 6ul);
        CPPUNIT_ASSERT_EQUAL(6ul, ba.size());

        ba[0] = ba[3] = '\0';
        CPPUNIT_ASSERT(!ba.isEmpty());
        CPPUNIT_ASSERT_EQUAL(6ul, ba.size());
        CPPUNIT_ASSERT(ba[0] == '\0');
        CPPUNIT_ASSERT(ba[4] == 'a');
        CPPUNIT_ASSERT(ba[5] == 'r');

        ByteArray b2 = ba;
        CPPUNIT_ASSERT_EQUAL(6ul, b2.size());
        CPPUNIT_ASSERT_EQUAL(ba, b2);
    }

    void testImplicitSharing() {
        const ByteArray ba("Pieces", 6);

        // Create non-const copies
        ByteArray b2 = ba;
        ByteArray b3 = ba;

        // constData() should not trigger detach
        CPPUNIT_ASSERT(b2.constData() == b3.constData());

        // data() triggers detach on non-const objects
        CPPUNIT_ASSERT(b2.data() != b3.data());

        // after detachment, constData() returns a different value
        CPPUNIT_ASSERT(b2.constData() != b3.constData());

        // Create a const copy
        const ByteArray b4 = ba;

        // data() does not trigger detach on const objects
        CPPUNIT_ASSERT(ba.data() == b4.data());

        // b2 and b3 is already detached
        CPPUNIT_ASSERT(b2.data() != b4.data());
        CPPUNIT_ASSERT(b3.data() != b4.data());
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestByteArray);

class TestByteArraySlicing : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestByteArraySlicing);
    CPPUNIT_TEST(testLeft);
    CPPUNIT_TEST(testRight);
    CPPUNIT_TEST(testMiddle);
    CPPUNIT_TEST_SUITE_END();

public:
    void testLeft() {
        ByteArray ba("foobar", 6);

        CPPUNIT_ASSERT_EQUAL(ByteArray(), ba.left(0));
        CPPUNIT_ASSERT_EQUAL(ba, ba.left(6));
        CPPUNIT_ASSERT_EQUAL(ba, ba.left(99));

        CPPUNIT_ASSERT_EQUAL(ByteArray("f", 1), ba.left(1));
        CPPUNIT_ASSERT_EQUAL(ByteArray("fo", 2), ba.left(2));
        CPPUNIT_ASSERT_EQUAL(ByteArray("foo", 3), ba.left(3));
    }

    void testRight() {
        ByteArray ba("foobar", 6);

        CPPUNIT_ASSERT_EQUAL(ByteArray(), ba.right(0));
        CPPUNIT_ASSERT_EQUAL(ba, ba.right(6));
        // CPPUNIT_ASSERT_EQUAL(ba, ba.right(99));

        CPPUNIT_ASSERT_EQUAL(ByteArray(  "r", 1), ba.right(1));
        CPPUNIT_ASSERT_EQUAL(ByteArray( "ar", 2), ba.right(2));
        CPPUNIT_ASSERT_EQUAL(ByteArray("bar", 3), ba.right(3));
    }

    void testMiddle() {
        ByteArray ba("foobar", 6);

        CPPUNIT_ASSERT_EQUAL(ByteArray(), ba.middle(0, 0));
        CPPUNIT_ASSERT_EQUAL(ByteArray(), ba.middle(3, 0));
        CPPUNIT_ASSERT_EQUAL(ByteArray(), ba.middle(6, 0));
        CPPUNIT_ASSERT_EQUAL(ByteArray(), ba.middle(6, 99));
        CPPUNIT_ASSERT_EQUAL(ByteArray(), ba.middle(6));
        CPPUNIT_ASSERT_EQUAL(ba, ba.middle(0, 6));
        CPPUNIT_ASSERT_EQUAL(ba, ba.middle(0, 99));
        CPPUNIT_ASSERT_EQUAL(ba, ba.middle(0));

        CPPUNIT_ASSERT_EQUAL(ByteArray("f", 1), ba.middle(0, 1));
        CPPUNIT_ASSERT_EQUAL(ByteArray("o", 1), ba.middle(1, 1));
        CPPUNIT_ASSERT_EQUAL(ByteArray("o", 1), ba.middle(2, 1));
        CPPUNIT_ASSERT_EQUAL(ByteArray("b", 1), ba.middle(3, 1));
        CPPUNIT_ASSERT_EQUAL(ByteArray("a", 1), ba.middle(4, 1));
        CPPUNIT_ASSERT_EQUAL(ByteArray("r", 1), ba.middle(5, 1));
        CPPUNIT_ASSERT_EQUAL(ByteArray("fo", 2), ba.middle(0, 2));
        CPPUNIT_ASSERT_EQUAL(ByteArray("oo", 2), ba.middle(1, 2));
        CPPUNIT_ASSERT_EQUAL(ByteArray("ob", 2), ba.middle(2, 2));
        CPPUNIT_ASSERT_EQUAL(ByteArray("ba", 2), ba.middle(3, 2));
        CPPUNIT_ASSERT_EQUAL(ByteArray("ar", 2), ba.middle(4, 2));
        CPPUNIT_ASSERT_EQUAL(ByteArray( "r", 1), ba.middle(5, 2));
        CPPUNIT_ASSERT_EQUAL(ByteArray("foob", 4), ba.middle(0, 4));
        CPPUNIT_ASSERT_EQUAL(ByteArray("ooba", 4), ba.middle(1, 4));
        CPPUNIT_ASSERT_EQUAL(ByteArray("obar", 4), ba.middle(2, 4));
        CPPUNIT_ASSERT_EQUAL(ByteArray( "bar", 3), ba.middle(3, 4));
        CPPUNIT_ASSERT_EQUAL(ByteArray(  "ar", 2), ba.middle(4, 4));
        CPPUNIT_ASSERT_EQUAL(ByteArray(   "r", 1), ba.middle(5, 4));
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestByteArraySlicing);

class TestByteArrayChopping : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestByteArrayChopping);
    CPPUNIT_TEST(testChopEmpty);
    CPPUNIT_TEST(testChopBack);
    CPPUNIT_TEST(testChopFront);
    CPPUNIT_TEST_SUITE_END();

public:
    void testChopEmpty() {
        ByteArray ba;
        CPPUNIT_ASSERT_NO_THROW(ba.chopBack(3));
        CPPUNIT_ASSERT_NO_THROW(ba.chopFront(3));
        CPPUNIT_ASSERT(ba.isEmpty());

        ba = ByteArray("foo", 3);
        CPPUNIT_ASSERT_NO_THROW(ba.chopBack(6));
        CPPUNIT_ASSERT(ba.isEmpty());

        ba = ByteArray("foo", 3);
        CPPUNIT_ASSERT_NO_THROW(ba.chopFront(6));
        CPPUNIT_ASSERT(ba.isEmpty());
    }

    void testChopBack() {
        ByteArray ba("foobar", 6);

        ba.chopBack(0);
        CPPUNIT_ASSERT_EQUAL(ByteArray("foobar", 6), ba);
        ba.chopBack(1);
        CPPUNIT_ASSERT_EQUAL(ByteArray("fooba", 5), ba);
        ba.chopBack(2);
        CPPUNIT_ASSERT_EQUAL(ByteArray("foo", 3), ba);
        ba.chopBack(3);
        CPPUNIT_ASSERT(ba.isEmpty());
    }

    void testChopFront() {
        ByteArray ba("foobar", 6);

        ba.chopFront(0);
        CPPUNIT_ASSERT_EQUAL(ByteArray("foobar", 6), ba);
        ba.chopFront(1);
        CPPUNIT_ASSERT_EQUAL(ByteArray("oobar", 5), ba);
        ba.chopFront(2);
        CPPUNIT_ASSERT_EQUAL(ByteArray("bar", 3), ba);
        ba.chopFront(3);
        CPPUNIT_ASSERT(ba.isEmpty());
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestByteArrayChopping);

class TestByteArrayExtending : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestByteArrayExtending);
    CPPUNIT_TEST(testAppendEmpty);
    CPPUNIT_TEST(testPrependEmpty);
    CPPUNIT_TEST(testAppend);
    CPPUNIT_TEST(testPrepend);
    CPPUNIT_TEST(testAppendSelf);
    CPPUNIT_TEST(testPrependSelf);
    CPPUNIT_TEST_SUITE_END();

public:
    void testAppendEmpty() {
        const ByteArray ba("foo", 3);
        ByteArray b2;
        b2.append(ByteArray());
        CPPUNIT_ASSERT(b2.isEmpty());
        b2.append(ba);
        CPPUNIT_ASSERT_EQUAL(ba, b2);
    }

    void testPrependEmpty() {
        const ByteArray ba("foo", 3);
        ByteArray b2;
        b2.prepend(ByteArray());
        CPPUNIT_ASSERT(b2.isEmpty());
        b2.prepend(ba);
        CPPUNIT_ASSERT_EQUAL(ba, b2);
    }

    void testAppend() {
        ByteArray ba("foo", 3);
        ba.append("b", 1);
        ba.append("ar", 2);
        CPPUNIT_ASSERT_EQUAL(ByteArray("foobar", 6), ba);
        ba.append('!');
        CPPUNIT_ASSERT_EQUAL(ByteArray("foobar!", 7), ba);
    }

    void testPrepend() {
        ByteArray ba("foo", 3);
        ba.prepend("ar", 2);
        ba.prepend("b", 1);
        CPPUNIT_ASSERT_EQUAL(ByteArray("barfoo", 6), ba);
        ba.prepend('!');
        CPPUNIT_ASSERT_EQUAL(ByteArray("!barfoo", 7), ba);
    }

    void testAppendSelf() {
        ByteArray ba("foo", 3);
        ba.append(ba);
        CPPUNIT_ASSERT_EQUAL(ByteArray("foofoo", 6), ba);
    }

    void testPrependSelf() {
        ByteArray ba("foo", 3);
        ba.prepend(ba);
        CPPUNIT_ASSERT_EQUAL(ByteArray("foofoo", 6), ba);
    }
};
CPPUNIT_TEST_SUITE_REGISTRATION(TestByteArrayExtending);