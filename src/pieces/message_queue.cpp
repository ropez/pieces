/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Pieces/MessageQueue"

#include "Pieces/Message"
#include "OpenThreads/Mutex"
#include "OpenThreads/Condition"
#include "OpenThreads/ScopedLock"
#include <queue>


namespace pcs
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

} // namespace pcs
