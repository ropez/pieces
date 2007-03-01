
#include "Pieces/EventHandler"
#include "Pieces/EventLoop"

#include <OpenThreads/Thread>
#include <iostream>


const int EVENT_TIMER = 1000;

namespace Pieces
{
class TimerThread : public OpenThreads::Thread
{
public:
    TimerThread(EventLoop* eventLoop)
    : m_eventLoop(eventLoop)
    , m_delay(0)
    {
    }

    /**
     * In microseconds.
     */
    void setDelay(unsigned int delay)
    {
        m_delay = delay;
    }

protected:
    void run()
    {
        microSleep(m_delay);
        m_eventLoop->postEvent(Event(EVENT_TIMER));
    }

private:
    EventLoop* m_eventLoop;
    unsigned int m_delay;
};

class Timer
{
public:
    Timer(EventLoop* eventLoop)
    : m_thread(eventLoop)
    {
    }

    ~Timer()
    {
        m_thread.join();
    }

    void start(int delay)
    {
        m_thread.setDelay(delay);
        m_thread.start();
    }

private:
    TimerThread m_thread;
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
        Pieces::Timer t1(h.eventLoop());
        t1.start(2000000);
        OpenThreads::Thread::microSleep(1000000);
        t1.start(1000000);
        Pieces::Timer t2(h.eventLoop());
        t2.start(5000000);
    } // Join timers

    h.eventLoop()->quit();
    h.join();
}
