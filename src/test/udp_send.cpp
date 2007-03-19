#include "Pieces/PropertyList"
#include "Pieces/ValueList"
#include "Pieces/ByteArray"
#include "Pieces/BufferStream"
#include "Pieces/Vector"
#include "Pieces/File"
#include "Pieces/Debug"
#include "Pieces/UDPSocket"
#include "Pieces/Datagram"
#include "Pieces/Exception"

#include <iostream>
#include <sstream>

using namespace Pieces;

int main()
{
    try{
    // create socket
    UDPSocket us;

    // bind to specified socket address
    InetAddress ia = InetAddress("129.242.219.56");
    port_t port = 5000;
    SocketAddress addr(ia, port);
    us.bind(port);

    //send data
    BufferStream data;
    data << "Dette er en test";
    std::string str;
    data >> str;
    DEBUG << str;
    Datagram dg;
    dg.setAddress(addr);
    dg.setData(data.data());
    us.send(dg);

    //close socket
    us.close();
    }catch(Pieces::Exception e)
    {
        ERROR << e;
    }
}




