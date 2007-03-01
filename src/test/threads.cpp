
#include "Pieces/Timer"
#include "Pieces/EventHandler"
#include "Pieces/EventLoop"

#include <OpenThreads/Thread>

#include <iostream>


namespace Pieces
{

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
        OpenThreads::Thread::microSleep(1500000);

        t1.start(2000, Event(2));
        Timer t2(h.eventLoop());
        t2.start(5000, Event(3));
        t2.stop();
    } // Join timers


    h.eventLoop()->quit();
    h.join();
}
