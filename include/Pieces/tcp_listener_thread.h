/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

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
