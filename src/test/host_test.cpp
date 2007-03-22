
#include "Pieces/Host"

#include "Pieces/ConnectionManager"

#include "Pieces/NetworkEvent"
#include "Pieces/SocketAddress"
#include "Pieces/BufferStream"
#include "Pieces/IOException"
#include "Pieces/Debug"

#if defined WIN32
#include <winsock2.h>
#endif

using namespace Pieces;


class HostTest : public Host
{
protected:

    virtual void handle(NetworkEvent* event)
    {
        PDEBUG << "Got network event, type " << event->type();

        try
        {
            BufferStream bf(event->getData());

            std::string str;
            bf >> str;
            PDEBUG << "From: " << event->getSenderAddress();
            PDEBUG << "Message type: " << event->getMessageType();
            PDEBUG << "Data (as string): " << str;
        }
        catch (const IOException& e)
        {
            PWARNING << e;
        }
    }
};


int main()
{

#if defined WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 2, 2 );

    err = WSAStartup( wVersionRequested, &wsaData );
#endif

    AutoPointer<HostTest> host(new HostTest);

    host->connectionManager()->listen(2222);
    host->exec();

#if defined WIN32
    WSACleanup();
#endif
}
