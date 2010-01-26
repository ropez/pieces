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

#ifndef PIECES_NETWORK_EVENT_H
#define PIECES_NETWORK_EVENT_H

#include "Pieces/Event"
#include "Pieces/SocketAddress"
#include "Pieces/Message"


namespace pcs
{


/**
 * \class NetworkEvent network_event.h <Pieces/NetworkEvent>
 * \brief A network-specific event.
 *
 * This is a base class for network-related events. They all have the common
 * property that they contain the address that identifies the socket.
 *
 * \author Tord Heimdal
 */
class NetworkEvent : public Event
{
    friend class AutoPointer<NetworkEvent>;

public:

    /**
     * Creates an event of the given type, from the given sender.
     */
    NetworkEvent(const SocketAddress& sender);

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const;

    /**
     * Calls h->handle(this).
     */
    virtual void dispatch(EventHandler* h);

    /**
     * Returns the address of the process that sent the event.
     */
    SocketAddress getSenderAddress() const;

protected:

    /**
     * Protected destructor prevents stack allocation.
     */
    virtual ~NetworkEvent();

private:
    DISABLE_COPY(NetworkEvent);

    SocketAddress m_sender;
};

} // namespace pcs

#endif // PIECES_NETWORK_EVENT_H
