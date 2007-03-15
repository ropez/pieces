#include "Pieces/PropertyList"
#include "Pieces/ValueList"
#include "Pieces/ByteArray"
#include "Pieces/DataStream"
#include "Pieces/Vector"
#include "Pieces/Debug"

#include <iostream>
#include <sstream>

int main()
{
    using namespace Pieces;

    DataStream ds;
    ds << "Piece of shit";
    DEBUG << ds.data() << " " << ds.data().allocated();

    std::string str;
    ds >> str;
    DEBUG << str;


    ByteArray ba = ds.data();
    ByteArray b2 = ba;
    ByteArray b3 = ba;
    const ByteArray b4 = ba;

    b2[0] = 'K';
    b2.resize(5);
    DEBUG << ba;
    DEBUG << b2;
    DEBUG << std::boolalpha << (ba.data() == b3.data());
    DEBUG << std::boolalpha << (ba.data() == b4.data());

    DEBUG << (b2 + b3);

    using Pieces::Vector;
    Vector<int> vec;
    vec.append(6);
    vec.append(7);
    vec.append(8);

    for (Vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        DEBUG << "Element: " << *it;
    }

    Pieces::DataStream d;
    d << vec[0] << vec[1] << vec[2];
    int a, b, c;
    d >> a >> b >> c;
    DEBUG << a << " " << b << " " << c;

    enum
    {
        ROBIN,
        ANGLE,
        DOCUMENTATION,
        SUB_PIECE,
        SUB_LIST,
        BYTE_ARRAY,
        STRING
    };

    using Pieces::ValueList;
    using Pieces::PropertyList;

    PropertyList t;
    t.set(ROBIN, 10).set(ANGLE, 2e23).set(BYTE_ARRAY, ds.data());
    t.set(STRING, "Hello world");

    ValueList l;
    l.add('a').add(10).add(2.34);

    DEBUG << "A piece:\n" << t;
    DEBUG << "A list:\n" << l;

    DEBUG << "Reading from the piece:";
    DEBUG << t.get<int>(ROBIN);
    DEBUG << t.get<double>(ANGLE);
    DEBUG << t.get<std::string>(STRING);

    PropertyList p;
    p.set(SUB_PIECE, t);
    p.set(SUB_LIST, l);

    DEBUG << "A piece that contains a list and a piece:\n" << p;

    DEBUG << "Extracted data:";
    DEBUG << p.get<PropertyList>(SUB_PIECE).get<int>(ROBIN);
    DEBUG << p.get<ValueList>(SUB_LIST).get<double>(2);

    ValueList q;
    q.add(t).add(l);

    DEBUG << "Can do the same with a list:\n" << q;
}

