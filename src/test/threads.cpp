#include "Pieces/Debug"
#include "Pieces/Timer"
#include "Pieces/Host"
#include "Pieces/Peer"


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
    void userDefinedEvent(const Event& event)
    {
        // Handle events
        debug() << "Incoming event, type: " << event.type();

        if (event.type() == QUIT_PEER)
        {
            quit();
        }
    }
};


class MyHost : public Host
{
protected:
    void userDefinedEvent(const Event& event)
    {
        // Handle events
        debug() << "Incoming event, type: " << event.type();

        if (event.type() == QUIT_HOST)
        {
            quit();
        }
    }
};

int main()
{
    MyHost h;

    Timer* repeating = new Timer(h.eventLoop());
    repeating->setRepeating(true);
    repeating->start(200, Event(FIRE_BAZOOKA));

    Timer t1(h.eventLoop());
    t1.start(999, Event(KICK_MONSTER));
    // Restart the timer
    t1.start(2000, Event(RUN_AND_HIDE));

    // This timer stops the Host
    Timer t2(h.eventLoop());
    t2.start(5000, Event(QUIT_HOST));

    h.exec();

    debug() << "Running host";
    MyPeer p;

    Timer peerTimer(p.eventLoop());
    peerTimer.start(1000, Event(QUIT_PEER));

    debug() << "Running peer";
    p.exec();
}
