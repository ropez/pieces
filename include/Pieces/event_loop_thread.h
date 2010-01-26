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

#ifndef PIECES_EVENT_LOOP_THREAD_H
#define PIECES_EVENT_LOOP_THREAD_H

#include "OpenThreads/Thread"
#include "Pieces/global"


namespace pcs
{
class EventLoop;
class EventHandler;


/**
 * \class EventLoopThread event_loop_thread.h <Pieces/EventLoopThread>
 * \brief A thread that runs an event loop.
 *
 * EventLoop::exec() blocks the calling thread, and the event handler
 * is called on the same thread. This is a convenience class that runs an
 * eventloop in a background thread, and calls the event handler in this
 * thread.
 *
 * \see HostThread, PeerThread
 * \author Robin Pedersen
 */
class EventLoopThread : public OpenThreads::Thread
{
public:

    /**
     * Create an event loop thread that will send events to the given \a handler.
     */
    EventLoopThread(EventHandler* handler);

    /**
     * Quits the event loop and joins the thread.
     */
    ~EventLoopThread();

    /**
     * Returns a pointer to the internal event loop.
     *
     * Use this to post events.
     */
    EventLoop* eventLoop() const;

protected:

    /**
     * Thread main function, calls \link EventLoop::exec eventLoop()->exec() \endlink.
     */
    virtual void run();

private:
    DISABLE_COPY(EventLoopThread);

    EventHandler* m_handler;
    EventLoop* m_eventLoop;
};

} // namespace pcs

#endif // PIECES_EVENT_LOOP_THREAD_H
