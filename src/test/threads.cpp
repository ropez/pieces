#include "Pieces/Debug"
#include "Pieces/Timer"
#include "Pieces/Host"
#include "Pieces/Peer"


using namespace Pieces;

enum MyEvents
{
    USER_DEFINED = Event::USER_DEFINED, // Make the automatic counter start here

    QUIT_PEER
};


class MyPeer : public Peer
{
protected:
    void userDefinedEvent(const Event& event)
    {
        // Handle events
        debug() << "Incoming event:";
        debug() << " type: " << event.type();
        debug() << " data: " << event.data();

        if (event.type() == QUIT_PEER)
        {
            quit();
        }
    }
};

int main()
{
    Host h;

    Timer* repeating = new Timer(h.eventLoop());
    repeating->setRepeating(true);
    repeating->start(200, Event(222));

    Timer t1(h.eventLoop());
    t1.start(999, Event(1));
    // Restart the timer
    t1.start(2000, Event(2));

    // This timer stops the Host
    Timer t2(h.eventLoop());
    t2.start(5000, Event(3));

    h.exec();

    debug() << "Running host";
    MyPeer p;

    Timer peerTimer(p.eventLoop());
    peerTimer.start(1000, Event(QUIT_PEER));

    debug() << "Running peer";
    p.exec();
}
