
#include "Pieces/TimerThread"
#include "Pieces/Event"
#include "Pieces/EventLoop"

#include "OpenThreads/Mutex"
#include "OpenThreads/Condition"
#include "OpenThreads/ScopedLock"


namespace Pieces
{

using OpenThreads::Mutex;
using OpenThreads::Condition;
using OpenThreads::ScopedLock;


class TimerThreadPrivate
{
public:
    TimerThreadPrivate();

    EventLoop* eventLoop;
    
    bool aborted;
    Mutex mutex;
    Condition cond;
    
    unsigned int delay;
    Event event;
};


TimerThreadPrivate::TimerThreadPrivate()
: eventLoop(0)
, aborted(false)
, mutex()
, cond()
, delay(0)
, event()
{
}


TimerThread::TimerThread(EventLoop* eventLoop)
    : d(new TimerThreadPrivate)
{
    d->eventLoop = eventLoop;
}


TimerThread::~TimerThread()
{
    delete d;
}


void TimerThread::setDelay(unsigned long int ms)
{
    d->delay = ms;
}


void TimerThread::setEvent(const Event& event)
{
    d->event = event;
}


void TimerThread::abort()
{
    {
        ScopedLock<Mutex> lock(d->mutex);
        d->aborted = true;
        d->cond.signal();
    }
    join();
    d->aborted = false;
}


void TimerThread::run()
{
    ScopedLock<Mutex> lock(d->mutex);
    
    // Check if it was aborted
    if (!d->aborted && d->cond.wait(&d->mutex, d->delay))
    {
        // Timed out, post event
        d->eventLoop->postEvent(d->event);
    }
}

} // namespace Pieces
