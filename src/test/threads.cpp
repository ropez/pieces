
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
        delete m_eventLoop;
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
        
        if (event.type() == 3)
        {
            eventLoop()->quit();
        }
    }

private:
    EventLoop* m_eventLoop;
};

}


int main()
{
    Pieces::Host h;
    h.start();
    
    using Pieces::Timer;
    using Pieces::Event;
    
    Timer* repeating = new Timer(h.eventLoop());
    repeating->setRepeating(true);
    repeating->start(200, Event(222));
    
    {
        Timer t1(h.eventLoop());
        t1.start(999, Event(1));
        
        // Sleep to let the first timer trigger
        OpenThreads::Thread::microSleep(1500000);

        // This timer is not seen, because it's deleted before it's triggered
        t1.start(2000, Event(2));
    }
    
    // kill repeating timer
    delete repeating;
    repeating = 0;
    
    // This timer stops the Host
    Timer t2(h.eventLoop());
    t2.start(5000, Event(3));

    h.join();
}
