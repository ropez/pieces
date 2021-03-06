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

#ifndef PIECES_EVENT_LOOP_H
#define PIECES_EVENT_LOOP_H

#include "Pieces/Event"


namespace pcs
{
class EventHandler;
class EventQueue;


/**
 * \class EventLoop event_loop.h <Pieces/EventLoop>
 * \brief Basic interface for building event-loops.
 *
 * This class provides an event loop. All events must be handled by an
 * EventHandler. New events are queued (posted) with postEvent().
 *
 * To run the event-loop, call exec(). The thread that called exec() will be
 * used to call the event-handler's event() function for each incoming event,
 * and otherwise blocked.
 *
 * To exit the event loop, and return from exec(), call quit(). This will post
 * a special quit event that is not forwarded to the event handler. The quit
 * event will be at the back of the queue, so all events posted before that
 * will be processed before the loop exits.
 *
 * \author Robin Pedersen
 */
class EventLoop
{
public:

    /**
     * Create event-loop object.
     */
    EventLoop();

    /**
     * Destructor.
     *
     * Deleting a running event-loop is illegal.
     */
    virtual ~EventLoop();

    /**
     * Execute the event-loop.
     *
     * This makes the current thread enter the event-loop, and start processing
     * events. Each event posted with postEvent() results in a call to the
     * event-handler's event() function. This is done on the same thread that
     * called exec().
     *
     * To exit from the event-loop, call quit().
     *
     * This function must only be called from one thread.
     */
    void exec(EventHandler* handler);

    /**
     * Quit the event-loop.
     *
     * Posts a special quit-event. When this event is seens by the internal
     * event dispatcher it returns from the exec() call instead of passing the
     * event to the event handler.
     *
     * \note This function returns immediately.
     * \note This function is thread-safe.
     */
    void quit();

    /**
     * Post an event to the event-loop.
     *
     * The event is queued, and later forwarded to the event-handler.
     *
     * \note This function returns immediately.
     * \note This function is thread-safe.
     */
    void postEvent(Event* e);

private:
    DISABLE_COPY(EventLoop);

    EventQueue* m_queue;
};

} // namespace pcs

#endif // PIECES_EVENT_LOOP_H
