
#include "Pieces/TimerThread"
#include "Pieces/TimerEvent"
#include "Pieces/EventLoop"

#include "OpenThreads/Mutex"
#include "OpenThreads/Condition"
#include "OpenThreads/ScopedLock"


namespace pcs
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

    bool repeating;

    int id;
    unsigned long delay;

    ByteArray data;
};


TimerThreadPrivate::TimerThreadPrivate()
: eventLoop(0)
, aborted(false)
, mutex()
, cond()
, repeating(false)
, id(0)
, delay(0)
, data()
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


bool TimerThread::isRepeating() const
{
    return d->repeating;
}


void TimerThread::setRepeating(bool on)
{
    d->repeating = on;
}


int TimerThread::getTimerId() const
{
    return d->id;
}


void TimerThread::setTimerId(int id)
{
    d->id = id;
}


unsigned long TimerThread::getDelay() const
{
    return d->delay;
}


void TimerThread::setDelay(unsigned long msec)
{
    d->delay = msec;
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

    do
    {
        // Check if it was aborted
        if (d->aborted)
            break;

        if (!d->cond.wait(&d->mutex, d->delay))
            break;

        // Timed out, post event
        AutoPointer<Event> e(new TimerEvent(d->id));

        d->eventLoop->postEvent(e.release());
    }
    while (d->repeating);
}

} // namespace pcs
