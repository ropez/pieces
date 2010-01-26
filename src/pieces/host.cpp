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

#include "Pieces/Host"
#include "Pieces/Debug"
#include "Pieces/EventLoop"
#include "Pieces/GameDataSender"
#include "Pieces/TCPConnectionManager"

#include "NetworkEventFilter"



namespace pcs
{

class HostPrivate
{
public:
    HostPrivate();

    AutoPointer<EventLoop> eventLoop;
    AutoPointer<TCPConnectionManager> connectionManager;
    AutoPointer<GameDataSender> sender;

    AutoPointer<NetworkEventFilter> networkEventFilter;

    std::map<objectid_t, msgid_t> createMessageIds;
};


HostPrivate::HostPrivate()
: eventLoop(0)
, connectionManager(0)
, sender(0)
, networkEventFilter(0)
, createMessageIds()
{
}


Host::Host()
: EventHandler()
, d(new HostPrivate)
{
    d->eventLoop = new EventLoop();
    d->connectionManager = new TCPConnectionManager(eventLoop());
    d->networkEventFilter = new NetworkEventFilter(this, d->connectionManager.get());
}


Host::~Host()
{
    delete d;
}


EventLoop* Host::eventLoop() const
{
    return d->eventLoop.get();
}


void Host::startListening(port_t port)
{
    connectionManager()->startListening(port);
}


void Host::stopListening()
{
    connectionManager()->stopListening();
}


void Host::postEvent(Event* e)
{
    eventLoop()->postEvent(e);
}


msgid_t Host::sendMessage(const Message& message)
{
    return connectionManager()->sendMessage(message);
}


msgid_t Host::sendMessage(const Message& message, msgid_t originalId)
{
    return connectionManager()->sendMessage(message, originalId);
}


void Host::sendCreateObject(objectid_t objectId, int objectType)
{
    Message message(OBJECT_CREATE, Message::FL_PERMANENT);
    message.set(PR_OBJECT_TYPE, objectType);
    message.set(PR_OBJECT_ID, objectId);

    msgid_t msgid = sendMessage(message);
    d->createMessageIds[objectId] = msgid;
}


void Host::sendRemoveObject(objectid_t objectId)
{
    Message message(OBJECT_REMOVE, Message::FL_PERMANENT);
    message.set(PR_OBJECT_ID, objectId);

    if (d->createMessageIds.find(objectId) != d->createMessageIds.end())
    {
        sendMessage(message, d->createMessageIds[objectId]);
        d->createMessageIds.erase(objectId);
    }
    else
    {
        sendMessage(message);
    }
}


void Host::exec()
{
    PDEBUG << "Host running";
    eventLoop()->exec(d->networkEventFilter.get());
}


void Host::quit()
{
    PDEBUG << "Host quitting";
    eventLoop()->quit();
}


ConnectionManager* Host::connectionManager() const
{
    return d->connectionManager.get();
}


GameDataSender* Host::sender()
{
    // Lazy instantiation
    if (d->sender.isNull())
    {
        d->sender = new GameDataSender();
    }
    return d->sender.get();
}

} // namespace pcs
