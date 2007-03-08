#include "Pieces/Debug"
#include "Pieces/Timer"
#include "Pieces/Host"
#include "Pieces/Peer"


int main()
{
    using namespace Pieces;

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
    Peer p;

    Timer peerTimer(p.eventLoop());
    peerTimer.start(1000, Event(3));

    debug() << "Running peer";
    p.exec();
}
