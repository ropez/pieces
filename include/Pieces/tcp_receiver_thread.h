#ifndef PIECES_TCP_RECEIVER_THREAD_H
#define PIECES_TCP_RECEIVER_THREAD_H

#include "OpenThreads/Thread"
#include "Pieces/global"


namespace pcs
{
class TCPSocket;
class EventLoop;
class TCPReceiverThreadPrivate;

/**
 * \class TCPReceiverThread tcp_receiver_thread.h <Pieces/TCPReceiverThread>
 * \brief Thread that receives messages.
 *
 * \internal
 * It is unlikely that users of Pieces will have to use this class directly.
 *
 * Messages are received on a background thread reading from a TCP socket.
 * When a message is received, a MessageReceivedEvent is posted to the given
 * event loop.
 *
 * \see ConnectionManager, TCPConnection, TCPSenderThread
 * \author Tord Heimdal
 */
class TCPReceiverThread : public OpenThreads::Thread
{
public:

    /**
     * Create a receiver thread that reads messages from the given socket,
     * and posts events to the given event loop.
     */
    TCPReceiverThread(TCPSocket* socket, EventLoop* eventLoop);

    /**
     * Destructor.
     *
     * Calls abort().
     */
    ~TCPReceiverThread();

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
    DISABLE_COPY(TCPReceiverThread);

    TCPReceiverThreadPrivate* d;
};

} // namespace pcs

#endif // PIECES_TCP_RECEIVER_THREAD_H
