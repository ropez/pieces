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
