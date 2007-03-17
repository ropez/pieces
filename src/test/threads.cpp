#include "Pieces/Debug"
#include "Pieces/Timer"
#include "Pieces/Host"
#include "Pieces/Peer"
#include "Pieces/Event"
#include "Pieces/TimerEvent"
#include "Pieces/GameEvent"
#include "Pieces/InputEvent"
#include "Pieces/UDPSocket"
#include "Pieces/Datagram"
#include "Pieces/PropertyList"
#include "Pieces/Exception"
#include "Pieces/BufferStream"
#include "OpenThreads/Thread"


using namespace Pieces;

enum MyEvents
{
    ID_QUIT_PEER,
    ID_QUIT_HOST,
    ID_REPEATING,

    KICK_MONSTER,
    FIRE_BAZOOKA,
    RUN_AND_HIDE
};

std::auto_ptr<Peer> peer;
std::auto_ptr<Host> host;


class Listener : public OpenThreads::Thread
{
protected:
    void run()
    {
        try
        {
            std::auto_ptr<UDPSocket> sock(new UDPSocket);

            sock->bind(3333);

            DEBUG << "Waiting for datagram";

            Datagram dg = sock->receive(0x1000);

            DEBUG << "Incoming datagram from " << dg.getAddress();

            BufferStream ds(dg.getData());
            PropertyList pl;
            ds >> pl;

            DEBUG << "Value 0: " << pl.get<double>(0);
            DEBUG << "Value 1: " << pl.get<double>(1);
        }
        catch (const Exception& e)
        {
            ERROR << e;
        }
    }
};


class MyPeer : public Peer
{
public:
    MyPeer()
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
        DEBUG << "Peer game-event, type = " << event->type();
    }

private:
    Timer* m_repeating;
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
        DEBUG << "Host timer-event, id = " << event->getTimerId();

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

            DEBUG << "Sent datagram to " << dg.getAddress();
        }
        catch (const Exception& e)
        {
            ERROR << e;
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
        DEBUG << "Host input-event, type = " << event->type();
    }

private:
    std::auto_ptr<UDPSocket> sock;
};


class ThreadRunningPeer : public OpenThreads::Thread
{
protected:
    virtual void run()
    {
        peer->exec();
    }
};


class ThreadRunningHost : public OpenThreads::Thread
{
protected:
    virtual void run()
    {
        host->exec();
    }
};


int main()
{
    host.reset(new MyHost);
    peer.reset(new MyPeer);

    ThreadRunningHost th;
    th.start();
    ThreadRunningPeer tp;
    tp.start();
    Listener l;
    l.start();

    // This timer stops the Host
    Timer tQuitHost(ID_QUIT_HOST, host->eventLoop());
    tQuitHost.start(8000);

    // This timer stops the Peer
    Timer tQuitPeer(ID_QUIT_PEER, peer->eventLoop());
    tQuitPeer.start(10000);

    th.join();
    tp.join();
    l.join();
}
