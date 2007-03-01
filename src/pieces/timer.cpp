
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
    // TODO: Replace this with stop(), it's implemented like this for debugging purposes
    if (d->started)
    {
        d->thread->join();
    }
    
    delete d->thread;
    delete d;
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
    }
}

} // namespace Pieces
