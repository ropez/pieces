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

#include "Pieces/Peer"
#include "Pieces/Debug"
#include "Pieces/EventLoop"
#include "Pieces/GameDataReceiver"
#include "Pieces/TCPConnectionManager"

#include "NetworkEventFilter"


namespace pcs
{

class PeerPrivate
{
public:
    PeerPrivate();

    AutoPointer<EventLoop> eventLoop;
    AutoPointer<TCPConnectionManager> connectionManager;
    AutoPointer<GameDataReceiver> receiver;

    AutoPointer<NetworkEventFilter> networkEventFilter;
};


PeerPrivate::PeerPrivate()
: eventLoop(0)
, connectionManager(0)
, receiver(0)
, networkEventFilter(0)
{
}


Peer::Peer()
: EventHandler()
, d(new PeerPrivate)
{
    d->eventLoop = new EventLoop();
    d->connectionManager = new TCPConnectionManager(eventLoop());
    d->networkEventFilter = new NetworkEventFilter(this, d->connectionManager.get());
}


Peer::~Peer()
{
    delete d;
}


EventLoop* Peer::eventLoop()
{
    return d->eventLoop.get();
}


void Peer::connectTo(const SocketAddress& address)
{
    connectionManager()->connectTo(address);
}


void Peer::postEvent(Event* e)
{
    eventLoop()->postEvent(e);
}


void Peer::sendMessage(const Message& message)
{
    connectionManager()->sendMessage(message);
}


void Peer::exec()
{
    PDEBUG << "Peer running";
    eventLoop()->exec(d->networkEventFilter.get());
}


void Peer::quit()
{
    PDEBUG << "Peer quitting";
    eventLoop()->quit();
}


ConnectionManager* Peer::connectionManager() const
{
    return d->connectionManager.get();
}


GameDataReceiver* Peer::receiver()
{
    // Lazy instantiation
    if (d->receiver.isNull())
    {
        d->receiver = new GameDataReceiver(eventLoop());
    }
    return d->receiver.get();
}

}
