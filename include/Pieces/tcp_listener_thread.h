
#ifndef PIECES_TCP_LISTENER_THREAD_H
#define PIECES_TCP_LISTENER_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace pcs
{
class TCPConnectionManager;
class TCPListenerThreadPrivate;


/**
 * \class TCPListenerThread tcp_listener_thread.h <Pieces/TCPListenerThread>
 * \brief Thread that listens for incoming TCP connections.
 *
 * This class is meant for internal use.
 * It is unlikely that users of Pieces will have to use this class directly.
 *
 * Background thread that listens for incoming TCP connections, and adds
 * connections to a connection manager.
 *
 * \see ConnectionManager, TCPConnectionManager, TCPConnection
 * \author Robin Pedersen
 */
class TCPListenerThread : public OpenThreads::Thread
{
public:

    /**
     * Create a thread that will listen for connections on the given \a port,
     * and add incoming connections to the given \a manager.
     */
    TCPListenerThread(port_t port, TCPConnectionManager* manager);

    /**
     * Destructor.
     *
     * Calls abort().
     */
    ~TCPListenerThread();

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
    DISABLE_COPY(TCPListenerThread);

    TCPListenerThreadPrivate* d;
};

} // namespace pcs

#endif // PIECES_TCP_LISTENER_THREAD_H
