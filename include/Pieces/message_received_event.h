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

#ifndef PIECES_MESSAGE_RECEIVED_EVENT_H
#define PIECES_MESSAGE_RECEIVED_EVENT_H

#include "Pieces/NetworkEvent"
#include "Pieces/Message"


namespace pcs
{

/**
 * \class MessageReceivedEvent message_received_event.h <Pieces/MessageReceivedEvent>
 * \brief A network-message received event.
 *
 * Both the Host and the Peer receives this kind of event when a message is
 * received by the Pieces message system. This event plays a major role in the
 * Pieces application, because it's where the user is supposed to implement
 * functionality that is triggered by messages.
 *
 * \author Tord Heimdal
 */
class MessageReceivedEvent : public NetworkEvent
{
    friend class AutoPointer<MessageReceivedEvent>;

public:

    /**
     * Constructor, creates an event with the given \a sender, and the pair of
     * message id and message \a msg.
     */
    MessageReceivedEvent(const SocketAddress& sender, const msgpair_t& msg);

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const;

    /**
     * Calls h->handle(this).
     */
    virtual void dispatch(EventHandler* h);

    /**
     * Returns the message id.
     *
     * This is an increasing number that is unique per sender.
     */
    msgid_t getMessageId() const;

    /**
     * Returns the received message.
     */
    Message getMessage() const;

protected:

    /**
     * Protected destructor prevents stack allocation.
     */
    virtual ~MessageReceivedEvent();


private:
    DISABLE_COPY(MessageReceivedEvent);
    msgpair_t m_msg;
};

} // namespace pcs

#endif // PIECES_MESSAGE_RECEIVED_EVENT_H
