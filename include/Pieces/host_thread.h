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

#ifndef PIECES_HOST_THREAD_H
#define PIECES_HOST_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace pcs
{
class Host;


/**
 * \class HostThread host_thread.h <Pieces/HostThread>
 * \brief Thread that executes a host.
 *
 * This is a convenience class that can be used to run a host in a background
 * thread.
 *
 * \author Robin Pedersen
 */
class HostThread : public OpenThreads::Thread
{
public:

    /**
     * Create a thread that will execute the event loop of \a host.
     */
    HostThread(Host* host);

    /**
     * Destructor, calls abort().
     */
    ~HostThread();

    /**
     * Calls \link Host::quit host->quit() \endlink and waits
     * for the thread to exit.
     */
    void abort();

protected:

    /**
     * Thread main function, calls \link Host::exec host->exec() \endlink
     */
    virtual void run();

private:
    DISABLE_COPY(HostThread);

    Host* m_host;
};

} // namespace pcs

#endif // PIECES_HOST_THREAD_H
