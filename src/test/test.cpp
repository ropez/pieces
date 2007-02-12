#include "pieces/Piece"
#include "pieces/List"
#include "pieces/ByteArray"
#include "pieces/DataStream"

#include <iostream>
#include <sstream>

int main()
{
    using Pieces::ByteArray;

    const ByteArray ba("Piece of shit", 14);
    std::cout << ba.data() << std::endl;

    ByteArray b2 = ba;
    ByteArray b3 = ba;
    const ByteArray b4 = ba;

    b2[0] = 'K';
    b2.resize(5);
    std::cout << ba.data() << std::endl;
    std::cout << b2.data() << std::endl;
    std::cout << std::boolalpha << (ba.data() == b3.data()) << std::endl;
    std::cout << std::boolalpha << (ba.data() == b4.data()) << std::endl;

    std::cout << (b2 + b3).data() << std::endl;

    Pieces::DataStream d;
    d << 6 << 7 << 7.5 << 8;
    int a, b, c;
    double dl;
    d >> a >> b >> dl >> c;
    std::cout << a << " " << b << " " << c << " " << dl << std::endl;

//     Piece t;
//     t.set("robin", 10).set("angle", 2e23).set("documentation", "supercool stuff");
//
//     List l;
//     l.add('a').add(10).add(2.34).add("joakim simonsson");
//
//     std::cout << "A piece:\n" << t << std::endl;
//     std::cout << "A list:\n" << l << std::endl;
//
//     std::cout << "Reading from the piece:" << std::endl;
//     std::cout << t.get<int>("robin") << std::endl;
//     std::cout << t.get<double>("angle") << std::endl;
//
//     Piece p;
//     p.set("sub-piece", t);
//     p.set("sub-list", l);
//
//     std::cout << "A piece that contains a list and a piece:\n" << p << std::endl;
//
//     std::cout << "Extracted data:" << std::endl;
//     std::cout << p.get<Piece>("sub-piece").get<PString>("documentation") << std::endl;
//     std::cout << p.get<List>("sub-list").get<PString>(3) << std::endl;
//
//     List q;
//     q.add(t).add(l);
//
//     std::cout << "Can do the same with a list:\n" << q << std::endl;
}

