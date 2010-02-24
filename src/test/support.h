#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <Pieces/ByteArray>
#include <Pieces/ValueList>
#include <Pieces/PropertyList>
#include <cstring>
#include <iomanip>
#include <algorithm>

namespace CppUnit {
template<>
struct assertion_traits<pcs::ByteArray>
{
    static bool equal(const pcs::ByteArray& x, const pcs::ByteArray& y)
    {
        if (x.size() != y.size())
            return false;
        if (std::memcmp(x.constData(), y.constData(), x.size()))
            return false;
        else
            return true;
    }

    static std::string toString(const pcs::ByteArray& x)
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

template<>
struct assertion_traits<pcs::ValueList>
{
    static bool equal(const pcs::ValueList& x, const pcs::ValueList& y)
    {
        if (x.size() != y.size())
            return false;
        for (int i = 0; i < x.size(); ++i) {
            if (x.getValue(i) != y.getValue(i))
                return false;
        }
        return true;
    }

    static std::string toString(const pcs::ValueList& x)
    {
        std::stringstream ss;
        ss << '[';
        for (int i = 0; i < x.size(); ++i) {
            if (i != 0)
                ss << ", ";
            ss << assertion_traits<pcs::ByteArray>::toString(x.getValue(i));
        }
        ss << ']';
        return ss.str();
    }
};

template<>
struct assertion_traits<pcs::PropertyList>
{
    typedef pcs::PropertyList::map_t::const_iterator iter_t;

    static bool equal(const pcs::PropertyList& x, const pcs::PropertyList& y)
    {
        if (x.size() != y.size())
            return false;
        for (iter_t it = x.begin(); it != x.end(); ++it) {
            if (!y.hasProperty(it->first))
                return false;
            if (y.getProperty(it->first) != it->second)
                return false;
        }
        return true;
    }

    static std::string toString(const pcs::PropertyList& x)
    {
        std::stringstream ss;
        ss << '{';
        for (iter_t it = x.begin(); it != x.end(); ++it) {
            if (it != x.begin())
                ss << ", ";
            ss << it->first << " => " << assertion_traits<pcs::ByteArray>::toString(it->second);
        }
        ss << '}';
        return ss.str();
    }
};
}