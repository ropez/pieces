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

#ifndef PIECES_EVENT_QUEUE_H
#define PIECES_EVENT_QUEUE_H

#include "Pieces/Event"


namespace pcs
{
class EventQueuePrivate;


/**
 * \class EventQueue event_queue.h <Pieces/EventQueue>
 * \brief Thread-safe event queue.
 *
 * This class provides an event queue where events (pointers) can be pushed and popped
 * from different threads. The size of the queue is only limited by the amount
 * of available memory.
 *
 * Events are added (produced) with push(), and removed (consumed) with pop().
 * A thread calling pop() will block if the queue is empty.
 *
 * The push() and pop() functions are thread-safe.
 *
 * \see Event, EventLoop
 * \author Robin Pedersen
 */
class EventQueue
{
public:

    /**
     * Create an empty event queue.
     */
    EventQueue();

    /**
     * Destructor.
     *
     * Deleting an event-queue that other threads are using is illegal.
     */
    ~EventQueue();

    /**
     * Add an event to the end of the queue.
     *
     * This will wake up one thread if there are any blocked in pop().
     */
    void push(Event* e);

    /**
     * Pop one event off the queue and return it.
     *
     * If the queue is empty, this will block until another thread calls
     * push().
     */
    AutoPointer<Event> pop();

private:
    DISABLE_COPY(EventQueue);

    EventQueuePrivate* d;
};

} // namespace pcs

#endif // PIECES_EVENT_QUEUE_H
