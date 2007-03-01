
#include "Pieces/EventHandler"
#include "Pieces/EventLoop"

#include <OpenThreads/Thread>
#include <OpenThreads/Condition>
#include <OpenThreads/Mutex>
#include <OpenThreads/ScopedLock>
#include <iostream>


namespace Pieces
{

using OpenThreads::Condition;
using OpenThreads::Mutex;
using OpenThreads::ScopedLock;

class TimerThread : public OpenThreads::Thread
{
public:
    TimerThread(EventLoop* eventLoop)
    : d(new Data)
    {
        d->eventLoop = eventLoop;
        d->aborted = false;
        d->delay = 0;
    }

    ~TimerThread()
    {
        delete d;
    }

    /**
     * In milliseconds.
     */
    void setDelay(unsigned long int ms)
    {
        d->delay = ms;
    }

    void setEvent(const Event& event)
    {
        d->event = event;
    }

    void abort()
    {
        {
            ScopedLock<Mutex> lock(d->mutex);
            d->aborted = true;
            d->cond.signal();
        }
        join();
        d->aborted = false;
    }

protected:
    void run()
    {
        ScopedLock<Mutex> lock(d->mutex);

        // Check if it was aborted
        std::cout << d->aborted << " " << d->delay << std::endl;
        if (!d->aborted && d->cond.wait(&d->mutex, d->delay))
        {
            d->eventLoop->postEvent(d->event);
        }
    }

private:
    class Data
    {
    public:
        EventLoop* eventLoop;

        bool aborted;
        Mutex mutex;
        Condition cond;

        unsigned int delay;
        Event event;
    } * d;
};


class Timer
{
public:
    Timer(EventLoop* eventLoop)
        : d(new Data)
    {
        d->started = false;
        d->thread = new TimerThread(eventLoop);
    }

    ~Timer()
    {
        // TODO: Replace this with stop()
        if (d->started)
        {
            d->thread->join();
        }
        delete d->thread;
        delete d;
    }

    void start(unsigned long int delay, const Event& event)
    {
        stop();

        d->thread->setDelay(delay);
        d->thread->setEvent(event);
        d->thread->start();
        d->started = true;
    }

    void stop()
    {
        if (d->started)
        {
            d->thread->abort();
            d->thread->join();
        }
    }

private:
    class Data
    {
    public:
        bool started;
        TimerThread* thread;
    } * d;
};

class Host : public OpenThreads::Thread, public EventHandler
{
public:
    Host()
        : Thread()
        , EventHandler()
        , m_eventLoop(0)
    {
        m_eventLoop = new EventLoop(this);
    }

    ~Host()
    {
    }

    EventLoop* eventLoop()
    {
        return m_eventLoop;
    }

    void exec()
    {
        start();
        join();
    }

protected:
    virtual void run()
    {
        std::cout << "Host thread running" << std::endl;
        eventLoop()->exec();
    }

    virtual void event(const Event& event)
    {
        // Handle events
        std::cout << "Incoming event:";
        std::cout << " type: " << event.type();
        std::cout << " data: " << event.data() << std::endl;
    }

private:
    EventLoop* m_eventLoop;
};

}


int main()
{
    Pieces::Host h;
    h.start();

    {
        using Pieces::Timer;
        using Pieces::Event;

        Timer t1(h.eventLoop());
        t1.start(999, Event(1));
//         OpenThreads::Thread::microSleep(1500000);

//         t1.start(2000, Event(2));
//         Timer t2(h.eventLoop());
//         t2.start(5000, Event(3));
//         t2.stop();
    } // Join timers


    h.eventLoop()->quit();
    h.join();
}
