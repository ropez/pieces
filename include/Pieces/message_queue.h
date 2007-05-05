
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
 * This class is used internally to send messages in background threads
 * per connection.
 *
 * It's unlikely that users of Pieces will ever have to use this class directly.
 *
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
