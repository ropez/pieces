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

#include "Pieces/NetworkEvent"
#include "Pieces/EventHandler"


namespace pcs
{

NetworkEvent::NetworkEvent(const SocketAddress& sender)
: Event()
, m_sender(sender)
{
}


AutoPointer<Event> NetworkEvent::clone() const
{
    AutoPointer<NetworkEvent> event(new NetworkEvent(getSenderAddress()));

    return AutoPointer<Event>(event);
}


void NetworkEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


SocketAddress NetworkEvent::getSenderAddress() const
{
    return m_sender;
}


NetworkEvent::~NetworkEvent()
{
}

} // namespace pcs
