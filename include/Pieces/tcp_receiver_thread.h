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
 * This class is meant for internal use.
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
