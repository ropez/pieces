
#include "Pieces/EventQueue"

#include <OpenThreads/Condition>
#include <OpenThreads/Mutex>
#include <OpenThreads/ScopedLock>

#include <queue>


namespace Pieces
{
using OpenThreads::Condition;
using OpenThreads::Mutex;
using OpenThreads::ScopedLock;


class EventQueuePrivate
{
public:
    std::queue<Event*> events;

    Mutex mutex;
    Condition cond;
};


EventQueue::EventQueue()
: d(new EventQueuePrivate)
{
}


EventQueue::~EventQueue()
{
    // Pop remaining events
    while (!d->events.empty())
    {
        std::auto_ptr<Event> e(d->events.front());
        d->events.pop();
    }
    delete d;
}


void EventQueue::push(Event* e)
{
    ScopedLock<Mutex> lock(d->mutex);

    d->events.push(e);
    d->cond.signal();
}


std::auto_ptr<Event> EventQueue::pop()
{
    ScopedLock<Mutex> lock(d->mutex);
    while (d->events.empty())
    {
        d->cond.wait(&d->mutex);
    }
    std::auto_ptr<Event> e(d->events.front());
    d->events.pop();

    return e;
}

} // namespace Pieces
