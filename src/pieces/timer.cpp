
#include "Pieces/Timer"
#include "Pieces/TimerThread"


namespace Pieces
{

class TimerPrivate
{
public:
    TimerPrivate();
    
    TimerThread* thread;
    bool started;
};


TimerPrivate::TimerPrivate()
: thread(0)
, started(false)
{
}


Timer::Timer(EventLoop* eventLoop)
: d(new TimerPrivate)
{
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


void Timer::start(unsigned long int delay, const Event& event)
{
    stop();
    
    d->thread->setDelay(delay);
    d->thread->setEvent(event);
    d->thread->start();
    d->started = true;
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
