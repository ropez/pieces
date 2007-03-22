#include "Pieces/TCPSocket"
#include "Pieces/SocketAddress"
#include "Pieces/Exception"
#include "OpenThreads/Thread"
#include "Pieces/Debug"


int main()
{
    using namespace Pieces;
    OpenThreads::Thread::Init();

    const char* request = "GET /index.html HTTP/1.1\r\nHost: www.google.com\r\n\r\n";

    try
    {
        InetAddress ia = InetAddress::getHostByName("www.google.com");

        TCPSocket s;
        if (s.connect(SocketAddress(ia, 80)))
        {
            PINFO << "Connected";

            ByteArray ba(request, strlen(request) + 1);
            s.send(ba);
            PDEBUG << "Sent request";

            PDEBUG << s.read(1000).data();
        }
        s.close();


        // Try to use the socket two times
        s.open();
        if (s.connect(SocketAddress(ia, 80)))
        {
            PINFO << "Connected again";
        }

        // This will cause close() to be called twice
        s.close();
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

