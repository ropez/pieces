
#ifndef PIECES_TCP_LISTENER_THREAD_H
#define PIECES_TCP_LISTENER_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace Pieces
{
class TCPConnectionManager;
class TCPListenerThreadPrivate;


/**
 * \class TCPListenerThread
 * \brief Thread that listens for incoming TCP connections.
 *
 * Adds incoming connections to a connection manager.
 *
 * \author Robin Pedersen
 */
class TCPListenerThread : public OpenThreads::Thread
{
public:
    TCPListenerThread(port_t port, TCPConnectionManager* manager);

    ~TCPListenerThread();

    void abort();

protected:
    virtual void run();

private:
    DISABLE_COPY(TCPListenerThread);

    TCPListenerThreadPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_LISTENER_THREAD_H
