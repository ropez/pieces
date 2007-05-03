
#include "Pieces/Application"
#include "Pieces/Debug"
#include "Pieces/Timer"
#include "Pieces/Host"
#include "Pieces/Peer"
#include "Pieces/HostThread"
#include "Pieces/PeerThread"
#include "Pieces/Event"
#include "Pieces/TimerEvent"
#include "Pieces/GameEvent"
#include "Pieces/InputEvent"
#include "Pieces/UDPSocket"
#include "Pieces/Datagram"
#include "Pieces/PropertyList"
#include "Pieces/Exception"
#include "Pieces/BufferStream"
#include "Pieces/TCPReceiverThread"
#include "Pieces/TCPSocket"
#include "Pieces/EventLoop"
#include "OpenThreads/Thread"


using namespace pcs;

enum MyEvents
{
    ID_QUIT_PEER,
    ID_QUIT_HOST,
    ID_REPEATING,

    KICK_MONSTER,
    FIRE_BAZOOKA,
    RUN_AND_HIDE
};

AutoPointer<Peer> peer;
AutoPointer<Host> host;


class Listener : public OpenThreads::Thread
{
protected:
    void run()
    {
        try
        {
            AutoPointer<UDPSocket> sock(new UDPSocket);

            sock->bind(3333);

            PDEBUG << "Waiting for datagram";

            Datagram dg = sock->receive(0x1000);

            PDEBUG << "Incoming datagram from " << dg.getAddress();

            BufferStream ds(dg.getData());
            PropertyList pl;
            ds >> pl;

            PDEBUG << "Value 0: " << pl.get<double>(0);
            PDEBUG << "Value 1: " << pl.get<double>(1);
        }
        catch (const Exception& e)
        {
            PERROR << e;
        }
    }
};


class MyPeer : public Peer
{
public:
    MyPeer()
        : m_repeating(new Timer(ID_REPEATING, eventLoop()))
    {
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
            host->postEvent(new InputEvent(FIRE_BAZOOKA));
            break;
        case ID_QUIT_PEER:
            quit();
            break;
        default:
            break;
        }
    }

    void handle(GameEvent* event)
    {
        PDEBUG << "Peer game-event, type = " << event->type();
    }

private:
    AutoPointer<Timer> m_repeating;
};


class MyHost : public Host
{
public:
    MyHost()
    : sock(new UDPSocket)
    {
    }

protected:
    void handle(TimerEvent* event)
    {
        // Handle events
        PDEBUG << "Host timer-event, id = " << event->getTimerId();

        try
        {
            PropertyList pl;
            pl.set(0, 3.14);
            pl.set(1, 2.54);

            BufferStream ds;
            ds << pl;

            Datagram dg;
            dg.setAddress(SocketAddress(InetAddress("<broadcast>"), 3333));
            dg.setData(ds.data());

            sock->send(dg);

            PDEBUG << "Sent datagram to " << dg.getAddress();
        }
        catch (const Exception& e)
        {
            PERROR << e;
        }

        switch (event->getTimerId())
        {
        case ID_QUIT_HOST:
            quit();
            break;
        default:
            break;
        }
    }

    void handle(InputEvent* event)
    {
        // Handle events
        PDEBUG << "Host input-event, type = " << event->type();
    }

private:
    AutoPointer<UDPSocket> sock;
};


int main(int argc, char** argv)
{
    Application application(argc, argv);

    host = new MyHost;
    peer = new MyPeer;

    HostThread th(host.get());
    th.start();
    PeerThread tp(peer.get());
    tp.start();
    Listener l;
    l.start();

    // This timer stops the Host
    Timer tQuitHost(ID_QUIT_HOST, host->eventLoop());
    tQuitHost.start(8000);

    // This timer stops the Peer
    Timer tQuitPeer(ID_QUIT_PEER, peer->eventLoop());
    tQuitPeer.start(10000);


    // Testing tcp receiver thread
    TCPSocket socket;

    TCPReceiverThread tcpthread(&socket, peer->eventLoop());
    tcpthread.start();
    tcpthread.join();

    th.join();
    tp.join();
    l.join();
}
