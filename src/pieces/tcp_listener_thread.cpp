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

#include "Pieces/TCPListenerThread"
#include "Pieces/TCPConnection"
#include "Pieces/TCPConnectionManager"
#include "Pieces/TCPServer"
#include "Pieces/TCPSocket"
#include "Pieces/Exception"
#include "Pieces/Debug"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"
#include "OpenThreads/Thread"


namespace pcs
{

using namespace OpenThreads;

class TCPListenerThreadPrivate
{
public:
    TCPListenerThreadPrivate();

    Mutex mutex;

    AutoPointer<TCPServer> server;

    port_t port;
    TCPConnectionManager* manager;
};


TCPListenerThreadPrivate::TCPListenerThreadPrivate()
: mutex()
, server(0)
, port(0)
, manager(0)
{
}


TCPListenerThread::TCPListenerThread(port_t port, TCPConnectionManager* manager)
: d(new TCPListenerThreadPrivate)
{
    d->port = port;
    d->manager = manager;

    d->server = new TCPServer;
    d->server->listen(d->port);
}


TCPListenerThread::~TCPListenerThread()
{
    abort();
    delete d;
}


void TCPListenerThread::abort()
{
    ScopedLock<Mutex> lock(d->mutex);

    if (isRunning())
    {
        cancel();

        // Allow thread to exit
        ReverseScopedLock<Mutex> unlock(d->mutex);
        join();
    }
}


void TCPListenerThread::run()
{
    ScopedLock<Mutex> lock(d->mutex);

    try
    {
        PDEBUG << "Server listening";

        for (;;)
        {
            AutoPointer<TCPSocket> s;

            {
                // Release lock while blocked (most of the time)
                ReverseScopedLock<Mutex> unlock(d->mutex);

                s = d->server->accept();
            }

            PINFO << "Accepted connection from " << s->getPeerAddress();

            // Add connection to manager
            d->manager->add(new TCPConnection(s.release()));
        }
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}


} // namespace pcs
