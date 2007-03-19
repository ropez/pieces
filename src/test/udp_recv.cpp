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
        us.bind(5000);

        //recv data
        DEBUG  << "Here";

        Datagram dg(us.receive(1000));

        DEBUG  << "Here";

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




