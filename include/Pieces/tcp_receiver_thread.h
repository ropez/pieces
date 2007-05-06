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
     * TODO: write stuff here.
     */
    TCPReceiverThread(TCPSocket* socket, EventLoop* eventLoop);

    ~TCPReceiverThread();

    void abort();

protected:
    virtual void run();

private:
    DISABLE_COPY(TCPReceiverThread);

    TCPReceiverThreadPrivate* d;
};

} // namespace pcs

#endif // PIECES_TCP_RECEIVER_THREAD_H
