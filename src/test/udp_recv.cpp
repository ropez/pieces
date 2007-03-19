#include "Pieces/Exception"
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
    try{
    // create socket
    UDPSocket us;

    // bind to specified socket address
    InetAddress ia = InetAddress("129.242.13.188");
    port_t port = 5000;
    SocketAddress addr(ia, port);
    DEBUG << addr.getInetAddress().toString();
    us.bind(addr);

    //recv data
    Datagram dg(us.receive(1000));

    ByteArray ba(dg.getData());
    BufferStream data(ba);

    DEBUG << data.data() << " " << data.data().allocated();

    //close socket
    us.close();
    }catch(Pieces::Exception e)
    {
        ERROR << e;
    }
}




