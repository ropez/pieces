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
#include "OpenThreads/Thread"


#include <iostream>
#include <sstream>

using namespace Pieces;

int main()
{
    OpenThreads::Thread::Init();

    try
    {
        // create socket
        UDPSocket us;

        // bind to specified socket address
        InetAddress ia("127.0.0.1");
        port_t port = 5000;
        SocketAddress addr(ia, port);

        DEBUG << ia;

        //send data
        BufferStream data;
        data << "Dette er en test";
        std::string str;
        data >> str;
        DEBUG << str;
        Datagram dg;
        dg.setAddress(addr);
        dg.setData(data.data());

        while(true)
        {
            us.send(dg);
            OpenThreads::Thread::microSleep(1000000);
        }


    //close socket
        us.close();
    }
    catch(Pieces::Exception e)
    {
        ERROR << e;
    }
}




