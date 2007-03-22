
#include "Pieces/Peer"

#include "Pieces/ConnectionManager"

#include "Pieces/Timer"
#include "Pieces/TimerEvent"

#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"
#include "Pieces/AutoPointer"

#include "Pieces/BufferStream"
#include "Pieces/Debug"

#include <cstdlib>
#include <string>

#if defined WIN32
#include <winsock2.h>
#endif

using namespace Pieces;


enum MyEvents
{
    ID_QUIT_PEER,
    ID_REPEATING
};


class PeerTest : public Peer
{
public:
    PeerTest()
    {
        m_repeating = new Timer(ID_REPEATING, eventLoop());
        m_repeating->setRepeating(true);
        m_repeating->start(500);
    }

protected:

    void handle(TimerEvent* event)
    {
        // Handle events
        PDEBUG << "Peer timer-event, id = " << event->getTimerId();

        switch (event->getTimerId())
        {
        case ID_REPEATING:
            {
                BufferStream s;
                s << "Follow the white rabbit";
                connectionManager()->sendMessage(666, s.data());
            }
            break;
        case ID_QUIT_PEER:
            quit();
            break;
        default:
            break;
        }
    }

private:
    AutoPointer<Timer> m_repeating;
};


int main(int argc, char** argv)
{

#if defined WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 2, 2 );

    err = WSAStartup( wVersionRequested, &wsaData );
#endif

    AutoPointer<PeerTest> peer(new PeerTest);

    std::string hostname = "localhost";
    if (argc > 1)
    {
        hostname = argv[1];
    }

    port_t port = 2222;
    if (argc > 2)
    {
        port = std::atoi(argv[2]);
    }

    SocketAddress address(InetAddress::getHostByName(hostname), port);
    peer->connectionManager()->connectTo(address);

    // This timer stops the Peer
    Timer tQuitPeer(ID_QUIT_PEER, peer->eventLoop());
    tQuitPeer.start(4000);

    peer->exec();

#if defined WIN32
    WSACleanup();
#endif
}
