#ifndef PIECES_TCP_RECEIVER_THREAD_H
#define PIECES_TCP_RECEIVER_THREAD_H

#include "OpenThreads/Thread"


namespace Pieces
{
class TCPSocket;
class EventLoop;
class TCPReceiverThreadPrivate;

/**
 * \class TCPReceiverThread
 * \brief Thread that creates events by reading from a TCP socket.
 *
 *
 *
 *
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
    // Disable copy
    TCPReceiverThread(const TCPReceiverThread&);
    TCPReceiverThread& operator=(const TCPReceiverThread&);

    TCPReceiverThreadPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_RECEIVER_THREAD_H
