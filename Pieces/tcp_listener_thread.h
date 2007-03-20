
#ifndef PIECES_TCP_LISTENER_THREAD_H
#define PIECES_TCP_LISTENER_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace Pieces
{
class EventLoop;
class TCPListenerThreadPrivate;


/**
 * \class TCPListenerThread
 * \brief Thread that listens for incoming TCP connections.
 *
 *
 * \author Robin Pedersen
 */
class TCPListenerThread : public OpenThreads::Thread
{
public:
    TCPListenerThread(port_t port, EventLoop* eventLoop);

    ~TCPListenerThread();

    void abort();

protected:
    virtual void run();

private:
    // Disable copy operations
    TCPListenerThread(const TCPListenerThread&);
    TCPListenerThread& operator=(const TCPListenerThread&);

    TCPListenerThreadPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_LISTENER_THREAD_H
