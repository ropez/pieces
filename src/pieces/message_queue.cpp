
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
    MessageQueuePrivate(const std::deque<Message>& messages);

    std::queue<Message> queue;
    Mutex mutex;
    Condition cond;
};


MessageQueuePrivate::MessageQueuePrivate()
: queue()
, mutex()
, cond()
{
}


MessageQueuePrivate::MessageQueuePrivate(const std::deque<Message>& messages)
: queue(messages)
, mutex()
, cond()
{
}


MessageQueue::MessageQueue()
: d(new MessageQueuePrivate)
{
}


MessageQueue::MessageQueue(const std::deque<Message>& messages)
: d(new MessageQueuePrivate(messages))
{
}


MessageQueue::~MessageQueue()
{
    delete d;
}


void MessageQueue::push(const Message& message)
{
    ScopedLock<Mutex> lock(d->mutex);

    d->queue.push(message);
    d->cond.signal();
}


Message MessageQueue::pop()
{
    ScopedLock<Mutex> lock(d->mutex);
    while (d->queue.empty())
    {
        d->cond.wait(&d->mutex);
    }
    Message message(d->queue.front());
    d->queue.pop();

    return message;
}

} // namespace Pieces
