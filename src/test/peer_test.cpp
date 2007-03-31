
#include "Pieces/Application"
#include "Pieces/Peer"

#include "Pieces/ConnectionManager"
#include "Pieces/Message"

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
                Message message(666);
                message.set<std::string>(PR_TEXT, "Follow the white rabbit");

                connectionManager()->sendMessage(message);
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
    Application application(argc, argv);

    AutoPointer<PeerTest> peer(new PeerTest);

    std::string hostname = "localhost";
    if (app->argc() > 1)
    {
        hostname = app->arg(1);
    }

    port_t port = 2222;
    if (app->argc() > 2)
    {
        port = std::atoi(app->arg(2).c_str());
    }

    SocketAddress address(InetAddress::getHostByName(hostname), port);
    peer->connectTo(address);

    // This timer stops the Peer
    Timer tQuitPeer(ID_QUIT_PEER, peer->eventLoop());
    tQuitPeer.start(4000);

    peer->exec();
}
