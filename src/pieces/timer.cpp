
#include "Pieces/Timer"
#include "Pieces/TimerThread"
#include "Pieces/ByteArray"


namespace Pieces
{

class TimerPrivate
{
public:
    TimerPrivate();

    int id;

    TimerThread* thread;
    bool started;
};


TimerPrivate::TimerPrivate()
: id(0)
, thread(0)
, started(false)
{
}


Timer::Timer(EventLoop* eventLoop)
: d(new TimerPrivate)
{
    d->thread = new TimerThread(eventLoop);
}


Timer::Timer(int id, EventLoop* eventLoop)
: d(new TimerPrivate)
{
    d->id = id;
    d->thread = new TimerThread(eventLoop);
}


Timer::~Timer()
{
    // If the timer is running, stop it.
    stop();

    delete d->thread;
    delete d;
}


bool Timer::isRepeating() const
{
    return d->thread->isRepeating();
}


void Timer::setRepeating(bool on)
{
    if (!d->started)
    {
        d->thread->setRepeating(on);
    }
}


void Timer::start(unsigned long int delay, const ByteArray& data)
{
    stop();

    d->thread->setTimerId(d->id);
    d->thread->setDelay(delay);
    d->thread->setData(data);
    d->thread->start();
    d->started = true;
}


void Timer::start(unsigned long int delay)
{
    start(delay, ByteArray());
}


void Timer::stop()
{
    if (d->started)
    {
        d->thread->abort();
        d->started = false;
    }
}

} // namespace Pieces
