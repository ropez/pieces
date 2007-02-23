
#ifndef PIECES_EVENT_LOOP_H
#define PIECES_EVENT_LOOP_H

#include "Event"

#include <queue>


namespace Pieces
{

class EventLoop
{
public:
    EventLoop();
    virtual ~EventLoop();

    void exec();
    void quit();

    void postEvent(const Event& e);

protected:
    virtual void processEvent(const Event& e);

private:
    // Disable copy
    EventLoop(const EventLoop&);
    EventLoop& operator=(const EventLoop&);

    bool m_quit;
    std::queue<Event> m_queue;
};

} // namespace Pieces

#endif // PIECES_EVENT_LOOP_H
