
#include "Pieces/EventQueue"

#include <OpenThreads/Condition>
#include <OpenThreads/Mutex>

#include <queue>


namespace Pieces
{

class EventQueuePrivate
{
public:
    std::queue<Event> events;

    OpenThreads::Mutex mutex;
    OpenThreads::Condition cond;
};


EventQueue::EventQueue()
    : d(new EventQueuePrivate)
{
}


EventQueue::~EventQueue()
{
    delete d;
}


void EventQueue::push(const Event& e)
{
    d->mutex.lock();
    d->events.push(e);
    d->cond.signal();
    d->mutex.unlock();
}


Event EventQueue::pop()
{
    d->mutex.lock();
    while (d->events.empty())
    {
        d->cond.wait(&d->mutex);
    }
    Event e = d->events.front();
    d->events.pop();
    d->mutex.unlock();

    return e;
}

} // namespace Pieces
