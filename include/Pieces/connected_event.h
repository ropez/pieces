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

#ifndef PIECES_CONNECTED_EVENT_H
#define PIECES_CONNECTED_EVENT_H

#include "Pieces/NetworkEvent"


namespace pcs
{

/**
 * \class ConnectedEvent connected_event.h <Pieces/ConnectedEvent>
 * \brief A network-connect event.
 *
 * Both the Host and the Peer receives a ConnectedEvent after a new connection
 * is added to the ConnectionManager.
 *
 * \todo This is not implemented.
 *
 * \author Tord Heimdal
 */
class ConnectedEvent : public NetworkEvent
{
    friend class AutoPointer<ConnectedEvent>;

public:

    /**
     * Constructor.
     */
    ConnectedEvent(const SocketAddress& sender);

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const;

    /**
     * Calls h->handle(this).
     */
    virtual void dispatch(EventHandler* h);

protected:

    /**
     * Protected destructor prevents stack allocation.
     */
    virtual ~ConnectedEvent();


private:
    DISABLE_COPY(ConnectedEvent);
};

} // namespace pcs

#endif // PIECES_CONNECTED_EVENT_H
