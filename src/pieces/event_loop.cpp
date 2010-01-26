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

#include "Pieces/EventLoop"
#include "Pieces/EventHandler"
#include "Pieces/EventQueue"
#include "Pieces/Exception"
#include "Pieces/Debug"


namespace pcs
{

EventLoop::EventLoop()
: m_queue(new EventQueue)
{
}


EventLoop::~EventLoop()
{
    delete m_queue;
}


void EventLoop::exec(EventHandler* handler)
{
    for (;;)
    {
        // Block while waiting for event
        AutoPointer<Event> e = m_queue->pop();

        // Quit when popping a 0 pointer
        if (e.isNull())
            break;

        try
        {
            // Dispatch the event to the correct event-handler function
            e->dispatch(handler);
        }
        catch (const Exception& e)
        {
            PERROR << "Unhandled exception in event handler: " << e;
        }
    }
}


void EventLoop::quit()
{
    m_queue->push(0);
}


void EventLoop::postEvent(Event* e)
{
    if (e != 0)
    {
        m_queue->push(e);
    }
}

} // namespace pcs
