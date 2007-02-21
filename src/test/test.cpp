#include "pieces/PropertyList"
#include "pieces/ValueList"
#include "pieces/ByteArray"
#include "pieces/DataStream"
#include "pieces/Vector"

#include <iostream>
#include <sstream>

int main()
{
//     using Pieces::ByteArray;
//
//     const ByteArray ba("Piece of shit", 14);
//     std::cout << ba.data() << std::endl;
//
//     ByteArray b2 = ba;
//     ByteArray b3 = ba;
//     const ByteArray b4 = ba;
//
//     b2[0] = 'K';
//     b2.resize(5);
//     std::cout << ba.data() << std::endl;
//     std::cout << b2.data() << std::endl;
//     std::cout << std::boolalpha << (ba.data() == b3.data()) << std::endl;
//     std::cout << std::boolalpha << (ba.data() == b4.data()) << std::endl;
//
//     std::cout << (b2 + b3).data() << std::endl;
//
//     using Pieces::Vector;
//     Vector<int> vec;
//     vec.append(6);
//     vec.append(7);
//     vec.append(8);
//
//     for (Vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
//     {
//         std::cout << "Element: " << *it << std::endl;
//     }
//
//     Pieces::DataStream d;
//     d << vec[0] << vec[1] << vec[2];
//     int a, b, c;
//     d >> a >> b >> c;
//     std::cout << a << " " << b << " " << c << std::endl;

    using Pieces::ValueList;
    using Pieces::PropertyList;

    PropertyList t;
    t.set("robin", 10).set("angle", 2e23).set("documentation", "supercool stuff");

    ValueList l;
    l.add('a').add(10).add(2.34).add("joakim simonsson");

    std::cout << "A piece:\n" << t << std::endl;
    std::cout << "A list:\n" << l << std::endl;

    std::cout << "Reading from the piece:" << std::endl;
    std::cout << t.get<int>("robin") << std::endl;
    std::cout << t.get<double>("angle") << std::endl;

    PropertyList p;
    p.set("sub-piece", t);
    p.set("sub-list", l);

    std::cout << "A piece that contains a list and a piece:\n" << p << std::endl;

    std::cout << "Extracted data:" << std::endl;
    std::cout << p.get<PropertyList>("sub-piece").get<PString>("documentation") << std::endl;
    std::cout << p.get<ValueList>("sub-list").get<PString>(3) << std::endl;

    ValueList q;
    q.add(t).add(l);

    std::cout << "Can do the same with a list:\n" << q << std::endl;
}

