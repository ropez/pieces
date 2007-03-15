#include "Pieces/TCPSocket"
#include "Pieces/SocketAddress"
#include "Pieces/Exception"
#include "Pieces/Debug"


int main()
{
    using namespace Pieces;

    const char* request = "GET /index.html HTTP/1.1\r\nHost: www.google.no\r\n\r\n";

    try
    {
        InetAddress ia = InetAddress::getHostByName("www.google.no");

        TCPSocket s;
        if (s.connect(SocketAddress(ia, 80)))
        {
            INFO << "Connected";

            ByteArray ba(request, strlen(request) + 1);
            s.write(ba);
            DEBUG << "Sent request";

            DEBUG << s.read().data();
        }
    }
    catch (const Exception& e)
    {
        ERROR << e;
    }
}

