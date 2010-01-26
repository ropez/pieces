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

#ifndef PIECES_MESSAGE_QUEUE_H
#define PIECES_MESSAGE_QUEUE_H

#include "Pieces/Message"
#include <deque>


namespace pcs
{
class Message;
class MessageQueuePrivate;


/**
 * \class MessageQueue message_queue.h <Pieces/MessageQueue>
 * \brief Thread safe message queue.
 *
 * This class is meant for internal use.
 * It is unlikely that users of Pieces will have to use this class directly.
 *
 * This class is used internally to send messages in background threads
 * per connection.
 *
 * \see TCPConnection, ConnectionManager
 * \author Robin Pedersen
 */
class MessageQueue
{
public:

    /**
     * Create an empty message queue.
     */
    MessageQueue();

    /**
     * Create a queue initialized with the given messages.
     */
    MessageQueue(const std::deque<msgpair_t>& messages);

    /**
     * Delete the queue.
     *
     * Deleting while a thread is blocked in pop() is undefined.
     */
    ~MessageQueue();

    /**
     * Add the message to the message queue.
     *
     * Signal to wake up a thread blocked in pop().
     */
    void push(const msgpair_t& message);

    /**
     * Returns the first element in the queue.
     *
     * Block if the queue is empty.
     */
    msgpair_t pop();

private:
    DISABLE_COPY(MessageQueue);
    MessageQueuePrivate* d;
};

} // namespace pcs

#endif // PIECES_MESSAGE_QUEUE_H
