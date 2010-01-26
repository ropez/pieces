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

#ifndef PIECES_EVENT_H
#define PIECES_EVENT_H

#include "Pieces/AutoPointer"
#include "Pieces/ByteArray"


namespace pcs
{
class EventHandler;


/**
 * \class Event event.h <Pieces/Event>
 * \brief Basic event type.
 *
 * This is an abstract base class used by the event system.
 *
 * \see EventQueue, EventLoop, EventHandler
 * \author Robin Pedersen
 */
class Event
{
    friend class AutoPointer<Event>;

public:

    /**
     * Default constructor.
     */
    Event();

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const = 0;

    /**
     * Calls h->handle(this).
     */
    virtual void dispatch(EventHandler* h) = 0;

protected:

    /**
     * Protected destructor prevents stack allocation.
     */
    virtual ~Event();

private:
    DISABLE_COPY(Event);
};

} // namespace pcs

#endif // PIECES_EVENT_H
