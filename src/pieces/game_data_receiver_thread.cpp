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

#include "Pieces/GameDataReceiverThread"
#include "Pieces/EventLoop"
#include "Pieces/FrameData"
#include "Pieces/GameData"
#include "Pieces/UDPSocket"
#include "Pieces/Datagram"
#include "Pieces/BufferStream"
#include "Pieces/GameDataEvent"
#include "Pieces/Exception"
#include "Pieces/AutoPointer"
#include "Pieces/Debug"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"


namespace pcs
{
using namespace OpenThreads;

class GameDataReceiverThreadPrivate
{
public:
    GameDataReceiverThreadPrivate();

    Mutex mutex;

    AutoPointer<UDPSocket> socket;

    EventLoop* eventLoop;
};


GameDataReceiverThreadPrivate::GameDataReceiverThreadPrivate()
: socket(0)
, eventLoop(0)
{
}


GameDataReceiverThread::GameDataReceiverThread(EventLoop* eventLoop, port_t port)
: d(new GameDataReceiverThreadPrivate)
{
    d->socket = new UDPSocket;
    d->socket->bind(port);

    d->eventLoop = eventLoop;
}


GameDataReceiverThread::~GameDataReceiverThread()
{
    abort();
    delete d;
}


void GameDataReceiverThread::abort()
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


void GameDataReceiverThread::run()
{
    const size_t MAX_PACKET_SIZE = 0x1000;

    ScopedLock<Mutex> lock(d->mutex);

    try
    {
        for (;;)
        {
            Datagram dg;
            {
                ReverseScopedLock<Mutex> unlock(d->mutex);

                dg = d->socket->receive(MAX_PACKET_SIZE);
            }

            BufferStream bs(dg.getData());

            framenum_t frameNum = 0;
            FrameData frameData;
            bs >> frameNum >> frameData;

            // Notify
            d->eventLoop->postEvent(new GameDataEvent(frameNum, frameData));
        }
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

} // namespace pcs
