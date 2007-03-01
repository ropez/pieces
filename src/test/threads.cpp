
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
}

class MyEventHandler : public Pieces::EventHandler
{
protected:
    void event(const Pieces::Event& e)
    {
        std::cout << "Event " << e.type() << std::endl;
    }
};


Pieces::EventLoop* loop;


class MyThread : public OpenThreads::Thread
{
public:
    void run()
    {
        std::cout << "Running thread" << std::endl;

        loop->exec();
    }
};

int main()
{
    MyEventHandler h;
    loop = new Pieces::EventLoop(&h);

    MyThread t;
    t.start();

    Pieces::Timer t1(loop, 2000);
    t1.start();
    Pieces::Timer t2(loop, 5000);
    t2.start();

    t1.join();
    t2.join();
    loop->quit();
    t.join();
}
