#include "Pieces/Debug"
#include "Pieces/Timer"
#include "Pieces/Host"
#include "Pieces/Peer"
#include "Pieces/Event"
#include "Pieces/TimerEvent"
#include "OpenThreads/Thread"


using namespace Pieces;

enum MyEvents
{
    ID_QUIT_PEER,
    ID_QUIT_HOST,

    KICK_MONSTER,
    FIRE_BAZOOKA,
    RUN_AND_HIDE
};


class MyPeer : public Peer
{
protected:
    void handle(TimerEvent* event)
    {
        // Handle events
        debug() << "Peer timer-event";

        if (event->getTimerId() == ID_QUIT_PEER)
        {
            quit();
        }
    }

    void handle(GameEvent*)
    {
        debug() << "Peer game-event";
    }
};


class MyHost : public Host
{
protected:
    void handle(TimerEvent* event)
    {
        // Handle events
        debug() << "Host timer-event";

        if (event->getTimerId() == ID_QUIT_HOST)
        {
            quit();
        }
    }


    void handle(GameEvent*)
    {
        debug() << "Peer game-event";
    }
};


class ThreadRunningPeer : public OpenThreads::Thread
{
public:
    ThreadRunningPeer(Peer* p)
    : m_peer(p)
    {
    }

protected:
    virtual void run()
    {
        m_peer->exec();
    }

private:
    Peer* m_peer;
};


int main()
{
    MyPeer p;
    Timer peerTimer(ID_QUIT_PEER, p.eventLoop());
    peerTimer.start(10000);

    ThreadRunningPeer th(&p);

    debug() << "Running peer";
    th.start();

    MyHost h;

    std::auto_ptr<Timer> repeating(new Timer(h.eventLoop()));
    repeating->setRepeating(true);
    repeating->start(200);

    Timer t1(h.eventLoop());
    t1.start(999);
    // Restart the timer
    t1.start(2000);

    // This timer stops the Host
    Timer t2(ID_QUIT_HOST, h.eventLoop());
    t2.start(5000);

    debug() << "Running host";
    h.exec();

    th.join();
}
