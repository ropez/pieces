
#include "Pieces/Peer"

#include "Pieces/TCPConnectionManager"

#include "Pieces/Timer"
#include "Pieces/TimerEvent"

#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"
#include "Pieces/AutoPointer"

#include "Pieces/Debug"

#include <cstdlib>
#include <string>

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
        DEBUG << "Peer timer-event, id = " << event->getTimerId();

        switch (event->getTimerId())
        {
        case ID_REPEATING:
            // TODO: Send message to host
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
    tQuitPeer.start(10000);

    peer->exec();
}
