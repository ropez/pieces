#include "Pieces/Debug"
#include "Pieces/Timer"
#include "Pieces/Host"
#include "Pieces/Peer"
#include "Pieces/Event"
#include "Pieces/TimerEvent"
#include "Pieces/GameEvent"
#include "Pieces/InputEvent"
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


class MyPeer : public Peer
{
protected:
    void handle(TimerEvent* event)
    {
        // Handle events
        debug() << "Peer timer-event";

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
        debug() << "Peer game-event, type = " << event->type();
    }
};


class MyHost : public Host
{
protected:
    void handle(TimerEvent* event)
    {
        // Handle events
        debug() << "Host timer-event";

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
        debug() << "Host input-event, type = " << event->type();
    }
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

    // This timer stops the Host
    Timer tQuitHost(ID_QUIT_HOST, host->eventLoop());
    tQuitHost.start(8000);

    // This timer stops the Peer
    Timer tQuitPeer(ID_QUIT_PEER, peer->eventLoop());
    tQuitPeer.start(10000);

    Timer repeating(ID_REPEATING, peer->eventLoop());
    repeating.setRepeating(true);
    repeating.start(500);

    th.join();
    tp.join();
}
