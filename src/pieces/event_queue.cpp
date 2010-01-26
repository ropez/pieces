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

#include "Pieces/EventQueue"

#include <OpenThreads/Condition>
#include <OpenThreads/Mutex>
#include <OpenThreads/ScopedLock>

#include <queue>


namespace pcs
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
        AutoPointer<Event> e(d->events.front());
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


AutoPointer<Event> EventQueue::pop()
{
    ScopedLock<Mutex> lock(d->mutex);
    while (d->events.empty())
    {
        d->cond.wait(&d->mutex);
    }
    AutoPointer<Event> e(d->events.front());
    d->events.pop();

    return e;
}

} // namespace pcs
