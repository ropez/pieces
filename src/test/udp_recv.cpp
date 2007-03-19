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
        SocketAddress addr(InetAddress(), 5000);
        us.bind(addr);

        //recv data
        DEBUG  << "Bound to " << addr;

        while (true)
        {
            Datagram dg(us.receive(1000));

            DEBUG  << "Here";

            ByteArray ba(dg.getData());
            BufferStream data(ba);

            std::string str;
            data >> str;

            DEBUG << str;
        }

        //close socket
        us.close();
    }
    catch(Pieces::Exception e)
    {
        ERROR << e;
    }
}




