
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
        usleep(m_delay * 1000);
        m_eventLoop->postEvent(Event(EVENT_TIMER));
    }

private:
    EventLoop* m_eventLoop;
    int m_delay;
};
}


class MyEventLoop : public Pieces::EventLoop
{
protected:
    void processEvent(const Pieces::Event& e)
    {
        std::cout << "Event " << e.type() << std::endl;
    }
};


MyEventLoop loop;


class MyThread : public OpenThreads::Thread
{
public:
    void run()
    {
        std::cout << "Running thread" << std::endl;

        loop.exec();
    }
};

int main()
{
    MyThread t;
    t.start();

    Pieces::Timer t1(&loop, 2000);
    t1.start();
    Pieces::Timer t2(&loop, 5000);
    t2.start();

    t1.join();
    t2.join();
    loop.quit();
    t.join();
}
