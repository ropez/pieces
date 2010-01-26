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

#ifndef PIECES_PEER_THREAD_H
#define PIECES_PEER_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace pcs
{
class Peer;


/**
 * \class PeerThread peer_thread.h <Pieces/PeerThread>
 * \brief Thread that executes a peer.
 *
 * This is a convenience class that can be used to run a peer in a background
 * thread.
 *
 * \author Robin Pedersen
 */
class PeerThread : public OpenThreads::Thread
{
public:

    /**
     * Create a thread that will execute the event loop of \a peer.
     */
    PeerThread(Peer* peer);

    /**
     * Destructor, calls abort().
     */
    ~PeerThread();

    /**
     * Calls \link Peer::quit peer->quit() \endlink and waits
     * for the thread to exit.
     */
    void abort();

protected:

    /**
     * Thread main function, calls \link Peer::exec peer->exec() \endlink
     */
    virtual void run();

private:
    DISABLE_COPY(PeerThread);

    Peer* m_peer;
};

} // namespace pcs

#endif // PIECES_HOST_THREAD_H
