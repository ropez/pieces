#include "Pieces/Debug"
#include "Pieces/Timer"
#include "Pieces/Host"
#include "Pieces/Peer"
#include "OpenThreads/Thread"


using namespace Pieces;

enum MyEvents
{
    USER_DEFINED = Event::USER_DEFINED, // Make the automatic counter start here

    QUIT_PEER,

    QUIT_HOST,

    KICK_MONSTER,
    FIRE_BAZOOKA,
    RUN_AND_HIDE
};


class MyPeer : public Peer
{
protected:
    void userDefinedEvent(Event* event)
    {
        // Handle events
        debug() << "Peer incoming event, type: " << event->type();

        if (event->type() == QUIT_PEER)
        {
            quit();
        }
    }
};


class MyHost : public Host
{
protected:
    void userDefinedEvent(Event* event)
    {
        // Handle events
        debug() << "Host incoming event, type: " << event->type();

        if (event->type() == QUIT_HOST)
        {
            quit();
        }
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
    Timer peerTimer(p.eventLoop());
    peerTimer.start(10000, new Event(QUIT_PEER));

    ThreadRunningPeer th(&p);

    debug() << "Running peer";
    th.start();

    MyHost h;

//     std::auto_ptr<Timer> repeating(new Timer(h.eventLoop()));
//     repeating->setRepeating(true);
//     repeating->start(200, new Event(FIRE_BAZOOKA));

    Timer t1(h.eventLoop());
    t1.start(999, new Event(KICK_MONSTER));
    // Restart the timer
    t1.start(2000, new Event(RUN_AND_HIDE));

    // This timer stops the Host
    Timer t2(h.eventLoop());
    t2.start(5000, new Event(QUIT_HOST));

    debug() << "Running host";
    h.exec();

    th.join();
}
