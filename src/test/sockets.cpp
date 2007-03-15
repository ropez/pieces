#include "Pieces/PropertyList"
#include "Pieces/ValueList"
#include "Pieces/ByteArray"
#include "Pieces/DataStream"
#include "Pieces/Vector"
#include "Pieces/Debug"
#include "Pieces/InetAddress"

#include <iostream>
#include <sstream>

int main()
{
    using namespace Pieces;

    //make invalid inet address object (0.0.0.0)
    InetAddress ia;

    //show it
    std::cout << "Inet address is: " << ia << std::endl;

    //test constructor giving ip as string argument
    ia = InetAddress("192.168.0.1");

    //show it
    std::cout << "Inet address is: " << ia << std::endl;

    //test get host by name
    ia = InetAddress::getHostByName("www.google.com");

    //show it
    std::cout << "Inet address is: " << ia << std::endl;
}

