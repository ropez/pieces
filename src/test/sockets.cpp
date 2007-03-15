#include "Pieces/Debug"
#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"


int main()
{
    using namespace Pieces;

    //make invalid inet address object (0.0.0.0)
    InetAddress ia;
    SocketAddress sa;

    //show it
    DEBUG << "Inet address is: " << ia;
    DEBUG << "Socket address is: " << sa;

    //test constructor giving ip as string argument
    ia = InetAddress("192.168.0.1");
    sa = SocketAddress(ia, 2048);

    //show it
    DEBUG << "Inet address is: " << ia;
    DEBUG << "Socket address is: " << sa;

    //test get host by name
    ia = InetAddress::getHostByName("www.google.com");
    sa.setInetAddress(InetAddress::getHostByName("www.google.com"));

    //show it
    DEBUG << "Inet address is: " << ia;
    DEBUG << "Socket address is: " << sa;
}

