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

#include "Pieces/MessageReceivedEvent"
#include "Pieces/EventHandler"


namespace pcs
{

MessageReceivedEvent::MessageReceivedEvent(const SocketAddress& sender, const msgpair_t& msg)
: NetworkEvent(sender)
, m_msg(msg)
{
}


AutoPointer<Event> MessageReceivedEvent::clone() const
{
    AutoPointer<MessageReceivedEvent> event(new MessageReceivedEvent(getSenderAddress(), m_msg));

    return AutoPointer<Event>(event);
}


void MessageReceivedEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


msgid_t MessageReceivedEvent::getMessageId() const
{
    return m_msg.first;
}


Message MessageReceivedEvent::getMessage() const
{
    return m_msg.second;
}


MessageReceivedEvent::~MessageReceivedEvent()
{
}

} // namespace pcs
