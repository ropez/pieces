
#ifndef PIECES_MESSAGE_QUEUE_H
#define PIECES_MESSAGE_QUEUE_H

#include "Pieces/Message"
#include <deque>


namespace pcs
{
class Message;
class MessageQueuePrivate;


/**
 * \class MessageQueue
 * \brief Thread safe message queue.
 *
 * \author Robin Pedersen
 */
class MessageQueue
{
public:

    /**
     * Create an empty message queue
     */
    MessageQueue();

    /**
     * Create a queue initialized width the given messages.
     */
    MessageQueue(const std::deque<msgpair_t>& messages);

    /**
     * Delete the queue.
     *
     * Deleting while a thread is blocked in pop() is undefined.
     */
    ~MessageQueue();

    void push(const msgpair_t& message);
    msgpair_t pop();

private:
    DISABLE_COPY(MessageQueue);
    MessageQueuePrivate* d;
};

} // namespace pcs

#endif // PIECES_MESSAGE_QUEUE_H
