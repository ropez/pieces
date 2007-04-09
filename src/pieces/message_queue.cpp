
#include "Pieces/MessageQueue"

#include "Pieces/Message"
#include "OpenThreads/Mutex"
#include "OpenThreads/Condition"
#include "OpenThreads/ScopedLock"
#include <queue>


namespace Pieces
{
using namespace OpenThreads;

class MessageQueuePrivate
{
public:
    MessageQueuePrivate();
    MessageQueuePrivate(const std::deque<msgpair_t>& messages);

    std::queue<msgpair_t> queue;
    Mutex mutex;
    Condition cond;
};


MessageQueuePrivate::MessageQueuePrivate()
: queue()
, mutex()
, cond()
{
}


MessageQueuePrivate::MessageQueuePrivate(const std::deque<msgpair_t>& messages)
: queue(messages)
, mutex()
, cond()
{
}


MessageQueue::MessageQueue()
: d(new MessageQueuePrivate)
{
}


MessageQueue::MessageQueue(const std::deque<msgpair_t>& messages)
: d(new MessageQueuePrivate(messages))
{
}


MessageQueue::~MessageQueue()
{
    delete d;
}


void MessageQueue::push(const msgpair_t& message)
{
    ScopedLock<Mutex> lock(d->mutex);

    d->queue.push(message);
    d->cond.signal();
}


msgpair_t MessageQueue::pop()
{
    ScopedLock<Mutex> lock(d->mutex);
    while (d->queue.empty())
    {
        d->cond.wait(&d->mutex);
    }
    msgpair_t message(d->queue.front());
    d->queue.pop();

    return message;
}

} // namespace Pieces
