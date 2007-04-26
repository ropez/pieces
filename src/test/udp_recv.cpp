#include "Pieces/Application"
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

using namespace pcs;

int main(int argc, char** argv)
{
    Application application(argc, argv);

    try
    {
        // create socket
        UDPSocket us;

        // bind to specified socket address
        SocketAddress addr(InetAddress(), 5000);
        us.bind(addr);

        //recv data
        PDEBUG  << "Bound to " << addr;

        while (true)
        {
            Datagram dg(us.receive(1000));

            PDEBUG  << "Here";

            ByteArray ba(dg.getData());
            BufferStream data(ba);

            std::string str;
            data >> str;

            PDEBUG << str;
        }

        //close socket
        us.close();
    }
    catch(pcs::Exception e)
    {
        PERROR << e;
    }
}




