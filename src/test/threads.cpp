
#include "Pieces/EventHandler"
#include "Pieces/EventLoop"

#include <OpenThreads/Thread>
#include <iostream>


const int EVENT_TIMER = 1000;

namespace Pieces
{
class Timer : public OpenThreads::Thread
{
public:
    Timer(EventLoop* eventLoop,  int delay)
    : m_eventLoop(eventLoop)
    , m_delay(delay)
    {
    }

protected:
    void run()
    {
        microSleep(m_delay * 1000);
        m_eventLoop->postEvent(Event(EVENT_TIMER));
    }

private:
    EventLoop* m_eventLoop;
    int m_delay;
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

    Pieces::Timer t1(h.eventLoop(), 2000);
    t1.start();
    Pieces::Timer t2(h.eventLoop(), 5000);
    t2.start();

    t1.join();
    t2.join();

    h.eventLoop()->quit();

    h.join();
}
