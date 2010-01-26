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

#include "Pieces/TCPSenderThread"
#include "Pieces/TCPSocket"
#include "Pieces/DataStream"
#include "Pieces/Message"
#include "Pieces/MessageQueue"
#include "Pieces/Exception"
#include "Pieces/Debug"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"


namespace pcs
{
using namespace OpenThreads;

class TCPSenderThreadPrivate
{
public:
    TCPSenderThreadPrivate();

    Mutex mutex;

    TCPSocket* socket;
    MessageQueue* queue;
};


TCPSenderThreadPrivate::TCPSenderThreadPrivate()
: socket(0)
, queue(0)
{
}


TCPSenderThread::TCPSenderThread(TCPSocket* socket, MessageQueue* queue)
: Thread()
, d(new TCPSenderThreadPrivate)
{
    d->socket = socket;
    d->queue = queue;
}


TCPSenderThread::~TCPSenderThread()
{
    abort();
    delete d;
}


void TCPSenderThread::abort()
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


void TCPSenderThread::run()
{
    ScopedLock<Mutex> lock(d->mutex);

    try
    {
        DataStream ds(d->socket);

        for (;;)
        {
            // Pop message from queue
            msgpair_t msg;
            {
                // Release lock while blocked (most of the time)
                ReverseScopedLock<Mutex> unlock(d->mutex);

                msg = d->queue->pop();
            }

            // Send message
            ds << msg.first << msg.second << flush;
        }
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

} // namespace pcs
