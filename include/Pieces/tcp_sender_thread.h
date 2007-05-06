#ifndef PIECES_TCP_SENDER_THREAD_H
#define PIECES_TCP_SENDER_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace pcs
{
class TCPSocket;
class MessageQueue;
class TCPSenderThreadPrivate;


/**
 * \class TCPSenderThread tcp_sender_thread.h <Pieces/TCPSenderThread>
 * \brief Thread that sends messages.
 *
 * \internal
 * It is unlikely that users of Pieces will have to use this class directly.
 *
 * Messages are send by a background thread that pops messages from a queue.
 * This is a typical producer/consumer model. Messages are sent by starting
 * a sender thread, and push messages to the queue.
 *
 * \see ConnectionManager, TCPConnection, TCPReceiverThread
 * \author Robin Pedersen
 */
class TCPSenderThread : public OpenThreads::Thread
{
public:

    /**
     * Create a sender thread that sends messages on the given TCP socket,
     * and pops from the given message queue.
     */
    TCPSenderThread(TCPSocket* socket, MessageQueue* queue);

    /**
     * Destructor.
     *
     * Calls abort().
     */
    ~TCPSenderThread();

    /**
     * Stops the thread.
     *
     * The thread is not running anymore when this function returns.
     */
    void abort();

protected:

    /**
     * Thread main function.
     */
    virtual void run();

private:
    DISABLE_COPY(TCPSenderThread);

    TCPSenderThreadPrivate* d;
};

} // namespace pcs

#endif // PIECES_TCP_SENDER_THREAD_H
