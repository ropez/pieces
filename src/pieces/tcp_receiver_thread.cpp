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
#include "Pieces/TCPReceiverThread"
#include "Pieces/Debug"
#include "Pieces/MessageReceivedEvent"
#include "Pieces/DisconnectedEvent"
#include "Pieces/DataStream"
#include "Pieces/TCPSocket"
#include "Pieces/EventLoop"
#include "Pieces/Exception"
#include "Pieces/DisconnectedException"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"

using namespace OpenThreads;


namespace pcs
{

class TCPReceiverThreadPrivate
{
public:
    TCPReceiverThreadPrivate();

    Mutex mutex;

    TCPSocket* socket;
    EventLoop* eventLoop;
};


TCPReceiverThreadPrivate::TCPReceiverThreadPrivate()
: mutex()
, socket(0)
, eventLoop(0)
{
}


TCPReceiverThread::TCPReceiverThread(TCPSocket* socket, EventLoop* eventLoop)
: OpenThreads::Thread()
, d(new TCPReceiverThreadPrivate)
{
    d->socket = socket;
    d->eventLoop = eventLoop;
}


TCPReceiverThread::~TCPReceiverThread()
{
    abort();
    delete d;
}


void TCPReceiverThread::abort()
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


void TCPReceiverThread::run()
{
    ScopedLock<Mutex> lock(d->mutex);

    try
    {
        PDEBUG << "Receiver thread started";

        DataStream ds(d->socket);

        for (;;)
        {
            msgpair_t msg;
            {
                // Release lock while blocked (most of the time)
                ReverseScopedLock<Mutex> unlock(d->mutex);

                ds >> msg.first >> msg.second;
            }

            AutoPointer<MessageReceivedEvent> e(new MessageReceivedEvent(d->socket->getPeerAddress(), msg));
            d->eventLoop->postEvent(e.release());
        }
    }
    catch (const DisconnectedException&)
    {
        d->eventLoop->postEvent(new DisconnectedEvent(d->socket->getPeerAddress()));
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

} // namespace pcs
