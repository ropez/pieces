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

#ifndef PIECES_EVENT_FILTER_H
#define PIECES_EVENT_FILTER_H

#include "Pieces/EventHandler"


namespace pcs
{


/**
 * \class EventFilter event_filter.h <Pieces/EventFilter>
 * \brief Base class for event filters.
 *
 * An event filter can be used to handle some event before they are sent to the
 * "real" event handler.
 *
 * This is a base class that provides no other features than to forward all
 * events to the next event handler.
 *
 * Many filters can be linked together to a \em chain of event handlers, that
 * together handles events for an event loop.
 *
 * \author Robin Pedersen
 */
class EventFilter : public EventHandler
{
public:

    /**
     * Create an event filter that by default forwards all events to the
     * \a nextHandler.
     */
    EventFilter(EventHandler* nextHandler);

protected:

    /**
     * Forwards all events.
     */
    virtual void handle(Event* event);

private:
    DISABLE_COPY(EventFilter);

    EventHandler* m_nextHandler;
};

} // namespace pcs

#endif // PIECES_EVENT_FILTER_H
