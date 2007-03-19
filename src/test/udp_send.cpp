#include "Pieces/PropertyList"
#include "Pieces/ValueList"
#include "Pieces/ByteArray"
#include "Pieces/BufferStream"
#include "Pieces/Vector"
#include "Pieces/File"
#include "Pieces/Debug"
#include "Pieces/UDPSocket"
#include "Pieces/Datagram"

#include <iostream>
#include <sstream>

using namespace Pieces;

int main()
{
    // create socket
    UDPSocket us;

    // bind to specified socket address
    InetAddress ia = InetAddress("129.242.219.56");
    port_t port = 5000;
    SocketAddress addr(ia, port);
    us.bind(addr);

    //send data
    BufferStream data;
    data << "Dette er en test";
    DEBUG << data.data() << " " << data.data().allocated();
    Datagram dg;
    dg.setAddress(addr);
    dg.setData(data.data());
    us.send(dg);

    //close socket
    us.close();
}




