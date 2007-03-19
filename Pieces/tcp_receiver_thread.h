#ifndef PIECES_TCP_RECEIVER_THREAD_H
#define PIECES_TCP_RECEIVER_THREAD_H

#include "OpenThreads/Thread"


namespace Pieces
{
class TCPSocket;
class EventLoop;


/**
 * \class tcp_receiver_thread
 * \brief TODO: write info.
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

protected:
    virtual void run();

private:
    TCPSocket* m_socket;
    EventLoop* m_eventLoop;

    // Disable copy
    TCPReceiverThread(const TCPReceiverThread&);
    TCPReceiverThread& operator=(const TCPReceiverThread&);
};

} // namespace Pieces

#endif // PIECES_TCP_RECEIVER_THREAD_H
